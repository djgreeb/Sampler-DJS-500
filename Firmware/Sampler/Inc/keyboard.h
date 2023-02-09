/////////////////////////////////////////////////////////////////////////////////////////////////
// 	KEYBOARD GUI part
//	product: DJS-500 sampler
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdint.h"
void int_KBRD_(uint8_t updwn);					//internal function for keyboard
void int_TYPING(void);									//internal function for keyboard
void int_RET_PRST_NAME(void);						//internal function for keyboard
void int_blinking_cursor(void);					//internal function for keyboard

/////////////////////////////////////////////////	
//
//internal function for keyboard
//		
void int_KBRD_(uint8_t updwn)
	{
	BSP_LCD_SelectLayer(0);				
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);	
	if(KBRD_Position==36 || KBRD_Position==73)
		{
		BSP_LCD_FillRect(1+13*(KBRD_Position%37), 217+26*(KBRD_Position/37), 10, 19);	
		BSP_LCD_DrawLine(13*(KBRD_Position%37),  218+26*(KBRD_Position/37), 13*(KBRD_Position%37), 234+26*(KBRD_Position/37));	
		BSP_LCD_DrawLine(11+13*(KBRD_Position%37),  218+26*(KBRD_Position/37), 11+13*(KBRD_Position%37), 234+26*(KBRD_Position/37));
		}
	else		
		{
		BSP_LCD_FillRect(1+13*(KBRD_Position%37), 217+26*(KBRD_Position/37), 11, 19);	
		BSP_LCD_DrawLine(13*(KBRD_Position%37),  218+26*(KBRD_Position/37), 13*(KBRD_Position%37), 234+26*(KBRD_Position/37));	
		BSP_LCD_DrawLine(12+13*(KBRD_Position%37),  218+26*(KBRD_Position/37), 12+13*(KBRD_Position%37), 234+26*(KBRD_Position/37));	
		}
	BSP_LCD_SelectLayer(1);		
	Buf[0] = lttrs[KBRD_Position/37][KBRD_Position%37];
	Buf[1] = 0;	
	if((KBRD_Position%37)<5 || (KBRD_Position%37)>30)
		{
		if(KBRD_Position==73)
			{
			BSP_LCD_SetTextColor(KBRD_RED_COLOR);		
			}						
		else
			{						
			BSP_LCD_SetTextColor(PATH_COLOR);	
			}
		}	
	else
		{
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);	
		}	
	BSP_LCD_DisplayStringAt(letter_offs[KBRD_Position/37][KBRD_Position%37], 219+26*(KBRD_Position/37), Buf, TRANSPARENT_MODE);			
	
	if(updwn==KBRD_UP)
		{
		if(KBRD_Position<73)
			{
			KBRD_Position++;
			}
		else
			{
			return;	
			}			
		}
	else if(updwn==KBRD_DOWN)
		{
		if(KBRD_Position>0)
			{
			KBRD_Position--;
			}
		else
			{
			return;	
			}			
		}	
	else if(updwn==KBRD_SH_UP)
		{
		if(KBRD_Position<37)
			{
			KBRD_Position+=37;
			}
		else
			{
			return;	
			}		
		}		
	else if(updwn==KBRD_SH_DOWN)
		{
		if(KBRD_Position>36)
			{
			KBRD_Position-=37;
			}
		else
			{
			return;	
			}			
		}		
	BSP_LCD_SelectLayer(0);				
	if((KBRD_Position%37)<5 || (KBRD_Position%37)>30)
		{
		if(KBRD_Position==73)
			{
			BSP_LCD_SetTextColor(KBRD_RED_COLOR);		
			}						
		else
			{						
			BSP_LCD_SetTextColor(PATH_COLOR);	
			}
		}	
	else
		{
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);	
		}	
	if(KBRD_Position==36 || KBRD_Position==73)
		{
		BSP_LCD_FillRect(1+13*(KBRD_Position%37), 217+26*(KBRD_Position/37), 10, 19);	
		BSP_LCD_DrawLine(13*(KBRD_Position%37),  218+26*(KBRD_Position/37), 13*(KBRD_Position%37), 234+26*(KBRD_Position/37));	
		BSP_LCD_DrawLine(11+13*(KBRD_Position%37),  218+26*(KBRD_Position/37), 11+13*(KBRD_Position%37), 234+26*(KBRD_Position/37));
		}
	else		
		{
		BSP_LCD_FillRect(1+13*(KBRD_Position%37), 217+26*(KBRD_Position/37), 11, 19);	
		BSP_LCD_DrawLine(13*(KBRD_Position%37),  218+26*(KBRD_Position/37), 13*(KBRD_Position%37), 234+26*(KBRD_Position/37));	
		BSP_LCD_DrawLine(12+13*(KBRD_Position%37),  218+26*(KBRD_Position/37), 12+13*(KBRD_Position%37), 234+26*(KBRD_Position/37));	
		}
	BSP_LCD_SelectLayer(1);		
	Buf[0] = lttrs[KBRD_Position/37][KBRD_Position%37];
	Buf[1] = 0;	
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);		
	BSP_LCD_DisplayStringAt(letter_offs[KBRD_Position/37][KBRD_Position%37], 219+26*(KBRD_Position/37), Buf, TRANSPARENT_MODE);
	return;			
	}


	
