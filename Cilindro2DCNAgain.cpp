/* O problema eh o seguinte : D^2T/Dx^2=DT/Dt para 0<x<1 , t>0
                              T=0 para x=0, t>0
                              T=0 para x=1, t>0
                              T=x para t=0, 0<=x<=1.

A soluçao exata eh T(x,t)=Sum((-2*(-1)^n*exp(-a*n^2*Pi^2*t)*sin(n*Pi*x)/(n*Pi) )  */

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M   10
#define N 10
#define tempo  5000


int main()
{
   double Dr,Dt,D12,e=1.0,rr,rz,ru,ru2,Dz,Lr,Lz,temp,u,a;
   double C[M+1][N+1][tempo+1],max=0.0;
   int i,k,n;
   FILE *fp;


   Lr=11.2;
   Lz=0.0002556;
   D12=2.0E-9;
   u=5.0E-3;

   Dr=Lr/(double)M;
   Dz=Lz/(double)N;
   Dt=Dr/10000.0;

   rr=(D12*Dt)/(Dr*Dr);
   rz=(D12*Dt)/(Dz*Dz);
   ru2=(u*Dt)/(2.0*Dz);


   /*Matriz chute inicial*/
   for(n=0;n<=tempo;n++)
    for(i=0;i<=M;i++)
     for(k=0;k<=N;k++)
      C[i][k][n]=0.0;

   for(i=0;i<=M;i++)
     {
      k=1;
      C[i][k][0]=10.0;
     }






while(e>0.0001){

 for(n=0;n<=(tempo-1);n++){
  for(k=1;k<=(N-1);k++) {
    for(i=1;i<=(M-1);i++){
    C[i][N][n]=0.0;
    ru=u*Dt*( 1.0- (i*i*Dr*Dr)/(a*a) )/(2.0*Dz);

    C[i][0][n+1]=((0.5*rr*(C[i+1][0][n+1]+C[i-1][0][n+1]+C[i+1][0][n]-2.0*C[i][0][n]+C[i-1][0][n])
                   +(rr/(4*i))*(C[i+1][0][n+1]-C[i-1][0][n+1]+C[i+1][0][n]-C[i-1][0][n])
                   +rz*(C[i][1][n+1]+C[i][1][n]-C[i][0][n])+C[i][0][n] )/(rr+rz+1));

    C[0][k][n+1]=((2*rr*(C[1][k][n+1]+C[1][k][n]-C[0][k][n])
                   +rz*0.5*(C[0][k+1][n+1]+C[0][k-1][n+1]+C[0][k+1][n]-2.0*C[0][k][n]+C[0][k-1][n])
                   +C[0][k][n]
                   -ru2*(C[0][k+1][n+1]-C[0][k-1][n+1]+C[0][k+1][n]-C[0][k+1][n]))/(2*rr+rz+1));

     temp=((rr*0.5*(C[i+1][k][n+1]+C[i-1][k][n+1]+C[i+1][k][n]-2.0*C[i][k][n]+C[i-1][k][n])
             +(rr/(4.0*i))*(C[i+1][k][n+1]-C[i-1][k][n+1]+C[i+1][k][n]-C[i-1][k][n])
             +rz*0.5*(C[i][k+1][n+1]+C[i][k-1][n+1]+C[i][k+1][n]-2.0*C[i][k][n]+C[i][k-1][n])
             +C[i][k][n]-ru*(C[i][k+1][n+1]-C[i][k-1][n+1]+C[i][k+1][n]-C[i][k-1][n]))/(rr+rz+1));

      if(fabs(C[i][k][n+1]-temp)>max){
         max=fabs(C[i][k][n+1]-temp);
         e=fabs(C[i][k][n+1]-temp)/temp;
      }
      C[i][k][n+1]=temp;

     C[M][k][n+1]=((rr*(C[M-1][k][n+1]+C[M-1][k][n]-C[M][k][n])
                    +rz*0.5*(C[M][k+1][n+1]+C[M][k-1][n+1]+C[M][k+1][n]-2.0*C[M][k][n]+C[M][k-1][n])
                    +C[M][k][n])/(rr+rz+1));
      }
     }
   }
   max=0.0;
}

if((fp=fopen("cilindro.txt","w"))==NULL)
        printf("Erro na criação de dados.txt");

   fprintf(fp,"CrankNicolson\n");

   

   for(n=0;n<=tempo;n++){
     for(i=0;i<=M;i++){

       k=(N-1);

          fprintf(fp,"%3.6f ",C[i][k][n]);

       fprintf(fp,"\t");
   }//for i
   fprintf(fp,"\n");
   }//tempo

   fclose(fp);

      return 0;
}
