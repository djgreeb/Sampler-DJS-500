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

void int_PRST_DRAW_ALL_LINES(void);													//internal function for PRESETS LIST
void int_PRST_DRAW_ONE_LINE(uint8_t UPDOWN);								//internal function for PRESETS LIST
void int_int_PRST(void);																		//internal function for PRESETS LIST
void intDrawLayer0_PRST(uint8_t CCP); 											//draw layer 0 for PRESET LIST


/////////////////////////////////	
//
//internal function for PRESETS LIST
void int_PRST_DRAW_ALL_LINES(void)
	{
	uint16_t E;
	BSP_LCD_SelectLayer(1);	
	for(E=0;E<13 && TOTAL_PRESETS>(E+CurrentPRSTPosition-1);E++)
		{				
		if(E==PRSTCCP && ((E+CurrentPRSTPosition-1)==CURRENT_PRESET))				//current preset
			{
			BSP_LCD_SetTextColor(LCD_COLOR_DGREEN);	
			}
		else if((E+CurrentPRSTPosition-1)==CURRENT_PRESET)	//current preset		
			{
			BSP_LCD_SetTextColor(LCD_COLOR_GREEN);	
			}
		else if(E==PRSTCCP)
			{
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);	
			}
		else
			{
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			}	
		BSP_LCD_DisplayStringAt(39,20+(19*E), presets_list[E+CurrentPRSTPosition-1], INFO_MODE);		
		sprintf((char*)Buf, "%s", "|");
		BSP_LCD_DisplayStringAt(20,20+(19*E), Buf, INFO_MODE);		
		}	
		
	int_int_PRST();	
		
	BSP_LCD_SelectLayer(0);
	ReDrawScroll(TOTAL_PRESETS, CurrentPRSTPosition);		
	return;	
	};
	
	
///////////////////////////////////////////////////////////////	
//	
//internal function for PRESETS LIST (COMMON INFO PART)
//	
void int_int_PRST(void)
	{
	uint8_t E;	
	BSP_LCD_SetTextColor(0x00000000);	
	BSP_LCD_FillRect(296, 40, 26, 13);		//clear
	BSP_LCD_FillRect(296, 59, 50, 15);		//
	BSP_LCD_FillRect(296, 78, 77, 15);		//
	BSP_LCD_FillRect(296, 97, 54, 15);		//
	BSP_LCD_FillRect(280, 116, 68, 13);		//
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	sprintf((char *)Buf , "%1lu", PRSTCCP+CurrentPRSTPosition);		
	BSP_LCD_DisplayStringAt(296, 39, Buf, TRANSPARENT_MODE);
			
	for(E=0;E<8;E++)							//search fast load pad
		{	
		if(FAST_LOADING[E]==(PRSTCCP+CurrentPRSTPosition-1))
			{
			sprintf((char *)Buf , "PAD %1lu", E+1);		
			BSP_LCD_DisplayStringAt(297, 58, Buf, TRANSPARENT_MODE);	
			E = 100;	
			}
		}
	for(E=0;E<8;E++)
		{
		if(presets_pads_colors[PRSTCCP+CurrentPRSTPosition-1][E]==0xFF)
			{				
			BSP_LCD_SetTextColor(LCD_COLOR_DISABLE);	
			}
		else
			{
			BSP_LCD_SetTextColor(PADS_LABEL_COLOR[presets_pads_colors[PRSTCCP+CurrentPRSTPosition-1][E]]);	
			}
		BSP_LCD_DrawHLine(304+12*(E%4), 218-10*(E>>2), 7);			//draw color display on sampler icon 
		BSP_LCD_DrawHLine(304+12*(E%4), 219-10*(E>>2), 10);			//	
		BSP_LCD_DrawRect(386+16*(E%4), 220-17*(E>>2), 13, 13);	//	
		}
//	sprintf((char *)Buf , "%2lu"".""%1lu"" bpm", original_tempo[TRACKS_DATABASE[TRACKLIST_OFFSET[B1CCP+BCurrentPlaylistPosition-1]+B0CCP+CurrentPRSTPosition-1]-1]/10, 
//		original_tempo[TRACKS_DATABASE[TRACKLIST_OFFSET[B1CCP+BCurrentPlaylistPosition-1]+B0CCP+CurrentPRSTPosition-1]-1]%10);		
//	BSP_LCD_DisplayStringAt(296, 78, Buf, TRANSPARENT_MODE);
//	int_VALUE_to_KEY(key_id[TRACKS_DATABASE[TRACKLIST_OFFSET[B1CCP+BCurrentPlaylistPosition-1]+B0CCP+CurrentPRSTPosition-1]-1]);	
//	BSP_LCD_DisplayStringAt(296, 97, Buf, TRANSPARENT_MODE);
//	sprintf((char *)Buf , "%02lu"":""%02lu", duration[TRACKS_DATABASE[TRACKLIST_OFFSET[B1CCP+BCurrentPlaylistPosition-1]+B0CCP+CurrentPRSTPosition-1]-1]/60, 
//		duration[TRACKS_DATABASE[TRACKLIST_OFFSET[B1CCP+BCurrentPlaylistPosition-1]+B0CCP+CurrentPRSTPosition-1]-1]%60);		
//	BSP_LCD_DisplayStringAt(296, 59, Buf, TRANSPARENT_MODE);
	int_DRAW_ICO(presets_icon[PRSTCCP+CurrentPRSTPosition-1],  presets_color[PRSTCCP+CurrentPRSTPosition-1], 0);	
	int_DRAW_STARS_RATING(presets_rating[PRSTCCP+CurrentPRSTPosition-1], presets_color[PRSTCCP+CurrentPRSTPosition-1], 0);			
	return;	
	};	
	
	
