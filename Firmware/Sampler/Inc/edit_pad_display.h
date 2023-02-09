/////////////////////////////////////////////////////////////////////////////////////////////////
// 	edit_pad_display functions
//	product: DJS-500 sampler
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdint.h"

void int_EPD_DRAW_ALL_LINES(void);	
void int_EPD_DRAW_ONE_LINE(uint8_t UPDOWN);	
void int_EPD_REDRAW_ONE_LINE(void);												//internal function for EPD for change parameter
void EPD_PARAMETER(uint8_t n_pr);													//return text buffer
void int_reload_epd_realtime(void);												//apply new parameters realtime
void draw_st_wvfm(uint32_t start_addr, uint8_t zoom);			//draw big waveform zoom==0 - pixel=sample.zoom==1 - pixel=2sample
void DRAW_EPD_SELECTOR(uint8_t pos, uint8_t mode);				//draw selector cursor 0 - clear 1 - draw
void EPD_PROMPT(uint8_t pos);															//prompt in status bar
void CLEAR_SEQUNCE_MEMORY(void);													//clear sequence	
void _int_draw_pad(uint8_t type);													//internal function draw pad on edit: type==0 all; type==1 sequence only
void int_sqnc_cursor(uint8_t sqc, uint8_t mode);					//internal function draw cursor on sequencer


/////////////////////////////////////////////////	
//
//internal function for EDIT PAD DISPLAY
//	
void int_EPD_DRAW_ALL_LINES(void)
	{
	uint8_t E;

	BSP_LCD_SelectLayer(1);
	BSP_LCD_SetTextColor(0x00000000);	
	BSP_LCD_FillRect(4, 170, 354, 75);			//clear text in table
	for(E=0; E<TOTAL_EPD_POSITIONS; E++)
		{
		if(E==0)			//path
			{
			BSP_LCD_SelectLayer(0);	
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			BSP_LCD_SetFont(&Font15P);	
			if(P_COLOR[pad_x-1]<8)  //pad is enable
				{		
				sprintf((char*)Buf, "%s", P_SAMPLE_NAME[pad_x-1]);			//path for sample: text
				}
			else
				{
				sprintf((char*)Buf, "%s", "Push the selector to select a sample.");	
				}				
			BSP_LCD_DisplayStringAt(10, 24, Buf, TRANSPARENT_MODE);		
			}
		else if(E==1)					//WAVEFORM
			{
			BSP_LCD_SelectLayer(0);
			if(P_COLOR[pad_x-1]<8)  //pad is enable
				{				
				BSP_LCD_SetTextColor(PADS_LABEL_COLOR[P_COLOR[pad_x-1]]);
				}
			else
				{
				BSP_LCD_SetTextColor(PERIPH_PAD_GRADIENT_2);	
				}
			FillTriangle(244,234, 239, 154, 154, 149);				//draw triangle		
			if(P_COLOR[pad_x-1]<8)  //pad is enable
				{				
				draw_st_wvfm(P_START_ADR[pad_x-1], wzoom);
				}					
			}			
		else if(E>1 && E<10)				//TEXT TABLE
			{
			BSP_LCD_SelectLayer(1);		
			BSP_LCD_SetFont(&Font15P);	
			if(E==EPD_Position)
				{
				BSP_LCD_SetTextColor(GUI_STYLE_COLOR);	
				}
			else
				{
				BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
				}
			BSP_LCD_DisplayStringAt(25+(198*((E-2)/4)), 172+(19*((E-2)%4)), EPD_BASE[E-2], TRANSPARENT_MODE);
			if(P_COLOR[pad_x-1]<8)  //pad is enable
				{		
				EPD_PARAMETER(E-2);	
				BSP_LCD_DisplayStringAt(113+(175*((E-2)/4)), 172+(19*((E-2)%4)), Buf, TRANSPARENT_MODE);					
				}	
			}
		else if(E==10)				//PAD preview
			{
			_int_draw_pad(0);	
			}				
		}	
	BSP_LCD_SelectLayer(0);
	return;		
	}	
	
	
	
