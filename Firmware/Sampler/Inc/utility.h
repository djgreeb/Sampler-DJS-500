/////////////////////////////////////////////////////////////////////////////////////////////////
// 	utility GUI part
//	product: DJS-500 sampler
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdint.h"

void int_U_DRAW_ALL_LINES(void);														//internal function for UTILITY
void int_U_DRAW_ONE_LINE(uint8_t UPDOWN);										//internal function for UTILITY
void int_U_REDRAW_ONE_LINE(void);														//internal function for UTILITY for change parameter
void UTILITY_PARAMETER(uint8_t n_pr);
void int_reload_parameter_realtime(void);										//apply new parameters realtime



/////////////////////////////////////////////////	
//
//internal function for UTILITY
//	
void int_U_DRAW_ALL_LINES(void)
	{
	uint8_t E;
	for(E=0; E<13 && (TOTAL_U_POSITIONS>(E+CurrentUPosition-1));E++)
		{
		if(E==UCurrentCursorPosition)
			{
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);	
			}
		else
			{
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			}
		BSP_LCD_DisplayStringAt(35, 21+(19*E), UTILITY_BASE[E+CurrentUPosition-1], TRANSPARENT_MODE);
		UTILITY_PARAMETER(E+CurrentUPosition-1);	
		BSP_LCD_DisplayStringAt(292, 21+(19*E),Buf, TRANSPARENT_MODE);			
		}	
	BSP_LCD_SelectLayer(0);
	ReDrawScroll(TOTAL_U_POSITIONS, CurrentUPosition);			
	return;	
	}


/////////////////////////////////////////////////	
//
//internal function for UTILITY
//		
void int_U_DRAW_ONE_LINE(uint8_t UPDOWN)
	{
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);				
	BSP_LCD_FillRect(14, 18+(19*UCurrentCursorPosition), 256, 19);
	BSP_LCD_FillRect(271, 18+(19*UCurrentCursorPosition), 208, 19);	
	BSP_LCD_SetTextColor(LCD_COLOR_DARK_1);
	BSP_LCD_DrawLine(14,18+(19*UCurrentCursorPosition),479,18+(19*UCurrentCursorPosition));
	BSP_LCD_SelectLayer(1);	
	BSP_LCD_SetFont(&Font15P);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_DisplayStringAt(35, 21+(19*UCurrentCursorPosition), UTILITY_BASE[UCurrentCursorPosition+CurrentUPosition-1], TRANSPARENT_MODE);	
	UTILITY_PARAMETER(UCurrentCursorPosition+CurrentUPosition-1);	
	BSP_LCD_DisplayStringAt(292, 21+(19*UCurrentCursorPosition),Buf, TRANSPARENT_MODE);		
	if(UPDOWN==UTILITY_UP)
		{
		UCurrentCursorPosition++;
		}
	else
		{
		UCurrentCursorPosition--;	
		}
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(35,21+(19*UCurrentCursorPosition), UTILITY_BASE[UCurrentCursorPosition+CurrentUPosition-1], TRANSPARENT_MODE);
	UTILITY_PARAMETER(UCurrentCursorPosition+CurrentUPosition-1);	
	BSP_LCD_DisplayStringAt(292, 21+(19*UCurrentCursorPosition),Buf, TRANSPARENT_MODE);				
	BSP_LCD_SelectLayer(0);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);		
	BSP_LCD_FillRect(14, (18+(19*UCurrentCursorPosition)), 256, 9);			////Draw selected cursor	
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_2);
	BSP_LCD_FillRect(14, (27+(19*UCurrentCursorPosition)), 256, 5);
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_1);
	BSP_LCD_FillRect(14, (32+(19*UCurrentCursorPosition)), 256, 5);
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_3);		
	BSP_LCD_FillRect(271, (18+(19*UCurrentCursorPosition)), 208, 9);			////Draw selected cursor	
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_5);
	BSP_LCD_FillRect(271, (27+(19*UCurrentCursorPosition)), 208, 5);
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_4);
	BSP_LCD_FillRect(271, (32+(19*UCurrentCursorPosition)), 208, 5);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	FillTriangle(20, 20, 27, 20+(19*UCurrentCursorPosition), 34+(19*UCurrentCursorPosition), 27 +(19*UCurrentCursorPosition));		
	return;			
	}


