#ifndef MODEL_H
#define MODEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <memory.h>
#include <pthread.h>

#include <cglm/cglm.h>
#include <cglm/struct.h>


struct vec{double x;double y;double z;};


// wierd vec-field
struct vec field(float x_, float y_, double z_){
    struct vec res;
    res.x = (rand() % 11 - 5) / (x_ + y_) * z_;
    res.y = (rand() % 11 - 5) / (x_ + y_) * z_;
    res.z = (rand() % 11 - 5) / (x_ + y_) * z_;
    return res;
}

// Function to be completed by threads
void* thread_ex(void* cubePosition){
    vec3* arg = (vec3*) cubePosition;
    //memcopy(arg, cubePosition, sizeof(vec3));
    struct vec delta = field((*arg)[0], (*arg)[1], (*arg)[2]);

    (*arg)[0] += 0.01 * delta.x;
    (*arg)[1] += 0.01 * delta.y;
    (*arg)[2] += 0.01 * delta.z;
    //for(int j = 0; j < 3; ++j){
    //    double m = (rand() % 10) - 4.5;  
    //}
    printf("doing\n");
    return 0;
}



#endif