/******************<Dependencies>*****************/
#include "peripherals/audio.h"
/******************</Dependencies>*****************/


/******************<Available Voice Prompts>*****************/
/* 
 * If you want to add any audio prompts
 * to the system, make sure to add its
 * file number in the correct category here!
*/
const uint16_t serious_lab_open_prompts[] = {0, 1};
const uint16_t serious_lab_closed_prompts[] = {30, 31, 32};
const uint16_t silly_lab_open_prompts[] = {100, 101, 102};
const uint16_t silly_lab_closed_prompts[] = {130, 131, 132};
/******************</Available Voice Prompts>*****************/



/******************<Public variables>*****************/
dfplayer_t dfplayer;		// create instance of DFplayer module
/******************</Public variables>*****************/


/******************<Helper Functions>*****************/

/*******get_random_val*******
 * Description
        > generates a random number in a given range
		> inclusive of min/max!
 * Arguments
        > uint32_t min: minimum value in range
		> uint32_t max: maximum value in range
		> uint32_t* res: pointer to variable in which to store result
 * Returns
        > N/A
*/
void get_random_val(uint32_t min, uint32_t max, uint32_t* res) {
    *res = min + (get_rand_32() % (max - min + 1));
}


/*******pick_track*******
 * Description
        > chooses a random track to play from some array
 * Arguments
        > uint16_t* arr: pointer to array from which to pick a track to play
		> uint8_t num_elements: number of elements within the array
		> uint16_t* track: pointer to variable to store number of track to play
 * Returns
        > N/A
*/
void pick_track(const uint16_t* arr, uint8_t num_elements, uint16_t* track) {

	// cast num_elements to uint32_t
	uint32_t num_elements_32 = (uint32_t)(num_elements);

	// create variable to store index for audio track to play
	uint32_t track_index = 0;

	// get index for audio track to play
	get_random_val(0, num_elements_32 - 1, &track_index);

	// return index to track to play
    *track = arr[track_index];
}
/******************</Helper Functions>*****************/


/******************<Function definitions>*****************/
/*******init_dfplayer*******
 * Description
        > initializes DFPlayer to play audio
 * Arguments
        > N/A
 * Returns
        > N/A
*/
void init_dfplayer(){

	// initialize dfplayer using library function
		dfplayer_init(&dfplayer, DFPLAYER_UART_CH, DF_UART_TX_PIN, DF_UART_RX_PIN);
		sleep_ms(200);

	// apply settings
		dfplayer_set_volume(&dfplayer, 30);	// set volume (0-30)
    	sleep_ms(200);
}

/*******play_track*******
 * Description
        > sends an instruction to the DFplayer to play a track from
			the "mp3" folder
 * Arguments
        > uint16_t track: track ID to play
 * Returns
        > N/A
*/
void play_track(uint16_t track){
	dfplayer_play_mp3_folder(&dfplayer, track);
	sleep_ms(200);	// always delay 200ms after sending instructions
}



/*******play_audio_prompt*******
 * Description
        > high-level function to be called from run_doorsense()
		> plays some audio cue based on what action just occurred
 * Arguments
        > bool special_prompts_allowed:
			- true = use silly prompts
			- false= use serious prompts
		> uint8_t event_type:
			- 0 = lab is now open
			- 1 = lab is now closed
 * Returns
        > N/A
*/
void play_audio_prompt(bool special_prompts_allowed, uint8_t event_type){

	// Create variable to store track ID to play
		uint16_t track_id = 0;

	// Create variables to store which array to use and array size
		const uint16_t* arr = NULL;
		uint8_t arr_size = 0;
	
	// Get index for audio prompt to play based on event type
		switch(event_type){
			case (0): {
				arr = special_prompts_allowed ? silly_lab_open_prompts : serious_lab_open_prompts;
				arr_size = special_prompts_allowed ? ARRAY_SIZE(silly_lab_open_prompts) : ARRAY_SIZE(serious_lab_open_prompts);
				break;
			}
			case (1): {
				arr = special_prompts_allowed ? silly_lab_closed_prompts : serious_lab_closed_prompts;
				arr_size = special_prompts_allowed ? ARRAY_SIZE(silly_lab_closed_prompts) : ARRAY_SIZE(serious_lab_closed_prompts);
				break;
			}
			default: {
				printf("play_audio_prompt: invalid event type!\n");
				return;
			}
		}

	// Get audio prompt to play
		pick_track(arr, arr_size, &track_id);

	// Play audio prompt
		play_track(track_id);
		printf("TRACK TO PLAY: %u\n", track_id);
}
/******************</Function definitions>*****************/