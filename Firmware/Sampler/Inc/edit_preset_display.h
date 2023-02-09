/////////////////////////////////////////////////////////////////////////////////////////////////
// 	edit_preset_display functions
//	product: DJS-500 sampler
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdint.h"

void int_EPRD_DRAW_ALL_LINES(void);
void int_EPRD_DRAW_ONE_LINE(uint8_t UPDOWN);
void int_EPRD_REDRAW_ONE_LINE(void);												//internal function for EPD for change parameter
void DRAW_EPRD_SELECTOR(uint8_t pos, uint8_t mode);					//draw selector cursor 0 - clear 1 - draw
void int_DRAW_DOT_ICON_SEL(uint16_t posx);									//draw dots for icon selector
void EPRD_PROMPT(uint8_t pos);															//prompt in status bar




/////////////////////////////////////////////////	
//
//internal function for EDIT PAD DISPLAY
//	
void int_EPRD_DRAW_ALL_LINES(void)
	{
	uint8_t E;	
	for(E=0; E<TOTAL_EPRD_POSITIONS; E++)
		{
		if(E==0)			//preset name
			{
			BSP_LCD_SelectLayer(0);	
			BSP_LCD_SetFont(&Font15P);		
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);			
			BSP_LCD_DisplayStringAt(23, 41, presets_list[CURRENT_PRESET], TRANSPARENT_MODE);			//preset name
			}
		else if(E==1)					//COLOR
			{
			BSP_LCD_SelectLayer(0);
			BSP_LCD_SetFont(&Font15P);		
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);				
			switch(presets_color[CURRENT_PRESET])
				{
				case 0:	
					{
					sprintf((char*)Buf, "%s", "PINK");	
					break;		
					}	
				case 1:	
					{
					sprintf((char*)Buf, "%s", "RED");	
					break;		
					}	
				case 2:	
					{
					sprintf((char*)Buf, "%s", "ORANGE");	
					break;		
					}	
				case 3:	
					{
					sprintf((char*)Buf, "%s", "YELLOW");	
					break;		
					}	
				case 4:	
					{
					sprintf((char*)Buf, "%s", "GREEN");	
					break;		
					}
				case 5:	
					{
					sprintf((char*)Buf, "%s", "AQUA");	
					break;		
					}	
				case 6:	
					{
					sprintf((char*)Buf, "%s", "BLUE");	
					break;		
					}	
				case 7:	
					{
					sprintf((char*)Buf, "%s", "PURPLE");	
					break;		
					}
				default: 
					{
					sprintf((char*)Buf, "%s", "NONE");	
					break;		
					}	
				}
			BSP_LCD_DisplayStringAt(157, 66, Buf, TRANSPARENT_MODE);
			}			
		else if(E==2)				//RATING
			{
			BSP_LCD_SelectLayer(0);	
			int_DRAW_STARS_RATING(presets_rating[CURRENT_PRESET], presets_color[CURRENT_PRESET], 1);	
			}		
		else if(E==3)					//ICON
			{
			BSP_LCD_SelectLayer(0);	
			int_DRAW_ICO(presets_icon[CURRENT_PRESET], presets_color[CURRENT_PRESET], 1);
			}
		}	
	return;		
	}	
	
	

/////////////////////////////////////////////////	
//
//internal function for EDIT PAD DISPLAY
//		
void int_EPRD_DRAW_ONE_LINE(uint8_t UPDOWN)
	{
	DRAW_EPRD_SELECTOR(EPRD_Position, 0);
	if(UPDOWN==EPRD_UP)
		{
		EPRD_Position++;
		}
	else if(UPDOWN==EPRD_DOWN)
		{
		EPRD_Position--;	
		}
	DRAW_EPRD_SELECTOR(EPRD_Position, 1);
	EPRD_PROMPT(EPRD_Position);	
	return;	
	}
	
	
/////////////////////////////////////////////////	
//
//			prompt in status bar
//	
void EPRD_PROMPT(uint8_t pos)
	{
	switch (pos)
			{
			case 0:
				{
				sprintf((char*)Buf, "%s", "Push to rename the preset.");	
				break;	
				}
			case 1:
				{
				sprintf((char*)Buf, "%s", "Edit preset color.");	
				break;	
				}
			case 2:
				{
				sprintf((char*)Buf, "%s", "Edit preset rating.");	
				break;	
				}
			case 3:
				{
				sprintf((char*)Buf, "%s", "Edit preset icon.");	
				break;	
				}	
			default:
			break;		
			}	
	uint32_t CURR_LAY;
	CURR_LAY = ActiveLayer;		
	BSP_LCD_SelectLayer(1);	
	BSP_LCD_SetTextColor(0x00000000);
	BSP_LCD_FillRect(9, 255, 180, 12);			
	BSP_LCD_SetFont(&Font8);				
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);	
	BSP_LCD_DisplayStringAt(9, 255, Buf, TRANSPARENT_MODE);	
	BSP_LCD_SelectLayer(CURR_LAY);			
	return;		
	}	
	

