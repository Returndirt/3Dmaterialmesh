// 3dMaterialMesh.cpp
//
#include "tdmm.h"


int main()
{
    /*
    TdmMesh a;
    a.header = Header(4, 4);
    a.mesh = Mesh(4, 4);
    a.mesh.nodeLine[0] = Node(0, 0, 0, 0);
    a.mesh.nodeLine[1] = Node(1, 1, 0, 0);
    a.mesh.nodeLine[2] = Node(2, 1, 0, 1);
    a.mesh.nodeLine[3] = Node(3, 1, 1, 1);
    a.mesh.triFaceLine[0] = TriangleFace(0, 0, 1, 2);
    a.mesh.triFaceLine[1] = TriangleFace(1, 0, 1, 3);
    a.mesh.triFaceLine[2] = TriangleFace(2, 0, 2, 3);
    a.mesh.triFaceLine[3] = TriangleFace(3, 1, 2, 3);
    a.material.imgFile = "taseter.bmp";
    */
    //std::string a = "4,4\n0.000000, 0.000000, 0.000000\n1.000000, 0.000000, 0.000000\n1.000000, 0.000000, 1.000000\n1.000000, 1.000000, 1.000000\n0, 1, 2\n0, 1, 3\n0, 2, 3\n1, 2, 3\ntaseter.bmp, 1, 1.000000, 1.000000, 1.000000";
    //TdmMesh b;
    //b.fromFile("./p1.tdm");
    //std::cout << b.mesh.nodeLine;
    //b.fromString(a);
    //b.toFile("./po.tdm");
    Image a = Image();
    a.sizeX = 13;
    a.sizeY = 13;
    a.colourMap[2][1] = Colour(255, 0, 0);
    rdBMWriteImage( (char *)"./test.bmp", a);

    
    //std::cout << b.material.img.colourMap[2][2].B;
    //rdBMReadImage((char*)"./taseter.bmp");
}


