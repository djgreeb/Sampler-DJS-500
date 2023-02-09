/////////////////////////////////////////////////////////////////////////////////////////////////
// 	edit preset gui part
//	product: DJS-500 sampler
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdint.h"



void int_EP_DRAW_ALL_LINES(void);														//internal function for EDIT preset menu
void int_EP_DRAW_ONE_LINE(uint8_t UPDOWN);									//internal function for EDIT preset menu

////////////////////////////////////////////////////	
//internal function for EDIT preset menu	
//	
void int_EP_DRAW_ALL_LINES(void)
	{
	BSP_LCD_SelectLayer(1);		
	uint8_t E;
	for(E=0; E<(TOTAL_EP_POSITIONS);E++)
		{
		if(E==CurrentEPPosition)
			{
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);	
			}
		else
			{
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			}
		BSP_LCD_DisplayStringAt(260, 24+(19*E), EP_BASE[E], TRANSPARENT_MODE);		
		}	
	BSP_LCD_SelectLayer(0);		
	return;	
	};


	
////////////////////////////////////////////////////	
//internal function for EDIT preset menu	
//	
void int_EP_DRAW_ONE_LINE(uint8_t UPDOWN)
	{
	BSP_LCD_SelectLayer(0);
	BSP_LCD_SetTextColor(LCD_COLOR_DARK_1);
	BSP_LCD_FillRect(254, (21+(19*CurrentEPPosition)), 115, 19);
	BSP_LCD_SelectLayer(1);	
	BSP_LCD_SetFont(&Font15P);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);	
	BSP_LCD_DisplayStringAt(260, 24+(19*CurrentEPPosition), EP_BASE[CurrentEPPosition], TRANSPARENT_MODE);	
	if(UPDOWN==EP_UP)
		{
		CurrentEPPosition++;
		}
	else
		{
		CurrentEPPosition--;	
		}
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(260, 24+(19*CurrentEPPosition), EP_BASE[CurrentEPPosition], TRANSPARENT_MODE);			
	BSP_LCD_SelectLayer(0);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);																											////////////////////////	
	BSP_LCD_DrawLine(257, (21+(19*CurrentEPPosition)), 365, (21+(19*CurrentEPPosition)));				//
	BSP_LCD_DrawLine(255, (22+(19*CurrentEPPosition)), 367, (22+(19*CurrentEPPosition)));				//
	BSP_LCD_FillRect(254, (23+(19*CurrentEPPosition)), 115, 7);																	//	Draw selected cursor	
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_2);																										//
	BSP_LCD_FillRect(254, (30+(19*CurrentEPPosition)), 115, 5);																	//
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_1);																										//
	BSP_LCD_FillRect(254, (35+(19*CurrentEPPosition)), 115, 3);																	//
	BSP_LCD_DrawLine(255, (38+(19*CurrentEPPosition)), 367, (38+(19*CurrentEPPosition)));				//
	BSP_LCD_DrawLine(257, (39+(19*CurrentEPPosition)), 365, (39+(19*CurrentEPPosition)));				//////////////////////////
	return;
	};	
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	