/////////////////////////////////////////////////	
//
//	internal function draw pad on edit
//	type==0 all		
//	type==1 sequence only
//	
void _int_draw_pad(uint8_t type)
	{
	if(type==0)
		{
		BSP_LCD_SelectLayer(1);
		BSP_LCD_SetTextColor(0x00000000);	
		BSP_LCD_FillRect(365, 200, 110, 55);			//clear area	
		}		
	BSP_LCD_SelectLayer(0);		
	BSP_LCD_SetTextColor(PAD_BACK_COLOR);	
	BSP_LCD_FillRect(365, 200, 110, 55);			//clear area	
	uint8_t seq;
	uint8_t wfm;	
	uint8_t shft;	
		
	BSP_LCD_SetFont(&Font8);
	if(P_COLOR[pad_x-1]<8 && (CURRENT_PRESET!=0xFF))					//pad enable
		{
		if(type==0)
			{	
			BSP_LCD_SetTextColor(PADS_LABEL_COLOR[P_COLOR[pad_x-1]]);
			BSP_LCD_FillRect(367, 174, 11, 12);		
			BSP_LCD_FillRect(380, 174, 34, 12);
			BSP_LCD_FillRect(367, 188, 27, 12);		
			BSP_LCD_FillRect(396, 188, 35, 12);
			BSP_LCD_FillRect(433, 188, 40, 12);	
			if(P_QUANTIZE[pad_x-1]==1)	
				{
				BSP_LCD_SetTextColor(PADS_LABEL_COLOR[P_COLOR[pad_x-1]]);		
				}
			else
				{
				BSP_LCD_SetTextColor(LCD_COLOR_DISABLE);		
				}
			BSP_LCD_FillRect(416, 174, 12, 12);	
			if(P_SYNC[pad_x-1]==1)	
				{
				BSP_LCD_SetTextColor(PADS_LABEL_COLOR[P_COLOR[pad_x-1]]);		
				}
			else
				{
				BSP_LCD_SetTextColor(LCD_COLOR_DISABLE);		
				}	
			BSP_LCD_FillRect(430, 174, 11, 12);
			BSP_LCD_SetTextColor(LCD_COLOR_DISABLE);		
			BSP_LCD_FillRect(443, 174, 30, 12);	
			BSP_LCD_SetTextColor(TEXT_PAD_COLOR);	
			Buf[0] = pad_x+0x30;																						//pad number
			Buf[1] = 0;
			BSP_LCD_DisplayStringAt(369, 176, Buf, TRANSPARENT_MODE);
			if(P_TYPE[pad_x-1]==0)			//sample
				{
				sprintf((char*)Buf, "%s", "SMPL");
				}
			else
				{
				sprintf((char*)Buf, "%s", "SQNC");	
				}
			BSP_LCD_DisplayStringAt(383, 176, Buf, TRANSPARENT_MODE);
			sprintf((char*)Buf, "%s", "Q");
			BSP_LCD_DisplayStringAt(418, 176, Buf, TRANSPARENT_MODE);
			sprintf((char*)Buf, "%s", "S");
			BSP_LCD_DisplayStringAt(432, 176, Buf, TRANSPARENT_MODE);		
			sprintf((char*)Buf, "%s", "OFF");
			BSP_LCD_DisplayStringAt(448, 176, Buf, TRANSPARENT_MODE);
			if(P_BPM[pad_x-1]<1000)			//if bpm<100.0
				{
				sprintf((char*)Buf, "%02lu.%01lu", P_BPM[pad_x-1]/10, P_BPM[pad_x-1]%10);			
				BSP_LCD_DisplayStringAt(405, 190, Buf, TRANSPARENT_MODE);	
				}
			else
				{
				sprintf((char*)Buf, "%03lu.%01lu", P_BPM[pad_x-1]/10, P_BPM[pad_x-1]%10);			
				BSP_LCD_DisplayStringAt(398, 190, Buf, TRANSPARENT_MODE);	
				}				
			if(P_GAIN[pad_x-1]<31)
				{
				sprintf((char*)Buf, "+%01lu.%01ludB", (30-P_GAIN[pad_x-1])/10, (30-P_GAIN[pad_x-1])%10);	
				BSP_LCD_DisplayStringAt(434, 190, Buf, TRANSPARENT_MODE);						
				}		
			else
				{
				sprintf((char*)Buf, "-%01lu.%01ludB", (P_GAIN[pad_x-1]-30)/10, (P_GAIN[pad_x-1]-30)%10);	
				BSP_LCD_DisplayStringAt(435, 190, Buf, TRANSPARENT_MODE);		
				}
			DrawLoopShot(P_TRIG[pad_x-1], PADS_LABEL_COLOR[P_COLOR[pad_x-1]], TEXT_PAD_COLOR, 3);		
			}
			
		if(P_TYPE[pad_x-1]==0)			//sample
			{
			BSP_LCD_SetTextColor(PAD_BACK_COLOR);
			BSP_LCD_FillRect(368, 206, 105, 34);		
			for(wfm=0;wfm<100;wfm++)	
				{
				ForceDrawVLine(wfm+370, 221-(P_WAVEFORM[pad_x-1][wfm]&0x0F), ((P_WAVEFORM[pad_x-1][wfm]&0x0F)<<1)+1, WS_COLOR_MAP[P_WAVEFORM[pad_x-1][wfm]>>7]);
				}		
			previous_play_position[pad_x-1] = (99*P_START_ADR[pad_x-1])/((P_SAMPLE_OFFSET[pad_x]-P_SAMPLE_OFFSET[pad_x-1])+P_START_ADR[pad_x-1]);		
			ForceDrawVLine(previous_play_position[pad_x-1]+370, 206, 31, 0xFFFFFFFF);		
			BSP_LCD_DrawPixel(previous_play_position[pad_x-1]+370, 237, PADS_LABEL_COLOR[P_COLOR[pad_x-1]]);	
			BSP_LCD_SetTextColor(PADS_LABEL_COLOR[P_COLOR[pad_x-1]]);	
			BSP_LCD_DrawHLine(previous_play_position[pad_x-1]+369, 238, 3);	
			BSP_LCD_DrawHLine(previous_play_position[pad_x-1]+368, 239, 5);		
			BSP_LCD_SetTextColor(0xFFBFBFBF);
			BSP_LCD_SetBackColor(PAD_BACK_COLOR);		
			sprintf((char*)Buf, "%s", "0:");	
			BSP_LCD_DisplayStringAt(399, 244, Buf, LEFT_MODE);			
			previous_time_position[pad_x-1] = P_START_ADR[pad_x-1]/588;		
			sprintf((char*)Buf, "%02lu.%02lu", (previous_time_position[pad_x-1]/75)%4500, previous_time_position[pad_x-1]%75);
			BSP_LCD_DisplayStringAt(409, 244, Buf, LEFT_MODE);
			BSP_LCD_SetBackColor(0xFF000000);				//return black back color, more useful
			}
		else																//sequencer
			{				
			BSP_LCD_SetTextColor(SQ_BACK_COLOR);	
			BSP_LCD_FillRect(370, 206, 100, 46);	
			BSP_LCD_SetTextColor(0xFF525252);	
			BSP_LCD_DrawRect(369, 205, 102, 48);
			for(seq=0;seq<16;seq++)
				{
				if(P_WAVEFORM[pad_x-1][64]>0)					//if sequence lenght> 4 beats
					{
					shft = seq_epos;	
					//shft = BEAT_CNT;	
					shft = shft>>4;	
					shft = shft<<4;		
					}					
				else
					{
					shft = 0;	
					}						
				if(seq==0)							//gradients red
					{	
					if(P_WAVEFORM[pad_x-1][seq+shft]==1)
						{	
						int_red_gradient(seq, 3);
						}							
					else
						{									
						BSP_LCD_SetTextColor(RED_PERIMETER_L);
						}
					}		
				else if(seq%4==0)							//gradients blue
					{	
					if(P_WAVEFORM[pad_x-1][seq+shft]==1)
						{	
						int_blue_gradient(seq, 3);
						}							
					else
						{		
						BSP_LCD_SetTextColor(BLUE_PERIMETER_L);
						}
					}
				else							//gradients white
					{
					if(P_WAVEFORM[pad_x-1][seq+shft]==1)
						{	
						int_grey_gradient(seq, 3);
						}							
					else
						{		
						BSP_LCD_SetTextColor(GREY_PERIMETER_L);
						}						
					}						
				int_sqnc_perimeter(seq, 3);	
					
				if(seq==8 || seq==10 || seq==12 || seq==14)					//squares
					{
					if(seq==8)
						{
						BSP_LCD_SetTextColor(SQ_STEP_CLR_0);	
						BSP_LCD_FillRect(376+24*(shft>>4), 244, 2, 2);
						BSP_LCD_FillRect(390+24*(shft>>4), 244, 2, 2);
						BSP_LCD_SetTextColor(SQ_STEP_CLR_1);	
						BSP_LCD_FillRect(378+24*(shft>>4), 244, 2, 2);
						BSP_LCD_FillRect(388+24*(shft>>4), 244, 2, 2);
						BSP_LCD_SetTextColor(SQ_STEP_CLR_2);	
						BSP_LCD_FillRect(380+24*(shft>>4), 244, 2, 2);
						BSP_LCD_FillRect(386+24*(shft>>4), 244, 2, 2);	
						BSP_LCD_SetTextColor(SQ_STEP_CLR_3);	
						BSP_LCD_FillRect(382+24*(shft>>4), 244, 4, 2);
						BSP_LCD_SetTextColor(RED_PERIMETER_SQ);		
						}
					else if(seq==10)
						{
						if(P_WAVEFORM[pad_x-1][64]==1 || P_WAVEFORM[pad_x-1][64]==3)	
							{
							BSP_LCD_SetTextColor(RED_PERIMETER_SQ);	
							}
						else
							{
							BSP_LCD_SetTextColor(GREY_PERIMETER_L);		
							}
						}	
					else if(seq==12)
						{
						if(P_WAVEFORM[pad_x-1][64]==3)	
							{
							BSP_LCD_SetTextColor(RED_PERIMETER_SQ);	
							}	
						else
							{
							BSP_LCD_SetTextColor(GREY_PERIMETER_L);		
							}								
						}
					else if(seq==14)
						{
						if(P_WAVEFORM[pad_x-1][64]==3)	
							{
							BSP_LCD_SetTextColor(RED_PERIMETER_SQ);	
							}
						else
							{
							BSP_LCD_SetTextColor(GREY_PERIMETER_L);		
							}
						}
					BSP_LCD_DrawHLine(376+12*(seq%8), 243, 16);		
					BSP_LCD_DrawHLine(376+12*(seq%8), 246, 16);	
					BSP_LCD_DrawVLine(375+12*(seq%8), 244, 2);	
					BSP_LCD_DrawVLine(392+12*(seq%8), 244, 2);	
					}		
				}	
			}			
		BSP_LCD_SetTextColor(PADS_LABEL_COLOR[P_COLOR[pad_x-1]]);		//sample name	
		uint8_t xlong;
		uint8_t xpath;
		xpath = 0;	
		xlong = strlen(P_SAMPLE_NAME[pad_x-1]);		
		if(xlong>0)
			{
			xlong--;	
			}	
		while(xlong>0)
			{
			if(P_SAMPLE_NAME[pad_x-1][xlong]==47 || P_SAMPLE_NAME[pad_x-1][xlong]==92)			//have a folder symbol in path
				{
				xpath = xlong;	
				xlong = 1;	
				}	
			xlong--;	
			}			
		if(xpath==0)
			{
			sprintf((char*)Buf, "%s", P_SAMPLE_NAME[pad_x-1]);	
			}
		else
			{
			sprintf((char*)Buf, "%s", &P_SAMPLE_NAME[pad_x-1][xpath+1]);		
			}		
		xlong = strlen(Buf);	//16 symbols max
		if(xlong>20)
			{
			Buf[16] = 0;	
			}	
		else
			{
			Buf[xlong-4] = 0;	
			}				
		BSP_LCD_DisplayStringAt(369, 256, Buf, TRANSPARENT_MODE);					
		//COLOR_SET(PADS_L_COLOR[P_COLOR[pad_x-1]], pad_x-1);	
		}	
	else										//this pad disable
		{
		BSP_LCD_SetTextColor(LCD_COLOR_DISABLE);		
		BSP_LCD_FillRect(367, 174, 11, 12);		
		BSP_LCD_FillRect(380, 174, 34, 12);		
		BSP_LCD_FillRect(416, 174, 12, 12);	
		BSP_LCD_FillRect(430, 174, 11, 12);	
		BSP_LCD_FillRect(367, 188, 27, 12);		
		BSP_LCD_FillRect(396, 188, 35, 12);
		BSP_LCD_FillRect(433, 188, 40, 12);		
		BSP_LCD_FillRect(443, 174, 30, 12);	
		BSP_LCD_SetTextColor(TEXT_PAD_COLOR);	
		Buf[0] = pad_x+0x30;
		Buf[1] = 0;
		BSP_LCD_DisplayStringAt(369, 176, Buf, TRANSPARENT_MODE);	
		sprintf((char*)Buf, "%s", "----");	
		BSP_LCD_DisplayStringAt(387, 175, Buf, TRANSPARENT_MODE);	
		sprintf((char*)Buf, "%s", "Q");
		BSP_LCD_DisplayStringAt(418, 176, Buf, TRANSPARENT_MODE);
		sprintf((char*)Buf, "%s", "S");
		BSP_LCD_DisplayStringAt(432, 176, Buf, TRANSPARENT_MODE);		
		sprintf((char*)Buf, "%s", "OFF");
		BSP_LCD_DisplayStringAt(88+360, 176, Buf, TRANSPARENT_MODE);
		sprintf((char*)Buf, "%s", "000.0");			
		BSP_LCD_DisplayStringAt(398, 190, Buf, TRANSPARENT_MODE);
		sprintf((char*)Buf, "%s", " 0.0dB");	
		BSP_LCD_DisplayStringAt(435, 190, Buf, TRANSPARENT_MODE);
		BSP_LCD_SetTextColor(0xFFBFBFBF);							//sample name
		sprintf((char*)Buf, "%s", "Empty");			
		BSP_LCD_DisplayStringAt(369, 256, Buf, TRANSPARENT_MODE);			
		COLOR_SET(EMPTY_PAD, pad_x-1);		
		}			
	
	if(ACTIVE_PAD<8)				//draw elements for active pad
		{
		BSP_LCD_SelectLayer(1);
		BSP_LCD_SetTextColor(PADS_LABEL_COLOR[P_COLOR[pad_x-1]]);		
		BSP_LCD_FillRect(443, 174, 30, 12);
		BSP_LCD_SetFont(&Font8);	
		BSP_LCD_SetTextColor(TEXT_PAD_COLOR);
		sprintf((char*)Buf, "%s", "ON");
		BSP_LCD_DisplayStringAt(451, 176, Buf, TRANSPARENT_MODE);
		BSP_LCD_SetFont(&Font15P);					
		BSP_LCD_SelectLayer(0);		
		}	
	return;	
	}	

