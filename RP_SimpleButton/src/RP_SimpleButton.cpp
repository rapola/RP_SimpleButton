/*
 * RP_SimpleButton.cpp
 *
 *  Created on: 22.03.2021
 *      Author: ralf.poschner
 */

#include "RP_SimpleButton.h"

/*
 * Call to initialize an object
*/
RP_SimpleButton::RP_SimpleButton(){
}


/*
 * Call to initialize the values if not default is used
*/
void RP_SimpleButton::begin(bool inv){
	invert = inv;
}

/*
* Call this function frequently in main loop, keeps the values up to date
* Parameters:
* 	- input		-	the input which must be debounced
*/
void RP_SimpleButton::Update(bool input){
	uint32_t msTick = millis();
	bool inVal = input;
		if(invert == true){
			inVal = !inVal;
		}
	if(msTick - mem_tm_lastChange < dbTime){
		flag_changed = false;
	}
	else{
		last_state = state;
		state = inVal;										  //update Button state
    flag_changed = (state != last_state);
		if(flag_changed){
			mem_tm_lastChange = msTick;
		}
	}

}

/*
 * returns the current state of the Button
 */
bool RP_SimpleButton::BtnState(){
	return state;
}


