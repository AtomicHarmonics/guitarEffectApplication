
#ifndef audioEffects_h
#define audioEffects_h

#define TABLE_SIZE   (512)
#ifndef M_PI
#define M_PI  (3.14159265)
#endif
#include  <stddef.h>
#include <math.h>
class audioEffects {
public:
    audioEffects();
    ~audioEffects();
    int returnFour();
    void tremoloEffect(float *inputBuffer, float *outputBuffer, size_t size);
    float sine[TABLE_SIZE];
    int counter;
};
#endif  
