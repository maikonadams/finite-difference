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
   float Dx,Dt,a,r,L,PI=3.14159265;
   double T[30][30],ta=0;
   int i,n,tempo,nu,M;

   tempo=20;
   L=1;//fronteira em x
   M=5;//número de equações
   a=1.4;
   Dx=L/M;
   Dt=(Dx*Dx)/(2*a);//condição necessária para estabilidade

   r=(a*Dt)/(Dx*Dx);

   for(i=0;i<=M;i++)//Condição inicial
   {
      T[0][i]=(i*Dx);
   }
   //a restrição do tempo é unicamente para ter um limite de exibição
    for(n=0;n<=(tempo-1);n++){
      T[n+1][0]=0; //numa fronteiraa temperatura é 0
      T[n+1][M]=2*r*T[n][M-1]+(1-2*r)*T[n][M];//na outra fronteira o fluxo é nulo
      for(i=1;i<=(M-1);i++){
               T[n+1][i]=r*T[n][i-1]+(1-2*r)*T[n][i]+r*T[n][i+1];
      }//for i

   }//for n

   printf("Numerico-Analitico\n");
   for(n=0;n<=(tempo);n++)
   {
     i=3;//for(i=0;i<=M;i++)
      {
         for(nu=1;nu<=1000;nu++)//para ter a série
         {
          ta=(ta+(-8*pow(-1,nu)*exp(-(pow(2*nu-1,2)*PI*PI*a*n*Dt)/(4*L*L))*sin((2*nu-1)*PI*i*Dx/2*L))/(pow(2*nu-1,2)*PI*PI));
         }
         printf("%3.4f-%3.4f",T[n][i],ta);
         ta=0;
      }
      printf("\n");
   }

      system("PAUSE");
      return 0;
}
