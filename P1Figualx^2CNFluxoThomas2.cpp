/* O problema eh o seguinte : D^2T/Dx^2=DT/Dt para 0<x<1 , t>0
            Fronteira Inicial T=0 para x=0, t>0
            Fronteira Final   T=0 para x=1, t>0
            Condição Inicial  T=x para t=0, 0<=x<=1.

A soluçao exata eh T(x,t)=Sum((-2*(-1)^n*exp(-a*n^2*Pi^2*t)*sin(n*Pi*x)/(n*Pi) )  */

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

main()
{
   float Dx,Dt,k,r,L,e=1,temp,PI=3.141592654;
   double T[100][100],ta=0,b[100],d[100],a[100],c[100],max=0;
   int i,n,tempo,nu,M;

   tempo=10;
   L=1;//fronteira em x
   M=10;//número de equações
   k=1.4;
   Dx=L/M;
   Dt=Dx/10;
//   Dt=0.0143;
   r=((k*Dt)/(Dx*Dx));

   //matriz chute inicial
   for(n=0;n<=tempo;n++)
      for(i=0;i<=M;i++){
         T[n][i]=0;

      }




   for(i=0;i<=M;i++)//preenchendo com a condição inicial
   {
      T[0][i]=i*Dx*Dx*i;
   }

   //Resolvendo por linha
while(e>0.0001){
   for(n=0;n<=tempo-1;n++)
   {
     T[n+1][0]=(2*r*T[n+1][1]+(2-2*r)*T[n][0]+2*r*T[n][1])/(2+2*r);
     for(i=1;i<=(M-1);i++)
     {
       temp=(r*(T[n+1][i-1]+T[n+1][i+1]+T[n][i-1]+T[n][i+1])+(2-2*r)*T[n][i])/(2+2*r);
       if(fabs(T[n+1][i]-temp)>max)
       {
         max=fabs(T[n+1][i]-temp);
         e=fabs(T[n+1][i]-temp)/temp;
       }//fim if
       T[n+1][i]=temp;
       T[n+1][M]=(2*r*(T[n][M-1]+T[n+1][M-1])+(2-2*r)*T[n][M])/(2+2*r);
     }//fim for i
   }//for n
   max=0;
}//fim while




   printf("Numerico->Analitico\n");
   for(n=0;n<=tempo;n++)
   {
     i=1;// for(i=0;i<=M;i++)
      {
         for(nu=1;nu<=10000;nu++)//para ter a série
         {
            ta=ta + 4*(pow(-1,nu)*exp(-nu*nu*PI*PI*k*n*Dt)*cos(nu*PI*i*Dx))/(nu*nu*PI*PI);
         }
         //ta=ta + 1/3;
         printf("%3.6f->%3.6f   ",T[n][i],ta+1/3);
         ta=0;
      }

      printf("\n");
   }

      system("PAUSE");
      return 0;
}
