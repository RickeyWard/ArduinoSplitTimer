// Rickey Ward 2017
// split on/off mosfet timer
//
// Toggle an IO pin on for x hours, off for x hours and repeat.
//

/// -- user set up
#define EnablePIN (2)
#define HOURS_ON  (6UL)
#define HOURS_OFF (18UL)

/// -- do not modify
//convervsion factors
#define MILLIS_IN_HOUR (3600000UL)
#define MILLIS_Multi (10000UL)
//list of possible states
#define STATE_ON 1
#define STATE_OFF 2
#define STATE_UNINIT 0
//calcuate time spans
#define ON_SPAN (MILLIS_IN_HOUR * HOURS_ON)
#define OFF_SPAN (MILLIS_IN_HOUR * HOURS_OFF)

volatile unsigned long offset_lastTime;
volatile unsigned int system_state = STATE_UNINIT;
volatile unsigned long millis_elapsed = 0;

void setup() {
  //setup output
  pinMode(EnablePIN, OUTPUT);
  //start in uninit state
  system_state = STATE_UNINIT;
}

void loop() {

  millis_elapsed = (unsigned long)(millis() - offset_lastTime);

  switch(system_state)
  {
    case STATE_ON :      
      if(millis_elapsed >= (unsigned long)ON_SPAN)
      {
        system_state = STATE_OFF;
        offset_lastTime = millis();
        digitalWrite(EnablePIN, LOW);
      }
    break;
    case STATE_OFF :
      if(millis_elapsed >= (unsigned long)OFF_SPAN)
      {
        system_state = STATE_ON;
        offset_lastTime = millis();
        digitalWrite(EnablePIN, HIGH);
      }
    break;
    default : //If we get lost or uninit, just turn on and restart
      system_state = STATE_ON;
      offset_lastTime = millis();
      digitalWrite(EnablePIN, HIGH);
    break;
  }
}
