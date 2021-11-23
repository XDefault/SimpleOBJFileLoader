#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL\GLU.h>
#include <stdbool.h>
#include <stdio.h>

#include "../libraries/libMeshFunctions.h"
#include "../libraries/libObjLoader.h"

SDL_Window *window = NULL;

int width,height;
char filepath[] = "build/monke.obj";
int ModelListID;

float angle = 0.0f;

int CreateModelList(char *path){    
    int num = 0;

    Mesh *modelMesh = CreateMeshObject();
    FILE *modelFile = GetMeshFile(path);

    if(modelMesh == NULL){
        SDL_Log("Error Creating Mesh");
        return -7;
    }

    if(modelFile == NULL){
        SDL_Log("Error Loading File");
        return -8;
    }

    LoadOBJModel(modelFile,modelMesh);

    num = glGenLists(1);
    glNewList(num,GL_COMPILE);
    DataFace *faceItem;
    DataCoord *normalItem;
    DataCoord *vertexItem1;
    DataCoord *vertexItem2;
    DataCoord *vertexItem3;
    DataCoord *vertexItem4;

    for(int i=0; i<modelMesh->Faces->Lenght;i++){
        faceItem = &modelMesh->Faces->data[i];
        normalItem = &modelMesh->Normals->data[faceItem->facenum -1];
        vertexItem1 = &modelMesh->Vertex->data[faceItem->faces[0] -1];
        vertexItem2 = &modelMesh->Vertex->data[faceItem->faces[1] -1];
        vertexItem3 = &modelMesh->Vertex->data[faceItem->faces[2] -1];
        vertexItem4 = &modelMesh->Vertex->data[faceItem->faces[3] -1];

        if(faceItem->haveFourFaces == 1){
            glBegin(GL_QUADS);
                glNormal3f(normalItem->dataX,normalItem->dataY,normalItem->dataZ);

                glVertex3f(vertexItem1->dataX,vertexItem1->dataY,vertexItem1->dataZ);
                glVertex3f(vertexItem2->dataX,vertexItem2->dataY,vertexItem2->dataZ);
                glVertex3f(vertexItem3->dataX,vertexItem3->dataY,vertexItem3->dataZ);
                glVertex3f(vertexItem4->dataX,vertexItem4->dataY,vertexItem4->dataZ);
            glEnd();
        }else{
            glBegin(GL_TRIANGLES);
                glNormal3f(normalItem->dataX,normalItem->dataY,normalItem->dataZ);

                glVertex3f(vertexItem1->dataX,vertexItem1->dataY,vertexItem1->dataZ);
                glVertex3f(vertexItem2->dataX,vertexItem2->dataY,vertexItem2->dataZ);
                glVertex3f(vertexItem3->dataX,vertexItem3->dataY,vertexItem3->dataZ);
            glEnd();
        }
    }

    glEndList();

    free(modelMesh->Vertex);
    free(modelMesh->Normals);
    free(modelMesh->Faces);
    free(modelMesh);

    return num;
}

void DrawBuffer(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //Draw Model to Buffer
    glLoadIdentity();
    float pos[] = {-3.0,0.0,0.0,0.0};
    glLightfv(GL_LIGHT0,GL_POSITION,pos);

    glTranslatef(0.0,0.0,-5.0);
    glRotatef(angle,0.0,0.5,1.0);
    glCallList(ModelListID);

    SDL_GL_SwapWindow(window);
}

bool initGL(){
    GLenum error = GL_NO_ERROR;

    glClearColor(0.f,0.f,0.f,1.f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90,1280 / 720,0.012,20);
    error = glGetError();

    if(error != GL_NO_ERROR){
        SDL_Log("Error initializing OpenGl!\n Error Details:\n %s\n",gluErrorString(error));
        return false;
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(error != GL_NO_ERROR){
        SDL_Log("Error initializing OpenGl!\n Error Details:\n %s\n",gluErrorString(error));
        return false;
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    float lcolor[] = {1.0,1.0,1.0,1.0};
    glLightfv(GL_LIGHT0,GL_DIFFUSE,lcolor);

    if(error != GL_NO_ERROR){
        SDL_Log("Error initializing OpenGl!\n Error Details:\n %s\n",gluErrorString(error));
        return false;
    }

    return true;
}


//The parameters in the main function cannot be omitted, or an error will be reported
int main(int arg, char *argv[])
{   
    if(arg > 1){
        *filepath = *argv[1];
    }

    //Init SDL Window
    int initWidth = 1280;
    int initHeight = 720;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,1);
    SDL_Log("Init 'main' OBJ Loader");

    window = SDL_CreateWindow("SDL2 OBJ Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, initWidth, initHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window){
        return -1;
    }

    SDL_GLContext gContext = SDL_GL_CreateContext(window);

    if(gContext == NULL){
        SDL_Log("glContext failed to be created!\n Error Details:\n %s\n",SDL_GetError());
        return -4;
    }

    if(SDL_GL_SetSwapInterval(1) < 0){
        SDL_Log("Warinig: Unable to set Vsync!\n Error Details:\n %s\n",SDL_GetError());
        return -5;
    }

    if(!initGL()){
        SDL_Log("Error at initGL\n");
        return -6;
    }

    SDL_GetWindowSize(window, &width,&height);
    if(width == 0){
        SDL_Log("SDL_GetWindowSize failed: No Value");
        return -3;
    }

    bool isRunning = true;
    SDL_Event event;

    ModelListID = CreateModelList(filepath);

    //Game Loop
    while (isRunning)
    {    
        SDL_PumpEvents();
        
        while(SDL_PollEvent(&event)){ 
            switch (event.type)
            {
                case SDL_QUIT:
                    isRunning = false;
                    break;

                case SDL_WINDOWEVENT:
                    if(event.window.event == SDL_WINDOWEVENT_RESIZED){
                        SDL_SetWindowSize(window,event.window.data1,event.window.data2); 
                        SDL_GetWindowSize(window, &width,&height);
                    }
                    break;

                default:
                    break;
            }
        }
        
        angle += 0.3f;
        if(angle > 360){
            angle -= 360;
        }

        DrawBuffer();
        
    }

    //Destroy everything and close program
    SDL_DestroyWindow(window);
    SDL_Quit();
    SDL_Log("'main' OBJ Loader Finished Successful");
    return 0;
}