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
   float Dr,Dt,D12,e=1,rr,rz,ru,ru2,ru3,Dz,Lr,Lz,PI=3.14159265,temp,u,a;
   double C[100][100][300],max=0;
   int i,k,n,tempo,M,N;
   FILE *fp;

   tempo=20;
   Lr=11.2;//fronteira em x
   Lz=0.0002556;//fronteira em y
   M=10;//número de equações ou nós em R
   N=10;//número de equações ou nós em Z
   D12=0.000000009; //coeficiente de difusibilidade
   u=0.005;//velocidade de propagação
   //u=1.5;
   Dr=Lr/M;
   Dz=Lz/N;
  // Dt=(Dr*Dr*Dz*Dz)/(2*D12*(Dz*Dz+Dr*Dr));//condição necessária para estabilidade
  //Dt=1/(2*D12*(1/(Dr*Dr)+1/(Dz*Dz))+u/Dz);
  Dt=Dr/100;

   rr=(D12*Dt)/(Dr*Dr);
   rz=(D12*Dt)/(Dz*Dz);
   ru2=u/(2*Dz);
   ru3=u*(1-(M*M*Dr*Dr)/(a*a))/(2*Dz);

   //matriz chute inicial
   for(n=0;n<=tempo;n++)
    for(i=0;i<=M;i++)
     for(k=0;k<=N;k++)
      C[i][k][n]=0;

   for(i=0;i<=M;i++)//Condição inicial de um pulso no inicio da cilindro
     {
      k=1;
      C[i][k+1][0]=10;
      C[i][k][0]=10;
      C[i][k-1][0]=10;
     }

   for(n=1;n<=tempo;n++)//Condições da Fronteira no começo e fim do cilindro
   {
     for(i=0;i<=M;i++)
     {
      C[i][0][n]=0;//Fronteira Inicial
      C[i][N][n]=0;//Fronteira Final
     }
   }

while(e>0.0001){
 //a restrição do tempo é unicamente para ter um limite de exibição
 for(n=0;n<=(tempo-1);n++){
  // for(k=1;k<=(N-1);k++) {
  for(k=1;k<=(N-1);k++) {
    C[0][k][n+1]=((rr*C[1][k][n+1]+(rz/2+ru2)*C[0][k-1][n+1]+(rz/2-ru2)*C[0][k+1][n+1]+
                         rr*C[1][k][n]-(rr+rz-1)*C[0][k][n]+(rz/2+ru2)*C[0][k-1][n]
                         +(rz/2-ru2)*C[0][k+1][n] )/(rr+rz+1));

    for(i=1;i<=(M-1);i++){
      ru=u*Dt*( 1-(i*i*Dr*Dr)/(a*a) )/(2*Dz);
      temp=(((rr/2-rr/(4*i))*C[i-1][k][n+1]+(rr/2+rr/(4*i))*C[i+1][k][n+1]+
            (rz/2+ru)*C[i][k-1][n+1]+(rz/2-ru)*C[i][k+1][n+1]+
            (rr/2-rr/(4*i))*C[i-1][k][n]+(1-rr-rz)*C[i+1][k][n]+(rz/2+ru)*C[i][k-1][n]+
            (rz/2-ru)*C[i][k+1][n])/(rr+rz+1));//fim if else
      if(fabs(C[i][k][n+1]-temp)>max){
         max=fabs(C[i][k][n+1]-temp);
         e=fabs(C[i][k][n+1]-temp)/temp;
      }//fim if
      C[i][k][n+1]=temp;
    }//for i

     C[M][k][n+1]=(rr*C[M-1][k][n+1]+ rr*C[M-1][k][n]+(-rr-rz+1)*C[M][k][n]
                        +(rz/2+ru3)*C[M][k-1][n+1]
                        +(rz/2-ru3)*C[M][k+1][n+1]
                        +(rz/2+ru3)*C[M][k-1][n]
                        +(rz/2-ru3)*C[M][k+1][n])/(rr+rz+1);
     }//for k

   }//for n
   max=0;
}//fimwhile

if((fp=fopen("cilindro.txt","w"))==NULL)
        printf("Erro na criação de dados.txt");

   fprintf(fp,"CrankNicolson\n");

   
   //for(n=0;n<=(tempo);n++){
   for(n=0;n<=tempo;n++){
     for(i=0;i<=M;i++){
       //for(k=0;k<=N;k++){
       //k=(N-1);
       k=(N-1);
         //printf("%3.2f ",C[i][k][n]);
          fprintf(fp,"%3.6f ",C[i][k][n]);
         //printf("\n");
      // }//for j
       fprintf(fp,"\t");
   }//for i
   fprintf(fp,"\n");
   }//tempo

   fclose(fp);
      system("PAUSE");
      return 0;
}
