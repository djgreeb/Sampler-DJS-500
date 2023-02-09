/////////////////////////////////////////////////////////////////////////////////////////////////
//	GUI functions and prototypes
//	product: DJS-500 sampler
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdint.h"

void ShowEFFECT(uint8_t color);															//show EFFECT on display 0 - none 1 - gray 2 - blue	
void ShowSYNCOUT(uint8_t color);														//show SYNC OUT on display 0 - none 1 - gray 2 - red	
void int_red_gradient(uint8_t sqc, uint8_t pd);							//internal gradient for sequencer
void int_blue_gradient(uint8_t sqc, uint8_t pd);						//internal gradient for sequencer
void int_grey_gradient(uint8_t sqc, uint8_t pd);						//internal gradient for sequencer
void int_sqnc_perimeter(uint8_t sqc, uint8_t pd);						//internal perimeter for sequencer
void DrawLOGO(void);
void ShowLinkNumb(uint8_t stat);				//0 - none; 1 - gray; 2 - white;
void ShowBPM(uint32_t bpm);
void ShowMasterDeck(uint8_t MD);						//0 - none; 1 - deck 1; 2 - deck 2;
void ShowSPhaseMeter(uint8_t phase);												//Show Phase meter 0 - none 1...4 phase
void ShowMPhaseMeter(uint8_t phase, uint16_t bar);					//Show Phase meter 0 - none 1...4 phase
void int_DRAW_TRANSPARENT_BAR(void);												//internal function transparent bar for Browser, waveform
void DrawLoopShot(uint8_t type, uint32_t pad_color, uint32_t back_color, uint8_t npad);			//draw icon shot (0) or loop (1)
void ShowRAM(uint8_t ram);			//show ram fill ram>100 - color red



///////////////////////////	
//show EFFECT on display
//	0 - none 1 - gray 2 - blue	
void ShowEFFECT(uint8_t color)
	{
	BSP_LCD_SetFont(&FontBMP);
	if(color==1)
		{
		BSP_LCD_SetTextColor(0xFF404040);	
		}
	else if(color==2)
		{
		BSP_LCD_SetTextColor(0xFF005DFF);
		}
	else
		{
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		}		
	sprintf((char*)Buf, "%s", "EF");						//effect
	BSP_LCD_DisplayStringAt(47, 36, Buf, TRANSPARENT_MODE);	
	return;	
	}	
	
///////////////////////////	
//show SYNC OUT on display
//	0 - none 1 - gray 2 - red			
void ShowSYNCOUT(uint8_t color)
	{
	BSP_LCD_SetFont(&FontBMP);
	if(color==1)
		{
		BSP_LCD_SetTextColor(0xFF404040);	
		}
	else if(color==2)
		{
		BSP_LCD_SetTextColor(LCD_COLOR_RED);
		}
	else
		{
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		}		
	sprintf((char*)Buf, "%s", "GHI");						//SYNC OUT
	BSP_LCD_DisplayStringAt(47, 50, Buf, TRANSPARENT_MODE);	
	return;	
	};
	
///////////////////////////////////////////////////////////////	
//	internal gradient for sequencer
//	
void int_red_gradient(uint8_t sqc, uint8_t pd)
	{
	uint16_t x, y;
	x = 16+12*(sqc%8)+120*(pd%4);
 	y = 107+16*(sqc>>3)+105*(1-(pd>>2));
	BSP_LCD_SetTextColor(RED_GRADIENT_3);	
	BSP_LCD_DrawHLine(x, y, 4);
	BSP_LCD_SetTextColor(RED_GRADIENT_2);	
	BSP_LCD_DrawHLine(x, y+1, 4);
	BSP_LCD_SetTextColor(RED_GRADIENT_1);	
	BSP_LCD_DrawHLine(x, y+2, 4);
	BSP_LCD_SetTextColor(RED_GRADIENT_0);
	BSP_LCD_DrawHLine(x, y+3, 4);	
	BSP_LCD_SetTextColor(RED_GRADIENT_00);	
	BSP_LCD_FillRect(x, y+4, 4, 5);	
	BSP_LCD_SetTextColor(RED_PERIMETER_H);
	return;	
	}	
	
///////////////////////////////////////////////////////////////	
//	internal gradient for sequencer
//	
void int_blue_gradient(uint8_t sqc, uint8_t pd)
	{
	uint16_t x, y;
	x = 16+12*(sqc%8)+120*(pd%4);
 	y = 107+16*(sqc>>3)+105*(1-(pd>>2));	
	BSP_LCD_SetTextColor(BLUE_GRADIENT_3);	
	BSP_LCD_DrawHLine(x, y, 4);
	BSP_LCD_SetTextColor(BLUE_GRADIENT_2);	
	BSP_LCD_DrawHLine(x, y+1, 4);
	BSP_LCD_SetTextColor(BLUE_GRADIENT_1);	
	BSP_LCD_DrawHLine(x, y+2, 4);
	BSP_LCD_SetTextColor(BLUE_GRADIENT_0);
	BSP_LCD_DrawHLine(x, y+3, 4);	
	BSP_LCD_SetTextColor(BLUE_GRADIENT_00);
	BSP_LCD_FillRect(x, y+4, 4, 5);	
	BSP_LCD_SetTextColor(BLUE_PERIMETER_H);
	return;			
	}

