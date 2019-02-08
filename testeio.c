/*Escreve alguns dados não-caracteres em um arquivo em disco e lê 
 de volta*/
#include <stdio.h>
#include <stdlib.h>

void main(void)
{
     FILE *fp;
     double d=12.23;
     int i=101;
     long l=123023L;
     
     if((fp=fopen("teste123.txt","wb+"))==NULL){
        printf("O arquivo não pode ser aberto.\n");
        exit(1);
     }
     
     fwrite(&d, sizeof(double), 1, fp);
     fwrite(&i, sizeof(int), 1, fp);
     fwrite(&l, sizeof(long), 1, fp);
     
     rewind(fp);
     
     fread(&d, sizeof(double), 1, fp);
     fread(&i, sizeof(int), 1, fp);
     fread(&l, sizeof(long), 1, fp);
     
     printf("%f %d %ld", d, i, l);
     
     fclose(fp);
     
     return 0;
     
     system("PAUSE");
     
}
