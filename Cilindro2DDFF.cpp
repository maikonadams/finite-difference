/* Temos um Cilindro em duas dimensões  */
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
main()
{
   float Dr,Dt,D12,a,e=1,rr,rz,ru,ru2,ru3,Dz,Lr,Lz,PI=3.14159265,temp,u;
   float C[100][100][600],max=0;
   int i,k,n,tempo,nu,M,N;

   FILE *fp;
   tempo=400;
   Lr=0.0002556;//comprimento do raio
   Lz=11.2;//comprimento do cilindro
   M=10;//número de equações ou nos em x
   N=10;//número de equações ou nós em z
   D12=0.000000002;
   a=0.0002556;
   u=0.005;

   Dr=Lr/M;
   Dz=Lz/N;

   Dt=2*D12/(u*u);


   rr=(D12*Dt)/(Dr*Dr);
   rz=(D12*Dt)/(Dz*Dz);
   ru2=(u*Dt)/Dz;
   ru3=((u*Dt)*(1-(M*M*Dr*Dr)/(a*a)))/Dz;

   //preenchendo a matriz com zeros
   for(n=0;n<=tempo;n++)
    for(i=0;i<=M;i++)
     for(k=0;k<=N;k++)
      C[i][k][n]=0;

   //-----------------------Condição Inicial-------------------

     for(i=0;i<=M;i++)
      {
       C[i][1][0]=10;
        C[i][0][0]=10;
       C[i][2][0]=10;
      }//fim for  i


   for(n=1;n<=tempo;n++)//Condições da Fronteira z=0 e z=N
   {
     for(i=0;i<=M;i++)
     {
      C[i][0][n]=0;//Fronteira Inicial
      C[i][N][n]=0;//Fronteira Final
     }
   }

  for(n=0;n<=(tempo-1);n++){
  for(k=1;k<=(N-1);k++)
   for(i=1;i<=(M-1);i++){


    // for(k=0;k<=N;k++)
    //i=0
    if(n==0) {
    ru=Dt*u*(1-(i*i*Dr*Dr)/(a*a))/(Dz);
    C[0][k][n+1]=4*rr*(C[1][k][n]-C[0][k][n])+rz*(C[0][k+1][n]-2*C[0][k][n]+C[0][k-1][n])
                 +C[0][k][n]-ru2*(C[0][k+1][n]-C[0][k-1][n]);

    //nós internos
    C[i][k][n+1]=C[i][k][n]+rr*(C[i+1][k][n]-2*C[i][k][n]+C[i-1][k][n])+
                 (rr/(2*i))*(C[i+1][k][n]-C[i-1][k][n])+
                 rz*(C[i][k+1][n]-2*C[i][k][n]+C[i][k-1][n])-
                 ru*(C[i][k+1][n]-C[i][k-1][n]);
    //fluxo nulo
    C[M][k][n+1]=2*rr*(C[M-1][k][n]-C[M][k][n])+rz*(C[M][k+1][n]-2*C[M][k][n]+C[M][k-1][n])
                  +C[M][k][n]-ru3*(C[M][k+1][n]-C[M][k-1][n]);
    }//fim do if
    else {
       Dt=1;
       ru=Dt*u*(1-(i*i*Dr*Dr)/(a*a))/(Dz);
       ru2=(u*Dt)/Dz;
       ru3=((u*Dt)*(1-(M*M*Dr*Dr)/(a*a)))/Dz;
       C[0][k][n+1]=(4*rr*(2*C[1][k][n]-C[0][k][n-1])
                     +2*rz*(C[0][k+1][n]-C[0][k][n-1]+C[0][k-1][n])
                     +C[0][k][n-1]-2*ru2*(C[0][k+1][n]-C[0][k-1][n]) )/(4*rr+2*rz+1);

       C[i][k][n+1]=((2*rr*(C[i+1][k][n]-C[i][k][n-1]+C[i-1][k][n])
                      +(rr/i)*(C[i+1][k][n]-C[i-1][k][n])
                      +2*rz*(C[i][k+1][n]-C[i][k][n+1]+C[i][k-1][n])
                      +C[i][k][n-1]-2*ru*(C[i][k+1][n]-C[i][k-1][n]))/(2*rr+2*rz+1));

       C[M][k][n+1]= (2*rr*(2*C[M-1][k][n]-C[M][k][n-1])
                     +2*rz*(C[M][k+1][n]-C[M][k][n-1]+C[M][k-1][n])
                     +C[M][k][n-1]-2*ru3*(C[M][k+1][n]-C[M][k-1][n]) )/(2*rr+2*rz+1);
    }//fim do else
   }//fim i
  }//fim n




if((fp=fopen("dadosDFF.txt","w"))==NULL)
        printf("Erro na criação de dados.txt");

   fprintf(fp,"Explicito Du Fort-Frankel\n");


   //for(n=0;n<=(tempo);n++){
   for(n=0;n<=tempo;n++){
     for(i=0;i<=M;i++){
       k=(N)/2;
          fprintf(fp,"%3.6f ",C[i][k][n]);

       fprintf(fp,"\t");
   }//for i
   fprintf(fp,"\n");
   }//tempo

   fclose(fp);
      system("PAUSE");
      return 0;
}
