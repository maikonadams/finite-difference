#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M   	10L
#define N 	10L
#define tempo  	1000L

int
main ()
{
  double Dr, Dt, D12, e = 1.0, rr, rz, ru, ru2, Dz, temp, u, zmax, rmax;
  static double C[M + 1][N + 1][tempo + 1];
  static double U[M + 1][N + 1][tempo + 1];
  static double V[M + 1][N + 1][tempo + 1];
  double max = 0.0;
  int i, k, n,j;
  FILE *fp;

  zmax = 11.2;
  rmax = 0.0002556;
  D12 = 2.0E-7;
  u = 5.0E-2;

  Dr = 1.0 / (double) M;
  Dz = 1.0 / (double) N;
  Dt = Dr / 10.0;

  rr = (D12 * Dt * zmax * zmax) / (Dr * Dr);
  rz = (D12 * Dt * rmax * rmax) / (Dz * Dz);


  /*Matriz chute inicial */
  for (n = 0; n <= tempo; n++)
    for (i = 0; i <= M; i++)
      for (k = 0; k <= N; k++){
	   C[i][k][n] = 0.0;
       U[i][k][n] = 0.0;
       V[i][k][n] = 0.0;
      }

  /*Matriz das Condições Iniciais*/
  for (i = 0; i <= M; i++){
      C[i][1][0] = 100.0;
      U[i][1][0] = 100.0;
      V[i][1][0] = 100.0;
  }



   for (n = 0; n <= (tempo - 1); n++)
   {
     for (j = 1; j <= (N - 1); j++)
     {
       for (i = 1; i <= (M - 1); i++)
       {
         ru = ((u * Dt * rmax * rmax * zmax)*(1-i*i*Dr*Dr)) / ( Dz);
         ru2= u*Dt*rmax*rmax*zmax;
         U[i][N][n] = 0.0;
         V[i][N][n] = 0.0;
         U[0][j][n+1]=(2*rr*(U[1][j][n+1]-U[0][j][n]+U[1][j][n])
                        +rz*(U[0][j-1][n+1]-U[0][j][n]+U[0][j+1][n])
                        +rmax*rmax*zmax*zmax*U[0][j][n]-ru2*(U[0][j+1][n+1]-U[0][j-1][n+1]) )/(2*rr+rz+rmax*rmax*zmax*zmax);
         V[0][j][n+1]=(2*rr*(V[1][j][n]-V[0][j][n]+V[1][j][n+1])
                        +rz*(V[0][j-1][n]-V[0][j][n]+V[0][j+1][n+1])
                        +rmax*rmax*zmax*zmax*V[0][j][n]-ru2*(V[0][j+1][n+1]-V[0][j-1][n+1]) )/(2*rr+rz+rmax*rmax*zmax*zmax);

         U[i][0][n+1]=((rr*(U[i-1][0][n+1]-U[i][0][n]+U[i+1][0][n])
                         +(rr/(2.0*i))*(U[i+1][0][n+1]-U[i-1][0][n+1])
                         +rz*(U[i][1][n+1]-U[i][0][n]+U[i][1][n])
                         +rmax*rmax*zmax*zmax*U[i][0][n])/(rmax*rmax*zmax*zmax+rr+rz));

         V[i][0][n+1]=((rr*(V[i-1][0][n]-V[i][0][n]+V[i+1][0][n+1])
                         +(rr/(2.0*i))*(V[i+1][0][n+1]-V[i-1][0][n+1])
                         +rz*(V[i][1][n]-V[i][0][n]+V[i][1][n+1])
                         +rmax*rmax*zmax*zmax*V[i][0][n])/(rmax*rmax*zmax*zmax+rr+rz));

         U[i][j][n+1]=((rr*(U[i-1][j][n+1]-U[i][j][n]+U[i+1][j][n])
                       +(rr/(2.0*i))*(U[i+1][j][n+1]-U[i-1][j][n+1])
                       +rz*(U[i][j-1][n+1]-U[i][j][n]+U[i][j+1][n])
                       +rmax*rmax*zmax*zmax*U[i][j][n]
                       -ru*(U[i][j+1][n+1]-U[i][j-1][n+1]))/(rmax*rmax*zmax*zmax+rr+rz));

         V[i][j][n+1]=((rr*(V[i-1][j][n]-V[i][j][n]+V[i+1][j][n+1])
                       +(rr/(2.0*i))*(V[i+1][j][n+1]-V[i-1][j][n+1])
                       +rz*(V[i][j-1][n]-V[i][j][n]+V[i][j+1][n+1])
                       +rmax*rmax*zmax*zmax*V[i][j][n]
                       -ru*(V[i][j+1][n+1]-V[i][j-1][n+1]))/(rmax*rmax*zmax*zmax+rr+rz));


         U[M][j][n+1]=((rr*(U[M-1][j][n+1]-U[M][j][n]+U[M-1][j][n])
                        +rz*(U[M][j-1][n+1]-U[M][j][n]+U[M][j+1][n])
                        +rmax*rmax*zmax*zmax*U[M][j][n])/(rmax*rmax*zmax*zmax+rr+rz));

         V[M][j][n+1]=((rr*(V[M-1][j][n]-V[M][j][n]+V[M-1][j][n+1])
                        +rz*(V[M][j-1][n]-V[M][j][n]+V[M][j+1][n+1])
                        +rmax*rmax*zmax*zmax*V[M][j][n])/(rmax*rmax*zmax*zmax+rr+rz));

         C[i][j][n+1]=(0.5)*(U[i][j][n+1]+V[i][j][n+1]);

       }//for i
     }//for k
   }//for n



  if ((fp = fopen ("escoamentoMistoADE.txt", "w")) == NULL)
    {
        printf ("escoamento.txt");
	return 1;
    }



 /* for (n = 0; n <= tempo; n++)
    {
      for (i = 0; i <= M; i++)
	  fprintf (fp, "%e\t", C[i][1][n] );

      fprintf (fp, "\n");
    }  */
    for (i = 0; i <= N; i++)
    {
      for (k = 0; k <= M; k++)
	  fprintf (fp, "%e\t", C[i][k][1000] );

      fprintf (fp, "\n");
    }


  fclose (fp);

  return 0;
}


