/*Exemplo de fscan.f() - fprintf() */
#include <stdio.h>
#include <io.h>
#include <stdlib.h>


#define NUM 10
#define xi 0
#define xf NUM-1


void main (void)
{
     FILE *fp;
     char s[80];
     int t[NUM+1][NUM+1] , d[NUM][NUM];
     int i,j,L,k,N=5;
     double p[NUM];
     double temp=1;
     
     if((fp=fopen("test02.txt","r"))==NULL){
       printf("O arquivo não pode ser aberto. \n");
       exit(1);
     }

     
     
     //inicializando o vetor interpolador
     for(i=0;i<NUM;i++)
     {
        p[i]=0; 
     }
     
     for(i=0;i<NUM;i++)
     {
                      fscanf(fp, "%d", &t[i][0]); /*lê do arquivo*/
                   
                      fprintf(stdout, " %d \n",  t[i][0]); /*imprime na tela */
     }
     
     printf("\n");
     
      printf("Imprimindo o vetor salvo em t ");
     
      printf("\n");
     /*imprimindo t*/
     for(i=0;i<NUM;i++)
     {
       printf("%d ",t[i][0]); 
     }
     
     printf("\n");
     printf("\n");
     
     /*calculo de d*/
     L=NUM;
     for(i=0;i<NUM;i++)
     {
        for(j=0;j<L;j++)
        {
         t[j][i+1]= (t[j+1][i]- t[j][i])/((i+j+1)-j );
        /* printf("%d= %d- %d \n",t[j][i+1],t[j+1][i],t[j][i]);*/
         
        }
      /*printf("-------------\n");*/
        L=L-1;
     }
     
     printf("\n");
     
     printf("Imprimindo o operador diferenças divididas ");
     
     printf("\n");
     
     
     L=NUM;
     for(i=0;i<NUM;i++)
     {
        for(j=0;j<L;j++)
        {
        printf("%d " ,t[j][i]);
        }
        L=L-1;
         printf("\n");
       
     }
     
     printf("\n");
     
     /*calculo dos pontos interpolados*/
     p[0]=t[0][0];//p(x0)=d0
     for(k=1;k<NUM;k++)//for para cada ponto q dv ser interpolado
     {
      p[k]=p[k]+p[0];//primeiro somatório q sempre acontece
      for(i=1;i<=k;i++)//for para o somatório
      {
       for(j=0;j<i;j++)//for para o produtório dos termos
       {
        
           temp=temp*(k-j); 
       }//j 
       temp=temp*(t[0][i]);
       p[k]=p[k]+temp;         
   
       temp=1;
       }//i
      }//k  
     
     
     
     for(i=0;i<NUM;i++)//vai até o 4, no 5 não entra
     {
       printf(" %f - %d \n", p[i],t[i][0]);              
     }
      
     
     
     
     system("PAUSE");
     
}
