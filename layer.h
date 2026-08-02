#ifndef LAYER_H
#define LAYER_H
#include "neuron.h"


typedef struct{
    Array neurons;
}Layer;

Layer layer_alloc();

void layer_add_neuron(Layer* layer, neuron* n);

Array layer_forward(Layer* layer, Array Inputs);


#endif // LAYER_H   