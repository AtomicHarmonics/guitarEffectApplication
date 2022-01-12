#include "audioEffects.h"
#include <stdio.h>
#include <iostream>
#include <math.h>

int audioEffects::returnFour()
{
    return 4;
}

audioEffects::audioEffects()
{
    tremoloCounter = 0;
    for(int  i=0; i<TABLE_SIZE; i++ )
	{
		sine[i] = 0.2 * (float) sin( ((double)i/(double)TABLE_SIZE) * M_PI * 2. );
	}
}

audioEffects::~audioEffects()
{

}

void audioEffects::tremoloEffect(float *inputBuffer, float *outputBuffer, size_t size, float numOscPerSecond, unsigned int sampleRate)
{
    //TODO: VERIFY THAT NO DIVIDE BY ZERO ERRORS OCCUR!!!

    //In order for us to 'oscilate' the input signal n number of times per second, we need to 
    // divide the duration of desired oscilation (for example if we wanted 4 oscllations per second, this would be 0.25 seconds) by
    // the duration of the sine wave's period (our sine wave table size at this time is 512 samples, with a sample rate of 44100, this is 0.0116 seconds).
    // the division results in how much slower we need to traverse the sine wave table.
    float sineWaveDuration = (float)(1.0/sampleRate) * TABLE_SIZE;
    float oscDuration = 1.0/numOscPerSecond;

    int sineWaveDivisor =(int)(oscDuration/sineWaveDuration);
    for(int x = 0; x < size; x++)
    {
        //Multiply input buffer by sin wave, we also multiple 12.0 just for a volume increase, since it's fairly quiet without any extra multiplication
        outputBuffer[x] = 12.0 * inputBuffer[x] * sine[(tremoloCounter/sineWaveDivisor)%TABLE_SIZE];
        tremoloCounter += 1;
        //resetting our tremolo counter arbitrarily after 500000, to avoid overflows (technically we don't need this since tremoloCounter is an unsigned int...)
        if(tremoloCounter > 500000)
        {
            tremoloCounter = 0;
        }
    }
}

void audioEffects::tremoloEffect_2(float *inputBuffer, float *outputBuffer, size_t size, float numOscPerSecond, int depth)
{
    float a = depth/200;
    float offset = 1 - a;
    
    //on matlab, vector lfo is multiplied with input vector
    for(int i = 0; i < size; i++)
    {
        


    }

}



void audioEffects::distortEffect(float *inputBuffer, float *outputBuffer, size_t size, float thresh)
{
    for(int i = 0; i < size; i++)
    {
        if(inputBuffer[i] > thresh)
            outputBuffer[i] = thresh;
        else if(inputBuffer[i] < -thresh)
            outputBuffer[i] = -thresh;
        else
            outBuffer[i] = inputBuffer[i];

    }

}

void audioEffects::overdriveEffect(float *inputBuffer, float *outputBuffer, size_t size, float a)
{
    for(int i = 0; i < size; i++)
    {
        outputBuffer[i] = (2./M_PI) * atan(inputBuffer[i] * a); // double atan(double x)
    }

}



