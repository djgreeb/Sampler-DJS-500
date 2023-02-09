/////////////////////////////////////////////////////////////////////////////////////////////////
// Audio processing handler 44100Hz
//	product: DJS-500 sampler
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

int16_t keep_bits_from_16(int16_t input, int keepBits);			//bit crusher	
float MoogVCF(float input, float fc, float res);				//filter



void SAI2_IRQHandler(void)												////////////////////////////////AUDIO PROCESSING   44K1Hz//////////////////////////////
	{
  //GPIOI->BSRR = 0x00000002;						//led EDIT (contact D13 on board)
	HAL_SAI_IRQHandler(&hsai_BlockA2);
	HAL_SAI_Transmit_IT(&hsai_BlockA2, SAMPLE, 2);
		
	if((play_adr+step_position+3)<all_long)						//change all_long extract!
		{
		pitch =	sai_pitch;	
		end_of_track = 0;
		position+= pitch;		
		}
	else
		{
		position = 0;	
		end_of_track = 1;
		pitch = 0;		
		}			
			
	if(position>9999)	
		{
		if(end_of_track==0)					
			{
			step_position = position/10000;	
			play_adr+= step_position;	
			if(step_position==1)
				{
				LR[0][0] = LR[0][1];
				LR[1][0] = LR[1][1];
				LR[0][1] = LR[0][2];
				LR[1][1] = LR[1][2];
				LR[0][2] = LR[0][3];
				LR[1][2] = LR[1][3];					
				}
			else
				{
				sdram_adr = play_adr&0x001FFFFF;
				LR[0][0] = PCM[(sdram_adr>>13)][sdram_adr&0x1FFF][0];							
				LR[1][0] = PCM[(sdram_adr>>13)][sdram_adr&0x1FFF][1];
				sdram_adr = (play_adr+1)&0x001FFFFF;
				LR[0][1] = PCM[(sdram_adr>>13)][sdram_adr&0x1FFF][0];								
				LR[1][1] = PCM[(sdram_adr>>13)][sdram_adr&0x1FFF][1];		
				sdram_adr = (play_adr+2)&0x001FFFFF;
				LR[0][2] = PCM[(sdram_adr>>13)][sdram_adr&0x1FFF][0];									
				LR[1][2] = PCM[(sdram_adr>>13)][sdram_adr&0x1FFF][1];
				}
			sdram_adr = (play_adr+3)&0x001FFFFF;	
			LR[0][3] = PCM[(sdram_adr>>13)][sdram_adr&0x1FFF][0];							
			LR[1][3] = PCM[(sdram_adr>>13)][sdram_adr&0x1FFF][1];		
			}
		position = position%10000;	
		}	

	T = position;
	T = T/10000;
	T = T - 1/2.0F;
	
	even1 = LR[0][2];
	even1 = even1 + LR[0][1];
	odd1 = LR[0][2];
	odd1 = odd1 - LR[0][1];
	even2 = LR[0][3];
	even2 = even2 + LR[0][0]; 
	odd2 = LR[0][3];
	odd2 = odd2 - LR[0][0];
	c0 = (float)even1*COEF[0];
	r0 = (float)even2*COEF[1];
	c0 = c0 + r0;
	c1 = (float)odd1*COEF[2];
	r1 = (float)odd2*COEF[3];
	c1 = c1 + r1;
	c2 = (float)even1*COEF[4]; 
	r2 = (float)even2*COEF[5];
	c2 = c2 + r2;
	c3 = (float)odd1*COEF[6];
	r3 = (float)odd2*COEF[7];
	c3 = c3 + r3;

	SAMPLE_0 = c0+T*(c1+T*(c2+T*c3));
	SAMPLE_0*=ATNTR[ATT_LVL];
	

	even1 = LR[1][2];
	even1 = even1 + LR[1][1];
	odd1 = LR[1][2];
	odd1 = odd1 - LR[1][1];
	even2 = LR[1][3];
	even2 = even2 + LR[1][0]; 
	odd2 = LR[1][3];
	odd2 = odd2 - LR[1][0];
	c0 = (float)even1*COEF[0];
	r0 = (float)even2*COEF[1];
	c0 = c0 + r0;
	c1 = (float)odd1*COEF[2];
	r1 = (float)odd2*COEF[3];
	c1 = c1 + r1;
	c2 = (float)even1*COEF[4]; 
	r2 = (float)even2*COEF[5];
	c2 = c2 + r2;
	c3 = (float)odd1*COEF[6];
	r3 = (float)odd2*COEF[7];
	c3 = c3 + r3;

	SAMPLE_1 = c0+T*(c1+T*(c2+T*c3));
	SAMPLE_1*= ATNTR[ATT_LVL];
	
	
	if(EFFECT_ON)
		{
		if(UTILITY_SETTINGS[2]==4)	//CRUSH
			{	
			if(dk<VR_LEVEL)
				{
				dk++;	
				}
			else
				{
				dk = 0;
				PCM_2[0] = (int)SAMPLE_0;
				PCM_2[1] = (int)SAMPLE_1;
				PCM_2[0] = keep_bits_from_16(PCM_2[0], VR_LEVEL/10);		
				PCM_2[1] = keep_bits_from_16(PCM_2[1], VR_LEVEL/10);		
				}
			}	
		else if(UTILITY_SETTINGS[2]==3)			/////DISTORTION
			{
			if(abs(SAMPLE_0)<(VR_LEVEL<<7))
				{
				if(VR_PARAMETER_1==0)
					{
					SAMPLE_0 = 0;	
					}					
				else if(music_tim%VR_PARAMETER_1==0)
					{
					SAMPLE_0 = 0;	
					}						
				}
			if(abs(SAMPLE_1)<(VR_LEVEL<<7))
				{
				if(VR_PARAMETER_1==0)
					{
					SAMPLE_1 = 0;	
					}					
				else if(music_tim%VR_PARAMETER_1==0)
					{
					SAMPLE_1 = 0;	
					}		
				}	
			PCM_2[0] = (int)SAMPLE_0;
			PCM_2[1] = (int)SAMPLE_1;					
			}
		else if(UTILITY_SETTINGS[2]==2)			//LP FILTER
			{				
			SM0	= (VR_POS[VR_LEVEL]*SAMPLE_0)+(VR_POS[127-VR_LEVEL]*SM0);
			SM1	= (VR_POS[VR_LEVEL]*SAMPLE_1)+(VR_POS[127-VR_LEVEL]*SM1);	
			PCM_2[0] = (int)SM0;
			PCM_2[1] = (int)SM1;
			}
		else if(UTILITY_SETTINGS[2]==1)		//Moog Filter			
			{
			PCM_2[1] = (int)MoogVCF(SAMPLE_1, fcutoff, resonanse);		
			PCM_2[0] = PCM_2[1];	
			}
		else if(UTILITY_SETTINGS[2]==0)			//TRANS
			{
			if(trans_mute==1)
				{
				if(fade>0)
					{
					SAMPLE_0*= ATT[fade];
					SAMPLE_1*= ATT[fade];			
					fade--;	
					}
				else
					{
					if(VR_PARAMETER_1==0)
						{
						SAMPLE_0 = 0;
						SAMPLE_1 = 0;		
						}
					else
						{								
						SAMPLE_0/=(128-VR_PARAMETER_1);	
						SAMPLE_1/=(128-VR_PARAMETER_1);		
						}	
					}			
				}
			else
				{
				if(fade>0)
					{
					SAMPLE_0*= ATT[23-fade];
					SAMPLE_1*= ATT[23-fade];			
					fade--;	
					}	
				}
			PCM_2[0] = (int)SAMPLE_0;
			PCM_2[1] = (int)SAMPLE_1;	
			}	
		else
			{
			PCM_2[0] = (int)SAMPLE_0;
			PCM_2[1] = (int)SAMPLE_1;				
			}				
		}
	else
		{
		PCM_2[0] = (int)SAMPLE_0;
		PCM_2[1] = (int)SAMPLE_1;		
		}

			
	SAMPLE[3] = PCM_2[0]>>8;
	SAMPLE[2] = PCM_2[0]&0x00FF;
	SAMPLE[1] = PCM_2[1]>>8;
	SAMPLE[0] = PCM_2[1]&0x00FF;	
		
		
  //GPIOI->BSRR = 0x00020000;						//led EDIT (contact D13 on board)
	};


	
	
/////////////////////////////////	
//
// bit crusher 
//	
int16_t keep_bits_from_16( int16_t input, int keepBits ) 
	{
  return (input & (-1 << (keepBits)));
	}

	
/////////////////////////////////	
//
// filter 
//		
float MoogVCF(float input, float f, float fb)
	{
  input -= out4 * fb;
  input *= 0.35013 * (f*f)*(f*f);		
  out1 = input + 0.3 * in1 + (1 - f) * out1; // Pole 1
  in1  = input;
  out2 = out1 + 0.3 * in2 + (1 - f) * out2;  // Pole 2
  in2  = out1;
  out3 = out2 + 0.3 * in3 + (1 - f) * out3;  // Pole 3
  in3  = out2;
  out4 = out3 + 0.3 * in4 + (1 - f) * out4;  // Pole 4
  in4  = out3;
  return 2.0*out4;
	}	
	
	

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



