/* O problema eh o seguinte : D^2T/Dx^2=DT/Dt para 0<x<1 , t>0
            Fronteira Inicial T=0 para x=0, t>0
            Fronteira Final   T=0 para x=1, t>0
            Condição Inicial  T=x para t=0, 0<=x<=1.

*/

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

main()
{
   float d,Dt,a,r,Lb,La,e=1,temp;
   double T[30][30],ta=0,max=0;
   int i,n,tempo,nu,M,p;

   tempo=20;
   La=0;//fronteira em x
   Lb=1;
   M=10;//número de equações
   a=1.4;
   d=(Lb-La)/M;
   Dt=d/1;
   r=((a*Dt)/(d*d));
   p=2; //p=1 "cilindro" e p=2 "esfera"

   //matriz chute inicial
   for(n=0;n<=tempo;n++)
      for(i=0;i<=M;i++)
         T[n][i]=0;



   for(i=0;i<=M;i++)//preenchendo com a condição inicial
   {
      T[0][i]=i*d;
   }

   for(n=1;n<=tempo-1;n++)//preenchendo as condições de fronteira
   {
      T[n][M]=0;//Condição de Fronteira Final
      T[n][0]=0;//Condição de Fronteira Inicial
   }

   //a restrição do tempo é unicamente para ter um limite de exibição
while(e>0.00001){
   for(n=0;n<=(tempo-1);n++){
      for(i=1;i<=(M-1);i++)
      {
         temp=( r*((1-p/(2*((La/d)+i)))*T[n+1][i-1]+(1+p/(2*((La/d)+i)))*T[n+1][i+1]) +T[n][i] )/(1+2*r);
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
     i=4;// for(i=0;i<=M;i++)
      {
         printf("%3.4f ",T[n][i]);

      }
      printf("\n");
   }

      system("PAUSE");
      return 0;
}
