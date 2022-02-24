#ifndef TDMM_H
#define TDMM_H

#include <iostream>
#include "rdcv.h"
#include <string>
#include <sstream>
#include <fstream>
#include "log.h"
#include <cmath>

std::string firstSplit(std::string fr,std::string su)
{
    for (int i = 1; i <= (fr.length()-su.length()); i++)
    {
        if (fr.substr(i, su.length()) == su)
        {
            return fr.substr(0, i);
        }
    }
    return fr;
}

int stringToInt(std::string a)
{
    int b;
    std::stringstream ss;
    ss.clear();
    ss << a;
    ss >> b;
    return b;
}

double stringToDouble(std::string a)
{
    double b;
    std::stringstream ss;
    ss.clear();
    ss << a;
    ss >> b;
    return b;
}

std::string doubleToString(double a)
{
    std::string b;
    std::stringstream ss;
    ss.clear();
    ss << a;
    ss >> b;
    return b;
}

struct VECTOR
{
    double x;
    double y;
    double z;
    void set(double _x, double _y, double _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
    
    double length()
    {
        return sqrt(x * x + y * y + z * z);
    }

    void normalize()
    {
        double _len = length();
        x = x / _len;
        y = y / _len;
        z = z / _len;
    }
    
    void scale(double a)
    {
        x = x * a;
        y = y * a;
        z = z * a;
    }

    void add(VECTOR a)
    {
        x = x + a.x;
        y = y + a.y;
        z = z + a.z;
    }

    double dot(VECTOR a)
    {
        double ans = 0;
        ans += x * a.x;
        ans += y * a.y;
        ans += z * a.z;
        return ans;
    }

    VECTOR r_add(VECTOR a)
    {
        VECTOR b;
        b.set(x, y, z);
        b.add(a);
        return b;
    }

    VECTOR r_scale(double sca)
    {
        VECTOR b;
        b.set(x, y, z);
        b.scale(sca);
        return b;
    }

    std::string toString()
    {
        std::string a = std::to_string(x);
        a = a + ",";
        a = a + std::to_string(y);
        a = a + ",";
        a = a + std::to_string(z);
        return a;
    }


};
VECTOR makeVector(double x, double y, double z)
{
    VECTOR a;
    a.set(x, y, z);
    return a;
}

class Node
{
public:
    VECTOR Pos;
    int cnt;
    Node()
    {
        cnt = 0;
        Pos = makeVector(0.0, 0.0, 0.0);
    }
    Node(int name, double _x, double _y, double _z)
    {
        cnt = name;
        Pos = makeVector(_x, _y, _z);
    }
};
/*
class Edge
{
    int from;
    int to;
    Edge(int _from, int _to)
    {
        from = _from;
        to = _to;
    }
};
*/
class TriangleFace
{
public:
    int n1, n2, n3;
    int cnt;
    TriangleFace()
    {
        n1 = n2 = n3 = cnt = 0;
    }
    TriangleFace(int _cnt, int _n1, int _n2, int _n3)
    {
        cnt = _cnt;
        n1 = _n1;
        n2 = _n2;
        n3 = _n3;
    }
    std::string toString()
    {
        std::string a = std::to_string(n1);
        a = a + ",";
        a = a + std::to_string(n2);
        a = a + ",";
        a = a + std::to_string(n3);
        return a;
    }
};

class Mesh
{
public:
    int totNode;
    Node * nodeLine;
    int totTriFace;
    TriangleFace * triFaceLine;
    Mesh(int _totNode, int _totTriFace)
    {
        totNode = _totNode;
        totTriFace = _totTriFace;
        nodeLine = (Node*)malloc(sizeof(Node) * 2048);
        triFaceLine = (TriangleFace*)malloc(sizeof(TriangleFace) * 2048);
        for (int i = 0; i < 2048; i++)
        {
            if (nodeLine != NULL)
            nodeLine[i] = Node(i, 0.0, 0.0, 0.0);
            if(triFaceLine != NULL)
            triFaceLine[i] = TriangleFace(i, 0, 0, 0);
        }
    }
    std::string toString()
    {
        std::string a = "";
        for (int i = 0; i < totNode; i++)
        {
            Node tis = nodeLine[i];
            a = a + tis.Pos.toString();
            a = a + "\n";
        }
        for (int i = 0; i < totTriFace; i++)
        {
            a = a + triFaceLine[i].toString();
            a = a + "\n";
        }
        return a;
    }
    Mesh()
    {
        totNode = 0;
        totTriFace = 0;
    }
    void setNode(int cnt, double x, double y, double z)
    {
        nodeLine[cnt].Pos.set(x, y, z);
        nodeLine[cnt].cnt = cnt;
    }
    VECTOR getNormal(int x)
    {
        if (x >= totTriFace)
        {
            return makeVector(0, 0, 0);
        }
        VECTOR a = nodeLine[triFaceLine[x].n1].Pos;
        VECTOR b = nodeLine[triFaceLine[x].n2].Pos;
        VECTOR c = nodeLine[triFaceLine[x].n3].Pos;
        a.scale(-1);
        b.add(a);
        c.add(a);
        return makeVector((b.y * c.z) - (c.y * b.z), (c.x * b.z) - (b.x * c.z), (b.x * c.y) - (c.x * b.y));    
    }
    

};

class Material
{
public:
    Image img;
    std::string imgFile;
    int extendType;
    //0 translation;1 winding;2 random 
    VECTOR deviation;
    double scale;
    std::string toString()
    {
        std::string a;
        a = imgFile;
        a = a + ",";
        a = a + std::to_string(extendType);
        a = a + ",";
        a = a + deviation.toString();
        a = a + ",";
        a = a + doubleToString(scale);
        return a;
    }
    Material()
    {
        extendType = 0;
        deviation = makeVector(0, 0, 0);
    }
    Colour getColorAtPosition(VECTOR a)
    {
        if (extendType == 0)
        {
            VECTOR trans = deviation;
            //trans.normalize();
            trans.scale(a.z / trans.z);
            trans.scale(-1.0);
            a.add(trans);
            double xPos = fmod(fmod(a.x, scale)+scale,scale)/scale;
            double yPos = fmod(fmod(a.y, scale)+scale,scale)/scale;
            return img.colourMap[(int)(xPos * img.sizeX)][(int)(yPos * img.sizeY)];
        }
        if (extendType == 1)
        {
            VECTOR trans = deviation;
            trans.normalize();
            trans.scale(a.dot(trans));
            double xPos = fmod(fmod(trans.length(), scale) + scale, scale) / scale;
            trans.scale(-1.0);
            a.add(trans);
            double yPos = fmod(fmod(    a.length(), scale) + scale, scale) / scale;
            return img.colourMap[(int)(xPos * img.sizeX)][(int)(yPos * img.sizeY)];
        }
    }

};

class Header
{
public:
    int totNode;
    int totTriFace;
    Header(int _totNode, int _totTriFace)
    {
        totNode = _totNode;
        totTriFace = _totTriFace;
    }
    std::string toString()
    {
        std::string a;
        a = std::to_string(totNode);
        a = a + ",";
        a = a + std::to_string(totTriFace);
        a = a + "\n";
        return a;
    }
    Header()
    {
        totNode = 0;
        totTriFace = 0;
    }
};

class TdmMesh
{
public:
    Mesh mesh;
    Material material;
    Header header;
    TdmMesh()
    {
    }
    std::string toString()
    {
        std::string a;
        a = header.toString();
        a = a + mesh.toString();
        a = a + material.toString();
        return a;
    }
    void fromString(std::string a,std::string path = "./")
    {
        std::string lsLine;
        std::string lsWord;
        lsLine = firstSplit(a, "\n");
        a = a.erase(0, lsLine.length() + 1);
        lsWord = firstSplit(lsLine, ",");
        int a1 = stringToInt(lsWord);
        lsLine = lsLine.erase(0, lsWord.length() + 1);
        int a2 = stringToInt(lsLine);
        mesh = Mesh(a1, a2);
        for (int i = 0; i < mesh.totNode; i++)
        {
            lsLine = firstSplit(a, "\n");
            a = a.erase(0, lsLine.length() + 1);
            lsWord = firstSplit(lsLine, ",");
            lsLine = lsLine.erase(0, lsWord.length() + 1);
            double x = stringToDouble(lsWord);
            lsWord = firstSplit(lsLine, ",");
            lsLine = lsLine.erase(0, lsWord.length() + 1);
            double y = stringToDouble(lsWord);
            double z = stringToDouble(lsLine);
            mesh.setNode(i, x, y, z);
        }
        for (int i = 0; i < mesh.totTriFace; i++)
        {
            lsLine = firstSplit(a, "\n");
            a = a.erase(0, lsLine.length() + 1);
            lsWord = firstSplit(lsLine, ",");
            lsLine = lsLine.erase(0, lsWord.length() + 1);
            int x = stringToInt(lsWord);
            lsWord = firstSplit(lsLine, ",");
            lsLine = lsLine.erase(0, lsWord.length() + 1);
            int y = stringToInt(lsWord);
            int z = stringToInt(lsLine);
            mesh.triFaceLine[i] = TriangleFace(i, x, y, z);
        }
        material = Material();
        lsWord = firstSplit(a, ",");
        material.imgFile = lsWord;
        a = a.erase(0,lsWord.length() + 1);
        lsWord = firstSplit(a, ",");
        material.extendType = stringToInt(lsWord);
        a = a.erase(0,lsWord.length() + 1);

        lsWord = firstSplit(a, ",");
        material.deviation.x = stringToDouble(lsWord);
        a = a.erase(0,lsWord.length() + 1);
        lsWord = firstSplit(a, ",");
        material.deviation.y = stringToDouble(lsWord);
        a = a.erase(0,lsWord.length() + 1);
        lsWord = firstSplit(a, ",");
        material.deviation.z = stringToDouble(lsWord);

        a = a.erase(0, lsWord.length() + 1);
        material.scale = stringToDouble(a);

        header = Header(mesh.totNode, mesh.totTriFace);
        std::string entirePath = path + material.imgFile;
        material.img = rdBMReadImage((char*)entirePath.c_str());
    }

