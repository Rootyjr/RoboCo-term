#include "robco.h"

void slowType(int row, int col, char * string, int delay){
	move(row,col);
	for(int ch = 0; ch < strlen(string); ch++){
        //printw("%s",string);
        addch(string[ch]);
		refresh();
		usleep(delay);
	}
}

int printLogin(char ** array, int highy, int highx, int line, int usedelay){
    int c_delay;
    int ahighx = highx;
    int ahighy = highy;
    int bhighx = highx;
    int bhighy = highy;
    
    if(usedelay){
        c_delay = CH_DELAY;
    }
    else{
        c_delay = 0;
    }
    
    char highlight = array[highy][highx];
    if (array[highy][highx] == '<' || '(' || '[' || '{'){
        for(int x = highx; x<=H_ARRAY; x++){
            if(highlight == '<' && array[highy][x] == '>'){
                ahighx = x;
                break;
            }
            else if(highlight == '(' && array[highy][x] == ')'){
                ahighx = x;
                break;
            }
            else if(highlight == '[' && array[highy][x] == ']'){
                ahighx = x;
                break;
            }
            else if(highlight == '{' && array[highy][x] == '}'){
                ahighx = x;
                break;
            }
        }
    }
    
    if (array[highy][highx] >= 65 && array[highy][highx] <= 97){
        int a = 1;
        int x = highx;
        int y = highy;
        while (a){
            if (array[y][x] >= 65 && array[y][x] <= 90){
                bhighx=x;
                bhighy=y;
                if(x==0){
                    y--;
                    x=11;
                } else{
                    x--;
                }
            }
            else{
                a=0;
            }
        }
        a=1;
        x = highx;
        y = highy;
        while (a){
            if (array[y][x] >= 65 && array[y][x] <= 90){
                ahighx=x;
                ahighy=y;
                if(x==11){
                    y++;
                    x=0;
                } else{
                    x++;
                }
            }
            else{
                a=0;
            }
        }
    }
    
    for(int y = 0; y<V_ARRAY; y++){
		char hex[5];
		sprintf(hex, "%04x", line);
		for(int i = 0;i<strlen(hex);i++){
			hex[i] = toupper(hex[i]);
		}
		char finalhex[8];
		sprintf(finalhex, "0x%4s", hex);
		line = line+12;
		if(y < (V_ARRAY/2)){
			slowType(6+y,0, finalhex,c_delay);
			for(int x = 0; x<H_ARRAY; x++){
				char oneChar[] = {array[y][x],'\0'};
				char * charPtr = oneChar;                
                if((x >= bhighx && y == bhighy && (x <= ahighx || y < ahighy) && y <= ahighy) || (y > bhighy && x <= ahighx && y <= ahighy)){
                    attron(A_REVERSE);
                }
				slowType(6+y,7+x,charPtr, c_delay);
                //if(x <= ahighx && y <= ahighy){
                    attroff(A_REVERSE);
                //}
			}
		}
		else{
			slowType(6+y-(V_ARRAY/2),H_ARRAY+8,finalhex,c_delay);
			for(int x = 0; x<H_ARRAY; x++){
				char oneChar[] = {array[y][x],'\0'};
				char * charPtr = oneChar;
                if((x >= bhighx && y == bhighy && (x <= ahighx || y < ahighy) && y <= ahighy) || (y > bhighy && x <= ahighx && y <= ahighy)){
                    attron(A_REVERSE);
                }
				slowType(6+y-(V_ARRAY/2), (H_ARRAY+(15))+x,charPtr, c_delay);
                
                //if(x <= ahighx && y <= ahighy){
                    attroff(A_REVERSE);
                //}
			}
		}
	}
    char oneString[] = {'>',array[highy][highx],'\0'};
    char * stringPtr = oneString;
    slowType((V_ARRAY/2)+5, H_ARRAY*3+4,stringPtr, CH_DELAY);
    attron(A_REVERSE);
    addch(' ');
    attroff(A_REVERSE);
    
    return 1;
}
