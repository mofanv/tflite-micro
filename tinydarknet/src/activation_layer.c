#include "activation_layer.h"
#include "utils.h"
#include "blas.h"
#include "gemm.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_activation_string(ACTIVATION a)
{
    switch(a){
        case RELU:
            return "relu";
        case LINEAR:
            return "linear";
        case TANH:
            return "tanh";
        case LEAKY:
            return "leaky";
        default:
            break;
    }
    return "relu";
}

ACTIVATION get_activation(char *s)
{
    if (strcmp(s, "relu")==0) return RELU;
    if (strcmp(s, "linear")==0) return LINEAR;
    if (strcmp(s, "leaky")==0) return LEAKY;
    if (strcmp(s, "tanh")==0) return TANH;
    fprintf(stderr, "Couldn't find activation function %s, going with ReLU\n", s);
    return RELU;
}

float activate(float x, ACTIVATION a)
{
    switch(a){
        case LINEAR:
            return linear_activate(x);
        case RELU:
            return relu_activate(x);
        case LEAKY:
            return leaky_activate(x);
        case TANH:
            return tanh_activate(x);
    }
    return 0;
}

void activate_array(float *x, const int n, const ACTIVATION a)
{
    int i;
    for(i = 0; i < n; ++i){
        x[i] = activate(x[i], a);
    }
}

float gradient(float x, ACTIVATION a)
{
    switch(a){
        case LINEAR:
            return linear_gradient(x);
        case RELU:
            return relu_gradient(x);
        case LEAKY:
            return leaky_gradient(x);
        case TANH:
            return tanh_gradient(x);
    }
    return 0;
}

void gradient_array(const float *x, const int n, const ACTIVATION a, float *delta)
{
    int i;
    for(i = 0; i < n; ++i){
        delta[i] *= gradient(x[i], a);
    }
} 


layer make_activation_layer(int batch, int inputs, ACTIVATION activation)
{
    layer l = {0};
    l.type = ACTIVE;

    l.inputs = inputs;
    l.outputs = inputs;
    l.batch=batch;

    l.output = calloc(batch*inputs, sizeof(float*));
    l.delta = calloc(batch*inputs, sizeof(float*));

    l.forward = forward_activation_layer;
    l.backward = backward_activation_layer;

    l.activation = activation;
    fprintf(stderr, "Activation Layer: %d inputs\n", inputs);
    return l;
}

void forward_activation_layer(layer l, network net)
{
    copy_cpu(l.outputs*l.batch, net.input, 1, l.output, 1);
    activate_array(l.output, l.outputs*l.batch, l.activation);
}

void backward_activation_layer(layer l, network net)
{
    gradient_array(l.output, l.outputs*l.batch, l.activation, l.delta);
    copy_cpu(l.outputs*l.batch, l.delta, 1, net.delta, 1);
}