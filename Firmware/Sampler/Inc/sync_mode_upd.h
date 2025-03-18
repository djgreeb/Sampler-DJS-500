/////////////////////////////////////////////////////////////////////////////////////////////////
// 	sync mode upd function
//	product: DJS-500 sampler
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdint.h"

void int_sync_mode_upd(void);

void int_sync_mode_upd(void)
	{
	if(UTILITY_SETTINGS[3]==0)		//internal bpm clock
		{
		link_status = 1;
		IBEAT_TIM = 0;		
		IUDP_MPHASE_CNT = 1;
		THR_TIME = 0;		
		UDP_MD = 0;	
		UDP_NEED_UPDATE_MD = 1;		
		UDP_BPM	= 10*UTILITY_SETTINGS[4];
		UDP_NEED_UPDATE_BPM = 1;				
		}	
	else				//external bpm
		{
		UDP_BPM = 0xFFFFFFFF;	
		link_status = 0xFF;	
		UDP_NEED_UPDATE_BPM = 1;	
		}	
	return;	
	}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