/////////////////////////////////////////////////	
//
//internal function for keyboard
//		
void int_TYPING(void)
	{
	uint8_t lng;
	lng = strlen(rnm_buff);
	if(KBRD_Position<73)			
		{
		if(blink_cursor==1)
			{			
			if(lng<32)			//check lenght
				{
				if(KBRD_Position==36)
					{				
					rnm_buff[lng-1] = 32; 	
					}
				else
					{
					rnm_buff[lng-1] =	lttrs[KBRD_Position/37][KBRD_Position%37];
					}				
				rnm_buff[lng] = 0x82;	
				rnm_buff[lng+1] = 0;	
				}			
			}
		else if(blink_cursor==0)
			{
			if(lng<31)			//check lenght
				{
				if(KBRD_Position==36)
					{				
					rnm_buff[lng] = 32; 	
					}
				else
					{
					rnm_buff[lng] =	lttrs[KBRD_Position/37][KBRD_Position%37];
					}				
				rnm_buff[lng+1] = 0;		
				}	
			}	
		}
	else if(KBRD_Position==73)	//del
		{
		if(blink_cursor==1)
			{			
			if(lng>1)			//check lenght
				{
				rnm_buff[lng-2] = 0x82;	
				rnm_buff[lng-1] = 0;		
				}
			}
		else if(blink_cursor==0)
			{
			if(lng>0)			//check lenght
				{
				rnm_buff[lng-1] = 0;		
				}
			}			
		}		
	BSP_LCD_SelectLayer(1);	
	BSP_LCD_SetTextColor(0x00000000);	
	BSP_LCD_FillRect(10, 39, 352, 18);				//clear window for preset name
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_DisplayStringAt(13, 41, rnm_buff, TRANSPARENT_MODE);			//preset name_	
	BSP_LCD_SetTextColor(KBRD_TRANPARENT_COLOR);	
	BSP_LCD_FillRect(362, 39, 76, 18);				//clear after window artefact		
	return;	
	}	
	
/////////////////////////////////////////////////	
//
//internal function for keyboard
//		
void int_RET_PRST_NAME(void)
	{
	uint8_t lng, i;
	lng = strlen(rnm_buff);
	if(blink_cursor==1)
		{		
		if(lng<2)
			{
			sprintf((char*)presets_list[CURRENT_PRESET], "%s", "NO NAME");	
			for(i=8;i<32;i++)
				{
				presets_list[CURRENT_PRESET][i] = 0;	
				}			
			}
		else if(lng<33)
			{
			sprintf((char*)presets_list[CURRENT_PRESET], rnm_buff);			//copy preset name
			for(i=(lng-1);i<32;i++)
				{
				presets_list[CURRENT_PRESET][i] = 0;	
				}
			}		
		}
	else if(blink_cursor==0)
		{
		if(lng==0)
			{
			sprintf((char*)presets_list[CURRENT_PRESET], "%s", "NO NAME");	
			for(i=8;i<32;i++)
				{
				presets_list[CURRENT_PRESET][i] = 0;	
				}			
			}
		else if(lng<32)
			{
			sprintf((char*)presets_list[CURRENT_PRESET], rnm_buff);			//copy preset name
			for(i=lng;i<32;i++)
				{
				presets_list[CURRENT_PRESET][i] = 0;	
				}
			}	
		}		
	return;	
	}
	
		
/////////////////////////////////////////////////	
//
//internal function for keyboard
//	
void int_blinking_cursor(void)
	{
	uint8_t ln;	
	ln = strlen(rnm_buff);	
	if(blink_cursor==0)
		{
		rnm_buff[ln] = 0x82;
		rnm_buff[ln+1] = 0;
		blink_cursor = 1;	
		}		
	else
		{
		rnm_buff[ln-1] = 0;		
		blink_cursor = 0;	
		}		
	BSP_LCD_SelectLayer(1);	
	BSP_LCD_SetTextColor(0x00000000);	
	BSP_LCD_FillRect(10, 39, 352, 18);				//clear window for preset name
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_DisplayStringAt(13, 41, rnm_buff, TRANSPARENT_MODE);			//preset name_	
	BSP_LCD_SetTextColor(KBRD_TRANPARENT_COLOR);	
	BSP_LCD_FillRect(362, 39, 76, 18);				//clear after window artefact			
	return;	
	}


/////////////////////////////////////////////////////////////////////////////////////////////////

