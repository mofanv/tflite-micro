#include "darknet.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

extern void run_classifier(int argc, char **argv);


int main(int argc, char **argv)
{
    if(argc < 2){
        fprintf(stderr, "usage: %s <function>\n", argv[0]);
        return 0;
    }

    if (0 == strcmp(argv[1], "classifier")){
        run_classifier(argc, argv);
    } else
    {
        fprintf(stderr, "Not an option: %s\n", argv[1]);
    }
    return 0;
}

