/* O problema eh o seguinte : D^2T/Dx^2=DT/Dt para 0<x<1 , t>0
                              T=0 para x=0, t>0
                              T=0 para x=1, t>0
                              T=x para t=0, 0<=x<=1.

A solu�ao exata eh T(x,t)=Sum((-2*(-1)^n*exp(-a*n^2*Pi^2*t)*sin(n*Pi*x)/(n*Pi) )  */

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

main()
{
   float Dx,Dt,a,r,L;
   double T[30][30],ta=0;
   int i,n,tempo,nu,M;

   tempo=15;
   L=1;//fronteira em x
   M=10;//n�mero de equa��es
   a=1.4;
   Dx=L/M;
   Dt=(Dx*Dx)/(2*a);//condi��o necess�ria para estabilidade

   r=(a*Dt)/(Dx*Dx);

   for(i=0;i<=M;i++)//Condi��o inicial
   {
      T[0][i]=i*Dx;
   }
   for(n=0;n<=tempo;n++)//Condi��es de Fronteira
   {
      T[n][0]=0;//Fronteira Inicial
      T[n][M]=0;//Fronteira Final
   }

   //a restri��o do tempo � unicamente para ter um limite de exibi��o
   for(n=0;n<=(tempo-1);n++){
      for(i=1;i<=(M-1);i++){
               T[n+1][i]=r*T[n][i-1]+(1-2*r)*T[n][i]+r*T[n][i+1];
      }//for i
   }//for n

   for(n=0;n<=tempo;n++)
   {
     i=4;//for(i=0;i<=M;i++)
      {
         for(nu=1;nu<=1000;nu++)//para ter a s�rie
         {
            ta=ta+( (-2)*( pow(-1,nu)*exp(-nu*nu*3.14*3.14*a*n*Dt)*sin(nu*3.14*i*Dx))/(nu*3.14)  );
         }
         printf("%3.6f-%3.6f   ",T[n][i],ta);
         ta=0;
      }
      printf("\n");
   }

      system("PAUSE");
      return 0;
}