/////////////////////////////////////////////////	
//
//draw layer 0 for PRESET LIST
//
void intDrawLayer0_PRST(uint8_t CCP)
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
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);		
	BSP_LCD_FillRect(14, (18+(19*CCP)), 242, 9);			////Draw selected cursor
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_2);
	BSP_LCD_FillRect(14, (27+(19*CCP)), 242, 5);
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_1);
	BSP_LCD_FillRect(14, (32+(19*CCP)), 242, 5);
	BSP_LCD_SetTextColor(LCD_COLOR_PAPER);					//Draw paper rectangle
	BSP_LCD_FillRect(270, 18, 210, 247);	
	BSP_LCD_SetTextColor(LCD_COLOR_SHADOW);					//Shadow
	BSP_LCD_DrawRect(271, 19, 208, 245);
	intDrawTriangle(CCP);					//Draw triangle	
		
	for(j=0;j<8188;j++)					//Label
		{
		BSP_LCD_DrawPixel(384+(j%92), 120-j/92, (0xFF000000+disc[j][0]+256*disc[j][1]+65536*disc[j][2]));
		}		
	for(j=0;j<10416;j++)					//sampler icon
		{
		BSP_LCD_DrawPixel(295+(j%168), 248-j/168, (0xFF000000+sampler_icon[j][0]+256*sampler_icon[j][1]+65536*sampler_icon[j][2]));
		}		
	for(j=0;j<5;j++)							////Dots
		{
		for(k=0;k<54;k++)
			{
			BSP_LCD_DrawPixel(276+2*k, 36+19*j, LCD_COLOR_DARK_1);
			}
		}
	for(j=0;j<2;j++)							////Dots
		{
		for(k=0;k<99;k++)
			{
			BSP_LCD_DrawPixel(276+2*k, 131+19*j, LCD_COLOR_DARK_1);
			}
		}
	for(k=0;k<192;k++)					////preset number
		{
		if((iPRST[k/16]>>(k%16))%2)
			{
			BSP_LCD_DrawPixel(295-k%16, 40+k/16, LCD_COLOR_DARK_1);
			}	
		}	
	for(k=0;k<192;k++)					////FAST LOAD
		{
		if((iFL[k/16]>>(k%16))%2)
			{
			BSP_LCD_DrawPixel(294-k%16, 59+k/16, LCD_COLOR_DARK_1);
			}	
		}
	for(k=0;k<192;k++)					////BPM
		{
		if((iBPM[k/16]>>(k%16))%2)
			{
			BSP_LCD_DrawPixel(294-k%16, 78+k/16, LCD_COLOR_DARK_1);
			}	
		}
	for(k=0;k<224;k++)					////TONE
		{
		if((iTONE[k/16]>>(k%16))%2)
			{
			BSP_LCD_DrawPixel(294-k%16, 97+k/16, LCD_COLOR_DARK_1);
			}	
		}
	for(k=0;k<208;k++)					////DISC
		{
		if((iDISC[k/16]>>(k%16))%2)
			{
			BSP_LCD_DrawPixel(294-k%16, 135+k/16, LCD_COLOR_DARK_1);
			}	
		}
	for(k=0;k<224;k++)					////COMENTS
		{
		if((iCOMMENTS[k/16]>>(k%16))%2)
			{
			BSP_LCD_DrawPixel(294-k%16, 153+k/16, LCD_COLOR_DARK_1);
			}	
		}	
	BSP_LCD_SetFont(&Font15P);	
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);		
	sprintf((char*)Buf, "%s", "External: micro SD");						//static text			
	BSP_LCD_DisplayStringAt(298, 134, Buf, TRANSPARENT_MODE);		
	return;	
	};

	
