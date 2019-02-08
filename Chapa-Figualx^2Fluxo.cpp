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
   float Dx,Dt,k,rx,ry,Dy,Lx,Ly,PI=3.14159265;
   double T[100][100][100];
   int i,j,n,tempo,nu,M;

   tempo=10;
   Lx=1;//fronteira em x
   Ly=1;//fronteira em y
   M=5;//número de equações
   k=1.4;
   Dx=Lx/M;
   Dy=Ly/M;
   Dt=(Dx*Dx*Dy*Dy)/(2*k*(Dy*Dy+Dx*Dx));//condição necessária para estabilidade

   rx=(k*Dt)/(Dx*Dx);
   ry=(k*Dt)/(Dy*Dy);



   for(i=0;i<=M;i++)//Condição inicial
   {
     for(j=0;j<=M;j++)
     {
      T[i][j][0]=(i*Dx)*(i*Dx)+(j*Dy)*(j*Dy);
     }
   }
   for(n=1;n<=tempo;n++)//Condições da Fronteira y
   {
     for(j=0;j<=M;j++)
     {
      T[0][j][n]=0;//Fronteira Inicial
      T[M][j][n]=0;//Fronteira Final
     }
   }

   //a restrição do tempo é unicamente para ter um limite de exibição

    for(n=0;n<=(tempo-1);n++){
     //   T[i][0][n+1]=(1-2*r)*T[n][0]+2*r*T[n][1];
       // T[i][M][n+1]=2*r*T[n][M-1]+(1-2*r)*T[n][M];
      for(i=1;i<=(M-1);i++){
         T[i][0][n+1]=(1-2*ry)*T[i][0][n]+2*ry*T[i][1][n];
         T[i][M][n+1]=2*ry*T[i][M-1][n]+(1-2*ry)*T[i][M][n];
        for(j=1;j<=(M-1);j++){
         T[i][j][n+1]=T[i][j][n]+rx*(T[i-1][j][n]-2*T[i][j][n]+T[i+1][j][n])+
                             ry*(T[i][j-1][n]-2*T[i][j][n]+T[i][j+1][n]);
        }//for j
      }//for i
   }//for n



   //for(n=0;n<=(tempo);n++){
   n=2;
     for(i=0;i<=M;i++){
       for(j=0;j<=M;j++){
         printf("%3.2f ",T[i][j][n]);
         //printf("\n");
       }//for j
      printf("\n");
   }//for i

      system("PAUSE");
      return 0;
}