///////////////////////////////////////////////////////////////	
//	internal gradient for sequencer
//		
void int_grey_gradient(uint8_t sqc, uint8_t pd)
	{
	uint16_t x, y;
	x = 16+12*(sqc%8)+120*(pd%4);
 	y = 107+16*(sqc>>3)+105*(1-(pd>>2));
	BSP_LCD_SetTextColor(GREY_GRADIENT_3);	
	BSP_LCD_DrawHLine(x, y, 4);
	BSP_LCD_SetTextColor(GREY_GRADIENT_2);	
	BSP_LCD_DrawHLine(x, y+1, 4);
	BSP_LCD_SetTextColor(GREY_GRADIENT_1);	
	BSP_LCD_DrawHLine(x, y+2, 4);
	BSP_LCD_SetTextColor(GREY_GRADIENT_0);
	BSP_LCD_DrawHLine(x, y+3, 4);	
	BSP_LCD_SetTextColor(GREY_GRADIENT_00);
	BSP_LCD_FillRect(x, y+4, 4, 5);			
	BSP_LCD_SetTextColor(GREY_PERIMETER_H);	
	return;		
	}	
	
///////////////////////////////////////////////////////////////	
//	internal perimeter for sequencer	
//		
void int_sqnc_perimeter(uint8_t sqc, uint8_t pd)
	{
	uint16_t x, y;
	x = 15+12*(sqc%8)+120*(pd%4);
 	y = 106+16*(sqc>>3)+105*(1-(pd>>2));
	BSP_LCD_DrawHLine(x+1, y, 4);		
	BSP_LCD_DrawHLine(x+1, y+10, 4);
	BSP_LCD_DrawVLine(x, y+1, 9);		
	BSP_LCD_DrawVLine(x+5, y+1, 9);	
	return;
	}	
	
	
/////////////////////////////////////////////	
//
//	draw logo Pioneer DJ on display
void DrawLOGO(void)
	{		
	uint8_t frame = 0;
	uint8_t VL = 0;	
	uint16_t n = 0;
	while(frame<26)							//change frame
		{	
		n = 0;	
		if(VL==0)
			{
			BSP_LCD_SelectLayer(1);	
			while(n<57600)						//draw picture
				{
				BSP_LCD_DrawPixel(n%480, (215-n/480), (0xFF000000+ANIMATION[frame][n][1]+256*ANIMATION[frame][n][2]+65536*ANIMATION[frame][n][0]));
				n++;		
				}	
			BSP_LCD_SetTransparency(1, 255);		//верхний слой виден
			BSP_LCD_SelectLayer(0);
			VL = 1;
			}
		else
			{
			BSP_LCD_SelectLayer(0);
			while(n<57600)						//draw picture
				{
				BSP_LCD_DrawPixel(n%480, (215-n/480), (0xFF000000+ANIMATION[frame][n][1]+256*ANIMATION[frame][n][2]+65536*ANIMATION[frame][n][0]));
				n++;		
				}		
			BSP_LCD_SetTransparency(1, 0);		//верхний не слой виден
			VL = 0;	
			}
		frame++;
		HAL_Delay(15);	
		}
	BSP_LCD_SetTransparency(1, 0);		//верхний не слой виден	
	BSP_LCD_SelectLayer(0);	
		
	HAL_Delay(330);
	BSP_LCD_SetFont(&Font15P);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	sprintf((char*)Buf, "%s", "ver.");
	BSP_LCD_DisplayStringAt(384,257,Buf, LEFT_MODE);	
	BSP_LCD_DisplayStringAt(420,257,FIRMWARE_VERSION, LEFT_MODE);	
			
	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);	
	BSP_LCD_DrawLine(101, 190, 379, 190);	
	BSP_LCD_DrawLine(101, 196, 379, 196);
	BSP_LCD_DrawLine(100, 191, 100, 195);
	BSP_LCD_DrawLine(380, 191, 380, 195);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);		
	n = 0;	
	while(n<277)
		{
		BSP_LCD_DrawLine(102+n, 192, 102+n, 194);
		n++;	
		HAL_Delay(6);	
		}	
	HAL_Delay(600);		
	return;	
	}		
	
	