///////////////////////////////////////////////////	
////
////internal function for EPRD for change parameter
////		
void int_EPRD_REDRAW_ONE_LINE(void)
	{	
	BSP_LCD_SelectLayer(1);
	if(EPRD_Position<3)
		{	
		BSP_LCD_SetTextColor(0x00000000);	
		FillTriangle(8, 8, 15, 40+(25*EPRD_Position), 54+(25*EPRD_Position), 47+(25*EPRD_Position));	
		BSP_LCD_SelectLayer(0);
		BSP_LCD_SetTextColor(LCD_COLOR_PAPER);				
		BSP_LCD_FillRect(157, 91, 69, 13);	
		}
	else if(EPRD_Position==3)			
		{
		BSP_LCD_SetTextColor(ICON_SELBG_COLOR);
		BSP_LCD_FillRect(365, 68, 8, 11);	
		BSP_LCD_FillRect(459, 68, 8, 11);		
		}	
	BSP_LCD_SelectLayer(0);		
	}
	
	




/////////////////////////////////////////////////	
//
//draw selector cursor 0 - clear 1 - draw
//		
void DRAW_EPRD_SELECTOR(uint8_t pos, uint8_t mode)
	{
	if(pos<3)					//dot-cursor
		{
		BSP_LCD_SelectLayer(1);
		if(mode==0)			//clear	
			{
			BSP_LCD_SetTextColor(0x00000000);		
			}
		else					//draw
			{
			BSP_LCD_SetTextColor(LCD_COLOR_DARK_1);
			}
		BSP_LCD_FillRect(9, 45+(25*pos), 5, 5);
		BSP_LCD_DrawLine(10, 44+(25*pos), 12, 44+(25*pos));	
		BSP_LCD_DrawLine(10, 50+(25*pos), 12, 50+(25*pos));	
		BSP_LCD_DrawLine(8, 46+(25*pos), 8, 48+(25*pos));	
		BSP_LCD_DrawLine(14, 46+(25*pos), 14, 48+(25*pos));			
		}	
	else if(pos==3)						//////////////////icon selector
		{
		BSP_LCD_SelectLayer(1);
		if(mode==0)			//clear	
			{
			BSP_LCD_SetTextColor(0x00000000);
			BSP_LCD_FillRect(364, 28, 105, 96);
			}
		else					//draw
			{
			BSP_LCD_SetTextColor(LCD_COLOR_PAPER);
			BSP_LCD_FillRect(372, 36, 5, 76);		
			BSP_LCD_FillRect(455, 36, 8, 76);	
			BSP_LCD_FillRect(373, 32, 95, 4);		
			BSP_LCD_FillRect(372, 112, 95, 10);		
			BSP_LCD_SetTextColor(ICON_SELBG_COLOR);
			BSP_LCD_FillRect(365, 36, 8, 76);	
			BSP_LCD_DrawLine(364, 37, 364, 110);	
			BSP_LCD_DrawLine(373, 37, 373, 110);	
			BSP_LCD_FillRect(459, 36, 8, 76);		
			BSP_LCD_DrawLine(458, 37, 458, 110);	
			BSP_LCD_DrawLine(467, 37, 467, 110);	
			int_DRAW_DOT_ICON_SEL(0);
			int_DRAW_DOT_ICON_SEL(94);
			}
		return;		
		}
	BSP_LCD_SelectLayer(0);		
	return;		
	}



/////////////////////////////////////////////////	
//
//draw dots for icon selector	
//
void int_DRAW_DOT_ICON_SEL(uint16_t posx)
	{
	BSP_LCD_SetTextColor(LCD_COLOR_PAPER);		
	BSP_LCD_FillRect(367+posx, 72, 4, 4);
	BSP_LCD_DrawPixel(366+posx, 73, LCD_COLOR_PAPER);	
	BSP_LCD_DrawPixel(366+posx, 74, LCD_COLOR_PAPER);	
	BSP_LCD_DrawPixel(371+posx, 73, LCD_COLOR_PAPER);	
	BSP_LCD_DrawPixel(371+posx, 74, LCD_COLOR_PAPER);					
	BSP_LCD_DrawPixel(368+posx, 71, LCD_COLOR_PAPER);		
	BSP_LCD_DrawPixel(369+posx, 71, LCD_COLOR_PAPER);			
	BSP_LCD_DrawPixel(368+posx, 76, LCD_COLOR_PAPER);		
	BSP_LCD_DrawPixel(369+posx, 76, LCD_COLOR_PAPER);	
	BSP_LCD_DrawPixel(366+posx, 72, ICON_SELROND_COLOR);	
	BSP_LCD_DrawPixel(367+posx, 71, ICON_SELROND_COLOR);	
	BSP_LCD_DrawPixel(366+posx, 75, ICON_SELROND_COLOR);	
	BSP_LCD_DrawPixel(367+posx, 76, ICON_SELROND_COLOR);	
	BSP_LCD_DrawPixel(371+posx, 72, ICON_SELROND_COLOR);	
	BSP_LCD_DrawPixel(370+posx, 71, ICON_SELROND_COLOR);	
	BSP_LCD_DrawPixel(371+posx, 75, ICON_SELROND_COLOR);	
	BSP_LCD_DrawPixel(370+posx, 76, ICON_SELROND_COLOR);		
	return;	
	}
	


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



