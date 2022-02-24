// TDMtoOBJ.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <cstdio>
#include <io.h>
#include <string>
#include "tdmm.h"

class VECTORobj : VECTOR
{
public:
    std::string toString()
    {
        std::string a;
        a = doubleToString(x);
        a += " ";
        a += doubleToString(y);
        a += " ";
        a += doubleToString(z);
        return a;
    }
    std::string toString2d()
    {
        std::string a;
        a = doubleToString(y);
        a += " ";
        a += doubleToString(x);
        return a;
    }

    void getInfInFa(VECTOR a)
    {
        x = a.x;
        y = a.y;
        z = a.z;
    }

};

int getMinSquare(int size)
{
    for (int i = 1; i <= 100; i++)
    {
        if ((i * i) >= size)
        return i;
    }
    return -1;
}

class FaceNodeObj {
public:
    int node3dNum;
    int node2dNum;
    int normalNodeNum;
    FaceNodeObj(int node3d, int node2d, int nodeNormal)
    {
        node3dNum = node3d;
        node2dNum = node2d;
        normalNodeNum = nodeNormal;
    }
    FaceNodeObj()
    {
        node3dNum = 0;
        node2dNum = 0;
        normalNodeNum = 0;
    }
    std::string toString()
    {
        std::string a;
        a = std::to_string(node3dNum+1);
        a += "/";
        a += std::to_string(node2dNum+1);
        a += "/";
        a += std::to_string(normalNodeNum+1);
        return a;
    }
};

class TriFaceObj {
public:
    FaceNodeObj Nodes[3];
};

class OBJ {
public:
    std::string name;
    VECTORobj* node3dLine;
    int totNode3d;
    VECTORobj* node2dLine;
    int totNode2d;
    VECTORobj* nodeNormalLine;
    int totNodeNormal;
    TriFaceObj* faceLine;
    int totFaces;
    OBJ(std::string _name, int _totNode3d, int _totNode2d,int _totNodeNormal,int _totface)
    {
        name = _name;
        totNode3d = _totNode3d;
        totNode2d = _totNode2d;
        totNodeNormal = _totNodeNormal;
        totFaces = _totface;
        node3dLine = (VECTORobj*) malloc(sizeof(VECTORobj) * totNode3d);
        node2dLine = (VECTORobj*) malloc(sizeof(VECTORobj) * totNode2d);
        nodeNormalLine = (VECTORobj*)malloc(sizeof(VECTORobj) * totNodeNormal);
        faceLine = (TriFaceObj*)malloc(sizeof(TriFaceObj) * totFaces);
    }

    std::string toString()
    {
        std::string ans;
        ans = "#3d Material Mesh\n#www.baidu.com\n";
        ans += "mtllib ";
        ans += name;
        ans += ".mtl\n";
        ans += "o Cube_Cube.001\n";
        for (int i = 0; i < totNode3d; i++)
        {
            ans += "v ";
            ans += node3dLine[i].toString();
            ans += "\n";
        }
        for (int i = 0; i < totNode2d; i++)
        {
            ans += "vt ";
            ans += node2dLine[i].toString2d();
            ans += "\n";
        }
        for (int i = 0; i < totNodeNormal; i++)
        {
            ans += "vn ";
            ans += nodeNormalLine[i].toString();
            ans += "\n";
        }
        ans += "usemtl Material.001\ns off";
        for (int i = 0; i < totFaces; i++)
        {
            ans += "\nf ";
            ans += faceLine[i].Nodes[0].toString();
            ans += " ";
            ans += faceLine[i].Nodes[1].toString();
            ans += " ";
            ans += faceLine[i].Nodes[2].toString();
        }
        return ans;

    }

    void writeFile(std::string name)
    {
        std::ofstream _fileOut(name.c_str());
        if (!_fileOut)
        {
            _log(0, "open " + name + " failed");
            return;
        }
        std::string lsa = toString();
        _fileOut << lsa;
        _fileOut.close();
    }

};

