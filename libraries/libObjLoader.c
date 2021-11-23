#include "..\libraries\libObjLoader.h"
#include "..\libraries\libMeshFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

FILE *GetMeshFile(char filename[]){
    FILE *infile = fopen(filename,"r");

    if(infile == NULL){
        printf("ERROR! Could not open the file\n ERROR DETAILS:\n %s\n",strerror(errno));
        exit(-1);
    }
    
    return infile;
}

void LoadOBJModel(FILE *modelFile,Mesh *mesh){
    if(modelFile == NULL){
        printf("ERROR! File not passed to LoadModel()\n");
        exit(-1);
    }

    if(mesh == NULL){
        printf("ERROR! Mesh not created\n");
        exit(-3);
    }
    
    stringList *fileDataList = (stringList*)malloc(sizeof(stringList));
    fileDataList->lastNode = fileDataList;
    fileDataList->Lenght = 1;
    Coord *vertex = CreateCoordList();
    Coord *normals = CreateCoordList();
    Face *faces = CreateFaceList();

    char buf[256];
    memset(buf,0,256);
    while(fgets((char*)&buf,256,modelFile) != NULL){
        AddToStringList(fileDataList,buf);
    }
    
    char *listData = malloc(256 * sizeof(char));
    for(int i=0;i<fileDataList->Lenght;i++){
        GetStringDataFromIndex(fileDataList,i,&listData);

        if(listData[0] == '#'){
            //comments
            continue;
        }

        if(listData[0] == 'v' && listData[1] == ' '){
            //vertex

            float tempx,tempy,tempz;
            sscanf(listData,"v %f %f %f",&tempx,&tempy,&tempz);
            AppendToCoordList(vertex,tempx,tempy,tempz);
        }else if(listData[0] == 'v' && listData[1] == 'n'){
            //normals

            float tempx,tempy,tempz;
            sscanf(listData,"vn %f %f %f",&tempx,&tempy,&tempz);
            AppendToCoordList(normals,tempx,tempy,tempz);

        }else if (listData[0] == 'f'){
            //faces

            int facen,a,b,c,d = 0;

            if(CountAppearance(listData,' ') == 3){ //Check if face is a triagule
                sscanf(listData, "f %d//%d %d//%d %d//%d",&a,&facen,&b,&facen,&c,&facen);
                AppendToFaceList(faces,facen,0,a,b,c,d);
            }else{
                //Face is a Quad
                sscanf(listData, "f %d//%d %d//%d %d//%d %d//%d",&a,&facen,&b,&facen,&c,&facen,&d,&facen);
                AppendToFaceList(faces,facen,1,a,b,c,d);
            }


        }

    }

    mesh->Faces = faces;
    mesh->Normals = normals;
    mesh->Vertex = vertex;
    
    fclose(modelFile);
}


void AddToStringList(stringList *head_ref,char *new_string){
    stringList* new_node = (stringList*) malloc(sizeof(stringList));
    stringList* head = (stringList*)head_ref;
    stringList* currentNode = head_ref;

    size_t len = strlen(new_string);

    if(len > 256){
        len = 256;
    }

    strncpy(new_node->data,new_string,len);

    new_node->next = NULL;

    if(head_ref == NULL){
        printf("ERROR! StringList head reference is NULL\n EROOR DETAILS:\n%s\n",strerror(errno));
        return;
    }

    currentNode = head->lastNode;
    
    currentNode->next = new_node;
    currentNode->lastNode = new_node;
    head->lastNode = new_node;
    head->Lenght = head->Lenght +1;
    return;
}

void GetStringDataFromIndex(stringList *head_ref,int index,char *out[]){
    int i =0;
    stringList* list = head_ref;

    while(i < index){
        i++;
        list = list->next;
    }

    *out = list->data;
}

int CountAppearance(char *string,char c){
    int counter = 0;
    char check [256];
    memset(check,0,256);
    size_t len = strlen(string);

    strncpy(check,string,len);

    for (int i=0; i < len; i++){
        if(check[i] == c){
            counter++;
        }
    }

    return counter;
}