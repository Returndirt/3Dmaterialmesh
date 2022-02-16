package rdcv;

public class LOG{
    private static final int wall = 1;
    public void _log(int level,String a)
    {
        if(level<wall)
        {
            System.out.println(a);
        }
    }
}
