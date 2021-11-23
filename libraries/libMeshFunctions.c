#include "libMeshFunctions.h"
#include <stdlib.h>
#include <stdio.h>

Coord *CreateCoordList(){
    Coord* new_node = (Coord*) malloc(sizeof(Coord));
    if(new_node == NULL){
        printf("ERROR! Cannot create CoordList\n");
        exit(-1);
    }

    new_node->data = malloc(sizeof(DataCoord) * 2);
    if(new_node->data == NULL){
        printf("ERROR! Cannot alloc coord data\n");
        exit(-1);
    }

    new_node->Lenght = 0;
    
    return new_node;
}

void AppendToCoordList(Coord* head_ref,float new_x_data,float new_y_data,float new_z_data){

    if(head_ref == NULL){
        printf("ERROR! List Ref is NULL\n");
        exit(-4);
    }
    head_ref->Lenght += 1;

    head_ref->data = realloc(head_ref->data,sizeof(DataCoord) *  head_ref->Lenght);
    head_ref->data[head_ref->Lenght -1].dataX = new_x_data;
    head_ref->data[head_ref->Lenght -1].dataY = new_y_data;
    head_ref->data[head_ref->Lenght -1].dataZ = new_z_data;

    return;

}

void PrintCoordList(Coord* node){
    printf("____________________________\n");
    for(int i=0;i<node->Lenght;i++){
        DataCoord *data = &node->data[i];
        printf("|%.6f,%.6f,%.6f|\n",data->dataX,data->dataY,data->dataZ);
    }
    printf("|--------------------------|\n");
}

//#Face---------------------------------------------------------------------------------------

Face *CreateFaceList(){
    Face* new_node = (Face*) malloc(sizeof(Face));
    if(new_node == NULL){
        printf("ERROR! Cannot create CoordList\n");
        exit(-1);
    }

    new_node->data = malloc(sizeof(DataFace) * 2);
    if(new_node->data == NULL){
        printf("ERROR! Cannot alloc coord data\n");
        exit(-1);
    }

    new_node->Lenght = 0;
    return new_node;

}

void AppendToFaceList(Face* head_ref, int facen,int FourFaces,int f1,int f2,int f3,int f4){

    if(head_ref == NULL){
        printf("ERROR! List Ref is NULL\n");
        exit(-4);
    }
    head_ref->Lenght += 1;

    head_ref->data = realloc(head_ref->data,sizeof(DataFace) *  head_ref->Lenght);
    head_ref->data[head_ref->Lenght -1].facenum = facen;
    head_ref->data[head_ref->Lenght -1].faces[0] = f1;
    head_ref->data[head_ref->Lenght -1].faces[1] = f2;
    head_ref->data[head_ref->Lenght -1].faces[2] = f3;
    head_ref->data[head_ref->Lenght -1].faces[3] = f4;
    head_ref->data[head_ref->Lenght -1].haveFourFaces = FourFaces;
    return;
}

void PrintFaceList(Face* node){
    printf("_________\n");
    for(int i=0;i<node->Lenght;i++){
        DataFace *data = &node->data[i];
        printf("|%d,%d,%d,%d|\n",data->faces[0],data->faces[1],data->faces[2],data->faces[3]);
    }
    printf("|-------|\n");
}

Mesh *CreateMeshObject(){
    Mesh* newMesh = (Mesh*) malloc(sizeof(Mesh));
    if(newMesh == NULL){
        printf("ERROR! Cannot create MeshObject");
        exit(-1);
    }

    return newMesh;
}