/////////////////////////////////////////////////////////////////////////////////////////////////
// 	fat process for white uSD card
//	product: DJS-500 sampler
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdint.h"

uint8_t write_setings_prc(void);	
uint8_t write_preset_prc(void);
uint8_t write_pad_prc(void);
uint8_t write_new_dupl_prc(uint8_t mode);								// mode: 0 - new 1 - duplicate
uint8_t delete_prc(uint8_t prst);	
uint8_t newpstfile(void);
uint8_t move_preser_prc(uint8_t mv, uint8_t np);

/////////////////////////////////////////////////////
//
//	write to file Presets.pst settings data
//
uint8_t write_setings_prc(void)
	{
	uint8_t i;	
	for(i=0;i<48;i++)
		{
		wdata[i] = 0;	
		}			
	wdata[0] = TOTAL_PRESETS;
	wdata[1] = UTILITY_SETTINGS[2];
	wdata[2] = UTILITY_SETTINGS[3];
	wdata[3] = UTILITY_SETTINGS[5];
	wdata[4] = UTILITY_SETTINGS[1];
	wdata[12] = UTILITY_SETTINGS[0]; 	
	wdata[13] = UTILITY_SETTINGS[6];
	wdata[14] = (UTILITY_SETTINGS[4]>>8)&0x000000FF;
	wdata[15] = UTILITY_SETTINGS[4]&0x000000FF;
	wdata[16] = FAST_LOADING[0];
	wdata[17] = FAST_LOADING[1];
	wdata[18] = FAST_LOADING[2];
	wdata[19] = FAST_LOADING[3];
	wdata[20] = FAST_LOADING[4];
	wdata[21] = FAST_LOADING[5];
	wdata[22] = FAST_LOADING[6];
	wdata[23] = FAST_LOADING[7];
	wdata[32] = UTILITY_SETTINGS[7]>>24;
	wdata[33] = (UTILITY_SETTINGS[7]>>16)&0x000000FF;
	wdata[34] = (UTILITY_SETTINGS[7]>>8)&0x000000FF;
	wdata[35] = UTILITY_SETTINGS[7]&0x000000FF;
	wdata[36] = UTILITY_SETTINGS[8]>>24;
	wdata[37] = (UTILITY_SETTINGS[8]>>16)&0x000000FF;
	wdata[38] = (UTILITY_SETTINGS[8]>>8)&0x000000FF;
	wdata[39] = UTILITY_SETTINGS[8]&0x000000FF;
	wdata[40] = UTILITY_SETTINGS[9]>>24;
	wdata[41] = (UTILITY_SETTINGS[9]>>16)&0x000000FF;
	wdata[42] = (UTILITY_SETTINGS[9]>>8)&0x000000FF;
	wdata[43] = UTILITY_SETTINGS[9]&0x000000FF;

	f_close(&file);
	res = f_open(&file, presets_path, FA_WRITE);
	if(res==FR_OK)
		{
		res = f_write(&file, wdata, 48, &nbytes);
		f_close(&file);	
		}
	return res;		
	}

	
/////////////////////////////////////////////////////
//
//	write to file Presets.pst preset config
//	
uint8_t write_preset_prc(void)
	{	
	f_close(&file);
	res = f_open(&file, presets_path, FA_WRITE);
	if(res==FR_OK)
		{			
		f_lseek(&file, (48+1584*CURRENT_PRESET));		
		wdata[0] = 117;	
		wdata[1] = presets_icon[CURRENT_PRESET];	
		wdata[2] = presets_rating[CURRENT_PRESET];	
		wdata[3] = presets_color[CURRENT_PRESET];
		res = f_write(&file, wdata, 4, &nbytes);
		if(res==FR_OK)
			{
			f_lseek(&file, (64+1584*CURRENT_PRESET));						
			res = f_write(&file, presets_list[CURRENT_PRESET], 32, &nbytes);	
			}	
		else
			{
			f_close(&file);
			return res;		
			}
		f_close(&file);	
		}
	return res;		
	}
	
	
