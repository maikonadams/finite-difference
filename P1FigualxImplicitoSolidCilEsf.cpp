/* O problema eh o seguinte : D^2T/Dx^2=DT/Dt para 0<x<1 , t>0
            Fronteira Inicial T=0 para x=0, t>0
            Fronteira Final   T=0 para x=1, t>0
            Condi��o Inicial  T=x para t=0, 0<=x<=1.

*/

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

main()
{
   float d,Dt,a,r,L,e=1,temp;
   double T[30][30],ta=0,max=0;
   int i,n,tempo,nu,M,p;

   tempo=20;
   L=1;//fronteira
   M=10;//n�mero de equa��es
   a=1.4;
   d=L/M;
   Dt=d/1;
   r=((a*Dt)/(d*d));
   p=2; //p=1 "cilindro" e p=2 "esfera"

   //matriz chute inicial
   for(n=0;n<=tempo;n++)
      for(i=0;i<=M;i++)
         T[n][i]=0;



   for(i=0;i<=M;i++)//preenchendo com a condi��o inicial
   {
      T[0][i]=i*d;
   }

   for(n=1;n<=tempo-1;n++)//preenchendo as condi��es de fronteira
   {
      T[n][M]=0;//Condi��o de Fronteira Final
   }

   //a restri��o do tempo � unicamente para ter um limite de exibi��o
while(e>0.00001){
   for(n=0;n<=(tempo-1);n++){
      for(i=1;i<=(M-1);i++)
      {
       if(i==1){
          temp=(r*((1-p/(2*i))*(((r*2*(1+p))*T[n+1][1]+T[n][0])/(1+2*r*(1+p))+T[n][0]) + (1+p/(2*i))*T[n+1][i+1])+T[n][i])/(1+2*r);
       }
       else {
          temp=(r*((1-p/(2*i))*T[n+1][i-1] + (1+p/(2*i))*T[n+1][i+1])+T[n][i])/(1+2*r);
       }
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
     i=0;// for(i=0;i<=M;i++)
      {
         printf("%3.4f ",T[n][i]);

      }
      printf("\n");
   }

      system("PAUSE");
      return 0;
}
