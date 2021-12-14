#include "audioEffects.h"
#include <stdio.h>
#include <iostream>
int audioEffects::returnFour()
{
    return 4;
}

audioEffects::audioEffects()
{
    counter = 0;
    for(int  i=0; i<TABLE_SIZE; i++ )
	{
		sine[i] = 0.2 * (float) sin( ((double)i/(double)TABLE_SIZE) * M_PI * 2. );
	}
}

audioEffects::~audioEffects()
{

}

void audioEffects::tremoloEffect(float *inputBuffer, float *outputBuffer, size_t size)
{
    for(int x = 0; x < size; x++)
    {
        outputBuffer[x] = 0.0;
        int maxCount = 1;
        volatile int opCount = 0;
        for(volatile int zx =  0; zx < maxCount; zx++)
        {
            outputBuffer[x] += (12.0/maxCount) * inputBuffer[x] * sine[(counter/22)%TABLE_SIZE];
        }
        counter += 1;
        if(counter > 500000)
        {
            counter = 0;
        }
    }
}
