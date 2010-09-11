#include <data_types.h>
#include <k_printf.h>
#include <exceptions.h>

void fault(u_char int_num)
{
	if(int_num == 0x0E) // page fault
	{
		k_printf("PAGE FAULT!!!!!!!!!");
	}
	else
	{
		k_printf("%d", int_num);
		panic("System fault...  You need to restart your computer.");
		asm("cli");
		asm("hlt");
	};
	outportb(0x20, 0x20);
};

unsigned int panic(char *message)
{
	char *vidmem = (char *) 0xb8000;

	unsigned int i=0;
	unsigned int line=0;

	i=(line*80*2);

	while(*message!=0)
	{
		vidmem[i]=*message;
		*message++;
		i++;
		vidmem[i]=0x9; // use blue text
		i++;
	};
	return(1);
};