//#include <iostream.h>
#include <math.h>
//#include <fstream.h>

#define IMAX 19
#define JMAX 39
#define KMAX 19
#define ITER 100
#define NMAX 2
#define NHW 40
#define MED 2
#define JS 3
const double DELTA = 3E-3;
const double CL = 3.0E8;
const double F = 2.5E9;
const double PIE = 3.141592654;

//scatter dimension
#define OI 19.5
#define OJ 20
#define OK 19
#define RADIUS 15

class matrix{
      int a,b,c,d;
      int amax, bmax, cmax, dmax;
      float *data;
      int checkMinus(int index);
      void getSize(void){cout << amax <<"x"<<
      bmax <<"x"<<cmax <<"x"<< dmax << endl;}

};


int main()
{

      system("PAUSE");
      return 0;
}
