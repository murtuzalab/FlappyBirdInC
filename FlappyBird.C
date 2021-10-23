#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<time.h>

void render_canvas();
void reset();
void prepare_canvas(int,int);
void refresh();
void game_over();

char arr[15][30];
int wall_count=0;
int count=0,bird_row=7,game_over_flag=0;
char inp_key;

void main(){
	reset();
	randomize();
	render_canvas();
	getch();
	while(1){
		if(kbhit()){
			inp_key=getch();
		}
		if(inp_key==' '){
			if(bird_row>1){
				bird_row-=3;
			}
			inp_key='a';
		}
		if(inp_key=='q'){
			break;
		}
		if(game_over_flag!=1){
			if(bird_row>15){
				game_over();
			}else{
				prepare_canvas(bird_row,random(5)+4);
			}
		}else{
			break;
		}
		delay(150);
		refresh();
		count++;
		bird_row++;
	}
	game_over();
	getch();
}

void prepare_canvas(int bird_row,int gap_loc){
	int row, col;
	for(row=0;row<15;row++){
		for(col=0;col<30;col++){
			if(wall_count%8==0&&col==29){
        if(row>gap_loc-3&&row<gap_loc+3&&gap_loc-3>0&&gap_loc+3<15){
          arr[row][col]='=';
          arr[row][col-1]='=';
        }else{
          arr[row][col]='X';
          arr[row][col-1]='X';
        }
			}
		}
	}
	arr[bird_row][5]='B';
	render_canvas();
}

void refresh(){
	int row, col;
	for(row=0;row<15;row++){
		for(col=0;col<30;col++){
			if(col>0){
				if(col==29){
					arr[row][col]='=';
					if(row==14){
						wall_count++;
					}
				}else if(arr[row][col]=='B'){
          if(arr[row][col+1]!='X'){
            arr[row][col]='=';
            arr[row][col-1]='=';
          }
          else if(arr[row][col+1]=='X'||arr[row][col-1]=='X'||arr[row][col]=='X'||arr[row][col-2]=='X'){
            game_over();
            break;
          }
          arr[row][col]=arr[row][col+1];
				}else{
						arr[row][col]=arr[row][col+1];
				}
			}
		}
	}
	render_canvas();
}

void render_canvas(){
	int row, col;
	clrscr();
	textcolor(3);
	cprintf("                 M u r t u z a   L a b i b\r\n");
	for(row=0;row<15;row++){
		for(col=0;col<30;col++){
			textcolor(8);
			if(arr[row][col]=='o'||arr[row][col]=='B'){
				textcolor(6);
			}
			if(arr[row][col]=='X'){
				textcolor(7);
			}
			cprintf("%c ",arr[row][col]);
		}
		cprintf("\n\r");
	}
	textcolor(5);
	cprintf("Score = %d",wall_count/11);
}

void reset(){
	int row, col;
	clrscr();
	for(row=0;row<15;row++){
		for(col=0;col<30;col++){
				arr[row][col]='=';
		}
	}
}

void game_over(){
	int row, col;
	clrscr();
	textcolor(3);
	cprintf("                 M u r t u z a   L a b i b\r\n");
	for(row=0;row<15;row++){
		for(col=0;col<30;col++){
			textcolor(1);
			if(row==8&&col==0){
				textcolor(4);
				cprintf("                     G a m e  O v e r\r\n");
			}
			cprintf("%c ",arr[row][col]);
		}
		cprintf("\n\r");
	}
	textcolor(5);
	cprintf("Score = %d",wall_count/11);
	game_over_flag=1;
}