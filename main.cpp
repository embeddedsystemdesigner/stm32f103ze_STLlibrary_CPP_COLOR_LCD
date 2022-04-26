#include "stm32f10x.h"
#include <stdio.h>
#include <iostream>
#include <limits>
#include <algorithm>
#include <functional>
#include <vector>


// telegram id --->    @eneeir
// github --->  https://github.com/embeddedsystemdesigner
// website  ---> www.enee.ir




extern "C"
{
	
#include "GUI.h"
#include "tftlcd.h"	
	
}




using namespace std;

void delay_us(unsigned int time);
void delay_ms(unsigned int time);



void TIM1_Init (void);
void timer1_enable(void);
void timer1_disable(void);
void GPIO_INIT(void);






int main()
{
char buffer[20];
GUI_Init();
GUI_SetTextMode(GUI_TEXTMODE_NORMAL);
GUI_SetFont(GUI_FONT_20B_ASCII);
GUI_SetColor(GUI_WHITE);	
GUI_SetBkColor(GUI_DARKBLUE);	
GUI_Clear();

cout<<"please enter text"<<endl;
cin.getline(buffer,30,'\n');
GUI_SetColor(GUI_GREEN);		
cout<<buffer<<endl;	


	
while(1)
{


	
}


	
}





void GPIO_INIT(void)
{
GPIO_InitTypeDef GPIO;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);	

	
GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO.GPIO_Pin = GPIO_Pin_4;
GPIO.GPIO_Speed = GPIO_Speed_2MHz;

GPIO_Init(GPIOF,&GPIO);	
	
}
/////////////////////////////////////////////////////////////


void delay_us(unsigned int time)
{
	
	while(time--)	
		{
			
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();	
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();	
    __NOP();__NOP();	

		}
	
}
/////////////////////////////////////////////////////////////
void delay_ms(unsigned int time)
{
	
	while(time--)	
		{
     delay_us(1000);
	
		}

}



void TIM1_Init (void)
{
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;              /* enable clock for TIM1    */

  TIM1->PSC   = ( 7200 - 1);                       /* set prescaler   = 10KHz  */
  TIM1->ARR   = ( 10000 - 1);                       /* set auto-reload = 500ms */
  TIM1->RCR   =  0;;                               /* set repetition counter   */

  TIM1->DIER = TIM_DIER_UIE;                       /* Update Interrupt enable  */
  TIM1->CR1  &=~ TIM_CR1_CEN;                      /* timer1 disable             */	
  NVIC_DisableIRQ(TIM1_UP_IRQn);                   /* TIM1   Interrupt disable  */	

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void timer1_enable(void)
{

	TIM1->CR1  |= TIM_CR1_CEN; 
	NVIC_SetPriority(TIM1_UP_IRQn,1);		/* timer enable             */	
	NVIC_EnableIRQ(TIM1_UP_IRQn);                    /* TIM1   Interrupt enable  */
		
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void timer1_disable(void)
{
		
	TIM1->CR1  &=~ TIM_CR1_CEN;                      /* timer disable             */	
	TIM1->CNT=0;	
	NVIC_DisableIRQ(TIM1_UP_IRQn);                   /* TIM1   Interrupt disable  */	
		
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern "C"
{
void TIM1_UP_IRQHandler (void)
{

  if (TIM1->SR & (TIM_SR_UIF))
		{       

    TIM1->SR &= ~(TIM_SR_UIF);           
    }
		
		
}

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



