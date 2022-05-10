/*
 * 7.1 Midi OUT controller
 * roguescience.org
 *
 * digital pin 11 (OUTPUT/PWM) --> LED
 * digital pin 2 (INPUT) <-- button
 * analog pin 0 <-- pot
 * tx1 <-- pin 5 (5 PIN DIN aka MIDI jack)
 *
 * Send a MIDI note when the button is pressed and sends MIDI
 * CC data when a potentiometer is turned.
 */
 
int ledPin = 11;                //choose the pin for the LED - needs to be (3,5,6,9,10, or 11)
int buttonPin2 = 2;               //choose the input pin for a pushbutton
int buttonPin3 = 3;               //choose the input pin for a pushbutton
int buttonPin4 = 4;               //choose the input pin for a pushbutton
int buttonPin5 = 5;               //choose the input pin for a pushbutton
int buttonPin6 = 6;               //choose the input pin for a pushbutton
int buttonPin7 = 7;               //choose the input pin for a pushbutton
int buttonPin8 = 8;               //choose the input pin for a pushbutton
int buttonPin9 = 9;               //choose the input pin for a pushbutton
int buttonPin10 = 10;               //choose the input pin for a pushbutton
int buttonPin11 = 11;               //choose the input pin for a pushbutton
int buttonPin12 = 12;               //choose the input pin for a pushbutton
int buttonPin13 = 13;               //choose the input pin for a pushbutton
int potPin = 0;                  //choose the input pin for a potentometer
int buttonVal2 = 0;                    //variable for reading the button status
int buttonVal3 = 0;                    //variable for reading the button status
int buttonVal4 = 0;                    //variable for reading the button status
int buttonVal5 = 0;                    //variable for reading the button status
int buttonVal6 = 0;                    //variable for reading the button status
int buttonVal7 = 0;                    //variable for reading the button status
int buttonState2 = 0;            //variable to hold the buttons current state
int buttonState3 = 0;            //variable to hold the buttons current state
int buttonState4 = 0;            //variable to hold the buttons current state
int buttonState5 = 0;            //variable to hold the buttons current state
int buttonState6 = 0;            //variable to hold the buttons current state
int buttonState7 = 0;            //variable to hold the buttons current state
int bounceCheck2 = 0;            //variable for debouncing
int bounceCheck3 = 0;            //variable for debouncing
int bounceCheck4 = 0;            //variable for debouncing
int bounceCheck5 = 0;            //variable for debouncing
int bounceCheck6 = 0;            //variable for debouncing
int bounceCheck7 = 0;            //variable for debouncing
int delaymode = 1;               //variable for current delay on/off 1 = on
int reverbmode = 1;
int stompmode = 0;
int effectmode = 0;
int potVal = 0;                //variable for reading potentiometer value
int mappedPotVal = 0;          //variable for holding remapped pot value
int prevPotVal = 0;               //variable for storing our prev pot value
int THRESHOLD = 2;            //threshold amount
int current_vol = 0;        // variable to hold current volume for toggling
int current_reverb = 1;
int button_mode = 0;
 
void setup() {
  //pinMode(ledPin, OUTPUT);      //declare LED as output
  pinMode(buttonPin2, INPUT);     //declare pushbutton as input
  pinMode(buttonPin3, INPUT);     //declare pushbutton as input
  pinMode(buttonPin4, INPUT);     //declare pushbutton as input
  pinMode(buttonPin5, INPUT);     //declare pushbutton as input
  pinMode(buttonPin6, INPUT);     //declare pushbutton as input
  pinMode(buttonPin7, INPUT);     //declare pushbutton as input
  pinMode(buttonPin8, OUTPUT);     //declare pushbutton as input
  pinMode(buttonPin9, OUTPUT);     //declare pushbutton as input
  pinMode(buttonPin10, OUTPUT);     //declare pushbutton as input
  pinMode(buttonPin11, OUTPUT);     //declare pushbutton as input
  pinMode(buttonPin12, OUTPUT);     //declare pushbutton as input
  pinMode(buttonPin13, OUTPUT);     //declare pushbutton as input
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
   
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
  digitalWrite(12,LOW);
  digitalWrite(13,HIGH);
  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,HIGH);
  digitalWrite(A3,LOW);
  digitalWrite(A4,HIGH);
  
  Serial.begin(31250);            //MIDI communicates at 31250 baud
 
  // set volume to low
  Serial.write(0xB0); //CC
  Serial.write(0x24); //volume pedal
  Serial.write(0x3C); //60
  current_vol = 0;
  // Set program 00
  Serial.write(0xC0); // Program change
  Serial.write(0x00); //  00
   
   
}
 