/////////////////////////////////////////////////////
//
//	write to file Presets.pst PAD_X config
//	
uint8_t write_pad_prc(void)
	{
	f_close(&file);
	res = f_open(&file, presets_path, FA_WRITE);
	if(res==FR_OK)
		{	
		if(P_COLOR[pad_x-1]<8)  //pad is enable
			{		
			presets_pads_colors[CURRENT_PRESET][pad_x-1] = P_COLOR[pad_x-1]&0x07; 	//rewrite color in ram
			}
		f_lseek(&file, (48+(1584*CURRENT_PRESET)+48+(192*(pad_x-1))));
		uint32_t AL;	
		if(P_COLOR[pad_x-1]<8)  //pad is enable
			{		
			wdata[0] = 135;
			wdata[1] = P_COLOR[pad_x-1]&0x07;
			wdata[2] = P_TYPE[pad_x-1]&0x01;	
			wdata[3] = P_QUANTIZE[pad_x-1]&0x01;	
			wdata[4] = P_SYNC[pad_x-1]&0x01;	
			wdata[5] = P_TRIG[pad_x-1]&0x01;
			wdata[6] = (P_BPM[pad_x-1]>>8)&0x00FF;
			wdata[7] = P_BPM[pad_x-1]&0x00FF;	
			wdata[8] = P_GAIN[pad_x-1];
			wdata[9] = (P_START_ADR[pad_x-1]>>16)&0x000000FF;
			wdata[10] = (P_START_ADR[pad_x-1]>>8)&0x000000FF;
			wdata[11] = P_START_ADR[pad_x-1]&0x000000FF;		
			AL = new_all_data - P_START_ADR[pad_x-1];
			wdata[12] = AL>>24;
			wdata[13] = (AL>>16)&0x000000FF;
			wdata[14] = (AL>>8)&0x000000FF;
			wdata[15] = AL&0x000000FF;	
			}
		else
			{
			wdata[0] = 0;
			wdata[1] = 0xFF;
			wdata[2] = 0;	
			wdata[3] = 0;	
			wdata[4] = 0;	
			wdata[5] = 0;
			wdata[6] = 0;
			wdata[7] = 0;	
			wdata[8] = 0;
			wdata[9] = 0;
			wdata[10] = 0;
			wdata[11] = 0;		
			wdata[12] = 0;
			wdata[13] = 0;
			wdata[14] = 0;
			wdata[15] = 0;	
			}
		res = f_write(&file, wdata, 16, &nbytes);	
		if(P_COLOR[pad_x-1]>7)  //pad is disable
			{		
			f_close(&file);	
			return res;
			}
		if(res==FR_OK)
			{
			f_lseek(&file, (48+(1584*CURRENT_PRESET)+64+(192*(pad_x-1))));
			res = f_write(&file, P_SAMPLE_NAME[pad_x-1], 64, &nbytes);	
			if(res==FR_OK)
				{
				f_lseek(&file, (48+(1584*CURRENT_PRESET)+128+(192*(pad_x-1))));						
				res = f_write(&file, P_WAVEFORM[pad_x-1], 100, &nbytes);		
				f_close(&file);
				return res;						
				}
			else				
				{
				f_close(&file);
				return res;				
				}	
			}
		else
			{
			f_close(&file);
			return res;				
			}			
		f_close(&file);	
		}
	return res;	
	}
	
	
	
/////////////////////////////////////////////////////
//
//	write to file Presets.pst new preset
//	mode: 0 - new 1 - duplicate
//	
uint8_t write_new_dupl_prc(uint8_t mode)
	{
	f_close(&file);
	res = f_open(&file, presets_path, FA_WRITE);
	if(res==FR_OK)
		{
		uint16_t i;	
		wdata[0] = TOTAL_PRESETS+1; 	
		f_lseek(&file, 0);
		res = f_write(&file, wdata, 1, &nbytes);	
		if(res==FR_OK)
			{
			if(mode==0)				//create new preset
				{
				for(i=0;i<1584;i++)
					{
					wdata[i] = 0;
					}	
				wdata[0] = 117;		//enable preset	
				wdata[3] = 1;		//color red default	
				for(i=0;i<8;i++)
					{
					wdata[54+(192*i)] = 0x04;		//BPM 120.0 	
					wdata[55+(192*i)] = 0xB0;		//BPM 120.0	
					wdata[56+(192*i)] = 30;			//Gain=0dB
					}	
				sprintf((char*)&wdata[16], "%s", "NEW PRESET");					
				}
			else							//create duplicate
				{
				f_close(&file);		
				res = f_open(&file, presets_path, FA_READ);
				if(res==FR_OK)
					{
					f_lseek(&file, 48+(1584*(CurrentPRSTPosition+PRSTCCP-1)));
					if(res==FR_OK)
						{	
						f_read(&file, wdata, 1584, &nbytes);	
						f_close(&file);
						f_open(&file, presets_path, FA_WRITE);
						}
					else
						{
						f_close(&file);
						return res;			
						}						
					}
				else
					{
					f_close(&file);
					return res;		
					}					
				}
			f_lseek(&file, (1584*TOTAL_PRESETS)+48);	
			res = f_write(&file, wdata, 1584, &nbytes);	
			f_close(&file);	
			}
		else
			{
			f_close(&file);
			return res;				
			}	
		}
	return res;	
	}

	