/////////////////////////////////	
//	0 - none; 1 - gray; 2 - white;
//	
//	
void ShowLinkNumb(uint8_t stat)
	{
	uint32_t col;	
	if(stat==0)
		{
		col = LCD_COLOR_BLACK; 	
		}
	else if(stat==1)
		{
		col = LCD_COLOR_GRAY; 	
		}	
	else if(stat==2)
		{
		col = LCD_COLOR_WHITE; 	
		}		
	BSP_LCD_SetFont(&FontBMP);
	BSP_LCD_SetTextColor(col);		
	sprintf((char*)Buf, "%s", "67");						//PLAYER
	BSP_LCD_DisplayStringAt(4, 25,Buf, TRANSPARENT_MODE);	
	BSP_LCD_SetFont(&Font18D);	
	sprintf((char*)Buf, "%s", "#$");			//PLAYER NUBMER 3
	BSP_LCD_DisplayStringAt(9, 40, Buf, TRANSPARENT_MODE);
	BSP_LCD_DrawLine(3, 60, 36, 60);					//PLAYER shield
	BSP_LCD_DrawLine(1, 23, 1, 58);
	BSP_LCD_DrawPixel(2, 22, col);
	BSP_LCD_DrawPixel(2, 59, col);
	BSP_LCD_DrawLine(3, 21, 36, 21);
	BSP_LCD_DrawLine(38, 23, 38, 58);
	BSP_LCD_DrawPixel(37, 22, col);
	BSP_LCD_DrawPixel(37, 59, col);	
	return;	
	}	
	
//////////////////////////////////////////////////	
//show bpm and bpm shield
//
// input bpm*100
//	
void ShowBPM(uint32_t bpm)
	{		
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	uint32_t bpm_color;	
	if(UTILITY_SETTINGS[3]==0)			//internal bpm
		{
		bpm_color = CUE_COLOR;
		}
	else
		{			
		bpm_color = LCD_COLOR_WHITE;  
		}	
	if(bpm<40000)
		{
		bpm = bpm%100000; 	
		bpm = bpm+5;					//compensation;	
		BSP_LCD_SetTextColor(bpm_color);	
		BSP_LCD_SetFont(&Font20D);
		sprintf((char*)Buf, "%3lu", bpm/100);			//BPM count
		BSP_LCD_DisplayStringAt(418, 28, Buf, LEFT_MODE);
		BSP_LCD_DrawPixel(466, 46, bpm_color);	//
		BSP_LCD_DrawPixel(466, 47, bpm_color);	//	DOT
		BSP_LCD_DrawPixel(465, 46, bpm_color);	//
		BSP_LCD_DrawPixel(465, 47, bpm_color);	//
		BSP_LCD_SetFont(&Font11D);
		sprintf((char*)Buf, "%01lu", (bpm%100)/10);			//BPM count
		BSP_LCD_DisplayStringAt(469, 37,Buf, LEFT_MODE);
		}
	else
		{
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		BSP_LCD_FillRect(418, 28, 58, 20);	
		BSP_LCD_SetTextColor(bpm_color);		
		}
	BSP_LCD_SetFont(&FontBMP);
	if(UTILITY_SETTINGS[3]==0)				//internal bpm	
		{
		BSP_LCD_FillRect(415, 52, 63, 7);	
		BSP_LCD_DrawLine(416, 59, 476, 59);
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);	
		sprintf((char*)Buf, "%s", ";J");						//MASTER
		BSP_LCD_DisplayStringAt(426, 48, Buf, TRANSPARENT_MODE);
		BSP_LCD_SetTextColor(bpm_color);	
		}
	else			//external bpm
		{			
		sprintf((char*)Buf, "%s", "1");						//BPM
		BSP_LCD_DisplayStringAt(454, 53, Buf, TRANSPARENT_MODE);
		}
	BSP_LCD_DrawLine(416, 60, 476, 60);					//BPM shield
	BSP_LCD_DrawLine(478, 58, 478, 25);
	BSP_LCD_DrawPixel(477, 59, bpm_color);
	BSP_LCD_DrawPixel(477, 24, bpm_color);
	BSP_LCD_DrawLine(416, 23, 476, 23);
	BSP_LCD_DrawLine(414, 58, 414, 25);
	BSP_LCD_DrawPixel(415, 59, bpm_color);
	BSP_LCD_DrawPixel(415, 24, bpm_color);	
	return;	
	}
	
/////////////////////////////////	
//	0 - none; 1 - deck 1; 2 - deck 2;
//	ShowMasterDeck
//
void ShowMasterDeck(uint8_t MD)
	{
	if(MD>2)
		{
		return;	
		}	
	else if(MD!=previousMD)
		{
		if(MD==0)
			{
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);		
			BSP_LCD_FillRect(116, 20, 57, 14);		
			}			
		else
			{
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);		
			BSP_LCD_FillRect(116, 20, 57, 14);	
			BSP_LCD_SetTextColor(CUE_COLOR);
			BSP_LCD_SetFont(&FontBMP);	
			if(MD==1)
				{
				sprintf((char*)Buf, "%s", ";AB");						//MASTER PLAYER
				BSP_LCD_DisplayStringAt(116, 16, Buf, TRANSPARENT_MODE);
				sprintf((char*)Buf, "%s", ">CD");						//MASTER PLAYER
				BSP_LCD_DisplayStringAt(116, 27, Buf, TRANSPARENT_MODE);		
				}
			else if(MD==2)
				{
				sprintf((char*)Buf, "%s", ";<=");						//MASTER PLAYER
				BSP_LCD_DisplayStringAt(116, 16, Buf, TRANSPARENT_MODE);
				sprintf((char*)Buf, "%s", ">?@");						//MASTER PLAYER
				BSP_LCD_DisplayStringAt(116, 27, Buf, TRANSPARENT_MODE);	
				}
			}
		previousMD = MD;	
		}		
	}	
	
