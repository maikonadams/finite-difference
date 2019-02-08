#include<string.h>
#include<time.h>
#include<stdio.h>
#include<conio.h>
#include<dos.h>
main()
{
   unsigned char dado_saida[10240],dado_entrada[10240];
   unsigned int i;
   FILE *arquivo;
   clock_t inicio,fim;

   arquivo = fopen("c:\\airton\\dados_saida.bin","rb");
   fread(dado_saida,1,10240,arquivo);
   fclose(arquivo);

   outp(0X27A,32);

   inicio=clock();
for(i=0;i<10240;i++)
	{
	outp(0X378,dado_saida[i]);
	dado_entrada[i]=inportb(0X278);
	}
   fim=clock();

   arquivo = fopen("c:\\airton\\dados_lidos.bin","wb");
   fwrite(dado_entrada,1,10240,arquivo);
   fclose(arquivo);
   clrscr();
   float tempo_total,tempo_amostragem;
   tempo_total=(fim-inicio)/CLK_TCK;
   tempo_amostragem=tempo_total/10240;

   printf("O tempo foi de: %1.15f\n",tempo_total);
   printf("\nO tempo entre amostras foi de: %1.15f\n",tempo_amostragem);

   arquivo = fopen("c:\\airton\\tempos.txt","w+");
   fprintf(arquivo,"Tempo decorrido: %1.15f\nTempo amostragem: %1.15f",tempo_total,tempo_amostragem);
   fclose(arquivo);

   getch();

return 0;
}

