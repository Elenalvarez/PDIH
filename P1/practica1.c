#include <stdio.h>
#include <dos.h>

unsigned char color=15;
unsigned char fondo=0;

void mi_pausa(){
	union REGS inregs, outregs;
	inregs.h.ah = 8;
	int86(0x21, &inregs, &outregs);
}

void gotoxy(){
	union REGS inregs, outregs;
	inregs.h.ah = 0x02;
	inregs.h.dh = 0x00;
	inregs.h.dl = 0x00;
	inregs.h.bh = 0x00;
	int86(0x10, &inregs, &outregs);
}

void setcursortype(int tipo_cursor){
	union REGS inregs, outregs;
	inregs.h.ah = 0x01;
	switch(tipo_cursor){
		case 0: //invisible
			inregs.h.ch = 010;
			inregs.h.cl = 000;
			break;
		case 1: //normal
			inregs.h.ch = 010;
			inregs.h.cl = 010;
			break;
		case 2: //grueso
			inregs.h.ch = 000;
			inregs.h.cl = 010;
			break;
	}
	int86(0x10, &inregs, &outregs);
}
  
void setvideomode(unsigned char modo){
	union REGS inregs, outregs;
	inregs.h.ah = 0x00;
	inregs.h.al = modo;
	int86(0x10, &inregs, &outregs);
}

int getvideomode(){
	union REGS inregs, outregs;
	int modo;
	
	inregs.h.ah= 0X0F;
	int86(0x10, &inregs, &outregs);
	
	modo= outregs.h.al;
	return modo;
}

void textcolor(char c){
	color=c;
}

void textbackground(char f){	
	fondo=f;
}

void clrscr(){
	union REGS inregs, outregs;
	inregs.h.ah = 0x06;
	inregs.h.al = 0x00;
	inregs.h.bh = 0x00;
	inregs.h.ch = 0x00;
	inregs.h.cl = 0x00;
	inregs.h.dh = 0x25;
	inregs.h.dl = 0x80;
	int86(0x10, &inregs, &outregs);
}

void cputchar(char c){
	union REGS inregs, outregs;

	 inregs.h.ah = 9;
	 inregs.h.al = c;
	 inregs.h.bl = color;
	 inregs.h.bh = fondo;
	 inregs.x.cx = 1;
	 int86(0x10, &inregs, &outregs);
}

int getche(){
	union REGS inregs, outregs;
	int caracter;

	inregs.h.ah = 1;
	int86(0x21, &inregs, &outregs);

	caracter = outregs.h.al;
	return caracter;
}

void pixel(int x, int y, unsigned char C){
	union REGS inregs, outregs;
	inregs.x.cx = x;
	inregs.x.dx = y;
	inregs.h.al = C;
	inregs.h.ah = 0x0C;
	int86(0x10, &inregs, &outregs);
}

void dibujar(){
int color=0;
	int i;
	setvideomode(4);
	for(i=10; color<16; i=i+5){
		pixel(i, i, color);
		color++;
	}
}

int main(){
	
	int modo=getvideomode();
 	int letra=0;
	
	clrscr();
	mi_pausa();
 	setvideomode(3);
	printf("\nLimpiar pantalla");
	
	printf("\nModo de video:  ");
	cputchar((char)modo);
	mi_pausa();
	
	printf("\nMover cursor: ");
	gotoxy();
	mi_pausa();
	
	printf("\nCursor invisible: ");
   	setcursortype(0);
   	mi_pausa();
   	printf("\nCursor grueso: ");
   	setcursortype(2);
   	mi_pausa();
   	printf("\nCursor normal: ");
   	setcursortype(1);
   	mi_pausa();
 	
 	printf("\nPasando a modo de video: Gráfico ");
 	setvideomode(4);
   	pixel(10,50,1);
 	mi_pausa();
 	setvideomode(3);
 	mi_pausa();
 	
 	printf("\nPulsa una tecla...  ");
 	letra= getche();
 	printf("\nHas pulsado:  ");
 	cputchar((char)letra);
 	printf("\nHas pulsado en color rojo :");
 	textcolor(4);
 	cputchar((char)letra);
 	mi_pausa();
 	
 	dibujar();
 	mi_pausa();
 	setvideomode(3);
 	
 	return 0;
 	
}


