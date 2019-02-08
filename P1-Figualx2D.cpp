/* O problema eh o seguinte : D^2T/Dx^2=DT/Dt para 0<x<1 , t>0
                              T=0 para x=0, t>0
                              T=0 para x=1, t>0
                              T=x para t=0, 0<=x<=1.

A soluçao exata eh T(x,t)=Sum((-2*(-1)^n*exp(-a*n^2*Pi^2*t)*sin(n*Pi*x)/(n*Pi) )  */

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

main()
{
   float Dx,Dt,a,rx,ry,Lx,Ly,Dy;
   double T[30][30][30],ta=0;
   int i,n,j,tempo,nu,M;

   tempo=15;
   Lx=1;//fronteira em x
   Ly=1;
   M=5;//número de equações
   a=1.4;
   Dx=Lx/M;
   Dy=Ly/M;
   Dt=(Dx*Dx*Dy*Dy)/(2*a*(Dy*Dy+Dx*Dx));//condição necessária para estabilidade

   rx=(a*Dt)/(Dx*Dx);
   ry=(a*Dt)/(Dy*Dy);

   for(i=0;i<=M;i++)//Condição inicial
   {
     for(j=0;j<=M;j++)
     {
      T[0][i][j]=(i*Dx)*(i*Dx)+(j*Dy)*(j*Dy);
     }
   }
   for(n=0;n<=tempo;n++)//Condições de Fronteira
   {
      T[n][0][0]=0;//Fronteira Inicial
      T[n][M][M]=0;//Fronteira Final
   }

   //a restrição do tempo é unicamente para ter um limite de exibição
   for(n=0;n<=(tempo-1);n++){
      for(i=1;i<=(M-1);i++){
        for(j=1;j<=(M-1);j++){
               T[n+1][i][j]=T[n][i][j]+rx*(T[n][i-1][j]-2*T[n][i][j]+T[n][i+1][j])+
                             ry*(T[n][i][j-1]-2*T[n][i][j]+T[n][i][j+1]);
        }//for j
      }//for i
   }//for n

   //for(n=0;n<=tempo;n++)
   n=8;
   for(i=0;i<=M;i++)
   {
     for(j=0;j<=M;j++)
      {
         printf("%3.4f  ",T[n][i][j]);
      }
      printf("\n");
   }

      system("PAUSE");
      return 0;
}
