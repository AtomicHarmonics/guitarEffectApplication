
#ifndef audioEffects_h
#define audioEffects_h

#define TABLE_SIZE   (512)
#ifndef PI
#define PI  (3.14159265)
#endif
#include  <stddef.h>
#include <math.h>
class audioEffects {
public:
    audioEffects();
    ~audioEffects();
    int returnFour();
    //Simple tremolo effect that just multiplies the input signal by a sine wave, has numOscPerSecond to control how 'fast' the osciliation effect is
    void tremoloEffect(float *inputBuffer, float *outputBuffer, size_t size, float numOscPerSecond, unsigned int sampleRate);
    float sine[TABLE_SIZE]; //table of sine values
    size_t tremoloCounter; //Counter variable for our tremoloEffect, it is to determine how far in the sine wave we are

    //adding new effects
    void tremoloEffect_2(float *inputBuffer, float *outputBuffer, size_t size, float freq, int depth);
    void distortEffect(float *inputBuffer, float *outputBuffer, size_t size, float thresh);
    void overdriveEffect(float *inputBuffer, float *outputBuffer, size_t size, float a);

};
#endif  
