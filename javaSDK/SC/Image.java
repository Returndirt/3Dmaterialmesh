package rdcv;

public class Image extends LOG{
    public int sizeX;
    public int sizeY;
    public Colour[][] colourMap;
    Image()
    {
        colourMap= new Colour[2048][];
        if(colourMap!=null)
        {
            for(int i=0;i<2048;i++)
            {
                colourMap[i]=new Colour[2048];
            }
        }
        if(colourMap!=null)
        {
            for(int i=0;i<2048;i++)
            {
                if(colourMap[i]!=null)
                {
                    for(int j=0;j<2048;j++)
                    {
                        colourMap[i][j]=new Colour(0,0,0);
                    }
                }
            }
        }
        clearSize();
    }
    private void clearSize()
    {
        sizeX=0;
        sizeY=0;
    }
}
