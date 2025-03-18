/////////////////////////////////////////////////////////////////////////////////////////////////
// 	timer handler
//	product: DJS-500 sampler
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdint.h"

	
///////////////////////////////////////////////
//TIMER	1000Hz
//	
//
void TIM2_IRQHandler(void)	
	{			
	//////////////////////////////////////////////////////////////////////
	//
	//			internal bpm generator
	//	
	if(UTILITY_SETTINGS[3]==0)		//internal bpm clock
		{	
		if(IBEAT_TIM<599999)
			{
			IBEAT_TIM++;	
			}
		else
			{
			IUDP_MPHASE_CNT = 0;	
			THR_TIME = 0;		
			IBEAT_TIM = 0;	
			}
		if(IBEAT_TIM>THR_TIME)
			{
			IUDP_MPHASE_CNT++;
			time_tmp = 600000*IUDP_MPHASE_CNT;
			THR_TIME = time_tmp/UTILITY_SETTINGS[4]; 	
			music_tim = 0;				//////////force start sample
			if(UDP_MPHASE_CNT<16)
				{
				UDP_MPHASE_CNT++;	
				}
			else		
				{
				UDP_MPHASE_CNT = 1;	
				}
			UDP_MPHASE = ((UDP_MPHASE_CNT+3)%4)+1; 	
			UDP_NEED_UPDATE_MPHASE = 1;	
			}
		}
		
		
	if(HAL_GPIO_ReadPin(GPIOC, PAD_0_Pin)==1 && PAD_0_PRESSED==0)								//PAD 0
		{
		int_pad_handler(0);						
		PAD_0_PRESSED = 1;	
		}	
	else if(HAL_GPIO_ReadPin(GPIOC, PAD_0_Pin)==0 && PAD_0_PRESSED==1)
		{
		PAD_0_PRESSED = 0;	
		}		
	else if(HAL_GPIO_ReadPin(GPIOC, PAD_1_Pin)==1 && PAD_1_PRESSED==0)								//PAD 1
		{
		int_pad_handler(1);				
		PAD_1_PRESSED = 1;	
		}	
	else if(HAL_GPIO_ReadPin(GPIOC, PAD_1_Pin)==0 && PAD_1_PRESSED==1)
		{
		PAD_1_PRESSED = 0;	
		}	
	else if(HAL_GPIO_ReadPin(GPIOG, PAD_2_Pin)==1 && PAD_2_PRESSED==0)								//PAD 2
		{
		int_pad_handler(2);			
		PAD_2_PRESSED = 1;	
		}	
	else if(HAL_GPIO_ReadPin(GPIOG, PAD_2_Pin)==0 && PAD_2_PRESSED==1)
		{
		PAD_2_PRESSED = 0;	
		}			
	else if(HAL_GPIO_ReadPin(PAD_3_GPIO_Port, PAD_3_Pin)==1 && PAD_3_PRESSED==0)			//PAD 3
		{
		int_pad_handler(3);			
		PAD_3_PRESSED = 1;	
		}	
	else if(HAL_GPIO_ReadPin(PAD_3_GPIO_Port, PAD_3_Pin)==0 && PAD_3_PRESSED==1)
		{
		PAD_3_PRESSED = 0;	
		}
	else if(HAL_GPIO_ReadPin(GPIOG, PAD_4_Pin)==1 && PAD_4_PRESSED==0)								//PAD 4
		{
		int_pad_handler(4);
		PAD_4_PRESSED = 1;	
		}	
	else if(HAL_GPIO_ReadPin(GPIOG, PAD_4_Pin)==0 && PAD_4_PRESSED==1)
		{
		PAD_4_PRESSED = 0;	
		}	
	else if(HAL_GPIO_ReadPin(GPIOI, PAD_5_Pin)==1 && PAD_5_PRESSED==0)								//PAD 5
		{
		int_pad_handler(5);
		PAD_5_PRESSED = 1;	
		}	
	else if(HAL_GPIO_ReadPin(GPIOI, PAD_5_Pin)==0 && PAD_5_PRESSED==1)
		{
		PAD_5_PRESSED = 0;	
		}				
	else if(HAL_GPIO_ReadPin(PAD_6_GPIO_Port, PAD_6_Pin)==1 && PAD_6_PRESSED==0)								//PAD 6
		{
		int_pad_handler(6);
		PAD_6_PRESSED = 1;	
		}	
	else if(HAL_GPIO_ReadPin(PAD_6_GPIO_Port, PAD_6_Pin)==0 && PAD_6_PRESSED==1)
		{
		PAD_6_PRESSED = 0;	
		}	
	else if(HAL_GPIO_ReadPin(PAD_7_GPIO_Port, PAD_7_Pin)==1 && PAD_7_PRESSED==0)								//PAD 7
		{
		int_pad_handler(7);
		PAD_7_PRESSED = 1;	
		}	
	else if(HAL_GPIO_ReadPin(PAD_7_GPIO_Port, PAD_7_Pin)==0 && PAD_7_PRESSED==1)
		{
		PAD_7_PRESSED = 0;	
		}	
	
		
		
	//////////////////time effect processing	
	if(EFFECT_ON && UTILITY_SETTINGS[2]==0)		//trans
		{
		if(UDP_BPM!=0xFFFFFFFF)
			{
			mbp_mux = music_tim*(UDP_BPM+5); 
			}	
		else
			{
			mbp_mux = music_tim*12000;	
			}
			
		inv_VR_LEVEL = 127-VR_LEVEL;	
		if(VR_PARAMETER_2<44)			//trans 1 beat
			{
			if(mbp_mux>=(47245*inv_VR_LEVEL))
				{
				if(VR_PARAMETER_1!=127)
					{					
					trans_mute = 1;
					}
				}
			else
				{
				trans_mute = 0;
				}				
			}
		else if(VR_PARAMETER_2<86)			//trans 1/2 beat
			{
			vlevel_mux = 23623*inv_VR_LEVEL;
			if(mbp_mux>=vlevel_mux && (mbp_mux<3000000) ||  mbp_mux>=(vlevel_mux+3000000))	
				{
				if(VR_PARAMETER_1!=127)
					{					
					trans_mute = 1;
					}		
				}
			else
				{
				trans_mute = 0;
				}
			}
		else			//trans 1/4 beat
			{
			vlevel_mux = 11812*inv_VR_LEVEL;
			if(mbp_mux>=vlevel_mux && (mbp_mux<1500000) ||	
					mbp_mux>=(vlevel_mux+1500000) && (mbp_mux<3000000) ||	
					mbp_mux>=(vlevel_mux+3000000) && (mbp_mux<4500000) ||	
					mbp_mux>=(vlevel_mux+4500000))
				{
		 		if(VR_PARAMETER_1!=127)
					{					
					trans_mute = 1;
					}	
				}				
			else
				{
				trans_mute = 0;	
				}
			}
			
		if(previous_trans_mute != trans_mute)	
			{
			previous_trans_mute = trans_mute;
			fade = 23;	
			}
		}		
	else if(EFFECT_ON && UTILITY_SETTINGS[2]==1)			//Moog Filter	
		{		
		if(VR_LEVEL<2)
			{
			fcutoff = 1.16*VR_POS[2]; 	
			}	
		else
			{
			fcutoff = 1.16*VR_POS[VR_LEVEL]; 	
			}	
		resonanse = 1.700f - 0.255 * fcutoff * fcutoff;	
		}

		
	
				
	if(ACTIVE_PAD<8)
		{
		if(music_tim==0 && force_start_sample==1)    //force start when quantize enable 
			{
			play_adr = SMPL_STRT;
			force_start_sample = 2;		
			}
		else if(end_of_track==0 && force_start_sample==2)		//wait when restart audio handler
			{
			force_start_sample = 0;	
			}

		if(P_TYPE[ACTIVE_PAD]==1)						//sequencer	
			{	
			if(end_one_shot_seq==0)	
				{
				if(music_tim==0)
					{
					if(P_WAVEFORM[ACTIVE_PAD][64]==0 && BEAT_CNT>2)
						{	
						if(P_TRIG[ACTIVE_PAD]==0 && BEAT_CNT!=0xFF)		//sequencer & one shot
							{
							end_one_shot_seq = 1;	
							}
						BEAT_CNT = 0;
						}					
					else if(P_WAVEFORM[ACTIVE_PAD][64]==1 && BEAT_CNT>6)
						{
						if(P_TRIG[ACTIVE_PAD]==0 && BEAT_CNT!=0xFF)		//sequencer & one shot
							{
							end_one_shot_seq = 1;	
							}
						BEAT_CNT = 0;							
						}	
					else if(BEAT_CNT>14)
						{
						if(P_TRIG[ACTIVE_PAD]==0 && BEAT_CNT!=0xFF)		//sequencer & one shot
							{
							end_one_shot_seq = 1;	
							}
						BEAT_CNT = 0;								
						}
					else
						{
						BEAT_CNT++;		
						}	
					PARTBEAT_CNT = 0;		
					
					if(P_WAVEFORM[ACTIVE_PAD][(BEAT_CNT%16)<<2]==1 && end_one_shot_seq==0)						//optimizirovat - ubrat[ ....PARTBEAT_CNT]
						{					
						play_adr = SMPL_STRT;
						COLOR_SET(PADS_H_COLOR[P_COLOR[ACTIVE_PAD]], ACTIVE_PAD);			
						need_load_rgb = 1;						
						pad_off_tim	= SQN[0]>>1;
						}		
					}				
				else if((music_tim==SQN[0] && PARTBEAT_CNT==0) || (music_tim==SQN[1] && PARTBEAT_CNT==1) || (music_tim==SQN[2] && PARTBEAT_CNT==2))
					{
					PARTBEAT_CNT++;	
					if(P_WAVEFORM[ACTIVE_PAD][((BEAT_CNT%16)<<2)+PARTBEAT_CNT]==1)
						{					
						play_adr = SMPL_STRT;	
						COLOR_SET(PADS_H_COLOR[P_COLOR[ACTIVE_PAD]], ACTIVE_PAD);		
						need_load_rgb = 1;						
						pad_off_tim	= SQN[0]>>1;	
						}						
					}	
				}	
			else
				{
				if(end_of_track==1 && (need_load_rgb==0) && (ACTIVE_PAD<8))
					{				
					COLOR_SET(PADS_L_COLOR[P_COLOR[ACTIVE_PAD]], ACTIVE_PAD);	
					need_load_rgb = 1;		
					ACTIVE_PAD = 0xFF;	
					end_one_shot_seq = 0;	
					}	
				}
					
			if(pad_off_tim>0)				//led off pad
				{
				if(pad_off_tim==1)
					{	
					COLOR_SET(0xFF000000, ACTIVE_PAD);	
					need_load_rgb = 1;						
					}
				pad_off_tim--;
				}	
			}	
		else if(P_TRIG[ACTIVE_PAD]==1 && P_TYPE[ACTIVE_PAD]==0)		//if sample & loop
			{
			if(music_tim==0)
				{
				if(P_SYNC[ACTIVE_PAD]==0)							//sync speed disable
					{
					sai_pitch = 10000;	
					}			
				else													//sync speed
					{
					tmp_pitch = UDP_BPM+5;
					tmp_pitch = tmp_pitch*1000;	
					tmp_pitch = tmp_pitch/P_BPM[ACTIVE_PAD];	
					sai_pitch = tmp_pitch;
					}
				play_adr = SMPL_STRT;
				COLOR_SET(PADS_H_COLOR[P_COLOR[ACTIVE_PAD]], ACTIVE_PAD);	
				need_load_rgb = 1;						
				}
			else if(music_tim==SQN[0]>>1)
				{
				COLOR_SET(PADS_L_COLOR[P_COLOR[ACTIVE_PAD]], ACTIVE_PAD);	
				need_load_rgb = 1;		
				}
			}
		else					//sample one shot
			{				
			if(end_of_track==1 && (need_load_rgb==0) && (ACTIVE_PAD<8) && (force_start_sample==0))
				{				
				COLOR_SET(PADS_L_COLOR[P_COLOR[ACTIVE_PAD]], ACTIVE_PAD);	
				need_load_rgb = 1;		
				ACTIVE_PAD = 0xFF;	
				}
				
			if(pad_sample_on_tim>0)
				{
				if(pad_sample_on_tim==1)
					{
					COLOR_SET(PADS_H_COLOR[P_COLOR[ACTIVE_PAD]], ACTIVE_PAD);			//turn on sample pad
					need_load_rgb = 1;						
					}
				pad_sample_on_tim--;
				}					
			}		
		}
		
	if(music_tim==0)										//blink SYNC OUT led
		{
		UDP_NEED_UPDATE_SPHASE = 1;	
		if(SYNC_OUT_ON)
			{
			need_send_sync = 1;	
			sync_out_tim = SQN[0]>>2;
			GPIOD->BSRR = 0x00000020;				//HAL_GPIO_WritePin(LED_SYNC_OUT_GPIO_Port, LED_SYNC_OUT_Pin, GPIO_PIN_SET);				
			}						
		}	
	else if(sync_out_tim>0 && SYNC_OUT_ON)
		{
		if(sync_out_tim==1)
			{
			GPIOD->BSRR = 0x00200000;			//HAL_GPIO_WritePin(LED_SYNC_OUT_GPIO_Port, LED_SYNC_OUT_Pin, GPIO_PIN_RESET);	
			}			
		sync_out_tim--;	
		}			
		
	music_tim++;	

	if(TIM_LED_DIV<124)
		{
		TIM_LED_DIV++;	
		}
	else
		{
		if(ENCODER_LED_BLINK<8 || END_BLINK==0)
			{	
			if(ENCODER_LED_BLINK%2==0)
				{
				GPIOB->BSRR = 0x01000000;  //HAL_GPIO_WritePin(GPIOB, LED_ENC_Pin, GPIO_PIN_RESET);						
				}
			else
				{
				GPIOB->BSRR = 0x00000100;  //HAL_GPIO_WritePin(GPIOB, LED_ENC_Pin, GPIO_PIN_SET);
				}
			ENCODER_LED_BLINK++;	
			}			
		TIM_LED_DIV = 0;	
		}
	
	if(TIM_DIVIDER<2000)
		{
		if(TIM_DIVIDER%10==5)
			{
			if(link_req>0)
				{
				link_req--;	
				}				
			else
				{
				if(UTILITY_SETTINGS[3]==1)		//external bpm clock
					{
					if(TIM_DIVIDER==5 || TIM_DIVIDER==505 || TIM_DIVIDER==1005 || TIM_DIVIDER==1505)	
						{
						link_status = 0;
						}
					else if(TIM_DIVIDER==255 || TIM_DIVIDER==755 || TIM_DIVIDER==1255 || TIM_DIVIDER==1755)			
						{
						link_status = 1;	
						}
					}
				}
			if(EFFECT_ON)
				{
				if(TIM_DIVIDER==5 || TIM_DIVIDER==505 || TIM_DIVIDER==1005 || TIM_DIVIDER==1505)	
					{
					GPIOA->BSRR = 0x00000800; 		//HAL_GPIO_WritePin(GPIOA, LED_EFFECT_Pin, GPIO_PIN_SET);
					}
				else if(TIM_DIVIDER==255 || TIM_DIVIDER==755 || TIM_DIVIDER==1255 || TIM_DIVIDER==1755)			
					{
					GPIOA->BSRR = 0x08000000;			//HAL_GPIO_WritePin(GPIOA, LED_EFFECT_Pin, GPIO_PIN_RESET);		
					}	
				}				
			}
			
		if(TIM_DIVIDER%18==0)												//LEVEL VR	
			{
			ADC_1_TEMP = 3*ADC_1_TEMP + HAL_ADC_GetValue(&hadc1);	
			ADC_1_TEMP = ADC_1_TEMP>>2;	
			if(ADC_1_TEMP>(ADC_1_center+ADC_HYSTERESIS) || (ADC_HYSTERESIS+ADC_1_TEMP)<ADC_1_center)			
					{																																							
					ADC_1_center = ADC_1_TEMP;																				
					}	
			if(ADC_1_center<32)
				{
				VR_LEVEL = 0;	
				}
			else if(ADC_1_center>4062)
				{
				VR_LEVEL = 127;	
				}
			else
				{
				VR_LEVEL = (ADC_1_center-32)>>5;	
				}				
			}
		else if(TIM_DIVIDER%18==3)
			{
			HAL_ADC_Start(&hadc1);		
			}
		else if(TIM_DIVIDER%18==6)										//PARAMETER_1 VR
			{				
			ADC_2_TEMP = 3*ADC_2_TEMP + HAL_ADC_GetValue(&hadc2);	
			ADC_2_TEMP = ADC_2_TEMP>>2;	
			if(ADC_2_TEMP>(ADC_2_center+ADC_HYSTERESIS) || (ADC_HYSTERESIS+ADC_2_TEMP)<ADC_2_center)			
					{																																							
					ADC_2_center = ADC_2_TEMP;																				
					}				
			if(ADC_2_center<32)
				{
				VR_PARAMETER_1 = 0;	
				}
			else if(ADC_2_center>4062)
				{
				VR_PARAMETER_1 = 127;	
				}
			else
				{
				VR_PARAMETER_1 = (ADC_2_center-32)>>5;	
				}				
			}
		else if(TIM_DIVIDER%18==9)
			{
			HAL_ADC_Start(&hadc2);	
			}
		else if(TIM_DIVIDER%18==12)									//PARAMETER_2 VR	
			{				
			ADC_3_TEMP = 3*ADC_3_TEMP + HAL_ADC_GetValue(&hadc3);	
			ADC_3_TEMP = ADC_3_TEMP>>2;	
			if(ADC_3_TEMP>(ADC_3_center+ADC_HYSTERESIS) || (ADC_HYSTERESIS+ADC_3_TEMP)<ADC_3_center)			
					{																																							
					ADC_3_center = ADC_3_TEMP;																				
					}	
			if(ADC_3_center<32)
				{
				VR_PARAMETER_2 = 0;	
				}
			else if(ADC_3_center>4062)
				{
				VR_PARAMETER_2 = 127;	
				}
			else
				{
				VR_PARAMETER_2 = (ADC_3_center-32)>>5;	
				}	
			}
		else if(TIM_DIVIDER%18==15)
			{
			HAL_ADC_Start(&hadc3);	
			}			
		TIM_DIVIDER++;	
		}
	else
		{
		if(UTILITY_SETTINGS[3]!=0)		//external bpm clock
			{
			if(UDP_SEND_PART==1)
				{
				UDP_SEND_PART	= 2;
				}
			else
				{
				UDP_SEND_PART	= 1;	
				}
			udp_client_send(UDP_SEND_PART);	
			}
		TIM_DIVIDER = 0;		
		}		
  HAL_TIM_IRQHandler(&htim2);
	}	



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



