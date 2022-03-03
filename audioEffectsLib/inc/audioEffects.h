#ifndef audioEffects_h
#define audioEffects_h
#include "reverbLib.h"
#define VERBLIB_IMPLEMENTATION
#include <math.h>
#define TABLE_SIZE   (512)
#ifndef PI
#define PI  (3.14159265)
#endif
#include  <stddef.h>

#include <math.h>
#include <json.hpp>
#include "readerwriterqueue.h"
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

using json = nlohmann::json;

typedef struct audioEffectsConfig
{
    bool tremoloEnabled;
    int tremoloOrderNumber;
    float tremoloFreq;
    int tremoloDepth;
    
    bool distortEnabled; 
    int distortOrderNumber;
    float distortThresh;
    
    bool overDriveEnabled;
    int overDriveOrderNumber;
    float overDriveThresh;
    
    bool reverbEnabled;
    int reverbOrderNumber;
    float reverbWetLevel;
    float reverbRoomSize;
    float reverbDryLevel;
    float reverbDampLevel;
    float reverbWidth;
    float reverbMode;
    
    bool bitcrusherEnabled;
    int bitcrusherOrderNumber;
    int bitcrusherDownSample;
    
    bool preAmpEnabled;
    float preAmpGain;
    
    bool bypassEnabled;

} audioEffectsConfig;


class audioEffects {
public:
    audioEffects();
    ~audioEffects();
    int returnFour();
    //Simple tremolo effect that just multiplies the input signal by a sine wave, has numOscPerSecond to control how 'fast' the osciliation effect is
    void tremoloEffect(float *inputBuffer, float *outputBuffer, size_t size, float numOscPerSecond, unsigned int sampleRate);
    float sine[TABLE_SIZE]; //table of sine values
    float scratchBuffer[2048];
    size_t tremoloCounter; //Counter variable for our tremoloEffect, it is to determine how far in the sine wave we are
    moodycamel::ReaderWriterQueue<audioEffectsConfig> *configQueue;
    audioEffectsConfig config;

    void process(float *inputBuffer, float *outputBuffer, size_t size);
    void recieveConfig(void);
    //adding new effects
    void tremoloEffect_2(float *inputBuffer, float *outputBuffer, size_t size, float freq, int depth);
    void distortEffect(float *inputBuffer, float *outputBuffer, size_t size, float thresh);
    void overdriveEffect(float *inputBuffer, float *outputBuffer, size_t size, float a);
   
    void reverbEffect(const float* inputBuffer, float* outputBuffer, unsigned long frames, unsigned int sampleRate, float WetLevel, float RoomSize, float DryLevel, float DampLevel, float Width, float Mode);
    verblib verb0;

    void bitcrusherEffect(float *inputBuffer, float *outputBuffer, size_t size, int DownSample);

    void preAmp(float *inputBuffer, float *outputBuffer, size_t size, float gain); 

};
#endif  
