#ifndef NEURON_H
#define NEURON_H
#include "Array.h"
#include "Util.h"

#define TYPE float

typedef struct
{
    Array Weights;
    TYPE bias;
}neuron;

neuron neuron_alloc(size_t nWeights);

void neuron_rand(neuron* n);

TYPE neuron_forward(neuron* n, Array Inputs);


#endif // NEURON_H   