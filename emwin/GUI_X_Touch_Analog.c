#include "GUI.h"

GUI_PID_STATE tc;
void GUI_TOUCH_X_ActivateX(void) {
//	TP_Init();
}

void GUI_TOUCH_X_ActivateY(void) {
//	TP_Init();

}

int  GUI_TOUCH_X_MeasureX(void) {
 
	GUI_TOUCH_GetState(&tc);
  return tc.x;
}

int  GUI_TOUCH_X_MeasureY(void) {
	GUI_TOUCH_GetState(&tc);
return tc.y	;
}





