/*----------------------------------------------------------------------------
 * Name:    Retarget.c
 * Purpose: 'Retarget' layer for target-dependent low level functions
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2012 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <rt_misc.h>
#include "GUI.h"

#pragma import(__use_no_semihosting_swi)


extern int  SER_PutChar(int c);                               /* see Serial.c */
extern int  SER_GetChar(void);                                /* see Serial.c */


struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;
FILE __stderr;

static int current_line=0;

int fputc(int c, FILE *f) {
  if (c == '\n')  {
    SER_PutChar('\r');
		GUI_DispString("\n");
    current_line++;		
		if(current_line==16){ GUI_Clear();  GUI_GotoXY(0,0);}
  }
	
	GUI_DispChar(c);
  return (SER_PutChar(c));
}


int fgetc(FILE *f) {
  return (SER_GetChar());
}


int fclose(FILE* f) {
  return (0);
}


int fseek (FILE *f, long nPos, int nMode)  {
  return (0);
}


int fflush (FILE *f)  {
  return (0);
}

int ferror(FILE *f) {
  /* Your implementation of ferror */
  return (EOF);
}


void _ttywrch(int c) {
  SER_PutChar(c);
}


void _sys_exit(int return_code) {
label:  goto label;  /* endless loop */
}
