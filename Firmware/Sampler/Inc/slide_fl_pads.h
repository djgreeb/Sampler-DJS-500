/////////////////////////////////////////////////////////////////////////////////////////////////
// 	pads slide animation for FL presets
//	product: DJS-500 sampler
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdint.h"

void  SLIDE_PAD(uint8_t y, uint8_t pad, uint8_t clear);								//slide pads	
void int_real_color_pads(void);															//draw pads perimeter with real colors
void fl_load_animation(uint8_t pad);																//animation display for load FL preset


///////////////////////////////////////////////////////////////	
//	
//		slide pads		
//		input frame 0..134
//		
void  SLIDE_PAD(uint8_t y, uint8_t pad, uint8_t clear)
	{
	if(y==0)
		{
		return;	
		}		
	uint16_t len;	
	uint32_t work_color, x, fill_color;	
	uint8_t pad_en;	
	x = y*590;
	x = x/1340;	
	if(FAST_LOADING[pad]>63)
		{
		work_color = PERIPH_PAD_GRADIENT_0;
		fill_color = LCD_COLOR_BLACK;	
		pad_en = 0;	
		}		
	else
		{
		work_color = PADS_LABEL_COLOR[presets_color[FAST_LOADING[pad]]];
		fill_color = PADS_LABEL_LOW_COLOR[presets_color[FAST_LOADING[pad]]];	
		pad_en = 1;	
		}			
	if((pad==0) || (pad==3) || (pad==4) || (pad==7))
		{		
		if(x<21)
			{
			x = 0;	
			return;	
			}
		else
			{
			x-=20;
			if(x==39)
				{
				x = 118;	
				}
			else
				{
				x*=3;
				}
			}	
		}	
	if(clear==0)
		{
		BSP_LCD_SetTextColor(0x00000000);	
		}
	else
		{
		BSP_LCD_SetTextColor(work_color);	
		}
	if(pad==6)										//////////////////////////////////PAD 6
		{
		BSP_LCD_DrawHLine(301-x, y-1, 116);	
		if(y>1)	
			{
			BSP_LCD_DrawHLine(302-x, y-2, 114);	
			}
		if(y>2)	
			{
			BSP_LCD_DrawHLine(303-x, y-3, 112);	
			}		
		if(y>3)		//draw vertical lines
			{
			if(y<101)
				{
				BSP_LCD_DrawVLine(301-x, 0, y);	
				BSP_LCD_DrawVLine(302-x, 0, y);
				BSP_LCD_DrawVLine(303-x, 0, y);
				BSP_LCD_DrawVLine(416-x, 0, y);	
				BSP_LCD_DrawVLine(415-x, 0, y);
				BSP_LCD_DrawVLine(414-x, 0, y);	
				}				
			else
				{
				BSP_LCD_DrawVLine(301-x, y-100, 99);	
				BSP_LCD_DrawVLine(302-x, y-99, 97);
				BSP_LCD_DrawVLine(303-x, y-98, 95);	
				BSP_LCD_DrawVLine(416-x, y-100, 99);	
				BSP_LCD_DrawVLine(415-x, y-99, 97);
				BSP_LCD_DrawVLine(414-x, y-98, 95);		
				}
			if(clear==1)
				{					
				BSP_LCD_SetTextColor(fill_color);	
				}	
			if(y>98)
				{	
				BSP_LCD_FillRect(304-x, y-98, 110, 95);	
				}
			else
				{
				BSP_LCD_FillRect(304-x, 0, 110, y-3);		
				}
			if(clear==1)
				{
				BSP_LCD_SetTextColor(work_color);	
				}	
			}		
		if(y>98)
			{
			BSP_LCD_DrawHLine(303-x, y-99, 112);		
			}
		if(y>99)
			{
			BSP_LCD_DrawHLine(302-x, y-100, 114);		
			}
		if(y>100)
			{
			BSP_LCD_DrawHLine(301-x, y-101, 116);	
			}	
		if(y>54)				//print preset name on FL pad
			{
			BSP_LCD_SetFont(&Font8);	
			sprintf((char*)Buf, "%s", presets_list[FAST_LOADING[pad]]);
			Buf[15] = 0;			//15 symbols max!				
			len = strlen(Buf)*7;	
			if(len<100)	
				{
				len = (100-len)>>1;
				}
			else
				{
				len = 0;	
				}	
			BSP_LCD_DisplayStringAt(len+309-x, y-55, Buf, TRANSPARENT_MODE);
			}
		}			
	else if(pad==5)										//////////////////////////////////PAD 5
		{
		BSP_LCD_DrawHLine(63+x, y-1, 116);	
		if(y>1)	
			{
			BSP_LCD_DrawHLine(64+x, y-2, 114);	
			}
		if(y>2)	
			{
			BSP_LCD_DrawHLine(65+x, y-3, 112);	
			}		
		if(y>3)		//draw vertical lines
			{
			if(y<101)
				{
				BSP_LCD_DrawVLine(63+x, 0, y);	
				BSP_LCD_DrawVLine(64+x, 0, y);
				BSP_LCD_DrawVLine(65+x, 0, y);
				BSP_LCD_DrawVLine(178+x, 0, y);	
				BSP_LCD_DrawVLine(177+x, 0, y);
				BSP_LCD_DrawVLine(176+x, 0, y);	
				}				
			else
				{
				BSP_LCD_DrawVLine(63+x, y-100, 99);	
				BSP_LCD_DrawVLine(64+x, y-99, 97);
				BSP_LCD_DrawVLine(65+x, y-98, 95);	
				BSP_LCD_DrawVLine(178+x, y-100, 99);	
				BSP_LCD_DrawVLine(177+x, y-99, 97);
				BSP_LCD_DrawVLine(176+x, y-98, 95);		
				}
			if(clear==1)
				{
				BSP_LCD_SetTextColor(fill_color);	
				}	
			if(y>98)
				{	
				BSP_LCD_FillRect(66+x, y-98, 110, 95);	
				}
			else
				{
				BSP_LCD_FillRect(66+x, 0, 110, y-3);		
				}
			if(clear==1)
				{
				BSP_LCD_SetTextColor(work_color);	
				}	
			}		
		if(y>98)
			{
			BSP_LCD_DrawHLine(65+x, y-99, 112);		
			}
		if(y>99)
			{
			BSP_LCD_DrawHLine(64+x, y-100, 114);		
			}
		if(y>100)
			{
			BSP_LCD_DrawHLine(63+x, y-101, 116);	
			}	
		if(y>54 && (pad_en==1))				//print preset name on FL pad
			{
			BSP_LCD_SetFont(&Font8);	
			sprintf((char*)Buf, "%s", presets_list[FAST_LOADING[pad]]);
			Buf[15] = 0;			//15 symbols max!				
			len = strlen(Buf)*7;	
			if(len<100)	
				{
				len = (100-len)>>1;
				}
			else
				{
				len = 0;	
				}	
			BSP_LCD_DisplayStringAt(len+71+x, y-55, Buf, TRANSPARENT_MODE);
			}
		}	
	else if(pad==2)										//////////////////////////////////PAD 2
		{
		BSP_LCD_DrawHLine(301-x, 272-y, 116);	
		if(y>1)	
			{
			BSP_LCD_DrawHLine(302-x, 273-y, 114);	
			}
		if(y>2)	
			{
			BSP_LCD_DrawHLine(303-x, 274-y, 112);	
			}		
		if(y>3)		//draw vertical lines
			{
			if(y<101)
				{
				BSP_LCD_DrawVLine(301-x, 272-y, y);	
				BSP_LCD_DrawVLine(302-x, 272-y, y);
				BSP_LCD_DrawVLine(303-x, 272-y, y);
				BSP_LCD_DrawVLine(416-x, 272-y, y);	
				BSP_LCD_DrawVLine(415-x, 272-y, y);
				BSP_LCD_DrawVLine(414-x, 272-y, y);	
				}				
			else
				{
				BSP_LCD_DrawVLine(301-x, 273-y, 99);	
				BSP_LCD_DrawVLine(302-x, 274-y, 97);
				BSP_LCD_DrawVLine(303-x, 275-y, 95);	
				BSP_LCD_DrawVLine(416-x, 273-y, 99);	
				BSP_LCD_DrawVLine(415-x, 274-y, 97);
				BSP_LCD_DrawVLine(414-x, 275-y, 95);		
				}
			if(clear==1)
				{
				BSP_LCD_SetTextColor(fill_color);	
				}	
			if(y>98)
				{	
				BSP_LCD_FillRect(304-x, 275-y, 110, 95);	
				}
			else
				{
				BSP_LCD_FillRect(304-x, 275-y, 110, y-3);		
				}
			if(clear==1)
				{
				BSP_LCD_SetTextColor(work_color);	
				}	
			}		
		if(y>98)
			{
			BSP_LCD_DrawHLine(303-x, 370-y, 112);		
			}
		if(y>99)
			{
			BSP_LCD_DrawHLine(302-x, 371-y, 114);		
			}
		if(y>100)
			{
			BSP_LCD_DrawHLine(301-x, 372-y, 116);	
			}	
		if((y>57) && (pad_en==1))				//print preset name on FL pad
			{
			BSP_LCD_SetFont(&Font8);	
			sprintf((char*)Buf, "%s", presets_list[FAST_LOADING[pad]]);
			Buf[15] = 0;			//15 symbols max!				
			len = strlen(Buf)*7;	
			if(len<100)	
				{
				len = (100-len)>>1;
				}
			else
				{
				len = 0;	
				}	
			BSP_LCD_DisplayStringAt(len+309-x, 318-y, Buf, TRANSPARENT_MODE);
			}
		}			
	else if(pad==1)										//////////////////////////////////PAD 1
		{
		BSP_LCD_DrawHLine(63+x, 272-y, 116);	
		if(y>1)	
			{
			BSP_LCD_DrawHLine(64+x, 273-y, 114);	
			}
		if(y>2)	
			{
			BSP_LCD_DrawHLine(65+x, 274-y, 112);	
			}		
		if(y>3)		//draw vertical lines
			{
			if(y<101)
				{
				BSP_LCD_DrawVLine(63+x, 272-y, y);	
				BSP_LCD_DrawVLine(64+x, 272-y, y);
				BSP_LCD_DrawVLine(65+x, 272-y, y);
				BSP_LCD_DrawVLine(178+x, 272-y, y);	
				BSP_LCD_DrawVLine(177+x, 272-y, y);
				BSP_LCD_DrawVLine(176+x, 272-y, y);	
				}				
			else
				{
				BSP_LCD_DrawVLine(63+x, 273-y, 99);	
				BSP_LCD_DrawVLine(64+x, 274-y, 97);
				BSP_LCD_DrawVLine(65+x, 275-y, 95);	
				BSP_LCD_DrawVLine(178+x, 273-y, 99);	
				BSP_LCD_DrawVLine(177+x, 274-y, 97);
				BSP_LCD_DrawVLine(176+x, 275-y, 95);		
				}
			if(clear==1)
				{
				BSP_LCD_SetTextColor(fill_color);	
				}	
			if(y>98)
				{	
				BSP_LCD_FillRect(66+x, 275-y, 110, 95);	
				}
			else
				{
				BSP_LCD_FillRect(66+x, 275-y, 110, y-3);		
				}
			if(clear==1)
				{
				BSP_LCD_SetTextColor(work_color);	
				}	
			}		
		if(y>98)
			{
			BSP_LCD_DrawHLine(65+x, 370-y, 112);		
			}
		if(y>99)
			{
			BSP_LCD_DrawHLine(64+x, 371-y, 114);		
			}
		if(y>100)
			{
			BSP_LCD_DrawHLine(63+x, 372-y, 116);	
			}	
		if((y>57) && (pad_en==1))				//print preset name on FL pad
			{
			BSP_LCD_SetFont(&Font8);	
			sprintf((char*)Buf, "%s", presets_list[FAST_LOADING[pad]]);
			Buf[15] = 0;			//15 symbols max!				
			len = strlen(Buf)*7;	
			if(len<100)	
				{
				len = (100-len)>>1;
				}
			else
				{
				len = 0;	
				}	
			BSP_LCD_DisplayStringAt(len+71+x, 318-y, Buf, TRANSPARENT_MODE);
			}
		}		
	else if(pad==7)										//////////////////////////////////PAD 7
		{
		len = x;
		if(len>116)
			{
			len = 116;	
			}
		BSP_LCD_DrawHLine(480-x, y-1, len);
		if((y>1) && (x>1))	
			{		
			len = x;
			if(len>115)
				{
				len = 115;	
				}
			BSP_LCD_DrawHLine(481-x, y-2, len-1);	
			}
		if((y>2) && (x>2))	
			{
			len = x;
			if(len>114)
				{
				len = 114;	
				}	
			BSP_LCD_DrawHLine(482-x, y-3, len-2);	
			}		
		if(y>3)		//draw vertical lines
			{
			if(y<101)
				{
				BSP_LCD_DrawVLine(480-x, 0, y);	
				if(x>1)
					{		
					BSP_LCD_DrawVLine(481-x, 0, y);
					}
				if(x>2)
					{	
					BSP_LCD_DrawVLine(482-x, 0, y);
					}
				if(x>113)
					{		
					BSP_LCD_DrawVLine(593-x, 0, y);	
					}
				if(x>114)
					{		
					BSP_LCD_DrawVLine(594-x, 0, y);	
					}					
				if(x>115)
					{		
					BSP_LCD_DrawVLine(595-x, 0, y);	
					}							
				}				
			else
				{
				BSP_LCD_DrawVLine(480-x, y-100, 99);	
				BSP_LCD_DrawVLine(481-x, y-99, 97);
				BSP_LCD_DrawVLine(482-x, y-98, 95);
				if(x>113)
					{		
					BSP_LCD_DrawVLine(593-x, y-98, 95);	
					}
				if(x>114)
					{		
					BSP_LCD_DrawVLine(594-x, y-99, 97);	
					}					
				if(x>115)
					{		
					BSP_LCD_DrawVLine(595-x, y-100, 99);	
					}					
				}
			if(clear==1)
				{
				BSP_LCD_SetTextColor(fill_color);	
				}	
			if((y>98) && (x>113))
				{	
				BSP_LCD_FillRect(483-x, y-98, 110, 95);	
				}
			else if(x>3)
				{
				if(y<99)
					{					
					BSP_LCD_FillRect(483-x, 0, x-3, y-3);
					}
				else
					{
					BSP_LCD_FillRect(483-x, y-98, x-3, 95);	
					}					
				}
			if(clear==1)
				{
				BSP_LCD_SetTextColor(work_color);	
				}	
			}		
		if(y>98)
			{
			len = x;	
			if(len>114)
				{
				len = 114;	
				}		
			BSP_LCD_DrawHLine(482-x, y-99, len-2);		
			}
		if(y>99)
			{
			len = x;	
			if(len>115)
				{
				len = 115;	
				}		
			BSP_LCD_DrawHLine(481-x, y-100, len-1);		
			}
		if(y>100)
			{
			len = x;	
			if(len>116)
				{
				len = 116;	
				}		
			BSP_LCD_DrawHLine(480-x, y-101, len);	
			}
		if((x>108) && (pad_en==1))				//print preset name on FL pad
			{
			BSP_LCD_SetFont(&Font8);	
			sprintf((char*)Buf, "%s", presets_list[FAST_LOADING[pad]]);
			Buf[15] = 0;			//15 symbols max!				
			len = strlen(Buf)*7;	
			if(len<100)	
				{
				len = (100-len)>>1;
				}
			else
				{
				len = 0;	
				}	
			BSP_LCD_DisplayStringAt(len+487-x, y-55, Buf, TRANSPARENT_MODE);
			}
		}	
	else if(pad==4)										//////////////////////////////////PAD 4
		{
		if(x>116)
			{
			BSP_LCD_DrawHLine(x-116, y-1, 116);	
			}
		else
			{
			BSP_LCD_DrawHLine(0, y-1, x);
			}
		if((y>1) && (x>1))	
			{		
			if(x>114)
				{	
				BSP_LCD_DrawHLine(x-115, y-2, 114);		
				}
			else
				{
				BSP_LCD_DrawHLine(0, y-2, x-1);		
				}				
			}
		if((y>2) && (x>2))	
			{
			if(x>113)
				{	
				BSP_LCD_DrawHLine(x-114, y-3, 112);		
				}	
			else
				{
				BSP_LCD_DrawHLine(0, y-3, x-2);		
				}				
			}	
		if(y>3)		//draw vertical lines
			{
			if(y<101)
				{
				BSP_LCD_DrawVLine(x-1, 0, y);	
				if(x>1)
					{		
					BSP_LCD_DrawVLine(x-2, 0, y);
					}
				if(x>2)
					{	
					BSP_LCD_DrawVLine(x-3, 0, y);
					}
				if(x>113)
					{		
					BSP_LCD_DrawVLine(x-113, 0, y);	
					}
				if(x>114)
					{		
					BSP_LCD_DrawVLine(x-114, 0, y);	
					}					
				if(x>115)
					{		
					BSP_LCD_DrawVLine(x-115, 0, y);	
					}					
				}				
			else
				{
				BSP_LCD_DrawVLine(x-1, y-100, 99);	
				BSP_LCD_DrawVLine(x-2, y-99, 97);
				BSP_LCD_DrawVLine(x-3, y-98, 95);
				if(x>113)
					{		
					BSP_LCD_DrawVLine(x-114, y-98, 95);	
					}
				if(x>114)
					{		
					BSP_LCD_DrawVLine(x-115, y-99, 97);	
					}					
				if(x>115)
					{		
					BSP_LCD_DrawVLine(x-116, y-100, 99);	
					}					
				}
			if(clear==1)
				{
				BSP_LCD_SetTextColor(fill_color);	
				}	
				
			if((y>98) && (x>113))
				{	
				BSP_LCD_FillRect(x-113, y-98, 110, 95);	
				}
			else if(x>3)
				{
				if(y<99)
					{					
					BSP_LCD_FillRect(0, 0, x-3, y-3);
					}
				else
					{
					if(x>112)
						{
						BSP_LCD_FillRect(x-113, y-98, 110, 95);		
						}						
					else
						{						
						BSP_LCD_FillRect(0, y-98, x-3, 95);
						}							
					}					
				}
			if(clear==1)
				{
				BSP_LCD_SetTextColor(work_color);	
				}	
			}		
		if(y>98)
			{
			if(x>114)
				{	
				BSP_LCD_DrawHLine(x-114, y-99, 112);	
				}		
			else
				{
				BSP_LCD_DrawHLine(0, y-99, x-2);	
				}
			}
		if(y>99)
			{
			if(x>115)
				{
				BSP_LCD_DrawHLine(x-115, y-100, 114);		
				}		
			else
				{
				BSP_LCD_DrawHLine(0, y-100, x-1);		
				}				
			}
		if(y>100)
			{
			if(x>116)
				{
				BSP_LCD_DrawHLine(x-116, y-101, 116);	
				}		
			else
				{
				BSP_LCD_DrawHLine(0, y-101, x);	
				}
			}
		if((x>108) && (pad_en==1))				//print preset name on FL pad
			{
			BSP_LCD_SetFont(&Font8);	
			sprintf((char*)Buf, "%s", presets_list[FAST_LOADING[pad]]);
			Buf[15] = 0;			//15 symbols max!				
			len = strlen(Buf)*7;	
			if(len<100)	
				{
				len = (100-len)>>1;
				}
			else
				{
				len = 0;	
				}	
			BSP_LCD_DisplayStringAt(len+x-108, y-55, Buf, TRANSPARENT_MODE);
			}
		}			
	else if(pad==0)										//////////////////////////////////PAD 0
		{
		if(x>116)
			{
			BSP_LCD_DrawHLine(x-116, 272-y, 116);	
			}
		else
			{
			BSP_LCD_DrawHLine(0, 272-y, x);
			}
		if((y>1) && (x>1))	
			{		
			if(x>114)
				{	
				BSP_LCD_DrawHLine(x-115, 273-y, 114);		
				}
			else
				{
				BSP_LCD_DrawHLine(0, 273-y, x-1);		
				}				
			}
		if((y>2) && (x>2))	
			{
			if(x>113)
				{	
				BSP_LCD_DrawHLine(x-114, 274-y, 112);		
				}	
			else
				{
				BSP_LCD_DrawHLine(0, 274-y, x-2);		
				}				
			}	
		if(y>3)		//draw vertical lines
			{
			if(y<101)
				{
				BSP_LCD_DrawVLine(x-1, 272-y, y);	
				if(x>1)
					{		
					BSP_LCD_DrawVLine(x-2, 272-y, y);
					}
				if(x>2)
					{	
					BSP_LCD_DrawVLine(x-3, 272-y, y);
					}
				if(x>113)
					{		
					BSP_LCD_DrawVLine(x-113, 272-y, y);	
					}
				if(x>114)
					{		
					BSP_LCD_DrawVLine(x-114, 272-y, y);	
					}					
				if(x>115)
					{		
					BSP_LCD_DrawVLine(x-115, 272-y, y);	
					}					
				}				
			else
				{
				BSP_LCD_DrawVLine(x-1, 273-y, 99);	
				BSP_LCD_DrawVLine(x-2, 274-y, 97);
				BSP_LCD_DrawVLine(x-3, 275-y, 95);
				if(x>113)
					{		
					BSP_LCD_DrawVLine(x-114, 275-y, 95);	
					}
				if(x>114)
					{		
					BSP_LCD_DrawVLine(x-115, 274-y, 97);	
					}					
				if(x>115)
					{		
					BSP_LCD_DrawVLine(x-116, 273-y, 99);	
					}					
				}
			if(clear==1)
				{
				BSP_LCD_SetTextColor(fill_color);	
				}	
				
			if((y>98) && (x>113))
				{	
				BSP_LCD_FillRect(x-113, 275-y, 110, 95);	
				}
			else if(x>3)
				{
				if(y<99)
					{					
					BSP_LCD_FillRect(0, 275-y, x-3, y-3);
					}
				else
					{
					if(x>112)
						{
						BSP_LCD_FillRect(x-113, 275-y, 110, 95);		
						}						
					else
						{						
						BSP_LCD_FillRect(0, 275-y, x-3, 95);
						}							
					}					
				}
			if(clear==1)
				{
				BSP_LCD_SetTextColor(work_color);	
				}	
			}		
		if(y>98)
			{
			if(x>114)
				{	
				BSP_LCD_DrawHLine(x-114, 370-y, 112);	
				}		
			else
				{
				BSP_LCD_DrawHLine(0, 370-y, x-2);	
				}
			}
		if(y>99)
			{
			if(x>115)
				{
				BSP_LCD_DrawHLine(x-115, 371-y, 114);		
				}		
			else
				{
				BSP_LCD_DrawHLine(0, 371-y, x-1);		
				}				
			}
		if(y>100)
			{
			if(x>116)
				{
				BSP_LCD_DrawHLine(x-116, 372-y, 116);	
				}		
			else
				{
				BSP_LCD_DrawHLine(0, 372-y, x);	
				}
			}
		if((x>108) && (pad_en==1))				//print preset name on FL pad
			{
			BSP_LCD_SetFont(&Font8);	
			sprintf((char*)Buf, "%s", presets_list[FAST_LOADING[pad]]);
			Buf[15] = 0;			//15 symbols max!				
			len = strlen(Buf)*7;	
			if(len<100)	
				{
				len = (100-len)>>1;
				}
			else
				{
				len = 0;	
				}	
			BSP_LCD_DisplayStringAt(len+x-108, 318-y, Buf, TRANSPARENT_MODE);
			}
		}			
	else if(pad==3)										//////////////////////////////////PAD 3
		{
		len = x;
		if(len>116)
			{
			len = 116;	
			}
		BSP_LCD_DrawHLine(480-x, 272-y, len);
		if((y>1) && (x>1))	
			{		
			len = x;
			if(len>115)
				{
				len = 115;	
				}
			BSP_LCD_DrawHLine(481-x, 273-y, len-1);	
			}
		if((y>2) && (x>2))	
			{
			len = x;
			if(len>114)
				{
				len = 114;	
				}	
			BSP_LCD_DrawHLine(482-x, 274-y, len-2);	
			}		
		if(y>3)		//draw vertical lines
			{
			if(y<101)
				{
				BSP_LCD_DrawVLine(480-x, 272-y, y);	
				if(x>1)
					{		
					BSP_LCD_DrawVLine(481-x, 272-y, y);
					}
				if(x>2)
					{	
					BSP_LCD_DrawVLine(482-x, 272-y, y);
					}
				if(x>113)
					{		
					BSP_LCD_DrawVLine(593-x, 272-y, y);	
					}
				if(x>114)
					{		
					BSP_LCD_DrawVLine(594-x, 272-y, y);	
					}					
				if(x>115)
					{		
					BSP_LCD_DrawVLine(595-x, 272-y, y);	
					}							
				}				
			else
				{
				BSP_LCD_DrawVLine(480-x, 273-y, 99);	
				BSP_LCD_DrawVLine(481-x, 274-y, 97);
				BSP_LCD_DrawVLine(482-x, 275-y, 95);
				if(x>113)
					{		
					BSP_LCD_DrawVLine(593-x, 275-y, 95);	
					}
				if(x>114)
					{		
					BSP_LCD_DrawVLine(594-x, 274-y, 97);	
					}					
				if(x>115)
					{		
					BSP_LCD_DrawVLine(595-x, 273-y, 99);	
					}					
				}
			if(clear==1)
				{
				BSP_LCD_SetTextColor(fill_color);	
				}	
			if((y>98) && (x>113))
				{	
				BSP_LCD_FillRect(483-x, 275-y, 110, 95);	
				}
			else if(x>3)
				{
				if(y<99)
					{					
					BSP_LCD_FillRect(483-x, 275-y, x-3, y-3);
					}
				else
					{
					BSP_LCD_FillRect(483-x, 275-y, x-3, 95);	
					}					
				}
			if(clear==1)
				{
				BSP_LCD_SetTextColor(work_color);	
				}	
			}		
		if(y>98)
			{
			len = x;	
			if(len>114)
				{
				len = 114;	
				}		
			BSP_LCD_DrawHLine(482-x, 370-y, len-2);		
			}
		if(y>99)
			{
			len = x;	
			if(len>115)
				{
				len = 115;	
				}		
			BSP_LCD_DrawHLine(481-x, 371-y, len-1);		
			}
		if(y>100)
			{
			len = x;	
			if(len>116)
				{
				len = 116;	
				}		
			BSP_LCD_DrawHLine(480-x, 372-y, len);	
			}
		if((x>108) && (pad_en==1))				//print preset name on FL pad
			{
			BSP_LCD_SetFont(&Font8);	
			sprintf((char*)Buf, "%s", presets_list[FAST_LOADING[pad]]);
			Buf[15] = 0;			//15 symbols max!				
			len = strlen(Buf)*7;	
			if(len<100)	
				{
				len = (100-len)>>1;
				}
			else
				{
				len = 0;	
				}	
			BSP_LCD_DisplayStringAt(len+487-x, 318-y, Buf, TRANSPARENT_MODE);
			}
		}	
	return;	
	}	

