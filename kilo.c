/*** includes ***/

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#include <unistd.h>

/*** data ***/

struct termios orig_termios; 


/*** terminal ***/
void die(const char *s){
	perror(s);
	exit(1);

}

void disableRawMode(){
	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1){
		die("tcsetattr");
	} //Leio do teclado e coloco na struct
}

void enableRawMode(){
	if(tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tchetattr"); //Fazendo um Backup das COnfig do Terminal
	atexit(disableRawMode);

	struct termios raw = orig_termios; //Cria uma Struct do Tipo termios
	raw.c_iflag &= ~( BRKINT |ICRNL | INPCK| ISTRIP | IXON); //Arruma o CTRL+M , Desabilita o CTRL S, CTRL Q
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG); //Habilito o ECOAMENTO, Desativar o modo Canonio,Desativa o CTRL V,  Desativar as teclas CTRL Z - CTRL_C
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
 
	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr"); //Mostro isso no terminal	
}

/*** init ***/

int main(){
	enableRawMode();
	
	while(1){
		char c = '\0';
		if(read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) die("read");
		if(iscntrl(c)){		//Verifica se 'e um char printavel
			printf("%d \r \n", c);
		}else{
			printf("%d ('%c') \r \n", c, c);
		}
		if(c == 'q') break;	
	}
	return 0; 
}
