#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>
#include <play_sd_mp3.h>
#include "Utils.h"
#include "FreqBands.h"
#include "PotHandler.h"
#include "DirectoryHandler.h"

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  11
#define SDCARD_SCK_PIN   13

Bounce button0 = Bounce(0, 15);

AudioPlaySdMp3           mp3Player;
AudioOutputI2S           i2s1;
AudioConnection          patchCord1(mp3Player, 0, i2s1, 0);
AudioConnection          patchCord2(mp3Player, 1, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;

void setup() {  
  Serial.begin(9600);
  
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (true) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }

  pinMode(0, INPUT_PULLUP);

  File root = SD.open("/");
  printDirectory(root, 0);

  fillPotInputs((float)analogRead(A3));
  cacheAudioFilePaths();
  
  delay(1000);
}

void loop() {
  /*
  if (mp3Player.isPlaying() == false) {
    //char path[6 + MAX_PATH_LENGTH];
    //strcpy(path, "/FILES");
    //strcat(path, cachedFilePaths[0][0][0]);
    
    Serial.print("Playing: ");
    //Serial.println("/FILES/AM/580/720825.MP3");
    Serial.println("/TEST3.MP3");
        
    //playSdWav1.play(path);
    
    mp3Player.play("/TEST3.MP3");
    
    delay(100000); // wait for library to parse WAV info
  }
  
  return;
*/
  
  static bool isAM = false;
  
  button0.update();
  if(button0.fallingEdge()) {
    isAM = !isAM;
  }

  addToPotInputs((float)analogRead(A3));
  
  float potAverage = getAveragePotInput();
  int freq;
  if(isAM) {
    freq = lerp(AM_BAND_MIN, AM_BAND_MAX, potAverage);
  }
  else {
    freq = lerp(FM_BAND_MIN, FM_BAND_MAX, potAverage);
  }

/*
  for(int i = 0; i < MAX_FREQ_COUNT; ++i){
    if (isAM){
      Serial.print("AM, #");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(FREQUENCIES_AM[i]);    
    }
    else {
      Serial.print("FM, #");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(FREQUENCIES_FM[i]);   
    }  
  }
*/

  int lowerFreq = GetFrequencyIndex(freq, isAM, true);
  int higherFreq = GetFrequencyIndex(freq, isAM, false);

  float lowerFreqClarity = GetFrequencyClarity(freq, lowerFreq, higherFreq, true);
  float higherFreqClarity = GetFrequencyClarity(freq, lowerFreq, higherFreq, false);

  Serial.print(freq);
  Serial.print(", Lower Freq Index = ");
  Serial.print(lowerFreq);
  Serial.print(" (");
  Serial.print(lowerFreqClarity);
  Serial.print("), Higher Freq Index = ");
  Serial.print(higherFreq);
  Serial.print(" (");
  Serial.print(higherFreqClarity);
  Serial.println(")");
}
