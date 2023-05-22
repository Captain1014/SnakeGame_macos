/* 
///////////////////////////////////////////////////////////
   SNAKE GAME FOR MACOS
            got ideas from @10sabana

    "Snake Game" only operated on the Mac OS
    If you want to compile this file, you need to use Command
                        -> gcc -o snakegame snakegame.cpp -lncurses

    * Need to revise : time count
    ** According to the score, show prize and penalty
///////////////////////////////////////////////////////////
*/
#include <iostream>
#include <cstdlib>
#include <ncurses.h> // input and output
#include <unistd.h> // sleep function

// Global variables
bool gameOver;
const int width = 20;
const int height = 20;
int x,y; // the head of snake
int fruitX, fruitY;
int score;

typedef enum DIRECTION {STOP = 0, LEFT, RIGHT, UP, DOWN}
Dir;
Dir dir;

// Snake tail
int tailX[50], tailY[50];
int numTail = 0;

void Initialize(){
    // Shell Screen Init, functions from ncurses.h
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);

    gameOver = false;
    dir = STOP;
    x = width/2;
    y = height/2;
    // fruitX = (rand() % width) + 1;
    // fruitY = (rand() % height) + 1;
    fruitX = (rand() % (width - 2)) + 1; // Generate fruitX between 1 and width-2
    fruitY = (rand() % (height - 2)) + 1; // Generate fruitY between 1 and height-2

    score = 0;
}

void Render(){

    clear();
    // Draw map, snake head, fruit, and tail
    for(int i = 0; i<height+2; i++){
        for(int j = 0; j<width+2; j++){
            // Draw map

            if(i==0 | i==21){
                mvprintw(i, j, "0");
            }
            else if (j==0 | j==21){
                mvprintw(i, j, "0");
            }
            // Draw snake head
            else if(i==y && j==x){
                mvprintw(i,j,"0");
            }
            // Draw fruit
            else if (i == fruitY && j == fruitX){
                mvprintw(i,j,"@");
            }
            else{
                // Draw tail
                for(int k = 0; k<numTail; k++){
                    if(tailX[k]==j && tailY[k]==i){
                        mvprintw(i,j,"o");
                    }
                }
            }
        }
    }
    // Draw information
    mvprintw(3, 29, "------------------------------------");
    mvprintw(4, 29, "|    Snake Game Made by leah     |");
    mvprintw(5, 29, "------------------------------------");
    mvprintw(7, 29, "Use direction keys to eat fruit");
    mvprintw(9, 43, "   ^ ");
    mvprintw(10, 43, "<  v  >");
    mvprintw(14, 29, "** Goal: 5 scores ");

    mvprintw(16, 29, "$$ Score = %d", score);
    //mvprintw(17, 29, "$$ Remain Time = %d", current_time);

    // Print the ASCII art when the score is 5
if (score == 5) {
    mvprintw(19, 29, "   YOU WON!                                 .''");
    mvprintw(20, 29, "       .''              *''*    :_\\/_:     .");
    mvprintw(21, 29, "      :_\\/_:   .     :.*_\\/_*   : /\\ :  .'.:.'.");
    mvprintw(22, 29, "  .''.: /\\ : _\\(/_  ':'* /\\ *  : '..'.  -=:o:=--");
    mvprintw(23, 29, " :_\\/_:'.:::. /)\\*''*  .|.* '.\\'/.' _\\(/_'.':'.");
    mvprintw(24, 29, " : /\\ : :::::  '*_\\/_* | |  -= o =-  /)\\    '  *");
    mvprintw(25, 29, "  '..'  ':::'   * /\\ * |'|  .'/\\.   '");
    mvprintw(26, 29, "      *        __*..* |  |     :      |.   |' .---\"|");
    mvprintw(27, 29, "       _*   .-'   '-. |  |     .--'|  ||   | _|    |");
}


    refresh();
}

void Poll_input(){
    keypad(stdscr, TRUE); // Check whether there is an input, function from ncurses
    halfdelay(1);

    int c = getch(); // Save the typed key

    switch(c){
        case KEY_LEFT:
            dir = LEFT;
            break;
        case KEY_RIGHT:
            dir = RIGHT;
            break;
        case KEY_DOWN:
            dir = UP;
            break;
        case KEY_UP:
            dir = DOWN;
            break;
        case KEY_EXIT:
            gameOver = true;
            break;
    }
}

void Update(){
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    // add new position and other one copy
    for (int i=1; i<numTail; i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;


        
    }

    switch(dir){
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y++;
            break;
        case DOWN:
            y--;
            break;
        default: 
            break;
    }


    //if snake goes outside from the map, snake dies
    if(x>width || x<1 || y<1 || y>height){
        gameOver = true;
    }

    //if snake eats the fruit, score inscreases

    if(x == fruitX && y == fruitY){

        score ++;
        fruitX = (rand() % width - 2) + 1;
        fruitY = (rand() % height -2 ) + 1;
        numTail++;
    }

    // for(int i = 0; i<numTail; i++){
    //     if(tailX[i] == x && tailY[i]==y){
    //         gameOver = true;
    //     }
    // }

   
}


int main(void)
{
    Initialize();

   while(!gameOver)
    {
        Render();
        Poll_input();
        Update();

    }
    getch();
    sleep(1); 
    endwin();

    return 0;
}