// ANUBIS projet code
// 8 steps sequencer
// 1 bar = 4 steps
// Steps LED must be connected to a PWM pin (between 2 and 13)

// Map all the input and output pins
#define AnalogInTempo         0
#define AnalogInDuration      1
#define AnalogInPitch1        2
#define AnalogInPitch2        3
#define AnalogInPitch3        4
#define AnalogInPitch4        5
#define AnalogInPitch5        6
#define AnalogInPitch6        7
#define AnalogInPitch7        8
#define AnalogInPitch8        9

#define DigitalInButton1      22
#define DigitalInButton2      24
#define DigitalInButton3      25
#define DigitalInButton4      26
#define DigitalInButton5      28
#define DigitalInButton6      30
#define DigitalInButton7      32
#define DigitalInButton8      34
#define DigitalInStartStop    36
#define DigitalInSpeakerMode  38
#define DigitalOutLEDStep1    2
#define DigitalOutLEDStep2    3
#define DigitalOutLEDStep3    4
#define DigitalOutLEDStep4    5
#define DigitalOutLEDStep5    6
#define DigitalOutLEDStep6    7
#define DigitalOutLEDStep7    8
#define DigitalOutLEDStep8    9
#define DigitalOutLEDPower    40
#define DigitalOutSignal      42

// Parameters
int tempo_min = 50; // [bpm] miminum tempo
int tempo_max = 200; // [bpm] maximum tempo
int minute_s = 60; // [s] 1 minute in seconds
int minute_ms = 60000; // [ms] 1 minute in milliseconds
int duration_min = 10; // [ms] minimum duration of a note
int duration_max = (minute_ms/tempo_max)/4; // [ms] maximum duration of a note (depends on the maximum admissible tempo)
int LEDLuminosity_off = 0; // Luminosity of the LED when the step is not activated
int LEDLuminosity_on = 103; // Luminosity of the LED when the step is activated
int LEDLuminosity_play = 255; // Luminosity of the LED when the step is being played
int LEDFlashingDelay = 500; // [ms] Delay between two flashes at the setup part 

// Global variables
int tempo = 100; // [bpm]
int duration = 50; // [ms]
int stepStatus[] = {1, 1, 1, 1, 1, 1, 1, 1};
int pitchVal[] = {1, 1, 1, 1, 1, 1, 1, 1};
int steps[] = {100,120,140,160,180,200,220,240};
int playMode = false;
int lastPushedStep = -1;


// Define useful functions
void LEDs_off() {
  analogWrite(DigitalOutLEDStep1, LEDLuminosity_off);
  analogWrite(DigitalOutLEDStep2, LEDLuminosity_off);
  analogWrite(DigitalOutLEDStep3, LEDLuminosity_off);
  analogWrite(DigitalOutLEDStep4, LEDLuminosity_off);
  analogWrite(DigitalOutLEDStep5, LEDLuminosity_off);
  analogWrite(DigitalOutLEDStep6, LEDLuminosity_off);
  analogWrite(DigitalOutLEDStep7, LEDLuminosity_off);
  analogWrite(DigitalOutLEDStep8, LEDLuminosity_off);
}
void LEDs_on() {
  analogWrite(DigitalOutLEDStep1, LEDLuminosity_on);
  analogWrite(DigitalOutLEDStep2, LEDLuminosity_on);
  analogWrite(DigitalOutLEDStep3, LEDLuminosity_on);
  analogWrite(DigitalOutLEDStep4, LEDLuminosity_on);
  analogWrite(DigitalOutLEDStep5, LEDLuminosity_on);
  analogWrite(DigitalOutLEDStep6, LEDLuminosity_on);
  analogWrite(DigitalOutLEDStep7, LEDLuminosity_on);
  analogWrite(DigitalOutLEDStep8, LEDLuminosity_on);
}
void LEDs_play() {
  analogWrite(DigitalOutLEDStep1, LEDLuminosity_play);
  analogWrite(DigitalOutLEDStep2, LEDLuminosity_play);
  analogWrite(DigitalOutLEDStep3, LEDLuminosity_play);
  analogWrite(DigitalOutLEDStep4, LEDLuminosity_play);
  analogWrite(DigitalOutLEDStep5, LEDLuminosity_play);
  analogWrite(DigitalOutLEDStep6, LEDLuminosity_play);
  analogWrite(DigitalOutLEDStep7, LEDLuminosity_play);
  analogWrite(DigitalOutLEDStep8, LEDLuminosity_play);
}

