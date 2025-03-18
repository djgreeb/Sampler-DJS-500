/////////////////////////////////////////////////////////////////////////////////////////////////
// 	preset list GUI part
//	product: DJS-500 sampler
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdint.h"

void int_MPRST_DRAW_ALL_LINES(void);													//internal function for PRESETS LIST
void int_MPRST_DRAW_ONE_LINE(uint8_t UPDOWN);								//internal function for PRESETS LIST
void int_int_MPRST(void);																		//internal function for PRESETS LIST
void intDrawLayer0_MPRST(uint8_t CCP); 											//draw layer 0 for PRESET LIST
void int_int_draw_selected_cursor(uint8_t pos);							//draw white line selected cursor

/////////////////////////////////	
//
//internal function for PRESETS LIST
void int_MPRST_DRAW_ALL_LINES(void)
	{
	uint16_t E;
	uint8_t pnumber, shft;	
	BSP_LCD_SelectLayer(1);	
	for(E=0;E<13 && TOTAL_PRESETS>(E+CurrentMPRSTPosition-1);E++)
		{				
		if(moveable_preset==(MPRSTCCP+CurrentMPRSTPosition-1))
			{
			pnumber = E+CurrentMPRSTPosition-1;			
			}
		else
			{
			if(E==MPRSTCCP)
				{
				pnumber = moveable_preset;
				}	
			else
				{
				pnumber = E+CurrentMPRSTPosition-1;
				if(MPRSTCCP==0)
					{
					if(moveable_preset<(E+CurrentMPRSTPosition-1))	
						{
						pnumber++;	
						}
					pnumber--;	
					}
				else
					{
					if(moveable_preset<=(E+CurrentMPRSTPosition-1))	
						{
						pnumber++;	
						}
					if(MPRSTCCP<=E)	
						{
						pnumber--;	
						}	
					}
				}		
			}
		if(E==MPRSTCCP)
			{
			BSP_LCD_SetTextColor(MOVE_PRESET_COLOR);
			shft = 40;	
			}
		else if(pnumber==CURRENT_PRESET)	//current preset		
			{
			BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
			shft = 0;	
			}
		else
			{
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			shft = 0;	
			}		
		BSP_LCD_DisplayStringAt(39+shft, 20+(19*E), presets_list[pnumber], INFO_MODE);	
		sprintf((char*)Buf, "%s", "|");
		BSP_LCD_DisplayStringAt(20+shft, 20+(19*E), Buf, INFO_MODE);		
		}	
	int_int_MPRST();	
	BSP_LCD_SelectLayer(0);
	ReDrawScroll(TOTAL_PRESETS, CurrentMPRSTPosition);		
	return;	
	};
	
	
///////////////////////////////////////////////////////////////	
//	
//internal function for PRESETS LIST (COMMON INFO PART)
//	
void int_int_MPRST(void)
	{
	uint8_t E;	
	BSP_LCD_SetTextColor(0x00000000);	
	BSP_LCD_FillRect(296, 40, 87, 13);		//clear
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	sprintf((char *)Buf , "%1lu>%1lu", moveable_preset+1, MPRSTCCP+CurrentMPRSTPosition);		
	BSP_LCD_DisplayStringAt(296, 39, Buf, TRANSPARENT_MODE);		
	return;	
	};	
	
	
/////////////////////////////////////////////////	
//
//draw layer 0 for PRESET LIST
//
void intDrawLayer0_MPRST(uint8_t CCP)
	{
	uint8_t E, k;	
	uint16_t j;	
	BSP_LCD_SetTextColor(LCD_COLOR_DARK_1);
	for(E=0;E<7;E++)															/////Draw gray lines
		{
		if(CCP%2==1 | (CCP/2) != E)
			{		
			BSP_LCD_FillRect(14, 18+(38*E), 256, 19);
			}			
		}
	BSP_LCD_SetTextColor(LCD_COLOR_DARK_2);
	for(E=0;E<6;E++)
		{
		if(CCP%2==0 | (CCP/2) != E)
			{				
			BSP_LCD_FillRect(14, 37+(38*E), 256, 19);
			}			
		}
	int_int_draw_selected_cursor(CCP);		
	return;	
	};

	
