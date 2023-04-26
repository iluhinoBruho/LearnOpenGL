#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <memory.h>
#include <pthread.h>

#define NUM_THREADS 300

// SOIL
#include "include/SOIL.h"

#include "shader.h"
#include "model.h"
//#include "camera.h"

#include <cglm/cglm.h>
#include <cglm/struct.h>
//#include <cglm/gtc/matrix_transform.h>
//#include <..inclide/GLM/gtc/type_ptr.hpp>


// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>



// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;


// The MAIN function, from here we start the application and run the game loop
int main()
{

    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();

    // Define the viewport dimensions
    glViewport(0, 0, WIDTH, HEIGHT);

    // Setup OpenGL options
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );


    // Build and compile our shader program
    struct Shader ourShader;
    initShader(&ourShader, "../shaders/default.vs", "../shaders/default.fs");


    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    // World space positions of our cubes
    /*
    vec3 cubePositions[] = {
        {0.0f,  0.0f,  0.0f},
        { 2.0f,  5.0f, -15.0f},
        {-1.5f, -2.2f, -2.5f},
        {-3.8f, -2.0f, -12.3f},
        { 2.4f, -0.4f, -3.5f},
        {-1.7f,  3.0f, -7.5f},
        { 1.3f, -2.0f, -2.5f},
        { 1.5f,  2.0f, -2.5f},
        { 1.5f,  0.2f, -1.5f},
        {-1.3f,  1.0f, -1.5f}
    };
    */


    // random numbers generator's seed
    srand(time(NULL));
    vec3 cubePositions[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS; ++i){
        for(int j = 0; j < 3; ++j)
            cubePositions[i][j] = (rand() % 20 - 10.0) * 0.5f;
    }

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // TexCoord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); // Unbind VAO


    // Load and create a texture 
    GLuint texture1;
    GLuint texture2;
    // ====================
    // Texture 1
    // ====================
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
    // Set our texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load, create texture and generate mipmaps
    int width, height;
    unsigned char* image = SOIL_load_image("../textures/container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
    // ===================
    // Texture 2
    // ===================
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // Set our texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load, create texture and generate mipmaps
    image = SOIL_load_image("../textures/awesomeface.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    
    // Counting frames for productivity test
    long long int cnt_frames = 0;
    long long int frames_x100 = 0;
    
    // Time mesurement
    clock_t start, end;
    start = clock();
    double cpu_time_used;

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        
        ++cnt_frames;
        //printf("%d", cnt_frames % 10);
        //printf("\n");
        if( cnt_frames % 100 == 0 ){
            ++frames_x100;
            cnt_frames = 0;
            printf("x100 frames > %d\n", frames_x100);

            if(frames_x100 % 10 == 0){
                end = clock();
                cpu_time_used = difftime(end, start) / CLOCKS_PER_SEC;
                printf("CPU TIME: %f\n", cpu_time_used);
                break;
            }
        }
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Bind Textures using texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture2"), 1); 

        // Activate shader
        UseShader(&ourShader);
        
        // Create transformations
        //mat4 model;
        mat4 view;
        mat4 projection;
        glm_mat4_identity(view);
        glm_mat4_identity(projection);

        //vec3 tmpvec1 = {5.0f, 1.0f, 0.0f};
        //glm_rotate(model, glm_rad((GLfloat)glfwGetTime() * 50.0f), tmpvec1);
        //vec3 tmpvec2 = ;
        glm_translate(view, (vec3){0.0f, 0.0f, -3.0f});
        glm_perspective(glm_rad(60.0f), (GLfloat)WIDTH/(GLfloat)HEIGHT, 1.0f, 100.0f, projection);
        

        // Get their uniform location
        GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
        GLint projLoc = glGetUniformLocation(ourShader.Program, "projection");

        // Pass them to the shaders
        //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view);
        // Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, projection); 


        pthread_t threads[NUM_THREADS];
        //pthread_mutex_t mutex[10];
        //pthread_cond_t cond[10];
        int status;
        struct thr_pack args[NUM_THREADS];
        int status_addr;
        int counter = 0;
        int numproc = 0;

        pthread_mutex_t mutex;
        pthread_cond_t cond;
        pthread_cond_init(&cond, NULL);
        pthread_mutex_init(&mutex, NULL);

        // Draw container
        glBindVertexArray(VAO);
        for (GLuint i = 0; i < NUM_THREADS; i++)
        {
            
            // Calculate the model matrix for each object and pass it to shader before drawing
            // tried to implement it in different threads
            // but got wrong frames generation - seems because of absence of broadcast
            // but after implementing of broadcast still get wrong frames generation
            mat4 model;
            
            
            args[i].cubePos = &cubePositions[i];
            args[i].model = &model;
            args[i].cond = &cond;
            args[i].mutex = &mutex;
            args[i].numthreads = NUM_THREADS;
            args[i].counter = &counter;


            status = pthread_create(&threads[i], NULL, thread_ex, (void*) &args[i]);
		    if (status != 0) {
			    printf("main error: can't create thread, status = %d\n", status);
			    exit(ERROR_CREATE_THREAD);
		    }
 
            
        }
        //printf("Main Message\n");
        pthread_mutex_lock(&mutex);
        while (counter < NUM_THREADS){
            pthread_cond_wait(&cond, &mutex);
        }
        pthread_mutex_unlock(&mutex);

        //pthread_cond_broadcast(&cond);
        for (int i = 0; i < NUM_THREADS; i++) {
            status = pthread_join(threads[i], (void**)&status_addr);
            if (status != 0) {
                printf("main error: can't join thread, status = %d\n", status);
                exit(ERROR_JOIN_THREAD);
            }

            glm_mat4_identity(*(args[i].model));
            glm_translate(*(args[i].model), cubePositions[i]);
            GLfloat angle = 20.0f * i;

             // Update the uniform brightness
            GLfloat timeValue = glfwGetTime();
            double tmp = sin( timeValue );
            GLfloat brightValue = 1; //(tmp / 2) + 0.5;

            SetFloat(&ourShader, brightValue, "brightness");
            
            //glm_rotate(model, glm_rad(angle), (vec3){1.0f, 0.3f, 0.5f});
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, *(args[i].model));
            glDrawArrays(GL_TRIANGLES, 0, 36);

        }

        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);

        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;

}   

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}



            // Calculate the model matrix for each object and pass it to shader before drawing
            //mat4 model;
            /*

            glm_mat4_identity(model);
            glm_translate(model, cubePositions[i]);
            GLfloat angle = 20.0f * i;

             // Update the uniform brightness
            GLfloat timeValue = glfwGetTime();
            double tmp = sin( timeValue );
            GLfloat brightValue = 1; //(tmp / 2) + 0.5;
        
            if(i%3 == 0){
                angle = (GLfloat)glfwGetTime() * 50.0f;
                brightValue = 1;
            }

            SetFloat(&ourShader, brightValue, "brightness");
            
            //glm_rotate(model, glm_rad(angle), (vec3){1.0f, 0.3f, 0.5f});
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            
            */