/////////////////////////////////////////////////	
//
//internal function for EDIT PAD DISPLAY
//		
void int_EPD_DRAW_ONE_LINE(uint8_t UPDOWN)
	{
	DRAW_EPD_SELECTOR(EPD_Position, 0);
	if(UPDOWN==EPD_UP)
		{
		EPD_Position++;
		}
	else if(UPDOWN==EPD_DOWN)
		{
		EPD_Position--;	
		}
	DRAW_EPD_SELECTOR(EPD_Position, 1);
	EPD_PROMPT(EPD_Position);	
	return;	
	}


/////////////////////////////////////////////////	
//
//			prompt in status bar
//	
void EPD_PROMPT(uint8_t pos)
	{
	switch (pos)
			{
			case 0:
				{
				sprintf((char*)Buf, "%s", "Select sample file. Push selector.");	
				break;	
				}
			case 1:
				{
				sprintf((char*)Buf, "%s", "Waveform editor.");	
				break;	
				}
			case 2:
				{
				sprintf((char*)Buf, "%s", "Select PAD type.");	
				break;	
				}
			case 3:
				{
				sprintf((char*)Buf, "%s", "Start quantization.");	
				break;	
				}
			case 4:
				{
				sprintf((char*)Buf, "%s", "Tempo synchronization.");	
				break;	
				}
			case 5:
				{
				sprintf((char*)Buf, "%s", "Trigger type.");	
				break;	
				}
			case 6:
				{
				sprintf((char*)Buf, "%s", "Push selector to change tempo. SHIFT for edit tenths.");	
				break;	
				}
			case 7:
				{
				sprintf((char*)Buf, "%s", "Sample output level.");	
				break;	
				}
			case 8:
				{
				if(P_TYPE[pad_x-1]==0)
					{
					sprintf((char*)Buf, "%s", "Parameter not available for sample.");		
					}					
				else
					{
					sprintf((char*)Buf, "%s", "Number of bars for sequencer.");		
					}					
				break;	
				}
			case 9:
				{
				sprintf((char*)Buf, "%s", "Select PAD color.");	
				break;	
				}				
			case 10:
				{
				sprintf((char*)Buf, "%s", "Editing a sequence.");	
				break;	
				}		
			default:
			break;		
			}	
	uint32_t CURR_LAY;
	CURR_LAY = ActiveLayer;		
	BSP_LCD_SelectLayer(1);	
	BSP_LCD_SetTextColor(PERIPH_PAD_GRADIENT_2);
	BSP_LCD_FillRect(5, 251, 352, 17);			
	BSP_LCD_SetFont(&Font8);				
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);	
	BSP_LCD_DisplayStringAt(8, 255, Buf, TRANSPARENT_MODE);	
	BSP_LCD_SelectLayer(CURR_LAY);			
	return;		
	}
	
	
	