/////////////////////////////////	
//
//internal function for PRESETS LIST
//	
void int_PRST_DRAW_ONE_LINE(uint8_t UPDOWN)							
	{
	if(PRSTCCP%2==0)
		{
		BSP_LCD_SetTextColor(LCD_COLOR_DARK_1);
		}
	else
		{
		BSP_LCD_SetTextColor(LCD_COLOR_DARK_2);
		}
	BSP_LCD_FillRect(14, 18+(19*PRSTCCP), 256, 19);
	BSP_LCD_SelectLayer(1);	
	BSP_LCD_SetFont(&Font15P);
	if(CurrentPRSTPosition+PRSTCCP-1==CURRENT_PRESET)
		{
		BSP_LCD_SetTextColor(LCD_COLOR_GREEN);	
		}	
	else
		{
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		}				
	BSP_LCD_DisplayStringAt(39,20+(19*PRSTCCP), presets_list[PRSTCCP+CurrentPRSTPosition-1], INFO_MODE);	
	sprintf((char*)Buf, "%s", "|");
	BSP_LCD_DisplayStringAt(20,20+(19*PRSTCCP),Buf, INFO_MODE);	

	if(UPDOWN==PRST_LIST_UP)
		{
		PRSTCCP++;
		}
	else
		{
		PRSTCCP--;	
		}
	if(CurrentPRSTPosition+PRSTCCP-1==CURRENT_PRESET)
		{
		BSP_LCD_SetTextColor(LCD_COLOR_DGREEN);	
		}	
	else
		{
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		}				
	BSP_LCD_DisplayStringAt(39,20+(19*PRSTCCP), presets_list[PRSTCCP+CurrentPRSTPosition-1], INFO_MODE);	
	sprintf((char*)Buf, "%s", "|");
	BSP_LCD_DisplayStringAt(20,20+(19*PRSTCCP),Buf, INFO_MODE);	
			
	int_int_PRST();		
		
	BSP_LCD_SelectLayer(0);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);		
	BSP_LCD_FillRect(14, (18+(19*PRSTCCP)), 242, 9);			//////////////////////////////	
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_2);
	BSP_LCD_FillRect(14, (27+(19*PRSTCCP)), 242, 5);
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_1);
	BSP_LCD_FillRect(14, (32+(19*PRSTCCP)), 242, 5);
	intDrawTriangle(PRSTCCP);			
	return;			
	};	

	
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	