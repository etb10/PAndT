#include "application.h"

SYSTEM_MODE(AUTOMATIC);

/* Output Definitions */
int reset2  = D7;
int state1 = D6;
int state2 = D5;
int state3 = D4;
int state4 = D3;

/* Sound Definitions */
int sound_array[]      = {reset2, state1, state2, state3, state4};
char* input_commands[] = {"reset", "state1", "state2", "state3", "state4"};
int sound_length_ms[]  = {1000000, 900, 900, 900, 3600};               // must update these to the specific lengths of sounds (in ms)
int sound_array_length = 5;
int input_commands_length = 5;

/* 
    Can set whether or not a repeat call to a currently running sound can be reset
    False = Allow Resetting Sound
    True  = Prevent Resetting Sound
*/
bool prevent_replay = false;

/* State Definitions */
char* state = "reset";
int last_played = reset2;

void setup() {
    //Serial.begin(115200);
    Particle.subscribe("transmitter_ECE364_Megaton", myHandler);
    // set up the array of sound outputs
    for(int i=0; i<sound_array_length; i++) {
      pinMode(sound_array[i], OUTPUT);
      digitalWrite(sound_array[i], HIGH); 
    }
    Serial.begin(9600);
}

void loop() {
  
}

/* Handler for publish events */
void myHandler(const char *event, const char *data) {
 // if there is data in the request
 // Particle.publish("testing", "Handler Event. State: " + String(state) + " Data: " + String(data));
 if (data) {
    // if the state is different than ours, change our state and make noise
    // if(strncmp(state, data, 6)!=0) {
      // Particle.publish("testing", "States were different. State: " + state + " Data: " + data);
      // state = (char*) data;
      // check against all input commands and if found, play a sound
      for(int i=0; i<input_commands_length; i++) {
          if(strcmp(input_commands[i], data) == 0) {
              playSound(sound_array[i], i);
          } 
      }
    // }
 }
}

/* 
playSound
inputs:
    port: number of port to be pulled down
    index: index in the array of sound ports. Used to pull the length of the sound.
function:
    Pulls all ports HIGH to turn them off. 
    Pull selected port LOW to play for selected amount of time
*/
void playSound(int port, int index) {
    // if this sound was just played, don't allow it to do anything
    if(last_played == port) {
      return;
    } else {
      last_played = port;
    }

    // write all signals down
    for(int i=0; i<sound_array_length; i++) {
        if(!prevent_replay && sound_array[i] == port) { // don't reset the signal for the given port
            // don't do anything because the sound was a repeat
        } else {
            // if(sound_array[i] == reset2) {
            //   digitalWrite(reset2, LOW); 
            //   delay(125);
            //   digitalWrite(reset2, HIGH);
            // } else {
              digitalWrite(sound_array[i], HIGH);
            // }
        }
    }
    // write the selected signals up
    digitalWrite(port, LOW); 
    delay(sound_length_ms[index]);
    digitalWrite(port, HIGH); 
}