/////////////////////////////////////////////////	
//
//internal function for EPD for change parameter
//		
void int_EPD_REDRAW_ONE_LINE(void)
	{	
	if((EPD_Position>1)&&(EPD_Position<10))
		{		
		BSP_LCD_SelectLayer(1);	
		BSP_LCD_SetTransparency(1, 255);	
		BSP_LCD_SetTextColor(0x00000000);		
		if((EPD_Position>1)&&(EPD_Position<6))		//table
			{		
			BSP_LCD_FillRect(106, 170+(19*(EPD_Position-2)), 95, 18);		
			}
		else if((EPD_Position>5) && (EPD_Position<10))	
			{
			BSP_LCD_FillRect(281, 170+(19*(EPD_Position-6)), 77, 18);		
			}
		BSP_LCD_SetFont(&Font15P);
		BSP_LCD_SetTextColor(GUI_STYLE_COLOR);
		EPD_PARAMETER(EPD_Position-2);	
		BSP_LCD_DisplayStringAt(113+(175*((EPD_Position-2)/4)), 172+(19*((EPD_Position-2)%4)), Buf, TRANSPARENT_MODE);	
		BSP_LCD_SelectLayer(0);		
		}
	else if(EPD_Position==10)				//edit seqence
		{
		seq_epos = 0;	
		previous_seq_epos = 0;	
		BSP_LCD_SelectLayer(1);			
		int_sqnc_cursor(previous_seq_epos, 1);	
		BSP_LCD_SelectLayer(0);		
		}		
	return;		
	}
	
	
/////////////////////////////////////////////////	
//
//internal function for EDIT PAD DISPLAY
//		return text buffer
//
void EPD_PARAMETER(uint8_t n_pr)
	{
	switch (n_pr)
		{
		case 0:			//TYPE
			{
			if(P_TYPE[pad_x-1]==0)
				{
				sprintf((char*)Buf, "%s", "SAMPLE");	
				}	
			else
				{
				sprintf((char*)Buf, "%s", "SEQUENCE");	
				}
			break;	
			}
		case 1:				//QUANTIZE
			{
			if(P_QUANTIZE[pad_x-1]==0)
				{
				sprintf((char*)Buf, "%s", "OFF");	
				}	
			else
				{
				sprintf((char*)Buf, "%s", "ON");	
				}
			break;	
			}	
		case 2:				//SYNC
			{
			if(P_SYNC[pad_x-1]==0)
				{
				sprintf((char*)Buf, "%s", "OFF");	
				}	
			else
				{
				sprintf((char*)Buf, "%s", "ON");	
				}
			break;		
			}		
		case 3:					//TRIGGER
			{
			if(P_TRIG[pad_x-1]==0)
				{
				sprintf((char*)Buf, "%s", "ONE SHOT");	
				}	
			else
				{
				sprintf((char*)Buf, "%s", "LOOP");	
				}
			break;		
			}
		case 4:				//BPM
			{
			sprintf((char*)Buf, "%1lu.%1lubpm", P_BPM[pad_x-1]/10, P_BPM[pad_x-1]%10);
			break;			
			}
		case 5:				//GAIN
			{
			if(P_GAIN[pad_x-1]==30)
				{
				sprintf((char*)Buf, "%01lu.%01ludB", (30-P_GAIN[pad_x-1])/10, (30-P_GAIN[pad_x-1])%10);	
				}				
			else if(P_GAIN[pad_x-1]<31)
				{
				sprintf((char*)Buf, "+%01lu.%01ludB", (30-P_GAIN[pad_x-1])/10, (30-P_GAIN[pad_x-1])%10);					
				}
			else
				{
				sprintf((char*)Buf, "-%01lu.%01ludB", (P_GAIN[pad_x-1]-30)/10, (P_GAIN[pad_x-1]-30)%10);		
				}	
			break;			
			}	
		case 6:						//BARS
			{				
			if(P_TYPE[pad_x-1]==0)
				{
				sprintf((char*)Buf, "%s", "-");	
				}	
			else
				{
				if(P_WAVEFORM[pad_x-1][64]==1)	
					{
					sprintf((char*)Buf, "%s", "2");	
					}
				else if(P_WAVEFORM[pad_x-1][64]==3)	
					{
					sprintf((char*)Buf, "%s", "4");	
					}
				else
					{
					sprintf((char*)Buf, "%s", "1");	
					}	
				}	
			break;		
			}		
		case 7:						//COLOR			
			{
			switch (P_COLOR[pad_x-1])
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
			default: break;		
				}
			break;			
			}		
		default:
			break;	
		}	
	return;		
	}
	
	
