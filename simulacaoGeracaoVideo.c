#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M   	10L
#define N 	10L
#define tempo  	200L

int
main ()
{
  double Dr, Dt, D12, e = 1.0, rr, rz, ru, ru2, Dz, temp, u, zmax, rmax;
  static double C[M + 1][N + 1][tempo + 1];
  double max = 0.0;
  int i, k, n;
  FILE *fp;



  zmax = 11.2;
  rmax = 1.278E-4;
  D12 = 2.0E-7;
  u = 9.4089E-3;

  Dr = 1.0 / (double) M;
  Dz = 1.0 / (double) N;
  Dt = Dr / 10.0;

  rr = (D12 * Dt * zmax * zmax) / (Dr * Dr);
  rz = (D12 * Dt * rmax * rmax) / (Dz * Dz);
  ru2 = (u * Dt * rmax * rmax * zmax) / (2.0 * Dz);

  /*Matriz chute inicial */
  for (n = 0; n <= tempo; n++)
    for (i = 0; i <= M; i++)
      for (k = 0; k <= N; k++)
	C[i][k][n] = 0.0;

  for (i = 0; i <= M; i++)
      C[i][1][0] = 1000.0;

  /* Truque para melhorar o chute*/
  for (i = 0; i <= M; i++)
     C[i][1][1] = 90.0;

  while (e > 0.001)
    {
      for (n = 0; n <= (tempo - 1); n++)
	{
	  for (k = 1; k <= (N - 1); k++)
	    {
	      for (i = 1; i <= (M - 1); i++)
		{
		  C[i][N][n] = 0.0;
		  ru = u * Dt * rmax * rmax * zmax * (1.0 - (double) (i * i * Dr * Dr)) / (2.0 * Dz);

		  C[i][0][n + 1] =
		       ((0.5*rr*(C[i+1][0][n+1] + C[i-1][0][n+1] + C[i+1][0][n]-2.0* C[i][0][n]+ C[i-1][0][n]) +
	           ((rr)/((double)4.0*i))*(C[i+1][0][n+1]-C[i-1][0][n+1]+C[i+1][0][n] -
						     C[i-1][0][n])+rz*(C[i][1][n+1]+C[i][1][n]-C[i][0][n])+
		        C[i][0][n]*rmax*rmax*zmax*zmax)/(rr+rz+rmax*rmax*zmax*zmax));

		  C[0][k][n+1]=((2.0*rr*(C[1][k][n+1]+C[1][k][n]-C[0][k][n])
				     + rz*0.5*(C[0][k+1][n+1]+C[0][k-1][n+1]+C[0][k+1][n]-2.0*C[0][k][n]+
						   C[0][k-1][n])+C[0][k][n]*rmax*rmax*zmax*zmax-ru2*(C[0][k+1][n+1]-C[0][k-1][n+1]
														     + C[0][k +
															    1]
														     [n] -
														     C[0][k +
															  1]
														     [n])) /
				    (2.0 * rr + rz + rmax * rmax * zmax * zmax));

		  temp =
		    ((rr * 0.5 *
		      (C[i + 1][k][n + 1] + C[i - 1][k][n + 1] + C[i + 1][k][n] - 2.0 * C[i][k][n] + C[i - 1][k][n]) +
		      (rr / ((double) 4.0 * i)) * (C[i + 1][k][n + 1] - C[i - 1][k][n + 1] + C[i + 1][k][n] - C[i - 1][k][n]) +
		      rz * 0.5 * (C[i][k + 1][n + 1] + C[i][k - 1][n + 1] + C[i][k + 1][n] - 2.0 * C[i][k][n] +
				  C[i][k - 1][n]) + C[i][k][n] * rmax * rmax * zmax * zmax - ru * (C[i][k + 1][n + 1] - C[i][k -
															     1]
												   [n + 1] + C[i][k + 1][n] -
												   C[i][k - 1][n])) / (rr + rz +
														       rmax *
														       rmax *
														       zmax *
														       zmax));

		  if (fabs (C[i][k][n + 1] - temp) > max)
		    {
		      max = fabs (C[i][k][n + 1] - temp);
		      e = fabs (C[i][k][n + 1] - temp) / temp;
		    }
		  C[i][k][n + 1] = temp;

		  C[M][k][n + 1] = ((rr * (C[M - 1][k][n + 1] + C[M - 1][k][n] - C[M][k][n])
				     + rz * 0.5 * (C[M][k + 1][n + 1] + C[M][k - 1][n + 1] + C[M][k + 1][n] - 2.0 * C[M][k][n] +
						   C[M][k - 1][n]) + C[M][k][n] * rmax * rmax * zmax * zmax) / (rr + rz +
														rmax * rmax *
														zmax * zmax));
		}
	    }
	}
      max = 0.0;
    }

  if ((fp = fopen ("simulacaoGeracao.txt", "w")) == NULL)
    {
        printf ("Erro na cria��o de dados.txt");
	return 1;
    }






  for (n = 0; n <= tempo; n++)
    {
     for(k=0;k<=N;k++){
        for (i = 0; i <= M; i++){
	     fprintf (fp, "%e\t", C[i][k][n] * rmax); }//fim for i

     fprintf (fp, "\n");}//fim for k

    fprintf(fp, "\n\n");}//fim for n

fclose (fp);


  return 0;
}