/////////////////////////////////////////////////	
//
//internal function for UTILITY for change parameter	
//		
void int_U_REDRAW_ONE_LINE(void)
	{
	BSP_LCD_SelectLayer(1);	
	BSP_LCD_SetTransparency(1, 255);	
	BSP_LCD_SetTextColor(0x00000000);	
	BSP_LCD_FillRect(271, 18+(19*UCurrentCursorPosition), 208, 19);		
	BSP_LCD_SetFont(&Font15P);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	UTILITY_PARAMETER(UCurrentCursorPosition+CurrentUPosition-1);	
	BSP_LCD_DisplayStringAt(292, 21+(19*UCurrentCursorPosition),Buf, TRANSPARENT_MODE);
	BSP_LCD_SelectLayer(0);		
	return;	
	}	


//////////////////////////////////////////
//	"AUTO LOAD           ",
//	"LOAD LOCK           ",
//	"EFFECT TYPE		      ",
//	"SYNC MODE 				  ",
//	"INTERNAL BPM 				",
//	"SYNC OUT TYPE       ",
//	"LCD BRIGHTNESS      ",
//	"CDJ 1 IP ADRESS     ",
//	"CDJ 2 IP ADRESS     ",
//	"SAMPLER IP ADRESS   ",
//	"SAMPLER MAC ADRESS  ",
//	"SD CARD INFO        ",
//	"DEVICE UID          ",
//	"VERSION No.         ",
//	"DEVELOPER           "
//	
void UTILITY_PARAMETER(uint8_t n_pr)
	{
	switch (n_pr)
		{
		case 0:
			{
			sprintf((char*)Buf, "| %s", presets_list[UTILITY_SETTINGS[n_pr]]);	
			break;	
			}
		case 1:
			{
			if(UTILITY_SETTINGS[n_pr]==0)
				{
				sprintf((char*)Buf, "%s", "UNLOCK");		
				}
			else
				{
				sprintf((char*)Buf, "%s", "LOCK");		
				}
			break;	
			}	
		case 2:
			{
			switch (UTILITY_SETTINGS[n_pr])
				{
				case 0:	
					{
					sprintf((char*)Buf, "%s", "TRANS");	
					break;		
					}	
				case 1:	
					{
					sprintf((char*)Buf, "%s", "MOOG FILTER");	
					break;		
					}	
				case 2:	
					{
					sprintf((char*)Buf, "%s", "FILTER");	
					break;		
					}	
				case 3:	
					{
					sprintf((char*)Buf, "%s", "DISTORTION");	
					break;		
					}	
				case 4:	
					{
					sprintf((char*)Buf, "%s", "CRUSH");	
					break;		
					}	
			default: break;		
				}
			break;		
			}		
		case 3:
			{
			if(UTILITY_SETTINGS[n_pr]==0)
				{
				sprintf((char*)Buf, "%s", "INTERNAL");	
				}		
			else
				{
				sprintf((char*)Buf, "%s", "EXTERNAL");
				}					
			break;		
			}
		case 4:
			{
			if(UTILITY_SETTINGS[n_pr]<500 || UTILITY_SETTINGS[n_pr]>2020)
				{
				UTILITY_SETTINGS[n_pr] = 1200;	
				}				
			sprintf((char*)Buf, "%1lu.%1luBPM", UTILITY_SETTINGS[n_pr]/10, UTILITY_SETTINGS[n_pr]%10);	
			break;			
			}
		case 5:
			{
			if(UTILITY_SETTINGS[n_pr]==0)
				{
				sprintf((char*)Buf, "%s", "TTL");	
				}		
			else
				{
				sprintf((char*)Buf, "%s", "UART 115200bps");
				}					
			break;			
			}	
		case 6:
			{				
			sprintf((char*)Buf , "%0lu", UTILITY_SETTINGS[n_pr]+1);						
			break;		
			}		
		case 7:																														//CDJ 1 IP ADRESS
			{
			if(edit_parameter==1 && ((UCurrentCursorPosition + CurrentUPosition)==8))			
				{
				if(ip_decade==0)
					{
					sprintf((char*)Buf, "[%01u].%01u.%01u.%01u", UTILITY_SETTINGS[n_pr]>>24, (UTILITY_SETTINGS[n_pr]>>16)&0x000000FF, (UTILITY_SETTINGS[n_pr]>>8)&0x000000FF, UTILITY_SETTINGS[n_pr]&0x000000FF);	
					}
				else if(ip_decade==1)
					{
					sprintf((char*)Buf, "%01u.[%01u].%01u.%01u", UTILITY_SETTINGS[n_pr]>>24, (UTILITY_SETTINGS[n_pr]>>16)&0x000000FF, (UTILITY_SETTINGS[n_pr]>>8)&0x000000FF, UTILITY_SETTINGS[n_pr]&0x000000FF);	
					}
				else if(ip_decade==2)
					{
					sprintf((char*)Buf, "%01u.%01u.[%01u].%01u", UTILITY_SETTINGS[n_pr]>>24, (UTILITY_SETTINGS[n_pr]>>16)&0x000000FF, (UTILITY_SETTINGS[n_pr]>>8)&0x000000FF, UTILITY_SETTINGS[n_pr]&0x000000FF);	
					}
				else if(ip_decade==3)
					{
					sprintf((char*)Buf, "%01u.%01u.%01u.[%01u]", UTILITY_SETTINGS[n_pr]>>24, (UTILITY_SETTINGS[n_pr]>>16)&0x000000FF, (UTILITY_SETTINGS[n_pr]>>8)&0x000000FF, UTILITY_SETTINGS[n_pr]&0x000000FF);	
					}
				}	
			else
				{
				sprintf((char*)Buf, "%01u.%01u.%01u.%01u", UTILITY_SETTINGS[n_pr]>>24, (UTILITY_SETTINGS[n_pr]>>16)&0x000000FF, (UTILITY_SETTINGS[n_pr]>>8)&0x000000FF, UTILITY_SETTINGS[n_pr]&0x000000FF);
				}	
			break;			
			}
		case 8:																														//CDJ 2 IP ADRESS
			{
			if(edit_parameter==1 && ((UCurrentCursorPosition + CurrentUPosition)==9))			
				{
				if(ip_decade==0)
					{
					sprintf((char*)Buf, "[%01u].%01u.%01u.%01u", UTILITY_SETTINGS[n_pr]>>24, (UTILITY_SETTINGS[n_pr]>>16)&0x000000FF, (UTILITY_SETTINGS[n_pr]>>8)&0x000000FF, UTILITY_SETTINGS[n_pr]&0x000000FF);	
					}
				else if(ip_decade==1)
					{
					sprintf((char*)Buf, "%01u.[%01u].%01u.%01u", UTILITY_SETTINGS[n_pr]>>24, (UTILITY_SETTINGS[n_pr]>>16)&0x000000FF, (UTILITY_SETTINGS[n_pr]>>8)&0x000000FF, UTILITY_SETTINGS[n_pr]&0x000000FF);	
					}
				else if(ip_decade==2)
					{
					sprintf((char*)Buf, "%01u.%01u.[%01u].%01u", UTILITY_SETTINGS[n_pr]>>24, (UTILITY_SETTINGS[n_pr]>>16)&0x000000FF, (UTILITY_SETTINGS[n_pr]>>8)&0x000000FF, UTILITY_SETTINGS[n_pr]&0x000000FF);	
					}
				else if(ip_decade==3)
					{
					sprintf((char*)Buf, "%01u.%01u.%01u.[%01u]", UTILITY_SETTINGS[n_pr]>>24, (UTILITY_SETTINGS[n_pr]>>16)&0x000000FF, (UTILITY_SETTINGS[n_pr]>>8)&0x000000FF, UTILITY_SETTINGS[n_pr]&0x000000FF);	
					}
				}	
			else
				{
				sprintf((char*)Buf, "%01u.%01u.%01u.%01u", UTILITY_SETTINGS[n_pr]>>24, (UTILITY_SETTINGS[n_pr]>>16)&0x000000FF, (UTILITY_SETTINGS[n_pr]>>8)&0x000000FF, UTILITY_SETTINGS[n_pr]&0x000000FF);
				}		
			break;	
			}		
		case 9:																														//SAMPLER IP ADRESS
			{
			if(edit_parameter==1 && ((UCurrentCursorPosition + CurrentUPosition)==10))			
				{
				if(ip_decade==0)
					{
					sprintf((char*)Buf, "[%01u].%01u.%01u.%01u", UTILITY_SETTINGS[n_pr]>>24, (UTILITY_SETTINGS[n_pr]>>16)&0x000000FF, (UTILITY_SETTINGS[n_pr]>>8)&0x000000FF, UTILITY_SETTINGS[n_pr]&0x000000FF);	
					}
				else if(ip_decade==1)
					{
					sprintf((char*)Buf, "%01u.[%01u].%01u.%01u", UTILITY_SETTINGS[n_pr]>>24, (UTILITY_SETTINGS[n_pr]>>16)&0x000000FF, (UTILITY_SETTINGS[n_pr]>>8)&0x000000FF, UTILITY_SETTINGS[n_pr]&0x000000FF);	
					}
				else if(ip_decade==2)
					{
					sprintf((char*)Buf, "%01u.%01u.[%01u].%01u", UTILITY_SETTINGS[n_pr]>>24, (UTILITY_SETTINGS[n_pr]>>16)&0x000000FF, (UTILITY_SETTINGS[n_pr]>>8)&0x000000FF, UTILITY_SETTINGS[n_pr]&0x000000FF);	
					}
				else if(ip_decade==3)
					{
					sprintf((char*)Buf, "%01u.%01u.%01u.[%01u]", UTILITY_SETTINGS[n_pr]>>24, (UTILITY_SETTINGS[n_pr]>>16)&0x000000FF, (UTILITY_SETTINGS[n_pr]>>8)&0x000000FF, UTILITY_SETTINGS[n_pr]&0x000000FF);	
					}
				}	
			else
				{
				sprintf((char*)Buf, "%01u.%01u.%01u.%01u", UTILITY_SETTINGS[n_pr]>>24, (UTILITY_SETTINGS[n_pr]>>16)&0x000000FF, (UTILITY_SETTINGS[n_pr]>>8)&0x000000FF, UTILITY_SETTINGS[n_pr]&0x000000FF);
				}				
			break;	
			}	
		case 10:
			{
			sprintf((char*)Buf, "%02lX-%02lX-%02lX-%02lX-%02lX-%02lX", MAC_ADR[0], MAC_ADR[1], MAC_ADR[2], MAC_ADR[3], MAC_ADR[4], MAC_ADR[5]);	
			break;	
			}	
		case 11:
			{
			if(HAL_GPIO_ReadPin(uSD_Detect_GPIO_Port, uSD_Detect_Pin)==1)
				{
				sprintf((char*)Buf, "%s", "NO CARD");	
				}		
			else
				{
				if(used_mem>999)
					{
					if(used_mem>9999)
						{
						sprintf((char*)Buf, "%1lu"".""%01lu""GB used ", used_mem/1000, (used_mem%1000)/100);		
						}
					else
						{
						sprintf((char*)Buf, "%1lu"".""%02lu""GB used ", used_mem/1000, (used_mem%1000)/10);		
						}
					}
				else
					{
					sprintf((char*)Buf, "%1lu""MB used ", used_mem);	
					}		
				if(free_mem>999)
					{	
					if(free_mem>9999)
						{
						sprintf((char*)&Buf[strlen(Buf)], "%1lu"".""%01lu""GB free", free_mem/1000, (free_mem%1000)/100);		
						}
					else
						{
						sprintf((char*)&Buf[strlen(Buf)], "%1lu"".""%02lu""GB free", free_mem/1000, (free_mem%1000)/10);		
						}
					}
				else
					{
					sprintf((char*)&Buf[strlen(Buf)], "%1lu""MB free", free_mem);	
					}	

				}								
			break;	
			}		
		case 12:
			{
			sprintf((char *)Buf , "%08lX", DEVICE_UID);	
			break;	
			}		
		case 13:
			{
			sprintf((char*)Buf, "%s", "Ver. ");
			Buf[5] = FIRMWARE_VERSION[0];
			Buf[6] = FIRMWARE_VERSION[1];
			Buf[7] = FIRMWARE_VERSION[2];
			Buf[8] = FIRMWARE_VERSION[3];	
			Buf[9] = FIRMWARE_VERSION[4];					
			Buf[10] = 0;					
			break;	
			}
		case 14:
			{
			sprintf((char*)Buf, "%s", "ANATSKA ANDREI");				
			break;	
			}		
		default:
			break;	
		}	
	return;	
	}


//////////////////////////////////////////////////////////////////////////////////////////	
//
//internal function for UTILITY for realtime reload parameters
//
//	
void int_reload_parameter_realtime(void)
	{
	if(UCurrentCursorPosition+CurrentUPosition==7)				//change lcd brightness
		{		
		TIM14->CCR1 = 48+(52*UTILITY_SETTINGS[6]);
		}		
	else if(UCurrentCursorPosition+CurrentUPosition==5)			//INTERNAL BPM 
		{
		if(UTILITY_SETTINGS[3]==0)  ////if sync mode: internal and changed int. bmp - may change in prc gen tick?  
			{
				
			}
		}
	}			
	
	

/////////////////////////////////////////////////////////////////////////////////////////////////

