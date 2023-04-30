
//  gcc pong.c -o pong -lncurses

#include <ncurses.h>
#include <unistd.h>

#define DELAY 60000

int main(int argc, char *argv[]) {

 int rows, cols;
 int x = 5, y = 0;
 int puntuacion=0;
 int next_x = 0;
 int directionx = 1;
 int next_y = 0;
 int directiony = 1;

 int y1 = 0, y2 = 0;
 int ch = 0;
 
 int puntua1=0, puntua2=0;
 char p1='_', p2='_';

 initscr();
 noecho();
 cbreak();
 curs_set(FALSE);
 nodelay(stdscr, TRUE);
 
 if (has_colors() == FALSE) {
    	endwin();
    	printf("Your terminal does not support color\n");
    	exit(1);
	}
 
 //---PANTALLA DE INICIO---

 start_color();
 init_pair(1, COLOR_WHITE, COLOR_BLUE);
 clear();
 
 refresh();
 getmaxyx(stdscr, rows, cols); 
 WINDOW *window = newwin(rows,cols,0,0);
 wbkgd(window, COLOR_PAIR(1));
 box(window, '|', '-'); 
 
 mvwprintw(window, rows/2-6, cols/2, "PONG");
 mvwprintw(window, rows/2-5, cols/2-7, "J1 - teclas w y s");
 mvwprintw(window, rows/2-4, cols/2-7, "J2 - teclas o y l");
 
 mvwprintw(window, rows/2, cols/2-24, "Elige el nivel de dificultad (predefinido en medio)");
 mvwprintw(window, rows/2+1, cols/2-10, "Tecla f: facil(3 puntos)");
 mvwprintw(window, rows/2+2, cols/2-10, "Tecla m: medio(5 puntos)");
 mvwprintw(window, rows/2+3, cols/2-12, "Tecla d: dificil(10 puntos)");
 wrefresh(window);
 ch = getchar();
 switch(ch){
 case 'f':
 	puntuacion=3;
 	break;
 case 'd':
 	puntuacion=10;
 	break;
 default:
 	puntuacion=5;
 };
 clear();

 //------------------------
 
 while(1) {
 	refresh();
 	getmaxyx(stdscr, rows, cols); 
	WINDOW *window = newwin(rows,cols,0,0);
	//marcador
 	mvaddch(0, cols/2-1, p1);
 	mvprintw(0, cols/2, "-");
 	mvaddch(0, cols/2+1, p2);
	//pelota
 	mvprintw(y, x, "o");
 	//pala J1
 	mvprintw(y1, 0, "|");
 	mvprintw(y1+1, 0, "|");
 	mvprintw(y1+2, 0, "|");
 	mvprintw(y1+3, 0, "|");
 	mvprintw(y1+4, 0, "|");
 	//pala J2
 	mvprintw(y2, cols-1, "|");
 	mvprintw(y2+1, cols-1, "|");
 	mvprintw(y2+2, cols-1, "|");
 	mvprintw(y2+3, cols-1, "|");
 	mvprintw(y2+4, cols-1, "|");
 	wrefresh(window);

    ch = getch();
    
    switch(ch){
    case 's':
    	if(y1 < rows-5) y1 += 1; 
    	break;
    case 'w':
    	if(y1 > 0) y1 -= 1;
    	break;
    case 'l':
    	if(y2 < rows-5) y2 += 1;
    	break;
    case 'o':
    	if(y2 > 0) y2 -= 1;
    	break;
    case 'q':
    	endwin();
    	exit(0);
    	break;
    case 'p':
    	//pausa
    	getchar();
    };
 	
 	usleep(DELAY);

 	next_x = x + directionx;
 	next_y = y + directiony;

 	if (next_x >= cols) {
 		directionx*= -1;
 		if(next_y == y2 || next_y == y2+1 || next_y == y2+2 || next_y == y2+3 || next_y == y2+4){
 			
 		} else{
 			puntua1++;
 			p1= puntua1 + '0';
 		}
 	} else {
 		x+= directionx;
 	}
 	
 	if(next_x < 0){
 		directionx*= -1;
 		if(next_y == y1 || next_y == y1+1 || next_y == y1+2 || next_y == y1+3 || next_y == y1+4){
 			
 		} else{
 			puntua2++;
 			p2= puntua2 + '0';
 		}
 	} else {
 		x+= directionx;
 	}

 	if (next_y >= rows || next_y < 0) {
 		directiony*= -1;
 	} else {
 		y+= directiony;
 	}
 	
 	if(puntua1==puntuacion || puntua2==puntuacion){
 		endwin();
    		exit(0);
 	}
 }

 
}