///////////////////////////////////////////////////////////////	
//	
//		animation display for load FL preset
//		
//	
void fl_load_animation(uint8_t pad)
	{	
	uint32_t color_l, color_h;	
	uint16_t x, y, w, h;
	uint16_t dx, dy, dw, dh;		
	uint16_t i;
	BSP_LCD_SelectLayer(1);
	if(FAST_LOADING[pad]<63)
		{
		color_l = PADS_LABEL_LOW_COLOR[presets_color[FAST_LOADING[pad]]];	
		color_h = PADS_LABEL_COLOR[presets_color[FAST_LOADING[pad]]];	
		}		
	else
		{
		return;	
		}		
	w = 118;	
	h = 103;
	x = 1+120*(pad%4);
	y = 32+105*(1-(pad>>2));
	for(i=0;i<362;i++)
		{
		BSP_LCD_SetTextColor(color_l);	
		BSP_LCD_DrawRect(x, y, w, h);	
		if(x>0)
			{
			x--;	
			}	
		if(y>0)
			{
			y--;	
			}	
		if((w+x)<479)
			{
			if(x==0)
				{
				w++;	
				}		
			else
				{				
				w+=2;
				}					
			}	
		if((h+y)<271)
			{
			if(y==0)
				{
				h++;	
				}	
			else
				{				
				h+=2;
				}					
			}		
		if(i%28==0)
			{
			BSP_LCD_SetTextColor(color_h);
			if(y>0)
				{
				BSP_LCD_DrawHLine(x, y, w);					
				}
			if((y+h-1)<270)
				{			
				BSP_LCD_DrawHLine(x, (y+h-1), w);
				}
			if(x>0)
				{			
				BSP_LCD_DrawVLine(x, y, h);
				}
			if((x+w-1)<478)
				{			
				BSP_LCD_DrawVLine((x+w-1), y, h);
				}
			dx = x;	
			dy = y;	
			dw = w;	
			dh = h;	
			if(x>0)
				{
				x--;	
				}	
			if(y>0)
				{
				y--;	
				}	
			if((w+x)<479)
				{
				if(x==0)
					{
					w++;	
					}		
				else
					{				
					w+=2;
					}					
				}	
			if((h+y)<271)
				{
				if(y==0)
					{
					h++;	
					}	
				else
					{				
					h+=2;
					}					
				}		
			if(y>0)
				{
				BSP_LCD_DrawHLine(x, y, w);					
				}
			if((y+h-1)<270)
				{			
				BSP_LCD_DrawHLine(x, (y+h-1), w);
				}
			if(x>0)
				{			
				BSP_LCD_DrawVLine(x, y, h);
				}
			if((x+w-1)<478)
				{			
				BSP_LCD_DrawVLine((x+w-1), y, h);
				}	
			if(x>0)
				{
				x--;	
				}	
			if(y>0)
				{
				y--;	
				}	
			if((w+x)<479)
				{
				if(x==0)
					{
					w++;	
					}		
				else
					{				
					w+=2;
					}					
				}	
			if((h+y)<271)
				{
				if(y==0)
					{
					h++;	
					}	
				else
					{				
					h+=2;
					}					
				}		
			if(y>0)
				{
				BSP_LCD_DrawHLine(x, y, w);					
				}
			if((y+h-1)<270)
				{			
				BSP_LCD_DrawHLine(x, (y+h-1), w);
				}
			if(x>0)
				{			
				BSP_LCD_DrawVLine(x, y, h);
				}
			if((x+w-1)<478)
				{			
				BSP_LCD_DrawVLine((x+w-1), y, h);
				}			
			x = dx;	
			y = dy;	
			w = dw;	
			h = dh;			
			HAL_Delay(11);
			}			
		}		
	return;	
	}



