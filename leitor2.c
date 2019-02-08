//www.rogercom.com
//rogercom@rogercom.com
//-------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <conio.h>
#include <dos.h>
int main(void)
{
    unsigned char RetByte; //Para armazenar o valor recebido da Porta Paralela.
    while( ! kbhit( ) )           //Faz enquanto nenhuma tecla for pressionada.
    {
          RetByte = inportb(0x379);  //Ler um byte da Porta Paralela (0x379)LPT1.
              printf("%u\n",RetByte);
     }
}
