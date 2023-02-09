/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2022 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "dma2d.h"
#include "fatfs.h"
#include "i2c.h"
#include "ltdc.h"
#include "lwip.h"
#include "quadspi.h"
#include "sai.h"
#include "sdmmc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fmc.h"

/* USER CODE BEGIN Includes */

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		This firmware for F7 chip, 32F746G DISCOVERY board.
//		Added support for some Rekordbox functions, display of static and dynamic waveform, audio interpolation process. 
//
//		Added support for control buttons with led backlight.
//		IMPORTANT!!! 
//		After regenerating the code with Cube, make these corrections:
//		File sai.c
//		 - hsai_BlockA2.FrameInit.ActiveFrameLength = 32;
//
//		File dma2d.c, comment 2 lines:
//		 - //  hdma2d.LayerCfg[1].AlphaInverted = DMA2D_REGULAR_ALPHA;
//		 - //  hdma2d.LayerCfg[1].RedBlueSwap = DMA2D_RB_REGULAR;
//
//		File arm_math.h, add line:
//		 - #define ARM_MATH_CM7
//		init this functions after LCD_Layers initialization:	
//
//		Copy from backup this files:
//					- ethernetif.c
//					- ethernetif.h
//					- lwip.c
//					- lwip.h
//					- copy folder FatFs and FatFs files
//  	
//		
//			File \F7 XDJ_PANEL\Drivers\BSP\STM32746G-Discovery\stm32746g_discovery_lcd.c
//				- //HAL_GPIO_WritePin(LCD_BL_CTRL_GPIO_PORT, LCD_BL_CTRL_PIN, GPIO_PIN_SET);      //300 line
//
//
//  		File main.c CHANGE VALUE PeriphClkInitStruct.PLLI2S.PLLI2SN = 271;			//135 old
//
//			Delete MX_LWIP_Init() in TOP!
//
//		Compilator settings:	
//
//--c99 -c --cpu Cortex-M7.fp.sp -D__MICROLIB -g -O1 --apcs=interwork --split_sections -I../Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I..\Drivers\BSP\STM32746G-Discovery -I..\Drivers\BSP\Components\rk043fn48h -I..\Drivers\BSP\Components\Common -I..\Utilities\CPU -I..\Utilities\Fonts -I..\Utilities\Log -I../Middlewares/Third_Party/FatFs/src/drivers -I../Middlewares/Third_Party/FatFs/src --C99 
//-I "C:\Keil_v5\My_Project\F7 XDJ_PANEL\MDK-ARM\RTE" 
//-I C:\Keil_v5\ARM\PACK\ARM\CMSIS\4.5.0\CMSIS\Include 
//-I C:\Keil_v5\ARM\PACK\Keil\STM32F7xx_DFP\2.11.0\Drivers\CMSIS\Device\ST\STM32F7xx\Include 
//-D__UVISION_VERSION="517" -D_RTE_ -DSTM32F746xx -DUSE_HAL_DRIVER -DSTM32F746xx -o "F7\*.o" --omf_browse "F7\*.crf" --depend "F7\*.d" 
//
//		generated by:
//			STM32CubeMX 4.22.0
//			STM32Cube FW_F7 V1.7.0
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	ver. 0.35
//		- added all periph buttons, leds, VRs and encoder
//	ver. 0.36
//		- added buttons handler
//	ver. 0.37
//		- added USB USART debug code
//		- added first service mode 
//	ver. 0.38
//		- improved encoder noise canceller code
//	ver. 0.41
//		- added service mode code parts
//		-	added ADCs VRs code with hysteresis and filter
//	ver. 0.45
//		- added service mode code parts
//	ver. 0.46
//		- fixed SERVICE MODE code
//	ver. 0.47
//		- added sync out led blink
//	ver. 0.48
//		- the signals from the pads are inverted, the pullups are replaced with pulldowns. It is also changed in the hardware
//	ver. 0.49
//		-	added PWM backlight
//	ver. 0.51
//		-	added PRESETS select display
//	ver. 0.53
//		-	added reading preset preview pads color, rating
//		-	added loading presets from preset list
//		-	added long blink encoder led if the preset is loaded for a very long time 
//	ver. 0.54
//		-	added color instruments icons
//		-	added shadow at the rating stars
//	ver. 0.57
//		-	added sync pitch 
//		-	added imitate deck mode
//		- added blink pads
//	ver. 0.61
//		-	added dynamic timeline on waveforms 
//		-	added colored CUE points and colored samle name
//	ver. 0.63
//		-	added first sequencer
//	ver. 0.65
//		-	minor fixes for the GUI sequencer
//		- added status bar with playback status
//		- added icons for effect and sync. out
//	ver. 0.67
//		-	added on-off pads label
//	ver. 0.68
//		-	minor fixes GUI
//	ver. 0.70
//		-	fixed pad1 RGB led problem
//		-	minor fixes
//	ver. 0.72
//		-	minor GUI fixes
//		- added UTILITY window
//		- added master bpm shield
//	ver. 0.73
//		- added timestamp for pads press moments and filter 
//		-	added ATT_LV for pads
//	ver. 0.74
//		- changed "+" symbol in 15P font
//		-	minol fixes in gui preset list
//		-	added gui.h and audio.h
//	ver. 0.77
//		- added EDIT PRESER window
//		- changed SYNC OUT and EFFECT GUI gray color
//	ver. 0.79
//		- improved debug mode
//		- added interrupt for received uart
//	ver. 0.80
//		-	added processing to the EDIT for the encoder button
//		- changed project structure main.c file is split into many * .h files
//	ver. 0.81
//		-	added preset list edit menu
//	ver. 0.87
//		-	added DELETE DIALOG
//		-	added encoder_handler.h, key_handler.h
//		- improved  DELETE DIALOG
//		-	added noise filter for encoder button
//	ver. 0.88
//		- fixed fixed bugs in GUI UTILITY
//		- improved GUI preset list
//		- improved the mechanism for creating screenshots, using both layers
//	ver. 0.89
//		- improved configuration in ffconf.h
//	ver. 0.90
//		- improved preset list gui
//	ver. 0.91
//		- improved UTILITY
//		- add edit pad display, edit preset display, edit FL display
//	ver. 0.94
//		- improved UTILITY id address set
//	ver. 0.98
//		- added utility edit menu
//		- added internal bpm generator
//	ver. 1.06
//		- added write uSD prc
//	ver. 1.09
//		- added edit preset display
//		- added write preset uSD prc 
//		- added keyboard and rename prc		
//		- added keyboard animation	
//	ver. 1.17
//		- added blinking cursor for kyeboard
//		- added waveform editor
//		- improved edit pad display gui
//		- improved home display gui
//		- added simple waveform analyzer
//	ver. 1.19
//		- improved edit pad display
//		- added prompt for edit pad display
//		- added prompt for edit preset display
//		- added first BROWSER display
//	ver. 1.23
//		- replaced FATFS lib! (previous lib not work USE_LFN for READDIR)
//	ver. 1.25
//		- fixed display of sample names inside folders. Folder removed from title bar
//		- fixed edit pad GUI bugs
//		- added realtime pad color update when editing a pad
//	ver. 1.26
//		- fixed ethernetif.c beat process for external sync
//		- added FLLIST_DISPLAY
//	ver. 1.28
//		- added sequence editor
//	ver. 1.31
//		-	minor fixes
//		-	added [folder] style in BROWSER display
//		-	added dynamic pad in edit pad display gui
//	ver. 1.33
//		-	added first FL presets animation
//	ver. 1.34
//		-	improved FL presets animation
//	ver. 1.35
//		-	added "create new preset" and "create duplicate" process
//	ver. 1.36
//		-	improved "create new preset" and "create duplicate" process
//		- added "preset list is full" and "error x" msg
//		- added automaticly wzoom for waveform
//	ver. 1.37
//		- added noise filters for buttons PRESET, SHIFT, EDIT, BACK, EFFECT
//	ver. 1.39
//		-	added delete prc
//		- fixed display of MAC-address in service mode
//	ver. 1.40
//		- fixed delete prc
//	ver. 1.42
//		- work on the edit fl list
//	ver. 1.43
//		- new FL preset load animation
//	ver. 1.44
//		- added background picture on edit preset display
//		- added FIR filter in WFMCREATE()
//	ver. 1.47
//		-	improved WFMCREATE(), FIR and analising algorythm
//		- the algorithm for displaying a big waveform has been changed
//		-	added a mechanism for creating a template Presets.pst file on an empty sd card
//	ver. 1.48
//		-	changed color map for big waveform (colors from cdj dump)
//	ver. 1.51
//		-	fixed a bug: where inactive pads in the edit_pad_display would start glowing after the pad_x being edited was stopped
//		-	improved edit_pad_display
//	ver. 1.55
//		-	bug fixes in the function REDRAW_PAD_EDIT()
//		- added first move preset display
//	ver. 1.56
//		-	bug fixes in the MOVE_PRESET	
//		-	first move_preser_prc
//	ver. 1.57
//		-	improved move_preser_prc	
//	ver. 1.59
//		-	bug fixes in the function REDRAW_PAD_EDIT()
//		-	added new icons for presets
//	ver. 1.60
//		-	added new icons for presets
//	ver. 1.61
//		-	changed PLL frequency multiplier PeriphClkInitStruct.PLLI2S.PLLI2SN = 271 (135 old)
//	ver. 1.65
//		-	quantize first
//	ver. 1.68
//		-	improved quantize process
//		-	minor fixes
//		-	added first effects
//	ver. 1.69
//		-	improved trans effect process
//	ver. 1.70
//		-	optimized and improved trans effect process
//	ver. 1.71
//		-	added ram fill percentage status
//	ver. 1.73
//		-	optimized HAL_SAI_Transmit_IT
//		-	added uart sync out signal
//	ver. 1.74
//		-	bug fixed in audio handler limiting play_adr size at 0xFFFFF
//		- added errors descriptor
//		-	bug fixed in waveform color draw_st_wvfm()
//	ver. 1.75
//		- changed the principle of operation of SPI2 for PADS LEDs. Now SPI2 works via DMA.
//	ver. 1.77
//		- improved performance of Moog Filter and LPF
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_lcd.h"
//#include "ff.h"
#include "wm8994.h"


/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
#include <math.h>
#include "arm_math.h"
#include "skins.h"
#include "logo.h"
#include "ft5336.h"
#include "stm32746g_discovery_qspi.h"
#include "lwip/udp.h"
#include "net.h"

#include "global_variables.h"


char FIRMWARE_VERSION[] = "1.77";								
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
void GET_SD_INFO(void);								//check used and free memory on sd card
#include "dac.h"
void ReDrawScroll(uint16_t total_elements, uint16_t current_element_pos);
void COLOR_SET(uint32_t color, uint8_t LD);									//set colors for PADS in color ram	
uint8_t LOAD_PRESET_LIST(void);															//load presets list, utility. return error
uint8_t LOAD_PRESET(uint8_t pst_num);												//load preset. return error
void PREPARE_ERR_MSG(uint8_t er);														//prepare error message string
uint8_t LOAD_ONE_PAD(uint8_t pst_num);											//load one pad for pad edit. return error
void SwitchInformationLayer(uint8_t LAY);										//Switch display layers
#include "utility.h"	
void intDrawTriangle(uint8_t CCP); 																//draw triangle for browser with INFO
void NAVIGATOR(uint8_t UPDOWN);																		//Navigate preset list, UTILITY and other
uint16_t CREATE_SCREEN(void);																			//univrsal function for creating current screenshots. return screen number
void int_DRAW_STARS_RATING(uint8_t rat, uint8_t rat_color, uint8_t pos);	//draw rating in preset list
void int_DRAW_ICO(uint8_t ICO_NUMB, uint8_t col, uint8_t pos);		//draw icons
void int_pad_handler(uint8_t PAD);																//internal for pads
void Draw_Static_Pads(void);																			//draw static gui pads for home display
void REDRAW_PAD(uint8_t pad);																			//redraw dynamic pad's GUI
void REDRAW_PAD_EDIT(uint8_t pad);																//redraw dynamic pad's in GUI edit pad
void CREATE_GUI_STYLE_COLOR(uint32_t color);											//create gui table color
uint32_t CREATE_PIC_COLOR(uint32_t col);													//create color for picture

#include "edit_fl_list.h"
#include "fat_process.h"
#include "waveformanalyzer.h"
#include "sync_mode_upd.h"
#include "edit_list_gui.h"
#include "edit_preset_gui.h"
#include "delete_dialog_gui.h"
#include "guifunc.h"
#include "edit_pad_display.h"
#include "audio_handler.h"
#include "service_mode.h"
#include "edit_preset_display.h"
#include "keyboard.h"
#include "browser.h"
#include "key_handler.h"
#include "encoder_handler.h"
#include "preset_list.h"
#include "move_preset.h"
#include "edit_utility_gui.h"
#include "slide_fl_pads.h"



