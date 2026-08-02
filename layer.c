#include "layer.h"



Layer layer_alloc(){
    Layer layer;

    layer.neurons = arr_alloc(sizeof(neuron));

    return layer;
}

void layer_add_neuron(Layer* layer, neuron* n)
{
    arr_push_back(&layer->neurons, n);
}

Array layer_forward(Layer* layer, Array Inputs)
{
    Array result = arr_alloc(sizeof(TYPE));
    for (uint i = 0; i < layer->neurons.size; i++){
        float n = neuron_forward(arr_index_item(&layer->neurons, i), Inputs);
        arr_push_back(&result, &n);
    }

    return result;
}