//////////////////////////////////////	
//	Show Phase meter 0 or 63 - none 1...4 phase	
//		
void ShowSPhaseMeter(uint8_t phase)
	{
	uint8_t j;	
	if(PreviousSPhase==phase)
		{
		return;	
		}	
	if(phase==0xFF || phase==63)								//draw static information	
		{
		BSP_LCD_SetFont(&Font13D);	
		BSP_LCD_SetTextColor(LCD_COLOR_LIGHTBLUE);
		BSP_LCD_DrawRect(178, 37, 29, 9);
		BSP_LCD_FillRect(207, 40, 3, 3);	
		BSP_LCD_DrawRect(210, 37, 29, 9);
		BSP_LCD_FillRect(239, 40, 3, 3);
		BSP_LCD_DrawRect(242, 37, 29, 9);
		BSP_LCD_FillRect(271, 40, 3, 3);	
		BSP_LCD_DrawRect(274, 37, 29,	 9);	
		sprintf((char*)Buf, "%s", ".");	
		BSP_LCD_DisplayStringAt(327, 36, Buf, LEFT_MODE);	
		sprintf((char*)Buf, "%s", "-");	
		BSP_LCD_DisplayStringAt(310, 36, Buf, LEFT_MODE);
		sprintf((char*)Buf, "%s", "-");	
		BSP_LCD_DisplayStringAt(321, 36, Buf, LEFT_MODE);		
		sprintf((char*)Buf, "%s", "-");				
		BSP_LCD_DisplayStringAt(336, 36, Buf, LEFT_MODE);			
		BSP_LCD_SetFont(&FontBMP);
		sprintf((char*)Buf, "%s", ":");						//Bars
		BSP_LCD_DisplayStringAt(348, 43, Buf, TRANSPARENT_MODE);
		BSP_LCD_SetTextColor(BLUE_COLOR_0);		//GRADIENT
		BSP_LCD_DrawHLine(179, 41, 27);	
		BSP_LCD_DrawHLine(211, 41, 27);	
		BSP_LCD_DrawHLine(243, 41, 27);	
		BSP_LCD_DrawHLine(275, 41, 27);	
		BSP_LCD_SetTextColor(BLUE_COLOR_1);
		BSP_LCD_DrawHLine(179, 40, 27);	
		BSP_LCD_DrawHLine(211, 40, 27);	
		BSP_LCD_DrawHLine(243, 40, 27);	
		BSP_LCD_DrawHLine(275, 40, 27);	
		BSP_LCD_SetTextColor(BLUE_COLOR_2);
		BSP_LCD_DrawHLine(179, 39, 27);	
		BSP_LCD_DrawHLine(211, 39, 27);	
		BSP_LCD_DrawHLine(243, 39, 27);	
		BSP_LCD_DrawHLine(275, 39, 27);	
		BSP_LCD_SetTextColor(BLUE_COLOR_3);
		BSP_LCD_DrawHLine(179, 38, 27);	
		BSP_LCD_DrawHLine(211, 38, 27);	
		BSP_LCD_DrawHLine(243, 38, 27);	
		BSP_LCD_DrawHLine(275, 38, 27);	
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		BSP_LCD_FillRect(179, 42, 27, 3);		
		BSP_LCD_FillRect(179+32, 42, 27, 3);
		BSP_LCD_FillRect(179+64, 42, 27, 3);
		BSP_LCD_FillRect(179+96, 42, 27, 3);
		}
	else
		{
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);	
		BSP_LCD_FillRect((179+32*(PreviousSPhase%4)), 42, 27, 3);
		BSP_LCD_SetTextColor(BLUE_COLOR_0);
		BSP_LCD_DrawHLine((179+32*(PreviousSPhase%4)), 41, 27);		
		BSP_LCD_SetTextColor(BLUE_COLOR_1);
		BSP_LCD_DrawHLine((179+32*(PreviousSPhase%4)), 40, 27);	
		BSP_LCD_SetTextColor(BLUE_COLOR_2);
		BSP_LCD_DrawHLine((179+32*(PreviousSPhase%4)), 39, 27);	
		BSP_LCD_SetTextColor(BLUE_COLOR_3);
		BSP_LCD_DrawHLine((179+32*(PreviousSPhase%4)), 38, 27);	
		BSP_LCD_SetTextColor(LCD_COLOR_LIGHTBLUE);	
		BSP_LCD_DrawRect(178+32*(PreviousSPhase%4), 37, 29, 9);	
		
			
		if(phase%4==0)									//RED PHASE
			{
			for(j=0;j<56;j++)	
				{
				BSP_LCD_DrawPixel((192+j%14), 41-(j/14), RED_BAR[j/14][j%14]);	
				BSP_LCD_DrawPixel((192+j%14), 41+(j/14), RED_BAR[j/14][j%14]);		
				BSP_LCD_DrawPixel((192-j%14), 41-(j/14), RED_BAR[j/14][j%14]);	
				BSP_LCD_DrawPixel((192-j%14), 41+(j/14), RED_BAR[j/14][j%14]);		
				}	
			BSP_LCD_SetTextColor(0xFFF1004F);		
			}
		else																						//BLUE PHASE
			{	
			for(j=0;j<56;j++)	
				{
				BSP_LCD_DrawPixel((192+j%14)+32*(phase%4), 41-(j/14), BLUE_BAR[j/14][j%14]);	
				BSP_LCD_DrawPixel((192+j%14)+32*(phase%4), 41+(j/14), BLUE_BAR[j/14][j%14]);		
				BSP_LCD_DrawPixel((192-j%14)+32*(phase%4), 41-(j/14), BLUE_BAR[j/14][j%14]);	
				BSP_LCD_DrawPixel((192-j%14)+32*(phase%4), 41+(j/14), BLUE_BAR[j/14][j%14]);		
				}
			BSP_LCD_SetTextColor(0xFFA6C8FF);		
			}	
	
		BSP_LCD_DrawRect(178+32*(phase%4), 37, 29, 9);		
			
		BSP_LCD_SetFont(&Font13D);
		BSP_LCD_SetTextColor(LCD_COLOR_LIGHTBLUE);
		sprintf((char*)Buf, "%s", ".");	
		BSP_LCD_DisplayStringAt(327, 36, Buf, LEFT_MODE);	
		sprintf((char *)Buf , "%01lu", (phase/40)%10);	
		BSP_LCD_DisplayStringAt(310, 36, Buf, LEFT_MODE);
		sprintf((char *)Buf, "%01lu", (phase>>2)%10);	
		BSP_LCD_DisplayStringAt(321, 36, Buf, LEFT_MODE);		
		sprintf((char *)Buf , "%01lu", (phase%4)+1);					
		BSP_LCD_DisplayStringAt(336, 36, Buf, LEFT_MODE);	
		}		
	PreviousSPhase = phase;
	return;	
	}


