# Sampler DJS-500 nexus


This is a sampler project that has a design in CDJ-2000 nexus and DJM-900 nexus style. The look and feel and the GUI have the same style. 
Sampler based on STM32F746G-DISCO board and pads from Akai LPD8. Replaced RGB LEDs in the pads.
The sampler supports Pro Dj Link. It automatically selects the master deck, can receive information about BPM and beat moments, beats from the CDJ. 
This allows you to synchronize samples with the track on the air, as well as trigger samples without delays using quantize.
Samples are stored on a micro SD card, wav format is supported.

https://youtu.be/_pMT7O0JRTI

https://youtu.be/_ofyAOzehKc

https://youtu.be/i8zc_d4uLBs

https://youtu.be/rUySWEsYK1w

# The current firmware version is 1.77

	ver. 0.35
		- added all periph buttons, leds, VRs and encoder
	ver. 0.36
		- added buttons handler
	ver. 0.37
		- added USB USART debug code
		- added first service mode 
	ver. 0.38
		- improved encoder noise canceller code
	ver. 0.41
		- added service mode code parts
		- added ADCs VRs code with hysteresis and filter
	ver. 0.45
		- added service mode code parts
	ver. 0.46
		- fixed SERVICE MODE code
	ver. 0.47
		- added sync out led blink
	ver. 0.48
		- the signals from the pads are inverted, the pullups are replaced with pulldowns. It is also changed in the hardware
	ver. 0.49
		- added PWM backlight
	ver. 0.51
		- added PRESETS select display
	ver. 0.53
		- added reading preset preview pads color, rating
		- added loading presets from preset list
		- added long blink encoder led if the preset is loaded for a very long time 
	ver. 0.54
		- added color instruments icons
		- added shadow at the rating stars
	ver. 0.57
		- added sync pitch 
		- added imitate deck mode
		- added blink pads
	ver. 0.61
		- added dynamic timeline on waveforms 
		- added colored CUE points and colored samle name
	ver. 0.63
		- added first sequencer
	ver. 0.65
		- minor fixes for the GUI sequencer
		- added status bar with playback status
		- added icons for effect and sync. out
	ver. 0.67
		- added on-off pads label
	ver. 0.68
		- minor fixes GUI
	ver. 0.70
		- fixed pad1 RGB led problem
		- minor fixes
	ver. 0.72
		- minor GUI fixes
		- added UTILITY window
		- added master bpm shield
	ver. 0.73
		- added timestamp for pads press moments and filter 
		- added ATT_LV for pads
	ver. 0.74
		- changed "+" symbol in 15P font
		- minol fixes in gui preset list
		- added gui.h and audio.h
	ver. 0.77
		- added EDIT PRESER window
		- changed SYNC OUT and EFFECT GUI gray color
	ver. 0.79
		- improved debug mode
		- added interrupt for received uart
	ver. 0.80
		- added processing to the EDIT for the encoder button
		- changed project structure main.c file is split into many * .h files
	ver. 0.81
		- added preset list edit menu
	ver. 0.87
		- added DELETE DIALOG
		- added encoder_handler.h, key_handler.h
		- improved  DELETE DIALOG
		- added noise filter for encoder button
	ver. 0.88
		- fixed fixed bugs in GUI UTILITY
		- improved GUI preset list
		- improved the mechanism for creating screenshots, using both layers
	ver. 0.89
		- improved configuration in ffconf.h
	ver. 0.90
		- improved preset list gui
	ver. 0.91
		- improved UTILITY
		- add edit pad display, edit preset display, edit FL display
	ver. 0.94
		- improved UTILITY id address set
	ver. 0.98
		- added utility edit menu
		- added internal bpm generator
	ver. 1.06
		- added write uSD prc
	ver. 1.09
		- added edit preset display
		- added write preset uSD prc 
		- added keyboard and rename prc		
		- added keyboard animation	
	ver. 1.17
		- added blinking cursor for kyeboard
		- added waveform editor
		- improved edit pad display gui
		- improved home display gui
		- added simple waveform analyzer
	ver. 1.19
		- improved edit pad display
		- added prompt for edit pad display
		- added prompt for edit preset display
		- added first BROWSER display
	ver. 1.23
		- replaced FATFS lib! (previous lib not work USE_LFN for READDIR)
	ver. 1.25
		- fixed display of sample names inside folders. Folder removed from title bar
		- fixed edit pad GUI bugs
		- added realtime pad color update when editing a pad
	ver. 1.26
		- fixed ethernetif.c beat process for external sync
		- added FLLIST_DISPLAY
	ver. 1.28
		- added sequence editor
	ver. 1.31
		- minor fixes
		- added [folder] style in BROWSER display
		- added dynamic pad in edit pad display gui
	ver. 1.33
		- added first FL presets animation
	ver. 1.34
		- improved FL presets animation
	ver. 1.35
		- added "create new preset" and "create duplicate" process
	ver. 1.36
		- improved "create new preset" and "create duplicate" process
		- added "preset list is full" and "error x" msg
		- added automaticly wzoom for waveform
	ver. 1.37
		- added noise filters for buttons PRESET, SHIFT, EDIT, BACK, EFFECT
	ver. 1.39
		- added delete prc
		- fixed display of MAC-address in service mode
	ver. 1.40
		- fixed delete prc
	ver. 1.42
		- work on the edit fl list
	ver. 1.43
		- new FL preset load animation
	ver. 1.44
		- added background picture on edit preset display
		- added FIR filter in WFMCREATE()
	ver. 1.47
		- improved WFMCREATE(), FIR and analising algorythm
		- the algorithm for displaying a big waveform has been changed
		- added a mechanism for creating a template Presets.pst file on an empty sd card
	ver. 1.48
		- changed color map for big waveform (colors from cdj dump)
	ver. 1.51
		- fixed a bug: where inactive pads in the edit_pad_display would start glowing after the pad_x being edited was stopped
		- improved edit_pad_display
	ver. 1.55
		- bug fixes in the function REDRAW_PAD_EDIT()
		- added first move preset display
	ver. 1.56
		- bug fixes in the MOVE_PRESET	
		- first move_preser_prc
	ver. 1.57
		- improved move_preser_prc	
	ver. 1.59
		- bug fixes in the function REDRAW_PAD_EDIT()
		- added new icons for presets
	ver. 1.60
		- added new icons for presets
	ver. 1.61
		- changed PLL frequency multiplier PeriphClkInitStruct.PLLI2S.PLLI2SN = 271 (135 old)
	ver. 1.65
		- quantize first
	ver. 1.68
		- improved quantize process
		- minor fixes
		- added first effects
	ver. 1.69
		- improved trans effect process
	ver. 1.70
		- optimized and improved trans effect process
	ver. 1.71
		- added ram fill percentage status
	ver. 1.73
		- optimized HAL_SAI_Transmit_IT
		- added uart sync out signal
	ver. 1.74
		- bug fixed in audio handler limiting play_adr size at 0xFFFFF
		- added errors descriptor
		- bug fixed in waveform color draw_st_wvfm()
	ver. 1.75
		- changed the principle of operation of SPI2 for PADS LEDs. Now SPI2 works via DMA.
	ver. 1.77
		- improved performance of Moog Filter and LPF

