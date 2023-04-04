
//  gcc pong.c -o pong -lncurses

#include <ncurses.h>
#include <unistd.h>

#define DELAY 60000

int main(int argc, char *argv[]) {

 int rows, cols;
 int x = 5, y = 0;
 int max_y = 25, max_x = 80;
 int next_x = 0;
 int directionx = 1;
 int next_y = 0;
 int directiony = 1;

 int x1 = 0, y1 = 0;
 int x2 = max_x, y2 = 0;
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
 
 mvwprintw(window, 10, 10, "una cadena");
 wrefresh(window);
 getch();

 //------------------------
 
 while(1) {
 	clear();
 	mvaddch(0, 39, p1);
 	mvprintw(0, 40, "-");
 	mvaddch(0, 41, p2);
 	mvprintw(y, x, "o");
 	mvprintw(y1, x1, "|\n|\n|\n|\n|");
 	mvprintw(y2, x2, "|\n");
 	mvprintw(y2+1, x2, "|\n");
 	mvprintw(y2+2, x2, "|\n");
 	mvprintw(y2+3, x2, "|\n");
 	mvprintw(y2+4, x2, "|\n");
 	refresh();

    ch = getch();
    
    switch(ch){
    case 's':
    	if(y1 < max_y) y1 += 1;  //esto no funciona bien
    	break;
    case 'w':
    	if(y1 > 0) y1 -= 1;
    	break;
    case 'l':
    	if(y2 < max_y) y2 += 1;
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

 	if (next_x >= max_x) {
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

 	if (next_y >= max_y || next_y < 0) {
 		directiony*= -1;
 	} else {
 		y+= directiony;
 	}
 	
 	if(puntua1==10 || puntua2==10){
  		endwin();
    		exit(0);
 	}
  
 }

 
}