/////////////////////////////////	
//
//internal function for PRESETS LIST
//	
void int_MPRST_DRAW_ONE_LINE(uint8_t UPDOWN)							
	{
	uint8_t stp;		
	uint8_t pnumber;		
	if(MPRSTCCP%2==0)
		{
		BSP_LCD_SetTextColor(LCD_COLOR_DARK_1);
		}
	else
		{
		BSP_LCD_SetTextColor(LCD_COLOR_DARK_2);
		}
	BSP_LCD_FillRect(14, 18+(19*MPRSTCCP), 256, 19);
	BSP_LCD_SelectLayer(1);	
	BSP_LCD_SetFont(&Font15P);
	BSP_LCD_SetTextColor(0x00000000);								//delete previous text
	BSP_LCD_FillRect(14, 18+(19*MPRSTCCP), 256, 19);	

	if(UPDOWN==MPRST_UP)
		{
		stp = MPRSTCCP+1;
		}
	else
		{
		stp = MPRSTCCP-1;	
		}	
	if(moveable_preset==(stp+CurrentMPRSTPosition-1))
		{
		pnumber = MPRSTCCP+CurrentMPRSTPosition-1;	
		}
	else
		{
		pnumber = stp+CurrentMPRSTPosition-1;	
		if(moveable_preset<=(stp+CurrentMPRSTPosition-1))	
			{
			pnumber++;	
			}
		if(MPRSTCCP<=stp)	
			{
			pnumber--;	
			}								
		}	
	if(pnumber==CURRENT_PRESET)
		{
		BSP_LCD_SetTextColor(LCD_COLOR_GREEN);	
		}	
	else
		{
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		}	
	BSP_LCD_DisplayStringAt(39,20+(19*MPRSTCCP), presets_list[pnumber], INFO_MODE);	
	sprintf((char*)Buf, "%s", "|");
	BSP_LCD_DisplayStringAt(20, 20+(19*MPRSTCCP),Buf, INFO_MODE);	
	if(UPDOWN==MPRST_UP)
		{
		MPRSTCCP++;
		}
	else
		{
		MPRSTCCP--;	
		}
	BSP_LCD_SetTextColor(0x00000000);								//delete previous text
	BSP_LCD_FillRect(14, 18+(19*MPRSTCCP), 256, 19);		
	BSP_LCD_SetTextColor(MOVE_PRESET_COLOR);
	BSP_LCD_DisplayStringAt(79, 20+(19*MPRSTCCP), presets_list[moveable_preset], INFO_MODE);	
	sprintf((char*)Buf, "%s", "|");
	BSP_LCD_DisplayStringAt(60, 20+(19*MPRSTCCP),Buf, INFO_MODE);	
	int_int_MPRST();	
	BSP_LCD_SelectLayer(0);
	int_int_draw_selected_cursor(MPRSTCCP);	
	return;			
	};	

	
	