/////////////////////////////////////////////////////
//
//	delete one preset
//
//	input format 0...63
//		
uint8_t delete_prc(uint8_t prst)
	{
	if((prst>63) || (TOTAL_PRESETS<2))
		{
		return 0xFF;	
		}		
	uint8_t i;	
	for(i=0;i<32;i++)
		{
		wdata[i] = 0;	
		}	
	wdata[0] = TOTAL_PRESETS-1;
	wdata[1] = UTILITY_SETTINGS[2];
	wdata[2] = UTILITY_SETTINGS[3];
	wdata[3] = UTILITY_SETTINGS[5];
	wdata[4] = UTILITY_SETTINGS[1];
	if(UTILITY_SETTINGS[0]==prst)
		{	
		wdata[12] = 0;		//load 1 preset default	
		}
	else if((UTILITY_SETTINGS[0]>prst) && (UTILITY_SETTINGS[0]<64))
		{
		wdata[12] = UTILITY_SETTINGS[0]-1;	//shift preset number
		}
	else
		{
		wdata[12] = UTILITY_SETTINGS[0]; 		//copy only	
		}
	wdata[13] = UTILITY_SETTINGS[6];
	wdata[14] = (UTILITY_SETTINGS[4]>>8)&0x000000FF;
	wdata[15] = UTILITY_SETTINGS[4]&0x000000FF;
	for(i=0;i<8;i++)
		{	
		if(FAST_LOADING[i]==prst)
			{
			wdata[16+i] = 0xFF;			//delete FL pad
			}
		else if((FAST_LOADING[i]>prst) && (FAST_LOADING[i]<64))
			{
			wdata[16+i] =	FAST_LOADING[i]-1;		//shift number
			}
		else
			{
			wdata[16+i] =	FAST_LOADING[i];		//copy only
			}
		}
	f_close(&file);
	res = f_open(&file, presets_path, FA_WRITE|FA_READ);
	if(res==FR_OK)
		{
		res = f_write(&file, wdata, 32, &nbytes);
		if(res==FR_OK)
			{		
			for(i=prst;i<(TOTAL_PRESETS-1);i++)
				{
				res = f_lseek(&file, 48+(1584*(i+1)));	
				if(res!=FR_OK)
					{
					return res;	
					}					
				res = f_read(&file, wdata, 1584, &nbytes);	
				if(res!=FR_OK)
					{
					return res;	
					}		
				res = f_lseek(&file, 48+(1584*i));	
				if(res!=FR_OK)
					{
					return res;	
					}	
				res = f_write(&file, wdata, 1584, &nbytes);	
				if(res!=FR_OK)
					{
					return res;	
					}		
				}
			res = f_lseek(&file, 48+(1584*(TOTAL_PRESETS-1)));	
			if(res!=FR_OK)
				{	
				return res;	
				}		
			res = f_truncate(&file);	
			if(res!=FR_OK)
				{	
				return res;	
				}			
			f_close(&file);
			}
		else
			{
			f_close(&file);
			return res;	
			}		
		}
	else
		{
		f_close(&file);
		return res;	
		}
	return res;	
	}
	
	