/////////////////////////////////////////////////	
//
//internal function for EDIT PAD DISPLAY
//		apply new parameters realtime	
//
void int_reload_epd_realtime(void)
	{
	if(EPD_Position==7)			//change gain in SAI
		{
		ATT_LVL = P_GAIN[pad_x-1];	
		}
	else if(EPD_Position==9)			//regenerate color
		{
		CREATE_GUI_STYLE_COLOR(PADS_LABEL_COLOR[P_COLOR[pad_x-1]]);				//create gui table color
		BSP_LCD_SelectLayer(0);	
		BSP_LCD_SetTextColor(GUI_STYLE_COLOR);
		BSP_LCD_FillRect(4, 170, 354, 56);		//background table part 1
		BSP_LCD_FillRect(4, 227, 197, 18);		//background table part 2	
		BSP_LCD_SetTextColor(PADS_LABEL_COLOR[P_COLOR[pad_x-1]]);						//	table
		BSP_LCD_DrawLine(3, 169, 358, 169);
		BSP_LCD_DrawLine(3, 188, 358, 188);
		BSP_LCD_DrawLine(3, 207, 358, 207);
		BSP_LCD_DrawLine(3, 226, 358, 226);
		BSP_LCD_DrawLine(3, 245, 358, 245);
		BSP_LCD_DrawLine(3, 170, 3, 244);
		BSP_LCD_DrawLine(105, 170, 105, 244);
		BSP_LCD_DrawLine(201, 170, 201, 244);
		BSP_LCD_DrawLine(280, 170, 280, 244);
		BSP_LCD_DrawLine(358, 170, 358, 244);	
		FillTriangle(244,234, 239, 154, 154, 149);				//draw triangle			
		BSP_LCD_SelectLayer(1);		
		BSP_LCD_SetFont(&Font15P);	
		BSP_LCD_SetTextColor(GUI_STYLE_COLOR);	
		BSP_LCD_DisplayStringAt(223, 229, EPD_BASE[7], TRANSPARENT_MODE);	
		DRAW_EPD_SELECTOR(EPD_Position, 2); //draw entering
		_int_draw_pad(0);	
		COLOR_SET(PADS_L_COLOR[P_COLOR[pad_x-1]] , pad_x-1);
		need_load_rgb = 1;			//realtime update RGB led	
		}	
	else if(EPD_Position==10)			//sequnce edit
		{	
		BSP_LCD_SelectLayer(1);	
		int_sqnc_cursor(previous_seq_epos, 0);		
		int_sqnc_cursor(seq_epos, 1);
		BSP_LCD_SelectLayer(0);
		if((seq_epos==16 && previous_seq_epos==15) ||
			 (seq_epos==15 && previous_seq_epos==16) ||
			 (seq_epos==31 && previous_seq_epos==32) ||
			 (seq_epos==32 && previous_seq_epos==31) ||
			 (seq_epos==47 && previous_seq_epos==48) ||
			 (seq_epos==48 && previous_seq_epos==47))
			{	
			_int_draw_pad(1);
			}			
		previous_seq_epos = seq_epos; 	
		}	
	}

	
	
/////////////////////////////////////////////////	
//
//	internal function for EDIT PAD DISPLAY
//	mode==0 - clear
//	mode==1 - draw
//	
void int_sqnc_cursor(uint8_t sqc, uint8_t mode)
	{
	sqc = sqc%16;	
	uint16_t x, y;
	x = 374+12*(sqc%8);
 	y = 210+16*(sqc>>3);
	if(mode==0)
		{
		BSP_LCD_SetTextColor(0x00000000);
		BSP_LCD_DrawHLine(x+1, y, 6);	
		BSP_LCD_DrawHLine(x+1, y+12, 6);
		BSP_LCD_DrawVLine(x, y+1, 11);		
		BSP_LCD_DrawVLine(x+7, y+1, 11);		
		BSP_LCD_DrawPixel(x+1, y+1, 0x00000000);		
		BSP_LCD_DrawPixel(x+6, y+1, 0x00000000);	
		BSP_LCD_DrawPixel(x+1, y+11, 0x00000000);		
		BSP_LCD_DrawPixel(x+6, y+11, 0x00000000);				
		}		
	else
		{
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);		
		BSP_LCD_DrawHLine(x+2, y, 4);	
		BSP_LCD_DrawHLine(x+2, y+12, 4);
		BSP_LCD_DrawVLine(x, y+2, 9);		
		BSP_LCD_DrawVLine(x+7, y+2, 9);		
		BSP_LCD_DrawPixel(x+1, y, 0xFFA3A3A3);	
		BSP_LCD_DrawPixel(x+6, y, 0xFFA3A3A3);	
		BSP_LCD_DrawPixel(x, y+1, 0xFFA3A3A3);	
		BSP_LCD_DrawPixel(x+7, y+1, 0xFFA3A3A3);		
		BSP_LCD_DrawPixel(x+1, y+12, 0xFFA3A3A3);	
		BSP_LCD_DrawPixel(x+6, y+12, 0xFFA3A3A3);	
		BSP_LCD_DrawPixel(x, y+11, 0xFFA3A3A3);	
		BSP_LCD_DrawPixel(x+7, y+11, 0xFFA3A3A3);	
		BSP_LCD_DrawPixel(x+1, y+1, 0xFFCDCDCD);		
		BSP_LCD_DrawPixel(x+6, y+1, 0xFFCDCDCD);	
		BSP_LCD_DrawPixel(x+1, y+11, 0xFFCDCDCD);		
		BSP_LCD_DrawPixel(x+6, y+11, 0xFFCDCDCD);	
		}
	return;
	}		


