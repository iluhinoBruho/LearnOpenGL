#ifndef MODEL_H
#define MODEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <memory.h>
#include <pthread.h>

#include "shader.h"

#include <cglm/cglm.h>
#include <cglm/struct.h>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#define ERROR_CREATE_THREAD 500
#define ERROR_JOIN_THREAD   600
#define SUCCESS               0

struct vec{double x;double y;double z;};


struct thr_pack
{
    vec3* cubePos;
    mat4* model;
    pthread_mutex_t* mutex;
    pthread_cond_t* cond;
    int* counter;
    int numthreads;
    //struct Shader* shader;
    //GLint* modelLoc;
};


// wierd vec-field
struct vec field(float x_, float y_, double z_){
    struct vec res;
    res.x = (rand() % 11 - 5) / (x_ + y_) * z_;
    res.y = (rand() % 11 - 5) / (x_ + y_) * z_;
    res.z = (rand() % 11 - 5) / (x_ + y_) * z_;
    return res;
}

// Function to be completed by threads
void* thread_ex(void* pack){
    struct thr_pack* arg = (struct thr_pack*) pack;
    struct vec delta = field(*(arg->cubePos)[0], *(arg->cubePos)[1], *(arg->cubePos)[2]);

    (*(arg->cubePos))[0] += 0.01 * delta.x;
    (*(arg->cubePos))[1] += 0.01 * delta.y;
    (*(arg->cubePos))[2] += 0.01 * delta.z;
    
    //glm_mat4_identity(*(arg->model));
    //glm_translate(*(arg->model), *(arg->cubePos));

    // additional calculations
    mat4 calc;
    glm_mat4_identity(calc);
    glm_translate(calc, (*(arg->cubePos)));
    for(int j = 0; j < 2500*4; ++j){
        glm_mat4_transpose(calc);
        glm_translate(calc, (*(arg->cubePos)));
        glm_mat4_mul(calc, calc, calc);
    }

    pthread_mutex_lock(arg->mutex);
    (*(arg->counter))++;
    //printf("INC NUM COUNTER %d\n", *(arg->counter));
    if(*(arg->counter) == arg->numthreads){
        pthread_cond_broadcast(arg->cond);
    }
    pthread_mutex_unlock(arg->mutex);

    return 0;
}




#endif