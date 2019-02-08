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
   float Dx,Dt,a,r,L,e=1,temp,PI=3.141592654,alpha=0.8,beta=0.9;
   double T[100][100],ta=0,max=0;
   int i,n,tempo,nu,M;

   tempo=20;
   L=1;//fronteira em x
   M=10;//número de equações
   a=1.4;
   Dx=L/M;
   //Dt=(Dx*Dx)/(2*a);//condição necessária para estabilidade
   Dt=Dx/10;
   r=((a*Dt)/(Dx*Dx));

   //matriz chute inicial
   for(n=0;n<=tempo;n++)
      for(i=0;i<=M;i++)
         T[n][i]=0;



   for(i=0;i<=M;i++)//preenchendo com a condição inicial
   {
      T[0][i]=i*Dx;
   }


   //a restrição do tempo é unicamente para ter um limite de exibição
while(e>0.00001){
   for(n=0;n<=(tempo-1);n++){
   //Temperatura na fronteira maior do q BETA, desligou
   if ((n>0)&&(T[n][M-1]>beta)){

      T[n][0]=0;//Condição de Fronteira Inicial
    //  T[n][M]=0;//Condição de Fronteira Final
   }
   //Temperatura na fronteira menor do q Alpha, ligou
   else if ((n>0)&&(T[n][M-1]<alpha)){

      T[n][0]=100;//Condição de Fronteira Inicial
     // T[n][M]=0;//Condição de Fronteira Final
   }
   else if ((n>0)&&((beta-T[n][M-1])<0.001)&&T[n][0]==0){  //desliga

      T[n][0]=0;//Condição de Fronteira Inicial
     // T[n][M]=0;//Condição de Fronteira Final
   }
   else if ((n>0)&&((T[n][M-1]-alpha)<0.001)&&T[n][0]==1){ //liga

      T[n][0]=100;//Condição de Fronteira Inicial
      //T[n][M]=0;//Condição de Fronteira Final
   }
      T[n][M]=0;//Condição de Fronteira Final
     //while(e>0.00001){
      for(i=1;i<=(M-1);i++)
      {
         temp=(r/(2+2*r))*T[n][i-1]+((2-2*r)/(2+2*r))*T[n][i]+(r/(2+2*r))*T[n][i+1]+(r/(2+2*r))*T[n+1][i+1]+(r/(2+2*r))*T[n+1][i-1];
         if( fabs( temp-T[n+1][i] )>max){
            max=fabs(temp-T[n+1][i]);
            e=( fabs(temp-T[n+1][i]) / fabs(temp) );
         }//fim if
         T[n+1][i]=temp;
      }//fim for i
     }//fim  for n
     max=0;


   }//fim while

   printf("Numerico->Analitico\n");
   for(n=0;n<=tempo;n++)
   {
     i=9;// for(i=0;i<=M;i++)
      {

        printf("%3.6f",T[n][i]);
      }
      printf("\n");
   }

      system("PAUSE");
      return 0;
}
