#include "Util.h"


float randf(){
    return (float)rand() / RAND_MAX;
}


float sigmoidf(float x)
{
    return 1.f / (1.f + expf(-x));
}
