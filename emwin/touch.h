///////////////////////////////////////////////////////
                //ADS7843 DRIVER//                   //
																										 //                                               
//pin DCLK is:   PB8                                 //
//pin CS is:     PB9                                 //
//pin DIN is:    PB10                                //
//pin DOUT is:   PB11                                //
//pin IRQ is:    PB12                                //
                                                     //
                                                     //
//this is softwer driver                             //
//developed by bijan vahdati                         //
                                                     //
                                                     //
//////////////////////////////////////////////////////

#include "stm32f10x.h"




#define CMD_RDY 0X90  
#define CMD_RDX	0XD0

#define READ_TIMES 15 
#define LOST_VAL 5	





#define clock_pin 8
#define cs_pin 9
#define output_pin  10
#define input_pin 11



#define out   (1<<output_pin)
#define clk   (1<<clock_pin)
#define cs    (1<<cs_pin)
#define input (2048)
#define PORT  GPIOB





#define out_high         PORT->BSRR=out;
#define out_low          PORT->BRR=out;


#define clk_high         PORT->BSRR=clk;
#define clk_low          PORT->BRR=clk;





#define cs_high          PORT->BSRR=cs;
#define cs_low           PORT->BRR=cs;


#define read_input      (PORT->IDR&input)






void delay_us(int i);
void ads_write_byte(unsigned char num);  
int ads_read(unsigned char CMD);
int ADS_Read_XY(unsigned char xy);
char read_ads(int *x,int *y);
void touch_init(void);




