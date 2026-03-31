/******************<Dependencies>*****************/
#include "peripherals/audio.h"
/******************</Dependencies>*****************/


/******************<Private variables>*****************/
/******************</Private variables>*****************/


/******************<Public variables>*****************/
//dfplayer_t dfplayer;		// create instance of DFplayer module
/******************</Public variables>*****************/


/******************<Function definitions>*****************/
/*******init_dfplayer*******
 * Description
        > initializes DFPlayer to play audio
 * Arguments
        > N/A
 * Returns
        > N/A
*/
/*
void init_dfplayer(){
	// initialize relevant UART bus
		//doorsense_init_uart(DFPLAYER_UART_CH, DF_UART_BAUDRATE, DF_UART_TX_PIN, DF_UART_RX_PIN);

	// initialize dfplayer using library function
		dfplayer_init(&dfplayer, DFPLAYER_UART_CH, DF_UART_TX_PIN, DF_UART_RX_PIN);

	// sleep for 200ms between commands
		sleep_ms(200);

	// apply settings
		dfplayer_set_volume(&dfplayer, 30);	// set volume (0-30)
    	sleep_ms(200);
}
*/

/*******play_track*******
 * Description
        > sends an instruction to the DFplayer to play a track from
			the "mp3" folder
 * Arguments
        > uint8_t track: track ID to play
 * Returns
        > N/A
*/
/*
void play_track(uint8_t track){
	dfplayer_play_mp3_folder(&dfplayer, track);
	sleep_ms(200);	// always delay 200ms after sending instructions
}
*/
/******************</Function definitions>*****************/