/* O problema eh o seguinte : D^2T/Dx^2=DT/Dt para 0<x<1 , t>0
            Fronteira Inicial T=0 para x=0, t>0
            Fronteira Final   T=0 para x=1, t>0
            Condi��o Inicial  T=x para t=0, 0<=x<=1.

A solu�ao exata eh T(x,t)=Sum((-2*(-1)^n*exp(-a*n^2*Pi^2*t)*sin(n*Pi*x)/(n*Pi) )  */

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

main()
{
   FILE *fp;
   float Dx,Dt,a,r,L,e=1,temp,PI=3.141592654;
   double T[1000][1000],ta=0,max=0;
   int i,n,tempo,nu,M;

   tempo=350;
   L=1;//fronteira em x
   M=50;//n�mero de equa��es
   a=1.4;
   Dx=L/M;
   //Dt=(Dx*Dx)/(2*a);//condi��o necess�ria para estabilidade
   Dt=Dx/10;
   r=((a*Dt)/(Dx*Dx));

   //matriz chute inicial
   for(n=0;n<=tempo;n++)
      for(i=0;i<=M;i++)
         T[n][i]=0;



   for(i=0;i<=M;i++)//preenchendo com a condi��o inicial
   {
      T[0][i]=i*Dx;
   }

   for(n=1;n<=tempo-1;n++)//preenchendo as condi��es de fronteira
   {
      T[n][0]=0;//Condi��o de Fronteira Inicial
      T[n][M]=0;//Condi��o de Fronteira Final
   }

   //a restri��o do tempo � unicamente para ter um limite de exibi��o
while(e>0.00001){
   for(n=0;n<=(tempo-1);n++){
     //while(e>0.00001){
      for(i=1;i<=(M-1);i++)
      {
         temp=(r*(T[n][i-1]+T[n][i+1]+T[n+1][i-1]+T[n+1][i+1])+(2-2*r)*T[n][i])/(2+2*r);
         if( fabs( temp-T[n+1][i] )>max){
            max=fabs(temp-T[n+1][i]);
            e=( fabs(temp-T[n+1][i]) / fabs(temp) );
         }//fim if
         T[n+1][i]=temp;
      }//fim for i
     }//fim  for n
     max=0;
   }//fim while

   if((fp=fopen("dadosTempCricte.txt","w"))==NULL)
        printf("Erro na cria��o de dados.txt");


   for(n=0;n<=tempo;n++)
   {
     i=M/2;// for(i=0;i<=M;i++)
      {
         for(nu=1;nu<=10000;nu++)//para ter a s�rie
         {
            ta=ta+( (-2)*( pow(-1,nu)*exp(-nu*nu*PI*PI*a*n*Dt)*sin(nu*PI*i*Dx))/(nu*PI)  );
         }
         fprintf(fp,"%3.6f %3.6f   ",T[n][i],ta);
         ta=0;
      }
      fprintf(fp,"\n");
   }
      fclose(fp);
      system("PAUSE");
      return 0;
}
