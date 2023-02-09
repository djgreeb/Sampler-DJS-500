/////////////////////////////////////////////////////////////////////////////////////////////////
// 	edit utility gui part
//	product: DJS-500 sampler
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdint.h"

void int_EU_DRAW_ALL_LINES(void);														//internal function for EDIT UTILITY
void int_EU_DRAW_ONE_LINE(uint8_t UPDOWN);									//internal function for EDIT UTILITY


////////////////////////////////////////////////////	
//internal function for EDIT UTILITY
//	
void int_EU_DRAW_ALL_LINES(void)
	{
	BSP_LCD_SelectLayer(1);		
	uint8_t E;
	for(E=0; E<TOTAL_EU_POSITIONS;E++)
		{
		if(E==CurrentEUPosition)
			{
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);	
			}
		else
			{
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			}
		BSP_LCD_DisplayStringAt(241, 24+(19*E), EU_BASE[E], TRANSPARENT_MODE);		
		}	
	BSP_LCD_SelectLayer(0);		
	return;	
	}												
					

	
////////////////////////////////////////////////////	
//internal function for EDIT UTILITY
//	
void int_EU_DRAW_ONE_LINE(uint8_t UPDOWN)
	{
	BSP_LCD_SelectLayer(0);
	BSP_LCD_SetTextColor(LCD_COLOR_DARK_1);
	BSP_LCD_FillRect(235, (21+(19*CurrentEUPosition)), 153, 19);
	BSP_LCD_SelectLayer(1);	
	BSP_LCD_SetFont(&Font15P);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);	
	BSP_LCD_DisplayStringAt(241, 24+(19*CurrentEUPosition), EU_BASE[CurrentEUPosition], TRANSPARENT_MODE);	
	if(UPDOWN==EU_UP)
		{
		CurrentEUPosition++;
		}
	else
		{
		CurrentEUPosition--;	
		}
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(241, 24+(19*CurrentEUPosition), EU_BASE[CurrentEUPosition], TRANSPARENT_MODE);			
	BSP_LCD_SelectLayer(0);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);																											////////////////////////	
	BSP_LCD_DrawLine(238, (21+(19*CurrentEUPosition)), 384, (21+(19*CurrentEUPosition)));				//
	BSP_LCD_DrawLine(236, (22+(19*CurrentEUPosition)), 386, (22+(19*CurrentEUPosition)));				//
	BSP_LCD_FillRect(235, (23+(19*CurrentEUPosition)), 153, 7);																	//	Draw selected cursor	
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_2);																										//
	BSP_LCD_FillRect(235, (30+(19*CurrentEUPosition)), 153, 5);																	//
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_1);																										//
	BSP_LCD_FillRect(235, (35+(19*CurrentEUPosition)), 153, 3);																	//
	BSP_LCD_DrawLine(236, (38+(19*CurrentEUPosition)), 386, (38+(19*CurrentEUPosition)));				//
	BSP_LCD_DrawLine(238, (39+(19*CurrentEUPosition)), 384, (39+(19*CurrentEUPosition)));				//////////////////////////
	return;
	}											

												

	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	