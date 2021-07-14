const int POT_INPUT_CACHE_SIZE = 20; // higher value == more precise pots, but slower response

float potInputs[POT_INPUT_CACHE_SIZE];

void fillPotInputs(float f) {
    for(int i = 0; i < POT_INPUT_CACHE_SIZE - 1; ++i) {
      potInputs[i] = f;
    }
}

void addToPotInputs(float f) {
    for(int i = 0; i < POT_INPUT_CACHE_SIZE - 1; ++i) {
      potInputs[i] = potInputs[i + 1];
    }

    potInputs[POT_INPUT_CACHE_SIZE - 1] = f;
}


float getAveragePotInput() {
    float value;
    for(int i = 0; i < POT_INPUT_CACHE_SIZE; ++i) {
      value += potInputs[i];
    }

    return value / (float)POT_INPUT_CACHE_SIZE / 1023.0;
}