void setup() {
  
  // Setup pin modes
  pinMode(DigitalInButton1, INPUT);
  pinMode(DigitalInButton2, INPUT);
  pinMode(DigitalInButton3, INPUT);
  pinMode(DigitalInButton4, INPUT);
  pinMode(DigitalInButton5, INPUT);
  pinMode(DigitalInButton6, INPUT);
  pinMode(DigitalInButton7, INPUT);
  pinMode(DigitalInButton8, INPUT);  
  pinMode(DigitalInStartStop, INPUT);
  pinMode(DigitalInSpeakerMode, INPUT);
  pinMode(DigitalOutSignal, OUTPUT); 
  pinMode(DigitalOutLEDPower, OUTPUT);
  pinMode(DigitalOutLEDStep1, OUTPUT);
  pinMode(DigitalOutLEDStep2, OUTPUT);
  pinMode(DigitalOutLEDStep3, OUTPUT);
  pinMode(DigitalOutLEDStep4, OUTPUT);
  pinMode(DigitalOutLEDStep5, OUTPUT);
  pinMode(DigitalOutLEDStep6, OUTPUT);
  pinMode(DigitalOutLEDStep7, OUTPUT);
  pinMode(DigitalOutLEDStep8, OUTPUT);
  
  // Turn on the steps LEDs
  // 1
  LEDs_play();
  delay(LEDFlashingDelay);
  LEDs_off();
  delay(LEDFlashingDelay);
  // 2
  LEDs_play();
  delay(LEDFlashingDelay);
  LEDs_off();
  delay(LEDFlashingDelay);
  // 3
  LEDs_play();
  delay(LEDFlashingDelay);
  LEDs_on();
  delay(LEDFlashingDelay);
}


void loop() {
  
  // Loop over the 8 steps sequence 
  for (int i=0; i<8; i++) {
    
    // Check if the sequencer is running
    playMode = digitalRead(DigitalInStartStop);
    
    // Manage the Power LED 
    if (playMode) {
      digitalWrite(DigitalOutLEDPower, HIGH);  
    } else {
      digitalWrite(DigitalOutLEDPower, LOW);
    }
    
    // Read the pitch values
    readButtons();
    
    // Read the pots values
    readPots();

    // update the display
    updateDisplay();

    // Make the noise
    if (fPlayMode) {
      freqout(steps[i], duration);
    }
    
    // Pause between steps
    dt_step = (minute_ms/tempo)/4; // The 4 comes from the sequencer design: 1 bar equals to 4 steps 
    delay(dt_step);
    
  }
}

void updateDisplay() {
  
}

// Read the current values of the pots to determine tempo and duration
void readPots () {
  // Compute tempo value in bpm
  tempoPot = analogRead(AnalogInTempo)
  tempo = (tempoPot/1024) * (tempo_max-tempo_min) + tempo_min;
  
  // Compute duration value in ms
  durationPot = analogRead(AnalogInDuration)
  duration = (durationPot/1024) * (duration_max-duration_min) + duration_min;
  
  // Compute pitch values
  
}

// Read the current values of the switches and
// if pressed, replace the switch's slot frequency
// by reading the frequency pot.
void readButtons() {
  // If pressed, get the actual status of the step and change it 
  if (digitalRead(DigitalInButton1)==HIGH) {
    if (stepStatus[0]==1) {
      stepStatus[0] = -1;
    } else {
      stepStatus[0] = 1;
    }
  } else if (digitalRead(DigitalInButton2)==HIGH) {
    if (stepStatus[1]==1) {
      stepStatus[1] = -1;
    } else {
      stepStatus[1] = 1;
    }
  } else if (digitalRead(DigitalInButton3)==HIGH) {
    if (stepStatus[2]==1) {
      stepStatus[2] = -1;
    } else {
      stepStatus[2] = 1;
    }
  } else if (digitalRead(DigitalInButton4)==HIGH) {
    if (stepStatus[3]==1) {
      stepStatus[3] = -1;
    } else {
      stepStatus[3] = 1;
    }
  } else if (digitalRead(DigitalInButton5)==HIGH) {
    if (stepStatus[4]==1) {
      stepStatus[4] = -1;
    } else {
      stepStatus[4] = 1;
    }
  } else if (digitalRead(DigitalInButton6)==HIGH) {
    if (stepStatus[5]==1) {
      stepStatus[5] = -1;
    } else {
      stepStatus[5] = 1;
    }
  } else if (digitalRead(DigitalInButton7)==HIGH) {
    if (stepStatus[6]==1) {
      stepStatus[6] = -1;
    } else {
      stepStatus[6] = 1;
    }
  } else if (digitalRead(DigitalInButton8)==HIGH) {
    if (stepStatus[7]==1) {
      stepStatus[7] = -1;
    } else {
      stepStatus[7] = 1;
    }
  }
}


//freqout code by Paul Badger
// freq - frequency value
// t - time duration of tone
void freqout(int freq, int t) {
  int hperiod;     //calculate 1/2 period in us
  long cycles, i;

  // subtract 7 us to make up for digitalWrite overhead - determined empirically
  hperiod = (500000 / ((freq - 7) * pitchval));            

  // calculate cycles
  cycles = ((long)freq * (long)t) / 1000;    // calculate cycles
  for (i=0; i<= cycles; i++)
  {              // play note for t ms 
    digitalWrite(DigitalOutSignal, HIGH); 
    delayMicroseconds(hperiod);
    digitalWrite(DigitalOutSignal, LOW); 
    delayMicroseconds(hperiod - 1);     // - 1 to make up for fractional microsecond in digitaWrite overhead
  }
}
