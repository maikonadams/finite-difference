
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main()
{
  double  l[50], Dt, i[50], R,E,N,A, L[12],I[12],D,lc,PI=3.141592654;
  double B[12]={0.01,0.05,0.1,0.2,0.5,0.75,1.0,1.2,1.3,1.4,1.5,1.6};
  double H[12]={1.1,2.9,4.5,6.4,9.6,12.4,16,22,27.6,37,55,116};
  int k,t,c;
  FILE *fp;
  FILE *fp2;

  /*-----------------Definindo as constantes---------------------*/
  E=2.0;       /*Tensão Interna*/
  D=1.5E-2;    /*Diametro Médio*/
  R=(D/2.0);   /*Raio Médio*/
  lc=2.0*PI*R; /*Comprimento Médio*/
  N=1500;      /*Número de Espiras*/
  A=0.2E-4;    /*Área de seção transversal */
  Dt=10E-6;     /*Passo de tempo*/
  t=40;         /*Número de Nós no tempo.*/

  /*-----------------Inicializando os vetores------------------*/
  for(k=0;k<t;k++){
   l[k]=0.0;
   i[k]=0.0;
  }

  /*-----------------Condições Iniciais-----------------------*/
  i[0]=0.0;
  l[0]=0.0;

  /*---------------Transformando de BxH para LxI---------------*/
  for(k=0;k<12;k++){
   L[k]=B[k]*N*A;
   I[k]=(H[k]*lc)/(N);
  }

  /*------------------------Interações no tempo---------------*/
  for(k=0;k<t;k++){
    l[k+1]=l[k]+(E-R*i[k])*Dt;
    /*logica para encontrar o intervalo de l em L*/
    /*percorre o vetor L para encontrar a corrente para esse*/
    for(c=0;c<12;c++)
     if (l[k+1]<L[0] ){
       i[k+1]=(I[0]/L[0])*l[k+1];
       c=12;
     }
     else if ((l[k+1]>L[c])&&(l[k+1]<L[c+1])){
       i[k+1]=I[c]+((I[c+1]-I[c])/(L[c+1]-L[c]))*(l[k+1]-L[c]);
       c=12;
     }
    else{
       printf("Extrapolou!/n");
       c=12;
       k=t;
    }
  }/*fim for*/


  /*resultados*/

  if((fp=fopen("curva.dat","w"))==NULL)
        printf("Erro na criação de dados.txt");

  /*if((fp=fopen("lamdba.dat","w"))==NULL)
        printf("Erro na criação de dados.txt");*/

   for(k=0;k<t;k++){
    /*printf("l->%.8f e i->%.8f \n",l[k],i[k]); */
    fprintf(fp,"%.8f    %.8f  \n",l[k],i[k]);
   /* fprintf(fp2,"%e \n",l[k]);   */
   }


  fclose(fp);
  /*fclose(fp2);      */

      system("PAUSE");
      return 0;
}