/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* Enable I-Cache-------------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache-------------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_DMA2D_Init();
  MX_FMC_Init();
  MX_LTDC_Init();
  MX_SDMMC1_SD_Init();
  MX_FATFS_Init();
  MX_I2C3_Init();
  MX_SAI2_Init();
  MX_QUADSPI_Init();
  MX_USART1_UART_Init();
  //MX_LWIP_Init();
  MX_TIM2_Init();
  MX_SPI2_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_ADC3_Init();
  MX_TIM14_Init();
  MX_TIM5_Init();

  /* USER CODE BEGIN 2 */

  //delete MX_LWIP_Init() in TOP!

	////////preparing massives
	for(mi=0;mi<15;mi++)
		{
		UTILITY_BASE[mi][19] = 0;	
		}
	for(mi=0;mi<11;mi++)
		{
		EP_BASE[mi][7] = 0;	
		}
	for(mi=0;mi<5;mi++)
		{
		EL_BASE[mi][16] = 0;
		}
	for(mi=0;mi<2;mi++)
		{
		DD_BASE[mi][3] = 0;
		}	
	for(mi=0;mi<4;mi++)
		{
		EU_BASE[mi][14] = 0;
		}	
	for(mi=0;mi<8;mi++)
		{
		EPD_BASE[mi][8] = 0;
		}		
		
	DEVICE_UID = *(unsigned long*)(0x1FF0F420);							//Read device ID
	
	#if defined(USART_DEBUG)
		USART1->CR1 |= USART_CR1_RXNEIE; //interrupt for a RX enable
	#endif	
	
	if(HAL_GPIO_ReadPin(KEY_PRESET_GPIO_Port, KEY_PRESET_Pin)==0 && HAL_GPIO_ReadPin(GPIOD, KEY_EFFECT_Pin)==0 &&							//Check service mode combination
		HAL_GPIO_ReadPin(GPIOB, KEY_SHIFT_Pin)==1 && HAL_GPIO_ReadPin(GPIOB, KEY_EDIT_Pin)==1 &&
		HAL_GPIO_ReadPin(GPIOF, KEY_MENU_Pin)==1 && HAL_GPIO_ReadPin(GPIOD, KEY_BACK_Pin)==1 &&
		HAL_GPIO_ReadPin(KEY_SYNC_OUT_GPIO_Port, KEY_SYNC_OUT_Pin)==1 && HAL_GPIO_ReadPin(GPIOF, KEY_ENC_Pin)==1)
		{
		SERVICE_MODE_ENABLE++;	
		}
	for(mi=0;mi<8;mi++)
		{	
		COLOR_SET(PIO_PAD_COLOR, mi);
		}
	HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);	
	HAL_Delay(5);	
	HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);	
	
	HAL_TIM_Base_Start_IT(&htim5);				//ENCODER
		
	TIM14->CCR1 = 0;		//PWM BLACKLIGHT
	HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);		//PWM BLACKLIGHT
	
	if(HAL_GPIO_ReadPin(KEY_PRESET_GPIO_Port, KEY_PRESET_Pin)==0 && HAL_GPIO_ReadPin(GPIOD, KEY_EFFECT_Pin)==0 &&							//Check service mode combination
		HAL_GPIO_ReadPin(GPIOB, KEY_SHIFT_Pin)==1 && HAL_GPIO_ReadPin(GPIOB, KEY_EDIT_Pin)==1 &&
		HAL_GPIO_ReadPin(GPIOF, KEY_MENU_Pin)==1 && HAL_GPIO_ReadPin(GPIOD, KEY_BACK_Pin)==1 &&
		HAL_GPIO_ReadPin(KEY_SYNC_OUT_GPIO_Port, KEY_SYNC_OUT_Pin)==1 && HAL_GPIO_ReadPin(GPIOF, KEY_ENC_Pin)==1)
		{
		SERVICE_MODE_ENABLE++;	
		}
	
	HAL_GPIO_WritePin(GPIOB, LED_ENC_Pin|LED_SHIFT_Pin, GPIO_PIN_SET);										//////////////////////////////
	HAL_GPIO_WritePin(GPIOA, LED_PRESET_Pin|LED_EFFECT_Pin, GPIO_PIN_SET);								//
	HAL_GPIO_WritePin(LED_SYNC_OUT_GPIO_Port, LED_SYNC_OUT_Pin, GPIO_PIN_SET);						//			turn on leds
	HAL_GPIO_WritePin(GPIOI, LED_EDIT_Pin, GPIO_PIN_SET);																	//
	HAL_GPIO_WritePin(LED_MENU_GPIO_Port, LED_MENU_Pin, GPIO_PIN_SET);										//////////////////////////////
	
	BSP_QSPI_Init();
  BSP_QSPI_MemoryMappedMode();
	WRITE_REG(QUADSPI->LPTR, 0xFFF);

	BSP_SD_Init();
		
	lcd_status = BSP_LCD_Init();
	BSP_LCD_LayerDefaultInit(0, LCD_FRAME_BUFFER);
	BSP_LCD_LayerDefaultInit(1, LCD_FRAME_BUFFER_2);
	
	BSP_LCD_SelectLayer(1);
	BSP_LCD_Clear(0x00000000);					//higher layer filling a transparent color
	BSP_LCD_SetTransparency(1, 255);	
	BSP_LCD_SelectLayer(0);
	BSP_LCD_SetTransparency(0, 255);
	BSP_LCD_Clear(LCD_COLOR_BLACK);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	HAL_Delay(200);		//500	
	HAL_TIM_Base_Start_IT(&htim2);									//start timer
	HAL_Delay(200);		//500

	if(HAL_GPIO_ReadPin(KEY_PRESET_GPIO_Port, KEY_PRESET_Pin)==0 && HAL_GPIO_ReadPin(GPIOD, KEY_EFFECT_Pin)==0 &&							//Check service mode combination
		HAL_GPIO_ReadPin(GPIOB, KEY_SHIFT_Pin)==1 && HAL_GPIO_ReadPin(GPIOB, KEY_EDIT_Pin)==1 &&
		HAL_GPIO_ReadPin(GPIOF, KEY_MENU_Pin)==1 && HAL_GPIO_ReadPin(GPIOD, KEY_BACK_Pin)==1 &&
		HAL_GPIO_ReadPin(KEY_SYNC_OUT_GPIO_Port, KEY_SYNC_OUT_Pin)==1 && HAL_GPIO_ReadPin(GPIOF, KEY_ENC_Pin)==1)
		{
		SERVICE_MODE_ENABLE++;	
		}
		
	BSP_LCD_DisplayOn();	
	HAL_Delay(100);					//need for display full init	
	TIM14->CCR1 = 48+(52*3);		//PWM BLACKLIGHT (3)		
	DrawLOGO();
	HAL_Delay(300);
	DAC_Init_and_Start(100);											/////Start AUDIO PROCESSING
	
	HAL_GPIO_WritePin(GPIOB, LED_SHIFT_Pin, GPIO_PIN_RESET);															//////////////////////////////
	HAL_GPIO_WritePin(GPIOA, LED_PRESET_Pin, GPIO_PIN_RESET);															//
	HAL_GPIO_WritePin(LED_SYNC_OUT_GPIO_Port, LED_SYNC_OUT_Pin, GPIO_PIN_RESET);					//			turn off leds
	HAL_GPIO_WritePin(GPIOI, LED_EDIT_Pin, GPIO_PIN_RESET);																//
	HAL_GPIO_WritePin(LED_MENU_GPIO_Port, LED_MENU_Pin, GPIO_PIN_RESET);									//////////////////////////////		
			
	if(HAL_GPIO_ReadPin(KEY_PRESET_GPIO_Port, KEY_PRESET_Pin)==0 && HAL_GPIO_ReadPin(GPIOD, KEY_EFFECT_Pin)==0 &&							//Check service mode combination
		HAL_GPIO_ReadPin(GPIOB, KEY_SHIFT_Pin)==1 && HAL_GPIO_ReadPin(GPIOB, KEY_EDIT_Pin)==1 &&
		HAL_GPIO_ReadPin(GPIOF, KEY_MENU_Pin)==1 && HAL_GPIO_ReadPin(GPIOD, KEY_BACK_Pin)==1 &&
		HAL_GPIO_ReadPin(KEY_SYNC_OUT_GPIO_Port, KEY_SYNC_OUT_Pin)==1 && HAL_GPIO_ReadPin(GPIOF, KEY_ENC_Pin)==1)
		{
		SERVICE_MODE_ENABLE++;	
		}
		
	if(SERVICE_MODE_ENABLE==4)				//ENTER TO SERVICE MODE
		{
		MX_LWIP_Init();	
		SERVICE_MODE();	
		}
		
	BSP_LCD_Clear(LCD_COLOR_BLACK);
	int_DRAW_TRANSPARENT_BAR();		
	BSP_LCD_SelectLayer(1);			
	BSP_LCD_Clear(0x00000000);	
	BSP_LCD_SetTransparency(1, 255);
	BSP_LCD_SelectLayer(0);
	
	BSP_LCD_SetFont(&Font8);	
	if(HAL_GPIO_ReadPin(uSD_Detect_GPIO_Port, uSD_Detect_Pin)==0)
		{
		SwitchInformationLayer(HOME_DISPLAY);	
		res = f_mount(&FAT, "0", 1);
		if (res!=FR_OK)
			{
			BSP_LCD_SetTextColor(LCD_COLOR_RED);	
			sprintf((char*)Buf, "%s", "Disc not mounted!");
			BSP_LCD_DisplayStringAt(180, 52,Buf, LEFT_MODE);	
			HAL_Delay(1000);		
			NVIC_SystemReset();							//reset system
			}
		else
			{
			GET_SD_INFO();
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);	
			sprintf((char*)Buf, "%s", "Disc mount OK!");
			BSP_LCD_DisplayStringAt(180, 52,Buf, LEFT_MODE);	
			}	
		mi = LOAD_PRESET_LIST(); 	
		if(mi!=0)				//error load preset list	
			{
			if(mi==15 || mi==16)	//cannot read file presets.pst or cannot open file presets.pst (need create a new file presets.pst)			
				{
				BSP_LCD_SetTextColor(LCD_COLOR_RED);	
				sprintf((char*)Buf, "%s", "File Presets.pst not available");
				BSP_LCD_DisplayStringAt(140, 52, Buf, LEFT_MODE);	
				HAL_Delay(2500);
				sprintf((char*)Buf, "%s", "A new Presets.pst file will be created");
				BSP_LCD_DisplayStringAt(130, 52, Buf, LEFT_MODE);	
				HAL_Delay(2500);		
				if(newpstfile()==0)
					{
					if(LOAD_PRESET_LIST()!=0)				//repeat error...
						{
						BSP_LCD_SetTextColor(LCD_COLOR_RED);	
						sprintf((char*)Buf, "%s", "Presets.pst error");
						BSP_LCD_DisplayStringAt(180, 52, Buf, LEFT_MODE);	
						HAL_Delay(2500);
						CURRENT_PRESET = 0xFF;					//current preset	
						while(1)	
							{
							}		
						}	
					}
				else
					{
					BSP_LCD_SetTextColor(LCD_COLOR_RED);	
					sprintf((char*)Buf, "%s", "SD card error");
					BSP_LCD_DisplayStringAt(180, 52, Buf, LEFT_MODE);	
					HAL_Delay(2500);
					CURRENT_PRESET = 0xFF;					//current preset	
					while(1)	
						{
						}	
					}
				}
			else
				{
				BSP_LCD_SetTextColor(LCD_COLOR_RED);	
				sprintf((char*)Buf, "%s", "Presets.pst error");
				BSP_LCD_DisplayStringAt(180, 52, Buf, LEFT_MODE);	
				HAL_Delay(2500);
				CURRENT_PRESET = 0xFF;					//current preset	
				while(1)	
					{
					}
				}
			}
		CURRENT_PRESET = UTILITY_SETTINGS[0];
		TIM14->CCR1 = 48+(52*UTILITY_SETTINGS[6]);		//PWM BLACKLIGHT FROM SD
		MX_LWIP_Init();
		HAL_Delay(500);			
		BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);	
		sprintf((char*)Buf, "%s%1lu", "Load preset ", CURRENT_PRESET+1);
		BSP_LCD_DisplayStringAt(180, 52,Buf, LEFT_MODE);	
		HAL_Delay(500);
			
		udp_client_connect();							//PRO DJ LINK connect
			
		ENCODER_LED_BLINK = 0;	//start encoder blink
		END_BLINK = 0;					//end encoder blink disable
		for(mi=0;mi<8;mi++)
			{
			COLOR_SET(0, mi);					
			}
		HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);	
		load_status = LOAD_PRESET(CURRENT_PRESET); 
		if(load_status!=0)					//error
			{	
			UTILITY_SETTINGS[0] = 0xFF;			//current preset	
			CURRENT_PRESET = 0xFF;					//current preset		
			}
		dSHOW = 0xFF;	
		SwitchInformationLayer(HOME_DISPLAY);	
		if(load_status!=0)						//error
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
			}					
		}
	else
		{
		SwitchInformationLayer(HOME_DISPLAY);		
		BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);	
		sprintf((char*)Buf, "%s", "Insert micro SD card");
		BSP_LCD_DisplayStringAt(180, 52,Buf, LEFT_MODE);		
		}
	HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);	
	int_sync_mode_upd();			//update sync mode		
	if(HAL_GPIO_ReadPin(uSD_Detect_GPIO_Port, uSD_Detect_Pin)==1)			//uSD card disable
		{
		while(1)
			{
			}
		}			
		
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
 while (1)
  {			
	MX_LWIP_Process(); 				//ethernet process
		
	if(UDP_NEED_UPDATE_SPHASE)
		{	
		if(dSHOW==HOME_DISPLAY)
			{
			ShowSPhaseMeter(BEAT_CNT);		
			}		
		UDP_NEED_UPDATE_SPHASE = 0;	
		}	

	if(UDP_NEED_UPDATE_MPHASE)
		{	
		if(dSHOW==HOME_DISPLAY)
			{	
			ShowMPhaseMeter(UDP_MPHASE-1, UDP_MPHASE_CNT);
			}				
		UDP_NEED_UPDATE_MPHASE = 0;	
		}	
	
	if(UDP_NEED_UPDATE_BPM)	
		{
		if(dSHOW==HOME_DISPLAY)
			{
			ShowBPM(UDP_BPM);
			}
		SQN[0] = 1500000/(UDP_BPM+5); 	
		SQN[1] = 3000000/(UDP_BPM+5);	
		SQN[2] = 4500000/(UDP_BPM+5);
		if(ACTIVE_PAD<8)
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
			}
		UDP_NEED_UPDATE_BPM = 0;		
		}
		
	if(UDP_NEED_UPDATE_MD)	
		{
		if(dSHOW==HOME_DISPLAY)
			{	
			ShowMasterDeck(UDP_MD);
			}				
		UDP_NEED_UPDATE_MD = 0;
		}
		
	if(link_status!=previous_link_status)										
		{
		previous_link_status = link_status;	
		if(dSHOW==HOME_DISPLAY)
			{
			ShowLinkNumb(link_status);
			}
			
		if(link_status==1)
			{
			if(send_connect==0)
				{
				udp_client_connect();
				send_connect = 1;	
				}
			if(SYNC_OUT_ON)
				{
				HAL_GPIO_WritePin(LED_SYNC_OUT_GPIO_Port, LED_SYNC_OUT_Pin, GPIO_PIN_SET);	
				}
			else
				{
				HAL_GPIO_WritePin(LED_SYNC_OUT_GPIO_Port, LED_SYNC_OUT_Pin, GPIO_PIN_RESET);	
				}				
			}
		else if(link_status==0)
			{
			if(dSHOW==HOME_DISPLAY)
				{
				if(UTILITY_SETTINGS[3]!=0)		//external bpm clock
					{
					ShowBPM(0xFFFFFFFF);
					ShowMasterDeck(0);
					ShowSPhaseMeter(0xFF);
					ShowMPhaseMeter(0xFF, 0x01FF);				
					}				
				}
			if(SYNC_OUT_ON)
				{
				HAL_GPIO_WritePin(LED_SYNC_OUT_GPIO_Port, LED_SYNC_OUT_Pin, GPIO_PIN_SET);	
				}
			else
				{
				HAL_GPIO_WritePin(LED_SYNC_OUT_GPIO_Port, LED_SYNC_OUT_Pin, GPIO_PIN_RESET);	
				}	
			}
		else if(link_status==2)
			{	
			UDP_NEED_UPDATE_BPM = 1;	
			UDP_NEED_UPDATE_MD = 1;
			HAL_GPIO_WritePin(LED_SYNC_OUT_GPIO_Port, LED_SYNC_OUT_Pin, GPIO_PIN_RESET);	
			}
		}		
	
	if(dSHOW==HOME_DISPLAY)
		{	
		REDRAW_PAD(ACTIVE_PAD);
		if((ACTIVE_PAD<8) && (show_status_string==0 || show_status_string==0xFF))						//draw status
			{
			BSP_LCD_SelectLayer(1);
			BSP_LCD_SetTextColor(0x00000000);
			BSP_LCD_DrawVLine(467, 5, 7);		
			BSP_LCD_DrawVLine(468, 5, 7);	
			BSP_LCD_DrawVLine(472, 5, 7);		
			BSP_LCD_DrawVLine(473, 5, 7);					
			BSP_LCD_SetTextColor(LCD_COLOR_GREEN);	
			FillTriangle(467, 467, 472, 3, 13, 8);				
			BSP_LCD_SelectLayer(0);	
			show_status_string = 1;	
			}
		else if(ACTIVE_PAD>7 && (show_status_string==1 || show_status_string==0xFF))						//clear status
			{
			BSP_LCD_SelectLayer(1);
			BSP_LCD_SetTextColor(0x00000000);	
			FillTriangle(467, 467, 472, 3, 13, 8);
			if(CURRENT_PRESET<64)
				{				
				BSP_LCD_SetTextColor(CUE_COLOR);
				BSP_LCD_DrawVLine(467, 5, 7);		
				BSP_LCD_DrawVLine(468, 5, 7);	
				BSP_LCD_DrawVLine(472, 5, 7);		
				BSP_LCD_DrawVLine(473, 5, 7);		
				}
			BSP_LCD_SelectLayer(0);		
			show_status_string = 0;	
			}
			
		if(need_redraw_effect)
			{
			if(EFFECT_ON)
				{
				ShowEFFECT(2);		
				}	
			else
				{
				ShowEFFECT(1);		
				}
			need_redraw_effect = 0;	
			}			
			
		if(need_redraw_syncout)
			{
			if(SYNC_OUT_ON)
				{
				ShowSYNCOUT(2);	
				}
			else
				{
				ShowSYNCOUT(1);	
				}				
			need_redraw_syncout = 0;	
			}					
		}
	else if(dSHOW==KEYBOARD)
		{
		if((HAL_GetTick() - cursor_tim)>500)
			{
			cursor_tim = HAL_GetTick();	
			int_blinking_cursor();	
			}			
		}
	else if(dSHOW==EDIT_PAD_DISPLAY)
		{	
		if(edit_epd_parameter==1 && P_TYPE[pad_x-1]==1 && EPD_Position==10)
			{	
			if(ACTIVE_PAD<8)
				{
				REDRAW_PAD_EDIT(ACTIVE_PAD);	
				}
			}
		else
			{
			REDRAW_PAD_EDIT(ACTIVE_PAD);				
			}
		if(ACTIVE_PAD<8 && (show_status_string==0 || show_status_string==0xFF))						//draw status
			{
			BSP_LCD_SelectLayer(1);
			BSP_LCD_SetTextColor(0x00000000);
			BSP_LCD_DrawVLine(467, 5, 7);		
			BSP_LCD_DrawVLine(468, 5, 7);	
			BSP_LCD_DrawVLine(472, 5, 7);		
			BSP_LCD_DrawVLine(473, 5, 7);			
			BSP_LCD_SetTextColor(LCD_COLOR_GREEN);	
			FillTriangle(467, 467, 472, 3, 13, 8);				
			BSP_LCD_SelectLayer(0);	
			show_status_string = 1;	
			}
		else if(ACTIVE_PAD>7 && (show_status_string==1 || show_status_string==0xFF))						//clear status
			{
			BSP_LCD_SelectLayer(1);
			BSP_LCD_SetTextColor(0x00000000);	
			FillTriangle(467, 467, 472, 3, 13, 8);		
			if(P_COLOR[pad_x-1]<8)
				{						
				BSP_LCD_SetTextColor(CUE_COLOR);
				BSP_LCD_DrawVLine(467, 5, 7);		
				BSP_LCD_DrawVLine(468, 5, 7);	
				BSP_LCD_DrawVLine(472, 5, 7);		
				BSP_LCD_DrawVLine(473, 5, 7);
				}					
			BSP_LCD_SelectLayer(0);		
			show_status_string = 0;	
			}		
		}
	else if(dSHOW==FLLIST_DISPLAY)
		{
		if(need_slide_pads>0)						//slide pads process
			{
			current_slide_time = HAL_GetTick() - start_slide_time;	
			current_slide_time*=1600;
			current_slide_time = current_slide_time>>10;		
			if(need_slide_pads==1)
				{				
				if(current_slide_time>134)
					{
					current_slide_time = 134;	
					for(mi=0;mi<8;mi++)
						{
						if(FAST_LOADING[mi]>63)
							{	
							COLOR_SET(EMPTY_PAD, mi);			//none FL pad	
							}
						else
							{
							COLOR_SET(PADS_L_COLOR[presets_color[FAST_LOADING[mi]]], mi);		
							}					
						}
					HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);	
					need_slide_pads = 2;	
					}
				SLIDE_PAD(previous_frame, 6, 0);	
				SLIDE_PAD(current_slide_time, 6, 1);	
				SLIDE_PAD(previous_frame, 5, 0);	
				SLIDE_PAD(current_slide_time, 5, 1);			
				SLIDE_PAD(previous_frame, 1, 0);	
				SLIDE_PAD(current_slide_time, 1, 1);				
				SLIDE_PAD(previous_frame, 2, 0);	
				SLIDE_PAD(current_slide_time, 2, 1);			
				SLIDE_PAD(previous_frame, 0, 0);	
				SLIDE_PAD(current_slide_time, 0, 1);	
				SLIDE_PAD(previous_frame, 3, 0);	
				SLIDE_PAD(current_slide_time, 3, 1);
				SLIDE_PAD(previous_frame, 4, 0);	
				SLIDE_PAD(current_slide_time, 4, 1);
				SLIDE_PAD(previous_frame, 7, 0);	
				SLIDE_PAD(current_slide_time, 7, 1);
				previous_frame	= current_slide_time;	
				}
			else if(need_slide_pads==2)
				{
				BSP_LCD_SelectLayer(1);
				BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
				BSP_LCD_FillRect(0,	0,	480, 33);
				BSP_LCD_FillRect(0,	239,	480, 33);	
				BSP_LCD_FillRect(0,	134,	480, 4);
				BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
				BSP_LCD_SetFont(&Font15P);
				sprintf((char*)Buf, "%s", "FAST LOAD PRESETS");		
				BSP_LCD_DisplayStringAt(155, 0, Buf, TRANSPARENT_MODE);	
				BSP_LCD_SetTextColor(LCD_COLOR_BLACK);	
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
				int_real_color_pads();
				need_slide_pads = 3;	
				}	
			else if(need_slide_pads==3)
				{
				need_slide_pads = 4;	
				}
			else if(need_slide_pads==4)
				{
				need_slide_pads = 5;	
				}
			else if(need_slide_pads==5)
				{
				need_slide_pads = 6;	
				}
			else if(need_slide_pads==6)
				{
				BSP_LCD_SelectLayer(1);		
				BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
				BSP_LCD_SetFont(&Font15P);
				sprintf((char*)Buf, "%s", "FAST LOAD PRESETS");		
				BSP_LCD_DisplayStringAt(155, 0, Buf, TRANSPARENT_MODE);		
				BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
				BSP_LCD_DisplayStringAt(155, 9, Buf, TRANSPARENT_MODE);		
				need_slide_pads = 0;	
				}	
			}	
		else if(need_reslide_pads>0)						//reslide pads process
			{
			current_slide_time = HAL_GetTick() - start_slide_time;	
			current_slide_time*=1600;
			current_slide_time = current_slide_time>>10;				
			if(current_slide_time<135)
				{	
				current_slide_time = 134-current_slide_time;
				}
			else
				{
				current_slide_time = 0;
				need_reslide_pads = 0;	
				}
			SLIDE_PAD(previous_frame, 6, 0);	
			SLIDE_PAD(current_slide_time, 6, 1);	
			SLIDE_PAD(previous_frame, 5, 0);	
			SLIDE_PAD(current_slide_time, 5, 1);			
			SLIDE_PAD(previous_frame, 1, 0);	
			SLIDE_PAD(current_slide_time, 1, 1);				
			SLIDE_PAD(previous_frame, 2, 0);	
			SLIDE_PAD(current_slide_time, 2, 1);			
			SLIDE_PAD(previous_frame, 0, 0);	
			SLIDE_PAD(current_slide_time, 0, 1);	
			SLIDE_PAD(previous_frame, 3, 0);	
			SLIDE_PAD(current_slide_time, 3, 1);
			SLIDE_PAD(previous_frame, 4, 0);	
			SLIDE_PAD(current_slide_time, 4, 1);
			SLIDE_PAD(previous_frame, 7, 0);	
			SLIDE_PAD(current_slide_time, 7, 1);
			previous_frame	= current_slide_time;	
			if(current_slide_time==0)
				{
				for(mi=0;mi<8;mi++)		/////////////////////redraw LEDS in PADs
					{
					if(P_COLOR[mi]==0xFF)
						{
						COLOR_SET(EMPTY_PAD, mi);			//none FL pad	
						}
					else
						{
						COLOR_SET(PADS_L_COLOR[P_COLOR[mi]], mi);	
						}		
					}				
				need_load_rgb = 1;
				after_fl = 1;	
				SwitchInformationLayer(HOME_DISPLAY);	
				}
			}	
		}		
		
	if(dSHOW!=HOME_DISPLAY && dSHOW!=EDIT_PAD_DISPLAY)	
		{
		show_status_string = 0xFF;
		}

	if(need_fastload_preset<8)				//fast loading preset
		{
		if(FAST_LOADING[need_fastload_preset]<64)				//have a FL preset
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
				if(mi==need_fastload_preset)
					{
					COLOR_SET(PADS_H_COLOR[presets_color[FAST_LOADING[need_fastload_preset]]], mi);	
					}
				else
					{
					COLOR_SET(0, mi);	
					}
				}
			HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);	
			HAL_GPIO_WritePin(GPIOB, LED_SHIFT_Pin, GPIO_PIN_RESET);			//turn off SHIFT led
				
			fl_load_animation(need_fastload_preset);	
			load_status = LOAD_PRESET(FAST_LOADING[need_fastload_preset]);			
			if(load_status!=0)					//error
				{	
				CURRENT_PRESET = 0xFF;					//current preset	
				}
			else
				{
				CURRENT_PRESET = FAST_LOADING[need_fastload_preset];		
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
		need_fastload_preset = 0xFF;	
		}		
		
	key_handler();
	encoder_handler();	

	if(need_load_rgb==1)
		{
		load_rgb_tim = HAL_GetTick();	
		if(load_rgb_tim-load_rgb_prev_tim>5)			//delay 3ms
			{
			if(dSHOW!=FLLIST_DISPLAY)	
				{
				HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);	
				}
			need_load_rgb = 0;
			load_rgb_prev_tim = load_rgb_tim;	
			}
		}	
			
	if(need_send_sync==1)
		{	
		if(UTILITY_SETTINGS[5]==0)	//TTL
			{
			if(UDP_MPHASE%4==1)
				{
				sync_pulse[0] = 0x00;	
				HAL_UART_Transmit(&huart1, sync_pulse, 1, 2);		
				}
			else
				{
				sync_pulse[0] = 0xF0;	
				HAL_UART_Transmit(&huart1, sync_pulse, 1, 2);	
				}				
			}			
		else			//UART 115200bps
			{
			uart_bpm = (UDP_BPM+5)/10;	
			sync_pulse[0] = (uart_bpm>>8)&0x000000FF;	
			sync_pulse[1] = uart_bpm%256;
			if(UDP_MPHASE%4==1)
				{
				sync_pulse[0]|=0x80;	
				}
			HAL_UART_Transmit(&huart1, sync_pulse, 2, 2);		
			}						
		need_send_sync = 0;	
		}	
		
		
	#if defined(USART_DEBUG)	
	if(usart_new_data)									////////////////////////usart data handler
		{
		HAL_Delay(5);	
		if((U_RX_DATA[0]==115) && (U_RX_DATA[1]==99) && (U_RX_DATA[2]==114) && (U_RX_DATA[3]==101) && (U_RX_DATA[4]==101) && (U_RX_DATA[5]==110))				//screen
			{			
			sprintf((char*)U_TX_DATA, "%s", "Prepare screen wait...");	
			U_TX_DATA[22] = 13;
			U_TX_DATA[23] = 10;	
			HAL_UART_Transmit(&huart1, U_TX_DATA, 24, 5);		
			uart_tmp = CREATE_SCREEN();
			if(uart_tmp==0xFFFF)
				{
				sprintf((char*)U_TX_DATA, "%s", "Error. Screen not created.");	
				U_TX_DATA[26] = 13;
				U_TX_DATA[27] = 10;	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 28, 15);		
				}
			else
				{
				sprintf((char*)U_TX_DATA, "%s", "Done!");	
				U_TX_DATA[5] = 13;
				U_TX_DATA[6] = 10;	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 7, 15);
				sprintf((char*)U_TX_DATA, "SCREEN_%03lu.bmp", uart_tmp);		
				U_TX_DATA[14] = 13;
				U_TX_DATA[15] = 10;	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 16, 15);
				}
			}	
		else if((U_RX_DATA[0]==112) && (U_RX_DATA[1]==114) && (U_RX_DATA[2]==115) && (U_RX_DATA[3]==108) && (U_RX_DATA[4]==105) && (U_RX_DATA[5]==115) && (U_RX_DATA[6]==116))	 //prslist
			{
			U_TX_DATA[0] = 13;
			U_TX_DATA[1] = 10;		
			for(uart_tmp=0;uart_tmp<64;uart_tmp++)
				{
				HAL_UART_Transmit(&huart1, &presets_list[uart_tmp][0], 32, 200);		
				HAL_UART_Transmit(&huart1, U_TX_DATA, 2, 15);	
				}			
			}
		else if((U_RX_DATA[0]==112) && (U_RX_DATA[1]==99) && (U_RX_DATA[2]==109))	 //pcm
			{	
			for(uart_tmp=0;uart_tmp<512;uart_tmp++)
				{
				HAL_UART_Transmit(&huart1, (uint8_t*)&PCM[(4*uart_tmp)/8192][(4*uart_tmp)%8192][0], 16, 50);		
				}
			}	
		else if((U_RX_DATA[0]==112) && (U_RX_DATA[1]==99) && (U_RX_DATA[2]==111) && (U_RX_DATA[3]==108))	 //pcol
			{	
			HAL_UART_Transmit(&huart1, COLOR, 104, 200);
			}		
		else if((U_RX_DATA[0]==101) && (U_RX_DATA[1]==112) && (U_RX_DATA[2]==111) && (U_RX_DATA[3]==115))	 //epos
			{	
			uint8_t DTIRb[2];
			DTIRb[0] = seq_epos;
			DTIRb[1] = previous_play_position[ACTIVE_PAD];				
			HAL_UART_Transmit(&huart1, DTIRb, 2, 20);			
			}
		else if((U_RX_DATA[0]==112) && (U_RX_DATA[1]==119) && (U_RX_DATA[2]==102) && (U_RX_DATA[3]==109))	 //pwfm
			{	
			HAL_UART_Transmit(&huart1, P_WAVEFORM[pad_x-1], 100, 200);
			}	
		else if((U_RX_DATA[0]==119) && (U_RX_DATA[1]==100) && (U_RX_DATA[2]==97) && (U_RX_DATA[3]==116) && (U_RX_DATA[4]==97))	 //wdata
			{	
			for(uart_tmp=0;uart_tmp<99;uart_tmp++)
				{
				HAL_UART_Transmit(&huart1, &wdata[16*uart_tmp], 16, 50);		
				}
			}	
		else if((U_RX_DATA[0]==115) && (U_RX_DATA[1]==110) && (U_RX_DATA[2]==97) && (U_RX_DATA[3]==109) && (U_RX_DATA[4]==101))	 //sname
			{	
			U_TX_DATA[0] = 13;
			U_TX_DATA[1] = 10;		
			for(uart_tmp=0;uart_tmp<8;uart_tmp++)
				{
				HAL_UART_Transmit(&huart1, &P_SAMPLE_NAME[uart_tmp][0], 64, 200);		
				HAL_UART_Transmit(&huart1, U_TX_DATA, 2, 15);		
				}
			}
		else if((U_RX_DATA[0]==102) && (U_RX_DATA[1]==115) && (U_RX_DATA[2]==115))	 //fss
			{
			sprintf((char*)U_TX_DATA, "%09lu", play_adr);		
			U_TX_DATA[10] = 13;
			U_TX_DATA[11] = 10;	
			HAL_UART_Transmit(&huart1, U_TX_DATA, 12, 15);
			

				
			//HAL_UART_Transmit(&huart1, (uint8_t*)P_START_ADR, 32, 50);	
			//HAL_UART_Transmit(&huart1, (uint8_t*)P_SAMPLE_OFFSET, 36, 50);		
			//HAL_UART_Transmit(&huart1, (uint8_t*)PADS_L_COLOR, 32, 50);			//pads color			
			//HAL_UART_Transmit(&huart1, &force_start_sample, 1, 50);		//force start sample status
			}	
		else if((U_RX_DATA[0]==0x72) && (U_RX_DATA[1]==0x65) && (U_RX_DATA[2]==0x73) && (U_RX_DATA[3]==0x65) && (U_RX_DATA[4]==0x74))	 //reset
			{				
			sprintf((char*)U_TX_DATA, "%s", "Now reset...");	
			U_TX_DATA[22] = 13;
			U_TX_DATA[23] = 10;	
			HAL_UART_Transmit(&huart1, U_TX_DATA, 12, 5);			
			HAL_Delay(500);
			for(mi=0;mi<8;mi++)
				{
				COLOR_SET(0xFF000000, mi);	
				}				
			HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);			//force rurn off pads
			TIM14->CCR1 = 0;								//PWM BLACKLIGHT
			HAL_GPIO_WritePin(GPIOB, LED_ENC_Pin|LED_SHIFT_Pin, GPIO_PIN_RESET);										//////////////////////////////
			HAL_GPIO_WritePin(GPIOA, LED_PRESET_Pin|LED_EFFECT_Pin, GPIO_PIN_RESET);								//
			HAL_GPIO_WritePin(LED_SYNC_OUT_GPIO_Port, LED_SYNC_OUT_Pin, GPIO_PIN_RESET);						//			turn off leds
			HAL_GPIO_WritePin(GPIOI, LED_EDIT_Pin, GPIO_PIN_RESET);																	//
			HAL_GPIO_WritePin(LED_MENU_GPIO_Port, LED_MENU_Pin, GPIO_PIN_RESET);										//////////////////////////////
			f_close(&file);	
			HAL_Delay(500);	
			NVIC_SystemReset();							//reset system
			}			
		else
			{
			sprintf((char*)U_TX_DATA, "%s", "Unknown command.");	
			U_TX_DATA[16] = 13;
			U_TX_DATA[17] = 10;	
			HAL_UART_Transmit(&huart1, U_TX_DATA, 18, 15);		
			}			
		usart_new_data = 0;		
		}
	#endif	
		
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 15;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Activate the Over-Drive mode 
    */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC|RCC_PERIPHCLK_USART1
                              |RCC_PERIPHCLK_SAI2|RCC_PERIPHCLK_I2C3
                              |RCC_PERIPHCLK_SDMMC1|RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.PLLI2S.PLLI2SN = 271;
  PeriphClkInitStruct.PLLI2S.PLLI2SP = RCC_PLLP_DIV2;
  PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
  PeriphClkInitStruct.PLLI2S.PLLI2SQ = 3;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 120;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
  PeriphClkInitStruct.PLLSAI.PLLSAIQ = 2;
  PeriphClkInitStruct.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV2;
  PeriphClkInitStruct.PLLI2SDivQ = 4;
  PeriphClkInitStruct.PLLSAIDivQ = 1;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
  PeriphClkInitStruct.Sai2ClockSelection = RCC_SAI2CLKSOURCE_PLLI2S;
  PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInitStruct.I2c3ClockSelection = RCC_I2C3CLKSOURCE_PCLK1;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
  PeriphClkInitStruct.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_CLK48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */
	


#include "timer_handler.h"
		
/////////////////////////////////////////////////////
//
//	led_num 0...7
//
void COLOR_SET(uint32_t color, uint8_t LD)
	{
	if(LD>7)
		{
		return;	
		}		
	uint8_t j, r, g, b;	
	if(LD>3)
		{
		LD = 11 - LD;	
		}
	r = (color>>16) & 0x000000FF;	
	g = (color>>8) & 0x000000FF;	
	b = color & 0x000000FF; 
	for(j=0;j<4;j++)
		{
		if((g<<(2*j)&0x80)!=0)
			{
			COLOR[j+(12*LD)] = 0xC0;	
			}
		else
			{
			COLOR[j+(12*LD)] = 0x80;	
			}
		if(((g<<(2*j+1))&0x80)!=0)
			{
			COLOR[j+(12*LD)]|=0x0C;	
			}
		else
			{
			COLOR[j+(12*LD)]|=0x08;	
			}	
		}
	for(j=0;j<4;j++)
		{
		if((r<<(2*j)&0x80)!=0)
			{
			COLOR[j+4+(12*LD)] = 0xC0;	
			}
		else
			{
			COLOR[j+4+(12*LD)] = 0x80;	
			}
		if(((r<<(2*j+1))&0x80)!=0)
			{
			COLOR[j+4+(12*LD)]|=0x0C;	
			}
		else
			{
			COLOR[j+4+(12*LD)]|=0x08;	
			}	
		}	
	for(j=0;j<4;j++)
		{
		if((b<<(2*j)&0x80)!=0)
			{
			COLOR[j+8+(12*LD)] = 0xC0;	
			}
		else
			{
			COLOR[j+8+(12*LD)] = 0x80;	
			}
		if(((b<<(2*j+1))&0x80)!=0)
			{
			COLOR[j+8+(12*LD)]|=0x0C;	
			}
		else
			{
			COLOR[j+8+(12*LD)]|=0x08;	
			}	
		}	
	return;	
	}
	
	
	
	
