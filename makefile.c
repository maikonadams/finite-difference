#include <stdio.h>
#include <stdlib.h>

main()
{
      FILE *fp;
      int i;
      char letter;

      if((fp=fopen("ALPHABET.txt","w"))==NULL)
        printf("Erro na criação de ALPHABET.DAT");
      else
       {
         for(i=1;i<=5;++i)
         {
          for(letter='A';letter<='Z';++letter)
             putc(letter,fp);
          putc('\n',fp);/*grava caractere de nova linha*/
         }
        fclose(fp);
       }

      system("PAUSE");
      return 0;
}
