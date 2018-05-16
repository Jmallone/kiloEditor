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
	raw.c_lflag &= ~(ECHO | ICANON); //Habilito o ECOAMENTO
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); //Mostro isso no terminal	
}

int main(){
	enableRawMode();
	
	char c;
	while(read(STDIN_FILENO, &c, 1) == 1 && c!= 'q'); //STDIN_FILENO LE O TECLADO
	return 0; 
}
