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
   float Dx,Dt,a,r,L,e=1,temp,PI=3.141592654;
   double T[1000][1000],ta=0,TI[1000][1000],TCN[1000][1000],max=0;
   int i,n,tempo,nu,M;
   char string[128],string2[128];

   tempo=800;
   L=1;//fronteira em x
   M=50;//número de equações
   a=1.4;
   Dx=L/M;
   Dt=(Dx*Dx)/(2*a);//condição necessária para estabilidade
   //Dt=Dx/10000;

   r=(a*Dt)/(Dx*Dx);

   //matriz chute inicial
   for(n=0;n<=tempo;n++)
      for(i=0;i<=M;i++){
         TI[n][i]=0;
         TCN[n][i]=0;
      }

   //Condição inicial
   for(i=0;i<=M;i++){
      T[0][i]=i*Dx;
      TI[0][i]=i*Dx;
      TCN[0][i]=i*Dx;
   }

   //Condições de Fronteira
   for(n=0;n<=tempo;n++){
      T[n][0]=0;   TI[n][0]=0;   TCN[n][0]=0;//Fronteira Inicial
      T[n][M]=0;   TI[n][M]=0;   TCN[n][M]=0;//Fronteira Final
   }

   //----------------------Simples Metodo Explicito---------------
   //a restrição do tempo é unicamente para ter um limite de exibição
   for(n=0;n<=(tempo-1);n++){
      for(i=1;i<=(M-1);i++){
               T[n+1][i]=r*T[n][i-1]+(1-2*r)*T[n][i]+r*T[n][i+1];
      }//for i
   }//for n

   //---------------------Simples Metodo Implicito
   //a restrição do tempo é unicamente para ter um limite de exibição
   while(e>0.00001){
     for(n=0;n<=(tempo-1);n++){
      for(i=1;i<=(M-1);i++)
      {
         temp=(1/(1+2*r))*TI[n][i]+(r/(1+2*r))*(TI[n+1][i-1]+TI[n+1][i+1]);
         if( fabs( temp-TI[n+1][i] )>max){//guardar o maior valor da interação
            max=fabs(temp-TI[n+1][i]);
            e=( fabs(temp-TI[n+1][i]) / fabs(temp) );//guardar o maior erro relativo
         }//fim if
         TI[n+1][i]=temp;
      }//fim for i
     }//fim  for n
     max=0;
   }//fim while

   max=0;
   e=1;
   temp=0;
   //---------------------------Método de Crank-Nicolson
   //a restrição do tempo é unicamente para ter um limite de exibição
   while(e>0.00001){
    for(n=0;n<=(tempo-1);n++){
      for(i=1;i<=(M-1);i++)
      {
         temp=(r*(TCN[n][i-1]+TCN[n][i+1]+TCN[n+1][i-1]+TCN[n+1][i+1])+(2-2*r)*TCN[n][i])/(2+2*r);
         if( fabs( temp-TCN[n+1][i] )>max){
            max=fabs(temp-TCN[n+1][i]);
            e=( fabs(temp-TCN[n+1][i]) / fabs(temp) );
         }//fim if
         TCN[n+1][i]=temp;
      }//fim for i
     }//fim  for n
     max=0;
   }//fim while

   if((fp=fopen("dadoscomparativos2.txt","w"))==NULL)
        printf("Erro na criação de dados.txt");

   //fprintf(fp,"Explicito Implicito CrankNicolson Analítico\n");
   for(n=0;n<=tempo;n++)
   {
     i=M/2;//for(i=0;i<=M;i++)
      {
       //if( (n==0)||(n==tempo/2)||(n==tempo)){
         for(nu=1;nu<=10000;nu++)//para ter a série
         {
            ta=ta+( (-2)*( pow(-1,nu)*exp(-nu*nu*PI*PI*a*n*Dt)*sin(nu*PI*i*Dx))/(nu*PI)  );
         }

         fprintf(fp,"%3.6f  %3.6f  %3.6f  %3.6f",T[n][i] , TI[n][i], TCN[n][i],ta);

         ta=0;
      }
      fprintf(fp,"\n");
     //  }//fim if
   }
   fclose(fp);

      system("PAUSE");
      return 0;
}
