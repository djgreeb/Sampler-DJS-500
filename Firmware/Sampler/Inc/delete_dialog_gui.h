/////////////////////////////////////////////////////////////////////////////////////////////////
// 	delete dialog gui part
//	product: DJS-500 sampler
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdint.h"

void int_DD_DRAW_ALL_LINES(void);														//internal function for DELETE DIALOG
void int_DD_DRAW_ONE_LINE(uint8_t UPDOWN);									//internal function for DELETE DIALOG												
											
////////////////////////////////////////////////////	
//internal function for DELETE DIALOG	
//	
void int_DD_DRAW_ALL_LINES(void)
	{
	BSP_LCD_SelectLayer(1);		
	uint8_t E;
	for(E=0; E<(TOTAL_DD_POSITIONS);E++)
		{
		if(E==CurrentDDPosition)
			{
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);	
			}
		else
			{
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			}
		BSP_LCD_DisplayStringAt(190+(74*E), 136, DD_BASE[E], TRANSPARENT_MODE);		
		}	
	BSP_LCD_SelectLayer(0);		
	return;	
	};


	
////////////////////////////////////////////////////	
//internal function for DELETE DIALOG
//	
void int_DD_DRAW_ONE_LINE(uint8_t UPDOWN)
	{
	BSP_LCD_SelectLayer(0);
	BSP_LCD_SetTextColor(DIALOG_BACK_COLOR);
	BSP_LCD_FillRect(167+(80*CurrentDDPosition), 133, 65, 19);
	BSP_LCD_SelectLayer(1);	
	BSP_LCD_SetFont(&Font15P);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);	
	BSP_LCD_DisplayStringAt(190+(74*CurrentDDPosition), 136, DD_BASE[CurrentDDPosition], TRANSPARENT_MODE);	
	if(UPDOWN==DELDIALOG_UP)
		{
		CurrentDDPosition++;
		}
	else
		{
		CurrentDDPosition--;	
		}
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(190+(74*CurrentDDPosition), 136, DD_BASE[CurrentDDPosition], TRANSPARENT_MODE);			
	BSP_LCD_SelectLayer(0);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);																										////////////////////////	
	BSP_LCD_DrawLine(170+(80*CurrentDDPosition), 133, 228+(80*CurrentDDPosition), 133);				//
	BSP_LCD_DrawLine(168+(80*CurrentDDPosition), 134, 230+(80*CurrentDDPosition), 134);				//
	BSP_LCD_FillRect(167+(80*CurrentDDPosition), 135, 65, 7);																	//	Draw selected cursor	
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_2);																									//
	BSP_LCD_FillRect(167+(80*CurrentDDPosition), 142, 65, 5);																	//
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_1);																									//
	BSP_LCD_FillRect(167+(80*CurrentDDPosition), 147, 65, 3);																	//
	BSP_LCD_DrawLine(168+(80*CurrentDDPosition), 150, 230+(80*CurrentDDPosition), 150);				//
	BSP_LCD_DrawLine(170+(80*CurrentDDPosition), 151, 228+(80*CurrentDDPosition), 151);				//////////////////////////	
	return;
	};
											
											
											
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	