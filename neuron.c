#include "Util.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "neuron.h"


neuron neuron_alloc(size_t nWeights)
{
    neuron n;
    n.Weights = arr_alloc(sizeof(TYPE));

    TYPE placeHolder = 0.0f;

    for (uint i = 0; i < nWeights; i++){
        arr_push_back(&n.Weights, &placeHolder);
    }

    n.bias = 0;

    return n;
}

void neuron_rand(neuron* n){
    size_t nWeights = n->Weights.size;

    // Randomizing Weights
    for (uint i = 0; i < nWeights; i++){
        TYPE num = randf();
        memcpy(arr_index_item(&(n->Weights), i), &num, n->Weights.ItemSize);
    }

    n->bias = randf();
}

TYPE neuron_forward(neuron* n, Array Inputs){
    TYPE result = 0;
    assert(Inputs.size == n->Weights.size);

    for (uint i = 0; i < n->Weights.size; i++){
        TYPE* weight = arr_index_item(&n->Weights, i);
        TYPE* Input = arr_index_item(&Inputs, i);

        result += (*weight) * (*Input);
    }
    result += n->bias;
    return sigmoidf(result);
}