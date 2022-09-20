/*
 * RP_SimpleButton.h
 *
 *  Created on: 20.09.2022
 *  Author: ralf.poschner
 */

#ifndef RP_SimpleButton_H_
#define RP_SimpleButton_H_



/*
 * include Arduino.h for millis()
 */

#include <Arduino.h>

class RP_SimpleButton
{
	public:
		/*
     * Call to generate an object
    */
    RP_SimpleButton();
	
		/*
		*	Initialize a Button object, if inv == true, button is invertet (e.g. pullup)
		*/
    void begin(bool inv);
		
		/*
		* Call this function frequently in main loop
		* Parameters:
		* 	- input		-	the input which must be debounced
		*/
		void Update(bool input);
		
		/*
		* Call this function to receive the current State of the Button
		*/
		bool BtnState();

    
		/*
		* Changeable variables, default initialisation
		*/	    
    uint32_t dbTime = 25;				    //debounce Time 													                        (25 mS is good value)

	
	private:

		bool invert = false;					  //if true, logic interprets low as pressed                        (e.g. if pullup used)	(default set to 0)
		uint32_t mem_tm_lastChange;		  //time of last state change (mS)									                (set to 0)
		bool state;						          //current button state, true if pressed								            (set to 0)
		bool last_state;				        //previous button state												                    (set to 0)
		bool flag_changed;				      //flag, state changed since last read								              (set to 0)

};

#endif
