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
   float Dx,Dt,a,r,L,alpha,beta,k,q0,qL,PI=3.14159265;
   double T[100][100],ta=0;
   int i,n,tempo,nu,M,F=1;

   tempo=90;
   L=1;//fronteira em x
   M=5;//número de equações
   a=1.4;
   Dx=L/M;
   Dt=(Dx*Dx)/(2*a);//condição necessária para estabilidade
   alpha=0.6;
   beta=0.8;
   k=3.8;

   r=(a*Dt)/(Dx*Dx);

   for(i=0;i<=M;i++)//Condição inicial
   {
      T[0][i]=i*Dx*i*Dx;
   }


   q0=0;qL=0;
   //a restrição do tempo é unicamente para ter um limite de exibição
   for(n=0;n<=(tempo-1);n++){
      if (n>0&&T[n][0]>beta)                   F=1;//desligou
      else if ((n>0)&&(T[n][0]<alpha))         F=0;//ligou
      else if ((n>0)&&((beta-T[n][0])<0.001))  F=1;//desligou
      else if ((n>0)&&((T[n][0]-alpha)<0.001)) F=0;//ligou
      for(i=1;i<=(M-1);i++){
         T[n+1][0]=(1-2*r)*T[n][0]+2*r*T[n][1]-2*r*Dx*Dx*i/k;
         T[n+1][i]=r*T[n][i-1]+(1-2*r)*T[n][i]+r*T[n][i+1];
      }//for i
      T[n+1][M]=2*r*T[n][M-1]+(1-2*r+2*Dx*r/k)*T[n][M]+(F-1)*2*r*Dx/k;
   }//for n

   printf("Analitica-Numerica\n");
   for(n=0;n<=tempo;n++)
   {
     i=4;

     printf("%3.6f ",T[n][i]);
     printf("\n");
   }

      system("PAUSE");
      return 0;
}
