/* O problema eh o seguinte : D^2T/Dx^2=DT/Dt para 0<x<1 , t>0
                              T=0 para x=0, t>0
                              T=0 para x=1, t>0
                              T=10sin(2*Pi*x) para t=0, 0<=x<=1.

A soluçao exata eh T(x,t)=10exp(-4*Pi^2*t)sin(2*Pi*x)*/


#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

main()
{
   float Dx,Dt,r,L;
   double T[30][30];
   int i,n,tempo,M;

   M=5;//número de nós da malha espacial
   L=1;
   Dx=L/M;//determinaçao do tamanho da malha do espaço
   Dt=((Dx*Dx)/2);//condição para estabilidade do sistema
   r=((Dt)/(Dx*Dx));

   for(i=0;i<=M;i++)//preenchendo com a condição inicial
   {
      T[0][i]=10*sin(2*3.14*i*Dx);
   }

   for(n=0;n<=M*2-1;n++)
      for(i=1;i<=M-1;i++)
      {
         T[n][0]=0;
         T[n][M]=0;
         T[n+1][i]=r*T[n][i-1]+(1-2*r)*T[n][i]+r*T[n][i+1];
      }

   for(n=0;n<=M*2;n++)
   {
      i=2;//for(i=0;i<=M;i++)
            {
         printf("%3.4f>>%3.4f\t",T[n][i],10*exp(-39.47842*n*Dt)*sin(6.2832*i*Dx));
      }
      printf("\n");
   }

      system("PAUSE");
      return 0;
}
