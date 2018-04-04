int sound7 = D7;
int sound6 = D6;
int sound5 = D5;

int sound_array[]      = {sound7, sound6, sound5};
char* input_commands[] = {"sound7", "sound6", "sound5"};
int sound_length_ms[]  = {1500, 900, 21000};               // must update these to the specific lengths of sounds (in ms)
int sound_array_length = 3;
int input_commands_length = 3;

/* 
    Can set whether or not a repeat call to a currently running sound can be reset
    False = Allow Resetting Sound
    True  = Prevent Resetting Sound
*/
bool prevent_replay = false;

/* Setup */
void setup() {

  Particle.subscribe("edwin_test",myHandler);
  
  // set up the array of sound outputs
  for(int i=0; i<sound_array_length; i++) {
    pinMode(sound_array[i], OUTPUT);
    digitalWrite(sound_array[i], HIGH); 
  }

  Serial.begin(9600);

}

/* Loop */
void loop() {
  
}

/* Handler for publish events */
void myHandler(const char *event, const char *data) {
 // if there is data in the request
 if (data) {
    // check against all input commands and if found, play a sound
    for(int i=0; i<input_commands_length; i++) {
        if(strcmp(input_commands[i], data) == 0) {
            playSound(sound_array[i], i);
        } 
    }
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
    // write all signals down
    for(int i=0; i<sound_array_length; i++) {
        if(!prevent_replay && sound_array[i] == port) { // don't reset the signal for the given port
            // don't do anything
        } else {
            digitalWrite(sound_array[i], HIGH);         
        }
    }
    // write the selected signals up
    digitalWrite(port, LOW); 
    delay(sound_length_ms[index]);
    digitalWrite(port, HIGH); 
}