//////////////////////////////////////	
//	Show Phase meter 0 - none 1...4 phase	
//		
void ShowMPhaseMeter(uint8_t phase, uint16_t bar)
	{	
	if(PreviousMPhase==phase)
		{
		return;	
		}	
	if(phase==0xFF)								//draw static information	
		{
		BSP_LCD_SetFont(&Font13D);	
		BSP_LCD_SetTextColor(DARK_CUE_COLOR);			
		BSP_LCD_DrawRect(178, 23, 29, 9);
		BSP_LCD_FillRect(207, 26, 3, 3);	
		BSP_LCD_DrawRect(210, 23, 29, 9);
		BSP_LCD_FillRect(239, 26, 3, 3);
		BSP_LCD_DrawRect(242, 23, 29, 9);
		BSP_LCD_FillRect(271, 26, 3, 3);	
		BSP_LCD_DrawRect(274, 23, 29, 9);	
		BSP_LCD_SetTextColor(CUE_COLOR);		
		sprintf((char*)Buf, "%s", ".");	
		BSP_LCD_DisplayStringAt(327, 20, Buf, LEFT_MODE);	
		sprintf((char*)Buf, "%s", "-");	
		BSP_LCD_DisplayStringAt(310, 20, Buf, LEFT_MODE);
		sprintf((char*)Buf, "%s", "-");	
		BSP_LCD_DisplayStringAt(321, 20, Buf, LEFT_MODE);		
		sprintf((char*)Buf, "%s", "-");				
		BSP_LCD_DisplayStringAt(336, 20, Buf, LEFT_MODE);		
		BSP_LCD_SetFont(&FontBMP);
		sprintf((char*)Buf, "%s", ":");						//Bars
		BSP_LCD_DisplayStringAt(348, 27, Buf, TRANSPARENT_MODE);
		BSP_LCD_SetTextColor(CUE_COLOR_0);						//GRADIENT
		BSP_LCD_DrawHLine(179, 27, 27);	
		BSP_LCD_DrawHLine(211, 27, 27);	
		BSP_LCD_DrawHLine(243, 27, 27);	
		BSP_LCD_DrawHLine(275, 27, 27);	
		BSP_LCD_SetTextColor(CUE_COLOR_1);
		BSP_LCD_DrawHLine(179, 28, 27);	
		BSP_LCD_DrawHLine(211, 28, 27);	
		BSP_LCD_DrawHLine(243, 28, 27);	
		BSP_LCD_DrawHLine(275, 28, 27);	
		BSP_LCD_SetTextColor(CUE_COLOR_2);
		BSP_LCD_DrawHLine(179, 29, 27);	
		BSP_LCD_DrawHLine(211, 29, 27);	
		BSP_LCD_DrawHLine(243, 29, 27);	
		BSP_LCD_DrawHLine(275, 29, 27);	
		BSP_LCD_SetTextColor(CUE_COLOR_3);
		BSP_LCD_DrawHLine(179, 30, 27);	
		BSP_LCD_DrawHLine(211, 30, 27);	
		BSP_LCD_DrawHLine(243, 30, 27);	
		BSP_LCD_DrawHLine(275, 30, 27);	
		}
	else
		{
		BSP_LCD_SetTextColor(CUE_COLOR_0);
		BSP_LCD_DrawHLine((179+32*(PreviousMPhase%4)), 27, 27);		
		BSP_LCD_SetTextColor(CUE_COLOR_1);
		BSP_LCD_DrawHLine((179+32*(PreviousMPhase%4)), 28, 27);	
		BSP_LCD_SetTextColor(CUE_COLOR_2);
		BSP_LCD_DrawHLine((179+32*(PreviousMPhase%4)), 29, 27);	
		BSP_LCD_SetTextColor(CUE_COLOR_3);
		BSP_LCD_DrawHLine((179+32*(PreviousMPhase%4)), 30, 27);	
		BSP_LCD_SetTextColor(DARK_CUE_COLOR);	
		BSP_LCD_DrawRect(178+32*(PreviousMPhase%4), 23, 29, 9);	
		
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);	
		BSP_LCD_FillRect(179+32*(phase%4), 27, 27, 4);
			
		if(phase%4==0)									//RED PHASE
			{
			BSP_LCD_SetTextColor(LCD_COLOR_RED);					
			}
		else																						//ORANGE PHASE
			{	
			BSP_LCD_SetTextColor(CUE_COLOR);						
			}	

		BSP_LCD_DrawRect(178+32*(phase%4), 23, 29, 9);
			
		if(bar==0x01FF)
			{
			if(previous_MPHASE_color!=3)
				{		
				BSP_LCD_SetFont(&Font13D);	
				BSP_LCD_SetTextColor(CUE_COLOR);
				sprintf((char*)Buf, "%s", ".");	
				BSP_LCD_DisplayStringAt(327, 20, Buf, LEFT_MODE);	
				sprintf((char*)Buf, "%s", "-");	
				BSP_LCD_DisplayStringAt(310, 20, Buf, LEFT_MODE);
				sprintf((char*)Buf, "%s", "-");	
				BSP_LCD_DisplayStringAt(321, 20, Buf, LEFT_MODE);		
				sprintf((char*)Buf, "%s", "-");				
				BSP_LCD_DisplayStringAt(336, 20, Buf, LEFT_MODE);		
				BSP_LCD_SetFont(&FontBMP);
				sprintf((char*)Buf, "%s", ":");						//Bars
				BSP_LCD_DisplayStringAt(348, 27, Buf, TRANSPARENT_MODE);
				previous_MPHASE_color = 3;	
				}
			}
		else
			{		
			bar&=0x01ff;
			if(bar<17)
				{
				BSP_LCD_SetTextColor(LCD_COLOR_RED);	
				if(previous_MPHASE_color != 1)
					{
					BSP_LCD_SetFont(&FontBMP);
					sprintf((char*)Buf, "%s", ":");						//Bars
					BSP_LCD_DisplayStringAt(348, 27, Buf, TRANSPARENT_MODE);	
					}
				previous_MPHASE_color = 1;	
				}
			else
				{
				BSP_LCD_SetTextColor(CUE_COLOR);
				if(previous_MPHASE_color != 0)
					{
					BSP_LCD_SetFont(&FontBMP);
					sprintf((char*)Buf, "%s", ":");						//Bars
					BSP_LCD_DisplayStringAt(348, 27, Buf, TRANSPARENT_MODE);	
					}
				previous_MPHASE_color = 0;					
				}	
			BSP_LCD_SetFont(&Font13D);
			sprintf((char*)Buf, "%s", ".");					
			BSP_LCD_DisplayStringAt(327, 20, Buf, LEFT_MODE);
			if(bar>0)
				{					
				bar = bar-1;
				sprintf((char *)Buf , "%01lu", (bar/40)%10);	
				BSP_LCD_DisplayStringAt(310, 20, Buf, LEFT_MODE);	
				sprintf((char *)Buf, "%01lu", (bar>>2)%10);	
				BSP_LCD_DisplayStringAt(321, 20, Buf, LEFT_MODE);
				sprintf((char *)Buf , "%01lu", (bar%4)+1);					
				BSP_LCD_DisplayStringAt(336, 20, Buf, LEFT_MODE);						
				}
			else
				{
				sprintf((char*)Buf, "%s", "0");	
				BSP_LCD_DisplayStringAt(310, 20, Buf, LEFT_MODE);
				sprintf((char*)Buf, "%s", "0");	
				BSP_LCD_DisplayStringAt(321, 20, Buf, LEFT_MODE);		
				sprintf((char*)Buf, "%s", "0");				
				BSP_LCD_DisplayStringAt(336, 20, Buf, LEFT_MODE);			
				}				
			}
		}
	PreviousMPhase = phase;
	return;	
	}

