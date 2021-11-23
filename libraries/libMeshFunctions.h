#ifndef __LIBMESHFUNCTIONS_H__
#define __LIBMESHFUNCTIONS_H__

struct CoordData{
    float dataX;
    float dataY;
    float dataZ;
}coordData;

typedef struct CoordData DataCoord;

struct CoordStruct{
    int Lenght;
    DataCoord *data;
};

typedef struct CoordStruct Coord;

struct FaceData{
    int facenum;
    int haveFourFaces;
    int faces[4];
};

typedef struct FaceData DataFace;

struct FaceStruct{

    int Lenght;
    DataFace *data;
};

typedef struct FaceStruct Face;

struct MeshStruct{
    Coord *Vertex;
    Coord *Normals;
    Face *Faces;
};

typedef struct MeshStruct Mesh;

Coord *CreateCoordList();
void AppendToCoordList(Coord* head_ref,float new_x_data,float new_y_data,float new_z_data);
void PrintCoordList(Coord* node);

Face *CreateFaceList();
void AppendToFaceList(Face* head_ref, int facen,int FourFaces,int f1,int f2,int f3,int f4);
void PrintFaceList(Face* node);

Mesh *CreateMeshObject();
#endif