/////////////////////////////////////////////////	
//
//	Draw big waveform
//	zoom==0 - pixel = sample,
//	zoom==1 - pixel = 2*sample;
//
void draw_st_wvfm(uint32_t start_addr, uint8_t zoom)
	{	
	uint16_t i, zm;	
	int16_t	L0, L1, R1, R0, Rmin, Rmax, Lmin, Lmax, TTL, TTR;
	uint32_t	waddr0, waddr1, offset;
	uint32_t R;	
	zm = 1;
	zm = zm<<zoom;	
	BSP_LCD_SelectLayer(0);				
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);			//clear
	BSP_LCD_DrawVLine(6, 46, 51);
	BSP_LCD_DrawVLine(6, 98, 51);	
	offset = start_addr>>zoom;	
	if(offset>234)					//ower display
		{
		offset-=234;
		for(i=0;i<468;i++)
			{
			waddr0 = (i+offset)*zm; 
			waddr1 = waddr0 + zm;
			if(i<467)
				{				
				BSP_LCD_SetTextColor(LCD_COLOR_BLACK);			//clear				
				BSP_LCD_DrawVLine(7+i, 46, 51);
				BSP_LCD_DrawVLine(7+i, 98, 51);		
				}
			if(zoom>3 && (waddr1<new_all_data))
				{							
				Rmax = PCM[waddr0>>13][waddr0%8192][1];
				Rmin = Rmax;
				Lmax = PCM[waddr0>>13][waddr0%8192][0];	
				Lmin = Lmax;
				for(R=1;R<zm;R++)					//search min & max
					{
					TTL = PCM[(waddr0+R)>>13][(waddr0+R)%8192][0];		
					TTR = PCM[(waddr0+R)>>13][(waddr0+R)%8192][1];		
					if(TTR<Rmin)
						{
						Rmin = TTR;	
						}
					else if(TTR>Rmax)
						{
						Rmax = TTR;	
						}
					if(TTL<Lmin)
						{
						Lmin = TTL;	
						}
					else if(TTL>Lmax)
						{
						Lmax = TTL;	
						}		
					}	
				BSP_LCD_SetTextColor(WF_COLOR_MAP[(Lmax-Lmin)>>13]);	
				if(zoom<7 && ((Lmax-Lmin)<5140))
					{
					//none	
					}
				else if(zoom<5)
					{
					Lmax-=1500;	
					Lmin+=1500;	
					BSP_LCD_DrawLine(6+i, 71-(Lmin/1285), i+6, 71-(Lmax/1285));		
					}
				else if(zoom<7)
					{
					Lmax-=900;	
					Lmin+=900;	
					BSP_LCD_DrawLine(6+i, 71-(Lmin/1285), i+6, 71-(Lmax/1285));		
					}	
				else
					{
					BSP_LCD_DrawLine(6+i, 71-(Lmin/1285), i+6, 71-(Lmax/1285));	
					}	
				BSP_LCD_SetTextColor(WF_COLOR_MAP[(Rmax-Rmin)>>13]);
				if(zoom<7 && ((Rmax-Rmin)<5140))
					{
					//none	
					}
				else if(zoom<5)
					{
					Rmax-=1500;	
					Rmin+=1500;	
					BSP_LCD_DrawLine(6+i, 123-(Rmin/1285), i+6, 123-(Rmax/1285));		
					}
				else if(zoom<7)
					{
					Rmax-=900;	
					Rmin+=900;	
					BSP_LCD_DrawLine(6+i, 123-(Rmin/1285), i+6, 123-(Rmax/1285));	
					}	
				else
					{
					BSP_LCD_DrawLine(6+i, 123-(Rmin/1285), i+6, 123-(Rmax/1285));	
					}		
				}
			if(waddr1<new_all_data && (i<467))				//end sample
				{
				L0 = PCM[waddr0>>13][waddr0%8192][0];
				L1 = PCM[waddr1>>13][waddr1%8192][0];
				R0 = PCM[waddr0>>13][waddr0%8192][1];
				R1 = PCM[waddr1>>13][waddr1%8192][1];	
				if(zoom>3)
					{
					BSP_LCD_SetTextColor(WF_COLOR_MAP[(abs(L1)>>12)+((Lmax-Lmin)>>13)>>1]);
					BSP_LCD_DrawLine(6+i, 71-(L0/1285), i+7, 71-(L1/1285));
					BSP_LCD_SetTextColor(WF_COLOR_MAP[(abs(R1)>>12)+((Rmax-Rmin)>>13)>>1]);
					BSP_LCD_DrawLine(6+i, 123-(R0/1285), i+7, 123-(R1/1285));	
					}
				else
					{	
					BSP_LCD_SetTextColor(WF_COLOR_MAP[abs(L1)>>12]);	
					BSP_LCD_DrawLine(6+i, 71-(L0/1285), i+7, 71-(L1/1285));		
					BSP_LCD_SetTextColor(WF_COLOR_MAP[abs(R1)>>12]);	
					BSP_LCD_DrawLine(6+i, 123-(R0/1285), i+7, 123-(R1/1285));		
					}
				}
			}				
		}
	else		
		{
		for(i=0;i<468;i++)
			{
			if(i<467)
				{				
				BSP_LCD_SetTextColor(LCD_COLOR_BLACK);			//clear				
				BSP_LCD_DrawVLine(7+i, 46, 51);
				BSP_LCD_DrawVLine(7+i, 98, 51);			
				}	
			if(i>=(234-offset))
				{
				waddr0 = (i-(234-offset))*zm; 
				waddr1 = waddr0 + zm;
				if(zoom>3 && (waddr1<new_all_data))
					{							
					Rmax = PCM[waddr0>>13][waddr0%8192][1];
					Rmin = Rmax;
					Lmax = PCM[waddr0>>13][waddr0%8192][0];	
					Lmin = Lmax;
					for(R=1;R<zm;R++)					//search min & max
						{
						TTL = PCM[(waddr0+R)>>13][(waddr0+R)%8192][0];		
						TTR = PCM[(waddr0+R)>>13][(waddr0+R)%8192][1];		
						if(TTR<Rmin)
							{
							Rmin = TTR;	
							}
						else if(TTR>Rmax)
							{
							Rmax = TTR;	
							}
						if(TTL<Lmin)
							{
							Lmin = TTL;	
							}
						else if(TTL>Lmax)
							{
							Lmax = TTL;	
							}		
						}	
					BSP_LCD_SetTextColor(WF_COLOR_MAP[(Lmax-Lmin)>>13]);	
					if(zoom<7 && ((Lmax-Lmin)<5140))
						{
						//none	
						}
					else if(zoom<5)
						{
						Lmax-=1500;	
						Lmin+=1500;	
						BSP_LCD_DrawLine(6+i, 71-(Lmin/1285), i+6, 71-(Lmax/1285));		
						}
					else if(zoom<7)
						{
						Lmax-=900;	
						Lmin+=900;	
						BSP_LCD_DrawLine(6+i, 71-(Lmin/1285), i+6, 71-(Lmax/1285));		
						}	
					else
						{
						BSP_LCD_DrawLine(6+i, 71-(Lmin/1285), i+6, 71-(Lmax/1285));	
						}	
					BSP_LCD_SetTextColor(WF_COLOR_MAP[(Rmax-Rmin)>>13]);
					if(zoom<7 && ((Rmax-Rmin)<5140))
						{
						//none	
						}
					else if(zoom<5)
						{
						Rmax-=1500;	
						Rmin+=1500;	
						BSP_LCD_DrawLine(6+i, 123-(Rmin/1285), i+6, 123-(Rmax/1285));		
						}
					else if(zoom<7)
						{
						Rmax-=900;	
						Rmin+=900;	
						BSP_LCD_DrawLine(6+i, 123-(Rmin/1285), i+6, 123-(Rmax/1285));	
						}	
					else
						{
						BSP_LCD_DrawLine(6+i, 123-(Rmin/1285), i+6, 123-(Rmax/1285));	
						}		
					}
				if(waddr1<new_all_data && (i<467))				//end sample
					{	
					L0 = PCM[waddr0>>13][waddr0%8192][0];
					L1 = PCM[waddr1>>13][waddr1%8192][0];
					R0 = PCM[waddr0>>13][waddr0%8192][1];
					R1 = PCM[waddr1>>13][waddr1%8192][1];		
					if(zoom>3)
						{
						BSP_LCD_SetTextColor(WF_COLOR_MAP[(abs(L1)>>12)+((Lmax-Lmin)>>13)>>1]);
						BSP_LCD_DrawLine(6+i, 71-(L0/1285), i+7, 71-(L1/1285));
						BSP_LCD_SetTextColor(WF_COLOR_MAP[(abs(R1)>>12)+((Rmax-Rmin)>>13)>>1]);
						BSP_LCD_DrawLine(6+i, 123-(R0/1285), i+7, 123-(R1/1285));	
						}
					else
						{
						BSP_LCD_SetTextColor(WF_COLOR_MAP[abs(L1)>>12]);	
						BSP_LCD_DrawLine(6+i, 71-(L0/1285), i+7, 71-(L1/1285));		
						BSP_LCD_SetTextColor(WF_COLOR_MAP[abs(R1)>>12]);	
						BSP_LCD_DrawLine(6+i, 123-(R0/1285), i+7, 123-(R1/1285));		
						}
					}
				}
			}					
		}	
	BSP_LCD_SetTextColor(PERIPH_PAD_GRADIENT_3);	
	BSP_LCD_FillRect(51, 155, 25, 8);	
	BSP_LCD_FillRect(299, 155, 32, 8);
	BSP_LCD_FillRect(338, 155, 111, 10);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetFont(&Font8);
	sprintf((char*)Buf, "%s%01u", "Zoom: 1:", zm);		
	BSP_LCD_DisplayStringAt(7, 155, Buf, TRANSPARENT_MODE);
	sprintf((char*)Buf, "%s%02lu.%02lu",  "Start 0:", (start_addr/44100)%4500, (start_addr/588)%75);		
	BSP_LCD_DisplayStringAt(253, 155, Buf, TRANSPARENT_MODE);	
	sprintf((char*)Buf, "(%01lu sample)", start_addr);	
	BSP_LCD_DisplayStringAt(334, 155, Buf, TRANSPARENT_MODE);		
	return;	
	}
	
	
	
	