/////////////////////////////////////////////////////
//
//	create new Presets.pst file
//		
uint8_t newpstfile(void)
	{
	uint16_t i;	
	res = f_opendir(&dir, fldname);				//open directory SAMPLER	
	if(res!=FR_OK)											//if directory SAMPLER does not exist, create directory							
		{
		res = f_mkdir(fldname);	
		if(res!=FR_OK)						
			{
			return res;	
			}				
		}		
	res = f_open(&file, presets_path, FA_CREATE_NEW | FA_WRITE);
	if(res!=FR_OK)						
		{
		return res;	
		}	
	for(i=0;i<48;i++)			//prepare wdata
		{
		wdata[i] = 0;	
		}		
	wdata[0] = 1;	
	wdata[3] = 1;	
	wdata[13] = 3;	
	wdata[14] = 0x04;	
	wdata[15] = 0xB0;
	wdata[16] = 0xFF;		
	wdata[17] = 0xFF;
	wdata[18] = 0xFF;
	wdata[19] = 0xFF;
	wdata[20] = 0xFF;
	wdata[21] = 0xFF;
	wdata[22] = 0xFF;
	wdata[23] = 0xFF;
	wdata[32] = 0xA9;
	wdata[33] = 0xFE;
	wdata[34] = 0x95;
	wdata[35] = 0x8C;		
	wdata[36] = 0xA9;
	wdata[37] = 0xFE;
	wdata[38] = 0x95;
	wdata[39] = 0xA0;
	wdata[40] = 0xA9;
	wdata[41] = 0xFE;
	wdata[42] = 0x28;
	wdata[43] = 0xF1;
	res = f_write(&file, &wdata, 48, &nbytes);
	if(res!=FR_OK)						
		{
		return res;	
		}	
	for(i=0;i<1584;i++)			//prepare wdata
		{
		wdata[i] = 0;	
		}	
	wdata[0] = 117;		//enable preset	
	wdata[3] = 1;		//color red default	
	for(i=0;i<8;i++)
		{
		wdata[54+(192*i)] = 0x04;		//BPM 120.0 	
		wdata[55+(192*i)] = 0xB0;		//BPM 120.0	
		wdata[56+(192*i)] = 30;			//Gain=0dB
		}	
	sprintf((char*)&wdata[16], "%s", "FIRST PRESET");		
	res = f_write(&file, &wdata, 1584, &nbytes);
	if(res!=FR_OK)						
		{
		return res;	
		}		
	res = f_close(&file);		
	if(res!=FR_OK)						
		{
		return res;	
		}	
	return 0;	
	}	
	
	
	
