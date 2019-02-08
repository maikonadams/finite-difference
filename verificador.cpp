//#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
#define GPA 0x201 /*Porta Joystick I/O endere\c co*/
#define MASK2 0x10 /*Entradas Digitais*/
#define MASK7 0x20
#define MASK10 0x40
#define MASK14 0x80
main()
{
unsigned char x,y;
delay(0);
for(;;)
{
x = inportb(GPA); /*l\^e a porta*/
printf("\n\n");
if(x & MASK2)printf("Pino 2 aberto\n");
if(x & MASK7)printf("Pino 7 aberto\n");
if(!(x & MASK14))printf("Pino 14 fechado\n");
if(inportb(GPA) & MASK10)
{
printf("Pino 10 aberto\n");
}else{
printf("Pino 10 fechado\n");
}
delay(500);
}



      system("PAUSE");
      return 0;
}