/////////////////////////////////	
//
//internal function transparent bar for Browser, waveform
//
void int_DRAW_TRANSPARENT_BAR(void)
	{
	uint16_t j;
	uint32_t t, color;
	uint8_t r, g, b;	
	for(j=0;j<480;j++)
		{
		t = j;
		t = 160*t;
		if(t>0xFFFF)
			{
			t = 0xFFFF;	
			}
		t = 0xFFFF - t;	
		color = 0x01*t; 	
		r = color>>16;	
		color = 0xA6*t; 	
		g = color>>16;		
		color = 0xD4*t; 	
		b = color>>16;	
		color = 0xFF000000|r<<16|g<<8|b; 
		ForceDrawVLine(j, 0, 17, color);
		t = j;
		t = 150*t;
		if(t>0xFFFF)
			{
			t = 0xFFFF;	
			}
		t = 0xFFFF - t;	
		color = 0x53*t; 	
		r = color>>16;	
		color = 0xBD*t; 	
		g = color>>16;		
		color = 0xE9*t; 	
		b = color>>16;	
		color = 0xFF000000|r<<16|g<<8|b; 
		BSP_LCD_DrawPixel(j, 17, color);	
		}			
	return;	
	}		
	
/////////////////////////////////	
//
//			draw icon type: shot (0) or loop (1)
//			npad: number of pad
//	
void DrawLoopShot(uint8_t type, uint32_t pad_color, uint32_t back_color, uint8_t npad)
	{
	if(npad<8)
		{
		uint32_t COL70, COL50, COL30;
		uint32_t _tmp_col;
		uint8_t _r, _g, _b;
		////////////color 30
		_tmp_col = 70*(pad_color%256);
		_tmp_col = _tmp_col + 30*(back_color%256); 		
		_b = _tmp_col/100;	
		_tmp_col = 70*((pad_color>>8)%256);	
		_tmp_col = _tmp_col + 30*((back_color>>8)%256);			
		_g = _tmp_col/100;
		_tmp_col = 70*((pad_color>>16)%256);	
		_tmp_col = _tmp_col + 30*((back_color>>16)%256);			
		_r = _tmp_col/100;
		COL30 = 0xFF000000+_b+256*_g+65536*_r;		
		////////////color 50
		_tmp_col = 50*(pad_color%256);
		_tmp_col = _tmp_col + 50*(back_color%256); 		
		_b = _tmp_col/100;	
		_tmp_col = 50*((pad_color>>8)%256);	
		_tmp_col = _tmp_col + 50*((back_color>>8)%256);			
		_g = _tmp_col/100;
		_tmp_col = 50*((pad_color>>16)%256);	
		_tmp_col = _tmp_col + 50*((back_color>>16)%256);			
		_r = _tmp_col/100;
		COL50 = 0xFF000000+_b+256*_g+65536*_r;			
		////////////color 70
		_tmp_col = 30*(pad_color%256);
		_tmp_col = _tmp_col + 70*(back_color%256); 		
		_b = _tmp_col/100;	
		_tmp_col = 30*((pad_color>>8)%256);	
		_tmp_col = _tmp_col + 70*((back_color>>8)%256);			
		_g = _tmp_col/100;
		_tmp_col = 30*((pad_color>>16)%256);	
		_tmp_col = _tmp_col + 70*((back_color>>16)%256);			
		_r = _tmp_col/100;
		COL70 = 0xFF000000+_b+256*_g+65536*_r;	
		
		BSP_LCD_SetTextColor(back_color);	
		if(type==0)			//one shot
			{
			BSP_LCD_DrawLine(11+120*(npad%4), 89+105*(1-(npad>>2)), 29+120*(npad%4), 89+105*(1-(npad>>2)));					////////////////////////////////////						
			BSP_LCD_DrawLine(21+120*(npad%4), 87+105*(1-(npad>>2)), 29+120*(npad%4), 89+105*(1-(npad>>2)));					//		ONE SHOT ICON
			BSP_LCD_DrawLine(21+120*(npad%4), 91+105*(1-(npad>>2)), 29+120*(npad%4), 89+105*(1-(npad>>2)));					//
			BSP_LCD_DrawLine(11+120*(npad%4), 87+105*(1-(npad>>2)), 11+120*(npad%4), 91+105*(1-(npad>>2)));					////////////////////////////////////	
			BSP_LCD_DrawPixel(22+120*(npad%4), 88+105*(1-(npad>>2)), COL50);			//30
			BSP_LCD_DrawPixel(22+120*(npad%4), 90+105*(1-(npad>>2)), COL50);			//30
			BSP_LCD_DrawPixel(23+120*(npad%4), 87+105*(1-(npad>>2)), COL50);			//50
			BSP_LCD_DrawPixel(23+120*(npad%4), 91+105*(1-(npad>>2)), COL50);			//50
			BSP_LCD_DrawPixel(24+120*(npad%4), 87+105*(1-(npad>>2)), COL30);			//30
			BSP_LCD_DrawPixel(24+120*(npad%4), 91+105*(1-(npad>>2)), COL30);			//30	
			BSP_LCD_DrawPixel(27+120*(npad%4), 88+105*(1-(npad>>2)), COL50);			//50
			BSP_LCD_DrawPixel(27+120*(npad%4), 90+105*(1-(npad>>2)), COL50);			//50
			BSP_LCD_DrawPixel(29+120*(npad%4), 89+105*(1-(npad>>2)), COL70);			//70
			}
		else								//loop
			{
			BSP_LCD_DrawLine(11+120*(npad%4), 88+105*(1-(npad>>2)), 11+120*(npad%4), 90+105*(1-(npad>>2)));		//////////////////////////////////////////
			BSP_LCD_DrawLine(29+120*(npad%4), 88+105*(1-(npad>>2)), 29+120*(npad%4), 90+105*(1-(npad>>2)));		//
			BSP_LCD_DrawLine(12+120*(npad%4), 87+105*(1-(npad>>2)), 14+120*(npad%4), 87+105*(1-(npad>>2)));   //
			BSP_LCD_DrawLine(18+120*(npad%4), 87+105*(1-(npad>>2)), 28+120*(npad%4), 87+105*(1-(npad>>2)));		//				LOOP ICON
			BSP_LCD_DrawLine(12+120*(npad%4), 91+105*(1-(npad>>2)), 28+120*(npad%4), 91+105*(1-(npad>>2)));		//
			BSP_LCD_DrawLine(21+120*(npad%4), 86+105*(1-(npad>>2)), 24+120*(npad%4), 86+105*(1-(npad>>2)));		//
			BSP_LCD_DrawLine(21+120*(npad%4), 88+105*(1-(npad>>2)), 24+120*(npad%4), 88+105*(1-(npad>>2)));		//
			BSP_LCD_DrawLine(25+120*(npad%4), 85+105*(1-(npad>>2)), 26+120*(npad%4), 85+105*(1-(npad>>2)));		//
			BSP_LCD_DrawLine(25+120*(npad%4), 89+105*(1-(npad>>2)), 26+120*(npad%4), 89+105*(1-(npad>>2)));		//////////////////////////////////////////	
			BSP_LCD_DrawPixel(12+120*(npad%4), 88+105*(1-(npad>>2)), COL50);		//50
			BSP_LCD_DrawPixel(28+120*(npad%4), 88+105*(1-(npad>>2)), COL50);		//50
			BSP_LCD_DrawPixel(12+120*(npad%4), 90+105*(1-(npad>>2)), COL50);		//50
			BSP_LCD_DrawPixel(28+120*(npad%4), 90+105*(1-(npad>>2)), COL50);		//50	
			BSP_LCD_DrawPixel(18+120*(npad%4), 87+105*(1-(npad>>2)), COL70);		//70		
			BSP_LCD_DrawPixel(20+120*(npad%4), 86+105*(1-(npad>>2)), COL50);	//50		
			BSP_LCD_DrawPixel(20+120*(npad%4), 88+105*(1-(npad>>2)), COL50);	//50		
			BSP_LCD_DrawPixel(23+120*(npad%4), 85+105*(1-(npad>>2)), COL30);	//30		
			BSP_LCD_DrawPixel(23+120*(npad%4), 89+105*(1-(npad>>2)), COL30);	//30	
			BSP_LCD_DrawPixel(24+120*(npad%4), 85+105*(1-(npad>>2)), COL50);	//50			
			BSP_LCD_DrawPixel(24+120*(npad%4), 89+105*(1-(npad>>2)), COL50);	//50	
			BSP_LCD_DrawPixel(25+120*(npad%4), 86+105*(1-(npad>>2)), COL50);		//30	
			BSP_LCD_DrawPixel(25+120*(npad%4), 88+105*(1-(npad>>2)), COL50);		//30	
			}					
		}		
	return;	
	}
	
	
/////////////////////////////////////////////////////	
//	
//	show ram fill ram>100 - color red	
//	
void ShowRAM(uint8_t ram)
	{
	if(ram>100)
		{
		BSP_LCD_SetTextColor(LCD_COLOR_RED);
		ram = 100;	
		}
	else
		{
		BSP_LCD_SetTextColor(0xFFD5D5D5);
		}	
	BSP_LCD_SetFont(&FontBMP);
	sprintf((char*)Buf, "%s", "L");						//RAM
	BSP_LCD_DisplayStringAt(441, 1, Buf, TRANSPARENT_MODE);	
	BSP_LCD_SetFont(&Font8);
	sprintf((char*)Buf, "%1lu%%", ram);			//ram
	if(ram<10)
		{
		BSP_LCD_DisplayStringAt(444, 8, Buf, TRANSPARENT_MODE);
		}		
	else if(ram<100)
		{
		BSP_LCD_DisplayStringAt(441, 8, Buf, TRANSPARENT_MODE);
		}	
	else
		{
		BSP_LCD_DisplayStringAt(435, 8, Buf, TRANSPARENT_MODE);
		}		
	return;	
	}
	

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