///////////////////////////////////////////////
//open file presets and load presets list in memory	
//	
//	fill: TOTAL_PRESETS, UTILITY, FAST_LOADING, presets_list[]  
//
//	fill: presets_pads_colors[64][8]
//	fill: presets_icon[64]	
//	fill: presets_rating[64]
//	fill: presets_color[64]
//	
uint8_t LOAD_PRESET_LIST(void)
	{
	res = f_open(&file, presets_path, FA_READ);
	if(res==FR_OK)
		{
		uint8_t pdata[16], i, j, endflag;		
		res = f_read(&file, pdata, 16, &nbytes);	
		if(res==FR_OK)
			{
			TOTAL_PRESETS = pdata[0];				
			UTILITY_SETTINGS[2] = pdata[1];			//EFFECT TYPE			
			if(UTILITY_SETTINGS[2]>4)
				{
				UTILITY_SETTINGS[2] = 0;	
				}		
			UTILITY_SETTINGS[3] = pdata[2];			//SYNC MODE
			if(UTILITY_SETTINGS[3]>1)
				{
				UTILITY_SETTINGS[3] = 0;	
				}		
			UTILITY_SETTINGS[5] = pdata[3];			//SYNC OUT TYPE
			if(UTILITY_SETTINGS[5]>1)
				{
				UTILITY_SETTINGS[5] = 0;	
				}		
			UTILITY_SETTINGS[1] = pdata[4];			//LOAD LOCK
			if(UTILITY_SETTINGS[1]>1)
				{
				UTILITY_SETTINGS[1] = 0;	
				}			
			UTILITY_SETTINGS[0] = pdata[12];		//current preset
			UTILITY_SETTINGS[6] = pdata[13];		//LCD BRIGHTNESS
			if(UTILITY_SETTINGS[6]>4)
				{
				UTILITY_SETTINGS[6] = 3;	
				}
			UTILITY_SETTINGS[4] = 256*pdata[14]+pdata[15];	//INTERNAL BPM
			if(UTILITY_SETTINGS[4]<600 || UTILITY_SETTINGS[4]>2020)
				{
				UTILITY_SETTINGS[4] = 1200;	
				}
			for(i=0;i<8;i++)												//reset fast loading
				{	
				FAST_LOADING[i] = 0xFF;	
				}
			f_lseek(&file, 16);
			f_read(&file, FAST_LOADING, 8, &nbytes);				//copy FAST_LOADING	
			f_lseek(&file, 32);
			f_read(&file, pdata, 16, &nbytes);				//read IPs address
			UTILITY_SETTINGS[7] = 0x01000000*pdata[0] + 0x00010000*pdata[1] + 0x00000100*pdata[2] + pdata[3];		//CDJ 1 IP ADDR.
			UTILITY_SETTINGS[8] = 0x01000000*pdata[4] + 0x00010000*pdata[5] + 0x00000100*pdata[6] + pdata[7];		//CDJ 2 IP ADDR.	
			UTILITY_SETTINGS[9] = 0x01000000*pdata[8] + 0x00010000*pdata[9] + 0x00000100*pdata[10] + pdata[11];		//SAMPLER IP ADDR.
			if(TOTAL_PRESETS>0 && TOTAL_PRESETS<65)
				{
				for(i=0;i<TOTAL_PRESETS;i++)
					{
					f_lseek(&file, 48+1584*i);							//read icon and ENABLE preset status 			
					f_read(&file, &pdata[0], 4, &nbytes);				//read preset name		
					presets_icon[i] = pdata[1];
					if(pdata[2]>5)				//protection against erroneous data
						{
						pdata[2] = 0;	
						}						
					presets_rating[i] = pdata[2];
					if(pdata[3]>7)				//protection against erroneous data
						{
						pdata[3] = 0xFF;	
						}		
					presets_color[i] = pdata[3];					
					f_lseek(&file, 64+1584*i);
					f_read(&file, &presets_list[i], 32, &nbytes);				//read preset name	
					endflag = 0;	
					for(j=0;j<32;j++)
						{
						if(endflag==0)
							{
							if(presets_list[i][j]==0)
								{
								endflag = 1;	
								}
							}
						else
							{
							presets_list[i][j] = 0;				
							}								
						}
					for(j=0;j<8;j++)				//reading colors pads	
						{
						f_lseek(&file, (j*192)+96+1584*i);											
						f_read(&file, &pdata[0], 2, &nbytes);					
						if(pdata[0]==135)
							{
							presets_pads_colors[i][j] = pdata[1]; 	
							}							
						else
							{
							presets_pads_colors[i][j] = 0xFF;				//pad disable
							}							
						}
					}
				f_close(&file);		
				return 0;	
				}				
			else
				{
				return 17;			//persets not found		
				}
			}
		else
			{
			return 16;		//cannot read file presets.pst					
			}		
		}
	else
		{
		return 15;				//cannot open file presets.pst		
		}
	};	
	
	
	
///////////////////////////////////////////////
//	load preset. return error	
//	
//	fill:
//
//		
uint8_t LOAD_PRESET(uint8_t pst_num)						
	{
	if(HAL_GPIO_ReadPin(uSD_Detect_GPIO_Port, uSD_Detect_Pin)==0)			//uSD card enable
		{
		uint8_t pd, i, endflag;		
		uint32_t P_ALL_D[8];	//data in SDRAM	
			
		if(pst_num>63)
			{
			return 30;							//pst_num>63		
			}
		else	
			{
			res = f_open(&file, presets_path, FA_READ);
			if(res==FR_OK)
				{
				for(pd=0;pd<8;pd++)
					{
					f_lseek(&file, (96 + (1584*pst_num) + 192*pd));
					f_read(&file, P_WAVEFORM[pd], 80, &nbytes);			//read parameters and sample name
					if(P_WAVEFORM[pd][0]==135)					// pad is enable
						{
						P_COLOR[pd] = P_WAVEFORM[pd][1];	
						P_TYPE[pd] = P_WAVEFORM[pd][2];
						P_QUANTIZE[pd] = P_WAVEFORM[pd][3];		
						P_SYNC[pd] = P_WAVEFORM[pd][4];	
						P_TRIG[pd] = P_WAVEFORM[pd][5];	
						P_BPM[pd] = 256*P_WAVEFORM[pd][6] + P_WAVEFORM[pd][7];
						P_GAIN[pd] = P_WAVEFORM[pd][8];		
						P_START_ADR[pd] = 65536*P_WAVEFORM[pd][9]+256*P_WAVEFORM[pd][10]+P_WAVEFORM[pd][11];
						P_ALL_D[pd] = 16777216*P_WAVEFORM[pd][12]+65536*P_WAVEFORM[pd][13]+256*P_WAVEFORM[pd][14]+P_WAVEFORM[pd][15];	
						endflag = 0;	
						for(i=0;i<64;i++)			//copy path and fill zeros
							{
							if(endflag==0)
								{
								P_SAMPLE_NAME[pd][i] = P_WAVEFORM[pd][i+16];	
								if(P_WAVEFORM[pd][i+16]==0)
									{
									endflag = 1;	
									}
								}
							else
								{
								 P_SAMPLE_NAME[pd][i] = 0;				
								}								
							}						
						f_read(&file, P_WAVEFORM[pd], 100, &nbytes);			//read waveform or sequencer data	
						}
					else						////pad is DISABLE clear disable pd data
						{
						P_COLOR[pd] = 0xFF;	
						P_TYPE[pd] = 0xFF;
						P_QUANTIZE[pd] = 0xFF;		
						P_SYNC[pd] = 0xFF;	
						P_TRIG[pd] = 0xFF;	
						P_BPM[pd] = 0xFFFF;
						P_GAIN[pd] = 0xFF;					
						P_START_ADR[pd] = 0;	
						P_ALL_D[pd] = 0;		
						for(i=0;i<64;i++)				//clear sample name
							{
							P_SAMPLE_NAME[pd][i] = 0;				
							}
						for(i=0;i<100;i++)				//clear waveform
							{
							P_WAVEFORM[pd][i] = 0xFF;				
							}
						}
					}			
				f_close(&file);		
					
				char _pth[80] = {0};	
				char dir_path[11]="0:/SAMPLER/";	
				sprintf((char*)_pth, "%s", dir_path);				
				uint8_t hdr[256] = {0};
				uint8_t i = 0;
				uint16_t ii = 0;	
				
				for(pd=0;pd<9;pd++)
					{
					if(pd==0)
						{
						P_SAMPLE_OFFSET[0] = 0;	
						}
					else
						{
						P_SAMPLE_OFFSET[pd] = P_SAMPLE_OFFSET[pd-1] + P_ALL_D[pd-1];	
						}					
					}
					
				ram = 0;		//calculate ram percentage status
				for(pd=0;pd<8;pd++)
					{
					ram+=P_ALL_D[pd];	
					}
				ram/=16875;
				for(pd=0;pd<8;pd++)
					{
					if(P_COLOR[pd]<8)					//if pd enable
						{
						sprintf((char*)&_pth[11], "%s", P_SAMPLE_NAME[pd]);			//create path
						res = f_open(&file, _pth, FA_READ);	
						if(res == FR_OK)
							{
							if(f_size(&file)>P_ALL_D[pd])		//check file size
								{	
								f_read(&file, hdr, 256, &nbytes);		
								if(hdr[0]==82 && hdr[1]==73 && hdr[2]==70 && hdr[3]==70)			//check RIFF in hdr
									{
									if(hdr[8]==87 		&& 
										 hdr[9]==65 		&& 
										 hdr[10]==86 	&& 
										 hdr[11]==69		&&
										 hdr[20]==1		&&
										 hdr[21]==0		&&
										 hdr[22]==2		&&
										 hdr[23]==0		&&
										 hdr[24]==68		&&
										 hdr[25]==172	&&
										 hdr[26]==0		&&
										 hdr[27]==0		&&
										 hdr[32]==4		&&
										 hdr[33]==0		&&
										 hdr[34]==16		&&
										 hdr[35]==0		)	//check format	
										{
										ii = 36;							
										while(ii<252)							//find 'data'
											{
											if(hdr[ii] !='d')
												{
												ii++;	
												}
											else
												{
												if(hdr[ii+1]=='a' && hdr[ii+2]=='t' && hdr[ii+3]=='a')
													{
													i = ii;				//pointer for PCM
													ii = 300;		
													}
												else
													{
													ii++;	
													}
												}
											}
											
										if(ii!=252)
											{
											if((P_ALL_D[pd]+P_SAMPLE_OFFSET[pd])>1687552)					//sdram memory empty!
												{
												return 25;				//sdram memory is full!	
												}
											else
												{
												f_lseek(&file, (i+8)+(P_START_ADR[pd]<<2));
												f_read(&file, &PCM[0][0][0] + (P_SAMPLE_OFFSET[pd]<<1), (P_ALL_D[pd]<<2), &nbytes);
												if(res == FR_OK)
													{
													f_close(&file);		
													}
												else
													{
													return 26;				//cannot read audio from file		
													}											
												}
											}
										else
											{	
											return 24;				//header incorrect	
											}					
										}
									else
										{	
										return 23;				//unsupported format
										}		
									}
								else
									{
									return 22;				//file is damadge
									}			
								}
							else
								{
								return 21;				//very short file	
								}
							}
						else
							{
							return 20;		//cannot open audio file	
							}
						}				
					}	
				return 0;	
				}
			else
				{
				ram = 0;	
				return 15;				//cannot open file presets.pst		
				}
			}			
		}	
	else
		{
		ram = 0;	
		return 27;				//uSD card disable	
		}		
	}








	
///////////////////////////////////////////////
//	
//	
//		prepare error message string
//
//	
	
void PREPARE_ERR_MSG(uint8_t er)
	{
	if(er==27)
		{
		sprintf((char*)Buf, "%s", "Error: uSD card disable");		
		}
	else if(er==15)
		{
		sprintf((char*)Buf, "%s", "Can't open file presets.pst");		
		}	
	else if(er==20)
		{
		sprintf((char*)Buf, "%s", "Can't open audio file");		
		}	
	else if(er==21)
		{
		sprintf((char*)Buf, "%s", "Very short file");		
		}	
	else if(er==22)
		{
		sprintf((char*)Buf, "%s", "File is damadge");		
		}	
	else if(er==23)
		{
		sprintf((char*)Buf, "%s", "Unsupported format");		
		}		
	else if(er==24)
		{
		sprintf((char*)Buf, "%s", "Header incorrect");		
		}		
	else if(er==25)
		{
		sprintf((char*)Buf, "%s", "SDRAM is full!");		
		}			
	else if(er==26)
		{
		sprintf((char*)Buf, "%s", "Can't read audio from file");		
		}		
	else if(er==30)
		{
		sprintf((char*)Buf, "%s", "Preset greater than 64");		
		}			
	else
		{
		sprintf((char*)Buf, "%s%1lu", "Error ", load_status);	
		}		
	return;	
	}


	
///////////////////////////////////////////////
//	load preset. return error	
//	
//	fill:
//
//		
uint8_t LOAD_ONE_PAD(uint8_t pst_num)						
	{
	if(HAL_GPIO_ReadPin(uSD_Detect_GPIO_Port, uSD_Detect_Pin)==0)			//uSD card enable
		{
		uint8_t pd, i, endflag;		
		uint32_t P_ALL_D[8];	//data in SDRAM		
		uint32_t WSIZE;	
			
		if(pst_num>63)
			{
			return 26;				
			}
		else	
			{
			res = f_open(&file, presets_path, FA_READ);
			if(res==FR_OK)
				{
				for(pd=0;pd<8;pd++)
					{
					f_lseek(&file, (96 + (1584*pst_num) + 192*pd));
					f_read(&file, P_WAVEFORM[pd], 80, &nbytes);			//read parameters and sample name
					if(pd==pad_x-1)					// pad is enable
						{
						P_COLOR[pd] = P_WAVEFORM[pd][1];	
						P_TYPE[pd] = P_WAVEFORM[pd][2];
						P_QUANTIZE[pd] = P_WAVEFORM[pd][3];		
						P_SYNC[pd] = P_WAVEFORM[pd][4];	
						P_TRIG[pd] = P_WAVEFORM[pd][5];	
						P_BPM[pd] = 256*P_WAVEFORM[pd][6] + P_WAVEFORM[pd][7];
						P_GAIN[pd] = P_WAVEFORM[pd][8];		
						P_START_ADR[pd] = 65536*P_WAVEFORM[pd][9]+256*P_WAVEFORM[pd][10]+P_WAVEFORM[pd][11];
						P_ALL_D[pd] = 16777216*P_WAVEFORM[pd][12]+65536*P_WAVEFORM[pd][13]+256*P_WAVEFORM[pd][14]+P_WAVEFORM[pd][15];	
						endflag = 0;	
						for(i=0;i<64;i++)			//copy path and fill zeros
							{
							if(endflag==0)
								{
								P_SAMPLE_NAME[pd][i] = P_WAVEFORM[pd][i+16];	
								if(P_WAVEFORM[pd][i+16]==0)
									{
									endflag = 1;	
									}
								}
							else
								{
								 P_SAMPLE_NAME[pd][i] = 0;				
								}								
							}						
						f_read(&file, P_WAVEFORM[pd], 100, &nbytes);			//read waveform or sequencer data	
						COLOR_SET(PADS_L_COLOR[P_COLOR[pd]] , pd);	
						}
					else						////pad is DISABLE clear disable pd data
						{
						P_COLOR[pd] = 0xFF;	
						P_TYPE[pd] = 0xFF;
						P_QUANTIZE[pd] = 0xFF;		
						P_SYNC[pd] = 0xFF;	
						P_TRIG[pd] = 0xFF;	
						P_BPM[pd] = 0xFFFF;
						P_GAIN[pd] = 0xFF;					
						P_START_ADR[pd] = 0;	
						P_ALL_D[pd] = 0;		
						for(i=0;i<64;i++)				//clear sample name
							{
							P_SAMPLE_NAME[pd][i] = 0;				
							}
						for(i=0;i<100;i++)				//clear waveform
							{
							P_WAVEFORM[pd][i] = 0xFF;				
							}
						COLOR_SET(EMPTY_PAD, pd);			//set off pad color	
						}	
					}			
				f_close(&file);		
					
				char _pth[80] = {0};	
				char dir_path[11]="0:/SAMPLER/";	
				sprintf((char*)_pth, "%s", dir_path);				
				uint8_t hdr[256] = {0};
				uint8_t i = 0;
				uint16_t ii = 0;	
				sprintf((char*)&_pth[11], "%s", P_SAMPLE_NAME[pad_x-1]);			//create path
				res = f_open(&file, _pth, FA_READ);	
				if(res == FR_OK)
					{
					WSIZE = f_size(&file);
					if(WSIZE<6750208 && WSIZE>255)		//if file < audio buffer
						{	
						f_read(&file, hdr, 256, &nbytes);		
						if(hdr[0]==82 && hdr[1]==73 && hdr[2]==70 && hdr[3]==70)			//check RIFF in hdr
							{
							if(hdr[8]==87 		&& 
								 hdr[9]==65 		&& 
								 hdr[10]==86 	&& 
								 hdr[11]==69		&&
								 hdr[20]==1		&&
								 hdr[21]==0		&&
								 hdr[22]==2		&&
								 hdr[23]==0		&&
								 hdr[24]==68		&&
								 hdr[25]==172	&&
								 hdr[26]==0		&&
								 hdr[27]==0		&&
								 hdr[32]==4		&&
								 hdr[33]==0		&&
								 hdr[34]==16		&&
								 hdr[35]==0		)	//check format	
								{
								ii = 36;							
								while(ii<252)							//find 'data'
									{
									if(hdr[ii] !='d')
										{
										ii++;	
										}
									else
										{
										if(hdr[ii+1]=='a' && hdr[ii+2]=='t' && hdr[ii+3]=='a')
											{
											i = ii;				//pointer for PCM
											ii = 300;		
											}
										else
											{
											ii++;	
											}
										}
									}
									
								if(ii!=252)
									{
									f_lseek(&file, i+8);
									new_all_data = (WSIZE-i)-136;										
									f_read(&file, &PCM[0][0][0], new_all_data, &nbytes);
									if(res == FR_OK)
										{
										f_close(&file);
										for(pd=0;pd<9;pd++)
											{
											if(pd>(pad_x-1))
												{
												P_SAMPLE_OFFSET[pd] =	new_all_data>>2;
												}
											else
												{
												P_SAMPLE_OFFSET[pd] = P_START_ADR[pad_x-1];	
												}																		
											}
										for(uint32_t g=new_all_data/2;g<3375104;g++)		//fill sdram zeros
											{
											PCM[g/16384][(g/2)%8192][g%2] = 0;	
											}	
										new_all_data = new_all_data>>2;			//convert bytes to samples	
										}
									else
										{
										return 25;				//cannot read audio from file		
										}											
									}
								else
									{
									return 24;				//header incorrect	
									}					
								}
							else
								{
								return 23;				//unsupported format
								}		
							}
						else
							{
							return 22;				//file is damadge
							}			
						}
					else
						{
						return 21;				//very short file	
						}
					}
				else
					{
					return 20;		//cannot open audio file	
					}
				return 0;	
				}
			else
				{
				return 15;				//cannot open file presets.pst		
				}
			}			
		}	
	else
		{
		return 27;				//uSD card disable	
		}		
	}	
	
	
	
	
///////////////////////////////////////////////
//get free space and total space	
//		
void GET_SD_INFO(void)
	{
	FATFS *fs;
	DWORD fre_clust;	
	f_getfree("0:", &fre_clust, &fs);
	used_mem = (fs->n_fatent - 2) * fs->csize;
	used_mem = used_mem>>11;
	if(used_mem>99999)
		{
		used_mem = 99999;	
		}	
	free_mem = fre_clust * (fs->csize);
	free_mem = free_mem>>11;		
	if(free_mem>99999)
		{
		free_mem = 99999;	
		}	
	used_mem = used_mem - free_mem;
	return;	
	}	
	

///////////////////////////////////////////////
// encoder handler
//			
void TIM5_IRQHandler(void)
	{		
	uint32_t TM, CTM;
	CTM = HAL_GetTick();	
	TM = CTM - enc_prev_time;
	
	if(__HAL_TIM_GET_FLAG(&htim5, TIM_FLAG_UPDATE) != RESET)	
		{
		__HAL_TIM_CLEAR_IT(&htim5, TIM_FLAG_UPDATE);	
			
		if (TIM5->CR1 & TIM_CR1_DIR)
			{
			if((TM>12 && enc_prev_dir==1) || (TM>100 && enc_prev_dir==0))	
				{
				enc_prev_time = CTM; 	
				enc_need_up = 1;	
				enc_prev_dir = 1;		
				}
			}
		else
			{
			if((TM>12 && enc_prev_dir==0) || (TM>100 && enc_prev_dir==1))	
				{	
				enc_prev_time = CTM; 	
				enc_need_down = 1;	
				enc_prev_dir = 0;		
				}					
			}				
		}
	HAL_TIM_IRQHandler(&htim5);
	}	
	
	

	
	
/////////////////////////////////////////////////////////////////////////////////////	
//Navigate preset list, UTILITY and other
//
//	PRST_LIST_DOWN 		position preset-- (cursor up)
//	PRST_LIST_UP			position preset++ (cursor down)
//	
void NAVIGATOR(uint8_t UPDOWN)
	{	
	if(dSHOW==PRST_LIST)		///////////////////////Preset list mode selected
		{
		if(UPDOWN==PRST_LIST_UP)
			{
			if(PRSTCCP==12)												//All lines update++
				{
				if(CurrentPRSTPosition == TOTAL_PRESETS-12)
					{
					return;	
					}
				else
					{
					BSP_LCD_SelectLayer(1);	
					BSP_LCD_SetTextColor(0x00000000);
					BSP_LCD_FillRect(14, 18, 260, 247);		
					BSP_LCD_SetFont(&Font15P);
					CurrentPRSTPosition++;
					int_PRST_DRAW_ALL_LINES();	
					return;
					}
				}
			else																								//One line update++
				{
				if(TOTAL_PRESETS>13 || PRSTCCP<(TOTAL_PRESETS-1))
					{
					int_PRST_DRAW_ONE_LINE(UPDOWN);	
					}
				return;
				}
			}
		else if(UPDOWN==PRST_LIST_DOWN)
			{
			if(PRSTCCP==0)											//All lines update--
				{
				if(CurrentPRSTPosition == 1)
					{
					return;	
					}
				else
					{
					BSP_LCD_SelectLayer(1);	
					BSP_LCD_SetTextColor(0x00000000);
					BSP_LCD_FillRect(14, 18, 260, 247);	
					BSP_LCD_SetFont(&Font15P);
					CurrentPRSTPosition--;
					int_PRST_DRAW_ALL_LINES();	
					return;						
					}	
				}
			else														//One line update--
				{
				int_PRST_DRAW_ONE_LINE(UPDOWN);	
				return;			
				}	
			}
		}	
	else if(dSHOW==BROWSER)		///////////////////////BROWSER display selected
		{	
		if(UPDOWN==BR_LIST_UP)
			{
			if(BRCCP==12)												//All lines update++
				{
				if(CurrentBRPosition == total_elements-12)
					{
					return;	
					}
				else
					{
					BSP_LCD_SelectLayer(1);	
					BSP_LCD_SetTextColor(0x00000000);
					BSP_LCD_FillRect(14, 18, 466, 247);		
					BSP_LCD_SetFont(&Font15P);
					CurrentBRPosition++;
					int_BR_DRAW_ALL_LINES();	
					return;
					}
				}
			else																								//One line update++
				{
				if(total_elements>13 || BRCCP<(total_elements-1))
					{
					int_BR_DRAW_ONE_LINE(UPDOWN);	
					}
				return;
				}
			}
		else if(UPDOWN==BR_LIST_DOWN)
			{
			if(BRCCP==0)											//All lines update--
				{
				if(CurrentBRPosition == 1)
					{
					return;	
					}
				else
					{
					BSP_LCD_SelectLayer(1);	
					BSP_LCD_SetTextColor(0x00000000);
					BSP_LCD_FillRect(14, 18, 466, 247);	
					BSP_LCD_SetFont(&Font15P);
					CurrentBRPosition--;
					int_BR_DRAW_ALL_LINES();	
					return;						
					}	
				}
			else														//One line update--
				{
				int_BR_DRAW_ONE_LINE(UPDOWN);	
				return;			
				}	
			}
		}	
	else if(dSHOW==UTILITY)		///////////////////////UTILITY mode selected
		{
		if(UPDOWN==UTILITY_UP)
			{
			if(UCurrentCursorPosition==12)												//All lines update++
				{
				if(CurrentUPosition == TOTAL_U_POSITIONS-12)
					{
					return;	
					}
				else
					{
					BSP_LCD_SelectLayer(1);	
					BSP_LCD_SetTransparency(1, 255);
					BSP_LCD_SetTextColor(0x00000000);
					BSP_LCD_FillRect(14, 18, 466, 247);		
					BSP_LCD_SetFont(&Font15P);
					CurrentUPosition++;
					int_U_DRAW_ALL_LINES();
					return;
					}
				}
			else if(TOTAL_U_POSITIONS>13 || UCurrentCursorPosition<(TOTAL_U_POSITIONS-1))								//One line update++
				{
				int_U_DRAW_ONE_LINE(UPDOWN);
				return;
				}
			}
		else if(UPDOWN==UTILITY_DOWN)
			{
			if(UCurrentCursorPosition==0)											//All lines update--
				{
				if(CurrentUPosition == 1)
					{
					return;	
					}
				else
					{
					BSP_LCD_SelectLayer(1);	
					BSP_LCD_SetTransparency(1, 255);
					BSP_LCD_SetTextColor(0x00000000);
					BSP_LCD_FillRect(14, 18, 466, 247);	
					BSP_LCD_SetFont(&Font15P);
					CurrentUPosition--;
					int_U_DRAW_ALL_LINES();
					return;						
					}	
				}
			else														//One line update--
				{
				int_U_DRAW_ONE_LINE(UPDOWN);
				return;			
				}	
			}	
		return;
		}	
	else if(dSHOW==EDIT_PAD_DISPLAY)		///////////////////////EDIT PAD DISPLAY
		{
		if(UPDOWN==EPD_UP)
			{
			if(EPD_Position==TOTAL_EPD_POSITIONS-1 || (EPD_Position==TOTAL_EPD_POSITIONS-2 && P_TYPE[pad_x-1]==0))
				{
				return;	
				}
			else
				{
				int_EPD_DRAW_ONE_LINE(UPDOWN);	
				}
			}				
		else if(UPDOWN==EPD_DOWN)
			{
			if(EPD_Position==0)											//All lines update--
				{
				return;
				}
			else
				{
				int_EPD_DRAW_ONE_LINE(UPDOWN);	
				}
			}
		return;
		}
	else if(dSHOW==EDIT_PRESET_DISPLAY)		///////////////////////EDIT PRESET DISPLAY
		{
		if(UPDOWN==EPRD_UP)
			{
			if(EPRD_Position == TOTAL_EPRD_POSITIONS-1)
				{
				return;	
				}
			else
				{
				int_EPRD_DRAW_ONE_LINE(UPDOWN);	
				}
			}				
		else if(UPDOWN==EPRD_DOWN)
			{
			if(EPRD_Position==0)											//All lines update--
				{
				return;
				}
			else
				{
				int_EPRD_DRAW_ONE_LINE(UPDOWN);	
				}
			}
		return;
		}
	else if(dSHOW==EDIT_UTILITY)		///////////////////////EDIT UTILITY mode selected
		{
		if(UPDOWN==EU_UP)													
			{	
			if(CurrentEUPosition<(TOTAL_EU_POSITIONS-1))			//All lines update++
				{
				int_EU_DRAW_ONE_LINE(UPDOWN);	
				}					
			}
		else if(UPDOWN==EU_DOWN)
			{
			if(CurrentEUPosition!=0)									//All lines update--
				{
				int_EU_DRAW_ONE_LINE(UPDOWN);	
				}				
			}	
		return;	
		}
	else if(dSHOW==EDIT_PRST)		///////////////////////EDIT_PRST mode selected
		{
		if(UPDOWN==EP_UP)													
			{	
			if(CurrentEPPosition<(TOTAL_EP_POSITIONS-1))			//All lines update++
				{
				int_EP_DRAW_ONE_LINE(UPDOWN);	
				}					
			}
		else if(UPDOWN==EP_DOWN)
			{
			if(CurrentEPPosition!=0)									//All lines update--
				{
				int_EP_DRAW_ONE_LINE(UPDOWN);	
				}				
			}	
		return;	
		}
	else if(dSHOW==EDIT_LIST)		///////////////////////EDIT LIST mode selected
		{
		if(UPDOWN==EL_UP)													
			{	
			if(CurrentELPosition<(TOTAL_EL_POSITIONS-1))			//All lines update++
				{
				int_EL_DRAW_ONE_LINE(UPDOWN);	
				}					
			}
		else if(UPDOWN==EL_DOWN)
			{
			if(CurrentELPosition!=0)									//All lines update--
				{
				int_EL_DRAW_ONE_LINE(UPDOWN);	
				}				
			}	
		return;	
		}
	else if(dSHOW==DELDIALOG)		///////////////////////DELETE DIALOG
		{
		if(UPDOWN==DELDIALOG_UP)													
			{	
			if(CurrentDDPosition<(TOTAL_DD_POSITIONS-1))			//All lines update++
				{
				int_DD_DRAW_ONE_LINE(UPDOWN);	
				}					
			}
		else if(UPDOWN==DELDIALOG_DOWN)
			{
			if(CurrentDDPosition!=0)									//All lines update--
				{
				int_DD_DRAW_ONE_LINE(UPDOWN);	
				}				
			}	
		return;	
		}
	else if(dSHOW==EDIT_FLLIST_DISPLAY)		///////////////////////EDIT FAST LOAD LIST DISPLAY
		{
		if(UPDOWN==EFL_UP)													
			{
			if(FLCurrentCursorPosition<7)	
				{
				int_FL_DRAW_ONE_LINE(UPDOWN);
				}
			}
		else if(UPDOWN==EFL_DOWN)													
			{
			if(FLCurrentCursorPosition!=0)
				{
				int_FL_DRAW_ONE_LINE(UPDOWN);	
				}				
			}
		return;
		}	
	else if(dSHOW==MOVE_PRESET)		///////////////////////Move Preset mode
		{
		if(UPDOWN==MPRST_UP)
			{
			if(MPRSTCCP==12)												//All lines update++
				{
				if(CurrentMPRSTPosition == TOTAL_PRESETS-12)
					{
					return;	
					}
				else
					{
					BSP_LCD_SelectLayer(1);	
					BSP_LCD_SetTextColor(0x00000000);
					BSP_LCD_FillRect(14, 18, 260, 247);		
					BSP_LCD_SetFont(&Font15P);
					CurrentMPRSTPosition++;
					int_MPRST_DRAW_ALL_LINES();	
					return;
					}
				}
			else																								//One line update++
				{
				if(TOTAL_PRESETS>13 || MPRSTCCP<(TOTAL_PRESETS-1))
					{
					int_MPRST_DRAW_ONE_LINE(UPDOWN);	
					}
				return;
				}
			}
		else if(UPDOWN==MPRST_DOWN)
			{
			if(MPRSTCCP==0)											//All lines update--
				{
				if(CurrentMPRSTPosition==1)
					{
					return;	
					}
				else
					{
					BSP_LCD_SelectLayer(1);	
					BSP_LCD_SetTextColor(0x00000000);
					BSP_LCD_FillRect(14, 18, 260, 247);	
					BSP_LCD_SetFont(&Font15P);
					CurrentMPRSTPosition--;
					int_MPRST_DRAW_ALL_LINES();	
					return;						
					}	
				}
			else														//One line update--
				{
				int_MPRST_DRAW_ONE_LINE(UPDOWN);	
				return;			
				}	
			}
		}	
	return;
	};	
	
	
