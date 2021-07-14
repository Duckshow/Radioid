const int AM_BAND_MIN = 550;
const int AM_BAND_MAX = 1720;
const int FM_BAND_MIN = 880;
const int FM_BAND_MAX = 1080;

const int AM_FREQ_COUNT = 24;
const int FM_FREQ_COUNT = 31;

const int AM_FREQUENCIES[] = {
    560,
    580,
    610,
    640,
    680,
    740,
    810,
    870,
    930,
    960,
    990,
    1010,
    1020,
    1050,
    1090,
    1110,
    1170,
    1260,
    1270,
    1310,
    1370,
    1580,
    1590,
    1600
};

const int FM_FREQUENCIES[] = {
    903,
    923,
    925,
    927,
    931,
    933,
    939,
    941,
    943,
    947,
    950,
    957,
    959,
    965,
    971,
    981,
    989,
    990,
    995,
    997,
    1003,
    1011,
    1013,
    1031,
    1037,
    1045,
    1053,
    1061,
    1065,
    1069,
    1077
};

const char CITIES_AM[][15] = {
    "San Francisco",
    "Tucson",
    "San Francisco",
    "Los Angeles",
    "San Francisco",
    "San Francisco",
    "San Francisco",
    "New Orleans",
    "Los Angeles",
    "Oakland",
    "Tucson",
    "San Francisco",
    "Los Angeles",
    "San Mateo",
    "Rosarito Beach",
    "Pasadena",
    "San José",
    "San Francisco",
    "Guntersville",
    "Oakland",
    "San José",
    "Santa Monica",
    "San José",
    "Riviera Beach"
};

const char CITIES_FM[][15] = {
    "San Francisco",
    "Los Angeles",
    "Oklahoma City",
    "Alameda",
    "San Francisco",
    "San Francisco",
    "Lake Tahoe",
    "Denver",
    "Garden Grove",
    "San Francisco",
    "San Francisco",
    "San Francisco",
    "Guntersville",
    "San Francisco",
    "Los Angeles",
    "San Francisco",
    "San Francisco",
    "San Francisco",
    "Birmingham",
    "San Francisco",
    "New York",
    "New York",
    "San Francisco",
    "San Francisco",
    "San Francisco", // unofficially, change to Truckee on March 12th 1978
    "San Francisco",
    "San Francisco",
    "San Francisco",
    "San José",
    "San Francisco",
    "San Francisco"
};

const char STATIONS_AM[][8] = {
    "KSFO",
    "KIKX",
    "KFRC",
    "KFI",
    "KNBR",
    "KCBS",
    "KGO",
    "WWL",
    "KHJ",
    "KNEW",
    "KTKT",
    "KIQI",
    "KTNQ",
    "KOFY",
    "XERB/XEPRS", // XERB, change to XEPRS on 01-01-1972
    "KRLA",
    "KLOK",
    "KYA/KXLR/KOIT", // KYA, change to KXLR in 1985, then KOIT in 1986
    "WGSV",
    "KDIA",
    "KEEN",
    "KDAY",
    "KLIV",
    "WHEW"
};

const char STATIONS_FM[][8] = {
    "KUSF",
    "KFAC",
    "KOMA",
    "KJAZ",
    "KCBS-FM",
    "KYA-FM",
    "KRLT",
    "KOA",
    "KIKF",
    "KTWV",
    "KSAN",
    "KPIX-FM",
    "WTWX",
    "KOIT",
    "KGBS",
    "KBGG",
    "KHIT/KOFY-FM/KDBK", // KHIT, change to KOFY-FM on May 14th 1988, then KDBK on July 31st 1990
    "KQAK",
    "WVOK-FM",
    "KYUU/KXXX/KFRC-FM", // KYUU, change to KXXX on March 1st 1991, then KFRC-FM on March 4th 1991
    "WHTZ",
    "WCBS-FM",
    "KIOI",
    "KKCY",
    "KGO-FM/KSFX/KLOK-FM", // KGO-FM, change to KSFX in 1971, (unofficially, change to KEZC on March 12th 1978), then KLOK-FM from 1984 onwards
    "KFOG",
    "KITS",
    "KFRC-FM/KMEL", // KFRC-FM, change to KMEL in 1978
    "KEZR",
    "KMPX",
    "KSOL"
};

int GetFreqBandMin(bool isAM) {
  if(isAM) {
    return AM_BAND_MIN;
  }
  else {
    return FM_BAND_MIN;
  }
}

int GetFreqBandMax(bool isAM) {
  if(isAM) {
    return AM_BAND_MAX;
  }
  else {
    return FM_BAND_MAX;
  }
}

int GetFreqCount(bool isAM) {
  if(isAM) {
    return AM_FREQ_COUNT;
  }
  else {
    return FM_FREQ_COUNT;
  }
}

int * GetFreqs(bool isAM) {
  if(isAM) {
    return AM_FREQUENCIES;
  }
  else {
    return FM_FREQUENCIES;
  }
}

int GetFreq(bool isAM, int index) {
  if(index == -1) { 
    return GetFreqBandMin(isAM); 
  }
  
  if(index == GetFreqCount(isAM)) { 
    return GetFreqBandMax(isAM);
  }
  
  return GetFreqs(isAM)[index];
}

int GetFrequencyIndex(int currentFreq, bool isAM, bool getLowerFreq){
  int freqCount = GetFreqCount(isAM);
  int *freqs = GetFreqs(isAM);

  for(int i = -1; i < freqCount; i++){
    int lowerFreqIndex  = i;
    int higherFreqIndex = i + 1;

    if(GetFreq(isAM, lowerFreqIndex) <= currentFreq && GetFreq(isAM, higherFreqIndex) >= currentFreq){
      return getLowerFreq ? lowerFreqIndex : higherFreqIndex;      
    }
  }

  return -1;
}

float GetFrequencyClarity(int currentFreq, int lowerFreq, int higherFreq, bool getLowerFreq){
  float clarity = InvLerp(lowerFreq, higherFreq, currentFreq);
  
  if(!getLowerFreq){
      clarity = 1.0 - clarity;
  }

  return clarity;
}
