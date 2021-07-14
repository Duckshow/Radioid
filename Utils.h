float lerp(float val1, float val2, float t) {
     return val1 * (1 - t) + val2 * t;
} 

float InvLerp(float a, float b, float v){
    return (v - a) / (b - a);
}