///////////////////////////////////////////////	
//Switch Displays
//
//	
void SwitchInformationLayer(uint8_t LAY)
	{
	uint8_t update_all_page = 0;
	uint16_t icnt;
	uint8_t reverse_animation = 0;
		
	if(dSHOW != LAY)
		{
		if(dSHOW==KEYBOARD && LAY==EDIT_PRESET_DISPLAY)	
			{
			reverse_animation = 1;	
			}
		dSHOW = LAY;
		update_all_page = 1;	
		}	
		
	if(LAY==HOME_DISPLAY)		//X => HOME_DISPLAY
		{
		BSP_LCD_SelectLayer(0);	
		if(update_all_page)
			{			
			HAL_GPIO_WritePin(GPIOB, LED_SHIFT_Pin, GPIO_PIN_RESET);																//
			HAL_GPIO_WritePin(GPIOA, LED_PRESET_Pin, GPIO_PIN_RESET);																//
			HAL_GPIO_WritePin(GPIOI, LED_EDIT_Pin, GPIO_PIN_RESET);																	//
			HAL_GPIO_WritePin(LED_MENU_GPIO_Port, LED_MENU_Pin, GPIO_PIN_RESET);										//
			if(after_fl==0)
				{				
				int_DRAW_TRANSPARENT_BAR();
				}					
			}
		if(after_fl==0)
			{		
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);	
			BSP_LCD_FillRect(0, 18, 480, 254);	
			}
		BSP_LCD_SelectLayer(1);
		BSP_LCD_Clear(0x00000000);
		BSP_LCD_SetFont(&Font15P);
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		if(CURRENT_PRESET==0xFF)
			{
			sprintf((char*)Buf, "%s", "Not Loaded.");		
			BSP_LCD_DisplayStringAt(5,2,Buf, TRANSPARENT_MODE);
			ram = 0;	
			}
		else if(CURRENT_PRESET<64)
			{		
			sprintf((char*)Buf, "%s", "|");		
			BSP_LCD_DisplayStringAt(5,2,Buf, TRANSPARENT_MODE);	
			BSP_LCD_DisplayStringAt(23, 2, presets_list[CURRENT_PRESET], TRANSPARENT_MODE);
			}
		BSP_LCD_SelectLayer(0);			
		ShowBPM(UDP_BPM);								//draw static information
		previousMD = 0xFE;							//forced update
		ShowMasterDeck(0);
		PreviousSPhase = 0xFFFE; 				//forced update
		ShowSPhaseMeter(0xFF);					//draw static information	
		PreviousMPhase = 0xFFFE;				//forced update
		previous_MPHASE_color = 0xFE;		//forced update
		ShowMPhaseMeter(0xFF, 0xFFFF);	//draw static information	
		ShowRAM(ram);	
		previous_link_status = 0xFF;		//forced update
		need_redraw_effect = 1;					//forced update
		need_redraw_syncout = 1;				//forced update	
		if(after_fl==0)
			{			
			Draw_Static_Pads();
			}		
		after_fl = 0;	
		}
	else if(LAY==PRST_LIST)													//X => PRST_LIST
		{
		if(update_all_page==1)
			{
			HAL_GPIO_WritePin(GPIOB, LED_SHIFT_Pin, GPIO_PIN_RESET);																//
			HAL_GPIO_WritePin(GPIOA, LED_PRESET_Pin, GPIO_PIN_SET);																	//
			HAL_GPIO_WritePin(GPIOI, LED_EDIT_Pin, GPIO_PIN_RESET);																	//
			HAL_GPIO_WritePin(LED_MENU_GPIO_Port, LED_MENU_Pin, GPIO_PIN_RESET);										//
			BSP_LCD_SelectLayer(1);
			BSP_LCD_Clear(0x00000000);
			BSP_LCD_SelectLayer(0);
			int_DRAW_TRANSPARENT_BAR();		
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);	
			BSP_LCD_FillRect(0, 18, 480, 254);
			BSP_LCD_SetTextColor(LCD_COLOR_DARK_1);
			BSP_LCD_DrawRect(0, 18, 14, 247);							//scroll frame		
			BSP_LCD_SetFont(&Font15P);	
			BSP_LCD_SelectLayer(1);		
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			sprintf((char*)Buf, "%s", "PRESET LIST");						
			BSP_LCD_DisplayStringAt(5, 2, Buf, TRANSPARENT_MODE);			
			sprintf((char*)Buf, "%s%1lu", "Total Presets ", TOTAL_PRESETS);						
			BSP_LCD_DisplayStringAt(344, 2,Buf, TRANSPARENT_MODE);
			BSP_LCD_SelectLayer(0);					
			intDrawLayer0_PRST(PRSTCCP);					
			}
		else
			{
			BSP_LCD_SelectLayer(1);		
			BSP_LCD_SetTextColor(0x00000000);	
			BSP_LCD_FillRect(20, 20+(19*PRSTCCP), 15, 19);		
			}
		int_PRST_DRAW_ALL_LINES();
		return;	
		}
	else if(LAY==FLLIST_DISPLAY)													//X => FAST LOAD LIST DISPLAY
		{		
		HAL_GPIO_WritePin(GPIOB, LED_SHIFT_Pin, GPIO_PIN_SET);																	//
		HAL_GPIO_WritePin(GPIOA, LED_PRESET_Pin, GPIO_PIN_RESET);																//
		HAL_GPIO_WritePin(GPIOI, LED_EDIT_Pin, GPIO_PIN_RESET);																	//
		HAL_GPIO_WritePin(LED_MENU_GPIO_Port, LED_MENU_Pin, GPIO_PIN_RESET);										//	
		BSP_LCD_SelectLayer(1);
		BSP_LCD_Clear(0x00000000);
		previous_frame = 0;
		need_reslide_pads = 0;	
		need_slide_pads = 1;
		start_slide_time	= HAL_GetTick();
		return;	
		}
	else if(LAY==UTILITY)													//X => UTILITY
		{	
		if(update_all_page)
			{	
			HAL_GPIO_WritePin(GPIOB, LED_SHIFT_Pin, GPIO_PIN_RESET);															//
			HAL_GPIO_WritePin(GPIOA, LED_PRESET_Pin, GPIO_PIN_RESET);															//
			HAL_GPIO_WritePin(GPIOI, LED_EDIT_Pin, GPIO_PIN_RESET);																//
			HAL_GPIO_WritePin(LED_MENU_GPIO_Port, LED_MENU_Pin, GPIO_PIN_SET);										//
			BSP_LCD_SelectLayer(1);
			BSP_LCD_Clear(0x00000000);		
			BSP_LCD_SelectLayer(0);
			BSP_LCD_Clear(LCD_COLOR_BLACK);	
			BSP_LCD_SetTextColor(LCD_COLOR_DARK_2);
			BSP_LCD_FillRect(0, 0, 480, 18);		
			BSP_LCD_SetTextColor(LCD_COLOR_DARK_1);
			BSP_LCD_DrawRect(0, 18, 14, 248);							//scroll frame	
			BSP_LCD_SetTextColor(LCD_COLOR_DARK_1);
			BSP_LCD_DrawLine(14, 18, 479, 18);
			BSP_LCD_DrawLine(14, 37, 479, 37);
			BSP_LCD_DrawLine(14, 56, 479, 56);
			BSP_LCD_DrawLine(14, 75, 479, 75);
			BSP_LCD_DrawLine(14, 94, 479, 94);
			BSP_LCD_DrawLine(14, 113, 479, 113);
			BSP_LCD_DrawLine(14, 132, 479, 132);
			BSP_LCD_DrawLine(14, 151, 479, 151);
			BSP_LCD_DrawLine(14, 170, 479, 170);
			BSP_LCD_DrawLine(14, 189, 479, 189);
			BSP_LCD_DrawLine(14, 208, 479, 208);
			BSP_LCD_DrawLine(14, 227, 479, 227);
			BSP_LCD_DrawLine(14, 246, 479, 246);
			BSP_LCD_DrawLine(14, 265, 479, 265);
			BSP_LCD_DrawLine(479, 18, 479, 265);
			BSP_LCD_DrawLine(270, 18, 270, 265);				//vertical line		
			}				
		if(edit_parameter==0)
			{
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
			}
		else
			{
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_3);		
			BSP_LCD_FillRect(14, (18+(19*UCurrentCursorPosition)), 256, 9);			////Draw selected cursor	
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_5);
			BSP_LCD_FillRect(14, (27+(19*UCurrentCursorPosition)), 256, 5);
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_4);
			BSP_LCD_FillRect(14, (32+(19*UCurrentCursorPosition)), 256, 5);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);				
			BSP_LCD_FillRect(271, (18+(19*UCurrentCursorPosition)), 208, 9);			////Draw selected cursor	
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_2);
			BSP_LCD_FillRect(271, (27+(19*UCurrentCursorPosition)), 208, 5);
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_1);
			BSP_LCD_FillRect(271, (32+(19*UCurrentCursorPosition)), 208, 5);				
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			FillTriangle(276, 276, 283, 20+(19*UCurrentCursorPosition), 34+(19*UCurrentCursorPosition), 27 +(19*UCurrentCursorPosition));	
			}				
		BSP_LCD_SelectLayer(1);	
		//BSP_LCD_SetTransparency(1, 255);
		BSP_LCD_SetFont(&Font15P);
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		if(update_all_page)
			{	
			sprintf((char*)Buf, "%s", "UTILITY");			
			BSP_LCD_DisplayStringAt(5,2,Buf, TRANSPARENT_MODE);
			}
		int_U_DRAW_ALL_LINES();	
		return;	
		}	
	else if(LAY==EDIT_PRST)		//X => EDIT PRESET
		{
		if(update_all_page)
			{
			BSP_LCD_SelectLayer(1);	
			BSP_LCD_SetTextColor(0x00000000);
			BSP_LCD_FillRect(250, 0, 123, 234);			//clear layer (1) square
			BSP_LCD_SelectLayer(0);		
			HAL_GPIO_WritePin(GPIOB, LED_SHIFT_Pin, GPIO_PIN_RESET);																//
			HAL_GPIO_WritePin(GPIOA, LED_PRESET_Pin, GPIO_PIN_RESET);																//
			HAL_GPIO_WritePin(GPIOI, LED_EDIT_Pin, GPIO_PIN_SET);																		//
			HAL_GPIO_WritePin(LED_MENU_GPIO_Port, LED_MENU_Pin, GPIO_PIN_RESET);										//
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_5);					////////////////////
			BSP_LCD_FillRect(252, 0, 119, 18);								//												
			BSP_LCD_DrawLine(251, 1, 251, 19);								//
			BSP_LCD_DrawLine(371, 1, 371, 19);								//	header window
			BSP_LCD_DrawLine(250, 2, 250, 231);								//
			BSP_LCD_DrawLine(372, 2, 372, 231);								//
			BSP_LCD_DrawLine(252, 233, 370, 233);							//	
			BSP_LCD_DrawPixel(370, 232, LCD_COLOR_LIGHT_5);		//
			BSP_LCD_DrawPixel(371, 232, LCD_COLOR_LIGHT_5);		//
			BSP_LCD_DrawPixel(371, 231, LCD_COLOR_LIGHT_5);		//
			BSP_LCD_DrawPixel(252, 232, LCD_COLOR_LIGHT_5);		//
			BSP_LCD_DrawPixel(251, 232, LCD_COLOR_LIGHT_5);		//
			BSP_LCD_DrawPixel(251, 231, LCD_COLOR_LIGHT_5);		//
			BSP_LCD_SetTextColor(LCD_COLOR_DARK_1);		///////////
			BSP_LCD_DrawLine(252, 18, 370, 18);				//
			BSP_LCD_DrawLine(252, 231, 370, 231);			//	body window
			BSP_LCD_DrawLine(253, 232, 369, 232);			//
			BSP_LCD_FillRect(251, 19, 121, 212);			//
			BSP_LCD_SetFont(&Font15P);
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);		
			sprintf((char*)Buf, "%s", "EDIT");		
			BSP_LCD_DisplayStringAt(295, 2, Buf, TRANSPARENT_MODE);	
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);																											////////////////////////	
			BSP_LCD_DrawLine(257, (21+(19*CurrentEPPosition)), 365, (21+(19*CurrentEPPosition)));				//
			BSP_LCD_DrawLine(255, (22+(19*CurrentEPPosition)), 367, (22+(19*CurrentEPPosition)));				//
			BSP_LCD_FillRect(254, (23+(19*CurrentEPPosition)), 115, 7);																	//	Draw selected cursor	
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_2);																										//
			BSP_LCD_FillRect(254, (30+(19*CurrentEPPosition)), 115, 5);																	//
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_1);																										//
			BSP_LCD_FillRect(254, (35+(19*CurrentEPPosition)), 115, 3);																	//
			BSP_LCD_DrawLine(255, (38+(19*CurrentEPPosition)), 367, (38+(19*CurrentEPPosition)));				//
			BSP_LCD_DrawLine(257, (39+(19*CurrentEPPosition)), 365, (39+(19*CurrentEPPosition)));				//////////////////////////
			int_EP_DRAW_ALL_LINES();	
			return;	
			}
		return;		
		}
	else if(LAY==EDIT_LIST)		//X => EDIT LIST
		{
		if(update_all_page)
			{
			BSP_LCD_SelectLayer(1);	
			BSP_LCD_SetTextColor(0x00000000);
			BSP_LCD_FillRect(221, 0, 181, 120);			//clear layer (1) square
			BSP_LCD_SelectLayer(0);		
			HAL_GPIO_WritePin(GPIOB, LED_SHIFT_Pin, GPIO_PIN_RESET);																//
			HAL_GPIO_WritePin(GPIOA, LED_PRESET_Pin, GPIO_PIN_SET);																	//
			HAL_GPIO_WritePin(GPIOI, LED_EDIT_Pin, GPIO_PIN_SET);																		//
			HAL_GPIO_WritePin(LED_MENU_GPIO_Port, LED_MENU_Pin, GPIO_PIN_RESET);										//
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_5);					////////////////////
			BSP_LCD_FillRect(223, 0, 177, 18);								//												
			BSP_LCD_DrawLine(222, 1, 222, 19);								//
			BSP_LCD_DrawLine(400, 1, 400, 19);								//	header window
			BSP_LCD_DrawLine(221, 2, 221, 117);								//
			BSP_LCD_DrawLine(401, 2, 401, 117);								//
			BSP_LCD_DrawLine(223, 119, 399, 119);							//	
			BSP_LCD_DrawPixel(399, 118, LCD_COLOR_LIGHT_5);		//
			BSP_LCD_DrawPixel(400, 118, LCD_COLOR_LIGHT_5);		//
			BSP_LCD_DrawPixel(400, 117, LCD_COLOR_LIGHT_5);		//
			BSP_LCD_DrawPixel(223, 118, LCD_COLOR_LIGHT_5);		//
			BSP_LCD_DrawPixel(222, 118, LCD_COLOR_LIGHT_5);		//
			BSP_LCD_DrawPixel(222, 117, LCD_COLOR_LIGHT_5);		//
			BSP_LCD_SetTextColor(LCD_COLOR_DARK_1);		///////////
			BSP_LCD_DrawLine(223, 18, 399, 18);				//
			BSP_LCD_DrawLine(223, 117, 399, 117);			//	body window
			BSP_LCD_DrawLine(224, 118, 398, 118);			//
			BSP_LCD_FillRect(222, 19, 179, 98);				//
			BSP_LCD_SetFont(&Font15P);
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);		
			sprintf((char*)Buf, "%s", "EDIT");		
			BSP_LCD_DisplayStringAt(295, 2, Buf, TRANSPARENT_MODE);	
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);																											////////////////////////	
			BSP_LCD_DrawLine(228, (21+(19*CurrentELPosition)), 394, (21+(19*CurrentELPosition)));				//
			BSP_LCD_DrawLine(226, (22+(19*CurrentELPosition)), 396, (22+(19*CurrentELPosition)));				//
			BSP_LCD_FillRect(225, (23+(19*CurrentELPosition)), 173, 7);																	//	Draw selected cursor	
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_2);																										//
			BSP_LCD_FillRect(225, (30+(19*CurrentELPosition)), 173, 5);																	//
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_1);																										//
			BSP_LCD_FillRect(225, (35+(19*CurrentELPosition)), 173, 3);																	//
			BSP_LCD_DrawLine(226, (38+(19*CurrentELPosition)), 396, (38+(19*CurrentELPosition)));				//
			BSP_LCD_DrawLine(228, (39+(19*CurrentELPosition)), 394, (39+(19*CurrentELPosition)));				//////////////////////////
			int_EL_DRAW_ALL_LINES();	
			return;	
			}
		return;		
		}	
	else if(LAY==DELDIALOG)		//X => DELETE DIALOG
		{
		if(update_all_page)
			{
			BSP_LCD_SelectLayer(1);	
			BSP_LCD_SetTextColor(0x00000000);	
			BSP_LCD_DrawLine(104, 79, 375, 79);			//clear layer (1) square
			BSP_LCD_DrawLine(102, 80, 377, 80);
			BSP_LCD_DrawLine(100, 81, 379, 81);
			BSP_LCD_DrawLine(100, 82, 379, 82);
			BSP_LCD_DrawLine(99, 83, 380, 83);
			BSP_LCD_DrawLine(99, 84, 380, 84);
			BSP_LCD_FillRect(98, 85, 284, 71);
			BSP_LCD_DrawLine(99, 156, 380, 156);
			BSP_LCD_DrawLine(99, 157, 380, 157);
			BSP_LCD_DrawLine(100, 158, 379, 158);
			BSP_LCD_DrawLine(100, 159, 379, 159);
			BSP_LCD_DrawLine(102, 160, 377, 160);
			BSP_LCD_DrawLine(104, 161, 375, 161);	
			BSP_LCD_SelectLayer(0);	
			HAL_GPIO_WritePin(GPIOB, LED_SHIFT_Pin, GPIO_PIN_RESET);																//
			HAL_GPIO_WritePin(GPIOA, LED_PRESET_Pin, GPIO_PIN_SET);																	//
			HAL_GPIO_WritePin(GPIOI, LED_EDIT_Pin, GPIO_PIN_RESET);																	//
			HAL_GPIO_WritePin(LED_MENU_GPIO_Port, LED_MENU_Pin, GPIO_PIN_RESET);										//	
			BSP_LCD_SetTextColor(DIALOG_BACK_COLOR);					//draw dialog square
			BSP_LCD_DrawLine(104, 79, 375, 79);		
			BSP_LCD_DrawLine(102, 80, 377, 80);
			BSP_LCD_DrawLine(100, 81, 379, 81);
			BSP_LCD_DrawLine(100, 82, 379, 82);
			BSP_LCD_DrawLine(99, 83, 380, 83);
			BSP_LCD_DrawLine(99, 84, 380, 84);
			BSP_LCD_FillRect(98, 85, 284, 71);
			BSP_LCD_DrawLine(99, 156, 380, 156);
			BSP_LCD_DrawLine(99, 157, 380, 157);
			BSP_LCD_DrawLine(100, 158, 379, 158);
			BSP_LCD_DrawLine(100, 159, 379, 159);
			BSP_LCD_DrawLine(102, 160, 377, 160);
			BSP_LCD_DrawLine(104, 161, 375, 161);	
			BSP_LCD_SetFont(&Font15P);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);		
			sprintf((char*)Buf, "%s", "DELETE PRESET?");		
			BSP_LCD_DisplayStringAt(170, 88, Buf, TRANSPARENT_MODE);	
			icnt = strlen(presets_list[PRSTCCP+CurrentPRSTPosition-1]);
			if(icnt<6)
				{
				icnt = 220;
				}
			else if(icnt<8)
				{
				icnt = 211;
				}
			else if(icnt<10)
				{
				icnt = 199;
				}			
			else if(icnt<12)
				{
				icnt = 189;
				}						
			else if(icnt<15)
				{
				icnt = 180;
				}
			else if(icnt<18)
				{
				icnt = 170;
				}	
			else if(icnt<22)
				{
				icnt = 159;
				}
			else if(icnt<24)
				{
				icnt = 149;
				}
			else if(icnt<26)
				{
				icnt = 139;
				}
			else if(icnt<28)
				{
				icnt = 127;
				}					
			else
				{
				icnt = 118;	
				}
			BSP_LCD_DisplayStringAt(icnt, 110, presets_list[PRSTCCP+CurrentPRSTPosition-1], TRANSPARENT_MODE);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);																										////////////////////////	
			BSP_LCD_DrawLine(170+(80*CurrentDDPosition), 133, 228+(80*CurrentDDPosition), 133);				//
			BSP_LCD_DrawLine(168+(80*CurrentDDPosition), 134, 230+(80*CurrentDDPosition), 134);				//
			BSP_LCD_FillRect(167+(80*CurrentDDPosition), 135, 65, 7);																	//	Draw selected cursor	
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_2);																									//
			BSP_LCD_FillRect(167+(80*CurrentDDPosition), 142, 65, 5);																	//
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_1);																									//
			BSP_LCD_FillRect(167+(80*CurrentDDPosition), 147, 65, 3);																	//
			BSP_LCD_DrawLine(168+(80*CurrentDDPosition), 150, 230+(80*CurrentDDPosition), 150);				//
			BSP_LCD_DrawLine(170+(80*CurrentDDPosition), 151, 228+(80*CurrentDDPosition), 151);				//////////////////////////	
			int_DD_DRAW_ALL_LINES();		
			return;	
			}
		return;	
		}
	else if(LAY==EDIT_PAD_DISPLAY)		//X => EDIT_PAD_DISPLAY
		{
		pad_x	= CurrentEPPosition-1;

		BSP_LCD_SelectLayer(0);	
		if(update_all_page)
			{
			EPD_Position = 0;	
			edit_epd_parameter = 0;		
			HAL_GPIO_WritePin(GPIOB, LED_SHIFT_Pin, GPIO_PIN_RESET);																//
			HAL_GPIO_WritePin(GPIOA, LED_PRESET_Pin, GPIO_PIN_RESET);																//
			HAL_GPIO_WritePin(GPIOI, LED_EDIT_Pin, GPIO_PIN_RESET);																	//
			HAL_GPIO_WritePin(LED_MENU_GPIO_Port, LED_MENU_Pin, GPIO_PIN_RESET);										//
			int_DRAW_TRANSPARENT_BAR();	
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);	
			BSP_LCD_FillRect(0, 18, 480, 254);	
			BSP_LCD_SelectLayer(1);
			BSP_LCD_Clear(0x00000000);
			BSP_LCD_SetFont(&Font15P);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);	
			sprintf((char*)Buf, "%s", "<");		
			BSP_LCD_DisplayStringAt(5,2, Buf, TRANSPARENT_MODE);	
			sprintf((char*)Buf, "%s", presets_list[CURRENT_PRESET]);
			sprintf((char*)&Buf[strlen(Buf)],	 ": PAD %1lu edit", pad_x);
			BSP_LCD_DisplayStringAt(23, 2, Buf, TRANSPARENT_MODE);			
			BSP_LCD_SelectLayer(0);		
			BSP_LCD_SetTextColor(PATH_COLOR);		
			BSP_LCD_FillRect(3, 21, 474, 19);							//path for sample	
			BSP_LCD_SetTextColor(PERIPH_PAD_GRADIENT_2);	
			BSP_LCD_DrawRect(3, 43, 474, 109);		
			BSP_LCD_SetTextColor(PERIPH_PAD_GRADIENT_3);	
			BSP_LCD_FillRect(3, 152, 474, 14);						//big waveform interface
			BSP_LCD_SetTextColor(PERIPH_PAD_GRADIENT_1);
			BSP_LCD_DrawRect(4, 44, 472, 107);	
			BSP_LCD_SetTextColor(PERIPH_PAD_GRADIENT_0);
			BSP_LCD_DrawRect(5, 45, 470, 105);	
			for(icnt=0;icnt<234;icnt++)							//gray horizontal dots
				{
				BSP_LCD_DrawPixel(6+2*icnt, 97, PERIPH_PAD_GRADIENT_0);	
				}	
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);	
			FillTriangle(244, 234, 239, 154, 154, 149);				//draw triangle	
			BSP_LCD_SetTextColor(0xFFF0F0F0);	
			BSP_LCD_DrawPixel(238, 149, LCD_COLOR_WHITE);	
			BSP_LCD_DrawPixel(240, 149, LCD_COLOR_WHITE);
			BSP_LCD_DrawPixel(237, 150, LCD_COLOR_WHITE);	
			BSP_LCD_DrawPixel(241, 150, LCD_COLOR_WHITE);			
			BSP_LCD_DrawPixel(236, 151, LCD_COLOR_WHITE);	
			BSP_LCD_DrawPixel(242, 151, LCD_COLOR_WHITE);
			BSP_LCD_DrawPixel(235, 152, LCD_COLOR_WHITE);	
			BSP_LCD_DrawPixel(243, 152, LCD_COLOR_WHITE);			
			BSP_LCD_DrawPixel(234, 153, LCD_COLOR_WHITE);	
			BSP_LCD_DrawPixel(244, 153, LCD_COLOR_WHITE);		
			BSP_LCD_DrawPixel(233, 154, LCD_COLOR_WHITE);	
			BSP_LCD_DrawPixel(245, 154, LCD_COLOR_WHITE);	
			BSP_LCD_SetTextColor(0xFFE4E4E4);
			BSP_LCD_DrawLine(233, 155, 245, 155);		
			BSP_LCD_DrawPixel(475, 164, PERIPH_PAD_GRADIENT_0);			///////////////
			BSP_LCD_DrawPixel(473, 164, PERIPH_PAD_GRADIENT_0);			//
			BSP_LCD_DrawPixel(471, 164, PERIPH_PAD_GRADIENT_0);			//	gray dots on panel
			BSP_LCD_DrawPixel(475, 162, PERIPH_PAD_GRADIENT_0);			//
			BSP_LCD_DrawPixel(475, 160, PERIPH_PAD_GRADIENT_0);			//
			BSP_LCD_DrawPixel(473, 162, PERIPH_PAD_GRADIENT_0);			////////////////
			BSP_LCD_SetTextColor(PERIPH_PAD_GRADIENT_0);	
			BSP_LCD_FillRect(77, 156, 21, 7);			//for SHIFT	
			BSP_LCD_SetTextColor(PADS_LABEL_COLOR[4]);
			BSP_LCD_SetFont(&FontBMP);	
			sprintf((char*)Buf, "%s", "K");						//SHIFT
			BSP_LCD_DisplayStringAt(76, 155, Buf, TRANSPARENT_MODE);		
			BSP_LCD_SelectLayer(1);							//draw to lay 1
			if(P_COLOR[pad_x-1]<8)  //pad is enable
				{	
				BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
				BSP_LCD_FillRect(209, 86, 73, 18);	
				BSP_LCD_SetTextColor(LCD_COLOR_RED);		
				BSP_LCD_SetFont(&Font15P);	
				sprintf((char*)Buf, "%s", "Loading...");					
				BSP_LCD_DisplayStringAt(211, 88, Buf, TRANSPARENT_MODE);				
				}
			BSP_LCD_SetTextColor(DIALOG_BACK_COLOR);
			BSP_LCD_FillRect(8, 47, 8, 10);		
			BSP_LCD_DrawLine(7, 48, 7, 55);
			BSP_LCD_DrawLine(16, 48, 16, 55);
			BSP_LCD_FillRect(8, 99, 8, 10);		
			BSP_LCD_DrawLine(7, 100, 7, 107);
			BSP_LCD_DrawLine(16, 100, 16, 107);	
			BSP_LCD_SetFont(&Font8);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			sprintf((char*)Buf, "%s", "{");				//L		
			BSP_LCD_DisplayStringAt(9, 49, Buf, TRANSPARENT_MODE);	
			sprintf((char*)Buf, "%s", "}");				//R
			BSP_LCD_DisplayStringAt(9, 101, Buf, TRANSPARENT_MODE);	
			BSP_LCD_SelectLayer(0);	
			
			if(P_COLOR[pad_x-1]==0xFF)  //pad is disable
				{
				CREATE_GUI_STYLE_COLOR(PERIPH_PAD_GRADIENT_2);			
				}				
			else
				{
				CREATE_GUI_STYLE_COLOR(PADS_LABEL_COLOR[P_COLOR[pad_x-1]]);											//create gui table color	
				}				
			BSP_LCD_SetTextColor(GUI_STYLE_COLOR);
			BSP_LCD_FillRect(4, 170, 354, 75);		//background table
			if(P_COLOR[pad_x-1]==0xFF)  //pad is disable
				{	
				BSP_LCD_SetTextColor(PERIPH_PAD_GRADIENT_2);						//	table, if pad is disable
				}
			else
				{				
				BSP_LCD_SetTextColor(PADS_LABEL_COLOR[P_COLOR[pad_x-1]]);		//	table
				}
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
			BSP_LCD_SetTextColor(PERIPH_PAD_GRADIENT_0);			//status bar
			BSP_LCD_DrawRect(3, 249, 356, 21);
			BSP_LCD_SetTextColor(PERIPH_PAD_GRADIENT_1);
			BSP_LCD_DrawRect(4, 250, 354, 19);		
			BSP_LCD_SetTextColor(PERIPH_PAD_GRADIENT_2);
			BSP_LCD_FillRect(5, 251, 352, 17);	
			BSP_LCD_SetTextColor(PERIPH_PAD_GRADIENT_0);				//pad perimeter
			BSP_LCD_DrawRect(2+120*3, 64+105, 116, 101);	
			BSP_LCD_SetTextColor(PERIPH_PAD_GRADIENT_1);
			BSP_LCD_DrawRect(3+120*3, 65+105, 114, 99);	
			BSP_LCD_SetTextColor(PERIPH_PAD_GRADIENT_2);
			BSP_LCD_DrawRect(4+120*3, 66+105, 112, 97);	
			BSP_LCD_SetTextColor(PAD_BACK_COLOR);	
			BSP_LCD_FillRect(5+120*3, 67+105, 110, 95);		
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
			if(P_COLOR[pad_x-1]<8)  //pad is enable
				{	
				if(LOAD_ONE_PAD(CURRENT_PRESET)!=0)		//load one pad data
					{
					BSP_LCD_SetTextColor(LCD_COLOR_RED);		
					BSP_LCD_SetFont(&Font15P);	
					sprintf((char*)Buf, "%s", "Error loading PAD data");					
					BSP_LCD_DisplayStringAt(211, 88, Buf, TRANSPARENT_MODE);	
					HAL_Delay(3000);	
					}				
				else
					{
					if(need_analyzing_wfm==1)		//analyzing waveform	
						{
						WFMCREATE();
						need_analyzing_wfm = 0;		
						}		
					HAL_Delay(10);
					HAL_SPI_Transmit_DMA(&hspi2, COLOR, 100);	
					HAL_Delay(100);
					BSP_LCD_SelectLayer(1);							//draw to lay 1		
					BSP_LCD_SetTextColor(0x00000000);	
					BSP_LCD_FillRect(209, 86, 73, 18);		
					BSP_LCD_SetTextColor(LCD_COLOR_WHITE);	
					BSP_LCD_DrawLine(239, 46, 239, 148);			//big waveform center line	
					mi = (P_SAMPLE_OFFSET[pad_x]-P_SAMPLE_OFFSET[pad_x-1])>>9;		//calculate wzoom 0...9
					if(mi==0)
						{
						wzoom = 0;	
						}
					else if(mi==1)
						{
						wzoom = 1;	
						}
					else if(mi<4)
						{
						wzoom = 2;	
						}
					else if(mi<8)
						{
						wzoom = 3;	
						}
					else if(mi<16)
						{
						wzoom = 4;	
						}
					else if(mi<32)
						{
						wzoom = 5;	
						}
					else if(mi<64)
						{
						wzoom = 6;	
						}
					else if(mi<128)
						{
						wzoom = 7;	
						}
					else if(mi<256)
						{
						wzoom = 8;	
						}
					else
						{
						wzoom = 9;	
						}
					}	
				}
			else
				{
				BSP_LCD_SetTextColor(LCD_COLOR_WHITE);	
				BSP_LCD_DrawLine(239, 46, 239, 148);			//big waveform center line		
				}
			BSP_LCD_SelectLayer(0);	
			EPD_PROMPT(EPD_Position);		
			}
		if((EPD_Position<2) || EPD_Position==10)
			{			
			if(edit_epd_parameter==0)
				{
				DRAW_EPD_SELECTOR(EPD_Position, 1);	
				}
			else
				{
				DRAW_EPD_SELECTOR(EPD_Position, 0);	
				}			
			}
		else if((EPD_Position>1) || EPD_Position<10)		//table
			{
			if(edit_epd_parameter==0)
				{
				DRAW_EPD_SELECTOR(EPD_Position, 1);	
				}
			else
				{
				DRAW_EPD_SELECTOR(EPD_Position, 2);	//draw entering
				}		
			}
		int_EPD_DRAW_ALL_LINES();
		return;	
		}
	else if(LAY==EDIT_PRESET_DISPLAY)		//X => EDIT_PRESET_DISPLAY
		{
		if(update_all_page)
			{
			BSP_LCD_SelectLayer(0);		
			HAL_GPIO_WritePin(GPIOB, LED_SHIFT_Pin, GPIO_PIN_RESET);																//
			HAL_GPIO_WritePin(GPIOA, LED_PRESET_Pin, GPIO_PIN_RESET);																//
			HAL_GPIO_WritePin(GPIOI, LED_EDIT_Pin, GPIO_PIN_RESET);																	//
			HAL_GPIO_WritePin(LED_MENU_GPIO_Port, LED_MENU_Pin, GPIO_PIN_RESET);										//
			if(reverse_animation==1)
				{
				BSP_LCD_SelectLayer(1);
				BSP_LCD_SetTextColor(KBRD_TRANPARENT_COLOR);
				HAL_Delay(12);	
				BSP_LCD_FillRect(0, 196, 480, 50);	
				HAL_Delay(12);
				BSP_LCD_FillRect(0, 246, 480, 26);	
				HAL_Delay(12);
				BSP_LCD_SelectLayer(0);
				BSP_LCD_SetTextColor(LCD_COLOR_PAPER);		
				BSP_LCD_FillRect(0, 196, 480, 11);	
				HAL_Delay(12);	
				BSP_LCD_FillRect(0, 207, 480, 10);	
				HAL_Delay(12);						
				BSP_LCD_FillRect(0, 217, 480, 10);	
				HAL_Delay(12);						
				BSP_LCD_FillRect(0, 227, 480, 10);	
				HAL_Delay(12);		
				BSP_LCD_FillRect(0, 237, 480, 10);	
				HAL_Delay(12);		
				BSP_LCD_FillRect(0, 247, 480, 10);	
				HAL_Delay(12);		
				BSP_LCD_FillRect(0, 257, 480, 15);	
				HAL_Delay(12);	
				BSP_LCD_SelectLayer(1);
				BSP_LCD_SetTextColor(0x00000000);
				BSP_LCD_FillRect(0, 18, 480, 254);
				BSP_LCD_SelectLayer(0);	
				reverse_animation = 0;		
				}				
			int_DRAW_TRANSPARENT_BAR();		
			BSP_LCD_SelectLayer(1);
			BSP_LCD_Clear(0x00000000);
			BSP_LCD_SetFont(&Font15P);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			sprintf((char*)Buf, "%s", "|");		
			BSP_LCD_DisplayStringAt(5,2, Buf, TRANSPARENT_MODE);	
			sprintf((char*)Buf, "%s", presets_list[CURRENT_PRESET]);
			sprintf((char*)&Buf[strlen(Buf)],	 ": preset edit");
			BSP_LCD_DisplayStringAt(23, 2, Buf, TRANSPARENT_MODE);	
			BSP_LCD_SelectLayer(0);
			BSP_LCD_SetFont(&Font15P);	
			BSP_LCD_SetTextColor(LCD_COLOR_PAPER);	
			BSP_LCD_FillRect(0, 18, 480, 254);
			for(icnt=0;icnt<49298;icnt++)					//swampler image
				{
				if((icnt%2)==0)
					{
					mi = sampler_img[icnt>>1]>>4;
					}
				else
					{
					mi = sampler_img[icnt>>1]&0x0F;	
					}					
				BSP_LCD_DrawPixel(2+(icnt%314), 113+(icnt/314), CREATE_PIC_COLOR(mi));
				}
			BSP_LCD_SetTextColor(LCD_COLOR_SHADOW);		
			BSP_LCD_DrawRect(1, 19, 478, 252);
			BSP_LCD_SetTextColor(LCD_COLOR_DARK_1);	
			sprintf((char*)&Buf, "PRESET COLOR");
			BSP_LCD_DisplayStringAt(23, 66, Buf, TRANSPARENT_MODE);	
			sprintf((char*)&Buf, "PRESET RATING");
			BSP_LCD_DisplayStringAt(23, 91, Buf, TRANSPARENT_MODE);					
			for(icnt=0;icnt<8188;icnt++)					//Label
				{
				BSP_LCD_DrawPixel(374+(icnt%92), 120-icnt/92, (0xFF000000+disc[icnt][0]+256*disc[icnt][1]+65536*disc[icnt][2]));
				}	
			EPRD_PROMPT(EPRD_Position);
			}
		BSP_LCD_SelectLayer(1);
		if(edit_eprd_parameter==0)
			{
			if(EPRD_Position<3)					//dot-cursor
				{
				BSP_LCD_SetTextColor(LCD_COLOR_DARK_1);
				BSP_LCD_FillRect(9, 45+(25*EPRD_Position), 5, 5);
				BSP_LCD_DrawLine(10, 44+(25*EPRD_Position), 12, 44+(25*EPRD_Position));	
				BSP_LCD_DrawLine(10, 50+(25*EPRD_Position), 12, 50+(25*EPRD_Position));	
				BSP_LCD_DrawLine(8, 46+(25*EPRD_Position), 8, 48+(25*EPRD_Position));	
				BSP_LCD_DrawLine(14, 46+(25*EPRD_Position), 14, 48+(25*EPRD_Position));			
				}	
			else if(EPRD_Position==3)						//////////////////icon selector
				{
				BSP_LCD_SetTextColor(LCD_COLOR_PAPER);
				BSP_LCD_FillRect(372, 36, 5, 76);		
				BSP_LCD_FillRect(455, 36, 8, 76);	
				BSP_LCD_FillRect(373, 32, 95, 4);		
				BSP_LCD_FillRect(372, 112, 95, 10);		
				BSP_LCD_SetTextColor(ICON_SELBG_COLOR);
				BSP_LCD_FillRect(365, 36, 8, 76);	
				BSP_LCD_DrawLine(364, 37, 364, 110);	
				BSP_LCD_DrawLine(373, 37, 373, 110);	
				BSP_LCD_FillRect(459, 36, 8, 76);		
				BSP_LCD_DrawLine(458, 37, 458, 110);	
				BSP_LCD_DrawLine(467, 37, 467, 110);	
				int_DRAW_DOT_ICON_SEL(0);
				int_DRAW_DOT_ICON_SEL(94);
				}	
			}
		else	
			{
			if(EPRD_Position<3)					//dot-cursor
				{
				BSP_LCD_SetTextColor(LCD_COLOR_DARK_1);
				FillTriangle(8, 8, 15, 40+(25*EPRD_Position), 54+(25*EPRD_Position), 47+(25*EPRD_Position));			
				}	
			else if(EPRD_Position==3)						//////////////////icon selector
				{
				BSP_LCD_SetTextColor(LCD_COLOR_PAPER);
				BSP_LCD_FillRect(372, 36, 5, 76);		
				BSP_LCD_FillRect(455, 36, 8, 76);	
				BSP_LCD_FillRect(373, 32, 95, 4);		
				BSP_LCD_FillRect(372, 112, 95, 10);		
				BSP_LCD_SetTextColor(ICON_SELBG_COLOR);
				BSP_LCD_FillRect(365, 36, 8, 76);	
				BSP_LCD_DrawLine(364, 37, 364, 110);	
				BSP_LCD_DrawLine(373, 37, 373, 110);	
				BSP_LCD_FillRect(459, 36, 8, 76);		
				BSP_LCD_DrawLine(458, 37, 458, 110);	
				BSP_LCD_DrawLine(467, 37, 467, 110);
				BSP_LCD_SetTextColor(LCD_COLOR_PAPER);		
				FillTriangle(460, 460, 465, 68, 78, 73);	
				FillTriangle(371, 371, 366, 68, 78, 73);	
				}		
			}			
		int_EPRD_DRAW_ALL_LINES();		
		return;	
		}
	else if(LAY==KEYBOARD)		//X => KEYBOARD
		{
		if(update_all_page)
			{
			HAL_GPIO_WritePin(GPIOB, LED_SHIFT_Pin, GPIO_PIN_RESET);																//
			HAL_GPIO_WritePin(GPIOA, LED_PRESET_Pin, GPIO_PIN_RESET);																//
			HAL_GPIO_WritePin(GPIOI, LED_EDIT_Pin, GPIO_PIN_RESET);																	//
			HAL_GPIO_WritePin(LED_MENU_GPIO_Port, LED_MENU_Pin, GPIO_PIN_RESET);										//
			BSP_LCD_SelectLayer(1);
			BSP_LCD_SetTextColor(KBRD_TRANPARENT_COLOR);
			BSP_LCD_FillRect(0, 18, 480, 254);	
			BSP_LCD_SelectLayer(0);
			HAL_Delay(20);		
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			//BSP_LCD_FillRect(0, 209, 480, 63);	
			BSP_LCD_FillRect(0, 262, 480, 10);					//keyboard animation
			HAL_Delay(15);	
			BSP_LCD_FillRect(0, 252, 480, 10);		
			HAL_Delay(15);	
			BSP_LCD_FillRect(0, 242, 480, 10);		
			HAL_Delay(15);	
			BSP_LCD_FillRect(0, 232, 480, 10);		
			HAL_Delay(15);	
			BSP_LCD_FillRect(0, 222, 480, 10);		
			HAL_Delay(15);	
			BSP_LCD_FillRect(0, 209, 480, 13);	
			HAL_Delay(20);		
			BSP_LCD_DrawLine(0, 208, 478, 208);	
			BSP_LCD_DrawLine(0, 207, 477, 207);			
			BSP_LCD_FillRect(0, 198, 34, 9);
			BSP_LCD_DrawLine(2, 196, 29, 196);
			BSP_LCD_DrawLine(1, 197, 31, 197);
			BSP_LCD_DrawLine(34, 199, 35, 199);
			BSP_LCD_DrawLine(34, 200, 37, 200);			
			BSP_LCD_DrawLine(34, 201, 39, 201);	
			BSP_LCD_DrawLine(34, 202, 41, 202);
			BSP_LCD_DrawLine(34, 203, 43, 203);
			BSP_LCD_DrawLine(34, 204, 45, 204);
			BSP_LCD_DrawLine(34, 205, 47, 205);
			BSP_LCD_DrawLine(34, 206, 48, 206);
			BSP_LCD_SetTextColor(0xFF656353);				/////////////
			BSP_LCD_FillRect(10, 39, 350, 18);			//		
			BSP_LCD_SetTextColor(0xFF9C987E);				//	rectangle for preset name (renamer)
			BSP_LCD_DrawRect(9, 38, 352, 20);				//
			BSP_LCD_SetTextColor(0xFFF0EBC4);				//
			BSP_LCD_DrawRect(8, 37, 354, 22);				/////////////
			BSP_LCD_SetTextColor(PADS_LABEL_COLOR[4]);
			BSP_LCD_SetFont(&FontBMP);	
			sprintf((char*)Buf, "%s", "K");						//SHIFT
			BSP_LCD_DisplayStringAt(4, 198, Buf, TRANSPARENT_MODE);	
			BSP_LCD_SelectLayer(1);
			BSP_LCD_SetFont(&Font15P);
			BSP_LCD_SetTextColor(0x00000000);
			BSP_LCD_FillRect(0, 209, 480, 63);	
			BSP_LCD_DrawLine(0, 208, 478, 208);	
			BSP_LCD_DrawLine(0, 207, 477, 207);			
			BSP_LCD_FillRect(0, 198, 34, 9);
			BSP_LCD_DrawLine(2, 196, 29, 196);
			BSP_LCD_DrawLine(1, 197, 31, 197);
			BSP_LCD_DrawLine(34, 199, 35, 199);
			BSP_LCD_DrawLine(34, 200, 37, 200);			
			BSP_LCD_DrawLine(34, 201, 39, 201);	
			BSP_LCD_DrawLine(34, 202, 41, 202);
			BSP_LCD_DrawLine(34, 203, 43, 203);
			BSP_LCD_DrawLine(34, 204, 45, 204);
			BSP_LCD_DrawLine(34, 205, 47, 205);
			BSP_LCD_DrawLine(34, 206, 48, 206);
			BSP_LCD_FillRect(8, 37, 354, 22);				//clear window for preset name
			sprintf((char*)rnm_buff, presets_list[CURRENT_PRESET]);			//copy preset name
			blink_cursor = 1;
			icnt = strlen(rnm_buff);
			rnm_buff[icnt] = 0x82;
			rnm_buff[icnt+1] = 0;
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			BSP_LCD_DisplayStringAt(13, 41, rnm_buff, TRANSPARENT_MODE);			//preset name_
			for(icnt=0;icnt<74;icnt++)					//keyboard generate
				{
				Buf[0] = lttrs[icnt/37][icnt%37];
				Buf[1] = 0;
				if((icnt%37)<5 || (icnt%37)>30)
					{
					if(icnt==73)
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
				BSP_LCD_DisplayStringAt(letter_offs[icnt/37][icnt%37], 219+26*(icnt/37), Buf, TRANSPARENT_MODE);			
				}
			KBRD_Position = 17;	
			int_KBRD_(KBRD_UP);	
			}	
		return;	
		}	
	else if(LAY==EDIT_FLLIST_DISPLAY)		//X => EDIT_FLLIST_DISPLAY
		{
		if(update_all_page)
			{
			HAL_GPIO_WritePin(GPIOB, LED_SHIFT_Pin, GPIO_PIN_RESET);																//
			HAL_GPIO_WritePin(GPIOA, LED_PRESET_Pin, GPIO_PIN_RESET);																//
			HAL_GPIO_WritePin(GPIOI, LED_EDIT_Pin, GPIO_PIN_RESET);																	//
			HAL_GPIO_WritePin(LED_MENU_GPIO_Port, LED_MENU_Pin, GPIO_PIN_RESET);										//
			BSP_LCD_SelectLayer(0);		
			int_DRAW_TRANSPARENT_BAR();	
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);	
			BSP_LCD_FillRect(0, 18, 480, 254);		
			BSP_LCD_SetTextColor(LCD_COLOR_DARK_1);	
			BSP_LCD_DrawLine(0, 18, 479, 18);
			BSP_LCD_DrawLine(0, 37, 479, 37);
			BSP_LCD_DrawLine(0, 56, 479, 56);
			BSP_LCD_DrawLine(0, 75, 479, 75);
			BSP_LCD_DrawLine(0, 94, 479, 94);
			BSP_LCD_DrawLine(0, 113, 479, 113);
			BSP_LCD_DrawLine(0, 132, 479, 132);
			BSP_LCD_DrawLine(0, 151, 479, 151);
			BSP_LCD_DrawLine(0, 170, 479, 170);
			BSP_LCD_DrawLine(479, 18, 479, 169);		//vertical line
			BSP_LCD_DrawLine(74, 18, 74, 169);			//vertical line	
			BSP_LCD_DrawLine(0, 18, 0, 169);				//vertical line	
			BSP_LCD_SetFont(&Font15P);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			sprintf((char*)Buf, "To fast load selected presets,");
			BSP_LCD_DisplayStringAt(118, 199, Buf, TRANSPARENT_MODE);
			sprintf((char*)Buf, "press SHIFT + PAD on the home display.");
			BSP_LCD_DisplayStringAt(81, 218, Buf, TRANSPARENT_MODE);
			}
		BSP_LCD_SelectLayer(1);
		BSP_LCD_Clear(0x00000000);
		BSP_LCD_SetFont(&Font15P);
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			
		for(icnt=0;icnt<192;icnt++)					////FAST LOAD icon
			{
			if((iFL[icnt/16]>>(icnt%16))%2)
				{
				BSP_LCD_DrawPixel(20-icnt%16, 3+icnt/16, LCD_COLOR_WHITE);
				}	
			}	
		sprintf((char*)Buf,	 "FAST LOAD list edit");
		BSP_LCD_DisplayStringAt(23, 2, Buf, TRANSPARENT_MODE);
		BSP_LCD_SelectLayer(0);	
		if(edit_fl_parameter==0)
			{			
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);		
			BSP_LCD_FillRect(1, (18+(19*FLCurrentCursorPosition)), 73, 9);			////Draw selected cursor	
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_2);
			BSP_LCD_FillRect(1, (27+(19*FLCurrentCursorPosition)), 73, 5);
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_1);
			BSP_LCD_FillRect(1, (32+(19*FLCurrentCursorPosition)), 73, 5);
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_3);		
			BSP_LCD_FillRect(75, (18+(19*FLCurrentCursorPosition)), 404, 9);			////Draw selected cursor	
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_5);
			BSP_LCD_FillRect(75, (27+(19*FLCurrentCursorPosition)), 404, 5);
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_4);
			BSP_LCD_FillRect(75, (32+(19*FLCurrentCursorPosition)), 404, 5);				
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			FillTriangle(7, 7, 14, 20+(19*FLCurrentCursorPosition), 34+(19*FLCurrentCursorPosition), 27 +(19*FLCurrentCursorPosition));		
			}
		else
			{
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_3);		
			BSP_LCD_FillRect(1, (18+(19*FLCurrentCursorPosition)), 73, 9);			////Draw selected cursor	
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_5);
			BSP_LCD_FillRect(1, (27+(19*FLCurrentCursorPosition)), 73, 5);
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_4);
			BSP_LCD_FillRect(1, (32+(19*FLCurrentCursorPosition)), 73, 5);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);		
			BSP_LCD_FillRect(75, (18+(19*FLCurrentCursorPosition)), 404, 9);			////Draw selected cursor	
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_2);
			BSP_LCD_FillRect(75, (27+(19*FLCurrentCursorPosition)), 404, 5);
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_1);
			BSP_LCD_FillRect(75, (32+(19*FLCurrentCursorPosition)), 404, 5);				
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			FillTriangle(81, 81, 88, 20+(19*FLCurrentCursorPosition), 34+(19*FLCurrentCursorPosition), 27 +(19*FLCurrentCursorPosition));	
			}	
		BSP_LCD_SelectLayer(1);	
		int_FL_DRAW_ALL_LINES();		
		return;	
		}
	else if(LAY==BROWSER)													//X => BROWSER
		{	
		if(update_all_page==1)
			{
			HAL_GPIO_WritePin(GPIOB, LED_SHIFT_Pin, GPIO_PIN_RESET);																//
			HAL_GPIO_WritePin(GPIOA, LED_PRESET_Pin, GPIO_PIN_RESET);																//
			HAL_GPIO_WritePin(GPIOI, LED_EDIT_Pin, GPIO_PIN_RESET);																	//
			HAL_GPIO_WritePin(LED_MENU_GPIO_Port, LED_MENU_Pin, GPIO_PIN_RESET);										//
			BSP_LCD_SelectLayer(0);
			int_DRAW_TRANSPARENT_BAR();		
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);	
			BSP_LCD_FillRect(0, 18, 480, 254);
			BSP_LCD_SetTextColor(LCD_COLOR_DARK_1);
			BSP_LCD_DrawRect(0, 18, 14, 247);							//scroll frame		
			}	
		BSP_LCD_SelectLayer(0);	
		intDrawLayer0_BR(BRCCP);			
		BSP_LCD_SelectLayer(1);			
		BSP_LCD_SetFont(&Font15P);		
		BSP_LCD_Clear(0x00000000);			
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		Buf[0] = 0x83;		//sd card icon
		Buf[1] = 0;				//	
		BSP_LCD_DisplayStringAt(5,2, Buf, TRANSPARENT_MODE);
		sprintf((char*)Buf, "/%s/", &path_opened[3]);
		BSP_LCD_DisplayStringAt(19, 2, Buf, TRANSPARENT_MODE);	
		if(update_all_page!=1)
			{
			BSP_LCD_SelectLayer(1);		
			BSP_LCD_SetTextColor(0x00000000);	
			BSP_LCD_FillRect(20, 20+(19*BRCCP), 15, 19);		
			}
		SCAN_DIR(path_opened);	
		int_BR_DRAW_ALL_LINES();
		return;				
		}	
	else if(LAY==EDIT_UTILITY)		//X => EDIT UTILITY
		{	
		if(update_all_page)
			{
			BSP_LCD_SelectLayer(1);	
			BSP_LCD_SetTextColor(0x00000000);
			BSP_LCD_FillRect(231, 0, 161, 101);			//clear layer (1) square
			BSP_LCD_SelectLayer(0);		
			HAL_GPIO_WritePin(GPIOB, LED_SHIFT_Pin, GPIO_PIN_RESET);													//
			HAL_GPIO_WritePin(GPIOA, LED_PRESET_Pin, GPIO_PIN_RESET);													//
			HAL_GPIO_WritePin(GPIOI, LED_EDIT_Pin, GPIO_PIN_SET);															//
			HAL_GPIO_WritePin(LED_MENU_GPIO_Port, LED_MENU_Pin, GPIO_PIN_SET);								//
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_5);					////////////////////
			BSP_LCD_FillRect(233, 0, 157, 18);								//												
			BSP_LCD_DrawLine(232, 1, 232, 19);								//
			BSP_LCD_DrawLine(390, 1, 390, 19);								//	header window
			BSP_LCD_DrawLine(231, 2, 231, 98);								//
			BSP_LCD_DrawLine(391, 2, 391, 98);								//				
			BSP_LCD_DrawLine(233, 100, 389, 100);							//	
			BSP_LCD_DrawPixel(389, 99, LCD_COLOR_LIGHT_5);		//
			BSP_LCD_DrawPixel(390, 99, LCD_COLOR_LIGHT_5);		//
			BSP_LCD_DrawPixel(390, 98, LCD_COLOR_LIGHT_5);		//
			BSP_LCD_DrawPixel(233, 99, LCD_COLOR_LIGHT_5);		//
			BSP_LCD_DrawPixel(232, 99, LCD_COLOR_LIGHT_5);		//
			BSP_LCD_DrawPixel(232, 98, LCD_COLOR_LIGHT_5);		//
			BSP_LCD_SetTextColor(LCD_COLOR_DARK_1);		///////////
			BSP_LCD_DrawLine(233, 18, 389, 18);				//
			BSP_LCD_DrawLine(233, 98, 389, 98);				//	body window
			BSP_LCD_DrawLine(234, 99, 388, 99);				//
			BSP_LCD_FillRect(232, 19, 159, 79);				//			
			BSP_LCD_SetFont(&Font15P);
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);		
			sprintf((char*)Buf, "%s", "EDIT");		
			BSP_LCD_DisplayStringAt(295, 2, Buf, TRANSPARENT_MODE);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);																											////////////////////////	
			BSP_LCD_DrawLine(238, (21+(19*CurrentEUPosition)), 384, (21+(19*CurrentEUPosition)));				//
			BSP_LCD_DrawLine(236, (22+(19*CurrentEUPosition)), 386, (22+(19*CurrentEUPosition)));				//
			BSP_LCD_FillRect(235, (23+(19*CurrentEUPosition)), 153, 7);																	//	Draw selected cursor	
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_2);																										//
			BSP_LCD_FillRect(235, (30+(19*CurrentEUPosition)), 153, 5);																	//
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHT_1);																										//
			BSP_LCD_FillRect(235, (35+(19*CurrentEUPosition)), 153, 3);																	//
			BSP_LCD_DrawLine(236, (38+(19*CurrentEUPosition)), 386, (38+(19*CurrentEUPosition)));				//
			BSP_LCD_DrawLine(238, (39+(19*CurrentEUPosition)), 384, (39+(19*CurrentEUPosition)));				//////////////////////////
			int_EU_DRAW_ALL_LINES();	
			return;	
			}
		return;		
		}
	else if(LAY==MOVE_PRESET)													//X => MOVE_PRESET
		{
		HAL_GPIO_WritePin(GPIOB, LED_SHIFT_Pin, GPIO_PIN_RESET);																//
		HAL_GPIO_WritePin(GPIOA, LED_PRESET_Pin, GPIO_PIN_SET);																	//
		HAL_GPIO_WritePin(GPIOI, LED_EDIT_Pin, GPIO_PIN_RESET);																	//
		HAL_GPIO_WritePin(LED_MENU_GPIO_Port, LED_MENU_Pin, GPIO_PIN_RESET);										//
		BSP_LCD_SelectLayer(1);
		BSP_LCD_SetTextColor(0x00000000);	
		BSP_LCD_FillRect(0, 0, 344, 18);
		MPRSTCCP = PRSTCCP;
		CurrentMPRSTPosition = CurrentPRSTPosition;
		moveable_preset = PRSTCCP+CurrentPRSTPosition-1;
		BSP_LCD_FillRect(14, 18+(19*MPRSTCCP), 256, 19);	//clear string
		BSP_LCD_SetFont(&Font15P);	
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		sprintf((char*)Buf, "| %s%s", presets_list[PRSTCCP+CurrentPRSTPosition-1], ": MOVE");
		BSP_LCD_DisplayStringAt(5, 2, Buf, TRANSPARENT_MODE);	
		BSP_LCD_SelectLayer(0);
		if(MPRSTCCP%2==0)
			{
			BSP_LCD_SetTextColor(LCD_COLOR_DARK_1);	
			}			
		else
			{
			BSP_LCD_SetTextColor(LCD_COLOR_DARK_2);	
			}
		BSP_LCD_FillRect(14, 18+(19*MPRSTCCP), 33, 19);	
		int_int_draw_selected_cursor(MPRSTCCP);
		int_MPRST_DRAW_ALL_LINES();
		return;	
		}
	return;	
	};

		
