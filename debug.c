#include <stdio.h>
#include <time.h>
#include<unistd.h> 

int main(void)
{
	

	while(1){

		system("clear");
		char url[]="log.txt";
		char ch;
		FILE *arq;
	
		arq = fopen(url, "r");
		if(arq == NULL)
		    printf("Erro, nao foi possivel abrir o arquivo\n");
		else
		    while( (ch=fgetc(arq))!= EOF )
			putchar(ch);
			
		fclose(arq);
		sleep(1);
	}
	return 0;
}
