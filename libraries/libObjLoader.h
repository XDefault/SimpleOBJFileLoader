#ifndef __LIBOBJLOADER_H__
#define __LIBOBJLOADER_H__

#include <stdio.h>
#include <string.h>
#include "..\libraries\libMeshFunctions.h"

struct stringListStruct{
    char data[256];
    int Lenght;
    struct stringListStruct *next;  
    struct stringListStruct *lastNode;
};

typedef struct stringListStruct stringList;

void AddToStringList(stringList *head_ref,char *new_string);
void GetStringDataFromIndex(stringList *head_ref,int index,char *out[]);

FILE *GetMeshFile(char filename[]);
void LoadOBJModel(FILE *modelFile,Mesh *mesh);

int CountAppearance(char *string,char c);

#endif