/////////////////////////////////////////////////	
//
//draw selector cursor 0 - clear, 1 - draw, 2 - draw entering
//		
void DRAW_EPD_SELECTOR(uint8_t pos, uint8_t mode)
	{
	if(pos<2 || pos==10)		//cursor
		{
		BSP_LCD_SelectLayer(1);		
		if(mode==0)			//clear	
			{
			BSP_LCD_SetTextColor(0x00000000);		
			}
		else					//draw
			{
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			}
		if(pos==0)			//path		
			{
			BSP_LCD_DrawRect(2, 20, 476, 21);		
			BSP_LCD_DrawRect(1, 19, 478, 23);		
			return;	
			}			
		else if(pos==1)			//wfm
			{
			BSP_LCD_DrawRect(2, 42, 476, 125);				
			BSP_LCD_DrawRect(1, 41, 478, 127);	
			return;	
			}	
		else if(pos==10)			//pad
			{
			BSP_LCD_DrawRect(361, 168, 118, 103);		
			BSP_LCD_DrawRect(360, 167, 120, 105);
			return;	
			}		
		}	
	else						//////////////////table
		{
		uint8_t ps;	
		ps = pos-2;
		BSP_LCD_SelectLayer(1);	
		BSP_LCD_SetFont(&Font15P);		
		if(mode==0)			//clear	
			{
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);	
			}
		else if(mode>0)
			{
			BSP_LCD_SetTextColor(GUI_STYLE_COLOR);
			}
		BSP_LCD_DisplayStringAt(25+(198*(ps/4)), 172+(19*((ps)%4)), EPD_BASE[ps], TRANSPARENT_MODE);
		EPD_PARAMETER(ps);	
		BSP_LCD_DisplayStringAt(113+(175*((ps)/4)), 172+(19*((ps)%4)), Buf, TRANSPARENT_MODE);
		BSP_LCD_SelectLayer(0);	
		if(mode==0)			//clear	
			{
			BSP_LCD_SetTextColor(GUI_STYLE_COLOR);
			if(ps<4)
				{	
				BSP_LCD_FillRect(4, 170+(19*ps), 101, 18);
				BSP_LCD_FillRect(106, 170+(19*ps), 95, 18);
				BSP_LCD_SetTextColor(PADS_LABEL_COLOR[P_COLOR[pad_x-1]]);
				BSP_LCD_DrawLine(4, 169+(19*ps), 201, 169+(19*ps));	
				}
			else
				{
				BSP_LCD_FillRect(202, 170+(19*(ps-4)), 78, 18);
				BSP_LCD_FillRect(281, 170+(19*(ps-4)), 77, 18);
				BSP_LCD_SetTextColor(PADS_LABEL_COLOR[P_COLOR[pad_x-1]]);
				BSP_LCD_DrawLine(202, 169+(19*(ps-4)), 358, 169+(19*(ps-4)));		
				}
			}
		else if(mode==1)			
			{
			if(ps<4)
				{	
				BSP_LCD_SetTextColor(LCD_COLOR_WHITE);			
				BSP_LCD_FillRect(4, 169+(19*ps), 101, 9);
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_2);	
				BSP_LCD_FillRect(4, 178+(19*ps), 101, 5);	
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_1);	
				BSP_LCD_FillRect(4, 183+(19*ps), 101, 5);	
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_3);		
				BSP_LCD_FillRect(106, 169+(19*ps), 95, 9);
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_5);	
				BSP_LCD_FillRect(106, 178+(19*ps), 95, 5);
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_4);
				BSP_LCD_FillRect(106, 183+(19*ps), 95, 5);
				BSP_LCD_SetTextColor(GUI_STYLE_COLOR);					
				BSP_LCD_FillRect(11, 176+(19*ps), 5, 5);							////////////////
				BSP_LCD_DrawLine(12, 175+(19*ps), 14, 175+(19*ps));		//
				BSP_LCD_DrawLine(12, 181+(19*ps), 14, 181+(19*ps));		//	BIG DOT
				BSP_LCD_DrawLine(10, 177+(19*ps), 10, 179+(19*ps));		//
				BSP_LCD_DrawLine(16, 177+(19*ps), 16, 179+(19*ps));		//					
				}
			else
				{
				BSP_LCD_SetTextColor(LCD_COLOR_WHITE);			
				BSP_LCD_FillRect(202, 169+(19*(ps-4)), 78, 9);
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_2);	
				BSP_LCD_FillRect(202, 178+(19*(ps-4)), 78, 5);	
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_1);	
				BSP_LCD_FillRect(202, 183+(19*(ps-4)), 78, 5);	
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_3);		
				BSP_LCD_FillRect(281, 169+(19*(ps-4)), 77, 9);
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_5);	
				BSP_LCD_FillRect(281, 178+(19*(ps-4)), 77, 5);
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_4);
				BSP_LCD_FillRect(281, 183+(19*(ps-4)), 77, 5);
				BSP_LCD_SetTextColor(GUI_STYLE_COLOR);	
				BSP_LCD_FillRect(209, 176+(19*(ps-4)), 5, 5);										/////////////
				BSP_LCD_DrawLine(210, 175+(19*(ps-4)), 212, 175+(19*(ps-4)));		//
				BSP_LCD_DrawLine(210, 181+(19*(ps-4)), 212, 181+(19*(ps-4)));		//	BIG DOT
				BSP_LCD_DrawLine(208, 177+(19*(ps-4)), 208, 179+(19*(ps-4)));		//
				BSP_LCD_DrawLine(214, 177+(19*(ps-4)), 214, 179+(19*(ps-4)));		//	
				}	
			}
		else if(mode==2)		//draw entering			
			{
			if(ps<4)
				{	
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_3);			
				BSP_LCD_FillRect(4, 169+(19*ps), 101, 9);
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_5);	
				BSP_LCD_FillRect(4, 178+(19*ps), 101, 5);	
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_4);	
				BSP_LCD_FillRect(4, 183+(19*ps), 101, 5);	
				BSP_LCD_SetTextColor(LCD_COLOR_WHITE);		
				BSP_LCD_FillRect(106, 169+(19*ps), 95, 9);
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_2);	
				BSP_LCD_FillRect(106, 178+(19*ps), 95, 5);
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_1);
				BSP_LCD_FillRect(106, 183+(19*ps), 95, 5);
				BSP_LCD_SetTextColor(GUI_STYLE_COLOR);	
				FillTriangle(10, 10, 17, 171+(19*ps), 185+(19*ps), 178+(19*ps));							
				}
			else
				{
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_3);			
				BSP_LCD_FillRect(202, 169+(19*(ps-4)), 78, 9);
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_5);	
				BSP_LCD_FillRect(202, 178+(19*(ps-4)), 78, 5);	
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_4);	
				BSP_LCD_FillRect(202, 183+(19*(ps-4)), 78, 5);	
				BSP_LCD_SetTextColor(LCD_COLOR_WHITE);		
				BSP_LCD_FillRect(281, 169+(19*(ps-4)), 77, 9);
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_2);	
				BSP_LCD_FillRect(281, 178+(19*(ps-4)), 77, 5);
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_1);
				BSP_LCD_FillRect(281, 183+(19*(ps-4)), 77, 5);
				BSP_LCD_SetTextColor(GUI_STYLE_COLOR);	
				FillTriangle(208, 208, 215, 171+(19*(ps-4)), 185+(19*(ps-4)), 178+(19*(ps-4)));		
				}
			}
		return;		
		}
	BSP_LCD_SelectLayer(0);		
	return;		
	}
	
	
	
	
/////////////////////////////////////////////////	
//
//		clear SEQUNCE memory
//		
void CLEAR_SEQUNCE_MEMORY(void)
	{
	uint8_t i;	
	P_WAVEFORM[pad_x-1][0] = 1;
	for(i=1;i<99;i++)
		{
		P_WAVEFORM[pad_x-1][i] = 0;	
		}		
	return;	
	}	


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



