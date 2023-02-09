/////////////////////////////////////////////////////////////////////////////////////////////////
// 	KEY HANDLER
//	product: DJS-500 sampler
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdint.h"

void key_handler(void);
void int_exit_edit_pad(void);  //internal function for exit edit pad
void int_draw_dialog_square(void);


//////////////////////////////////////////////////////////
//
//					KEY HANDLER
//
void key_handler(void)
	{		
	if(HAL_GPIO_ReadPin(KEY_PRESET_GPIO_Port, KEY_PRESET_Pin)==0 && KEY_PRESET_pressed==0)
		{
		if((HAL_GetTick() -	KEY_PRESET_tim)>120)				//noise button filter
			{
			KEY_PRESET_tim = HAL_GetTick();	
			if(dSHOW==HOME_DISPLAY)
				{
				SwitchInformationLayer(PRST_LIST);	
				}
			else if(dSHOW==UTILITY && edit_parameter==0)
				{	
				if(need_rw_setings_prc)
					{
					write_setings_prc();
					need_rw_setings_prc = 0;	
					}					
				SwitchInformationLayer(PRST_LIST);		
				}
			else if(dSHOW==PRST_LIST)
				{
				SwitchInformationLayer(HOME_DISPLAY);	
				}	
			}	
		KEY_PRESET_pressed = 1;	
		}
	else if(HAL_GPIO_ReadPin(KEY_PRESET_GPIO_Port, KEY_PRESET_Pin)==1 && KEY_PRESET_pressed==1)
		{
		KEY_PRESET_pressed = 0;	
		}		
	else if(HAL_GPIO_ReadPin(GPIOB, KEY_SHIFT_Pin)==0 && KEY_SHIFT_pressed==0)
		{
		if((HAL_GetTick() -	KEY_SHIFT_tim)>150)				//noise button filter
			{
			KEY_SHIFT_tim	= HAL_GetTick();	
			if(dSHOW==HOME_DISPLAY)
				{
				HAL_GPIO_WritePin(GPIOB, LED_SHIFT_Pin, GPIO_PIN_SET);	
				SwitchInformationLayer(FLLIST_DISPLAY);	
				}
			else if(dSHOW==UTILITY && edit_parameter==1)
				{
				if(UCurrentCursorPosition+CurrentUPosition==5)			//edit internal bpm			
					{
					HAL_GPIO_WritePin(GPIOB, LED_SHIFT_Pin, GPIO_PIN_SET);	
					}	
				else if(UCurrentCursorPosition+CurrentUPosition==8 || UCurrentCursorPosition+CurrentUPosition==9 || UCurrentCursorPosition+CurrentUPosition==10)		//edit IP adress
					{	
					HAL_GPIO_WritePin(GPIOB, LED_SHIFT_Pin, GPIO_PIN_SET);	
					if(ip_decade<3)
						{
						ip_decade++;	
						}					
					else
						{
						ip_decade = 0;	
						}					
					int_U_REDRAW_ONE_LINE();	
					}
				}	
			else if(dSHOW==EDIT_PAD_DISPLAY)
				{	
				if(EPD_Position==1 && edit_epd_parameter==1)		//shift for zoom
					{				
					HAL_GPIO_WritePin(GPIOB, LED_SHIFT_Pin, GPIO_PIN_SET);
					}
				}
			else if(dSHOW==KEYBOARD)
				{
				HAL_GPIO_WritePin(GPIOB, LED_SHIFT_Pin, GPIO_PIN_SET);		
				if(KBRD_Position<37)
					{
					int_KBRD_(KBRD_SH_UP);
					}
				}
			}
		KEY_SHIFT_pressed = 1;	
		}
	else if(HAL_GPIO_ReadPin(GPIOB, KEY_SHIFT_Pin)==1 && KEY_SHIFT_pressed==1)
		{
		if(dSHOW==KEYBOARD)
			{	
			if(KBRD_Position>36)
				{
				int_KBRD_(KBRD_SH_DOWN);
				}
			}
		else if(dSHOW==FLLIST_DISPLAY)
			{
			need_slide_pads = 0;
			previous_frame = 134;	
			BSP_LCD_SelectLayer(1);
			BSP_LCD_SetTextColor(0x00000000);
			BSP_LCD_FillRect(0,	0,	480, 33);
			BSP_LCD_FillRect(0,	239,	480, 33);	
			BSP_LCD_FillRect(0,	134,	480, 4);
			BSP_LCD_DrawVLine(0, 33, 206);	
			BSP_LCD_DrawVLine(1, 33, 206);
			BSP_LCD_DrawVLine(118, 33, 206);	
			BSP_LCD_DrawVLine(119, 33, 206);		
			BSP_LCD_DrawVLine(120, 33, 206);	
			BSP_LCD_DrawVLine(121, 33, 206);			
			BSP_LCD_DrawVLine(238, 33, 206);	
			BSP_LCD_DrawVLine(239, 33, 206);		
			BSP_LCD_DrawVLine(240, 33, 206);	
			BSP_LCD_DrawVLine(241, 33, 206);	
			BSP_LCD_DrawVLine(358, 33, 206);	
			BSP_LCD_DrawVLine(359, 33, 206);		
			BSP_LCD_DrawVLine(360, 33, 206);	
			BSP_LCD_DrawVLine(361, 33, 206);	
			BSP_LCD_DrawVLine(478, 33, 206);	
			BSP_LCD_DrawVLine(479, 33, 206);
			start_slide_time	= HAL_GetTick();		
			need_reslide_pads = 1;							
			}
		HAL_GPIO_WritePin(GPIOB, LED_SHIFT_Pin, GPIO_PIN_RESET);		
		KEY_SHIFT_pressed = 0;	
		}			
	else if(HAL_GPIO_ReadPin(GPIOB, KEY_EDIT_Pin)==0 && KEY_EDIT_pressed==0)
		{			
		if((HAL_GetTick() -	KEY_EDIT_tim)>180)				//noise button filter
			{
			KEY_EDIT_tim	= HAL_GetTick();	
			if(dSHOW==HOME_DISPLAY)					//call home edit display menu	
				{
				CurrentEPPosition = 0;	
				SwitchInformationLayer(EDIT_PRST);		
				}
			else if(dSHOW==PRST_LIST)				//call preset edit list menu	
				{
				CurrentELPosition = 0;	
				SwitchInformationLayer(EDIT_LIST);		
				}
			else if(dSHOW==EDIT_PRST)					//return to home display	
				{
				SwitchInformationLayer(HOME_DISPLAY);		
				}
			else if(dSHOW==EDIT_LIST)					//return to preset list
				{
				SwitchInformationLayer(PRST_LIST);
				}	
			else if(dSHOW==UTILITY)				//call edit utility list menu	
				{
				CurrentEUPosition = 0;	
				SwitchInformationLayer(EDIT_UTILITY);		
				}	
			else if(dSHOW==EDIT_UTILITY)			//return to UTILITY
				{	
				SwitchInformationLayer(UTILITY);		
				}	
			}
		KEY_EDIT_pressed = 1;	
		}
	else if(HAL_GPIO_ReadPin(GPIOB, KEY_EDIT_Pin)==1 && KEY_EDIT_pressed==1)
		{
		KEY_EDIT_pressed = 0;	
		}			
	else if(HAL_GPIO_ReadPin(GPIOF, KEY_MENU_Pin)==0 && (KEY_MENU_pressed==0 || KEY_MENU_HOLD==1))
		{
		if(dSHOW==HOME_DISPLAY || dSHOW==PRST_LIST)
			{
			if(KEY_MENU_HOLD==0)
				{
				KEY_MENU_HOLD_TIM = HAL_GetTick();			
				KEY_MENU_HOLD = 1;	
				}
			else
				{
				if((HAL_GetTick()-KEY_MENU_HOLD_TIM)>700)
					{
					edit_parameter = 0;	
					SwitchInformationLayer(UTILITY);
					KEY_MENU_HOLD = 2;		
					}						
				}				
			}	
		else if(dSHOW==UTILITY && edit_parameter==0)
			{	
			if(need_rw_setings_prc)
				{
				write_setings_prc();
				need_rw_setings_prc = 0;	
				}	
			SwitchInformationLayer(HOME_DISPLAY);
			}
		KEY_MENU_pressed = 1;	
		}
	else if(HAL_GPIO_ReadPin(GPIOF, KEY_MENU_Pin)==1 && KEY_MENU_pressed==1)
		{
		if(KEY_MENU_HOLD==2)
			{
			KEY_MENU_HOLD = 0;	
			}
		else if(KEY_MENU_HOLD==1)
			{
			if(dSHOW==HOME_DISPLAY)
				{
				//call home display menu	
				}
			else if(dSHOW==PRST_LIST)
				{
				//call home preset list menu		
				}
			KEY_MENU_HOLD = 0;		
			}			
		KEY_MENU_pressed = 0;	
		}		
	else if(HAL_GPIO_ReadPin(GPIOD, KEY_BACK_Pin)==0 && KEY_BACK_pressed==0)
		{
		if((HAL_GetTick() -	KEY_BACK_tim)>250)				//noise button filter
			{
			KEY_BACK_tim	= HAL_GetTick();
			if(dSHOW==PRST_LIST || dSHOW==EDIT_PRST)
				{
				SwitchInformationLayer(HOME_DISPLAY);	
				}
			else if(dSHOW==EDIT_PRESET_DISPLAY && edit_eprd_parameter==0)
				{	
				if(need_rw_preset_prc)
					{
					write_preset_prc();
					need_rw_preset_prc = 0;	
					}		
				SwitchInformationLayer(HOME_DISPLAY);		
				}
			else if(dSHOW==UTILITY && edit_parameter==0)
				{
				if(need_rw_setings_prc)
					{
					write_setings_prc();
					need_rw_setings_prc = 0;	
					}		
				SwitchInformationLayer(HOME_DISPLAY);		
				}
			else if(dSHOW==KEYBOARD)
				{
				int_RET_PRST_NAME();		//return new preset name
				SwitchInformationLayer(EDIT_PRESET_DISPLAY);	
				}	
			else if(dSHOW==EDIT_PAD_DISPLAY)
				{
				if(edit_epd_parameter==0)	
					{
					BSP_LCD_SelectLayer(1);	
					BSP_LCD_SetTextColor(DIALOG_BACK_COLOR);					//draw dialog square
					BSP_LCD_DrawLine(104, 79, 375, 79);	
					BSP_LCD_DrawLine(102, 80, 377, 80);
					BSP_LCD_DrawLine(100, 81, 379, 81);
					BSP_LCD_DrawLine(100, 82, 379, 82);
					BSP_LCD_DrawLine(99, 83, 380, 83);
					BSP_LCD_DrawLine(99, 84, 380, 84);
					BSP_LCD_FillRect(98, 85, 284, 56);	
					BSP_LCD_DrawLine(99, 141, 380, 141);
					BSP_LCD_DrawLine(99, 142, 380, 142);
					BSP_LCD_DrawLine(100, 143, 379, 143);
					BSP_LCD_DrawLine(100, 144, 379, 144);
					BSP_LCD_DrawLine(102, 145, 377, 145);
					BSP_LCD_DrawLine(104, 146, 375, 146);				
					BSP_LCD_SetFont(&Font15P);
					BSP_LCD_SetTextColor(LCD_COLOR_WHITE);		
					sprintf((char*)Buf, "%s", "SAVING DATA");		
					BSP_LCD_DisplayStringAt(187, 106, Buf, TRANSPARENT_MODE);	
					sai_pitch = 0;					//stop audio		
					ACTIVE_PAD = 0xFF;	
					for(mi=0;mi<8;mi++)
						{
						COLOR_SET(0, mi);	
						}
					HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);			//force turn off leds
					for(mi=0;mi<9;mi++)
						{	
						P_SAMPLE_OFFSET[mi] = 0;
						}							
					HAL_Delay(5);
					if(need_rw_pad_prc)
						{
						write_pad_prc();
						need_rw_pad_prc = 0;	
						}	
					LOAD_PRESET(CURRENT_PRESET);	
					SwitchInformationLayer(HOME_DISPLAY);
					HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);					//force rurn off pads	
					}
				else					//edit_epd_parameter==1
					{
					if(EPD_Position>0)
						{
						int_exit_edit_pad();	
						}
					}				
				}		
			else if(dSHOW==EDIT_LIST)
				{
				SwitchInformationLayer(PRST_LIST);	
				}	
			else if(dSHOW==DELDIALOG)
				{
				SwitchInformationLayer(PRST_LIST);		
				}
			else if(dSHOW==EDIT_UTILITY)			//return to UTILITY
				{	
				SwitchInformationLayer(UTILITY);		
				}	
			else if(dSHOW==BROWSER)
				{	
				if(path_opened[10]!=0)		//folder up
					{
					for(uint8_t j=127;j>0;j--)
						{
						if((path_opened[j])!=47)
							{
							path_opened[j] = 0; 	
							}
						else
							{
							path_opened[j] = 0; 	
							break;	
							}
						}	
					CurrentBRPosition = 1;	
					total_elements = 0;		
					BRCCP = 0;	
					TOTAL_TRACKS = 0;		
					SwitchInformationLayer(BROWSER);	
					}
				else
					{
					SwitchInformationLayer(EDIT_PAD_DISPLAY);	//return to EDIT PAD DISPLAY	
					}
				}
			else if(dSHOW==EDIT_FLLIST_DISPLAY)
				{
				if(need_rw_setings_prc)
					{
					write_setings_prc();
					need_rw_setings_prc = 0;	
					}						
				SwitchInformationLayer(HOME_DISPLAY);	
				}	
			else if(dSHOW==MOVE_PRESET)
				{
				END_BLINK = 1;		//end encoder blink allowed					//////////	
				if(ENCODER_LED_BLINK>6)																//
					{																										//
					if(ENCODER_LED_BLINK%2==0)													//
						{																									//	for long end blinking
						ENCODER_LED_BLINK = 2;														//
						}																									//
					else																								//
						{																									//
						ENCODER_LED_BLINK = 3;														//
						}																									//
					}																										//////////	
				SwitchInformationLayer(PRST_LIST);		
				}
			}
		KEY_BACK_pressed = 1;	
		}
	else if(HAL_GPIO_ReadPin(GPIOD, KEY_BACK_Pin)==1 && KEY_BACK_pressed==1)
		{
		KEY_BACK_pressed = 0;	
		}		
	else if(HAL_GPIO_ReadPin(KEY_SYNC_OUT_GPIO_Port, KEY_SYNC_OUT_Pin)==0 && KEY_SYNC_OUT_pressed==0)
		{
		if(SYNC_OUT_ON)
			{
			SYNC_OUT_ON = 0;	
			}
		else
			{
			SYNC_OUT_ON = 1;	
			}				
		GPIOD->BSRR = 0x00000020;				//HAL_GPIO_WritePin(LED_SYNC_OUT_GPIO_Port, LED_SYNC_OUT_Pin, GPIO_PIN_SET);
		need_redraw_syncout = 1;	
		KEY_SYNC_OUT_pressed = 1;	
		}
	else if(HAL_GPIO_ReadPin(KEY_SYNC_OUT_GPIO_Port, KEY_SYNC_OUT_Pin)==1 && KEY_SYNC_OUT_pressed==1)
		{
		KEY_SYNC_OUT_pressed = 0;	
		}
	else if(HAL_GPIO_ReadPin(GPIOD, KEY_EFFECT_Pin)==0 && KEY_EFFECT_pressed==0)
		{
		if((HAL_GetTick() -	KEY_EFFECT_tim)>80)				//noise button filter
			{
			KEY_EFFECT_tim = HAL_GetTick();
			if(EFFECT_ON)
				{
				EFFECT_ON = 0;	
				HAL_GPIO_WritePin(GPIOA, LED_EFFECT_Pin, GPIO_PIN_SET);	
				}
			else
				{
				EFFECT_ON = 1;
				HAL_GPIO_WritePin(GPIOA, LED_EFFECT_Pin, GPIO_PIN_RESET);		
				}
			need_redraw_effect = 1;	
			}
		KEY_EFFECT_pressed = 1;	
		}
	else if(HAL_GPIO_ReadPin(GPIOD, KEY_EFFECT_Pin)==1 && KEY_EFFECT_pressed==1)
		{
		KEY_EFFECT_pressed = 0;	
		}	
	else if(HAL_GPIO_ReadPin(GPIOF, KEY_ENC_Pin)==0 && KEY_ENC_pressed==0)
		{
		if((HAL_GetTick() -	KEY_ENC_tim)>220)				//noise button filter
			{
			KEY_ENC_tim	= HAL_GetTick();
			if(dSHOW==PRST_LIST)															//LOAD PRESET
				{
				sai_pitch = 0;					//stop audio	
				ACTIVE_PAD = 0xFF;
				for(mi=0;mi<9;mi++)
					{	
					P_SAMPLE_OFFSET[mi] = 0;
					}				
				ENCODER_LED_BLINK = 0;	//start encoder blink
				END_BLINK = 0;					//end encoder blink disable
				for(mi=0;mi<8;mi++)
					{			
					COLOR_SET(0, mi);	
					}	
				HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);
				load_status = LOAD_PRESET(PRSTCCP+CurrentPRSTPosition-1);			
				if(load_status!=0)					//error
					{	
					CURRENT_PRESET = 0xFF;					//current preset	
					}
				else
					{
					CURRENT_PRESET = PRSTCCP+CurrentPRSTPosition-1;		
					}			
				dSHOW = 0xFF;	
				SwitchInformationLayer(HOME_DISPLAY);		
				if(load_status!=0)					//error
					{
					BSP_LCD_SetTextColor(LCD_COLOR_RED);	
					PREPARE_ERR_MSG(load_status);
					BSP_LCD_DisplayStringAt(180, 52, Buf, LEFT_MODE);	
					}
					
				END_BLINK = 1;		//end encoder blink allowed					//////////	
				if(ENCODER_LED_BLINK>6)																//
					{																										//
					if(ENCODER_LED_BLINK%2==0)													//
						{																									//	for long end blinking
						ENCODER_LED_BLINK = 2;														//
						}																									//
					else																								//
						{																									//
						ENCODER_LED_BLINK = 3;														//
						}																									//
					}																										//////////
				HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);
				}
			else if(dSHOW==UTILITY)
				{
				if(edit_parameter==0 && ((UCurrentCursorPosition + CurrentUPosition)<11))
					{
					need_rw_setings_prc = 1;
					ip_decade = 0;	
					edit_parameter = 1;
					if(11>(UCurrentCursorPosition+CurrentUPosition) && (UCurrentCursorPosition+CurrentUPosition)>7)			//IPs address
						{
						int_U_REDRAW_ONE_LINE();	
						}				
					SwitchInformationLayer(UTILITY);		
					}
				else if(edit_parameter)
					{
					edit_parameter = 0;
					if(11>(UCurrentCursorPosition+CurrentUPosition) && (UCurrentCursorPosition+CurrentUPosition)>7)			//IPs address
						{
						int_U_REDRAW_ONE_LINE();	
						}		
					else if(UCurrentCursorPosition+CurrentUPosition==4)					//SYNC MODE
						{
						int_sync_mode_upd();	
						}
					else if(UCurrentCursorPosition+CurrentUPosition==5)					//INTERNAL BPM
						{
						if(UTILITY_SETTINGS[3]==0)		//internal bpm clock
							{
							int_sync_mode_upd();
							}								
						}		
					SwitchInformationLayer(UTILITY);
					}
				}
			else if(dSHOW==EDIT_PRESET_DISPLAY)
				{		
				if(edit_eprd_parameter==0)
					{
					need_rw_preset_prc = 1;	
					if(EPRD_Position>0)
						{
						edit_eprd_parameter = 1;	
						int_EPRD_REDRAW_ONE_LINE();
						SwitchInformationLayer(EDIT_PRESET_DISPLAY);	
						}
					else
						{
						SwitchInformationLayer(KEYBOARD);	
						}						
					}
				else if(edit_eprd_parameter)
					{
					edit_eprd_parameter = 0;
					if(EPRD_Position>0)
						{
						int_EPRD_REDRAW_ONE_LINE();
						SwitchInformationLayer(EDIT_PRESET_DISPLAY);	
						}
					}
				}
			else if(dSHOW==KEYBOARD)
				{
				int_TYPING();	
				}			
			else if(dSHOW==EDIT_PAD_DISPLAY)
				{
				if(edit_epd_parameter==0)
					{	
					if(EPD_Position==0)
						{
						need_rw_pad_prc = 1;	
						CurrentBRPosition = 1;	
						total_elements = 0;		
						BRCCP = 0;	
						TOTAL_TRACKS = 0;	
						sprintf((char*)path_opened, "%s", sample_path);		
						SwitchInformationLayer(BROWSER);
						}
					else if(EPD_Position==8 && P_TYPE[pad_x-1]==0)		//bars & P_TYPE==sample 
						{
						//blocked edit entering	
						}
					else if(EPD_Position==3 && P_TYPE[pad_x-1]==1)		//quantize & P_TYPE==sequencer 
						{
						//blocked edit entering			//quantize ON only
						}
					else if(EPD_Position==3 && P_TYPE[pad_x-1]==0 && P_TRIG[pad_x-1]==1)		//quantize & P_TYPE==sample & loop 
						{
						//blocked edit entering			//quantize ON only
						}
					else
						{
						if(EPD_Position==2 || EPD_Position==3 || EPD_Position==4 || EPD_Position==5)
							{
							sai_pitch = 0;					//stop audio	
							ACTIVE_PAD = 0xFF;								
							}							
						need_rw_pad_prc = 1;	
						edit_epd_parameter = 1;		
						previous_pad_type = P_TYPE[pad_x-1];	
						SwitchInformationLayer(EDIT_PAD_DISPLAY);		
						int_EPD_REDRAW_ONE_LINE();	
						}		
					}
				else if(edit_epd_parameter==1)
					{
					if(EPD_Position<10)
						{
						if(EPD_Position==2 || EPD_Position==3 || EPD_Position==4 || EPD_Position==5)
							{
							sai_pitch = 0;					//stop audio	
							ACTIVE_PAD = 0xFF;								
							}	
						int_exit_edit_pad();	
						}
					else if(EPD_Position==10)					//edit sequence
						{
						if(P_WAVEFORM[pad_x-1][seq_epos]==1)
							{
							P_WAVEFORM[pad_x-1][seq_epos] = 0;	
							}
						else
							{
							P_WAVEFORM[pad_x-1][seq_epos] = 1;	
							}
						_int_draw_pad(1);		
						}		
					}							
				}			
			else if(dSHOW==BROWSER)
				{	
				if(TRACKLIST[BRCCP+CurrentBRPosition-1][65]==1 )	//folder
					{
					sprintf((char*)path_opened, "%s", TRACKLIST[BRCCP+CurrentBRPosition-1]);
					CurrentBRPosition = 1;	
					total_elements = 0;		
					BRCCP = 0;	
					TOTAL_TRACKS = 0;		
					SwitchInformationLayer(BROWSER);	
					}
				else		//track
					{
					sprintf((char*)&path_opened[strlen(path_opened)], "%s", "/");		
					sprintf((char*)&path_opened[strlen(path_opened)], "%s", TRACKLIST[BRCCP+CurrentBRPosition-1]);
					sprintf((char*)P_SAMPLE_NAME[pad_x-1], "%s", &path_opened[11]);			//11
					if(P_COLOR[pad_x-1]<8)  //pad is enable
						{
						if(P_TYPE[pad_x-1]==0)		//type == sample	
							{
							need_analyzing_wfm = 1;	
							P_TRIG[pad_x-1] = 0;	
							}
						}
					else
						{
						P_COLOR[pad_x-1] = 1;		//create this pad is enable						
						P_TYPE[pad_x-1] = 0;		//sample
						P_TRIG[pad_x-1] = 0;	
						need_analyzing_wfm = 1;		
						}
					P_BPM[pad_x-1] = 1200;		//reset BPM	
					P_GAIN[pad_x-1] = 30;		//reset gain
					wzoom = 6;	
					P_START_ADR[pad_x-1] = 0;	
					P_QUANTIZE[pad_x-1] = 0;
					P_SYNC[pad_x-1] = 0;
					write_pad_prc();			//safe to sd card!	
					SwitchInformationLayer(EDIT_PAD_DISPLAY);		
					}					
				}
			else if(dSHOW==EDIT_PRST)
				{
				if(CurrentEPPosition==0)
					{
					edit_fl_parameter = 0;			
					FLCurrentCursorPosition = 0;	
					SwitchInformationLayer(EDIT_FLLIST_DISPLAY);		
					}
				else if(CurrentEPPosition==1)
					{
					if(CURRENT_PRESET<64)		//if preset now loading
						{	
						EPRD_Position = 0;			
						edit_eprd_parameter = 0;
						SwitchInformationLayer(EDIT_PRESET_DISPLAY);
						}
					}
				else if(CurrentEPPosition==10)		//return to home display
					{
					SwitchInformationLayer(HOME_DISPLAY);		
					}
				else if((CurrentEPPosition>1) && (CurrentEPPosition<10))				
					{
					if(CURRENT_PRESET<64)		//if preset now loading
						{	
						EPD_Position = 0;
						edit_epd_parameter = 0;			
						SwitchInformationLayer(EDIT_PAD_DISPLAY);
						}
					}				
				}	
			else if(dSHOW==EDIT_LIST)
				{
				if(CurrentELPosition==0)		//enter to create new list
					{
					if(TOTAL_PRESETS<64)
						{						
						sai_pitch = 0;		//stop audio	
						ACTIVE_PAD = 0xFF;	
						mi = write_new_dupl_prc(0); 
						if(mi==FR_OK)	
							{
							LOAD_PRESET_LIST();		
							if(TOTAL_PRESETS>12)
								{
								CurrentPRSTPosition = TOTAL_PRESETS-12;	
								PRSTCCP = 12;		
								}		
							}
						else
							{
							SwitchInformationLayer(PRST_LIST);	
							BSP_LCD_SelectLayer(1);				//error msg
							int_draw_dialog_square();
							BSP_LCD_SetFont(&Font15P);
							BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
							sprintf((char*)Buf, "%s%1lu", "Error ", mi);		
							BSP_LCD_DisplayStringAt(199, 106, Buf, TRANSPARENT_MODE);	
							HAL_Delay(3500);	
							BSP_LCD_SetTextColor(0x00000000);	
							BSP_LCD_FillRect(98, 79, 284, 68);								
							}
						}
					else
						{
						SwitchInformationLayer(PRST_LIST);	
						BSP_LCD_SelectLayer(1);			//message about full presets memory	
						int_draw_dialog_square();
						BSP_LCD_SetFont(&Font15P);
						BSP_LCD_SetTextColor(LCD_COLOR_WHITE);		
						sprintf((char*)Buf, "%s", "Preset list is full.");		
						BSP_LCD_DisplayStringAt(172, 106, Buf, TRANSPARENT_MODE);		
						HAL_Delay(2500);
						int_draw_dialog_square();
						BSP_LCD_SetFont(&Font15P);
						BSP_LCD_SetTextColor(LCD_COLOR_WHITE);		
						sprintf((char*)Buf, "%s", "Delete one or more presets.");		
						BSP_LCD_DisplayStringAt(132, 106, Buf, TRANSPARENT_MODE);		
						HAL_Delay(3500);
						BSP_LCD_SetTextColor(0x00000000);	
						BSP_LCD_FillRect(98, 79, 284, 68);	
						}
					SwitchInformationLayer(PRST_LIST);
					}
				else if(CurrentELPosition==1)		//enter to create duplicate
					{	
					if(TOTAL_PRESETS<64)
						{		
						sai_pitch = 0;		//stop audio	
						ACTIVE_PAD = 0xFF;		
						mi = write_new_dupl_prc(1);	
						if(mi==FR_OK)	
							{
							LOAD_PRESET_LIST();
							if(TOTAL_PRESETS>12)
								{
								CurrentPRSTPosition = TOTAL_PRESETS-12;	
								PRSTCCP = 12;	
								}	
							}
						else
							{
							SwitchInformationLayer(PRST_LIST);	
							BSP_LCD_SelectLayer(1);				//error msg
							int_draw_dialog_square();
							BSP_LCD_SetFont(&Font15P);
							BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
							sprintf((char*)Buf, "%s%1lu", "Error ", mi);		
							BSP_LCD_DisplayStringAt(199, 106, Buf, TRANSPARENT_MODE);	
							HAL_Delay(3500);	
							BSP_LCD_SetTextColor(0x00000000);	
							BSP_LCD_FillRect(98, 79, 284, 68);
							}
						}
					else
						{
						SwitchInformationLayer(PRST_LIST);	
						BSP_LCD_SelectLayer(1);			//message about full presets memory	
						int_draw_dialog_square();
						BSP_LCD_SetFont(&Font15P);
						BSP_LCD_SetTextColor(LCD_COLOR_WHITE);		
						sprintf((char*)Buf, "%s", "Preset list is full.");		
						BSP_LCD_DisplayStringAt(172, 106, Buf, TRANSPARENT_MODE);		
						HAL_Delay(2500);
						int_draw_dialog_square();
						BSP_LCD_SetFont(&Font15P);
						BSP_LCD_SetTextColor(LCD_COLOR_WHITE);		
						sprintf((char*)Buf, "%s", "Delete one or more presets.");		
						BSP_LCD_DisplayStringAt(132, 106, Buf, TRANSPARENT_MODE);		
						HAL_Delay(3500);	
						BSP_LCD_SetTextColor(0x00000000);	
						BSP_LCD_FillRect(98, 79, 284, 68);	
						}
					SwitchInformationLayer(PRST_LIST);
					}
				else if(CurrentELPosition==2)				//enter to move list
					{
					ENCODER_LED_BLINK = 0;	//start encoder blink
					END_BLINK = 0;					//end encoder blink disable
					SwitchInformationLayer(PRST_LIST);	
					SwitchInformationLayer(MOVE_PRESET);
					}	
				else if(CurrentELPosition==3)					//enter to DELETE dialog
					{	
					SwitchInformationLayer(PRST_LIST);
					if(TOTAL_PRESETS>1)
						{
						CurrentDDPosition = 0;	
						SwitchInformationLayer(DELDIALOG);
						}								
					}
				else if(CurrentELPosition==4)		//return to preset list display
					{
					SwitchInformationLayer(PRST_LIST);		
					}
				}		
			else if(dSHOW==EDIT_UTILITY)
				{
				if(CurrentEUPosition==0)			//set to default process
					{
					edit_parameter = 0;
					UTILITY_SETTINGS[0] = 0;   		//AUTO LOAD
					UTILITY_SETTINGS[1] = 0;   		//LOAD LOCK 
					UTILITY_SETTINGS[2] = 0;   		//EFFECT TYPE	
					UTILITY_SETTINGS[3] = 1;   		//SYNC MODE
					UTILITY_SETTINGS[4] = 1200;  	//INTERNAL BPM
					UTILITY_SETTINGS[5] = 0;   		//SYNC OUT TYPE
					UTILITY_SETTINGS[6] = 3;   		//LCD BRIGHTNESS	
					UTILITY_SETTINGS[7] = 0xA9FE958C;   		//CDJ 1 IP ADDR.	169, 254, 149, 140
					UTILITY_SETTINGS[8] = 0xA9FE95A0;   		//CDJ 2 IP ADDR.	169, 254, 149, 160
					UTILITY_SETTINGS[9] = 0xA9FE28F1;				//SAMPLER IP ADDR.	
					TIM14->CCR1 = 48+(52*UTILITY_SETTINGS[6]);	
					SwitchInformationLayer(UTILITY);		
					}
				else if(CurrentEUPosition==1)
					{
					HAL_Delay(50);	
					BSP_LCD_SelectLayer(0);	
					BSP_LCD_SetTextColor(LCD_COLOR_BLACK);	
					BSP_LCD_FillRect(0, 0, 480, 272);	
					BSP_LCD_SelectLayer(1);
					BSP_LCD_Clear(0x00000000);
					HAL_Delay(400);	
					BSP_LCD_SelectLayer(0);	
					int_draw_dialog_square();
					BSP_LCD_SetFont(&Font15P);
					BSP_LCD_SetTextColor(LCD_COLOR_WHITE);		
					sprintf((char*)Buf, "%s", "SYSTEM REBOOT");		
					BSP_LCD_DisplayStringAt(173, 106, Buf, TRANSPARENT_MODE);	
					HAL_Delay(2500);
					for(mi=0;mi<8;mi++)
						{
						COLOR_SET(0xFF000000, mi);	
						}						
					HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);					//force rurn off pads
					TIM14->CCR1 = 0;								//PWM BLACKLIGHT
					HAL_GPIO_WritePin(GPIOB, LED_ENC_Pin|LED_SHIFT_Pin, GPIO_PIN_RESET);										//////////////////////////////
					HAL_GPIO_WritePin(GPIOA, LED_PRESET_Pin|LED_EFFECT_Pin, GPIO_PIN_RESET);								//
					HAL_GPIO_WritePin(LED_SYNC_OUT_GPIO_Port, LED_SYNC_OUT_Pin, GPIO_PIN_RESET);						//			turn off leds
					HAL_GPIO_WritePin(GPIOI, LED_EDIT_Pin, GPIO_PIN_RESET);																	//
					HAL_GPIO_WritePin(LED_MENU_GPIO_Port, LED_MENU_Pin, GPIO_PIN_RESET);										//////////////////////////////
					BSP_LCD_SetTextColor(LCD_COLOR_BLACK);	
					BSP_LCD_FillRect(0, 0, 480, 272);	
					f_close(&file);	
					HAL_Delay(40);	
					NVIC_SystemReset();							//reset system
					}
				else if(CurrentEUPosition==2)
					{
					HAL_Delay(50);	
					BSP_LCD_SelectLayer(0);	
					BSP_LCD_SetTextColor(LCD_COLOR_BLACK);	
					BSP_LCD_FillRect(0, 0, 480, 272);	
					BSP_LCD_SelectLayer(1);
					BSP_LCD_Clear(0x00000000);
					HAL_Delay(400);	
					BSP_LCD_SelectLayer(0);	
					int_draw_dialog_square();
					BSP_LCD_SetFont(&Font15P);
					BSP_LCD_SetTextColor(LCD_COLOR_WHITE);		
					sprintf((char*)Buf, "%s", "TURN OFF");		
					BSP_LCD_DisplayStringAt(199, 106, Buf, TRANSPARENT_MODE);	
					HAL_Delay(2500);
					for(mi=0;mi<8;mi++)
						{
						COLOR_SET(0xFF000000, mi);	
						}					
					HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);					//force rurn off pads
					TIM14->CCR1 = 0;								//PWM BLACKLIGHT
					BSP_LCD_SetTextColor(LCD_COLOR_BLACK);	
					BSP_LCD_FillRect(0, 0, 480, 272);	
					f_close(&file);	
					HAL_TIM_Base_Stop_IT(&htim5);									//ENCODER STOP
					HAL_TIM_PWM_Stop(&htim14, TIM_CHANNEL_1);			//PWM BLACKLIGHT STOP
					HAL_TIM_Base_Stop_IT(&htim2);									//STOP timer
					HAL_GPIO_WritePin(GPIOB, LED_ENC_Pin|LED_SHIFT_Pin, GPIO_PIN_RESET);										//////////////////////////////
					HAL_GPIO_WritePin(GPIOA, LED_PRESET_Pin|LED_EFFECT_Pin, GPIO_PIN_RESET);								//
					HAL_GPIO_WritePin(LED_SYNC_OUT_GPIO_Port, LED_SYNC_OUT_Pin, GPIO_PIN_RESET);						//			turn off leds
					HAL_GPIO_WritePin(GPIOI, LED_EDIT_Pin, GPIO_PIN_RESET);																	//
					HAL_GPIO_WritePin(LED_MENU_GPIO_Port, LED_MENU_Pin, GPIO_PIN_RESET);										//////////////////////////////
					HAL_Delay(500);	
					while(1)		//turn off
						{
						}
					}	
				else if(CurrentEUPosition==3)		//return UTILITY (cancel)
					{
					SwitchInformationLayer(UTILITY);		
					}
				}			
			else if(dSHOW==DELDIALOG)
				{
				if(CurrentDDPosition==0)
					{
					SwitchInformationLayer(PRST_LIST);			//cancel delete prc
					}
				else if(CurrentDDPosition==1)
					{
					sai_pitch = 0;		//stop audio	
					ACTIVE_PAD = 0xFF;	
					for(mi=0;mi<9;mi++)
						{	
						P_SAMPLE_OFFSET[mi] = 0;
						}
					SwitchInformationLayer(PRST_LIST);	
					BSP_LCD_SelectLayer(1);				//error msg
					int_draw_dialog_square();
					BSP_LCD_SetFont(&Font15P);
					BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
					sprintf((char*)Buf, "%s", "Please wait...");	
					BSP_LCD_DisplayStringAt(190, 106, Buf, TRANSPARENT_MODE);		
					mi = delete_prc(CurrentPRSTPosition+PRSTCCP-1);	
					if(mi==FR_OK)	
						{
						if(LOAD_PRESET_LIST()==0)	
							{
							if(CURRENT_PRESET==(CurrentPRSTPosition+PRSTCCP-1))
								{
								CURRENT_PRESET = 0;	
								}								
							else if(CURRENT_PRESET>(CurrentPRSTPosition+PRSTCCP-1))	
								{
								CURRENT_PRESET = CURRENT_PRESET-1;	
								}
							load_status = LOAD_PRESET(CURRENT_PRESET);
							if(load_status==0)	
								{
								for(mi=0;mi<8;mi++)
									{	
									if(P_COLOR[mi]<8)
										{									
										COLOR_SET(PADS_L_COLOR[P_COLOR[mi]], mi);
										}
									else
										{
										COLOR_SET(EMPTY_PAD, mi);	
										}
									}											
								}
							else		//error
								{
								CURRENT_PRESET = 0xFF;
								for(mi=0;mi<8;mi++)
									{	
									COLOR_SET(EMPTY_PAD, mi);	
									}	
								BSP_LCD_SelectLayer(1);				//error msg
								int_draw_dialog_square();
								BSP_LCD_SetFont(&Font15P);
								BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
								PREPARE_ERR_MSG(load_status);	
								BSP_LCD_DisplayStringAt(199, 106, Buf, TRANSPARENT_MODE);	
								HAL_Delay(3500);	
								BSP_LCD_SetTextColor(0x00000000);	
								BSP_LCD_FillRect(98, 79, 284, 68);		
								}
							}
						else		//error
							{
							CURRENT_PRESET = 0xFF;
							for(mi=0;mi<8;mi++)
								{	
								COLOR_SET(EMPTY_PAD, mi);	
								}
							BSP_LCD_SelectLayer(1);				//error msg
							int_draw_dialog_square();
							BSP_LCD_SetFont(&Font15P);
							BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
							sprintf((char*)Buf, "%s", "Error preset list");		
							BSP_LCD_DisplayStringAt(180, 106, Buf, TRANSPARENT_MODE);	
							HAL_Delay(3500);	
							BSP_LCD_SetTextColor(0x00000000);	
							BSP_LCD_FillRect(98, 79, 284, 68);		
							}
						need_load_rgb = 1;	
						if(CurrentPRSTPosition>1)
							{
							CurrentPRSTPosition--;	
							}							
						else
							{
							if(PRSTCCP>0)
								{
								PRSTCCP--;	
								}								
							}	
						dSHOW = 0xFF;	
						}
					else
						{
						SwitchInformationLayer(PRST_LIST);	
						BSP_LCD_SelectLayer(1);				//error msg
						int_draw_dialog_square();
						BSP_LCD_SetFont(&Font15P);
						BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
						sprintf((char*)Buf, "%s%1lu", "Error ", mi);		
						BSP_LCD_DisplayStringAt(199, 106, Buf, TRANSPARENT_MODE);	
						HAL_Delay(3500);	
						BSP_LCD_SetTextColor(0x00000000);	
						BSP_LCD_FillRect(98, 79, 284, 68);	
						}
					SwitchInformationLayer(PRST_LIST);
					}	
				}
			else if(dSHOW==EDIT_FLLIST_DISPLAY)
				{		
				if(edit_fl_parameter==0)
					{
					need_rw_setings_prc = 1;
					edit_fl_parameter = 1;	
					}
				else
					{
					edit_fl_parameter = 0;
					}	
				SwitchInformationLayer(EDIT_FLLIST_DISPLAY);
				}	

			else if(dSHOW==MOVE_PRESET)
				{
				PRSTCCP = MPRSTCCP;
				CurrentPRSTPosition = CurrentMPRSTPosition;
				if(moveable_preset!=(MPRSTCCP+CurrentMPRSTPosition-1))
					{
					sai_pitch = 0;		//stop audio	
					ACTIVE_PAD = 0xFF;	
					for(mi=0;mi<9;mi++)
						{	
						P_SAMPLE_OFFSET[mi] = 0;
						}		
					BSP_LCD_SelectLayer(1);				//error msg
					int_draw_dialog_square();
					BSP_LCD_SetFont(&Font15P);
					BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
					sprintf((char*)Buf, "%s", "Please wait...");	
					BSP_LCD_DisplayStringAt(190, 106, Buf, TRANSPARENT_MODE);							
					mi = move_preser_prc(moveable_preset, MPRSTCCP+CurrentMPRSTPosition-1);		
					if(mi==FR_OK)	
						{
						if(LOAD_PRESET_LIST()==0)	
							{
							if(CURRENT_PRESET==moveable_preset)
								{	
								CURRENT_PRESET = (MPRSTCCP+CurrentMPRSTPosition-1);	
								}
							else 
								{
								if((MPRSTCCP+CurrentMPRSTPosition-1)>moveable_preset)		//shift down
									{
									if((CURRENT_PRESET>moveable_preset) && (CURRENT_PRESET<=(MPRSTCCP+CurrentMPRSTPosition-1)))
										{
										CURRENT_PRESET-=1;	
										}			
									}
								else				//shift up
									{
									if((CURRENT_PRESET>=(MPRSTCCP+CurrentMPRSTPosition-1)) && (CURRENT_PRESET<=moveable_preset))
										{
										CURRENT_PRESET+=1;	
										}
									}
								}						
							load_status = LOAD_PRESET(CURRENT_PRESET);
							if(load_status==0)	
								{
								for(mi=0;mi<8;mi++)
									{	
									if(P_COLOR[mi]<8)
										{									
										COLOR_SET(PADS_L_COLOR[P_COLOR[mi]], mi);
										}
									else
										{
										COLOR_SET(EMPTY_PAD, mi);	
										}
									}											
								}
							else		//error
								{
								CURRENT_PRESET = 0xFF;
								for(mi=0;mi<8;mi++)
									{	
									COLOR_SET(EMPTY_PAD, mi);	
									}	
								BSP_LCD_SelectLayer(1);				//error msg
								int_draw_dialog_square();
								BSP_LCD_SetFont(&Font15P);
								BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
								PREPARE_ERR_MSG(load_status);		
								BSP_LCD_DisplayStringAt(199, 106, Buf, TRANSPARENT_MODE);	
								HAL_Delay(3500);	
								BSP_LCD_SetTextColor(0x00000000);	
								BSP_LCD_FillRect(98, 79, 284, 68);		
								}
							}
						else		//error
							{
							CURRENT_PRESET = 0xFF;
							for(mi=0;mi<8;mi++)
								{	
								COLOR_SET(EMPTY_PAD, mi);	
								}
							BSP_LCD_SelectLayer(1);				//error msg
							int_draw_dialog_square();
							BSP_LCD_SetFont(&Font15P);
							BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
							PREPARE_ERR_MSG(load_status);	
							BSP_LCD_DisplayStringAt(180, 106, Buf, TRANSPARENT_MODE);	
							HAL_Delay(3500);	
							BSP_LCD_SetTextColor(0x00000000);	
							BSP_LCD_FillRect(98, 79, 284, 68);		
							}
						need_load_rgb = 1;	
						dSHOW = 0xFF;	
						}
					else
						{
						SwitchInformationLayer(PRST_LIST);	
						BSP_LCD_SelectLayer(1);				//error msg
						int_draw_dialog_square();
						BSP_LCD_SetFont(&Font15P);
						BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
						sprintf((char*)Buf, "%s%1lu", "Error ", mi);		
						BSP_LCD_DisplayStringAt(199, 106, Buf, TRANSPARENT_MODE);	
						HAL_Delay(3500);	
						BSP_LCD_SetTextColor(0x00000000);	
						BSP_LCD_FillRect(98, 79, 284, 68);	
						}
					}					
				END_BLINK = 1;		//end encoder blink allowed					//////////	
				if(ENCODER_LED_BLINK>6)																//
					{																										//
					if(ENCODER_LED_BLINK%2==0)													//
						{																									//	for long end blinking
						ENCODER_LED_BLINK = 2;														//
						}																									//
					else																								//
						{																									//
						ENCODER_LED_BLINK = 3;														//
						}																									//
					}																										//////////						
				SwitchInformationLayer(PRST_LIST);	
				}
				
			}
		KEY_ENC_pressed = 1;	
		}
	else if(HAL_GPIO_ReadPin(GPIOF, KEY_ENC_Pin)==1 && KEY_ENC_pressed==1)
		{
		KEY_ENC_pressed = 0;	
		}		
	}

	