////////////////////////////////////////////////////	
//Redraw scroll on new position	
//	
void ReDrawScroll(uint16_t total_elements, uint16_t current_element_pos)
	{
	ForceDrawVLine(5, ScrollPosition+24, ScrollLong-2, LCD_COLOR_BLACK);							//
	ForceDrawVLine(6, ScrollPosition+23, ScrollLong, LCD_COLOR_BLACK);								//	SCROLL
	ForceDrawVLine(7, ScrollPosition+23, ScrollLong, LCD_COLOR_BLACK);								//
	ForceDrawVLine(8, ScrollPosition+24, ScrollLong-2, LCD_COLOR_BLACK);							//
		///Calculate scroll	
	if(total_elements<14)							
		{
		ScrollLong = 237;											
		ScrollPosition = 0;	
		}
	else
		{
		ScrollLong = 3081/total_elements;
		if(ScrollLong>237)										
			{
			ScrollLong = 237;	
			}
		else if(ScrollLong<5)
			{
			ScrollLong = 5;	
			}	
		ScrollPosition = ((current_element_pos-1)*(237-ScrollLong))/(total_elements-13);	
		}
	ForceDrawVLine(5, ScrollPosition+24, ScrollLong-2, LCD_COLOR_WHITE);							//
	ForceDrawVLine(6, ScrollPosition+23, ScrollLong, 	LCD_COLOR_WHITE);								//	SCROLL
	ForceDrawVLine(7, ScrollPosition+23, ScrollLong, 	LCD_COLOR_WHITE);								//
	ForceDrawVLine(8, ScrollPosition+24, ScrollLong-2, LCD_COLOR_WHITE);							//		
	}	
	