/////////////////////////////////	
//
//   draw white line selected cursor
//		
void int_int_draw_selected_cursor(uint8_t pos)
	{
	uint32_t color, c1, c2;	
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);		
	BSP_LCD_FillRect(47, (18+(19*pos)), 209, 9);			//////////////////////////////	
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_2);
	BSP_LCD_FillRect(47, (27+(19*pos)), 209, 5);
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_1);
	BSP_LCD_FillRect(47, (32+(19*pos)), 209, 5);
	intDrawTriangle(pos);		
	if(MPRSTCCP%2==0)
		{
		color = LCD_COLOR_DARK_1;	
		c1 = LCD_COLOR_DARK_11;
		c2 = LCD_COLOR_DARK_12;			
		}			
	else
		{
		color = LCD_COLOR_DARK_2;	
		c1 = LCD_COLOR_DARK_21;
		c2 = LCD_COLOR_DARK_22;		
		}
	BSP_LCD_DrawPixel(46, 18+(19*pos), color);		
	BSP_LCD_DrawPixel(47, 18+(19*pos), color);	
	BSP_LCD_DrawPixel(48, 18+(19*pos), color);	
	BSP_LCD_DrawPixel(49, 18+(19*pos), color);	
	BSP_LCD_DrawPixel(50, 18+(19*pos), color);	
	BSP_LCD_DrawPixel(51, 18+(19*pos), color);
	BSP_LCD_DrawPixel(52, 18+(19*pos), color);	
	BSP_LCD_DrawPixel(53, 18+(19*pos), c1);	
	BSP_LCD_DrawPixel(54, 18+(19*pos), c2);						//	
	BSP_LCD_DrawPixel(46, 19+(19*pos), color);		
	BSP_LCD_DrawPixel(47, 19+(19*pos), color);	
	BSP_LCD_DrawPixel(48, 19+(19*pos), color);	
	BSP_LCD_DrawPixel(49, 19+(19*pos), color);	
	BSP_LCD_DrawPixel(50, 19+(19*pos), color);	
	BSP_LCD_DrawPixel(51, 19+(19*pos), color);
	BSP_LCD_DrawPixel(52, 19+(19*pos), c1);	
	BSP_LCD_DrawPixel(53, 19+(19*pos), c2);						//
	BSP_LCD_DrawPixel(46, 20+(19*pos), color);		
	BSP_LCD_DrawPixel(47, 20+(19*pos), color);	
	BSP_LCD_DrawPixel(48, 20+(19*pos), color);	
	BSP_LCD_DrawPixel(49, 20+(19*pos), color);
	BSP_LCD_DrawPixel(50, 20+(19*pos), color);
	BSP_LCD_DrawPixel(51, 20+(19*pos), c1);	
	BSP_LCD_DrawPixel(52, 20+(19*pos), c2);						//
	BSP_LCD_DrawPixel(46, 21+(19*pos), color);		
	BSP_LCD_DrawPixel(47, 21+(19*pos), color);	
	BSP_LCD_DrawPixel(48, 21+(19*pos), color);
	BSP_LCD_DrawPixel(49, 21+(19*pos), color);
	BSP_LCD_DrawPixel(50, 21+(19*pos), c1);	
	BSP_LCD_DrawPixel(51, 21+(19*pos), c2);					//
	BSP_LCD_DrawPixel(46, 22+(19*pos), color);		
	BSP_LCD_DrawPixel(47, 22+(19*pos), color);
	BSP_LCD_DrawPixel(48, 22+(19*pos), color);
	BSP_LCD_DrawPixel(49, 22+(19*pos), c1);	
	BSP_LCD_DrawPixel(50, 22+(19*pos), c2);				//
	BSP_LCD_DrawPixel(46, 23+(19*pos), color);	
	BSP_LCD_DrawPixel(47, 23+(19*pos), color);
	BSP_LCD_DrawPixel(48, 23+(19*pos), c1);	
	BSP_LCD_DrawPixel(49, 23+(19*pos), c2);				//
	BSP_LCD_DrawPixel(47, 24+(19*pos), c1);		
	BSP_LCD_DrawPixel(48, 24+(19*pos), c2);				//
	BSP_LCD_DrawPixel(47, 25+(19*pos), c2);			//
	BSP_LCD_DrawPixel(46, 26+(19*pos), c1);			//	
	BSP_LCD_DrawPixel(46, 27+(19*pos), c2);			//		
	BSP_LCD_DrawPixel(46, 28+(19*pos), c1);			//		
	BSP_LCD_DrawPixel(46, 36+(19*pos), color);		
	BSP_LCD_DrawPixel(47, 36+(19*pos), color);	
	BSP_LCD_DrawPixel(48, 36+(19*pos), color);	
	BSP_LCD_DrawPixel(49, 36+(19*pos), color);	
	BSP_LCD_DrawPixel(50, 36+(19*pos), color);	
	BSP_LCD_DrawPixel(51, 36+(19*pos), color);	
	BSP_LCD_DrawPixel(52, 36+(19*pos), color);
	BSP_LCD_DrawPixel(53, 36+(19*pos), c1);	
	BSP_LCD_DrawPixel(54, 36+(19*pos), c2);			//	
	BSP_LCD_DrawPixel(46, 35+(19*pos), color);		
	BSP_LCD_DrawPixel(47, 35+(19*pos), color);	
	BSP_LCD_DrawPixel(48, 35+(19*pos), color);	
	BSP_LCD_DrawPixel(49, 35+(19*pos), color);	
	BSP_LCD_DrawPixel(50, 35+(19*pos), color);
	BSP_LCD_DrawPixel(51, 35+(19*pos), color);
	BSP_LCD_DrawPixel(52, 35+(19*pos), c1);	
	BSP_LCD_DrawPixel(53, 35+(19*pos), c2);			//	
	BSP_LCD_DrawPixel(46, 34+(19*pos), color);		
	BSP_LCD_DrawPixel(47, 34+(19*pos), color);	
	BSP_LCD_DrawPixel(48, 34+(19*pos), color);	
	BSP_LCD_DrawPixel(49, 34+(19*pos), color);	
	BSP_LCD_DrawPixel(50, 34+(19*pos), color);
	BSP_LCD_DrawPixel(51, 34+(19*pos), c1);	
	BSP_LCD_DrawPixel(52, 34+(19*pos), c2);			//
	BSP_LCD_DrawPixel(46, 33+(19*pos), color);		
	BSP_LCD_DrawPixel(47, 33+(19*pos), color);	
	BSP_LCD_DrawPixel(48, 33+(19*pos), color);	
	BSP_LCD_DrawPixel(49, 33+(19*pos), color);
	BSP_LCD_DrawPixel(50, 33+(19*pos), c1);	
	BSP_LCD_DrawPixel(51, 33+(19*pos), c2);			//	
	BSP_LCD_DrawPixel(46, 32+(19*pos), color);		
	BSP_LCD_DrawPixel(47, 32+(19*pos), color);
	BSP_LCD_DrawPixel(48, 32+(19*pos), color);
	BSP_LCD_DrawPixel(49, 32+(19*pos), c1);	
	BSP_LCD_DrawPixel(50, 32+(19*pos), c2);			//
	BSP_LCD_DrawPixel(46, 31+(19*pos), color);	
	BSP_LCD_DrawPixel(47, 31+(19*pos), color);
	BSP_LCD_DrawPixel(48, 31+(19*pos), c1);	
	BSP_LCD_DrawPixel(49, 31+(19*pos), c2);			//
	BSP_LCD_DrawPixel(47, 30+(19*pos), c1);		
	BSP_LCD_DrawPixel(48, 30+(19*pos), c2);			//
	BSP_LCD_DrawPixel(47, 29+(19*pos), c2);			//	
	return;	
	}
	
	
	
	
	
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
	
	
	
	
	
	
	
	