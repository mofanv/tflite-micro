#include "darknet.h"

#include <sys/time.h>
#include <assert.h>

#include "input_datacfg.h"
#include "input_image.h"

matrix load_input(int n, int w, int h)
{
    int c = 1;
    matrix X;

    X.rows = n;
    X.cols = h*w*c;
    X.vals = calloc(X.rows, sizeof(float*));
    
    X.vals[0] = input_image1;
    X.vals[1] = input_image2;
    X.vals[2] = input_image3;
    X.vals[3] = input_image4;
    X.vals[4] = input_image5;
    X.vals[5] = input_image6;
    X.vals[6] = input_image7;
    X.vals[7] = input_image8;
    return X;
}

matrix load_label(int n, char **labels, int k)
{
    matrix y = make_matrix(n, k);

    y.vals[0] = input_label1;
    y.vals[1] = input_label2;
    y.vals[2] = input_label3;
    y.vals[3] = input_label4;
    y.vals[4] = input_label5;
    y.vals[5] = input_label6;
    y.vals[6] = input_label7;
    y.vals[7] = input_label8;
    return y;
}

void load_data_single_thread(load_args args)
{
    data *out = args.d;
    out->shallow = 0;
    out->X = load_input(args.n, args.w, args.h);
    out->y = load_label(args.n, args.labels, args.classes);
}


load_args set_args(network *net)
{
    load_args args = {0};

    args.w = net->w;
    args.h = net->h;
    args.hierarchy = net->hierarchy;

    args.min = net->min_ratio*net->w;
    args.max = net->max_ratio*net->w;

    args.angle = net->angle;
    args.aspect = net->aspect;
    args.exposure = net->exposure;
    args.saturation = net->saturation;
    args.hue = net->hue;
    args.size = net->w;
    args.n = net->batch;

    return args;
}


void train_classifier(char *cfgfile, char *weightfile)
{   
    // set base cfg and network parameters
    srand(time(0));

    float avg_loss = -1;
    char *base = basecfg(cfgfile);
    printf("%s\n", base);
    network **nets = calloc(1, sizeof(network*));

    // load into network based cfg and weights file
    int clear = 1;
    nets[0] = load_network(cfgfile, weightfile, clear);
    network *net = nets[0];
    char **labels = 0;

    load_args args = set_args(net);
    args.classes = classes_num;
    args.labels = labels;

    data buffer;
    args.d = &buffer;
    
    //repeat this part on the input data from the feature extractor
    // --- start ---
    for(int i=0; i<test_epoch; i++){

        load_data_single_thread(args);

        float loss = 0;
        loss = train_network(net, buffer);

        if(avg_loss == -1) avg_loss = loss;
        avg_loss = avg_loss*.9 + loss*.1;
        if(i % 100 ==0){
            printf("%d: %f, %f avg, %f rate, %llu images\n", i, loss, avg_loss, net->learning_rate, *net->seen);
        }
    }
    // --- end ---

    char buff[256];
    sprintf(buff, "%s/%s.weights", "cfg", base);
    save_weights(net, buff);

    free_network(net);
    free(base);
}


void predict_classifier(char *cfgfile, char *weightfile, int top)
{
    network *net = load_network(cfgfile, weightfile, 0);
    set_batch_network(net, 1);
    srand(2222222);

    char **names = label_list;
    
    clock_t time;
    int *indexes = calloc(top, sizeof(int));
    char *filename = "";
    char buff[256];
    char *input = buff;
    while(1){
        float *X = input_image1;
        time=clock();
        float *predictions = network_predict(net, X);
        top_k(predictions, net->outputs, top, indexes);
        fprintf(stderr, "%s: Predicted in %f seconds.\n", input, sec(clock()-time));
        for(int i = 0; i < top; ++i){
            int index = indexes[i];
            printf("%5.2f%%: %s\n", predictions[index]*100, names[index]);
        }
        if (filename) break;
    }
}



void run_classifier(int argc, char **argv)
{
    int top = 2;
    char *cfg = argv[3];
    char *weights = (argc > 4) ? argv[4] : 0;
    if(0==strcmp(argv[2], "predict")) predict_classifier(cfg, weights, top);
    else if(0==strcmp(argv[2], "train")) train_classifier(cfg, weights);
    else printf("Function does not supported.");
}