//////////////////////////////////////////////////////////
//
//		internal function for exit edit pad
//		
void int_exit_edit_pad(void)
	{
	edit_epd_parameter = 0;		
	int_EPD_REDRAW_ONE_LINE();	
	if(P_TYPE[pad_x-1]!=previous_pad_type)		//sample type has been changed
		{
		if(EPD_Position==2 && P_TYPE[pad_x-1]==0)		//edit type == sample	
			{
			BSP_LCD_SelectLayer(1);				//error msg
			int_draw_dialog_square();
			BSP_LCD_SetFont(&Font15P);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			sprintf((char*)Buf, "%s", "WAVEFORM ANALYSIS");	
			BSP_LCD_DisplayStringAt(152, 106, Buf, TRANSPARENT_MODE);
			anlz_time = HAL_GetTick(); 
			sai_pitch = 0;		//stop audio	
			ACTIVE_PAD = 0xFF;		
			WFMCREATE();		//analyzing waveform
			if((HAL_GetTick()-anlz_time)<250)	
				{
				HAL_Delay(800);
				}
			else if((HAL_GetTick()-anlz_time)<550)	
				{
				HAL_Delay(400);
				}
			else if((HAL_GetTick()-anlz_time)<750)	
				{
				HAL_Delay(200);
				}
			sai_pitch = 0;		//stop audio	
			ACTIVE_PAD = 0xFF;		
			BSP_LCD_SetTextColor(0x00000000);					//clear dialog square
			BSP_LCD_DrawLine(104, 79, 375, 79);	
			BSP_LCD_DrawLine(102, 80, 377, 80);
			BSP_LCD_DrawLine(100, 81, 379, 81);
			BSP_LCD_DrawLine(100, 82, 379, 82);
			BSP_LCD_DrawLine(99, 83, 380, 83);
			BSP_LCD_DrawLine(99, 84, 380, 84);
			BSP_LCD_FillRect(98, 85, 284, 56);	
			BSP_LCD_DrawLine(99, 141, 380, 141);
			BSP_LCD_DrawLine(99, 142, 380, 142);
			BSP_LCD_DrawLine(100, 143, 379, 143);
			BSP_LCD_DrawLine(100, 144, 379, 144);
			BSP_LCD_DrawLine(102, 145, 377, 145);
			BSP_LCD_DrawLine(104, 146, 375, 146);	
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);	
			BSP_LCD_DrawLine(239, 46, 239, 148);			//big waveform center line	
			P_TRIG[pad_x-1] = 0;		//one shot
			P_QUANTIZE[pad_x-1] = 0;	//quantize off	
			}
		else if(EPD_Position==2 && P_TYPE[pad_x-1]==1)		//edit type == sequence	
			{	
			CLEAR_SEQUNCE_MEMORY();
			P_TRIG[pad_x-1] = 1;		//loop	
			P_QUANTIZE[pad_x-1] = 1;	//quantize on	
			}
		}
	if(EPD_Position==5 && P_TRIG[pad_x-1]==1)		//set trigger==loop	
		{		
		P_QUANTIZE[pad_x-1] = 1;	//quantize on
		}		
	SwitchInformationLayer(EDIT_PAD_DISPLAY);	
	return;
	}


	
//////////////////////////////////////////////////////////
//
//		draw dialog square
//
void int_draw_dialog_square(void)
	{
	BSP_LCD_SetTextColor(DIALOG_BACK_COLOR);					//draw dialog square
	BSP_LCD_DrawLine(104, 79, 375, 79);	
	BSP_LCD_DrawLine(102, 80, 377, 80);
	BSP_LCD_DrawLine(100, 81, 379, 81);
	BSP_LCD_DrawLine(100, 82, 379, 82);
	BSP_LCD_DrawLine(99, 83, 380, 83);
	BSP_LCD_DrawLine(99, 84, 380, 84);
	BSP_LCD_FillRect(98, 85, 284, 56);	
	BSP_LCD_DrawLine(99, 141, 380, 141);
	BSP_LCD_DrawLine(99, 142, 380, 142);
	BSP_LCD_DrawLine(100, 143, 379, 143);
	BSP_LCD_DrawLine(100, 144, 379, 144);
	BSP_LCD_DrawLine(102, 145, 377, 145);
	BSP_LCD_DrawLine(104, 146, 375, 146);	
	return;	
	}
	
	
	
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

