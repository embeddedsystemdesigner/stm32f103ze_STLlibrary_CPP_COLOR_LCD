#include "GUI.h"
#include "touch.h"
#include "touch_task.h"
#include "stm32f10x.h"



void TouchTask(void) {

  int R,C;
  float res=0;
	

	
	
	
if( (GPIOA->IDR&2048 )==0)  
{	
	
		read_ads(&C,&R);
	
if( (C>149&&C<1900)&&(R>200&&R<1930))
	
{

C=C-145;  //y
res=(float)C/7.3;
C=res;	

R=R-190; //x
res=(float)R/5.4;
R=res;	

	
GUI_TOUCH_StoreState(R, 240-C);
	
}
	


}


else
{
	
GUI_TOUCH_StoreState(-1,-1);	
	
	
}


		
		
	
  

  GUI_TOUCH_Exec();  
	
	
  } 