void loop(){
 
  buttonVal2 = digitalRead(buttonPin2);     //read input value from button
  buttonVal3 = digitalRead(buttonPin3);     //read input value from button
  buttonVal4 = digitalRead(buttonPin4);     //read input value from button
  buttonVal5 = digitalRead(buttonPin5);     //read input value from button
  buttonVal6 = digitalRead(buttonPin6);     //read input value from button
  buttonVal7 = digitalRead(buttonPin7);     //read input value from button
  delay(10);                              //wait 10ms
  bounceCheck2 = digitalRead(buttonPin2);   //check again
  bounceCheck3 = digitalRead(buttonPin3);   //check again
  bounceCheck4 = digitalRead(buttonPin4);   //check again
  bounceCheck5 = digitalRead(buttonPin5);   //check again
  bounceCheck6 = digitalRead(buttonPin6);   //check again
  bounceCheck7 = digitalRead(buttonPin7);   //check again
 
  // Boost ----------------------------------------------------------------------------------------------
  if(buttonVal2 == bounceCheck2){           //if val is the same then not a bounce
     
    if(buttonVal2 == LOW && buttonState2 == 0){
      if(current_vol == 0){
         
        Serial.write(0xB0); //CC
        Serial.write(0x24); //volume pedal
        Serial.write(0x7F); //127
        buttonState2 = 1;
        current_vol = 1;
        digitalWrite(A4,LOW);
      }
      else {
         
        Serial.write(0xB0); //CC
        Serial.write(0x24); //volume pedal
        Serial.write(0x3C); //60
        buttonState2 = 1;
        current_vol = 0;
        digitalWrite(A4,HIGH);
      }
            
    }
    if (buttonVal2 == HIGH && buttonState2 == 1) {   //check if the input is HIGH
      buttonState2 = 0;
     }
  }
   // 6534 - Effect onoff------------------------------------------------------------------------------------------------
  if(buttonVal3 == bounceCheck3){           //if val is the same then not a bounce
     
    if(buttonVal3 == LOW && buttonState3 == 0){
      if(button_mode == 0){
          Serial.write(0xC0); // Program change
          Serial.write(0x00); //  00
          buttonState3 = 1;
          digitalWrite(13, HIGH);
          digitalWrite(A1, HIGH);
           
          digitalWrite(A3, LOW);
      }
      else{
          //Effect on/off
        Serial.write(0x90); //Note 
        Serial.write(0x0C); //Manual 
        Serial.write(0x7F); //127 (on)
        Serial.write(0x90); //Note 
        Serial.write(0x0C); //Manual 
        Serial.write(0x00); 
         
        Serial.write(0x90); //Note 
        Serial.write(0x04); //Effect 
        Serial.write(0x7F); //127 (on)
        Serial.write(0x90); //Note
        Serial.write(0x04); //Effect
        Serial.write(0x00);
 
        Serial.write(0x90); //Note 
        Serial.write(0x0C); //Manual 
        Serial.write(0x7F); //127 (on)
        Serial.write(0x90); //Note 
        Serial.write(0x0C); //Manual 
        Serial.write(0x00);
 
                if(effectmode == 1){
                      digitalWrite(A2, HIGH);
                      effectmode = 0;
                  }
                  else{
                      digitalWrite(A2, LOW);
                      effectmode = 1;
                  }
      }
         
       
      buttonState3 = 1;
    }
    if (buttonVal3 == HIGH && buttonState3 == 1) {   //check if the input is HIGH
      buttonState3 = 0;
     }
  }
  // clean - stomp ------------------------------------------------------------------------------------
  if(buttonVal4 == bounceCheck4){           //if val is the same then not a bounce
     
    if(buttonVal4 == LOW && buttonState4 == 0){
      if(button_mode == 0){
          Serial.write(0xC0);  // Program change
          Serial.write(0x02); // 02
          digitalWrite(A3, HIGH);
          digitalWrite(13, HIGH);
          digitalWrite(A1, LOW);
          digitalWrite(12, LOW);
          digitalWrite(10, LOW);
      }
      else{
        //stomp on/off
        Serial.write(0x90); //Note 
        Serial.write(0x0C); //Manual 
        Serial.write(0x7F); //127 (on)
        Serial.write(0x90); //Note 
        Serial.write(0x0C); //Manual 
        Serial.write(0x00); 
         
        Serial.write(0x90); //Note 
        Serial.write(0x05); //Stomp 
        Serial.write(0x7F); //127 (on)
        Serial.write(0x90); //Note
        Serial.write(0x05); //Stomp
        Serial.write(0x00);
 
        Serial.write(0x90); //Note 
        Serial.write(0x0C); //Manual 
        Serial.write(0x7F); //127 (on)
        Serial.write(0x90); //Note 
        Serial.write(0x0C); //Manual 
        Serial.write(0x00);
 
                if(stompmode == 1){
                      digitalWrite(A0, HIGH);
                      stompmode = 0;
                  }
                  else{
                      digitalWrite(A0, LOW);
                      stompmode = 1;
                  }
      }
      buttonState4 = 1;
    }
    if (buttonVal4 == HIGH && buttonState4 == 1) {   //check if the input is HIGH
      buttonState4 = 0;
     }
  }
  // B-4 Skynyrd---------------------------------------------------------------------------------------
  if(buttonVal5 == bounceCheck5){           //if val is the same then not a bounce
     
    if(buttonVal5 == LOW && buttonState5 == 0){
          if (button_mode == 0){
              // change to skynyrd
              Serial.write(0xC0);  // Program change
              Serial.write(0x07); // 07
              clearallpresets();
              digitalWrite(13,LOW);
          }
          else {
              //Delay on off
              Serial.write(0x90); //Note 
              Serial.write(0x0C); //Manual 
              Serial.write(0x7F); //127 (on)
              Serial.write(0x90); //Note 
              Serial.write(0x0C); //Manual 
              Serial.write(0x00); 
               
              Serial.write(0x90); //Note 
              Serial.write(0x09); //Delay 
              Serial.write(0x7F); //127 (on)
              Serial.write(0x90); //Note
              Serial.write(0x09); //Delay
              Serial.write(0x00);
     
              Serial.write(0x90); //Note 
              Serial.write(0x0C); //Manual 
              Serial.write(0x7F); //127 (on)
              Serial.write(0x90); //Note 
              Serial.write(0x0C); //Manual 
              Serial.write(0x00); 
 
                  if(delaymode == 1){
                      digitalWrite(12, HIGH);
                      delaymode = 0;
                  }
                  else{
                      digitalWrite(12, LOW);
                      delaymode = 1;
                  }
              }
           
      buttonState5 = 1;
      }
       
     
    if (buttonVal5 == HIGH && buttonState5 == 1) {   //check if the input is HIGH
      buttonState5 = 0;
     }
  }
 
// Reverb-------------------------------------------------------------------------------------
  if(buttonVal6 == bounceCheck6){           //if val is the same then not a bounce
    if(buttonVal6 == LOW && buttonState6 == 0){
        if (button_mode == 0){
          // clean
          Serial.write(0xC0);  // Program change
          Serial.write(0x02); // 02
          clearallpresets();
          digitalWrite(A1,LOW);
        }
        else{
          //reverb on off
          Serial.write(0x90); //Note 
          Serial.write(0x0C); //Manual 
          Serial.write(0x7F); //127 (on)
          Serial.write(0x90); //Note 
          Serial.write(0x0C); //Manual 
          Serial.write(0x00); 
           
          Serial.write(0x90); //Note 
          Serial.write(0x07); //Reverb 
          Serial.write(0x7F); //127 (on)
          Serial.write(0x90); //Note
          Serial.write(0x07); //Reverb
          Serial.write(0x00);
 
          Serial.write(0x90); //Note 
          Serial.write(0x0C); //Manual 
          Serial.write(0x7F); //127 (on)
          Serial.write(0x90); //Note 
          Serial.write(0x0C); //Manual 
          Serial.write(0x00); 
 
          if(reverbmode == 1){
                      digitalWrite(10, HIGH);
                      reverbmode = 0;
                  }
                  else{
                      digitalWrite(10, LOW);
                      reverbmode = 1;
                  }
        }          
        buttonState6 = 1;
    }
     
    if (buttonVal6 == HIGH && buttonState6 == 1) {   //check if the input is HIGH
      buttonState6 = 0;
     }
  }
   
  //Button mode switch--------------------------------------------------------------------------------
  if(buttonVal7 == bounceCheck7){           //if val is the same then not a bounce
    if(buttonVal7 == LOW && buttonState7 == 0){
          if(button_mode == 0){
              button_mode = 1;
              digitalWrite(9, LOW);
              digitalWrite(8, HIGH);
               
          }
           
          else{
            button_mode = 0; 
            digitalWrite(8, LOW);
            digitalWrite(9, HIGH);
          }
                     
          buttonState7 = 1;
    }
     
    if (buttonVal7 == HIGH && buttonState7 == 1) {   //check if the input is HIGH
      buttonState7 = 0;
     }
  }
    
 
}
int clearallpresets(){
    digitalWrite(13,HIGH);
    digitalWrite(A1,HIGH);
    digitalWrite(A3,HIGH);
}
