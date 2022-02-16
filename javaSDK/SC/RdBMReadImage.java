package rdcv;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;

public class RdBMReadImage {
    String data=null;
    short filetype;
    RdBMdetailHeader fileHeader;
    RdBMdetailHeader detailHeader;
    int channels = 1;
    int width=0;
    int height=0;
    int step=0;
    int offset=0;
    char pixVal;
    RdBMcolour colour4;
    Image out= new Image();
    public  Image rdBMReadImage(String path) throws IOException {
        try {
            out=new Image();

            data= Files.readString(Path.of(path));

        }catch (IOException e){
            System.out.println("Open failed or not a BitMap");
            return out;
        }
        if(detailHeader.bdBitCount==24)
        {
            width = (int) detailHeader.bdWidth;
            height = (int) detailHeader.bdHeight;
            out.sizeX = width;
            out.sizeY = height;
            channels = 3;
            offset = (channels * width) % 4;
            int index=0;
            char[] temp=data.toCharArray();
            if (offset != 0)offset = 4 - offset;
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    int[] p=new int[3];
                    for (int k = 0; k < 3; k++)
                    {

                        pixVal=temp[index];
                        p[2 - k] = (int)pixVal;
                        index++;
                    }
                    out.colourMap[i][j] = new Colour(p[0], p[1], p[2]);
                }
                if (offset != 0)
                {
                    for (int j = 0; j < offset; j++)
                    {
                        pixVal=temp[index];
                        index++;
                    }
                }
            }
        }
        return out;
    }
    public  RdMfileHeader getRdMfileHeader()//获取对象
    {
        RdMfileHeader obj=RdMfileHeader.getRdMfileHeader();
        return obj;
    }
    public  RdBMdetailHeader getRdBMdetailHeader()//获取对象
    {
        RdBMdetailHeader obj=RdBMdetailHeader.getRdBMdetailHeader();
        return obj;
    }
    public  RdBMcolour getRdBMcolour()//获取对象
    {
        RdBMcolour obj=RdBMcolour.getRdBMcolour();
        return obj;
    }
}
class RdMfileHeader
{
     long bfSize;
    int bfReserved1;//unsigned short
    int bfReserved2;//unsigned short
    long  bfOffBits;
    //暂不处理unsigned
    private int getUnsignedShort(short data)
    {
        return data&0X0FFFF;
    }
   private RdMfileHeader() {}
    public static RdMfileHeader getRdMfileHeader()//获取对象
    {
        RdMfileHeader obj=new RdMfileHeader();
        return obj;
    }
}
class RdBMdetailHeader
{
    long bdSize;
    long bdWidth;
    long bdHeight;
    short bdPlanes;
    short bdBitCount;
    long bdCompression;
    long bdSizeImage;
    long bdXPelsPerMeter;
    long bdYPelsPerMeter;
    long bdClrUsed;
    long bdClrImportant;
    private  RdBMdetailHeader(){}
    public static RdBMdetailHeader getRdBMdetailHeader()
    {
        RdBMdetailHeader obj=new RdBMdetailHeader();
        return obj;
    }
}
class RdBMcolour
{
	char bmBlue;
    char bmGreen;
    char bmRed;
	char bmReserved;
    private  RdBMcolour(){}
    public static RdBMcolour getRdBMcolour()
    {
        RdBMcolour obj =new RdBMcolour();
        return obj;
    }
}
