#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#include <unistd.h>

struct termios orig_termios; 

void disableRawMode(){
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios); //Leio do teclado e coloco na struct
}

void enableRawMode(){
	tcgetattr(STDIN_FILENO, &orig_termios); //Fazendo um Backup das COnfig do Terminal
	atexit(disableRawMode);

	struct termios raw = orig_termios; //Cria uma Struct do Tipo termios
	raw.c_lflag &= ~(IXON); //Desabilita o CTRL S, CTRL Q
	raw.c_lflag &= ~(ECHO | ICANON | ISIG); //Habilito o ECOAMENTO, Desativar o modo Canonio, Desativar as teclas CTRL Z - CTRL_C
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); //Mostro isso no terminal	
}

int main(){
	enableRawMode();
	
	char c;
	while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q'){
		if(iscntrl(c)){		//Verifica se 'e um char printavel
			printf("%d\n", c);
		}else{
			printf("%d ('%c')\n", c, c);
		}	
	} //STDIN_FILENO LE O TECLADO
	return 0; 
}