///////////////////////////////////////////////////////////////	
//	
//		draw pads perimeter with real colors	
//		
//	
void int_real_color_pads(void)
	{
	uint8_t i;	
	uint32_t P0, P1, P2;	
	uint8_t _r, _g, _b;	
		
	for(i=0;i<8;i++)
		{	
		if(FAST_LOADING[i]>63)
			{				
			P0 = PERIPH_PAD_GRADIENT_0;
			P1 = PERIPH_PAD_GRADIENT_1;
			P2 = PERIPH_PAD_GRADIENT_2;	
			}		
		else
			{
			P2 = PADS_LABEL_COLOR[presets_color[FAST_LOADING[i]]];
			P1 = 230*(P2%256);	
			_b = P1>>8;	
			P1 = 230*((P2>>8)%256);	
			_g = P1>>8;					
			P1 = 230*((P2>>16)%256);	
			_r = P1>>8;	
			P1 = 0xFF000000+_b+256*_g+65536*_r;		
			P0 = 182*(P2%256);	
			_b = P0>>8;	
			P0 = 182*((P2>>8)%256);	
			_g = P0>>8;					
			P0 = 182*((P2>>16)%256);	
			_r = P0>>8;	
			P0 = 0xFF000000+_b+256*_g+65536*_r;			
			}			
		BSP_LCD_SetTextColor(P0);
		BSP_LCD_DrawRect(2+120*(i%4), 33+105*(1-(i>>2)), 116, 101);	
		BSP_LCD_SetTextColor(P1);
		BSP_LCD_DrawRect(3+120*(i%4), 34+105*(1-(i>>2)), 114, 99);	
		BSP_LCD_SetTextColor(P2);
		BSP_LCD_DrawRect(4+120*(i%4), 35+105*(1-(i>>2)), 112, 97);		
		}
	return;	
	}	




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	

	
	

