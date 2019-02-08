/* Temos um Cilindro em duas dimensões  */
/* #include <stdlib.h> */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M	10
#define N	10
#define tempo	30000

int main()
{
   double Dr,Dt,D12,a,rr,rz,ru,ru2,Dz,rmax,zmax,u;
   double C[M+1][N+1][tempo+1];
   int i,k,n;
   FILE *fp;

   rmax=0.0002556;
   zmax=11.2;
   D12=2.0E-7;
   a=0.0002556;
   u=0.05;

   Dr=1.0/(double) M;
   Dz=1.0/(double) N;

   Dt = (2.0*D12) / (u*u);

   rr=(D12*Dt*zmax*zmax)/(Dr*Dr);
   rz=(D12*Dt*rmax*rmax)/(Dz*Dz);
   ru2=(u*Dt*rmax*rmax*zmax)/Dz;


   for(n=0;n<=tempo;n++)
    for(i=0;i<=M;i++)
     for(k=0;k<=N;k++)
      C[i][k][n]=0.0;

     for(i=0;i<=M;i++)
      {
      /* C[i][1][0]=10.0;  */
        C[i][0][0]=10.0;
      /* C[i][2][0]=10.0;  */
      }

   for(n=1;n<=tempo;n++)
     for(i=0;i<=M;i++)
      C[i][N][n]=0;

  for(n=0;n<=(tempo-1);n++)
  for(k=1;k<=(N-1);k++)
   for(i=1;i<=(M-1);i++){


    if(n==0) {
    ru=Dt*u*rmax*rmax*zmax*(1-(i*i*Dr*Dr))/(Dz);
    C[i][0][n+1]=C[i][0][n]*rmax*rmax*zmax*zmax
                 +rr*(C[i+1][0][n]-2*C[i][0][n]+C[i-1][0][n])
                 +(rr/(2*i))*(C[i+1][0][n]-C[i-1][0][n])+rz*(C[i][1][n]-C[i][0][n])
                 -ru*(C[i][1][n]-C[i][0][n]);

    C[0][k][n+1]=4*rr*(C[1][k][n]-C[0][k][n])
                 +rz*(C[0][k+1][n]-2*C[0][k][n]+C[0][k-1][n])
                 +C[0][k][n]*rmax*rmax*zmax*zmax
                 -ru2*(C[0][k+1][n]-C[0][k-1][n]);

    C[i][k][n+1]=C[i][k][n]*rmax*rmax*zmax*zmax+rr*(C[i+1][k][n]-2*C[i][k][n]+C[i-1][k][n])
                 +(rr/(2*i))*(C[i+1][k][n]-C[i-1][k][n])
                 +rz*(C[i][k+1][n]-2*C[i][k][n]+C[i][k-1][n])
                 -ru*(C[i][k+1][n]-C[i][k-1][n]);

    C[M][k][n+1]=2*rr*(C[M-1][k][n]-C[M][k][n])+rz*(C[M][k+1][n]-2*C[M][k][n]+C[M][k-1][n])
                  +C[M][k][n]*rmax*rmax*zmax*zmax;
    }
    else 
    {  Dt=0.01;
       rr=(D12*Dt*zmax*zmax)/(Dr*Dr);
       rz=(D12*Dt*rmax*rmax)/(Dz*Dz);
       ru=Dt*u*rmax*rmax*zmax*(1-(i*i*Dr*Dr))/(Dz);
       ru2=(u*Dt*rmax*rmax*zmax)/Dz;


       C[0][k][n+1]=(4.0*rr*(2*C[1][k][n]-C[0][k][n-1])
                     +2.0*rz*(C[0][k+1][n]-C[0][k][n-1]+C[0][k-1][n])
                     +C[0][k][n-1]*rmax*rmax*zmax*zmax
                     -2.0*ru2*(C[0][k+1][n]-C[0][k-1][n]) )/(4*rr+2.0*rz+rmax*rmax*zmax*zmax);

       C[i][0][n+1]=((2.0*rr*(C[i+1][0][n]-C[i][0][n-1]+C[i-1][0][n])
                      +(rr/i)*(C[i+1][0][n]-C[i-1][0][n])
                      +2.0*rz*(C[i][1][n]-C[i][0][n-1]+C[i][0][n])
                      +C[i][0][n-1]*rmax*rmax*zmax*zmax
                      -2.0*ru*(C[i][1][n]-C[i][0][n]) )/(2.0*rr+2.0*rz+rmax*rmax*zmax*zmax));

       C[i][k][n+1]=((2.0*rr*(C[i+1][k][n]-C[i][k][n-1]+C[i-1][k][n])
                      +(rr/i)*(C[i+1][k][n]-C[i-1][k][n])
                      +2.0*rz*(C[i][k+1][n]-C[i][k][n-1]+C[i][k-1][n])
                      +C[i][k][n-1]*rmax*rmax*zmax*zmax
                      -2.0*ru*(C[i][k+1][n]-C[i][k-1][n]))/(2.0*rr+2.0*rz+rmax*rmax*zmax*zmax));

       C[M][k][n+1]= (2*rr*(2*C[M-1][k][n]-C[M][k][n-1])
                     +2*rz*(C[M][k+1][n]-C[M][k][n-1]+C[M][k-1][n])
                     +C[M][k][n-1]*rmax*rmax*zmax*zmax )/(2.0*rr+2.0*rz+rmax*rmax*zmax*zmax);
    }
   }


if((fp=fopen("dadosDFFFinalNormalizado.txt","w"))==NULL)
        printf("Erro na criação de dados.txt");

   fprintf(fp,"Explicito Du Fort-Frankel\n");


   for(n=0;n<=tempo;n++){
     for(i=0;i<=M;i++){
       k=(N-1);
          fprintf(fp,"%.6f ",C[i][k][n]);
	    fprintf(fp,"\t");
	}
    fprintf(fp,"\n");

   }

   fclose(fp);
     return 0;
}

