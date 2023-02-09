/////////////////////////////////////////////////////////////////////////////////////////////////
// 	edit fl list GUI part
//	product: DJS-500 sampler
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdint.h"

void int_FL_DRAW_ALL_LINES(void);														//internal function for FL list
void int_FL_REDRAW_ONE_LINE(void);													//internal function FL for change parameter
void int_FL_DRAW_ONE_LINE(uint8_t UPDOWN);									//internal function for FL

/////////////////////////////////////////////////	
//
//	internal function for FL list
//	
void int_FL_DRAW_ALL_LINES(void)
	{
	uint8_t E;
	for(E=0; E<8;E++)
		{
		if(E==FLCurrentCursorPosition)
			{
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);	
			}
		else
			{
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			}
		sprintf((char*)Buf, "PAD %01u", E+1);	
		BSP_LCD_DisplayStringAt(22, 21+(19*E), Buf, TRANSPARENT_MODE);	
		if(FAST_LOADING[E]<TOTAL_PRESETS)
			{
			sprintf((char*)Buf, "%s", "|");
			BSP_LCD_DisplayStringAt(96, 21+(19*E), Buf, TRANSPARENT_MODE);	
			BSP_LCD_DisplayStringAt(115, 21+(19*E), presets_list[FAST_LOADING[E]], TRANSPARENT_MODE);	
			}
		else
			{
			sprintf((char*)Buf, "%s", "Empty");
			BSP_LCD_DisplayStringAt(96, 21+(19*E), Buf, TRANSPARENT_MODE);	
			}	
		}	
	BSP_LCD_SelectLayer(0);		
	return;	
	}

	
	
/////////////////////////////////////////////////	
//
//		internal function FL for change parameter	
//		
void int_FL_REDRAW_ONE_LINE(void)
	{
	BSP_LCD_SelectLayer(1);		
	BSP_LCD_SetTextColor(0x00000000);	
	BSP_LCD_FillRect(75, 18+(19*FLCurrentCursorPosition), 404, 19);		
	BSP_LCD_SetFont(&Font15P);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	if(FAST_LOADING[FLCurrentCursorPosition]<TOTAL_PRESETS)
		{
		sprintf((char*)Buf, "%s", "|");
		BSP_LCD_DisplayStringAt(96, 21+(19*FLCurrentCursorPosition), Buf, TRANSPARENT_MODE);		
		BSP_LCD_DisplayStringAt(115, 21+(19*FLCurrentCursorPosition), presets_list[FAST_LOADING[FLCurrentCursorPosition]], TRANSPARENT_MODE);	
		}
	else
		{
		sprintf((char*)Buf, "%s", "Empty");
		BSP_LCD_DisplayStringAt(96, 21+(19*FLCurrentCursorPosition), Buf, TRANSPARENT_MODE);	
		}	
	BSP_LCD_SelectLayer(0);		
	return;	
	}		

	
/////////////////////////////////////////////////	
//
//		internal function for FL
//	
void int_FL_DRAW_ONE_LINE(uint8_t UPDOWN)
	{
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);				
	BSP_LCD_FillRect(1, 18+(19*FLCurrentCursorPosition), 73, 19);
	BSP_LCD_FillRect(75, 18+(19*FLCurrentCursorPosition), 404, 19);		
	BSP_LCD_SetTextColor(LCD_COLOR_DARK_1);	
	BSP_LCD_DrawLine(0, 18+(19*FLCurrentCursorPosition), 479, 18+(19*FLCurrentCursorPosition));	
	BSP_LCD_SelectLayer(1);		
	BSP_LCD_SetFont(&Font15P);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);	
	sprintf((char*)Buf, "PAD %01u", FLCurrentCursorPosition+1);	
	BSP_LCD_DisplayStringAt(22, 21+(19*FLCurrentCursorPosition), Buf, TRANSPARENT_MODE);	
	if(FAST_LOADING[FLCurrentCursorPosition]<TOTAL_PRESETS)
		{
		sprintf((char*)Buf, "%s", "|");
		BSP_LCD_DisplayStringAt(96, 21+(19*FLCurrentCursorPosition), Buf, TRANSPARENT_MODE);
		BSP_LCD_DisplayStringAt(115, 21+(19*FLCurrentCursorPosition), presets_list[FAST_LOADING[FLCurrentCursorPosition]], TRANSPARENT_MODE);	
		}
	else
		{
		sprintf((char*)Buf, "%s", "Empty");
		BSP_LCD_DisplayStringAt(96, 21+(19*FLCurrentCursorPosition), Buf, TRANSPARENT_MODE);	
		}		
	if(UPDOWN==EFL_UP)
		{
		FLCurrentCursorPosition++;
		}
	else
		{
		FLCurrentCursorPosition--;	
		}	
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);	
	sprintf((char*)Buf, "PAD %01u", FLCurrentCursorPosition+1);	
	BSP_LCD_DisplayStringAt(22, 21+(19*FLCurrentCursorPosition), Buf, TRANSPARENT_MODE);	
	if(FAST_LOADING[FLCurrentCursorPosition]<TOTAL_PRESETS)
		{
		sprintf((char*)Buf, "%s", "|");
		BSP_LCD_DisplayStringAt(96, 21+(19*FLCurrentCursorPosition), Buf, TRANSPARENT_MODE);	
		BSP_LCD_DisplayStringAt(115, 21+(19*FLCurrentCursorPosition), presets_list[FAST_LOADING[FLCurrentCursorPosition]], TRANSPARENT_MODE);	
		}
	else
		{
		sprintf((char*)Buf, "%s", "Empty");
		BSP_LCD_DisplayStringAt(96, 21+(19*FLCurrentCursorPosition), Buf, TRANSPARENT_MODE);	
		}		
	BSP_LCD_SelectLayer(0);	
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);	
	BSP_LCD_FillRect(1, (18+(19*FLCurrentCursorPosition)), 73, 9);			////Draw selected cursor	
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_2);
	BSP_LCD_FillRect(1, (27+(19*FLCurrentCursorPosition)), 73, 5);
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_1);
	BSP_LCD_FillRect(1, (32+(19*FLCurrentCursorPosition)), 73, 5);
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_3);		
	BSP_LCD_FillRect(75, (18+(19*FLCurrentCursorPosition)), 404, 9);			////Draw selected cursor	
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_5);
	BSP_LCD_FillRect(75, (27+(19*FLCurrentCursorPosition)), 404, 5);
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_4);
	BSP_LCD_FillRect(75, (32+(19*FLCurrentCursorPosition)), 404, 5);				
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	FillTriangle(7, 7, 14, 20+(19*FLCurrentCursorPosition), 34+(19*FLCurrentCursorPosition), 27 +(19*FLCurrentCursorPosition));	
	return;	
	}	
	

/////////////////////////////////////////////////////////////////////////////////////////////////