////////////////////////////////////////////////////
//	draw triangle for preset browse
//	pos - position 0 - preset list, 1 - edit preset 
//	
//	
void intDrawTriangle(uint8_t CCP)
	{
	BSP_LCD_SetTextColor(LCD_COLOR_PAPER);
	BSP_LCD_DrawLine(270, 18, 270, 264)	;	
	BSP_LCD_SetTextColor(LCD_COLOR_SHADOW);
	BSP_LCD_DrawLine(271, 19, 271, 263);	
	for(uint16_t j = 0; j<304; j++)
		{
		BSP_LCD_DrawPixel(256+(j&0xF), ((36+(19*CCP))-(j>>4)), (0xFF000000+strelka[j][0]+256*strelka[j][1]+65536*strelka[j][2]));
		}
	BSP_LCD_DrawPixel(271, 18, LCD_COLOR_PAPER);	
	BSP_LCD_DrawPixel(271, 19, LCD_COLOR_SHADOW);	
	BSP_LCD_DrawPixel(271, 264, LCD_COLOR_PAPER);	
	BSP_LCD_DrawPixel(271, 263, LCD_COLOR_SHADOW);		
	return;
	}	
	
/////////////////////////////////	
//
//internal function for presets list 	
void int_DRAW_STARS_RATING(uint8_t rat, uint8_t rat_color, uint8_t pos)
	{
	uint16_t j, k;
	uint32_t RATING_COLOR;
	uint32_t PERIM_COLOR;		
	if(rat_color==0xFF)
		{				
		RATING_COLOR = 0xFF707070;
		PERIM_COLOR = 0xFF202020;			
		}
	else
		{
		RATING_COLOR = PADS_LABEL_COLOR[rat_color];	
		uint32_t _temp_col;
		uint8_t _r, _g, _b;
		_temp_col = 215*(RATING_COLOR%256);	
		_b = _temp_col>>8;	
		_temp_col = 215*((RATING_COLOR>>8)%256);	
		_g = _temp_col>>8;					
		_temp_col = 215*((RATING_COLOR>>16)%256);	
		_r = _temp_col>>8;		
		PERIM_COLOR = 0xFF000000+_b+256*_g+65536*_r;					
		}	
	for(j=0;j<5;j++)							////STARS
		{		
		for(k=0;k<208;k++)
			{
			if((iSTAR[k/16]>>(k%16))%2)
				{
				if(pos==0)
					{					
					BSP_LCD_DrawPixel((j*14)+294-k%16, 116+k/16, PERIM_COLOR);
					}
				else
					{
					BSP_LCD_DrawPixel((j*14)+172-k%16, 91+k/16, PERIM_COLOR);	
					}					
				}	
			}	
		if((rat&0x07)>j)
			{
			for(k=0;k<208;k++)		////STARS FILLED
				{
				if((iSTAR_FILLED[k/16]>>(k%16))%2)
					{
					if(pos==0)
						{		
						BSP_LCD_DrawPixel((j*14)+294-k%16, 116+k/16, RATING_COLOR);
						}	
					else
						{	
						BSP_LCD_DrawPixel((j*14)+172-k%16, 91+k/16, RATING_COLOR);	
						}							
					}	
				}		
			}
		}
	return;	
	}	
	


	
/////////////////////////////////	
//
//internal function for presets list 		
void int_DRAW_ICO(uint8_t ICO_NUMB, uint8_t col, uint8_t pos)
	{
	uint16_t j;	
	uint32_t _temp_col;
	uint8_t _r, _g, _b;		
	uint16_t posx;
	if(pos==0)
		{
		posx = 399;	
		}
	else
		{
		posx = 389;	
		}
	for(j = 0; j<3136; j++)					//INSTRUMENTS ICON
		{
		if(ICON_MASSIVE[ICO_NUMB][j]<56)
			{
			BSP_LCD_DrawPixel(posx+(j%56), 101-j/56, 0xFF383838);	
			}
		else if(ICON_MASSIVE[ICO_NUMB][j]==0xFF)
			{
			if(col==0xFF)
				{
				BSP_LCD_DrawPixel(posx+(j%56), 101-j/56, 0xFFFFFFFF);		
				}
			else
				{
				BSP_LCD_DrawPixel(posx+(j%56), 101-j/56, PADS_LABEL_COLOR[col]);	
				}		
			}			
		else
			{
			if(col==0xFF)
				{	
				BSP_LCD_DrawPixel(posx+(j%56), 101-j/56, (0xFF000000+ICON_MASSIVE[ICO_NUMB][j]+256*ICON_MASSIVE[ICO_NUMB][j]+65536*ICON_MASSIVE[ICO_NUMB][j]));	
				}	
			else
				{
				_temp_col = ICON_MASSIVE[ICO_NUMB][j]*(PADS_LABEL_COLOR[col]%256);	
				_b = _temp_col>>8;	
				_temp_col = ICON_MASSIVE[ICO_NUMB][j]*((PADS_LABEL_COLOR[col]>>8)%256);	
				_g = _temp_col>>8;					
				_temp_col = ICON_MASSIVE[ICO_NUMB][j]*((PADS_LABEL_COLOR[col]>>16)%256);	
				_r = _temp_col>>8;		
				BSP_LCD_DrawPixel(posx+(j%56), 101-j/56, (0xFF000000+_b+256*_g+65536*_r));		
				}				
			}			
		}	
	return;	
	}


