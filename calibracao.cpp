#include<string.h>
#include<stdio.h>
#include<conio.h>
#include<dos.h>
main()
{
outp(0X27A,32);
while(!kbhit())
	{
	printf("\n   %d",inportb(0X278));
	}
return 0;



      system("PAUSE");
      return 0;
}