OBJ tdmToObj(std::string name,TdmMesh a)
{
    OBJ b = OBJ(name, a.mesh.totNode, a.mesh.totTriFace * 3, a.mesh.totTriFace*2 , a.mesh.totTriFace*2);
    for (int i = 0; i < a.mesh.totNode; i++)
    {
        b.node3dLine[i].getInfInFa(a.mesh.nodeLine[i].Pos);
    }
    for (int i = 0; i < a.mesh.totTriFace; i++)
    {
        b.nodeNormalLine[i].getInfInFa(a.mesh.getNormal(i));
        b.nodeNormalLine[i + a.mesh.totTriFace].getInfInFa(a.mesh.getNormal(i).r_scale(-1.0));

        b.faceLine[i].Nodes[0].node3dNum = a.mesh.triFaceLine[i].n1;
        b.faceLine[i].Nodes[1].node3dNum = a.mesh.triFaceLine[i].n2;
        b.faceLine[i].Nodes[2].node3dNum = a.mesh.triFaceLine[i].n3;
        b.faceLine[i].Nodes[0].normalNodeNum = i;
        b.faceLine[i].Nodes[1].normalNodeNum = i;
        b.faceLine[i].Nodes[2].normalNodeNum = i;
        
        b.faceLine[i+ a.mesh.totTriFace].Nodes[0].node3dNum = a.mesh.triFaceLine[i].n1;
        b.faceLine[i+ a.mesh.totTriFace].Nodes[1].node3dNum = a.mesh.triFaceLine[i].n2;
        b.faceLine[i+ a.mesh.totTriFace].Nodes[2].node3dNum = a.mesh.triFaceLine[i].n3;
        b.faceLine[i+ a.mesh.totTriFace].Nodes[0].normalNodeNum = i+ a.mesh.totTriFace;
        b.faceLine[i+ a.mesh.totTriFace].Nodes[1].normalNodeNum = i+ a.mesh.totTriFace;
        b.faceLine[i+ a.mesh.totTriFace].Nodes[2].normalNodeNum = i+ a.mesh.totTriFace;
    }
    int squareX = getMinSquare((a.mesh.totTriFace/2)+ (a.mesh.totTriFace % 2));
    if (squareX == -1)_log(0, "bad square size");
    Image out = Image();
    out.sizeX = out.sizeY = 512;
    int offsetx = out.sizeX / squareX;
    double offsetDou = ((double)offsetx) / (out.sizeX);
    int cnt = 0;
    for (int i = 0; i < squareX; i++)
    {
        for (int j = 0; j < squareX; j++)
        {
            b.node2dLine[cnt].getInfInFa(makeVector(offsetDou * (double)i, offsetDou * (double)j, 0));
            b.node2dLine[cnt + a.mesh.totTriFace].getInfInFa(makeVector(offsetDou * ((double)i+1), (double)j* offsetDou, 0));
            b.node2dLine[cnt + 2 * a.mesh.totTriFace].getInfInFa(makeVector(((double)i + 1) * offsetDou, ((double)j + 1) * offsetDou, 0));

            b.faceLine[cnt].Nodes[0].node2dNum = cnt;
            b.faceLine[cnt].Nodes[1].node2dNum = cnt + a.mesh.totTriFace;
            b.faceLine[cnt].Nodes[2].node2dNum = cnt + 2 * a.mesh.totTriFace;

            b.faceLine[cnt+a.mesh.totTriFace].Nodes[0].node2dNum = cnt;
            b.faceLine[cnt+a.mesh.totTriFace].Nodes[1].node2dNum = cnt + a.mesh.totTriFace;
            b.faceLine[cnt+a.mesh.totTriFace].Nodes[2].node2dNum = cnt + 2 * a.mesh.totTriFace;

            out = a.drawFaceOnImage(i * offsetx, j * offsetx, offsetx, cnt, out);

            cnt++;
            if (cnt == a.mesh.totTriFace)break;
        }
        if (cnt == a.mesh.totTriFace)break;
    }
    rdBMWriteImage((char*)(name + ".bmp").c_str(), out);
    
    return b;
}

void writeMaterial(std::string name)
{
    std::string a = "# Material Count: 1\nnewmtl Material.001\nNs 225.000000\nKa 1.000000 1.000000 1.000000\nKd 0.800000 0.800000 0.800000\nKs 0.000000 0.000000 0.000000\nKe 0.000000 0.000000 0.000000\nNi 1.450000\nd 1.00000\nillum 2";
    a += "\nmap_Kd ";
    a += (name+".bmp");
    std::ofstream _fileOut((name+".mtl").c_str());
    if (!_fileOut)
    {
        _log(0, "open " + name + " failed");
        return;
    }
    _fileOut << a;
    _fileOut.close();
}

int main(int argc,char * argv[])
{/*
    OBJ a = OBJ("tet", 3, 4, 5, 4);
    std::cout << a.toString();
 */   
    if (argc != 2)
    {
        _log(0,"wrong file num");
        return 0;
    }
    TdmMesh a = TdmMesh();
    a.fromFile(argv[1]);
    OBJ b = tdmToObj("out", a);
    b.writeFile("out.obj");
    writeMaterial("out");
    return 0;


}

