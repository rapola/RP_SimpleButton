/*
 * RP_PremiumButton.c
 *
 *  Created on: 21.03.2021
 *      Author: ralf.poschner
 */

#include "RP_PremiumButton.h"

/*
 * Call to initialize an object
*/
RP_PremiumButton::RP_PremiumButton(){
}


/*
 * Call to initialize the values if not default is used
*/
void RP_PremiumButton::begin(bool inv){
	invert = inv;
}

/*
* Call this function frequently in main loop, keeps the values up to date
* Parameters:
* 	- ctrl		-	if zero, output always read as zero
* 	- lp_ena	-	if zero, long press detection off
* 	- input		-	the input which must be debounced
*/
void RP_PremiumButton::Update(bool ctrl, bool lp_ena, bool input){
	uint32_t msTick = millis();
	bool inVal = (input && ctrl);
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

	if(state == false){										//handle press ack
		tms_press_ack = msTick;
	}
	if((state == true) && (msTick - tms_press_ack <= tm_press_ack)){
			ack = true;
		}
		else{
			ack = false;
		}

  if(state == true){                    //handle press counter
    if(flag_press_cnt == false){
      press_cnt++;
      flag_press_cnt = true;
    }
  }
  else{
    flag_press_cnt = false;
  }


	if(state == true && ctrl == true){						//handle flip flop
		if(last_flipflop == false){
			last_flipflop = true;
			flipflop = !flipflop;
		}
	}
	else{
		last_flipflop = false;
	}
	if(ctrl == false){
		flipflop = false;
	}

	if(delaystate == false){								//handle delayed off
		if((state == true) && (ctrl == true)){
			delaystate = true;
			tms_delay = msTick;
			delayed = true;
		}
	}
	if(delaystate == true){
		if(msTick - tms_delay >= tm_delayed){
			delayed = false;
			if((state == false) || (ctrl == false)){
				delaystate = false;
			}
		}
	}
	if(ctrl == false){
		delayed = false;
		delaystate = false;
	}

	if((state == true) && (lp_prev == false)){		//handle long press
		longpressed = false;
		if((msTick - tms_lp) > tm_lp){
			if(lp_ena == true){
				longpressed = true;
				lp_prev = true;
			}
		}
	}
	else{
		tms_lp = msTick;
	}
	if((state == false) && (lp_prev == true)){
		lp_prev = false;
	}
	if(ctrl == false){
		longpressed = false;
		lp_prev = false;
	}

	if(longpressed == false){								//handle long press ack
		tms_lp_ack = msTick;
	}
	if((longpressed == true) && (msTick - tms_lp_ack <= tm_lp_ack)){
		lp_ack = true;
	}
	else{
		lp_ack = false;
	}


}

/*
 * returns the current state of the Button
 */
bool RP_PremiumButton::BtnState(){
	return state;
}

/*
 * retruns the flipflop state of the Button
 */
bool RP_PremiumButton::BtnFlipFlop(){
	return flipflop;
}

/*
 * returns the delayed off state of the Button
 */
bool RP_PremiumButton::BtnDelayed(){
	return delayed;
}

/*
 * retruns the state if Button is long pressed
 */
bool RP_PremiumButton::BtnLongPress(){
	return longpressed;
}

/*
 * resets the long press state of the Button (instead of a second Button-press)
 */
void RP_PremiumButton::BtnLongPressRst(){
	longpressed = false;
	lp_prev = false;
}

/*
 * returns the acknowledge for Button press detected
 */
bool RP_PremiumButton::BtnAck(){
	return ack;
}

/*
 * returns the acknowledge for Button was long pressed
 */
bool RP_PremiumButton::BtnLpAck(){
	return lp_ack;
}

