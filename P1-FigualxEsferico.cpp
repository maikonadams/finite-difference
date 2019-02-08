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
   float d,Dt,a,r,L;
   double T[30][30],ta=0;
   int i,n,tempo,nu,M,p;

   tempo=20;
   L=1;//fronteira em x
   M=5;//número de equações
   a=1.4;
   d=L/M;
   Dt=(d*d)/(2*a);//condição necessária para estabilidade
   //Dt=Dx/100;
   r=(a*Dt)/(d*d);
   p=2; //p=1 (cilindrica) e p=2 (esférica)



   for(i=0;i<=M;i++)//Condição inicial
   {
      T[0][i]=i*d;
   }
   for(n=1;n<=tempo;n++)//Condições de Fronteira
   {

      T[n][M]=0;//Fronteira Final

   }

   //a restrição do tempo é unicamente para ter um limite de exibição
   for(n=0;n<=(tempo-1);n++){
      i=0;
      T[n+1][0]=(1-2*r*(1+p))*T[n][0]+2*r*(1+p)*T[n][1];
      for(i=1;i<=(M-1);i++)
         T[n+1][i]=r*(1-p/(2*i))*T[n][i-1]+ (1-2*r)*T[n][i]+r*(1+p/(2*i))*T[n][i+1];
   }//fim for n






   for(n=0;n<=tempo;n++)
   {
     i=0;  // for(i=0;i<=M;i++)
      {
         printf("%3.8f   ",T[n][i]);
         ta=0;
      }
      printf("\n");
   }

      system("PAUSE");
      return 0;
}