/////////////////////////////////////////////////////
//
//	moove preset
//	mv 0...63
//	np 0...63
uint8_t move_preser_prc(uint8_t mv, uint8_t np)
	{
	if(np>63)
		{
		return 0xFF;	
		}		
	if(mv>63)
		{
		return 0xFF;	
		}			
	if(mv==np)
		{
		return 0xFE;	
		}
	uint8_t i;	
	for(i=0;i<32;i++)
		{
		wdata[i] = 0;	
		}	
	wdata[0] = TOTAL_PRESETS;
	wdata[1] = UTILITY_SETTINGS[2];
	wdata[2] = UTILITY_SETTINGS[3];
	wdata[3] = UTILITY_SETTINGS[5];
	wdata[4] = UTILITY_SETTINGS[1];
	if(UTILITY_SETTINGS[0]==mv)
		{	
		wdata[12] = np;	
		}
	else 
		{
		if(np>mv)		//shift down
			{
			if(UTILITY_SETTINGS[0]<mv)
				{
				wdata[12] = UTILITY_SETTINGS[0];
				}
			else if((UTILITY_SETTINGS[0]>mv) && (UTILITY_SETTINGS[0]<=np))
				{
				wdata[12] = UTILITY_SETTINGS[0]-1;	
				}
			else
				{
				wdata[12] = UTILITY_SETTINGS[0];	
				}				
			}
		else				//shift up
			{
			if(UTILITY_SETTINGS[0]<np)
				{
				wdata[12] = UTILITY_SETTINGS[0];
				}
			else if((UTILITY_SETTINGS[0]>=np) && (UTILITY_SETTINGS[0]<=mv))
				{
				wdata[12] = UTILITY_SETTINGS[0]+1;	
				}
			else
				{
				wdata[12] = UTILITY_SETTINGS[0];	
				}	
			}
		}
	wdata[13] = UTILITY_SETTINGS[6];
	wdata[14] = (UTILITY_SETTINGS[4]>>8)&0x000000FF;
	wdata[15] = UTILITY_SETTINGS[4]&0x000000FF;
	for(i=0;i<8;i++)
		{
		if(FAST_LOADING[i]==mv)
			{	
			wdata[16+i] = np;	
			}
		else if(FAST_LOADING[i]==0xFF)
			{
			wdata[16+i] = 0xFF;	
			}			
		else  
			{
			if(np>mv)		//shift down
				{
				if(FAST_LOADING[i]<mv)
					{
					wdata[16+i] = FAST_LOADING[i];
					}
				else if((FAST_LOADING[i]>mv) && (FAST_LOADING[i]<=np))
					{
					wdata[16+i] = FAST_LOADING[i]-1;	
					}
				else
					{
					wdata[16+i] = FAST_LOADING[i];	
					}				
				}
			else				//shift up
				{
				if(FAST_LOADING[i]<np)
					{
					wdata[16+i] = FAST_LOADING[i];
					}
				else if((FAST_LOADING[i]>=np) && (FAST_LOADING[i]<=mv))
					{
					wdata[16+i] = FAST_LOADING[i]+1;	
					}
				else
					{
					wdata[16+i] = FAST_LOADING[i];	
					}	
				}
			}
		}
	f_close(&file);
	res = f_open(&file, presets_path, FA_WRITE|FA_READ);		
	if(res==FR_OK)
		{		
		res = f_write(&file, wdata, 32, &nbytes);
		if(res==FR_OK)
			{		
			res = f_lseek(&file, 48+(1584*mv));	
			if(res==FR_OK)
				{	
				res = f_read(&file, wdata, 1584, &nbytes);		
				if(res==FR_OK)
					{
					res = f_lseek(&file, (1584*TOTAL_PRESETS)+48);	
					if(res==FR_OK)
						{	
						res = f_write(&file, wdata, 1584, &nbytes);			
						if(res==FR_OK)
							{	
							if(np>mv)		//shift down
								{	
								for(i=mv;i<np;i++)
									{
									res = f_lseek(&file, 48+(1584*(i+1)));	
									if(res!=FR_OK)
										{
										return res;	
										}		
									res = f_read(&file, wdata, 1584, &nbytes);	
									if(res!=FR_OK)
										{
										return res;	
										}		
									res = f_lseek(&file, 48+(1584*i));	
									if(res!=FR_OK)
										{
										return res;	
										}	
									res = f_write(&file, wdata, 1584, &nbytes);	
									if(res!=FR_OK)
										{
										return res;	
										}					
									}	
								}
							else		//shift up
								{
								for(i=mv;i>np;i--)
									{
									res = f_lseek(&file, 48+(1584*(i-1)));	
									if(res!=FR_OK)
										{
										return res;	
										}		
									res = f_read(&file, wdata, 1584, &nbytes);	
									if(res!=FR_OK)
										{
										return res;	
										}		
									res = f_lseek(&file, 48+(1584*i));	
									if(res!=FR_OK)
										{
										return res;	
										}	
									res = f_write(&file, wdata, 1584, &nbytes);	
									if(res!=FR_OK)
										{
										return res;	
										}					
									}	
								}		
							res = f_lseek(&file, (1584*TOTAL_PRESETS)+48);
							if(res!=FR_OK)
								{
								return res;	
								}	
							res = f_read(&file, wdata, 1584, &nbytes);	
							if(res!=FR_OK)
								{
								return res;	
								}	
							res = f_lseek(&file, 48+(1584*np));
							if(res!=FR_OK)
								{
								return res;	
								}	
							res = f_write(&file, wdata, 1584, &nbytes);	
							if(res!=FR_OK)
								{
								return res;	
								}	
							res = f_lseek(&file, 48+(1584*TOTAL_PRESETS));	
							if(res!=FR_OK)
								{	
								return res;	
								}		
							res = f_truncate(&file);	
							if(res!=FR_OK)
								{	
								return res;	
								}	
							}
						else
							{
							f_close(&file);
							return res;			
							}
						}
					else
						{
						f_close(&file);
						return res;			
						}
					}
				else
					{
					f_close(&file);
					return res;			
					}
				}
			else
				{
				f_close(&file);
				return res;			
				}				
			}
		else
			{
			f_close(&file);
			return res;			
			}
		}
	else
		{
		f_close(&file);
		return res;	
		}
	return res;	
	}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



