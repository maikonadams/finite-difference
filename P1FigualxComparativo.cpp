/* O problema eh o seguinte : D^2T/Dx^2=DT/Dt para 0<x<1 , t>0
            Fronteira Inicial T=0 para x=0, t>0
            Fronteira Final   T=0 para x=1, t>0
            Condição Inicial  T=x para t=0, 0<=x<=1.

A soluçao exata eh T(x,t)=Sum((-2*(-1)^n*exp(-a*n^2*Pi^2*t)*sin(n*Pi*x)/(n*Pi) )  */

/*Esse Problema foi resolvido com os três métodos para fim d comparar os resultados
entre esses : 1- Crank-Nicolson (cn) ,
              2- Explicito (e) ,
              3- Implicito (i) ,
              4- Combinado (c) ;*/

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

main()
{
   float Dx,Dt,a,r,L,e=1,temp,Dte,re,tempi,t;
   double T[30][30][5],ta=0,max=0,maxi=0;
   int i,n,tempo,nu,M,o;

   tempo=10;
   L=1;//fronteira em x
   M=7;//número de equações
   a=1.4;
   Dx=L/M;
   Dte=(Dx*Dx)/(2*a);//condição necessária para estabilidade
   Dt=Dx/100;
   r=((a*Dt)/(Dx*Dx));
   re=((a*Dte)/(Dx*Dx));
   t=(1/2 - (Dx*Dx)/(12*a*Dt));


   //matriz chute inicial
   for(n=0;n<=tempo;n++)
      for(i=0;i<=M;i++)
      {
         T[n][i][1]=0;
         T[n][i][3]=0;
         T[n][i][4]=0;
      }



   for(i=0;i<=M;i++)//preenchendo com a condição inicial
     for(o=1;o<=4;o++)
        T[0][i][o]=i*Dx;


   for(n=1;n<=tempo-1;n++)//preenchendo as condições de fronteira
   {
      for(o=1;o<=4;o++)
      {
         T[n][0][o]=0;//Condição de Fronteira Inicial
         T[n][M][o]=0;//Condição de Fronteira Final
      }
   }

   //a restrição do tempo é unicamente para ter um limite de exibição
   for(n=0;n<=(tempo-1);n++)
      for(i=1;i<=(M-1);i++)
               T[n+1][i][2]=re*T[n][i-1][2]+(1-2*re)*T[n][i][2]+re*T[n][i+1][2];

//-------------------------------------Crank-Nicolson
   //a restrição do tempo é unicamente para ter um limite de exibição
while(e>0.00001){
   for(n=0;n<=(tempo-1);n++){
     //while(e>0.00001){
      for(i=1;i<=(M-1);i++)
      {
         temp=(r/(2+2*r))*T[n][i-1][1]+((2-2*r)/(2+2*r))*T[n][i][1]+(r/(2+2*r))*T[n][i+1][1]+(r/(2+2*r))*T[n+1][i+1][1]+(r/(2+2*r))*T[n+1][i-1][1];
         if( fabs( temp-T[n+1][i][1] )>max){
            max=fabs(temp-T[n+1][i][1]);
            e=( fabs(temp-T[n+1][i][1]) / fabs(temp) );
         }//fim if


         T[n+1][i][1]=temp;

      }//fim for i
     }//fim  for n
     max=0;



   }//fim while

   //----------------------------------------Implicito
  //a restrição do tempo é unicamente para ter um limite de exibição
  e=1;
  max=0;
  while(e>0.00001){
     for(n=0;n<=(tempo-1);n++){
      for(i=1;i<=(M-1);i++)
      {
         temp=(1/(1+2*r))*T[n][i][3]+(r/(1+2*r))*(T[n+1][i-1][3]+T[n+1][i+1][3]);
         if( fabs( temp-T[n+1][i][3] )>max){
            max=fabs(temp-T[n+1][i][3]);
            e=( fabs(temp-T[n+1][i][3]) / fabs(temp) );
         }//fim if

         T[n+1][i][3]=temp;

      }//fim for i
     }//fim  for n
     max=0;
   }//fim while

   //---------------------------------------Combinado
   //a restrição do tempo é unicamente para ter um limite de exibição
  e=1;
  max=0;
  while(e>0.00001){
   for(n=0;n<=(tempo-1);n++){
      for(i=1;i<=(M-1);i++)
      {
         temp=(r*t*(T[n+1][i-1][4]+T[n+1][i+1][4])+r*(1-t)*T[n][i-1][4]+(1-2*r*(1-t))*T[n][i][4]+r*(1-t)*T[n][i+1][4])/(1+2*r*t);
         if( fabs( temp-T[n+1][i][4] )>max){
            max=fabs(temp-T[n+1][i][4]);
            e=( fabs(temp-T[n+1][i][4]) / fabs(temp) );
         }//fim if

         T[n+1][i][4]=temp;

      }//fim for i
     }//fim  for n
     max=0;
   }//fim while



   printf("CrankN-Explicito-Implicito-Combinado-Resp.A \n");
   for(n=0;n<=tempo;n++)
   {
     i=3;// for(i=0;i<=M;i++)
      {
         for(nu=1;nu<=10000;nu++)//para ter a série
         {
            ta=ta+( (-2)*( pow(-1,nu)*exp(-nu*nu*3.14*3.14*a*n*Dt)*sin(nu*3.14*i*Dx))/(nu*3.14)  );
         }
         printf("%3.4f>%3.4f>%3.4f>%3.4f>%3.4f ",T[n][i][1],T[n][i][2],T[n][i][3],T[n][i][4],ta);
         ta=0;
      }
      printf("\n");
   }

      system("PAUSE");
      return 0;
}
