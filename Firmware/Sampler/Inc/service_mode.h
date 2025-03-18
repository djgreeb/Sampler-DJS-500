/////////////////////////////////////////////////////////////////////////////////////////////////
//	Service mode
//	product: DJS-500 sampler
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdint.h"

/* SERVICE MODE ---------------------------------------------------------*/														
uint8_t SERVICE_MODE_ENABLE = 0;	


void SERVICE_MODE(void);			//service mode function

///////////////////////////////////////////////
// service mode
//			
void SERVICE_MODE(void)
	{
	uint8_t SM_STEP = 0xFF;
	uint8_t previous_CARD_SLOT = 0xFF;	
	uint8_t encoder_step = 127;
	uint8_t SM_ADC_1 = 0; 	
	uint8_t SM_ADC_2 = 0;
	uint8_t SM_ADC_3 = 0;
	uint8_t PUSH_LOCK = 0;		//for test buttons	
	uint8_t SM_PAD_COLOR[8] = {0};	
			
	HAL_GPIO_WritePin(GPIOB, LED_ENC_Pin|LED_SHIFT_Pin, GPIO_PIN_RESET);										//////////////////////////////
	HAL_GPIO_WritePin(GPIOA, LED_PRESET_Pin|LED_EFFECT_Pin, GPIO_PIN_RESET);								//
	HAL_GPIO_WritePin(LED_SYNC_OUT_GPIO_Port, LED_SYNC_OUT_Pin, GPIO_PIN_RESET);						//			turn off leds
	HAL_GPIO_WritePin(GPIOI, LED_EDIT_Pin, GPIO_PIN_RESET);																	//
	HAL_GPIO_WritePin(LED_MENU_GPIO_Port, LED_MENU_Pin, GPIO_PIN_RESET);										//////////////////////////////
	
	BSP_LCD_Clear(LCD_COLOR_BLACK);	
	BSP_LCD_SetFont(&Font15P);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	sprintf((char*)Buf, "%s", "DJS-500NXS SERVICE MODE");						
	BSP_LCD_DisplayStringAt(130, 43, Buf, TRANSPARENT_MODE);
	BSP_LCD_DrawRect(112, 30, 254, 40);	
	
	HAL_GPIO_WritePin(GPIOB, LED_ENC_Pin, GPIO_PIN_RESET);		//turn off encoder led	
	COLOR_SET(0x00000000, 0);
	COLOR_SET(0x00000000, 1);
	COLOR_SET(0x00000000, 2);
	COLOR_SET(0x00000000, 3);
	COLOR_SET(0x00000000, 4);
	COLOR_SET(0x00000000, 5);
	COLOR_SET(0x00000000, 6);
	COLOR_SET(0x00000000, 7);
	HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);	
	HAL_Delay(3);
	
	while(1)
		{
		if(HAL_GPIO_ReadPin(GPIOD, KEY_BACK_Pin)==0 && KEY_BACK_pressed==0)
			{
			if(SM_STEP<11)
				{				
				SM_STEP++;
				}
			else
				{
				SM_STEP = 0;	
				}				
				
			if(SM_STEP==0)					
				{
				BSP_LCD_Clear(LCD_COLOR_BLACK);	
				BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
				sprintf((char*)Buf, "%s", "SERVICE MODE");						
				BSP_LCD_DisplayStringAt(1, 3, Buf, TRANSPARENT_MODE);	
				sprintf((char*)Buf, "%s", "BUTTON");						
				BSP_LCD_DisplayStringAt(11, 20, Buf, TRANSPARENT_MODE);
				sprintf((char*)Buf, "%s", "ENCODER");						
				BSP_LCD_DisplayStringAt(11, 37, Buf, TRANSPARENT_MODE);	
				sprintf((char*)Buf, "%03lu", encoder_step);					
				BSP_LCD_DisplayStringAt(145, 37, Buf, LEFT_MODE);
				sprintf((char*)Buf, "%s", "EFF. LEVEL");						
				BSP_LCD_DisplayStringAt(11, 54, Buf, TRANSPARENT_MODE);	
				sprintf((char*)Buf, "%03lu", SM_ADC_1);					
				BSP_LCD_DisplayStringAt(145, 54, Buf, LEFT_MODE);	
				sprintf((char*)Buf, "%s", "PARAMETER 1");						
				BSP_LCD_DisplayStringAt(11, 71, Buf, TRANSPARENT_MODE);	
				sprintf((char*)Buf, "%03lu", SM_ADC_2);					
				BSP_LCD_DisplayStringAt(145, 71, Buf, LEFT_MODE);	
				sprintf((char*)Buf, "%s", "PARAMETER 2");						
				BSP_LCD_DisplayStringAt(11, 88, Buf, TRANSPARENT_MODE);		
				sprintf((char*)Buf, "%03lu", SM_ADC_3);					
				BSP_LCD_DisplayStringAt(145, 88, Buf, LEFT_MODE);	
				sprintf((char*)Buf, "%s", "CARD SLOT");						
				BSP_LCD_DisplayStringAt(11, 105, Buf, TRANSPARENT_MODE);	
					
				previous_CARD_SLOT = 0xFF;	
				}
			else if(SM_STEP==1)						//LCD TEST
				{
				HAL_GPIO_WritePin(GPIOB, LED_ENC_Pin|LED_SHIFT_Pin, GPIO_PIN_RESET);						
				HAL_GPIO_WritePin(GPIOA, LED_PRESET_Pin|LED_EFFECT_Pin, GPIO_PIN_RESET);								
				HAL_GPIO_WritePin(LED_SYNC_OUT_GPIO_Port, LED_SYNC_OUT_Pin, GPIO_PIN_RESET);						
				HAL_GPIO_WritePin(GPIOI, LED_EDIT_Pin, GPIO_PIN_RESET);																	
				HAL_GPIO_WritePin(LED_MENU_GPIO_Port, LED_MENU_Pin, GPIO_PIN_RESET);			
					
				BSP_LCD_SetTextColor(0xFFFFFFFF);	
				BSP_LCD_FillRect(0, 0, 80, 272);
				BSP_LCD_SetTextColor(0xFFA8A8A8);	
				BSP_LCD_FillRect(80, 0, 80, 272);	
				BSP_LCD_SetTextColor(0xFF7E7E7E);	
				BSP_LCD_FillRect(160, 0, 80, 272);
				BSP_LCD_SetTextColor(0xFF545454);	
				BSP_LCD_FillRect(240, 0, 80, 272);	
				BSP_LCD_SetTextColor(0xFF2A2A2A);	
				BSP_LCD_FillRect(320, 0, 80, 272);	
				BSP_LCD_SetTextColor(0xFF000000);	
				BSP_LCD_FillRect(400, 0, 80, 272);	
				}
			else if(SM_STEP==2)						//LCD TEST
				{
				BSP_LCD_SetTextColor(0xFFFFFF00);	
				BSP_LCD_FillRect(0, 0, 80, 272);
				BSP_LCD_SetTextColor(0xFF0000FF);	
				BSP_LCD_FillRect(80, 0, 80, 272);	
				BSP_LCD_SetTextColor(0xFF00FF00);	
				BSP_LCD_FillRect(160, 0, 80, 272);
				BSP_LCD_SetTextColor(0xFFFF00FF);	
				BSP_LCD_FillRect(240, 0, 80, 272);	
				BSP_LCD_SetTextColor(0xFFFF0000);	
				BSP_LCD_FillRect(320, 0, 80, 272);	
				BSP_LCD_SetTextColor(0xFF00FFFF);	
				BSP_LCD_FillRect(400, 0, 80, 272);	
				}	
			else if(SM_STEP==3)						//LCD TEST
				{
				BSP_LCD_Clear(LCD_COLOR_BLACK);	
				}		
			else if(SM_STEP==4)						//LCD TEST
				{
				BSP_LCD_Clear(LCD_COLOR_WHITE);	
				}	
			else if(SM_STEP==5)						//LCD TEST
				{
				BSP_LCD_Clear(0xFFFF0000);	
				}	
			else if(SM_STEP==6)						//LCD TEST
				{
				BSP_LCD_Clear(0xFF00FF00);	
				}	
			else if(SM_STEP==7)						//LCD TEST
				{
				BSP_LCD_Clear(0xFF0000FF);	
				}	
			else if(SM_STEP==8)						//LED TEST
				{
				BSP_LCD_Clear(LCD_COLOR_BLACK);	
				BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
				sprintf((char*)Buf, "%s", "SERVICE MODE");						
				BSP_LCD_DisplayStringAt(1, 3, Buf, TRANSPARENT_MODE);	
				sprintf((char*)Buf, "%s", "ALL LED ON");
				BSP_LCD_DisplayStringAt(11, 20, Buf, TRANSPARENT_MODE);
				HAL_GPIO_WritePin(GPIOB, LED_ENC_Pin|LED_SHIFT_Pin, GPIO_PIN_SET);										//////////////////////////////
				HAL_GPIO_WritePin(GPIOA, LED_PRESET_Pin|LED_EFFECT_Pin, GPIO_PIN_SET);								//
				HAL_GPIO_WritePin(LED_SYNC_OUT_GPIO_Port, LED_SYNC_OUT_Pin, GPIO_PIN_SET);						//			turn on leds
				HAL_GPIO_WritePin(GPIOI, LED_EDIT_Pin, GPIO_PIN_SET);																	//
				HAL_GPIO_WritePin(LED_MENU_GPIO_Port, LED_MENU_Pin, GPIO_PIN_SET);										//////////////////////////////
				COLOR_SET(0x002F2F2F, 0);
				COLOR_SET(0x002F2F2F, 1);
				COLOR_SET(0x002F2F2F, 2);
				COLOR_SET(0x002F2F2F, 3);
				COLOR_SET(0x002F2F2F, 4);
				COLOR_SET(0x002F2F2F, 5);
				COLOR_SET(0x002F2F2F, 6);
				COLOR_SET(0x002F2F2F, 7);
				HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);			
				}	
			else if(SM_STEP==9)						//LED TEST
				{
				BSP_LCD_Clear(LCD_COLOR_BLACK);	
				BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
				sprintf((char*)Buf, "%s", "SERVICE MODE");						
				BSP_LCD_DisplayStringAt(1, 3, Buf, TRANSPARENT_MODE);	
				sprintf((char*)Buf, "%s", "ALL LED OFF");
				BSP_LCD_DisplayStringAt(11, 20, Buf, TRANSPARENT_MODE);	
				HAL_GPIO_WritePin(GPIOB, LED_ENC_Pin|LED_SHIFT_Pin, GPIO_PIN_RESET);						
				HAL_GPIO_WritePin(GPIOA, LED_PRESET_Pin|LED_EFFECT_Pin, GPIO_PIN_RESET);								
				HAL_GPIO_WritePin(LED_SYNC_OUT_GPIO_Port, LED_SYNC_OUT_Pin, GPIO_PIN_RESET);						
				HAL_GPIO_WritePin(GPIOI, LED_EDIT_Pin, GPIO_PIN_RESET);																	
				HAL_GPIO_WritePin(LED_MENU_GPIO_Port, LED_MENU_Pin, GPIO_PIN_RESET);										
				COLOR_SET(0x00000000, 0);
				COLOR_SET(0x00000000, 1);
				COLOR_SET(0x00000000, 2);
				COLOR_SET(0x00000000, 3);
				COLOR_SET(0x00000000, 4);
				COLOR_SET(0x00000000, 5);
				COLOR_SET(0x00000000, 6);
				COLOR_SET(0x00000000, 7);
				HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);					
				}	
			else if(SM_STEP==10)						//PADS TEST
				{
				SM_PAD_COLOR[0] = 0;	
				SM_PAD_COLOR[1] = 0;
				SM_PAD_COLOR[2] = 0;
				SM_PAD_COLOR[3] = 0;
				SM_PAD_COLOR[4] = 0;
				SM_PAD_COLOR[5] = 0;
				SM_PAD_COLOR[6] = 0;
				SM_PAD_COLOR[7] = 0;					
				BSP_LCD_Clear(LCD_COLOR_BLACK);	
				BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
				sprintf((char*)Buf, "%s", "SERVICE MODE");						
				BSP_LCD_DisplayStringAt(1, 3, Buf, TRANSPARENT_MODE);	
				sprintf((char*)Buf, "%s", "PADS TEST");
				BSP_LCD_DisplayStringAt(11, 20, Buf, TRANSPARENT_MODE);		
				}
			else if(SM_STEP==11)						//ABOUT
				{
				COLOR_SET(0x00000000, 0);
				COLOR_SET(0x00000000, 1);
				COLOR_SET(0x00000000, 2);
				COLOR_SET(0x00000000, 3);
				COLOR_SET(0x00000000, 4);
				COLOR_SET(0x00000000, 5);
				COLOR_SET(0x00000000, 6);
				COLOR_SET(0x00000000, 7);
				HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);	
					
				BSP_LCD_Clear(LCD_COLOR_BLACK);	
				BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
				sprintf((char*)Buf, "%s", "SERVICE MODE");						
				BSP_LCD_DisplayStringAt(1, 3, Buf, TRANSPARENT_MODE);	
				sprintf((char*)Buf, "%s", "VERSION No.");						
				BSP_LCD_DisplayStringAt(11, 20, Buf, TRANSPARENT_MODE);
				sprintf((char*)Buf, "%s%s", "Ver. ", FIRMWARE_VERSION);						
				BSP_LCD_DisplayStringAt(145, 20, Buf, TRANSPARENT_MODE);					
				sprintf((char*)Buf, "%s", "MCU:");						
				BSP_LCD_DisplayStringAt(11, 37, Buf, TRANSPARENT_MODE);
				sprintf((char*)Buf, "%s", "ARM STM32F746NGH6");						
				BSP_LCD_DisplayStringAt(145, 37, Buf, TRANSPARENT_MODE);
				sprintf((char*)Buf, "%s", "DAC:");						
				BSP_LCD_DisplayStringAt(11, 54, Buf, TRANSPARENT_MODE);	
				sprintf((char*)Buf, "%s", "Cirrus Logic WM8994ECS 24-bit");						
				BSP_LCD_DisplayStringAt(145, 54, Buf, TRANSPARENT_MODE);
				sprintf((char*)Buf, "%s", "LAN:");						
				BSP_LCD_DisplayStringAt(11, 71, Buf, TRANSPARENT_MODE);	
				sprintf((char*)Buf, "%s", "SMSC LAN8742A-CZ-TR");						
				BSP_LCD_DisplayStringAt(145, 71, Buf, TRANSPARENT_MODE);
				sprintf((char*)Buf, "%s", "MAC ADRESS:");			
				BSP_LCD_DisplayStringAt(11, 88, Buf, TRANSPARENT_MODE);	
				sprintf((char*)Buf, "%02lX-%02lX-%02lX-%02lX-%02lX-%02lX", MAC_ADR[0], MAC_ADR[1], MAC_ADR[2], MAC_ADR[3], MAC_ADR[4], MAC_ADR[5]);					
				BSP_LCD_DisplayStringAt(145, 88, Buf, TRANSPARENT_MODE);
				sprintf((char*)Buf, "%s", "DEBUG MODE:");			
				BSP_LCD_DisplayStringAt(11, 105, Buf, TRANSPARENT_MODE);
				#ifdef USART_DEBUG
					sprintf((char*)Buf, "%s", "ENABLE");	
				#else
					sprintf((char*)Buf, "%s", "DISABLE");
				#endif
				BSP_LCD_DisplayStringAt(145, 105, Buf, TRANSPARENT_MODE);
				}
			KEY_BACK_pressed = 1;	
			}
		else if(HAL_GPIO_ReadPin(GPIOD, KEY_BACK_Pin)==1 && KEY_BACK_pressed==1)
			{
			KEY_BACK_pressed = 0;	
			}		

		if(SM_STEP==0)							
			{
			if(HAL_GPIO_ReadPin(KEY_PRESET_GPIO_Port, KEY_PRESET_Pin)==0)
				{	
				if(PUSH_LOCK==0)
					{					
					sprintf((char*)Buf, "%s", "PRESET         ");						
					BSP_LCD_DisplayStringAt(145, 20, Buf, LEFT_MODE);
					HAL_GPIO_WritePin(GPIOA, LED_PRESET_Pin, GPIO_PIN_SET);	
					PUSH_LOCK = 1;
					}						
				}
			else if(HAL_GPIO_ReadPin(GPIOB, KEY_SHIFT_Pin)==0)
				{
				if(PUSH_LOCK==0)
					{					
					sprintf((char*)Buf, "%s", "SHIFT          ");						
					BSP_LCD_DisplayStringAt(145, 20, Buf, LEFT_MODE);
					HAL_GPIO_WritePin(GPIOB, LED_SHIFT_Pin, GPIO_PIN_SET);	
					PUSH_LOCK = 1;
					}						
				}
			else if(HAL_GPIO_ReadPin(GPIOB, KEY_EDIT_Pin)==0)
				{
				if(PUSH_LOCK==0)	
					{
					sprintf((char*)Buf, "%s", "EDIT           ");						
					BSP_LCD_DisplayStringAt(145, 20, Buf, LEFT_MODE);
					HAL_GPIO_WritePin(GPIOI, LED_EDIT_Pin, GPIO_PIN_SET);	
					PUSH_LOCK = 1;
					}						
				}
			else if(HAL_GPIO_ReadPin(GPIOF, KEY_MENU_Pin)==0)
				{
				if(PUSH_LOCK==0)
					{
					sprintf((char*)Buf, "%s", "MENU           ");						
					BSP_LCD_DisplayStringAt(145, 20, Buf, LEFT_MODE);	
					HAL_GPIO_WritePin(LED_MENU_GPIO_Port, LED_MENU_Pin, GPIO_PIN_SET);	
					PUSH_LOCK = 1;	
					}
				}
			else if(HAL_GPIO_ReadPin(KEY_SYNC_OUT_GPIO_Port, KEY_SYNC_OUT_Pin)==0)
				{
				if(PUSH_LOCK==0)
					{
					sprintf((char*)Buf, "%s", "SYNC OUT       ");						
					BSP_LCD_DisplayStringAt(145, 20, Buf, LEFT_MODE);	
					HAL_GPIO_WritePin(LED_SYNC_OUT_GPIO_Port, LED_SYNC_OUT_Pin, GPIO_PIN_SET);
					PUSH_LOCK = 1;	
					}
				}
			else if(HAL_GPIO_ReadPin(GPIOD, KEY_EFFECT_Pin)==0)
				{
				if(PUSH_LOCK==0)
					{
					sprintf((char*)Buf, "%s", "EFFECT         ");						
					BSP_LCD_DisplayStringAt(145, 20, Buf, LEFT_MODE);		
					HAL_GPIO_WritePin(GPIOA, LED_EFFECT_Pin, GPIO_PIN_SET);	
					PUSH_LOCK = 1;			
					}					
				}
			else if(HAL_GPIO_ReadPin(GPIOF, KEY_ENC_Pin)==0)
				{
				if(PUSH_LOCK==0)
					{					
					sprintf((char*)Buf, "%s", "ENCODER        ");						
					BSP_LCD_DisplayStringAt(145, 20, Buf, LEFT_MODE);		
					HAL_GPIO_WritePin(GPIOB, LED_ENC_Pin, GPIO_PIN_SET);
					PUSH_LOCK = 1;
					}						
				}
			else if(HAL_GPIO_ReadPin(KEY_PRESET_GPIO_Port, KEY_PRESET_Pin)==1 &&
				HAL_GPIO_ReadPin(GPIOB, KEY_EDIT_Pin|KEY_SHIFT_Pin)==1 && 
				HAL_GPIO_ReadPin(KEY_SYNC_OUT_GPIO_Port, KEY_SYNC_OUT_Pin)==1 &&
				HAL_GPIO_ReadPin(GPIOD, KEY_EFFECT_Pin)==1 &&
				HAL_GPIO_ReadPin(GPIOF, KEY_MENU_Pin|KEY_ENC_Pin)==1 && PUSH_LOCK==1)	
				{	
				sprintf((char*)Buf, "%s", "                    ");						
				BSP_LCD_DisplayStringAt(145, 20, Buf, LEFT_MODE);		
				HAL_GPIO_WritePin(GPIOA, LED_PRESET_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB, LED_SHIFT_Pin, GPIO_PIN_RESET);		
				HAL_GPIO_WritePin(GPIOI, LED_EDIT_Pin, GPIO_PIN_RESET);		
				HAL_GPIO_WritePin(LED_MENU_GPIO_Port, LED_MENU_Pin, GPIO_PIN_RESET);		
				HAL_GPIO_WritePin(LED_SYNC_OUT_GPIO_Port, LED_SYNC_OUT_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA, LED_EFFECT_Pin, GPIO_PIN_RESET);	
				HAL_GPIO_WritePin(GPIOB, LED_ENC_Pin, GPIO_PIN_RESET);
				PUSH_LOCK = 0;
				}
			if(SM_ADC_1 != VR_LEVEL)				//VRs test
				{
				SM_ADC_1 = VR_LEVEL;	
				sprintf((char*)Buf, "%03lu", SM_ADC_1);					
				BSP_LCD_DisplayStringAt(145, 54, Buf, LEFT_MODE);		
				}
			if(SM_ADC_2 != VR_PARAMETER_1)
				{
				SM_ADC_2 = VR_PARAMETER_1;
				sprintf((char*)Buf, "%03lu", SM_ADC_2);					
				BSP_LCD_DisplayStringAt(145, 71, Buf, LEFT_MODE);	
				}
			if(SM_ADC_3 != VR_PARAMETER_2)
				{	
				SM_ADC_3 = VR_PARAMETER_2;	
				sprintf((char*)Buf, "%03lu", SM_ADC_3);					
				BSP_LCD_DisplayStringAt(145, 88, Buf, LEFT_MODE);	
				}
			if(enc_need_up==1)			//encoder test
				{
				if(encoder_step<255)
					{
					encoder_step++;
					sprintf((char*)Buf, "%03lu", encoder_step);					
					BSP_LCD_DisplayStringAt(145, 37, Buf, LEFT_MODE);							
					}
				enc_need_up = 0;	
				}
			else if(enc_need_down==1)
				{
				if(encoder_step>0)
					{
					encoder_step--;
					sprintf((char*)Buf, "%03lu", encoder_step);					
					BSP_LCD_DisplayStringAt(145, 37, Buf, LEFT_MODE);			
					}
				enc_need_down = 0;	
				}	
			if(HAL_GPIO_ReadPin(uSD_Detect_GPIO_Port, uSD_Detect_Pin)==0 && previous_CARD_SLOT!=1)						//check sd card slot
				{
				sprintf((char*)Buf, "%s", "SD ENABLE       ");						
				BSP_LCD_DisplayStringAt(145, 105, Buf, LEFT_MODE);	
				previous_CARD_SLOT = 1;	
				}
			else if(HAL_GPIO_ReadPin(uSD_Detect_GPIO_Port, uSD_Detect_Pin)==1 && previous_CARD_SLOT!=0)
				{
				sprintf((char*)Buf, "%s", "SD DISABLE       ");						
				BSP_LCD_DisplayStringAt(145, 105, Buf, LEFT_MODE);		
				previous_CARD_SLOT = 0;	
				}
			}
		else if(SM_STEP==10)					///PADs TEST
			{
			if(HAL_GPIO_ReadPin(GPIOC, PAD_0_Pin)==1 && PAD_0_PRESSED==0)								//PAD 0
				{
				if(SM_PAD_COLOR[0]<4)
					{					
					SM_PAD_COLOR[0]++;
					}
				else
					{
					SM_PAD_COLOR[0] = 0;	
					}					
				if(SM_PAD_COLOR[0]==0)					//black
					{
					COLOR_SET(0x00000000, 0);	
					}		
				else if(SM_PAD_COLOR[0]==1)			//red
					{
					COLOR_SET(0x002F0000, 0);	
					}	
				else if(SM_PAD_COLOR[0]==2)			//green
					{
					COLOR_SET(0x00002F00, 0);	
					}	
				else if(SM_PAD_COLOR[0]==3)			//blue
					{
					COLOR_SET(0x0000002F, 0);	
					}
				else if(SM_PAD_COLOR[0]==4)			//white
					{
					COLOR_SET(0x002F2F2F, 0);	
					}					
				HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);				
				PAD_0_PRESSED = 1;	
				}	
			else if(HAL_GPIO_ReadPin(GPIOC, PAD_0_Pin)==0 && PAD_0_PRESSED==1)
				{
				PAD_0_PRESSED = 0;	
				}		
			else if(HAL_GPIO_ReadPin(GPIOC, PAD_1_Pin)==1 && PAD_1_PRESSED==0)								//PAD 1
				{		
				if(SM_PAD_COLOR[1]<4)
					{					
					SM_PAD_COLOR[1]++;
					}
				else
					{
					SM_PAD_COLOR[1] = 0;	
					}					
				if(SM_PAD_COLOR[1]==0)					//black
					{
					COLOR_SET(0x00000000, 1);	
					}		
				else if(SM_PAD_COLOR[1]==1)			//red
					{
					COLOR_SET(0x002F0000, 1);	
					}	
				else if(SM_PAD_COLOR[1]==2)			//green
					{
					COLOR_SET(0x00002F00, 1);	
					}	
				else if(SM_PAD_COLOR[1]==3)			//blue
					{
					COLOR_SET(0x0000002F, 1);	
					}
				else if(SM_PAD_COLOR[1]==4)			//white
					{
					COLOR_SET(0x002F2F2F, 1);	
					}				
				HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);	
				PAD_1_PRESSED = 1;	
				}	
			else if(HAL_GPIO_ReadPin(GPIOC, PAD_1_Pin)==0 && PAD_1_PRESSED==1)
				{
				PAD_1_PRESSED = 0;	
				}	
			else if(HAL_GPIO_ReadPin(GPIOG, PAD_2_Pin)==1 && PAD_2_PRESSED==0)								//PAD 2
				{	
				if(SM_PAD_COLOR[2]<4)
					{					
					SM_PAD_COLOR[2]++;
					}
				else
					{
					SM_PAD_COLOR[2] = 0;	
					}					
				if(SM_PAD_COLOR[2]==0)					//black
					{
					COLOR_SET(0x00000000, 2);	
					}		
				else if(SM_PAD_COLOR[2]==1)			//red
					{
					COLOR_SET(0x002F0000, 2);	
					}	
				else if(SM_PAD_COLOR[2]==2)			//green
					{
					COLOR_SET(0x00002F00, 2);	
					}	
				else if(SM_PAD_COLOR[2]==3)			//blue
					{
					COLOR_SET(0x0000002F, 2);	
					}
				else if(SM_PAD_COLOR[2]==4)			//white
					{
					COLOR_SET(0x002F2F2F, 2);	
					}						
				HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);	
				PAD_2_PRESSED = 1;	
				}	
			else if(HAL_GPIO_ReadPin(GPIOG, PAD_2_Pin)==0 && PAD_2_PRESSED==1)
				{
				PAD_2_PRESSED = 0;	
				}			
			else if(HAL_GPIO_ReadPin(PAD_3_GPIO_Port, PAD_3_Pin)==1 && PAD_3_PRESSED==0)								//PAD 3
				{
				if(SM_PAD_COLOR[3]<4)
					{					
					SM_PAD_COLOR[3]++;
					}
				else
					{
					SM_PAD_COLOR[3] = 0;	
					}					
				if(SM_PAD_COLOR[3]==0)					//black
					{
					COLOR_SET(0x00000000, 3);	
					}		
				else if(SM_PAD_COLOR[3]==1)			//red
					{
					COLOR_SET(0x002F0000, 3);	
					}	
				else if(SM_PAD_COLOR[3]==2)			//green
					{
					COLOR_SET(0x00002F00, 3);	
					}	
				else if(SM_PAD_COLOR[3]==3)			//blue
					{
					COLOR_SET(0x0000002F, 3);	
					}
				else if(SM_PAD_COLOR[3]==4)			//white
					{
					COLOR_SET(0x002F2F2F, 3);	
					}						
				HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);	
				PAD_3_PRESSED = 1;	
				}	
			else if(HAL_GPIO_ReadPin(PAD_3_GPIO_Port, PAD_3_Pin)==0 && PAD_3_PRESSED==1)
				{
				PAD_3_PRESSED = 0;	
				}
			else if(HAL_GPIO_ReadPin(GPIOG, PAD_4_Pin)==1 && PAD_4_PRESSED==0)								//PAD 4
				{
				if(SM_PAD_COLOR[4]<4)
					{					
					SM_PAD_COLOR[4]++;
					}
				else
					{
					SM_PAD_COLOR[4] = 0;	
					}					
				if(SM_PAD_COLOR[4]==0)					//black
					{
					COLOR_SET(0x00000000, 4);	
					}		
				else if(SM_PAD_COLOR[4]==1)			//red
					{
					COLOR_SET(0x002F0000, 4);	
					}	
				else if(SM_PAD_COLOR[4]==2)			//green
					{
					COLOR_SET(0x00002F00, 4);	
					}	
				else if(SM_PAD_COLOR[4]==3)			//blue
					{
					COLOR_SET(0x0000002F, 4);	
					}
				else if(SM_PAD_COLOR[4]==4)			//white
					{
					COLOR_SET(0x002F2F2F, 4);	
					}						
				HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);
				PAD_4_PRESSED = 1;	
				}	
			else if(HAL_GPIO_ReadPin(GPIOG, PAD_4_Pin)==0 && PAD_4_PRESSED==1)
				{
				PAD_4_PRESSED = 0;	
				}	
			else if(HAL_GPIO_ReadPin(GPIOI, PAD_5_Pin)==1 && PAD_5_PRESSED==0)								//PAD 5
				{
				if(SM_PAD_COLOR[5]<4)
					{					
					SM_PAD_COLOR[5]++;
					}
				else
					{
					SM_PAD_COLOR[5] = 0;	
					}					
				if(SM_PAD_COLOR[5]==0)					//black
					{
					COLOR_SET(0x00000000, 5);	
					}		
				else if(SM_PAD_COLOR[5]==1)			//red
					{
					COLOR_SET(0x002F0000, 5);	
					}	
				else if(SM_PAD_COLOR[5]==2)			//green
					{
					COLOR_SET(0x00002F00, 5);	
					}	
				else if(SM_PAD_COLOR[5]==3)			//blue
					{
					COLOR_SET(0x0000002F, 5);	
					}
				else if(SM_PAD_COLOR[5]==4)			//white
					{
					COLOR_SET(0x002F2F2F, 5);	
					}						
				HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);	
				PAD_5_PRESSED = 1;	
				}	
			else if(HAL_GPIO_ReadPin(GPIOI, PAD_5_Pin)==0 && PAD_5_PRESSED==1)
				{
				PAD_5_PRESSED = 0;	
				}				
			else if(HAL_GPIO_ReadPin(PAD_6_GPIO_Port, PAD_6_Pin)==1 && PAD_6_PRESSED==0)								//PAD 6
				{
				if(SM_PAD_COLOR[6]<4)
					{					
					SM_PAD_COLOR[6]++;
					}
				else
					{
					SM_PAD_COLOR[6] = 0;	
					}					
				if(SM_PAD_COLOR[6]==0)					//black
					{
					COLOR_SET(0x00000000, 6);	
					}		
				else if(SM_PAD_COLOR[6]==1)			//red
					{
					COLOR_SET(0x002F0000, 6);	
					}	
				else if(SM_PAD_COLOR[6]==2)			//green
					{
					COLOR_SET(0x00002F00, 6);	
					}	
				else if(SM_PAD_COLOR[6]==3)			//blue
					{
					COLOR_SET(0x0000002F, 6);	
					}
				else if(SM_PAD_COLOR[6]==4)			//white
					{
					COLOR_SET(0x002F2F2F, 6);	
					}						
				HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);
				PAD_6_PRESSED = 1;	
				}	
			else if(HAL_GPIO_ReadPin(PAD_6_GPIO_Port, PAD_6_Pin)==0 && PAD_6_PRESSED==1)
				{
				PAD_6_PRESSED = 0;	
				}	
			else if(HAL_GPIO_ReadPin(PAD_7_GPIO_Port, PAD_7_Pin)==1 && PAD_7_PRESSED==0)								//PAD 7
				{
				if(SM_PAD_COLOR[7]<4)
					{					
					SM_PAD_COLOR[7]++;
					}
				else
					{
					SM_PAD_COLOR[7] = 0;	
					}					
				if(SM_PAD_COLOR[7]==0)					//black
					{
					COLOR_SET(0x00000000, 7);	
					}		
				else if(SM_PAD_COLOR[7]==1)			//red
					{
					COLOR_SET(0x002F0000, 7);	
					}	
				else if(SM_PAD_COLOR[7]==2)			//green
					{
					COLOR_SET(0x00002F00, 7);	
					}	
				else if(SM_PAD_COLOR[7]==3)			//blue
					{
					COLOR_SET(0x0000002F, 7);	
					}
				else if(SM_PAD_COLOR[7]==4)			//white
					{
					COLOR_SET(0x002F2F2F, 7);	
					}						
				HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);
				PAD_7_PRESSED = 1;	
				}	
			else if(HAL_GPIO_ReadPin(PAD_7_GPIO_Port, PAD_7_Pin)==0 && PAD_7_PRESSED==1)
				{
				PAD_7_PRESSED = 0;	
				}	
			}
		};		
	};	





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



