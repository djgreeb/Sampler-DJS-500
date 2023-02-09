/////////////////////////////////////////////////////////////////////////////////////////////////
// 	BROWSER GUI part
//	product: DJS-500 sampler
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdint.h"

void int_BR_DRAW_ALL_LINES(void);													//internal function for BROWSER
void int_BR_DRAW_ONE_LINE(uint8_t UPDOWN);								//internal function for BROWSER
void intDrawLayer0_BR(uint8_t CCP); 											//draw layer 0 for BROWSER
uint8_t SCAN_DIR(char* path);															//return error

/////////////////////////////////	
//
//internal function for BROWSER
void int_BR_DRAW_ALL_LINES(void)
	{
	uint16_t E;
	BSP_LCD_SelectLayer(1);	
		
	for(E=0;E<13 && total_elements>(E+CurrentBRPosition-1);E++)
		{				
		if(E==BRCCP)
			{
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);	
			}
		else
			{
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			}	
			
		if(TRACKLIST[E+CurrentBRPosition-1][65]==1)					//is folder	
			{
			sprintf((char*)Buf, "[%s]", &TRACKLIST[E+CurrentBRPosition-1][TRACKLIST[E+CurrentBRPosition-1][64]+1]);		
			BSP_LCD_DisplayStringAt(39, 20+(19*E), Buf, TRANSPARENT_MODE);	
			Buf[0] = 0x84;
			Buf[1] = 0;
			BSP_LCD_DisplayStringAt(20, 20+(19*E), Buf, TRANSPARENT_MODE);		
			}
		else				//is track
			{
			BSP_LCD_DisplayStringAt(39, 20+(19*E), TRACKLIST[E+CurrentBRPosition-1], TRANSPARENT_MODE);
			Buf[0] = 0x7E;
			Buf[1] = 0;
			BSP_LCD_DisplayStringAt(20, 20+(19*E), Buf, TRANSPARENT_MODE);					
			}			
		}	
	BSP_LCD_SelectLayer(0);
	ReDrawScroll(total_elements, CurrentBRPosition);		
	return;	
	};
	
	
	
/////////////////////////////////////////////////	
//
//draw layer 0 for BROWSER
//
void intDrawLayer0_BR(uint8_t CCP)
	{
	uint8_t E;		
	BSP_LCD_SetTextColor(LCD_COLOR_DARK_1);
	for(E=0;E<7;E++)															/////Draw gray lines
		{
		if(CCP%2==1 | (CCP/2) != E)
			{		
			BSP_LCD_FillRect(14, 18+(38*E), 466, 19);
			}			
		}
	BSP_LCD_SetTextColor(LCD_COLOR_DARK_2);
	for(E=0;E<6;E++)
		{
		if(CCP%2==0 | (CCP/2) != E)
			{				
			BSP_LCD_FillRect(14, 37+(38*E), 466, 19);
			}			
		}
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);		
	BSP_LCD_FillRect(14, (18+(19*CCP)), 466, 9);			////Draw selected cursor
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_2);
	BSP_LCD_FillRect(14, (27+(19*CCP)), 466, 5);
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_1);
	BSP_LCD_FillRect(14, (32+(19*CCP)), 466, 5);
	return;	
	};

	
