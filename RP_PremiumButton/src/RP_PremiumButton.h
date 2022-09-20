/*
 * RP_PremiumButton.h
 *
 *  Created on: 21.03.2021
 *  Author: ralf.poschner
 */

#ifndef RP_PremiumButton_H
#define RP_PremiumButton_H



/*
 * include Arduino.h for millis()
 */

#include <Arduino.h>

class RP_PremiumButton
{
	public:
		/*
     * Call to generate an object
    */
    RP_PremiumButton();
	
		/*
		*	Initialize a Button object, if inv == true, button is invertet (e.g. pullup)
		*/
    void begin(bool inv);
		
		/*
		* Call this function frequently in main loop
		* Parameters:
		* 	- ctrl		-	if zero, output always read as zero
		* 	- lp_ena	-	if zero, long press detection off
		* 	- input		-	the input which must be debounced
		*/
		void Update(bool ctrl, bool lp_ena, bool input);
		
		/*
		* Call this function to receive the current State of the Button
		*/
		bool BtnState();
		
		/*
		* Call this function to receive the current flipflop State of the Button
		*/
		bool BtnFlipFlop();

		/*
		* Call this function to receive the delayed state of the Button
		*/
		bool BtnDelayed();

		/*
		* Call this function to receive the long pressed state
		* this state is active until Button is pressed again or BtnLongPressRst() function is called
		*/
		bool BtnLongPress();

		/*
		* Call this function to reset the long pressed state by software if button is not pressed by user
		*/
		void BtnLongPressRst();

		/*
		* Call this function to receive the press acknowledge
		*/
		bool BtnAck();

		/*
		* Call this function to receive the Button is long pressed acknowledge
		*/	
		bool BtnLpAck();
    
		/*
		* Changeable variables, default initialisation
		*/
    uint32_t dbTime = 25;                 //debounce Time                                                   (25 mS is good value)
		uint32_t tm_delayed = 5000;           //time for off delay                                              (if not used, set to 5000 mS)
		uint32_t tm_press_ack = 400;          //time for duration of acknowledging button press detected        (400 mS is good value)
		uint32_t tm_lp = 4000;                //time until long press is detected                               (4000 mS is good value)
		uint32_t tm_lp_ack = 400;             //time for duration of acknowledging button long press detected   (400 mS is good value)
    uint32_t press_cnt = 0;               //counter how often button is pressed.
    
	private:

		bool invert = false;            //if true, logic interprets low as pressed                        (e.g. if pullup used) (default set to 0)
		uint32_t mem_tm_lastChange;     //time of last state change (mS)                                  (set to 0)
		bool state;                     //current button state, true if pressed                           (set to 0)
		bool last_state;                //previous button state                                           (set to 0)
		bool flag_changed;              //flag, state changed since last read                             (set to 0)
		bool ack;                       //high for duration of tm_ack                                     (set to 0)
		bool lp_ack;                    //high for duration of tm_lp_ack                                  (set to 0)
		bool delayed;                   //delayed low after button was pressed. needs a zero-crossing
                                    //for retriggering (safe if a switch is used instead of a button) (set to 0)
		bool delaystate;                //flag                                                            (set to 0)
		uint32_t tms_delay;				      //stores the time for delay                                       (set to 0)
		bool flipflop;					        //flip-flop output, toggles each debounced presss                 (set to 0)
		bool last_flipflop;				      //stores last flip flop state                                     (set to 0)
		bool lp_prev;					          //flag                                                            (set to 0)
		bool longpressed;               //high if button was long pressed                                 (set to 0)
		uint32_t tms_lp;                //stores the time for longpressed                                 (set to 0)
		uint32_t tms_lp_ack;            //stores the time for long pressed ack                            (set to 0)
		uint32_t tms_press_ack;         //stores the time for press ack
    bool flag_press_cnt;            //flag couted since last change...
		
		
};

#endif