///////////////////////////////////////////////////////////////	
//	draw static gui pads for home display
//
void Draw_Static_Pads(void)
	{
	uint8_t pds;	
	uint8_t seq;
	uint8_t wfm;	
	uint8_t shft;	
		
	BSP_LCD_SetFont(&Font8);	
	for(pds=0;pds<8;pds++)
		{
		BSP_LCD_SetTextColor(PERIPH_PAD_GRADIENT_0);
		BSP_LCD_DrawRect(2+120*(pds%4), 64+105*(1-(pds>>2)), 116, 101);	
		BSP_LCD_SetTextColor(PERIPH_PAD_GRADIENT_1);
		BSP_LCD_DrawRect(3+120*(pds%4), 65+105*(1-(pds>>2)), 114, 99);	
		BSP_LCD_SetTextColor(PERIPH_PAD_GRADIENT_2);
		BSP_LCD_DrawRect(4+120*(pds%4), 66+105*(1-(pds>>2)), 112, 97);	
		BSP_LCD_SetTextColor(PAD_BACK_COLOR);	
		BSP_LCD_FillRect(5+120*(pds%4), 67+105*(1-(pds>>2)), 110, 95);	
			
		if(P_COLOR[pds]<8 && (CURRENT_PRESET!=0xFF))					//pad enable
			{
			BSP_LCD_SetTextColor(PADS_LABEL_COLOR[P_COLOR[pds]]);	
			BSP_LCD_FillRect(7+120*(pds%4), 69+105*(1-(pds>>2)), 11, 12);		
			BSP_LCD_FillRect(20+120*(pds%4), 69+105*(1-(pds>>2)), 34, 12);
			BSP_LCD_FillRect(7+120*(pds%4), 83+105*(1-(pds>>2)), 27, 12);		
			BSP_LCD_FillRect(36+120*(pds%4), 83+105*(1-(pds>>2)), 35, 12);
			BSP_LCD_FillRect(73+120*(pds%4), 83+105*(1-(pds>>2)), 40, 12);	
				
			if(P_QUANTIZE[pds]==1)	
				{
				BSP_LCD_SetTextColor(PADS_LABEL_COLOR[P_COLOR[pds]]);		
				}
			else
				{
				BSP_LCD_SetTextColor(LCD_COLOR_DISABLE);		
				}
			BSP_LCD_FillRect(56+120*(pds%4), 69+105*(1-(pds>>2)), 12, 12);	
			
			if(P_SYNC[pds]==1)	
				{
				BSP_LCD_SetTextColor(PADS_LABEL_COLOR[P_COLOR[pds]]);		
				}
			else
				{
				BSP_LCD_SetTextColor(LCD_COLOR_DISABLE);		
				}	
			BSP_LCD_FillRect(70+120*(pds%4), 69+105*(1-(pds>>2)), 11, 12);
				
			BSP_LCD_SetTextColor(LCD_COLOR_DISABLE);		
			BSP_LCD_FillRect(83+120*(pds%4), 69+105*(1-(pds>>2)), 30, 12);	
			BSP_LCD_SetTextColor(TEXT_PAD_COLOR);	
			Buf[0] = pds+0x31;																						//pad number
			Buf[1] = 0;
			BSP_LCD_DisplayStringAt(9+120*(pds%4), 71+105*(1-(pds>>2)), Buf, TRANSPARENT_MODE);
				
			if(P_TYPE[pds]==0)			//sample
				{
				sprintf((char*)Buf, "%s", "SMPL");
				}
			else
				{
				sprintf((char*)Buf, "%s", "SQNC");	
				}
			BSP_LCD_DisplayStringAt(23+120*(pds%4), 71+105*(1-(pds>>2)), Buf, TRANSPARENT_MODE);

			sprintf((char*)Buf, "%s", "Q");
			BSP_LCD_DisplayStringAt(58+120*(pds%4), 71+105*(1-(pds>>2)), Buf, TRANSPARENT_MODE);
			sprintf((char*)Buf, "%s", "S");
			BSP_LCD_DisplayStringAt(72+120*(pds%4), 71+105*(1-(pds>>2)), Buf, TRANSPARENT_MODE);		
			sprintf((char*)Buf, "%s", "OFF");
			BSP_LCD_DisplayStringAt(88+120*(pds%4), 71+105*(1-(pds>>2)), Buf, TRANSPARENT_MODE);
			if(P_BPM[pds]<1000)			//if bpm<100.0
				{
				sprintf((char*)Buf, "%02lu.%01lu", P_BPM[pds]/10, P_BPM[pds]%10);			
				BSP_LCD_DisplayStringAt(45+120*(pds%4), 85+105*(1-(pds>>2)), Buf, TRANSPARENT_MODE);	
				}
			else
				{
				sprintf((char*)Buf, "%03lu.%01lu", P_BPM[pds]/10, P_BPM[pds]%10);			
				BSP_LCD_DisplayStringAt(38+120*(pds%4), 85+105*(1-(pds>>2)), Buf, TRANSPARENT_MODE);	
				}				
				
			if(P_GAIN[pds]<31)
				{
				sprintf((char*)Buf, "+%01lu.%01ludB", (30-P_GAIN[pds])/10, (30-P_GAIN[pds])%10);	
				BSP_LCD_DisplayStringAt(74+120*(pds%4), 85+105*(1-(pds>>2)), Buf, TRANSPARENT_MODE);						
				}		
			else
				{
				sprintf((char*)Buf, "-%01lu.%01ludB", (P_GAIN[pds]-30)/10, (P_GAIN[pds]-30)%10);	
				BSP_LCD_DisplayStringAt(75+120*(pds%4), 85+105*(1-(pds>>2)), Buf, TRANSPARENT_MODE);		
				}
			DrawLoopShot(P_TRIG[pds], PADS_LABEL_COLOR[P_COLOR[pds]], TEXT_PAD_COLOR, pds);	
			if(P_TYPE[pds]==0)			//sample
				{
				for(wfm=0;wfm<100;wfm++)	
					{
					ForceDrawVLine(wfm+10+120*(pds%4), 116+105*(1-(pds>>2)) - (P_WAVEFORM[pds][wfm]&0x0F), ((P_WAVEFORM[pds][wfm]&0x0F)<<1)+1, WS_COLOR_MAP[P_WAVEFORM[pds][wfm]>>7]);
					}
				previous_play_position[pds] = (99*P_START_ADR[pds])/((P_SAMPLE_OFFSET[pds+1]-P_SAMPLE_OFFSET[pds])+P_START_ADR[pds]);		
				ForceDrawVLine(previous_play_position[pds]+10+120*(pds%4), 101+105*(1-(pds>>2)), 31, 0xFFFFFFFF);	
				BSP_LCD_DrawPixel(previous_play_position[pds]+10+120*(pds%4), 132+105*(1-(pds>>2)), PADS_LABEL_COLOR[P_COLOR[pds]]);	//cue triangle
				BSP_LCD_SetTextColor(PADS_LABEL_COLOR[P_COLOR[pds]]);	
				BSP_LCD_DrawHLine(previous_play_position[pds]+9+120*(pds%4), 133+105*(1-(pds>>2)), 3);	
				BSP_LCD_DrawHLine(previous_play_position[pds]+8+120*(pds%4), 134+105*(1-(pds>>2)), 5);	
				BSP_LCD_SetTextColor(0xFFBFBFBF);	
				BSP_LCD_SetBackColor(PAD_BACK_COLOR);	
				sprintf((char*)Buf, "%s", "0:");	
				BSP_LCD_DisplayStringAt(39+120*(pds%4), 139+105*(1-(pds>>2)), Buf, LEFT_MODE);	
				previous_time_position[pds] = P_START_ADR[pds]/588;						
				sprintf((char*)Buf, "%02lu.%02lu", (previous_time_position[pds]/75)%4500, previous_time_position[pds]%75);					
				BSP_LCD_DisplayStringAt(49+120*(pds%4), 139+105*(1-(pds>>2)), Buf, LEFT_MODE);	
				BSP_LCD_SetBackColor(0xFF000000);				//return black back color, more useful	
				}
			else																//sequencer
				{				
				BSP_LCD_SetTextColor(SQ_BACK_COLOR);	
				BSP_LCD_FillRect(10+120*(pds%4), 101+105*(1-(pds>>2)), 100, 46);	
				BSP_LCD_SetTextColor(0xFF525252);	
				BSP_LCD_DrawRect(9+120*(pds%4), 100+105*(1-(pds>>2)), 102, 48);
				for(seq=0;seq<16;seq++)
					{
					if(pds==ACTIVE_PAD && (P_WAVEFORM[ACTIVE_PAD][64]>0))					//if current pad is active and sequence lenght> 4 beats
						{
						shft = BEAT_CNT;	
						shft = shft>>2;	
						shft = shft<<4;		
						}					
					else
						{
						shft = 0;	
						}						
						
					if(seq==0)							//gradients red
						{	
						if(P_WAVEFORM[pds][seq+shft]==1)
							{	
							int_red_gradient(seq, pds);
							}							
						else
							{									
							BSP_LCD_SetTextColor(RED_PERIMETER_L);
							}
						}		
					else if(seq%4==0)							//gradients blue
						{	
						if(P_WAVEFORM[pds][seq+shft]==1)
							{	
							int_blue_gradient(seq, pds);
							}							
						else
							{		
							BSP_LCD_SetTextColor(BLUE_PERIMETER_L);
							}
						}
					else							//gradients white
						{
						if(P_WAVEFORM[pds][seq+shft]==1)
							{	
							int_grey_gradient(seq, pds);
							}							
						else
							{		
							BSP_LCD_SetTextColor(GREY_PERIMETER_L);
							}						
						}						
					int_sqnc_perimeter(seq, pds);	

						
					if(seq==8 || seq==10 || seq==12 || seq==14)					//squares
						{
						if(seq==8)
							{
							BSP_LCD_SetTextColor(SQ_STEP_CLR_0);	
							BSP_LCD_FillRect(16+24*(shft>>4)+120*(pds%4), 107+32+105*(1-(pds>>2)), 2, 2);		
							BSP_LCD_FillRect(30+24*(shft>>4)+120*(pds%4), 107+32+105*(1-(pds>>2)), 2, 2);		
							BSP_LCD_SetTextColor(SQ_STEP_CLR_1);		
							BSP_LCD_FillRect(18+24*(shft>>4)+120*(pds%4), 107+32+105*(1-(pds>>2)), 2, 2);		
							BSP_LCD_FillRect(28+24*(shft>>4)+120*(pds%4), 107+32+105*(1-(pds>>2)), 2, 2);		
							BSP_LCD_SetTextColor(SQ_STEP_CLR_2);	
							BSP_LCD_FillRect(20+24*(shft>>4)+120*(pds%4), 107+32+105*(1-(pds>>2)), 2, 2);		
							BSP_LCD_FillRect(26+24*(shft>>4)+120*(pds%4), 107+32+105*(1-(pds>>2)), 2, 2);		
							BSP_LCD_SetTextColor(SQ_STEP_CLR_3);	
							BSP_LCD_FillRect(22+24*(shft>>4)+120*(pds%4), 107+32+105*(1-(pds>>2)), 4, 2);		
							BSP_LCD_SetTextColor(RED_PERIMETER_SQ);		
							}
						else if(seq==10)
							{
							if(P_WAVEFORM[pds][64]==1 || P_WAVEFORM[pds][64]==3)	
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
							if(P_WAVEFORM[pds][64]==3)	
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
							if(P_WAVEFORM[pds][64]==3)	
								{
								BSP_LCD_SetTextColor(RED_PERIMETER_SQ);	
								}
							else
								{
								BSP_LCD_SetTextColor(GREY_PERIMETER_L);		
								}
							}
						BSP_LCD_DrawHLine(16+12*(seq%8)+120*(pds%4), 106+32+105*(1-(pds>>2)), 16);		
						BSP_LCD_DrawHLine(16+12*(seq%8)+120*(pds%4), 109+32+105*(1-(pds>>2)), 16);	
						BSP_LCD_DrawVLine(15+12*(seq%8)+120*(pds%4), 107+32+105*(1-(pds>>2)), 2);	
						BSP_LCD_DrawVLine(32+12*(seq%8)+120*(pds%4), 107+32+105*(1-(pds>>2)), 2);	
						}		
					}	
				}			
			BSP_LCD_SetTextColor(PADS_LABEL_COLOR[P_COLOR[pds]]);		//sample name		
			uint8_t xlong;
			uint8_t xpath;
			xpath = 0;	
			xlong = strlen(P_SAMPLE_NAME[pds]);	
			if(xlong>0)
				{
				xlong--;	
				}
			while(xlong>0)
				{
				if(P_SAMPLE_NAME[pds][xlong]==47 || P_SAMPLE_NAME[pds][xlong]==92)			//have a folder symbol in path
					{
					xpath = xlong;	
					xlong = 1;	
					}	
				xlong--;	
				}				
			if(xpath==0)
				{
				sprintf((char*)Buf, "%s", P_SAMPLE_NAME[pds]);	
				}
			else
				{
				sprintf((char*)Buf, "%s", &P_SAMPLE_NAME[pds][xpath+1]);		
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
			BSP_LCD_DisplayStringAt(9+120*(pds%4), 151+105*(1-(pds>>2)), Buf, TRANSPARENT_MODE);					
			COLOR_SET(PADS_L_COLOR[P_COLOR[pds]], pds);	
			}	
		else										//this pad disable
			{
			BSP_LCD_SetTextColor(LCD_COLOR_DISABLE);		
			BSP_LCD_FillRect(7+120*(pds%4), 69+105*(1-(pds>>2)), 11, 12);		
			BSP_LCD_FillRect(20+120*(pds%4), 69+105*(1-(pds>>2)), 34, 12);		
			BSP_LCD_FillRect(56+120*(pds%4), 69+105*(1-(pds>>2)), 12, 12);	
			BSP_LCD_FillRect(70+120*(pds%4), 69+105*(1-(pds>>2)), 11, 12);	
			BSP_LCD_FillRect(7+120*(pds%4), 83+105*(1-(pds>>2)), 27, 12);		
			BSP_LCD_FillRect(36+120*(pds%4), 83+105*(1-(pds>>2)), 35, 12);
			BSP_LCD_FillRect(73+120*(pds%4), 83+105*(1-(pds>>2)), 40, 12);		
			BSP_LCD_FillRect(83+120*(pds%4), 69+105*(1-(pds>>2)), 30, 12);	
			BSP_LCD_SetTextColor(TEXT_PAD_COLOR);	
			Buf[0] = pds+0x31;
			Buf[1] = 0;
			BSP_LCD_DisplayStringAt(9+120*(pds%4), 71+105*(1-(pds>>2)), Buf, TRANSPARENT_MODE);	
			sprintf((char*)Buf, "%s", "----");	
			BSP_LCD_DisplayStringAt(27+120*(pds%4), 70+105*(1-(pds>>2)), Buf, TRANSPARENT_MODE);	
			sprintf((char*)Buf, "%s", "Q");
			BSP_LCD_DisplayStringAt(58+120*(pds%4), 71+105*(1-(pds>>2)), Buf, TRANSPARENT_MODE);
			sprintf((char*)Buf, "%s", "S");
			BSP_LCD_DisplayStringAt(72+120*(pds%4), 71+105*(1-(pds>>2)), Buf, TRANSPARENT_MODE);		
			sprintf((char*)Buf, "%s", "OFF");
			BSP_LCD_DisplayStringAt(88+120*(pds%4), 71+105*(1-(pds>>2)), Buf, TRANSPARENT_MODE);	
			sprintf((char*)Buf, "%s", "000.0");			
			BSP_LCD_DisplayStringAt(38+120*(pds%4), 85+105*(1-(pds>>2)), Buf, TRANSPARENT_MODE);
			sprintf((char*)Buf, "%s", " 0.0dB");	
			BSP_LCD_DisplayStringAt(75+120*(pds%4), 85+105*(1-(pds>>2)), Buf, TRANSPARENT_MODE);		
			BSP_LCD_SetTextColor(0xFFBFBFBF);							//sample name
			sprintf((char*)Buf, "%s", "Empty");			
			BSP_LCD_DisplayStringAt(9+120*(pds%4), 151+105*(1-(pds>>2)), Buf, TRANSPARENT_MODE);			
			COLOR_SET(EMPTY_PAD, pds);		
			}			
		}	
		
	if(ACTIVE_PAD<8)				//draw elements for active pad
		{
		BSP_LCD_SelectLayer(1);
		BSP_LCD_SetTextColor(PADS_LABEL_COLOR[P_COLOR[ACTIVE_PAD]]);		
		BSP_LCD_FillRect(83+120*(ACTIVE_PAD%4), 69+105*(1-(ACTIVE_PAD>>2)), 30, 12);
		BSP_LCD_SetFont(&Font8);	
		BSP_LCD_SetTextColor(TEXT_PAD_COLOR);
		sprintf((char*)Buf, "%s", "ON");
		BSP_LCD_DisplayStringAt(91+120*(ACTIVE_PAD%4), 71+105*(1-(ACTIVE_PAD>>2)), Buf, TRANSPARENT_MODE);
		BSP_LCD_SetFont(&Font15P);					
		BSP_LCD_SelectLayer(0);		
		}
	return;	
	}	


///////////////////////////////////////////////////////////////	
//	redraw dynamic pad's GUI
//	
void REDRAW_PAD(uint8_t pad)
	{
	uint8_t seq;	
	uint32_t temp_pos;	
	uint8_t SQ; 	

	if(pad != previous_pad)	
		{		
		BSP_LCD_SelectLayer(1);
		if(previous_pad<8)	
			{
			BSP_LCD_SetTextColor(0x00000000);	
			BSP_LCD_FillRect(83+120*(previous_pad%4), 69+105*(1-(previous_pad>>2)), 30, 12);
			}
		if(pad<8)
			{	
			BSP_LCD_SetTextColor(PADS_LABEL_COLOR[P_COLOR[pad]]);		
			BSP_LCD_FillRect(83+120*(pad%4), 69+105*(1-(pad>>2)), 30, 12);
			BSP_LCD_SetFont(&Font8);	
			BSP_LCD_SetTextColor(TEXT_PAD_COLOR);
			sprintf((char*)Buf, "%s", "ON");
			BSP_LCD_DisplayStringAt(91+120*(pad%4), 71+105*(1-(pad>>2)), Buf, TRANSPARENT_MODE);
			BSP_LCD_SetFont(&Font15P);		
			}				
		BSP_LCD_SelectLayer(0);		
		}
	if((pad != previous_pad) && (previous_pad<8))
		{			
		if(P_TYPE[previous_pad]==0)			//sample
			{
			if(previous_play_position[previous_pad]>99)
				{
				previous_play_position[previous_pad] = 0;
				}								
			uint32_t temp_pos = (99*(P_START_ADR[previous_pad]))/((P_SAMPLE_OFFSET[previous_pad+1]-P_SAMPLE_OFFSET[previous_pad])+P_START_ADR[previous_pad]);
			if(temp_pos>99)
				{
				return;	
				}				
			if(temp_pos!=previous_play_position[previous_pad])
				{
				ForceDrawVLine(previous_play_position[previous_pad]+10+120*(previous_pad%4), 101+105*(1-(previous_pad>>2)), 31, PAD_BACK_COLOR);
				ForceDrawVLine(previous_play_position[previous_pad]+10+120*(previous_pad%4), 116+105*(1-(previous_pad>>2)) - (P_WAVEFORM[previous_pad][previous_play_position[previous_pad]]&0x0F), 
					((P_WAVEFORM[previous_pad][previous_play_position[previous_pad]]&0x0F)<<1)+1, WS_COLOR_MAP[P_WAVEFORM[previous_pad][previous_play_position[previous_pad]]>>7]);
				ForceDrawVLine(temp_pos+10+120*(previous_pad%4), 101+105*(1-(previous_pad>>2)), 31, 0xFFFFFFFF);
				previous_play_position[previous_pad] = temp_pos;	
				}	
			temp_pos = P_START_ADR[previous_pad]/588;
			if(temp_pos>3000)
				{
				return;	
				}	
			if(temp_pos != previous_time_position[previous_pad])		
				{
				BSP_LCD_SetFont(&Font8);		
				BSP_LCD_SetTextColor(0xFFBFBFBF);
				BSP_LCD_SetBackColor(PAD_BACK_COLOR);		
				sprintf((char*)Buf, "%02lu.%02lu", (temp_pos/75)%4500, temp_pos%75);					
				BSP_LCD_DisplayStringAt(49+120*(previous_pad%4), 139+105*(1-(previous_pad>>2)), Buf, LEFT_MODE);		
				previous_time_position[previous_pad] = temp_pos;
				BSP_LCD_SetBackColor(0xFF000000);				//return black back color, more useful						
				}
			}
		else													////////////////////////////////////////////pad - sequencer
			{
			if(previous_play_position[previous_pad]>63)
				{
				previous_play_position[previous_pad] = 0;	
				}		
			if((0!=(previous_play_position[previous_pad]>>4)) && (P_WAVEFORM[previous_pad][64]>0))				//redraw sequncer page
				{
				for(seq=0;seq<16;seq++)
					{						
					if(seq==0)							//gradients red
						{	
						if(P_WAVEFORM[previous_pad][seq]==1)
							{	
							int_red_gradient(seq, previous_pad);
							}							
						else
							{
							BSP_LCD_SetTextColor(SQ_BACK_COLOR);	
							BSP_LCD_FillRect(16+12*(seq%8)+120*(previous_pad%4), 107+16*(seq>>3)+105*(1-(previous_pad>>2)), 4, 9);	
							BSP_LCD_SetTextColor(RED_PERIMETER_L);
							}
						}		
					else if(seq%4==0)							//gradients blue
						{	
						if(P_WAVEFORM[previous_pad][seq]==1)
							{	
							int_blue_gradient(seq, previous_pad);		
							}							
						else
							{		
							BSP_LCD_SetTextColor(SQ_BACK_COLOR);	
							BSP_LCD_FillRect(16+12*(seq%8)+120*(previous_pad%4), 107+16*(seq>>3)+105*(1-(previous_pad>>2)), 4, 9);	
							BSP_LCD_SetTextColor(BLUE_PERIMETER_L);
							}
						}
					else							//gradients white
						{
						if(P_WAVEFORM[previous_pad][seq]==1)
							{	
							int_grey_gradient(seq, previous_pad);
							}							
						else
							{		
							BSP_LCD_SetTextColor(SQ_BACK_COLOR);	
							BSP_LCD_FillRect(16+12*(seq%8)+120*(previous_pad%4), 107+16*(seq>>3)+105*(1-(previous_pad>>2)), 4, 9);	
							BSP_LCD_SetTextColor(GREY_PERIMETER_L);
							}						
						}						
					int_sqnc_perimeter(seq, previous_pad);					
					}	
				BSP_LCD_SetTextColor(SQ_BACK_COLOR);		
				BSP_LCD_FillRect(16+24*(previous_play_position[previous_pad]>>4)+120*(previous_pad%4), 107+32+105*(1-(previous_pad>>2)), 16, 2);	
				BSP_LCD_SetTextColor(SQ_STEP_CLR_0);	
				BSP_LCD_FillRect(16+120*(previous_pad%4), 107+32+105*(1-(previous_pad>>2)), 2, 2);		
				BSP_LCD_FillRect(30+120*(previous_pad%4), 107+32+105*(1-(previous_pad>>2)), 2, 2);		
				BSP_LCD_SetTextColor(SQ_STEP_CLR_1);		
				BSP_LCD_FillRect(18+120*(previous_pad%4), 107+32+105*(1-(previous_pad>>2)), 2, 2);		
				BSP_LCD_FillRect(28+120*(previous_pad%4), 107+32+105*(1-(previous_pad>>2)), 2, 2);		
				BSP_LCD_SetTextColor(SQ_STEP_CLR_2);	
				BSP_LCD_FillRect(20+120*(previous_pad%4), 107+32+105*(1-(previous_pad>>2)), 2, 2);		
				BSP_LCD_FillRect(26+120*(previous_pad%4), 107+32+105*(1-(previous_pad>>2)), 2, 2);		
				BSP_LCD_SetTextColor(SQ_STEP_CLR_3);	
				BSP_LCD_FillRect(22+120*(previous_pad%4), 107+32+105*(1-(previous_pad>>2)), 4, 2);			
				previous_play_position[previous_pad] = 0;
				}
			seq = previous_play_position[previous_pad];
			previous_play_position[previous_pad] = 0;
			if(seq%16==0)							//gradients red
				{	
				if(P_WAVEFORM[previous_pad][seq]==1)
					{	
					BSP_LCD_SetTextColor(RED_PERIMETER_H);
					}							
				else
					{							
					BSP_LCD_SetTextColor(RED_PERIMETER_L);
					}
				}		
			else if(seq%4==0)							//gradients blue
				{	
				if(P_WAVEFORM[previous_pad][seq]==1)
					{					
					BSP_LCD_SetTextColor(BLUE_PERIMETER_H);			
					}							
				else
					{		
					BSP_LCD_SetTextColor(BLUE_PERIMETER_L);
					}
				}
			else							//gradients white
				{
				if(P_WAVEFORM[previous_pad][seq]==1)
					{	
					BSP_LCD_SetTextColor(GREY_PERIMETER_H);
					}							
				else
					{		
					BSP_LCD_SetTextColor(GREY_PERIMETER_L);
					}						
				}
			int_sqnc_perimeter(seq, previous_pad);
			}
		//previous_pad = pad;	
		}
	else if(pad<8) 
		{
		if(P_TYPE[pad]==0)			//sample
			{
			if(previous_play_position[pad]>99)
				{
				previous_play_position[pad] = 0;	
				}					
			temp_pos = (99*((play_adr - P_SAMPLE_OFFSET[pad]) + P_START_ADR[pad]))/((P_SAMPLE_OFFSET[pad+1]-P_SAMPLE_OFFSET[pad])+P_START_ADR[pad]);
			
			if(temp_pos>99)
				{
				return;	
				}				
			if(temp_pos!=previous_play_position[pad])
				{
				ForceDrawVLine(previous_play_position[pad]+10+120*(pad%4), 101+105*(1-(pad>>2)), 31, PAD_BACK_COLOR);
				ForceDrawVLine(previous_play_position[pad]+10+120*(pad%4), 116+105*(1-(pad>>2)) - (P_WAVEFORM[pad][previous_play_position[pad]]&0x0F), 
					((P_WAVEFORM[pad][previous_play_position[pad]]&0x0F)<<1)+1, WS_COLOR_MAP[P_WAVEFORM[pad][previous_play_position[pad]]>>7]);
				ForceDrawVLine(temp_pos+10+120*(pad%4), 101+105*(1-(pad>>2)), 31, 0xFFFFFFFF);
				previous_play_position[pad] = temp_pos;	
				}				
			temp_pos = ((play_adr - P_SAMPLE_OFFSET[pad]) + P_START_ADR[pad])/588;	
			if(temp_pos>3000)
				{
				return;	
				}	
			if(temp_pos!=previous_time_position[pad])		
				{
				BSP_LCD_SetFont(&Font8);		
				BSP_LCD_SetTextColor(0xFFBFBFBF);
				BSP_LCD_SetBackColor(PAD_BACK_COLOR);		
				sprintf((char*)Buf, "%02lu.%02lu", (temp_pos/75)%4500, temp_pos%75);					
				BSP_LCD_DisplayStringAt(49+120*(pad%4), 139+105*(1-(pad>>2)), Buf, LEFT_MODE);		
				previous_time_position[pad] = temp_pos;
				BSP_LCD_SetBackColor(0xFF000000);				//return black back color, more useful						
				}
			}
		else													////////////////////////////////////////////pad - sequencer
			{
			if(previous_play_position[pad]>63)
				{
				previous_play_position[pad] = 0;	
				}		
			SQ = (BEAT_CNT<<2)+PARTBEAT_CNT; 	
			if(SQ>63)
				{
				return;	
				}				
			if(((SQ>>4)!=(previous_play_position[pad]>>4)) && (P_WAVEFORM[pad][64]>0))				//redraw sequncer page
				{
				for(seq=0;seq<16;seq++)
					{						
					if(seq==0)							//gradients red
						{	
						if(P_WAVEFORM[pad][seq+16*(SQ>>4)]==1)
							{	
							int_red_gradient(seq, pad);
							}							
						else
							{
							BSP_LCD_SetTextColor(SQ_BACK_COLOR);	
							BSP_LCD_FillRect(16+12*(seq%8)+120*(pad%4), 107+16*(seq>>3)+105*(1-(pad>>2)), 4, 9);	
							BSP_LCD_SetTextColor(RED_PERIMETER_L);
							}
						}		
					else if(seq%4==0)							//gradients blue
						{	
						if(P_WAVEFORM[pad][seq+16*(SQ>>4)]==1)
							{	
							int_blue_gradient(seq, pad);		
							}							
						else
							{		
							BSP_LCD_SetTextColor(SQ_BACK_COLOR);	
							BSP_LCD_FillRect(16+12*(seq%8)+120*(pad%4), 107+16*(seq>>3)+105*(1-(pad>>2)), 4, 9);	
							BSP_LCD_SetTextColor(BLUE_PERIMETER_L);
							}
						}
					else							//gradients white
						{
						if(P_WAVEFORM[pad][seq+16*(SQ>>4)]==1)
							{	
							int_grey_gradient(seq, pad);
							}							
						else
							{		
							BSP_LCD_SetTextColor(SQ_BACK_COLOR);	
							BSP_LCD_FillRect(16+12*(seq%8)+120*(pad%4), 107+16*(seq>>3)+105*(1-(pad>>2)), 4, 9);	
							BSP_LCD_SetTextColor(GREY_PERIMETER_L);
							}						
						}						
					int_sqnc_perimeter(seq, pad);					
					}	
				BSP_LCD_SetTextColor(SQ_BACK_COLOR);		
				BSP_LCD_FillRect(16+24*(previous_play_position[pad]>>4)+120*(pad%4), 107+32+105*(1-(pad>>2)), 16, 2);			
				BSP_LCD_SetTextColor(SQ_STEP_CLR_0);	
				BSP_LCD_FillRect(16+24*(SQ>>4)+120*(pad%4), 107+32+105*(1-(pad>>2)), 2, 2);		
				BSP_LCD_FillRect(30+24*(SQ>>4)+120*(pad%4), 107+32+105*(1-(pad>>2)), 2, 2);		
				BSP_LCD_SetTextColor(SQ_STEP_CLR_1);		
				BSP_LCD_FillRect(18+24*(SQ>>4)+120*(pad%4), 107+32+105*(1-(pad>>2)), 2, 2);		
				BSP_LCD_FillRect(28+24*(SQ>>4)+120*(pad%4), 107+32+105*(1-(pad>>2)), 2, 2);		
				BSP_LCD_SetTextColor(SQ_STEP_CLR_2);	
				BSP_LCD_FillRect(20+24*(SQ>>4)+120*(pad%4), 107+32+105*(1-(pad>>2)), 2, 2);		
				BSP_LCD_FillRect(26+24*(SQ>>4)+120*(pad%4), 107+32+105*(1-(pad>>2)), 2, 2);		
				BSP_LCD_SetTextColor(SQ_STEP_CLR_3);	
				BSP_LCD_FillRect(22+24*(SQ>>4)+120*(pad%4), 107+32+105*(1-(pad>>2)), 4, 2);		
				previous_play_position[pad] = SQ;	
				seq = SQ;
				if(seq%16==0)							//gradients red
					{	
					if(P_WAVEFORM[pad][seq]==1)
						{	
						BSP_LCD_SetTextColor(RED_SQ_H);
						}							
					else
						{							
						BSP_LCD_SetTextColor(RED_SQ_L);
						}
					}		
				else if(seq%4==0)							//gradients blue
					{	
					if(P_WAVEFORM[pad][seq]==1)
						{					
						BSP_LCD_SetTextColor(BLUE_SQ_H);			
						}							
					else
						{		
						BSP_LCD_SetTextColor(BLUE_SQ_L);
						}
					}
				else							//gradients white
					{
					if(P_WAVEFORM[pad][seq]==1)
						{	
						BSP_LCD_SetTextColor(GREY_SQ_H);
						}							
					else
						{		
						BSP_LCD_SetTextColor(GREY_SQ_L);
						}						
					}
				int_sqnc_perimeter(seq&0x0F, pad);		
				}
			else if(SQ != previous_play_position[pad])								//if change SQ
				{
				seq = previous_play_position[pad];
				previous_play_position[pad] = SQ;
				if(seq%16==0)							//gradients red
					{	
					if(P_WAVEFORM[pad][seq]==1)
						{	
						BSP_LCD_SetTextColor(RED_PERIMETER_H);
						}							
					else
						{							
						BSP_LCD_SetTextColor(RED_PERIMETER_L);
						}
					}		
				else if(seq%4==0)							//gradients blue
					{	
					if(P_WAVEFORM[pad][seq]==1)
						{					
						BSP_LCD_SetTextColor(BLUE_PERIMETER_H);			
						}							
					else
						{		
						BSP_LCD_SetTextColor(BLUE_PERIMETER_L);
						}
					}
				else							//gradients white
					{
					if(P_WAVEFORM[pad][seq]==1)
						{	
						BSP_LCD_SetTextColor(GREY_PERIMETER_H);
						}							
					else
						{		
						BSP_LCD_SetTextColor(GREY_PERIMETER_L);
						}						
					}
				int_sqnc_perimeter(seq&0x0F, pad);	
				seq = SQ;
				if(seq%16==0)							//gradients red
					{	
					if(P_WAVEFORM[pad][seq]==1)
						{	
						BSP_LCD_SetTextColor(RED_SQ_H);
						}							
					else
						{							
						BSP_LCD_SetTextColor(RED_SQ_L);
						}
					}		
				else if(seq%4==0)							//gradients blue
					{	
					if(P_WAVEFORM[pad][seq]==1)
						{					
						BSP_LCD_SetTextColor(BLUE_SQ_H);			
						}							
					else
						{		
						BSP_LCD_SetTextColor(BLUE_SQ_L);
						}
					}
				else							//gradients white
					{
					if(P_WAVEFORM[pad][seq]==1)
						{	
						BSP_LCD_SetTextColor(GREY_SQ_H);
						}							
					else
						{		
						BSP_LCD_SetTextColor(GREY_SQ_L);
						}						
					}
				seq = seq%16;	
				int_sqnc_perimeter(seq, pad);		
				}
			}
		//previous_pad = pad;	
		}
	previous_pad = pad;	
	return;	
	}
	
	

///////////////////////////////////////////////////////////////	
//	redraw dynamic pad's GUI edit pad
//	
void REDRAW_PAD_EDIT(uint8_t pad)
	{
	if((pad==(pad_x-1)) || (pad==0xFF))	
		{
		uint8_t seq;	
		uint32_t temp_pos;	
		uint8_t SQ; 	
		if(pad != previous_pad)	
			{		
			BSP_LCD_SelectLayer(1);
			if(previous_pad<8)	
				{
				BSP_LCD_SetTextColor(0x00000000);	
				BSP_LCD_FillRect(443, 174, 30, 12);
				}
			if(pad<8)
				{	
				BSP_LCD_SetTextColor(PADS_LABEL_COLOR[P_COLOR[pad]]);
				BSP_LCD_FillRect(443, 174, 30, 12);
				BSP_LCD_SetFont(&Font8);	
				BSP_LCD_SetTextColor(TEXT_PAD_COLOR);
				sprintf((char*)Buf, "%s", "ON");
				BSP_LCD_DisplayStringAt(451, 176, Buf, TRANSPARENT_MODE);
				BSP_LCD_SetFont(&Font15P);		
				}				
			BSP_LCD_SelectLayer(0);		
			}
		if((pad != previous_pad) && (previous_pad<8))
			{			
			if(P_TYPE[previous_pad]==0)			//sample
				{
				if(previous_play_position[previous_pad]>99)
					{
					previous_play_position[previous_pad] = 0;
					}								
				uint32_t temp_pos = (99*(P_START_ADR[previous_pad]))/((P_SAMPLE_OFFSET[previous_pad+1]-P_SAMPLE_OFFSET[previous_pad])+P_START_ADR[previous_pad]);
				if(temp_pos>99)
					{
					return;	
					}				
				if(temp_pos!=previous_play_position[previous_pad])
					{
					ForceDrawVLine(previous_play_position[previous_pad]+370, 206, 31, PAD_BACK_COLOR);
					ForceDrawVLine(previous_play_position[previous_pad]+370, 221 - (P_WAVEFORM[previous_pad][previous_play_position[previous_pad]]&0x0F), 
						((P_WAVEFORM[previous_pad][previous_play_position[previous_pad]]&0x0F)<<1)+1, WS_COLOR_MAP[P_WAVEFORM[previous_pad][previous_play_position[previous_pad]]>>7]);
					ForceDrawVLine(temp_pos+370, 206, 31, 0xFFFFFFFF);
					previous_play_position[previous_pad] = temp_pos;	
					}	
				temp_pos = P_START_ADR[previous_pad]/588;
				if(temp_pos>3000)
					{
					return;	
					}	
				if(temp_pos != previous_time_position[previous_pad])		
					{
					BSP_LCD_SetFont(&Font8);		
					BSP_LCD_SetTextColor(0xFFBFBFBF);
					BSP_LCD_SetBackColor(PAD_BACK_COLOR);		
					sprintf((char*)Buf, "%02lu.%02lu", (temp_pos/75)%4500, temp_pos%75);					
					BSP_LCD_DisplayStringAt(409, 244, Buf, LEFT_MODE);		
					previous_time_position[previous_pad] = temp_pos;
					BSP_LCD_SetBackColor(0xFF000000);				//return black back color, more useful						
					}
				}
			else													////////////////////////////////////////////pad - sequencer
				{
				if(previous_play_position[previous_pad]>63)
					{
					previous_play_position[previous_pad] = 0;	
					}		
				if((0!=(previous_play_position[previous_pad]>>4)) && (P_WAVEFORM[previous_pad][64]>0))				//redraw sequncer page
					{
					for(seq=0;seq<16;seq++)
						{						
						if(seq==0)							//gradients red
							{	
							if(P_WAVEFORM[previous_pad][seq]==1)
								{	
								int_red_gradient(seq, 3);
								}							
							else
								{
								BSP_LCD_SetTextColor(SQ_BACK_COLOR);	
								BSP_LCD_FillRect(376+12*(seq%8), 212+16*(seq>>3), 4, 9);	
								BSP_LCD_SetTextColor(RED_PERIMETER_L);
								}
							}		
						else if(seq%4==0)							//gradients blue
							{	
							if(P_WAVEFORM[previous_pad][seq]==1)
								{	
								int_blue_gradient(seq, 3);		
								}							
							else
								{		
								BSP_LCD_SetTextColor(SQ_BACK_COLOR);	
								BSP_LCD_FillRect(376+12*(seq%8), 212+16*(seq>>3), 4, 9);		
								BSP_LCD_SetTextColor(BLUE_PERIMETER_L);
								}
							}
						else							//gradients white
							{
							if(P_WAVEFORM[previous_pad][seq]==1)
								{	
								int_grey_gradient(seq, 3);
								}							
							else
								{		
								BSP_LCD_SetTextColor(SQ_BACK_COLOR);	
								BSP_LCD_FillRect(376+12*(seq%8), 212+16*(seq>>3), 4, 9);		
								BSP_LCD_SetTextColor(GREY_PERIMETER_L);
								}						
							}						
						int_sqnc_perimeter(seq, 3);					
						}	
					BSP_LCD_SetTextColor(SQ_BACK_COLOR);		
					BSP_LCD_FillRect(376+24*(previous_play_position[previous_pad]>>4), 244, 16, 2);	
					BSP_LCD_SetTextColor(SQ_STEP_CLR_0);	
					BSP_LCD_FillRect(376, 244, 2, 2);		
					BSP_LCD_FillRect(390, 244, 2, 2);		
					BSP_LCD_SetTextColor(SQ_STEP_CLR_1);		
					BSP_LCD_FillRect(378, 244, 2, 2);		
					BSP_LCD_FillRect(388, 244, 2, 2);		
					BSP_LCD_SetTextColor(SQ_STEP_CLR_2);	
					BSP_LCD_FillRect(380, 244, 2, 2);		
					BSP_LCD_FillRect(386, 244, 2, 2);		
					BSP_LCD_SetTextColor(SQ_STEP_CLR_3);	
					BSP_LCD_FillRect(382, 244, 4, 2);			
					previous_play_position[previous_pad] = 0;
					}
				seq = previous_play_position[previous_pad];
				previous_play_position[previous_pad] = 0;
				if(seq%16==0)							//gradients red
					{	
					if(P_WAVEFORM[previous_pad][seq]==1)
						{	
						BSP_LCD_SetTextColor(RED_PERIMETER_H);
						}							
					else
						{							
						BSP_LCD_SetTextColor(RED_PERIMETER_L);
						}
					}		
				else if(seq%4==0)							//gradients blue
					{	
					if(P_WAVEFORM[previous_pad][seq]==1)
						{					
						BSP_LCD_SetTextColor(BLUE_PERIMETER_H);			
						}							
					else
						{		
						BSP_LCD_SetTextColor(BLUE_PERIMETER_L);
						}
					}
				else							//gradients white
					{
					if(P_WAVEFORM[previous_pad][seq]==1)
						{	
						BSP_LCD_SetTextColor(GREY_PERIMETER_H);
						}							
					else
						{		
						BSP_LCD_SetTextColor(GREY_PERIMETER_L);
						}						
					}
				int_sqnc_perimeter(seq, 3);
				}
			}
		else if(pad<8) 
			{
			if(P_TYPE[pad]==0)			//sample
				{
				if(previous_play_position[pad]>99)
					{
					previous_play_position[pad] = 0;	
					}					
				temp_pos = (99*((play_adr - P_SAMPLE_OFFSET[pad]) + P_START_ADR[pad]))/((P_SAMPLE_OFFSET[pad+1]-P_SAMPLE_OFFSET[pad])+P_START_ADR[pad]);
				
				if(temp_pos>99)
					{
					return;	
					}				
				if(temp_pos!=previous_play_position[pad])
					{
					ForceDrawVLine(previous_play_position[pad]+370, 206, 31, PAD_BACK_COLOR);
					ForceDrawVLine(previous_play_position[pad]+370, 221 - (P_WAVEFORM[pad][previous_play_position[pad]]&0x0F), 
						((P_WAVEFORM[pad][previous_play_position[pad]]&0x0F)<<1)+1, WS_COLOR_MAP[P_WAVEFORM[pad][previous_play_position[pad]]>>7]);
					ForceDrawVLine(temp_pos+370, 206, 31, 0xFFFFFFFF);
					previous_play_position[pad] = temp_pos;	
					}				
				temp_pos = ((play_adr - P_SAMPLE_OFFSET[pad]) + P_START_ADR[pad])/588;	
				if(temp_pos>3000)
					{
					return;	
					}	
				if(temp_pos!=previous_time_position[pad])		
					{
					BSP_LCD_SetFont(&Font8);		
					BSP_LCD_SetTextColor(0xFFBFBFBF);
					BSP_LCD_SetBackColor(PAD_BACK_COLOR);		
					sprintf((char*)Buf, "%02lu.%02lu", (temp_pos/75)%4500, temp_pos%75);					
					BSP_LCD_DisplayStringAt(409, 244, Buf, LEFT_MODE);		
					previous_time_position[pad] = temp_pos;
					BSP_LCD_SetBackColor(0xFF000000);				//return black back color, more useful						
					}
				}
			else													////////////////////////////////////////////pad - sequencer
				{
				if(previous_play_position[pad]>63)
					{
					previous_play_position[pad] = 0;	
					}		
				SQ = (BEAT_CNT<<2)+PARTBEAT_CNT; 	
				if(SQ>63)
					{
					return;	
					}		
				if(((SQ>>4)!=(previous_play_position[pad]>>4)) && (P_WAVEFORM[pad][64]>0) && (edit_epd_parameter==0 || EPD_Position!=10))				//redraw sequncer page for all, but not redraw when edit sequence
					{
					for(seq=0;seq<16;seq++)
						{						
						if(seq==0)							//gradients red
							{	
							if(P_WAVEFORM[pad][seq+16*(SQ>>4)]==1)
								{	
								int_red_gradient(seq, 3);
								}							
							else
								{
								BSP_LCD_SetTextColor(SQ_BACK_COLOR);	
								BSP_LCD_FillRect(376+12*(seq%8), 212+16*(seq>>3), 4, 9);	
								BSP_LCD_SetTextColor(RED_PERIMETER_L);
								}
							}		
						else if(seq%4==0)							//gradients blue
							{	
							if(P_WAVEFORM[pad][seq+16*(SQ>>4)]==1)
								{	
								int_blue_gradient(seq, 3);		
								}							
							else
								{		
								BSP_LCD_SetTextColor(SQ_BACK_COLOR);	
								BSP_LCD_FillRect(376+12*(seq%8), 212+16*(seq>>3), 4, 9);	
								BSP_LCD_SetTextColor(BLUE_PERIMETER_L);
								}
							}
						else							//gradients white
							{
							if(P_WAVEFORM[pad][seq+16*(SQ>>4)]==1)
								{	
								int_grey_gradient(seq, 3);
								}							
							else
								{		
								BSP_LCD_SetTextColor(SQ_BACK_COLOR);	
								BSP_LCD_FillRect(376+12*(seq%8), 212+16*(seq>>3), 4, 9);
								BSP_LCD_SetTextColor(GREY_PERIMETER_L);
								}						
							}						
						int_sqnc_perimeter(seq, 3);					
						}	
					BSP_LCD_SetTextColor(SQ_BACK_COLOR);		
					BSP_LCD_FillRect(376+24*(previous_play_position[pad]>>4), 244, 16, 2);			
					BSP_LCD_SetTextColor(SQ_STEP_CLR_0);	
					BSP_LCD_FillRect(376+24*(SQ>>4), 244, 2, 2);		
					BSP_LCD_FillRect(390+24*(SQ>>4), 244, 2, 2);		
					BSP_LCD_SetTextColor(SQ_STEP_CLR_1);		
					BSP_LCD_FillRect(378+24*(SQ>>4), 244, 2, 2);		
					BSP_LCD_FillRect(388+24*(SQ>>4), 244, 2, 2);		
					BSP_LCD_SetTextColor(SQ_STEP_CLR_2);	
					BSP_LCD_FillRect(380+24*(SQ>>4), 244, 2, 2);		
					BSP_LCD_FillRect(386+24*(SQ>>4), 244, 2, 2);		
					BSP_LCD_SetTextColor(SQ_STEP_CLR_3);	
					BSP_LCD_FillRect(382+24*(SQ>>4), 244, 4, 2);		
					previous_play_position[pad] = SQ;	
					seq = SQ;
					if(seq%16==0)							//gradients red
						{	
						if(P_WAVEFORM[pad][seq]==1)
							{	
							BSP_LCD_SetTextColor(RED_SQ_H);
							}							
						else
							{							
							BSP_LCD_SetTextColor(RED_SQ_L);
							}
						}		
					else if(seq%4==0)							//gradients blue
						{	
						if(P_WAVEFORM[pad][seq]==1)
							{					
							BSP_LCD_SetTextColor(BLUE_SQ_H);			
							}							
						else
							{		
							BSP_LCD_SetTextColor(BLUE_SQ_L);
							}
						}
					else							//gradients white
						{
						if(P_WAVEFORM[pad][seq]==1)
							{	
							BSP_LCD_SetTextColor(GREY_SQ_H);
							}							
						else
							{		
							BSP_LCD_SetTextColor(GREY_SQ_L);
							}						
						}
					int_sqnc_perimeter(seq&0x0F, 3);		
					}
				else if(SQ != previous_play_position[pad])								//if change SQ
					{
					seq = previous_play_position[pad];
					previous_play_position[pad] = SQ;
					if((SQ>>4)==(seq_epos>>4) || edit_epd_parameter==0 || EPD_Position!=10 || (seq%16==15 && SQ%16==0))				//complex condition for draw a running sequence when editing
						{	
						if(seq%16==0)							//gradients red
							{	
							if(P_WAVEFORM[pad][seq]==1)
								{	
								BSP_LCD_SetTextColor(RED_PERIMETER_H);
								}							
							else
								{							
								BSP_LCD_SetTextColor(RED_PERIMETER_L);
								}
							}		
						else if(seq%4==0)							//gradients blue
							{	
							if(P_WAVEFORM[pad][seq]==1)
								{					
								BSP_LCD_SetTextColor(BLUE_PERIMETER_H);			
								}							
							else
								{		
								BSP_LCD_SetTextColor(BLUE_PERIMETER_L);
								}
							}
						else							//gradients white
							{
							if((seq%16==15 && SQ%16==0))
								{
								if(P_WAVEFORM[pad][(seq_epos&0xF0)+15]==1)
									{	
									BSP_LCD_SetTextColor(GREY_PERIMETER_H);
									}							
								else
									{		
									BSP_LCD_SetTextColor(GREY_PERIMETER_L);
									}				
								}
							else
								{	
								if(P_WAVEFORM[pad][seq]==1)
									{	
									BSP_LCD_SetTextColor(GREY_PERIMETER_H);
									}							
								else
									{		
									BSP_LCD_SetTextColor(GREY_PERIMETER_L);
									}		
								}
							}
						int_sqnc_perimeter(seq&0x0F, 3);
						}
					if((SQ>>4)==(seq_epos>>4) || edit_epd_parameter==0 || EPD_Position!=10)
						{
						seq = SQ;
						if(seq%16==0)							//gradients red
							{	
							if(P_WAVEFORM[pad][seq]==1)
								{	
								BSP_LCD_SetTextColor(RED_SQ_H);
								}							
							else
								{							
								BSP_LCD_SetTextColor(RED_SQ_L);
								}
							}		
						else if(seq%4==0)							//gradients blue
							{	
							if(P_WAVEFORM[pad][seq]==1)
								{					
								BSP_LCD_SetTextColor(BLUE_SQ_H);			
								}							
							else
								{		
								BSP_LCD_SetTextColor(BLUE_SQ_L);
								}
							}
						else							//gradients white
							{
							if(P_WAVEFORM[pad][seq]==1)
								{	
								BSP_LCD_SetTextColor(GREY_SQ_H);
								}							
							else
								{		
								BSP_LCD_SetTextColor(GREY_SQ_L);
								}						
							}
						seq = seq%16;	
						int_sqnc_perimeter(seq, 3);	
						}
					}
				}
			}
		previous_pad = pad;	
		}			
	return;	
	}


	
	
///////////////////////////////////////////////////////////////	
//	internal for pads
//	PAD 0...7
void int_pad_handler(uint8_t PAD)
	{
	uint32_t current_time;
	current_time = HAL_GetTick();
	
	if((current_time - pad_timestamp)<18)
		{
		pad_timestamp = current_time;
		return;	
		}
	else if(((current_time - pad_timestamp)<47) && (ACTIVE_PAD!=PAD))
		{
		pad_timestamp = current_time;	
		return;	
		}
	pad_timestamp = current_time;	
		
		
	if(SERVICE_MODE_ENABLE)
		{
		return;	
		}		
	else if((dSHOW==EDIT_PAD_DISPLAY) && (PAD!=(pad_x-1)))		
		{
		return;		
		}	
	else if(dSHOW==FLLIST_DISPLAY)	
		{
		need_fastload_preset = PAD;			
		return;	
		}
	else if(P_COLOR[PAD]==0xFF)		//this pad is disable
		{
		return;	
		}	
		
	end_one_shot_seq = 0;		
		
	if(P_TYPE[PAD]==1)		//if pad - sequencer
		{	
		if(music_tim>(3000000/(UDP_BPM+5)))	//1/2...beat position
			{	
			BEAT_CNT = 0xFF;
			}		
		else
			{
			BEAT_CNT = 0;		
			}	
		PARTBEAT_CNT = 0;	
		}						
		
	if(ACTIVE_PAD==PAD && P_TRIG[PAD]==1) //if pad is loop - stop
		{
		sai_pitch = 0;					//stop audio	
		ACTIVE_PAD = 0xFF;
		ATT_LVL = 0xFF;						///mute - minimal gain
		COLOR_SET(PADS_L_COLOR[P_COLOR[PAD]], PAD);		
		need_load_rgb = 1;
		}			
	else											//replace pad
		{
		if((ACTIVE_PAD<8) && (ACTIVE_PAD!=PAD))	
			{
			COLOR_SET(PADS_L_COLOR[P_COLOR[ACTIVE_PAD]], ACTIVE_PAD);	
			force_start_sample = 0;	
			}
		ACTIVE_PAD = PAD;	
		all_long = P_SAMPLE_OFFSET[PAD+1];	
		SMPL_STRT = P_SAMPLE_OFFSET[PAD];	
		ATT_LVL = P_GAIN[PAD];		
		if(P_TYPE[PAD]==1)		//if pad - sequencer - go to end sample for stop
			{			
			play_adr = P_SAMPLE_OFFSET[PAD+1];
			}
		else					//pad - sample
			{
			if(P_QUANTIZE[PAD]==0)			//quantize off
				{
				play_adr = SMPL_STRT;	
				}				
			else						//quantize on
				{
				if(P_SYNC[PAD]==0)							//sync speed disable
					{
					SHFT_STRT = 4410*music_tim;
					SHFT_STRT/=100;	
					}			
				else			//sync speed enable
					{					
					if(UDP_BPM==0xFFFFFFFF)
						{
						SHFT_STRT = 0;	
						}
					else
						{
						tmp_pitch = UDP_BPM+5;
						tmp_pitch = tmp_pitch*1000;	
						tmp_pitch = tmp_pitch/P_BPM[PAD];	
						SHFT_STRT = 441*music_tim;
						SHFT_STRT*=tmp_pitch;
						SHFT_STRT/=100000;		
						}	
					}	
				if(P_SAMPLE_OFFSET[PAD+1]>(SMPL_STRT+SHFT_STRT))
					{
					if(music_tim>(4500000/(UDP_BPM+5)))			//3/4 beat position
						{
						force_start_sample = 1;		
						}	
					play_adr = SMPL_STRT+SHFT_STRT;		
					}
				else
					{
					if(P_TRIG[PAD]==0 && P_TYPE[PAD]==0)		//if sample & one shot
						{
						if(music_tim>(4500000/(UDP_BPM+5))) 			//3/4 beat position
							{
							force_start_sample = 1;		
							}		
						}
					play_adr = P_SAMPLE_OFFSET[PAD+1];	
					}							
				}
			}
			
		if(P_SYNC[PAD]==0)							//sync speed disable
			{
			sai_pitch = 10000;	
			}			
		else													//sync speed
			{
			tmp_pitch = UDP_BPM+5;
			tmp_pitch = tmp_pitch*1000;	
			tmp_pitch = tmp_pitch/P_BPM[PAD];	
			sai_pitch = tmp_pitch;
			}			

		if(P_TYPE[PAD]==0)	//if pad - sample
			{			
			pad_sample_on_tim = 75;
			}				
		COLOR_SET(0x00000000, PAD);		
		need_load_rgb = 1;	
		}			
	return;	
	}
	
///////////////////////////////////////////////////////////////	
//	univrsal function for creating current screenshots		
//	
uint16_t CREATE_SCREEN(void)
	{
	////////////////////////////////////////////////////	
	//	UNIVERSAL CODE FOR SCREENSHOT
	//	set in file sdmmc.c
	//	hsd1.Init.ClockDiv = 12;					//1
	//	
	char path_rec[]="0:/SAMPLER/SCREEN_001.bmp";
		
	uint8_t bmp_header[54] = {
	0x42, 0x4D, 0x38, 0xF8, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00, 
	0x00, 0x00, 0xE0, 0x01, 0x00, 0x00, 0x10, 0x01, 0x00, 0x00, 0x01, 0x00, 0x20, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x0B, 0x00, 0x00, 0x12, 0x0B, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};	

	uint32_t RND = HAL_GetTick();
	path_rec[18] = (RND%1000)/100 + 48;
	path_rec[19] = (RND%100)/10 + 48;
	path_rec[20] = RND%10 + 48; 				
		
	res = f_open(&file, path_rec, FA_CREATE_NEW | FA_WRITE);
			
	if(res==FR_OK)
		{
		f_write(&file, bmp_header, 54, &nbytes);	//write header
		HAL_Delay(10);	
		uint16_t F;
		uint32_t IMG_BFR[128];	
		uint8_t q;	
		uint8_t r0, g0, b0, r1, g1, b1, trnsp;	
		uint8_t tmp_clr;	
			
		for(F=0;F<1020;F++)
			{
			for(q=0;q<128;q++)
				{
				IMG_BFR[q] = *((uint32_t*)LCD_FRAME_BUFFER_2+F*128+q);					//high layer with transparents
				if((IMG_BFR[q]>>24)==0)
					{
					IMG_BFR[q] = *((uint32_t*)LCD_FRAME_BUFFER+F*128+q);				//low (background) layer					
					}						
				else if((IMG_BFR[q]>>24)<0xFF)			//calculate pixel color with transparency
					{
					trnsp	= IMG_BFR[q]>>24;
					r1 = (IMG_BFR[q]>>16)%256;	
					g1 = (IMG_BFR[q]>>8)%256;	
					b1 = IMG_BFR[q]%256;	
					IMG_BFR[q] = *((uint32_t*)LCD_FRAME_BUFFER+F*128+q);
					r0 = (IMG_BFR[q]>>16)%256;	
					g0 = (IMG_BFR[q]>>8)%256;	
					b0 = IMG_BFR[q]%256;	
					if(r1>r0)
						{
						tmp_clr	= (trnsp*(r1-r0))>>8;
						r0+= tmp_clr;
						}
					else
						{
						tmp_clr = (trnsp*(r0-r1))>>8;		
						r0-= tmp_clr;	
						}
					if(g1>g0)
						{
						tmp_clr	= (trnsp*(g1-g0))>>8;
						g0+= tmp_clr;
						}
					else
						{
						tmp_clr = (trnsp*(g0-g1))>>8;		
						g0-= tmp_clr;	
						}
					if(b1>b0)
						{
						tmp_clr	= (trnsp*(b1-b0))>>8;
						b0+= tmp_clr;
						}
					else
						{
						tmp_clr = (trnsp*(b0-b1))>>8;		
						b0-= tmp_clr;	
						}		
					IMG_BFR[q] = 65536*r0 + 256*g0 + b0;
					IMG_BFR[q]|=0xFF000000;	
					}		
				}
			res = f_write(&file, IMG_BFR, 512, &nbytes);	
			HAL_Delay(10);		
			}
			
		if(res==FR_OK)				//write end header	
			{
			f_write(&file, &bmp_header[48], 2, &nbytes);
			}			
		if(res==FR_OK)
			{
			res = f_close(&file);	
			if(res==FR_OK)
				{
				return RND%1000;		
				}
			else
				{
				return 0xFFFF;		
				}
			}
		else
			{
			f_close(&file);
			return 0xFFFF;
			}	
		}	
	else
		{	
		return 0xFFFF;	
		}		
	};
	
	
	
///////////////////////////////////////////////////////////////	
//	
//		create gui table color
//	
void CREATE_GUI_STYLE_COLOR(uint32_t color)
	{
	uint32_t _tmp_col;
	uint8_t _r, _g, _b;
	_tmp_col = 107*(color%256);	
	_b = _tmp_col>>8;	
	_tmp_col = 107*((color>>8)%256);	
	_g = _tmp_col>>8;					
	_tmp_col = 107*((color>>16)%256);	
	_r = _tmp_col>>8;	
	GUI_STYLE_COLOR = 0xFF000000+_b+256*_g+65536*_r;	
	return;	
	};
	
///////////////////////////////////////////////////////////////	
//	
//		create color for picture
//	
uint32_t CREATE_PIC_COLOR(uint32_t col)
	{
	uint32_t _tmp_col;
	uint8_t _r, _g, _b;
	_tmp_col = (col+85)*(LCD_COLOR_PAPER%256);	
	_b = _tmp_col/100;	
	_tmp_col = (col+85)*((LCD_COLOR_PAPER>>8)%256);	
	_g = _tmp_col/100;					
	_tmp_col = (col+85)*((LCD_COLOR_PAPER>>16)%256);	
	_r = _tmp_col/100;
	_tmp_col = 0xFF000000+_b+256*_g+65536*_r;		
	return _tmp_col;	
	}
	
	
///////////////////////////////////////////////////////////////	
//	UART interrupt		
//	
#if defined(USART_DEBUG)
void USART1_IRQHandler(void)
	{
	uint8_t USART_RX_B;	
	if(USART1->ISR & USART_ISR_RXNE)		//have a new data
		{
		USART_RX_B = (USART1->RDR);	
		if(((HAL_GetTick() - usart_timeout)>200))
			{	
			if(USART_RX_B==47)
				{
				usart_data_cnt = 0;
				U_RX_DATA[1] = 0;
				U_RX_DATA[2] = 0;
				U_RX_DATA[3] = 0;
				U_RX_DATA[4] = 0;
				U_RX_DATA[5] = 0;
				U_RX_DATA[6] = 0;
				U_RX_DATA[7] = 0;
				U_RX_DATA[8] = 0;
				U_RX_DATA[9] = 0;
				U_RX_DATA[10] = 0;
				U_RX_DATA[11] = 0;
				U_RX_DATA[12] = 0;
				U_RX_DATA[13] = 0;
				U_RX_DATA[14] = 0;
				U_RX_DATA[15] = 0;						
				}
			else
				{
				usart_data_cnt = 0xFF;	
				}
			}
		else
			{
			if(usart_data_cnt<16)	
				{
				U_RX_DATA[usart_data_cnt] = USART_RX_B;			
				usart_data_cnt++;
					
				if(usart_data_cnt>2 && usart_new_data==0)
					{			
					usart_new_data = 1;	
					}
				}
			}
		usart_timeout = HAL_GetTick(); 			
		}
  HAL_UART_IRQHandler(&huart1);
	}	
#endif	


//////////////////////////////////////////////////FatFs Functions//////////////////////
WCHAR ff_convert (WCHAR wch, UINT dir) 
{ 
          if (wch < 0x80) { 
                    /* ASCII Char */ 
                    return wch; 
          }  

          /* I don't support unicode it is too big! */ 
          return 0; 
}  

WCHAR ff_wtoupper (WCHAR wch) 
{ 
          if (wch < 0x80) {      
                    /* ASCII Char */ 
                    if (wch >= 'a' && wch <= 'z') { 
                              wch &= ~0x20; 
                     } 
                      return wch; 
          }  

          /* I don't support unicode it is too big! */ 
          return 0; 
} 
//////////////////////////////////////////////////////////////////////////////////////

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