/////////////////////////////////	
//
//internal function for BROWSER
//	
void int_BR_DRAW_ONE_LINE(uint8_t UPDOWN)							
	{
	if(BRCCP%2==0)
		{
		BSP_LCD_SetTextColor(LCD_COLOR_DARK_1);
		}
	else
		{
		BSP_LCD_SetTextColor(LCD_COLOR_DARK_2);
		}
	BSP_LCD_FillRect(14, 18+(19*BRCCP), 466, 19);
	BSP_LCD_SelectLayer(1);	
	BSP_LCD_SetFont(&Font15P);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
						
	if(TRACKLIST[BRCCP+CurrentBRPosition-1][65]==1)					//is folder	
		{
		sprintf((char*)Buf, "[%s]", &TRACKLIST[BRCCP+CurrentBRPosition-1][TRACKLIST[BRCCP+CurrentBRPosition-1][64]+1]);	
		BSP_LCD_DisplayStringAt(39, 20+(19*BRCCP), Buf, TRANSPARENT_MODE);	
		Buf[0] = 0x84;
		Buf[1] = 0;
		BSP_LCD_DisplayStringAt(20, 20+(19*BRCCP), Buf, TRANSPARENT_MODE);		
		}
	else				//is track
		{
		BSP_LCD_DisplayStringAt(39, 20+(19*BRCCP), TRACKLIST[BRCCP+CurrentBRPosition-1], TRANSPARENT_MODE);	
		Buf[0] = 0x7E;
		Buf[1] = 0;
		BSP_LCD_DisplayStringAt(20, 20+(19*BRCCP), Buf, TRANSPARENT_MODE);		
		}

	if(UPDOWN==BR_LIST_UP)
		{
		BRCCP++;
		}
	else
		{
		BRCCP--;	
		}
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	if(TRACKLIST[BRCCP+CurrentBRPosition-1][65]==1)					//is folder	
		{
		sprintf((char*)Buf, "[%s]", &TRACKLIST[BRCCP+CurrentBRPosition-1][TRACKLIST[BRCCP+CurrentBRPosition-1][64]+1]);	
		BSP_LCD_DisplayStringAt(39, 20+(19*BRCCP), Buf, TRANSPARENT_MODE);	
		Buf[0] = 0x84;
		Buf[1] = 0;
		BSP_LCD_DisplayStringAt(20, 20+(19*BRCCP), Buf, TRANSPARENT_MODE);		
		}
	else				//is track
		{
		BSP_LCD_DisplayStringAt(39, 20+(19*BRCCP), TRACKLIST[BRCCP+CurrentBRPosition-1], TRANSPARENT_MODE);	
		Buf[0] = 0x7E;
		Buf[1] = 0;
		BSP_LCD_DisplayStringAt(20, 20+(19*BRCCP), Buf, TRANSPARENT_MODE);		
		}
	BSP_LCD_SelectLayer(0);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);		
	BSP_LCD_FillRect(14, (18+(19*BRCCP)), 466, 9);			//////////////////////////////	
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_2);
	BSP_LCD_FillRect(14, (27+(19*BRCCP)), 466, 5);
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_1);
	BSP_LCD_FillRect(14, (32+(19*BRCCP)), 466, 5);		
	return;			
	};	




	
//////////////////////////////////////////////////////	
//Scan directory, search *.wav files
//
//		
uint8_t SCAN_DIR(char* pth)
	{
	total_elements = 0;
	TOTAL_TRACKS = 0;	
	FRESULT res;
	DIR dir;
	UINT i;
	static FILINFO fno;	
		
	res = f_opendir(&dir, pth);                       /* Open the directory */
	if (res == FR_OK) 
		{
		for (;;) 
			{
			res = f_readdir(&dir, &fno);                   /* Read a directory item */
			if (res != FR_OK || fno.fname[0]==0) break;  /* Break on error or end of dir */
			if (fno.fattrib & AM_DIR) 
				{                    /* It is a directory */
				sprintf((char*)TRACKLIST[total_elements], "%s", pth);	
				i = strlen(pth);
				sprintf((char*)&TRACKLIST[total_elements][i], "/%s", fno.fname);	
				TRACKLIST[total_elements][64] = i;	
				TRACKLIST[total_elements][65] = 1;		
				total_elements++;	
				} 
			}
	  res = f_findfirst(&dir, &fno, pth, "*.wav");  /* Start to search for audio files */
    while (res == FR_OK && fno.fname[0]) 				/* Repeat while an item is found */
			{         
			//printf("%s\n", fno.fname);                /* Display the object name */
			sprintf((char*)TRACKLIST[total_elements], "%s", fno.fname);
			TRACKLIST[total_elements][64] = 0;	
			TRACKLIST[total_elements][65] = 0;	
			res = f_findnext(&dir, &fno);               /* Search for next item */
			total_elements++;	
			TOTAL_TRACKS++;	
			}		
		f_closedir(&dir);		
		return 0;	
		}	
	else
		{
		return 1;	
		}
	}		
	

	
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	