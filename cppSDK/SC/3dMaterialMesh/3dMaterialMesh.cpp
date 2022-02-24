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
    //TdmMesh a = TdmMesh();
    //a.fromFile("./po.tdm");
    //a.material.imgFile = "ea.bmp";
    //_log(2, a.toString());
    //a.toFile((std::string) "./po2.tdm");
    TdmMesh a = TdmMesh();
    a.fromFile("xl.tdm");
    
    std::cout << "size:" << a.material.img.sizeX << " " << a.material.img.sizeY << std::endl;
    std::cout << "extend type:" << a.material.extendType << std::endl;
    std::cout << "duration:" << a.material.deviation.toString() << std::endl;
    Colour ls = a.material.getColorAtPosition(makeVector(0.6, 0.4, 1.0));
    std::cout << "colour Get " << ls.R << " " << ls.G << " " << ls.B << std::endl;

    return 0;
    
    //std::cout << b.material.img.colourMap[2][2].B;
    //rdBMReadImage((char*)"./taseter.bmp");
}


