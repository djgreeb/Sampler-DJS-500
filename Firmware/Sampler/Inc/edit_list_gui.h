/////////////////////////////////////////////////////////////////////////////////////////////////
// 	edit list gui part
//	product: DJS-500 sampler
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdint.h"

void int_EL_DRAW_ALL_LINES(void);														//internal function for EDIT LIST menu
void int_EL_DRAW_ONE_LINE(uint8_t UPDOWN);									//internal function for EDIT LIST menu


////////////////////////////////////////////////////	
//internal function for EDIT LIST	
//	
void int_EL_DRAW_ALL_LINES(void)
	{
	BSP_LCD_SelectLayer(1);		
	uint8_t E;
	for(E=0; E<TOTAL_EL_POSITIONS;E++)
		{
		if(E==CurrentELPosition)
			{
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);	
			}
		else
			{
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			}
		BSP_LCD_DisplayStringAt(231, 24+(19*E), EL_BASE[E], TRANSPARENT_MODE);		
		}	
	BSP_LCD_SelectLayer(0);		
	return;	
	}												
					

	
////////////////////////////////////////////////////	
//internal function for EDIT LIST	
//	
void int_EL_DRAW_ONE_LINE(uint8_t UPDOWN)
	{
	BSP_LCD_SelectLayer(0);
	BSP_LCD_SetTextColor(LCD_COLOR_DARK_1);
	BSP_LCD_FillRect(225, (21+(19*CurrentELPosition)), 173, 19);
	BSP_LCD_SelectLayer(1);	
	BSP_LCD_SetFont(&Font15P);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);	
	BSP_LCD_DisplayStringAt(231, 24+(19*CurrentELPosition), EL_BASE[CurrentELPosition], TRANSPARENT_MODE);	
	if(UPDOWN==EL_UP)
		{
		CurrentELPosition++;
		}
	else
		{
		CurrentELPosition--;	
		}
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(231, 24+(19*CurrentELPosition), EL_BASE[CurrentELPosition], TRANSPARENT_MODE);			
	BSP_LCD_SelectLayer(0);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);																											////////////////////////	
	BSP_LCD_DrawLine(228, (21+(19*CurrentELPosition)), 394, (21+(19*CurrentELPosition)));				//
	BSP_LCD_DrawLine(226, (22+(19*CurrentELPosition)), 396, (22+(19*CurrentELPosition)));				//
	BSP_LCD_FillRect(225, (23+(19*CurrentELPosition)), 173, 7);																	//	Draw selected cursor	
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_2);																										//
	BSP_LCD_FillRect(225, (30+(19*CurrentELPosition)), 173, 5);																	//
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_1);																										//
	BSP_LCD_FillRect(225, (35+(19*CurrentELPosition)), 173, 3);																	//
	BSP_LCD_DrawLine(226, (38+(19*CurrentELPosition)), 396, (38+(19*CurrentELPosition)));				//
	BSP_LCD_DrawLine(228, (39+(19*CurrentELPosition)), 394, (39+(19*CurrentELPosition)));				//////////////////////////
	return;
	}											

												
												



	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	