    void fromFile(std::string target)
    {
        std::string path = "./";
        for (int i = 0; i < target.length(); i++)
        {
            if (target.substr(target.length() - i - 1) == "/" || target.substr(target.length() - i - 1) == "\\")
            {
                path = target.substr(0, target.length() - i);
                break;
            }
        }
        std::string in;
        std::ifstream fileIn(target, std::ios::in | std::ios::binary);
        if (!fileIn)
        {
            _log(0, "try to open "+target+" open File Failed");
            return;
        }
        fileIn.seekg(0, std::ios::end);
        in.resize(fileIn.tellg());
        fileIn.seekg(0, std::ios::beg);
        fileIn.read(&in[0], in.size());
        fileIn.close();
        //std::cout << in;
        fromString(in, path);
    }
    void toFile(std::string target)
    {
        _log(2, target);
        std::ofstream _fileOut(target.c_str());
        if (!_fileOut)
        {
            _log(0, "open " + target + " failed");
            return;
        }
        std::string lsa = toString();
        _fileOut << lsa;
        _fileOut.close();
        std::string path = "./";
        for (int i = 0; i < target.length(); i++)
        {
            if (target.substr(target.length() - i - 1) == "/" || target.substr(target.length() - i - 1) == "\\")
            {
                path = target.substr(0, target.length() - i);
                break;
            }
        }
        rdBMWriteImage((char*)(path + material.imgFile).c_str(), material.img);
        return;
    }

    Image drawFaceOnImage(int offsetX, int offsetY, int edgeLength, int faceName, Image a)
    {
        TriangleFace fa = mesh.triFaceLine[faceName];
        VECTOR n1ton2 = mesh.nodeLine[fa.n2].Pos;
        VECTOR n1 = mesh.nodeLine[fa.n1].Pos;
        n1.scale(-1);
        n1ton2.add(n1);
        n1 = mesh.nodeLine[fa.n2].Pos;
        n1.scale(-1);
        VECTOR n2ton3 = mesh.nodeLine[fa.n3].Pos;
        n2ton3.add(n1);
        VECTOR n1heart = mesh.nodeLine[fa.n1].Pos;

        for (int i = 0; i < edgeLength; i++)
        {
            for (int j = 0; j <= i; j++)
            {
                a.colourMap[i+offsetX][j+offsetY] = material.getColorAtPosition(n1heart.r_add(n1ton2.r_scale(((double)i + 0.5) / edgeLength)).r_add(n2ton3.r_scale((((double)j + 0.5) / edgeLength))));
            }
        }
        return a;

    }

};

#endif TDMM_H