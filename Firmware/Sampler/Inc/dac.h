/////////////////////////////////////////////////////////////////////////////////////////////////
// 	DAC init
//	product: DJS-500 sampler
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdint.h"

void DAC_Init_and_Start(uint8_t volume);

//init DAC on board discovery 
//and start SAI transaction
void DAC_Init_and_Start(uint8_t volume)
	{
	uint8_t _tmp[2];
	uint32_t deviceid = 0x00;
	AUDIO_DrvTypeDef          *audio_drv;
	HAL_SAI_Transmit(&hsai_BlockA2, _tmp, 2, 200);	
  deviceid = wm8994_drv.ReadID(AUDIO_I2C_ADDRESS);
  if((deviceid) == WM8994_ID)
		{  
		wm8994_Reset(AUDIO_I2C_ADDRESS);
    audio_drv = &wm8994_drv; 
    audio_drv->Init(AUDIO_I2C_ADDRESS, OUTPUT_DEVICE_BOTH, volume, AUDIO_FREQUENCY_44K);
		wm8994_SetMute(AUDIO_I2C_ADDRESS, AUDIO_MUTE_OFF);	
		}
	HAL_SAI_Transmit_IT(&hsai_BlockA2, _tmp, 2);
	return;	
	}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



