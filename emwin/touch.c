#include "stm32f10x.h"
#include "touch.h"





void delay_us(int i)
{

	int j=0,k=0;

	for(j=0; j<10; j++)
	for(k=0; k<i; k++);	
	
	
}
//////////////////////////////////////////////////////////////////////////////

void ads_write_byte(unsigned char num)    
{ 
	unsigned char count=0;
	cs_low
	delay_us(100);
	for(count=0;count<8;count++)  
		{ 	  
			if(num&0x80)
				{
					out_high
				}  
				
			else 
				{
					out_low
				}  
				
			num<<=1;    
			clk_low
			delay_us(10);	   	 
			clk_high
			delay_us(10);
		} 
	
	clk_low

}
//////////////////////////////////////////////////////////////////////////////

int ads_read(unsigned char CMD)	  
{ 	 
	unsigned char count=0; 	  
	unsigned int	Num=0;



	ads_write_byte(CMD);
	delay_us(100);		   	    

	for(count=0;count<16;count++)  
		{ 				  
		Num<<=1; 	 
		clk_low
		delay_us(10);	   	 
		clk_high
		delay_us(10);


		if(read_input>0)  
		Num++; 		 
		}

	Num>>=4;
	cs_high	 
	clk_low
	return(Num);   
}
//////////////////////////////////////////////////////////////////////////////

 int ADS_Read_XY(unsigned char xy)
{
	unsigned int  i, j;
	unsigned int buf[READ_TIMES];
	unsigned int sum=0;
	unsigned int temp;
	
	
	for(i=0;i<READ_TIMES;i++)
		{				 
		buf[i]=ads_read(xy);	    
		}	
		
	for(i=0;i<READ_TIMES-1; i++)
		{
		for(j=i+1;j<READ_TIMES;j++)
			{
			if(buf[i]>buf[j])
				{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
				}
			}
		}	  
		
	sum=0;
	for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)sum+=buf[i];
	temp=sum/(READ_TIMES-2*LOST_VAL);
	return temp;   
}
//////////////////////////////////////////////////////////////////////////////

char read_ads(int *x,int *y)
{
	unsigned int xtemp,ytemp;			 	 		  
	xtemp=ADS_Read_XY(CMD_RDX);
	ytemp=ADS_Read_XY(CMD_RDY);	  												   
	if(xtemp<100||ytemp<100)return 0;							
	*x=xtemp;
	*y=ytemp;
	return 1;												
}
//////////////////////////////////////////////////////////////////////////////

void touch_init(void)
{

	RCC->APB2ENR |=RCC_APB2ENR_IOPBEN;           
	PORT->CRH   &= ~ ( (0xf<< ((clock_pin-8)*4)) |(0xf<< ((cs_pin-8)*4)) |(0xf<<((output_pin-8)*4))|(0xf<<((input_pin-8)*4))  );                  
	PORT->CRH   |=( (3<<((clock_pin-8)*4))|(3<<((cs_pin-8)*4))|(3<<((output_pin-8)*4))|(4<<((input_pin-8)*4))    ); 	
	
}
//////////////////////////////////////////////////////////////////////////////



