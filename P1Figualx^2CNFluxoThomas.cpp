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
   M=5;//número de equações
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
   //Thomas Algorithm
   //Preenchendo os indices a,b,c,d
   //---------a
   for(i=1;i<=(M-1);i++){a[i]=-r;}a[M]=-2*r;

   //---------b
   for(i=1;i<=(M-1);i++){b[i]=2+2*r;}

   //---------c
   for(i=1;i<=(M-1);i++){c[i]=-r;}c[0]=-2*r;

   //---------d apenas na primeira vez, depois esse deve ser atualizado
   for(i=1;i<=(M-1);i++){d[i]=r*T[0][i-1]+(2-2*r)*T[0][i]+r*T[0][i+1];}
   d[0]=(2-2*r)*T[0][0]+2*r*T[0][1];
   d[M]=2*r*T[0][M-1]+(2-2*r)*T[0][M];


   //retrossubstituição para obter T
   for(n=0;n<=(tempo-1);n++)
   {
      //implimentação dos índices
      for(i=1;i<=M;i++){
         b[i]=b[i]-a[i]*c[i-1]/b[i-1];
         d[i]=d[i]-a[i]*d[i-1]/b[i-1];
      }
      for(i=(M-1);i>=0;i--)
      {
         T[n+1][M]=d[M]/b[M];
         T[n+1][i]=(d[i]-c[i]*T[n][i+1])/b[i];
      }
      //atualizando d
      d[0]=(2-2*r)*T[n+1][0]+2*r*T[n+1][1];
      for(i=1;i<=(M-1);i++)
       {
         d[i]=r*T[n+1][i-1]+(2-2*r)*T[n+1][i]+r*T[n+1][i+1];
       }
      d[M]=2*r*T[n+1][M-1]+(2-2*r)*T[n+1][M];

   }

   printf("Numerico->Analitico\n");
   for(n=0;n<=tempo;n++)
   {
     i=3;// for(i=0;i<=M;i++)
      {
         for(nu=1;nu<=10000;nu++)//para ter a série
         {
            ta=ta + 4*(pow(-1,nu)*exp(-nu*nu*PI*PI*k*n*Dt)*cos(nu*PI*i*Dx))/(nu*nu*PI*PI);
         }
         ta=ta + 1/3;
         printf("%3.6f->%3.6f   ",T[n][i],ta);
         ta=0;
      }

      printf("\n");
   }

      system("PAUSE");
      return 0;
}
