
const int FREQ_BAND_COUNT = 2;
const int FREQ_BAND_LENGTH = 2;
const int MAX_FREQ_COUNT = 31;
const int MAX_FREQ_LENGTH = 4;
const int MAX_FILE_COUNT = 137;
const int MAX_FILE_LENGTH = 12;
const int MAX_PATH_LENGTH = 1 + FREQ_BAND_LENGTH + 1 + MAX_FREQ_LENGTH + 1 + MAX_FILE_LENGTH;

char cachedFilePaths[FREQ_BAND_COUNT][MAX_FREQ_COUNT][MAX_FILE_COUNT][MAX_PATH_LENGTH + 1];

void cacheAudioFilePaths() {  
  File root = SD.open("/FILES/");
  int freqBandCount = 0;
  while (true) { // FreqBandFolder =========================
    File freqBandFolder = root.openNextFile();
    
    if (!freqBandFolder) {
      break;
    }
    if (freqBandCount >= FREQ_BAND_COUNT) {
      Serial.print("Found more frequency-band-folders than expected!: ");
      Serial.println(freqBandFolder.name());
      break;
    }
    if (!freqBandFolder.isDirectory()) {
      Serial.print("FreqBandFolder was not a directory!: ");
      Serial.println(freqBandFolder.name());
      break;
    } 

    char currentFreqBand[FREQ_BAND_LENGTH + 1];
    strcpy(currentFreqBand, freqBandFolder.name());

    int freqCount = 0;
    while (true) { // FreqFolder =========================
      File freqFolder = freqBandFolder.openNextFile();

      if (!freqFolder) {
        break;
      }
      if (freqCount >= MAX_FREQ_COUNT) {
        Serial.println("Found more frequency-folders than expected!");
        break;
      }
      if (!freqFolder.isDirectory()) {
        Serial.print("FreqFolder was not a directory!: ");
        Serial.println(freqFolder.name());
        break;
      } 

      char currentFreq[MAX_FREQ_LENGTH + 1];
      strcpy(currentFreq, freqFolder.name());
  
      int fileCount = 0;
      while(true){ // Files =========================
        File file = freqFolder.openNextFile();
        
        if (!file) {
          break;
        }
        if (fileCount >= MAX_FILE_COUNT) {
          Serial.println("Found more files than expected!");
          break;
        }
        if (file.isDirectory()) {
          Serial.print("File was a directory!: ");
          Serial.println(file.name());
          break;
        } 

        char path[MAX_PATH_LENGTH + 1];
        strcpy(path, "/");
        strcat(path, currentFreqBand);
        strcat(path, "/");
        strcat(path, currentFreq);
        strcat(path, "/");
        strcat(path, file.name());
        strcpy(cachedFilePaths[freqBandCount][freqCount][fileCount], path);
        
        ++fileCount;
      } // End Files =========================  
    
      ++freqCount;
    } // End FreqFolder =========================
  
    ++freqBandCount; 
  } // End FreqBandFolder =========================

  for(int i = 0; i < FREQ_BAND_COUNT; i++){
    for(int j = 0; j < MAX_FREQ_COUNT; j++){
      for(int k = 0; k < MAX_FILE_COUNT; k++){
        if(cachedFilePaths[i][j][k][0] == 0){
          continue;
        }
        
        Serial.println(cachedFilePaths[i][j][k]);
      }
    }
  }
}

void printDirectory(File dir, int numTabs) {
   while(true) {

     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       //Serial.println("**nomorefiles**");
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
   }
}
