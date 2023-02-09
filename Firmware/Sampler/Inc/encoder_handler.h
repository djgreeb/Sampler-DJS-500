/////////////////////////////////////////////////////////////////////////////////////////////////
// 	ENCODER HANDLER
//	product: DJS-500 sampler
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdint.h"

void encoder_handler(void);

//////////////////////////////////////////////////////////
//
//					ENCODER HANDLER
//
void encoder_handler(void)
	{
	if(enc_need_up)	
		{
		if(dSHOW==PRST_LIST)
			{
			NAVIGATOR(PRST_LIST_UP);	
			}
		else if(dSHOW==UTILITY)
			{
			if(edit_parameter==0)
				{
				NAVIGATOR(UTILITY_UP);
				}
			else
				{
				if((UCurrentCursorPosition+CurrentUPosition-1)==0)							//AUTO LOAD
					{
					if(UTILITY_SETTINGS[0]<(TOTAL_PRESETS-1))	
						{
						UTILITY_SETTINGS[UCurrentCursorPosition+CurrentUPosition-1]++;	
						int_U_REDRAW_ONE_LINE();	
						}							
					}
				else if((UCurrentCursorPosition+CurrentUPosition-1)==4)							//INTERNAL BPM
					{
					if(KEY_SHIFT_pressed==0)			//shift not pressed	
						{
						if((UTILITY_SETTINGS[4]/10)<200)	
							{
							UTILITY_SETTINGS[UCurrentCursorPosition+CurrentUPosition-1]+=10;	
							int_U_REDRAW_ONE_LINE();	
							int_reload_parameter_realtime();		
							}							
						}
					else								//shift pressed
						{
						if((UTILITY_SETTINGS[4]%10)<9)	
							{
							UTILITY_SETTINGS[UCurrentCursorPosition+CurrentUPosition-1]++;	
							int_U_REDRAW_ONE_LINE();	
							int_reload_parameter_realtime();		
							}		
						}	
					}
				else if(11>(UCurrentCursorPosition+CurrentUPosition) && (UCurrentCursorPosition+CurrentUPosition)>7)			//IPs address
					{
					if(ip_decade==0 && ((UTILITY_SETTINGS[UCurrentCursorPosition+CurrentUPosition-1]&0xFF000000)!=0xFF000000))
						{
						UTILITY_SETTINGS[UCurrentCursorPosition+CurrentUPosition-1]+=0x01000000;
						int_U_REDRAW_ONE_LINE();	
						}
					else if(ip_decade==1 && ((UTILITY_SETTINGS[UCurrentCursorPosition+CurrentUPosition-1]&0x00FF0000)!=0x00FF0000))
						{
						UTILITY_SETTINGS[UCurrentCursorPosition+CurrentUPosition-1]+=0x00010000;
						int_U_REDRAW_ONE_LINE();	
						}
					else if(ip_decade==2 && ((UTILITY_SETTINGS[UCurrentCursorPosition+CurrentUPosition-1]&0x0000FF00)!=0x0000FF00))
						{
						UTILITY_SETTINGS[UCurrentCursorPosition+CurrentUPosition-1]+=0x00000100;
						int_U_REDRAW_ONE_LINE();	
						}
					else if(ip_decade==3 && ((UTILITY_SETTINGS[UCurrentCursorPosition+CurrentUPosition-1]&0x000000FF)!=0x000000FF))
						{
						UTILITY_SETTINGS[UCurrentCursorPosition+CurrentUPosition-1]+=0x00000001;
						int_U_REDRAW_ONE_LINE();	
						}
					}			
				else if(UTILITY_SETTINGS[UCurrentCursorPosition+CurrentUPosition-1]<UTILITY_SETTINGS_MAX[UCurrentCursorPosition+CurrentUPosition-1])	
					{
					UTILITY_SETTINGS[UCurrentCursorPosition+CurrentUPosition-1]++;	
					int_U_REDRAW_ONE_LINE();	
					int_reload_parameter_realtime();					
					}					
				}				
			}		
		else if(dSHOW==EDIT_PAD_DISPLAY)
			{
			if(P_COLOR[pad_x-1]<8)  //pad is enable
				{					
				if(edit_epd_parameter==0)
					{
					NAVIGATOR(EPD_UP);
					}
				else
					{
					if(EPD_Position==1)			//waveform
						{
						if(KEY_SHIFT_pressed)			//zoom
							{
							if(wzoom>0)
								{
								wzoom--;	
								}		
							}						
						else								//offset
							{
							P_START_ADR[pad_x-1]+=(0x01<<wzoom);
							if(P_START_ADR[pad_x-1]>new_all_data)
								{
								P_START_ADR[pad_x-1] = new_all_data;		
								}
							for(uint8_t v=0;v<9;v++)
								{
								if(v<=(pad_x-1))
									{
									P_SAMPLE_OFFSET[v] = P_SAMPLE_OFFSET[pad_x] - (new_all_data - P_START_ADR[pad_x-1]);	
									}																	
								}	
							SMPL_STRT = P_SAMPLE_OFFSET[pad_x] - (new_all_data - P_START_ADR[pad_x-1]);		
							}
						draw_st_wvfm(P_START_ADR[pad_x-1], wzoom);		
						}	
					else if(EPD_Position==2)			//TYPE
						{
						if(P_TYPE[pad_x-1]==0)
							{
							P_TYPE[pad_x-1] = 1;	
							int_EPD_REDRAW_ONE_LINE();	
							int_reload_epd_realtime();
							}							
						}
					else if(EPD_Position==3)			//QUANTIZE
						{
						if(P_QUANTIZE[pad_x-1]==0)
							{
							P_QUANTIZE[pad_x-1] = 1;	
							int_EPD_REDRAW_ONE_LINE();	
							int_reload_epd_realtime();
							}				
						}					
					else if(EPD_Position==4)			//SYNC
						{
						if(P_SYNC[pad_x-1]==0)
							{
							P_SYNC[pad_x-1] = 1;	
							int_EPD_REDRAW_ONE_LINE();	
							int_reload_epd_realtime();
							}							
						}
					else if(EPD_Position==5)			//TRIGGER
						{
						if(P_TRIG[pad_x-1]==0)
							{
							P_TRIG[pad_x-1] = 1;	
							int_EPD_REDRAW_ONE_LINE();	
							int_reload_epd_realtime();
							}			
						}						
					else if(EPD_Position==6)			//TEMPO
						{
						if(KEY_SHIFT_pressed==0)			//shift not pressed	
							{
							if((P_BPM[pad_x-1]/10)<200)	
								{
								P_BPM[pad_x-1]+=10;	
								int_EPD_REDRAW_ONE_LINE();	
								int_reload_epd_realtime();		
								}							
							}
						else								//shift pressed
							{
							if((P_BPM[pad_x-1]%10)<9)	
								{
								P_BPM[pad_x-1]++;	
								int_EPD_REDRAW_ONE_LINE();	
								int_reload_epd_realtime();		
								}		
							}		
						}		
					else if(EPD_Position==7)			//GAIN
						{
						if(P_GAIN[pad_x-1]>0)
							{						
							P_GAIN[pad_x-1]--;
							int_EPD_REDRAW_ONE_LINE();	
							int_reload_epd_realtime();	
							}
						}		
					else if(EPD_Position==8)			//BARS
						{
						if(P_TYPE[pad_x-1]==1)		//sequencer
							{
							if(P_WAVEFORM[pad_x-1][64]==0)
								{
								P_WAVEFORM[pad_x-1][64] = 1;
								for(mi=16;mi<32;mi++)
									{
									P_WAVEFORM[pad_x-1][mi] = 0;	
									}
								}
							else if(P_WAVEFORM[pad_x-1][64]==1)
								{
								P_WAVEFORM[pad_x-1][64] = 3;
								for(mi=32;mi<64;mi++)
									{
									P_WAVEFORM[pad_x-1][mi] = 0;	
									}									
								}	
							int_EPD_REDRAW_ONE_LINE();	
							int_reload_epd_realtime();								
							}						
						}							
					else if(EPD_Position==9)			//COLOR
						{
						if(P_COLOR[pad_x-1]<7)
							{
							P_COLOR[pad_x-1]++;	
							int_EPD_REDRAW_ONE_LINE();	
							int_reload_epd_realtime();		
							}						
						}							
					else if(EPD_Position==10)			//SEQUENCE
						{
						if((P_WAVEFORM[pad_x-1][64]==0) && (seq_epos<15) ||
							 (P_WAVEFORM[pad_x-1][64]==1) && (seq_epos<31) ||
							 (P_WAVEFORM[pad_x-1][64]==3) && (seq_epos<63))
							{	
							seq_epos++;
							int_reload_epd_realtime();
							}		
							
						}							
					}
				}	
			}
		else if(dSHOW==BROWSER)
			{
			NAVIGATOR(BR_LIST_UP);	
			}	
		else if(dSHOW==EDIT_PRESET_DISPLAY)
			{	
			if(edit_eprd_parameter==0)
				{
				NAVIGATOR(EPRD_UP);
				}
			else
				{
				if(EPRD_Position==1)	//COLOR
					{
					if(presets_color[CURRENT_PRESET]<EPRD_MAX[EPRD_Position])
						{
						BSP_LCD_SelectLayer(0);	
						BSP_LCD_SetTextColor(LCD_COLOR_PAPER);		
						BSP_LCD_FillRect(157, 66, 100, 19);								
						presets_color[CURRENT_PRESET]++;
						int_EPRD_DRAW_ALL_LINES();			
						}
					}	
				else if(EPRD_Position==2)		//RATING
					{			
					if(presets_rating[CURRENT_PRESET]<EPRD_MAX[EPRD_Position])
						{
						BSP_LCD_SelectLayer(0);	
						BSP_LCD_SetTextColor(LCD_COLOR_PAPER);		
						BSP_LCD_FillRect(157, 91, 69, 13);			
						presets_rating[CURRENT_PRESET]++;
						int_EPRD_DRAW_ALL_LINES();			
						}
					}
				else if(EPRD_Position==3)		//ICON
					{			
					if(presets_icon[CURRENT_PRESET]<EPRD_MAX[EPRD_Position])		//ICON
						{							
						presets_icon[CURRENT_PRESET]++;
						int_EPRD_DRAW_ALL_LINES();			
						}	
					}	
				}	
			}
		else if(dSHOW==KEYBOARD)
			{	
			if((KBRD_Position%37)<36)
				{
				int_KBRD_(KBRD_UP);
				}
			}	
		else if(dSHOW==EDIT_PRST)
			{
			NAVIGATOR(EP_UP);	
			}	
		else if(dSHOW==EDIT_LIST)
			{
			NAVIGATOR(EL_UP);	
			}
		else if(dSHOW==DELDIALOG)
			{
			NAVIGATOR(DELDIALOG_UP);	
			}
		else if(dSHOW==EDIT_UTILITY)
			{
			NAVIGATOR(EU_UP);	
			}		
		else if(dSHOW==EDIT_FLLIST_DISPLAY)
			{
			if(edit_fl_parameter==0)
				{
				NAVIGATOR(EFL_UP);
				}
			else
				{
				if(FAST_LOADING[FLCurrentCursorPosition]<(TOTAL_PRESETS-1))	
					{
					FAST_LOADING[FLCurrentCursorPosition]++;
					int_FL_REDRAW_ONE_LINE();	
					}	
				else if(FAST_LOADING[FLCurrentCursorPosition]>63)
					{
					FAST_LOADING[FLCurrentCursorPosition] = 0;
					int_FL_REDRAW_ONE_LINE();		
					}					
				}
			}	
		else if(dSHOW==MOVE_PRESET)
			{
			NAVIGATOR(MPRST_UP);	
			}
		#if defined(USART_DEBUG)
//		sprintf((char*)U_TX_DATA, "%s", "Encoder UP");	
//		U_TX_DATA[10] = 13;
//		U_TX_DATA[11] = 10;	
//		HAL_UART_Transmit(&huart1, U_TX_DATA, 12, 5);
		#endif	
		enc_need_up = 0;	
		}
	else if(enc_need_down)
		{	
		if(dSHOW==PRST_LIST)
			{
			NAVIGATOR(PRST_LIST_DOWN);	
			}	
		else if(dSHOW==UTILITY)
			{
			if(edit_parameter==0)
				{
				NAVIGATOR(UTILITY_DOWN);
				}	
			else
				{					
				if((UCurrentCursorPosition+CurrentUPosition-1)==4)							//INTERNAL BPM
					{
					if(KEY_SHIFT_pressed==0)			//shift not pressed	
						{
						if((UTILITY_SETTINGS[4]/10)>60)	
							{
							UTILITY_SETTINGS[UCurrentCursorPosition+CurrentUPosition-1]-=10;	
							int_U_REDRAW_ONE_LINE();	
							int_reload_parameter_realtime();		
							}							
						}
					else								//shift pressed
						{
						if((UTILITY_SETTINGS[4]%10)>0)	
							{
							UTILITY_SETTINGS[UCurrentCursorPosition+CurrentUPosition-1]--;	
							int_U_REDRAW_ONE_LINE();	
							int_reload_parameter_realtime();		
							}		
						}	
					}	
				else if(11>(UCurrentCursorPosition+CurrentUPosition) && (UCurrentCursorPosition+CurrentUPosition)>7)			//IPs address
					{
					if(ip_decade==0 && ((UTILITY_SETTINGS[UCurrentCursorPosition+CurrentUPosition-1]&0xFF000000)!=0x00000000))
						{
						UTILITY_SETTINGS[UCurrentCursorPosition+CurrentUPosition-1]-=0x01000000;
						int_U_REDRAW_ONE_LINE();	
						}
					else if(ip_decade==1 && ((UTILITY_SETTINGS[UCurrentCursorPosition+CurrentUPosition-1]&0x00FF0000)!=0x00000000))
						{
						UTILITY_SETTINGS[UCurrentCursorPosition+CurrentUPosition-1]-=0x00010000;
						int_U_REDRAW_ONE_LINE();	
						}
					else if(ip_decade==2 && ((UTILITY_SETTINGS[UCurrentCursorPosition+CurrentUPosition-1]&0x0000FF00)!=0x00000000))
						{
						UTILITY_SETTINGS[UCurrentCursorPosition+CurrentUPosition-1]-=0x00000100;
						int_U_REDRAW_ONE_LINE();	
						}
					else if(ip_decade==3 && ((UTILITY_SETTINGS[UCurrentCursorPosition+CurrentUPosition-1]&0x000000FF)!=0x00000000))
						{
						UTILITY_SETTINGS[UCurrentCursorPosition+CurrentUPosition-1]-=0x00000001;
						int_U_REDRAW_ONE_LINE();	
						}
					}		
				else if(UTILITY_SETTINGS[UCurrentCursorPosition+CurrentUPosition-1]>0)
					{
					UTILITY_SETTINGS[UCurrentCursorPosition+CurrentUPosition-1]--;	
					int_U_REDRAW_ONE_LINE();		
					int_reload_parameter_realtime();	
					}
				}	
			}
		else if(dSHOW==EDIT_PAD_DISPLAY)
			{
			if(P_COLOR[pad_x-1]<8)  //pad is enable
				{		
				if(edit_epd_parameter==0)
					{
					NAVIGATOR(EPD_DOWN);
					}	
				else
					{
					if(EPD_Position==1)			//waveform
						{
						if(KEY_SHIFT_pressed)			//zoom
							{
							if(wzoom<9)
								{
								wzoom++;	
								}		
							}						
						else								//offset
							{
							if(P_START_ADR[pad_x-1]>(0x01<<wzoom))	
								{
								P_START_ADR[pad_x-1]-=(0x01<<wzoom);
								}
							else
								{
								P_START_ADR[pad_x-1] = 0;	
								}
							for(uint8_t v=0;v<9;v++)
								{
								if(v<=(pad_x-1))
									{
									P_SAMPLE_OFFSET[v] = P_SAMPLE_OFFSET[pad_x] - (new_all_data - P_START_ADR[pad_x-1]);	
									}																	
								}	
							SMPL_STRT = P_SAMPLE_OFFSET[pad_x] - (new_all_data - P_START_ADR[pad_x-1]);			
							}
						draw_st_wvfm(P_START_ADR[pad_x-1], wzoom);		
						}
					else if(EPD_Position==2)			//TYPE
						{
						if(P_TYPE[pad_x-1]==1)
							{
							P_TYPE[pad_x-1] = 0;	
							int_EPD_REDRAW_ONE_LINE();	
							int_reload_epd_realtime();
							}							
						}
					else if(EPD_Position==3)			//QUANTIZE
						{
						if(P_QUANTIZE[pad_x-1]==1)
							{
							P_QUANTIZE[pad_x-1] = 0;	
							int_EPD_REDRAW_ONE_LINE();	
							int_reload_epd_realtime();
							}				
						}					
					else if(EPD_Position==4)			//SYNC
						{
						if(P_SYNC[pad_x-1]==1)
							{
							P_SYNC[pad_x-1] = 0;	
							int_EPD_REDRAW_ONE_LINE();	
							int_reload_epd_realtime();
							}							
						}
					else if(EPD_Position==5)			//TRIGGER
						{
						if(P_TRIG[pad_x-1]==1)
							{
							P_TRIG[pad_x-1] = 0;	
							int_EPD_REDRAW_ONE_LINE();	
							int_reload_epd_realtime();
							}			
						}						
					else if(EPD_Position==6)			//TEMPO
						{
						if(KEY_SHIFT_pressed==0)			//shift not pressed	
							{
							if((P_BPM[pad_x-1]/10)>60)	
								{
								P_BPM[pad_x-1]-=10;	
								int_EPD_REDRAW_ONE_LINE();	
								int_reload_epd_realtime();		
								}							
							}
						else								//shift pressed
							{
							if((P_BPM[pad_x-1]%10)>0)	
								{
								P_BPM[pad_x-1]--;	
								int_EPD_REDRAW_ONE_LINE();	
								int_reload_epd_realtime();		
								}		
							}		
						}		
					else if(EPD_Position==7)			//GAIN
						{
						if(P_GAIN[pad_x-1]<255)
							{						
							P_GAIN[pad_x-1]++;
							int_EPD_REDRAW_ONE_LINE();	
							int_reload_epd_realtime();	
							}	
						}		
					else if(EPD_Position==8)			//BARS
						{
						if(P_TYPE[pad_x-1]==1)		//sequencer
							{
							if(P_WAVEFORM[pad_x-1][64]==1)
								{
								P_WAVEFORM[pad_x-1][64] = 0;	
								for(mi=16;mi<32;mi++)
									{
									P_WAVEFORM[pad_x-1][mi] = 0;	
									}	
								}
							else if(P_WAVEFORM[pad_x-1][64]==3)
								{
								P_WAVEFORM[pad_x-1][64] = 1;	
								for(mi=32;mi<64;mi++)
									{
									P_WAVEFORM[pad_x-1][mi] = 0;	
									}	
								}	
							int_EPD_REDRAW_ONE_LINE();	
							int_reload_epd_realtime();								
							}						
						}							
					else if(EPD_Position==9)			//COLOR
						{
						if(P_COLOR[pad_x-1]>0)
							{
							P_COLOR[pad_x-1]--;	
							int_EPD_REDRAW_ONE_LINE();	
							int_reload_epd_realtime();		
							}						
						}							
					else if(EPD_Position==10)			//SEQUENCE
						{
						if(seq_epos>0)
							{
							seq_epos--;
							int_reload_epd_realtime();
							}						
						}								
					}	
				}	
			}	
		else if(dSHOW==BROWSER)
			{
			NAVIGATOR(BR_LIST_DOWN);	
			}	
		else if(dSHOW==EDIT_PRESET_DISPLAY)
			{
			if(edit_eprd_parameter==0)
				{
				NAVIGATOR(EPRD_DOWN);
				}	
			else
				{
				if(EPRD_Position==1)	//COLOR
					{
					if(presets_color[CURRENT_PRESET]>0)
						{
						BSP_LCD_SelectLayer(0);	
						BSP_LCD_SetTextColor(LCD_COLOR_PAPER);		
						BSP_LCD_FillRect(157, 66, 100, 19);								
						presets_color[CURRENT_PRESET]--;
						int_EPRD_DRAW_ALL_LINES();			
						}
					}	
				else if(EPRD_Position==2)		//RATING
					{			
					if(presets_rating[CURRENT_PRESET]>0)
						{
						BSP_LCD_SelectLayer(0);	
						BSP_LCD_SetTextColor(LCD_COLOR_PAPER);		
						BSP_LCD_FillRect(157, 91, 69, 13);			
						presets_rating[CURRENT_PRESET]--;
						int_EPRD_DRAW_ALL_LINES();			
						}
					}
				else if(EPRD_Position==3)		//ICON
					{			
					if(presets_icon[CURRENT_PRESET]>0)		//ICON
						{							
						presets_icon[CURRENT_PRESET]--;
						int_EPRD_DRAW_ALL_LINES();			
						}	
					}	
				}	
			}		
		else if(dSHOW==KEYBOARD)
			{	
			if((KBRD_Position%37)>0)
				{
				int_KBRD_(KBRD_DOWN);
				}
			}		
		else if(dSHOW==EDIT_PRST)
			{
			NAVIGATOR(EP_DOWN);	
			}
		else if(dSHOW==EDIT_LIST)
			{
			NAVIGATOR(EL_DOWN);	
			}
		else if(dSHOW==DELDIALOG)
			{
			NAVIGATOR(DELDIALOG_DOWN);	
			}
		else if(dSHOW==EDIT_UTILITY)
			{
			NAVIGATOR(EU_DOWN);	
			}
		else if(dSHOW==EDIT_FLLIST_DISPLAY)
			{
			if(edit_fl_parameter==0)
				{
				NAVIGATOR(EFL_DOWN);
				}
			else
				{
				if((FAST_LOADING[FLCurrentCursorPosition]<TOTAL_PRESETS) && (FAST_LOADING[FLCurrentCursorPosition]>0))	
					{
					FAST_LOADING[FLCurrentCursorPosition]--;
					int_FL_REDRAW_ONE_LINE();		
					}
				else if(FAST_LOADING[FLCurrentCursorPosition]==0)
					{
					FAST_LOADING[FLCurrentCursorPosition] = 0xFF;	
					int_FL_REDRAW_ONE_LINE();		
					}
				}
			}
		else if(dSHOW==MOVE_PRESET)
			{
			NAVIGATOR(MPRST_DOWN);	
			}
		#if defined(USART_DEBUG)
//		sprintf((char*)U_TX_DATA, "%s", "Encoder DOWN");	
//		U_TX_DATA[12] = 13;
//		U_TX_DATA[13] = 10;	
//		HAL_UART_Transmit(&huart1, U_TX_DATA, 14, 5);
		#endif	
		enc_need_down = 0;	
		}
	}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

