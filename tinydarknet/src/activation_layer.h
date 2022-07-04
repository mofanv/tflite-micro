#ifndef ACTIVATION_LAYER_H
#define ACTIVATION_LAYER_H

#include "network.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ACTIVATION get_activation(char *s);

char *get_activation_string(ACTIVATION a);
float activate(float x, ACTIVATION a);
float gradient(float x, ACTIVATION a);
void gradient_array(const float *x, const int n, const ACTIVATION a, float *delta);
void activate_array(float *x, const int n, const ACTIVATION a);

static inline float linear_activate(float x){return x;}
static inline float relu_activate(float x){return x*(x>0);}
static inline float leaky_activate(float x){return (x>0) ? x : .1*x;}
static inline float tanh_activate(float x){return (exp(2*x)-1)/(exp(2*x)+1);}

static inline float linear_gradient(float x){return 1;}
static inline float relu_gradient(float x){return (x>0);}
static inline float leaky_gradient(float x){return (x>0) ? 1 : .1;}
static inline float tanh_gradient(float x){return 1-x*x;}

layer make_activation_layer(int batch, int inputs, ACTIVATION activation);

void forward_activation_layer(layer l, network net);
void backward_activation_layer(layer l, network net);

#endif