# Menu navigation
![Menu navigation](https://user-images.githubusercontent.com/17586315/218270290-57c5838d-2754-4a44-8228-09e534868395.png)

# Screenshots
![SCREEN_009](https://user-images.githubusercontent.com/17586315/218270592-56c0fd57-2d79-43f2-b6ac-b8895235987e.png)
![SCREEN_110](https://user-images.githubusercontent.com/17586315/218270595-8924f8f7-82ac-434d-97aa-5d83247af98c.png)
![SCREEN_124](https://user-images.githubusercontent.com/17586315/218270596-a87442e1-7c31-45e7-a85c-54f42a52f236.png)
![SCREEN_176](https://user-images.githubusercontent.com/17586315/218270598-14e05891-1216-468f-9314-d474ef31a792.png)
![SCREEN_189](https://user-images.githubusercontent.com/17586315/218270599-4e1e2bfb-7b0d-4c6e-917d-50c12443f107.png)
![SCREEN_191](https://user-images.githubusercontent.com/17586315/218270601-9ba86536-899d-461e-b158-20b6dbfcc69e.png)
![SCREEN_195](https://user-images.githubusercontent.com/17586315/218270604-82f4fbc2-57c9-4bf6-be57-d1d82506dc54.png)
![SCREEN_217 new](https://user-images.githubusercontent.com/17586315/218270606-49a59def-97a9-4f28-9492-5655c13fbb5f.png)
![SCREEN_217](https://user-images.githubusercontent.com/17586315/218270608-b8a6ffa2-9675-4c78-8668-b8e277ed840c.png)
![SCREEN_236](https://user-images.githubusercontent.com/17586315/218270610-45c6c8cf-4dda-402c-9825-754d0829aaf0.png)
![SCREEN_249](https://user-images.githubusercontent.com/17586315/218270611-896513fa-ead0-4d4b-bf1c-7124e4a1e4dc.png)
![SCREEN_285](https://user-images.githubusercontent.com/17586315/218270612-aab26510-5be6-4e58-86fe-fa9bed4eef91.png)
![SCREEN_414](https://user-images.githubusercontent.com/17586315/218270613-632bfe74-5a69-41fe-a869-1e4c6d171434.png)
![SCREEN_449_new](https://user-images.githubusercontent.com/17586315/218270616-a6e1ada6-e11e-4314-89e5-5cf0005870ad.png)
![SCREEN_456](https://user-images.githubusercontent.com/17586315/218270618-7608fdc4-c0b9-4704-a40e-8ef76b1b4d95.png)
![SCREEN_475](https://user-images.githubusercontent.com/17586315/218270623-cf641396-1be7-4dd8-bd11-41395835d6a1.png)
![SCREEN_734](https://user-images.githubusercontent.com/17586315/218270627-66c4989f-2389-4c8a-a5e4-5d359ea66515.png)
![SCREEN_740](https://user-images.githubusercontent.com/17586315/218270630-b3cc92d3-6e4b-41dd-81ad-a7646a2d496c.png)
![SCREEN_749](https://user-images.githubusercontent.com/17586315/218270631-7e3ebd24-95dc-4a10-ba52-202bf1027aaa.png)
![SCREEN_757](https://user-images.githubusercontent.com/17586315/218270636-424b24f2-d654-4bba-be04-71a012b658e6.png)
![SCREEN_758](https://user-images.githubusercontent.com/17586315/218270637-f238e8f1-e591-466e-bace-158c412e5069.png)
![SCREEN_795](https://user-images.githubusercontent.com/17586315/218270638-e09c61b0-0b25-4ba7-81fc-ad53fd92b32c.png)
![SCREEN_829](https://user-images.githubusercontent.com/17586315/218270641-4797cfc7-9d26-4ff3-baf5-8063de9603e4.png)
![SCREEN_839](https://user-images.githubusercontent.com/17586315/218270643-1472ce0b-4751-49fa-81af-fbfba53c7339.png)
![SCREEN_905_new](https://user-images.githubusercontent.com/17586315/218270644-1b2718f4-2e20-4b34-81eb-95def8af30da.png)
![SCREEN_956](https://user-images.githubusercontent.com/17586315/218270646-72f0927d-7f5a-4a06-8add-3d222e0b20b4.png)


Some photos:
![1](https://user-images.githubusercontent.com/17586315/141431744-7926b9c0-66c5-4e81-8e79-dfa8d694c17a.jpg)
![2020_07_29_23_54_IMG_2746](https://user-images.githubusercontent.com/17586315/141431752-045c9760-dcae-4291-88ce-1faf58bc2d01.jpg)
![2020_08_02_23_38_IMG_2779](https://user-images.githubusercontent.com/17586315/141431758-73a1c034-c52d-46dc-9630-2779e5225736.jpg)
![2020_09_19_19_30_IMG_2952](https://user-images.githubusercontent.com/17586315/141431761-af66c3b8-5382-429a-a4c0-df0ac1fe35d9.jpg)
![2020_09_19_19_30_IMG_2953](https://user-images.githubusercontent.com/17586315/141431763-6f0385d1-ee86-439b-991e-0e9e275454be.jpg)
![2020_09_29_15_57_IMG_3006](https://user-images.githubusercontent.com/17586315/141431765-738f16d6-a3eb-4b99-bfd8-de3a9253ce4e.jpg)
![2020_09_30_11_38_IMG_3007](https://user-images.githubusercontent.com/17586315/141431766-749cb9f2-9d5b-4931-9c0f-d01fd1d15ec5.jpg)
![2020_10_15_12_30_IMG_3105](https://user-images.githubusercontent.com/17586315/141431768-e45a38fa-1e5e-47b8-82cd-c3826944b279.jpg)
![2020_11_01_00_35_IMG_3214](https://user-images.githubusercontent.com/17586315/141431769-d19bd28a-7c59-4ec7-9132-fa8690ced81a.jpg)
![2020_11_01_02_20_IMG_3215](https://user-images.githubusercontent.com/17586315/141431770-7faffe0b-63af-431e-a747-b1f407a6fbcb.jpg)
![2020_11_01_15_38_IMG_3219](https://user-images.githubusercontent.com/17586315/141431771-0d92e91a-e6f1-44cb-ad02-cde3a1f0549f.jpg)
![2020_11_01_21_26_IMG_3228](https://user-images.githubusercontent.com/17586315/141431774-ac49e49e-a285-4a9c-8272-56072f5c26fb.jpg)
![2020_11_01_21_26_IMG_3229](https://user-images.githubusercontent.com/17586315/141431776-0b8c6510-573f-48fc-8447-30a6e3f093c8.jpg)
![2020_11_03_14_13_IMG_3241](https://user-images.githubusercontent.com/17586315/141431778-621c6a3a-789f-4ec7-aadc-28da0c6c1cc1.jpg)
![2020_11_03_21_55_IMG_3242](https://user-images.githubusercontent.com/17586315/141431780-d81d35cc-d7b9-4ffa-bcaa-f25801b73a28.jpg)
![2020_11_03_23_34_IMG_3244](https://user-images.githubusercontent.com/17586315/141431782-e9fe3a58-b4b0-4081-a931-d13e3338bd9c.jpg)
![2020_11_23_22_04_IMG_3343](https://user-images.githubusercontent.com/17586315/141431783-75bf330d-f446-4043-bc53-918d2709c5e3.jpg)
![2020_11_29_21_47_IMG_3356](https://user-images.githubusercontent.com/17586315/141431784-bcc6e5d4-9e62-47af-af40-790d1f54c099.jpg)
![2020_11_29_21_54_IMG_3357](https://user-images.githubusercontent.com/17586315/141431785-7f02ab20-71a9-4e86-9c19-d8554316ee31.jpg)
![2020_12_03_11_01_IMG_3373](https://user-images.githubusercontent.com/17586315/141431787-e7f3f6c3-1f88-4c99-8a1e-ff51c90a10c1.jpg)
![2020_12_04_14_35_IMG_3376](https://user-images.githubusercontent.com/17586315/141431791-220a2b76-e157-49e0-bc0c-71a4ad1e16a3.jpg)
![2020_12_04_21_59_IMG_3377](https://user-images.githubusercontent.com/17586315/141431792-dcc125b8-c355-493b-9a1a-d131efebd863.jpg)
![2020_12_05_16_33_IMG_3378](https://user-images.githubusercontent.com/17586315/141431793-11c775dc-713c-430d-8260-269f99290ba6.jpg)
![2020_12_05_17_58_IMG_3380](https://user-images.githubusercontent.com/17586315/141431794-4f322e74-69ea-47b2-a518-9dcf35a0561f.jpg)
![2020_12_05_17_58_IMG_3381](https://user-images.githubusercontent.com/17586315/141431796-884bb174-c5fe-4ec0-a2c4-647e7a68cacc.jpg)
![2020_12_15_12_30_IMG_3422](https://user-images.githubusercontent.com/17586315/141431798-101606d3-77c7-491e-8955-32e87d6853b5.jpg)
![2020_12_15_12_30_IMG_3423](https://user-images.githubusercontent.com/17586315/141431799-c621ac21-8ee9-4037-87c4-5719d52a3b90.jpg)
![2020_12_15_12_30_IMG_3424](https://user-images.githubusercontent.com/17586315/141431802-79a850b4-5a68-4535-a8da-40f1f637a42a.jpg)
![2020_12_15_12_31_IMG_3425](https://user-images.githubusercontent.com/17586315/141431804-265ec84a-159d-4326-bddc-61d804f9e77a.jpg)
![2020_12_15_12_55_IMG_3426](https://user-images.githubusercontent.com/17586315/141431806-bae69b91-2a11-4274-a499-faf826e3a36a.jpg)
![2020_12_17_21_16_IMG_3439](https://user-images.githubusercontent.com/17586315/141431809-de2f3838-a97d-46ce-8149-08b64895af04.jpg)
![Body 1](https://user-images.githubusercontent.com/17586315/141431810-54b922d5-b694-4ed7-bced-c6484dcdba4f.jpg)
![Body 1_1](https://user-images.githubusercontent.com/17586315/141431812-a70c29b0-016b-4847-a5cb-f7be90a3ce0d.jpg)
![Body 10](https://user-images.githubusercontent.com/17586315/141431814-5681cf69-8d13-4c89-99c6-e0e27c3607aa.jpg)
![Body 11](https://user-images.githubusercontent.com/17586315/141431815-e7acca0d-bd40-411b-bc80-a17c5e3b4378.jpg)
![Body 12](https://user-images.githubusercontent.com/17586315/141431816-a45c9fd2-a498-47fe-8eec-fca6e350caab.jpg)
![Body 12_1](https://user-images.githubusercontent.com/17586315/141431817-6dbe73ef-0ef7-4e2a-8a48-d1839f0a0e1c.jpg)
![Body 16](https://user-images.githubusercontent.com/17586315/141431819-9d771fc7-063b-4b44-993c-4fdcf03b54d8.jpg)
![Body 18](https://user-images.githubusercontent.com/17586315/141431820-4f94d440-973f-43c9-a75f-2a320a935672.jpg)
![Body 19](https://user-images.githubusercontent.com/17586315/141431822-df94daad-a652-41fb-b1ca-872a4df88972.jpg)
![Body 2](https://user-images.githubusercontent.com/17586315/141431823-f9181489-cc44-48d5-9190-ed3a47c6fab3.jpg)
![Body 2_2](https://user-images.githubusercontent.com/17586315/141431824-416e8d9c-6c86-4c82-a464-f07d428ceff9.jpg)
![Body 7](https://user-images.githubusercontent.com/17586315/141431825-a68f7368-809b-4010-8eff-ac7c0d038141.jpg)
![Body 9](https://user-images.githubusercontent.com/17586315/141431827-d0bae0e8-7057-4a19-ab5f-394c4c0a88a1.jpg)
![encoder](https://user-images.githubusercontent.com/17586315/141431828-d2abe15f-e821-4ece-87a9-4b7e83cd0747.jpg)
![IMG_3469](https://user-images.githubusercontent.com/17586315/141431829-15de14c2-b5f2-4f3c-a080-7bdac47fda3a.jpg)
![Sampler icon ready](https://user-images.githubusercontent.com/17586315/141431831-8637c319-06a1-4d80-bfc9-2d96717a6305.jpg)
![Sampler icon](https://user-images.githubusercontent.com/17586315/141431834-006efb59-319c-4041-9213-3527f35dd845.jpg)

