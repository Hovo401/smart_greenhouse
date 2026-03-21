
class Button {
private:
  unsigned char pin;
  // With INPUT_PULLUP: released = HIGH, pressed = LOW
  bool prevState = HIGH;
  unsigned long debounceDelay;
  unsigned char delay = 40;
  unsigned short int DelayBeforeRepeat = 500;
  unsigned long RepeatRateDelayDate;
public:
  static int newActivityCall ;
  Button(unsigned char buttonPin ) {
    pin = buttonPin;
    debounceDelay = millis();
    RepeatRateDelayDate = millis();
    pinMode(pin, INPUT_PULLUP);
  }

  bool isPressed(bool Repeat = true, unsigned char RepeatRateDelay = 80) {
    unsigned long date = millis();
    if(debounceDelay > date){
        debounceDelay = date;
    }
    bool reading = digitalRead(pin);
      
      if (reading != prevState) {
        if( debounceDelay + delay > date){
          return false;
        }
        prevState = reading;
        // trigger on physical press (LOW)
        if (reading == LOW) {
          debounceDelay = date;
          Button::newActivityCall ++ ;
          return true;
        }
      }else if(Repeat && (reading == LOW) && debounceDelay + DelayBeforeRepeat <= date){
        if(RepeatRateDelay > date){
          RepeatRateDelay = date;
        } 
        if(RepeatRateDelayDate + RepeatRateDelay <= date){
            RepeatRateDelayDate = date;
            Button::newActivityCall ++ ;
            return true;
        }
      }
    return false;
  }
};
int Button::newActivityCall = 0;