class Train
{
  public:
    int A,B,C,D,M,N,pitch;
    float ratio;
    float travel;
    float tpi;

    Train(int a, int b, int c, int d, int m, int n, int pitch)
    {
      A = a;
      B = b;
      C = c;
      D = d;
      M = m;
      N = n;


      ratio = ((float)A/(float)B) * ((float)C/(float)D);
      travel = ((float)m/(float)n) * ratio * pitch;
      tpi = (float)25.4/travel;
    }

    /*
    void fakeprint() const
    {
      std::string foo = print();
    }*/

    /* fprintf is MUCH faster; this.print() is deprecated
    std::string print() const
    {
      std::ostringstream retval;
      retval  << boost::format("%02d/%02d * %02d/%02d * %02d/%02d ")
              %M %N %A %B %C %D
              << boost::format(" => %.4fmm | %.4f TPI")
              %travel %tpi
              << std::endl;
      return retval.str();
    }
    */

    bool operator <(const Train &rhs) const
    {
      return ( ratio < rhs.ratio );
    }

    bool operator =(const Train &rhs) const
    {
      return ( ratio == rhs.ratio );
    }
};
