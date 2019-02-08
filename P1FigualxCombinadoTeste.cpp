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
   float Dx,Dt,a,r,r1,r2,L,e=1,temp,t;
   double T[30][30],ta=0,max=0;

   int i,n,tempo,nu,M;

   tempo=20;
   L=1;//fronteira em x
   M=10;//número de equações
   a=1.4;
   Dx=L/M;
   //Dt=(Dx*Dx)/(2*a);//condição necessária para estabilidade
   Dt=Dx/10;
   r=((a*Dt)/(Dx*Dx));
   t=(1/2 - (Dx*Dx)/(12*a*Dt));


   //matriz chute inicial
   for(n=0;n<=tempo;n++)
      for(i=0;i<=M;i++)
         T[n][i]=0;



   for(i=0;i<=M;i++)//preenchendo com a condição inicial
   {
      T[0][i]=i*Dx;
   }

   for(n=1;n<=tempo-1;n++)//preenchendo as condições de fronteira
   {
      T[n][0]=0;//Condição de Fronteira Inicial
      T[n][M]=0;//Condição de Fronteira Final
   }

//a restrição do tempo é unicamente para ter um limite de exibição
printf("t->%3.2f \n",t);
while(e>0.00001){
   for(n=0;n<=(tempo-1);n++){
     //while(e>0.00001){
      for(i=1;i<=(M-1);i++)
      {
         temp=(r*t*(T[n+1][i-1]+T[n+1][i+1])+r*(1-t)*T[n][i-1]+(1-2*r*(1-t))*T[n][i]+r*(1-t)*T[n][i+1])/(1+2*r*t);
         if( fabs( temp-T[n+1][i] )>max){
            max=fabs(temp-T[n+1][i]);
            e=( fabs(temp-T[n+1][i]) / fabs(temp) );
         }//fim if

         T[n+1][i]=temp;

      }//fim for i
     }//fim  for n
     max=0;


   }//fim while


   for(n=0;n<=tempo;n++)
   {
     i=2;// for(i=0;i<=M;i++)
      {
         for(nu=1;nu<=10000;nu++)//para ter a série
         {
            ta=ta+( (-2)*( pow(-1,nu)*exp(-nu*nu*3.14*3.14*a*n*Dt)*sin(nu*3.14*i*Dx))/(nu*3.14)  );
         }
         printf("%3.4f->%3.4f   ",T[n][i],ta);
         ta=0;
      }
      printf("\n");
   }

      system("PAUSE");
      return 0;
}
