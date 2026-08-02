#include <stdio.h>
#include "layer.h"

#include <time.h>
// xor
float train[][3] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 0},
};

#define train_count sizeof(train)/sizeof(train[0])


Array model_alloc(){

    Array layers = arr_alloc(sizeof(Layer));

    neuron n1 = neuron_alloc(2);
    neuron_rand(&n1);

    Layer layer1 = layer_alloc();
    Layer layer2 = layer_alloc();
    Layer layer3 = layer_alloc();


    
    neuron n2 = neuron_alloc(2);
    neuron_rand(&n2);

    neuron n3 = neuron_alloc(2);
    neuron_rand(&n3);

    neuron n4 = neuron_alloc(2);
    neuron_rand(&n4);

    neuron n5 = neuron_alloc(2);
    neuron_rand(&n5);

    layer_add_neuron(&layer3, &n5);


    layer_add_neuron(&layer2, &n4);

    layer_add_neuron(&layer2, &n3);


    layer_add_neuron(&layer1, &n2);



    

    layer_add_neuron(&layer1, &n1);

    arr_push_back(&layers, &layer1);
    arr_push_back(&layers, &layer2);
    arr_push_back(&layers, &layer3);



    return layers;
}


float forward(Array m, float x1, float x2){
    Array Inputs = arr_alloc(sizeof(TYPE));
    arr_push_back(&Inputs, &x1);
    arr_push_back(&Inputs, &x2);

    for (uint i = 0; i < m.size; i++){
        Layer* layer = arr_index_item(&m, i);
        Inputs = layer_forward(arr_index_item(&m, i), Inputs);
    }

    return *((float* )arr_index_item(&Inputs, 0));
}

float cost(Array m){
    float result = 0;
    uint n = train_count;
    for (uint i = 0; i < train_count; i++){
        float y = train[i][2];
        float expectedy = forward(m, train[i][0], train[i][1]);
        float d = expectedy - y;
        result += d*d;
    }

    result /= n;

    return result;
}


int main(){
    srand(time(0));
    Array layers = model_alloc();

    float eps = 1e-3;
    float rate = 1e-1;


    for (uint epoch = 0; epoch < 50*1000; epoch++){

        for (uint Nlayer = 0; Nlayer < layers.size; Nlayer++){
            Layer* layer = arr_index_item(&layers, Nlayer);

            for (uint Nneuron = 0; Nneuron < layer->neurons.size; Nneuron++){
                neuron* neuron = arr_index_item(&layer->neurons, Nneuron);
                for (uint weights = 0; weights < neuron->Weights.size; weights++){
                    TYPE* weight = arr_index_item(&neuron->Weights, weights);

                    TYPE originalValue = *weight;

                    TYPE originalCost = cost(layers);


                    *weight += eps;

                    TYPE newCost = cost(layers);

                    TYPE dw = (newCost - originalCost) / eps;
                    *weight = originalValue - rate * dw;

                }
                TYPE bias = neuron->bias;

                TYPE originalBias = bias;

                TYPE originalCost = cost(layers);

                bias += eps;

                TYPE newCost = cost(layers);

                TYPE db = (newCost - originalCost) / eps;
                neuron->bias = originalBias - rate * db; // Assign back directly

            }
        }
        printf("cost = %f\n", cost(layers));
    }

    while(1){
        size_t x1, x2;

        printf("Enter x1: ");
        scanf("%zu", &x1);

        printf("Enter x2: ");
        scanf("%zu", &x2);

        printf("%zu | %zu = %f\n", x1, x2, forward(layers, x1, x2));
    }



    return 0;
}