#include "GUI.h"
#include "GUIDRV_FlexColor.h"
#include "tftlcd.h"




#define XSIZE_PHYS  240
#define YSIZE_PHYS  320


#define COLOR_CONVERSION  GUICC_565


#define DISPLAY_DRIVER  GUIDRV_FLEXCOLOR



#define NUM_BUFFERS   1
#define NUM_VSCREENS  0



/*********************************************************************
*
*     
*
**********************************************************************
*/
#ifndef   VXSIZE_PHYS
  #define VXSIZE_PHYS XSIZE_PHYS
#endif
#ifndef   VYSIZE_PHYS
  #define VYSIZE_PHYS YSIZE_PHYS
#endif
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   COLOR_CONVERSION
  #error Color conversion not defined!
#endif
#ifndef   DISPLAY_DRIVER
  #error No display driver defined!
#endif





static void _LcdSetReg(U16 Data) {
LCD_WR_REG(Data);	
}

/**************************************************************************************************************
 
 *****************************************************************************************************************/
static void _LcdWriteData(U16 Data) {
LCD_WR_DATA(Data);	
}
/**************************************************************************************************************
 
 *****************************************************************************************************************/
static void _LcdWriteDataMultiple(U16 * pData, int NumItems) {
  while (NumItems--) {
    LCD_WR_DATA(*pData);
		pData++;
  }
}

/**************************************************************************************************************
  
 *****************************************************************************************************************/
static void _LcdReadDataMultiple(U16 * pData, int NumItems) {
	

	
 while (NumItems--) {
   *pData = LCD_RD_DATA();
		pData++;
  }
 
	

	
}

/**************************************************************************************************************
       

*****************************************************************************************************************/
/*
static void _WriteReg(U16 Reg, U16 Data) {
tft_WriteReg(Reg,Data);
}
*/

/**************************************************************************************************************
     
 *****************************************************************************************************************/
static void _InitLcdController(void) {
 tft_init();
  //LCD_Init_init();
	//while(0){_WriteReg(4,4);} //make compiler happy
}

/**************************************************************************************************************
 
 *****************************************************************************************************************/
static void _Init(void) {
		//touch_SPI_Configuration();
  _InitLcdController();
}


/**************************************************************************************************************
  
 *****************************************************************************************************************/
void LCD_X_Config(void) {
	
	
  GUI_DEVICE * pDevice;
  CONFIG_FLEXCOLOR Config = {0};
  GUI_PORT_API PortAPI = {0};
	

  //
  // 
  //
  pDevice = GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);
  //
  // 
  //
  LCD_SetSizeEx (0, XSIZE_PHYS , YSIZE_PHYS);
  LCD_SetVSizeEx(0, VXSIZE_PHYS, VYSIZE_PHYS);
  //
  //
 // Config.Orientation =GUI_SWAP_XY|GUI_MIRROR_X;
  //Config.RegEntryMode=0x6870;
	//Config.FirstSEG=0;
	//Config.FirstCOM=0;
  GUIDRV_FlexColor_Config(pDevice, &Config);
  //
  //
  PortAPI.pfWrite16_A0  = _LcdSetReg;
  PortAPI.pfWrite16_A1  = _LcdWriteData;
  PortAPI.pfWriteM16_A1 = _LcdWriteDataMultiple;
  PortAPI.pfReadM16_A1  = _LcdReadDataMultiple;
  GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66708, GUIDRV_FLEXCOLOR_M16C0B16);
	

	
	
}

















int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  int r;
  (void) LayerIndex;
  (void) pData;

  switch (Cmd) {
  //
  // Required
  //
  case LCD_X_INITCONTROLLER: {
    //
    // Called during the initialization process in order to set up the
    // display controller and put it into operation. If the display
    // controller is not initialized by any external routine this needs
    // to be adapted by the customer...
    //
    // ...
    _Init();
		

    return 0;
  }
  default:
    r = -1;
  }
  return r;
}

/*************************** End of file ****************************/

