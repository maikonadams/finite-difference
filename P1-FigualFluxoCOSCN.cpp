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
   FILE *fp;
   float Dx,Dt,a,r,L,PI=3.14159265,e=1,max=0,temp;
   double T[1000][1000],ta=0;
   int i,n,tempo,nu,M;

   tempo=15;
   L=1;//fronteira em x
   M=10;//número de equações
   a=1.4;
   Dx=L/M;
   //Dt=(Dx*Dx)/(2*a);//condição necessária para estabilidade
   Dt=Dx/100;

   r=(a*Dt)/(Dx*Dx);

   for(i=0;i<=M;i++)//Condição inicial
   {
      T[0][i]=cos(i*Dx);
   }
   //a restrição do tempo é unicamente para ter um limite de exibição
   while(e>0.00001){
    for(n=0;n<=(tempo-1);n++){
      T[n+1][0]=(2*r*(T[n+1][1]+T[n][1])+(2-2*r)*T[n][0])/(2+2*r);
       for(i=1;i<=(M-1);i++)
      {
         temp=(r*(T[n][i-1]+T[n][i+1]+T[n+1][i-1]+T[n+1][i+1])+(2-2*r)*T[n][i])/(2+2*r);
         if( fabs( temp-T[n+1][i] )>max){
            max=fabs(temp-T[n+1][i]);
            e=( fabs(temp-T[n+1][i]) / fabs(temp) );
         }//fim if
         T[n+1][i]=temp;
      }//fim for i
      T[n+1][M]=(2*r*(T[n][M-1]+T[n+1][M-1])+(2-2*r)*T[n][M])/(2+2*r);
     }//fim  for n
     max=0;
   }//fim while

   if((fp=fopen("dadosFluxoCRICTETSTE.txt","w"))==NULL)
        printf("Erro na criação de dados.txt");


   for(n=0;n<=(tempo);n++)
   {
     i=M;//for(i=0;i<=M;i++)
      {

         for(nu=1;nu<=1000;nu++)//para ter a série
         {
          ta=(ta+(-2*sin(1)*pow(-1,nu)*exp(-nu*nu*PI*PI*a*n*Dt)*cos(nu*PI*i*Dx))/((-1+nu*PI)*(1+nu*PI)));
         }
         fprintf(fp,"%3.6f  %3.6f ",T[n][i] ,ta+sin(1));

         ta=0;

      }

      fprintf(fp,"\n");
   }
          fclose(fp);
      system("PAUSE");
      return 0;
}
