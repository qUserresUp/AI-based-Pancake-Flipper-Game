#include <ncurses.h>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <algorithm>
#include "logic_unit.cpp"
using namespace std;

int n, diff;

int player_score;

vector<int> order;

string init_initial = "";

struct scores_vec {
    string initial;
    int score;
};
struct pancake_pos{

    int x, y;
    pancake_pos(int input_y, int input_x)
    {
        x = input_x;
        y = input_y;
    }
};
bool compareByLength(scores_vec a, scores_vec b)
{
    return a.score > b.score;
}
void draw_rec(int input_size, pancake_pos &p){

    attron(COLOR_PAIR(5));
    if(input_size != 0){
        attron(COLOR_PAIR(4));
    }
    int x = p.x;
    int y = p.y;
    int size = input_size;
    char width_char[] = "|";
    string length_string = "+";
    string size_string = to_string(size);
    for(int i = 0; i < size*2 - 1; i++)
    {
        length_string += '-';
    }
    length_string += "+";
    mvprintw(y, x, length_string.c_str());
    mvprintw(y + 1, x, width_char);
    mvprintw(y + 1, x + size, size_string.c_str());
    mvprintw(y + 1, x + size * 2, width_char);
    mvprintw(y + 2, x, length_string.c_str());


    refresh();

}
//==============================task5===========================



void move_pos_down(pancake_pos &p, int next_stack_size, int col){

    p.y += 3;

    if(p.x < col/2)
    {
        p.x =  ((col/2-(next_stack_size*2+1))/2);
    }

    else{
        p.x = (col/2-(next_stack_size*2+1))/2 + col/2;
    }

}
void draw_rec_animation(int input_size, pancake_pos &p,bool flag){

    attron(COLOR_PAIR(5));
    if(input_size != 0 && flag){
        attron(COLOR_PAIR(4));
    }
    int x = p.x;
    int y = p.y;
    int size = input_size;
    char width_char[] = "|";
    string length_string = "+";
    string size_string = to_string(size);
    for(int i = 0; i < size*2 - 1; i++)
    {
        length_string += '-';
    }
    length_string += "+";
    mvprintw(y, x, length_string.c_str());
    mvprintw(y + 1, x, width_char);
    mvprintw(y + 1, x + size, size_string.c_str());
    mvprintw(y + 1, x + size * 2, width_char);
    mvprintw(y + 2, x, length_string.c_str());


    refresh();

}



void draw_stack(vector<int> usr_order, vector<int> AI_order, vector<pancake_pos> &usr_position_vector, vector<pancake_pos> &AI_position_vector)
//This function takes four vectors as parameters, First parameter is used to draw the left stack, Second parameter is used to draw the right stack
//Third and fourth vectors are used to store the coordinates of each pancake
{
    initscr();                      // Start curses mode
    attron(COLOR_PAIR(4));
    clear();
    refresh();
    int row, col;
    getmaxyx(stdscr, row, col);
    usr_position_vector = {};                  //initialize usr_position_vector to empty vector
    AI_position_vector = {};                   //initialize AI_position_vector to empty vector
    int usr_first_panc_size = usr_order[0];
    int AI_first_panc_size = AI_order[0];
    int num_pancake = usr_order.size();
    pancake_pos usr_pos((row-num_pancake*3)/2, (col/2-(usr_first_panc_size*2+1))/2);        //find the coordinate for the top pancake of usr stack
    pancake_pos AI_pos((row-num_pancake*3)/2, (col/2-(AI_first_panc_size*2+1))/2+ col/2);   //find the coordinate for the top pancake of AI stack
    usr_position_vector.push_back(usr_pos);
    AI_position_vector.push_back(AI_pos);
    draw_rec(usr_first_panc_size, usr_pos);
    draw_rec(AI_first_panc_size, AI_pos);
    for(int i = 1; i < num_pancake; i ++){
        move_pos_down(usr_pos, usr_order[i], col); //find the coordinate for the next pancake of usr stack
        move_pos_down(AI_pos, AI_order[i], col);   //find the coordinate for the next pancake of AI stack
        usr_position_vector.push_back(usr_pos);
        AI_position_vector.push_back(AI_pos);
        draw_rec(usr_order[i], usr_pos);
        draw_rec(AI_order[i], AI_pos);}
}
void draw_stack_animation(vector<int> usr_order, vector<int> AI_order, vector<pancake_pos> &usr_position_vector, vector<pancake_pos> &AI_position_vector, bool flag)
//This function takes four vectors as parameters, First parameter is used to draw the left stack, Second parameter is used to draw the right stack
//Third and fourth vectors are used to store the coordinates of each pancake
{
    int row, col;
    getmaxyx(stdscr, row, col);
    usr_position_vector = {};                  //initialize usr_position_vector to empty vector
    AI_position_vector = {};                   //initialize AI_position_vector to empty vector
    int usr_first_panc_size = usr_order[0];
    int AI_first_panc_size = AI_order[0];
    int num_pancake = usr_order.size();
    pancake_pos usr_pos((row-num_pancake*3)/2, (col/2-(usr_first_panc_size*2+1))/2);        //find the coordinate for the top pancake of usr stack
    pancake_pos AI_pos((row-num_pancake*3)/2, (col/2-(AI_first_panc_size*2+1))/2+ col/2);   //find the coordinate for the top pancake of AI stack
    usr_position_vector.push_back(usr_pos);
    AI_position_vector.push_back(AI_pos);
    draw_rec_animation(usr_first_panc_size, usr_pos,flag);
    draw_rec_animation(AI_first_panc_size, AI_pos,flag);
    for(int i = 1; i < num_pancake; i ++){
        move_pos_down(usr_pos, usr_order[i], col); //find the coordinate for the next pancake of usr stack
        move_pos_down(AI_pos, AI_order[i], col);   //find the coordinate for the next pancake of AI stack
        usr_position_vector.push_back(usr_pos);
        AI_position_vector.push_back(AI_pos);
        draw_rec_animation(usr_order[i], usr_pos,flag);
        draw_rec_animation(AI_order[i], AI_pos,flag);}


}
//==============================task5===========================
//to compile: g++-8.2.0 -std=c++2a -Wall -Wextra -pedantic -fsanitize=address,undefined,pointer-compare,pointer-subtract -fstack-clash-protection -g -fno-omit-frame-pointer mainChain.cpp -lncurses
void print_team_info(int y_offset, int row, int col){
    //prints the Team number, name, and members
    vector<char*> names = {(char*)"Sournav Sekhar Bhattacharya",(char*)"Samantha Hay",(char*)"Reid Jordan",(char*)"Zheng Fang"}; //Vector of names
    attron(COLOR_PAIR(4));

    mvprintw(row/2+y_offset,(col-strlen("TEAM 16: The Flippers"))/2,"TEAM 16: The Flippers");

    for(int i = 0;i<(int)names.size();i++){
        mvprintw(row/2+2+i+y_offset,(col-strlen(names[i]))/2,names[i]);
    }

    return;
}

void print_title(int y_offset, int row, int col){
    //prints the title in three different colors
    char title[]="PANCAKE SORTING GAME \n";
    attron(COLOR_PAIR(3));
    mvprintw(row/2-6+y_offset,(col-strlen(title))/2,"%s",title);

    attron(COLOR_PAIR(1));
    mvprintw(row/2-5+y_offset,(col-strlen(title))/2,"%s",title);

    attron(COLOR_PAIR(2));
    mvprintw(row/2-4+y_offset,(col-strlen(title))/2,"%s",title);
    return;
}

bool enter_button_color_change(bool blank,int y_offset, int row, int col){
    //changes the enter button to visible to not
    if(blank){//erases print
        attron(COLOR_PAIR(5));
        mvprintw(row/2+3+5+y_offset,(col-strlen("Press ENTER to start"))/2,"Press ENTER to start");
        blank = false;
        refresh();
    }
    else{//prints print
        attron(COLOR_PAIR(4));
        mvprintw(row/2+3+5+y_offset,(col-strlen("Press ENTER to start"))/2,"Press ENTER to start");
        blank = true;
        refresh();
    }
    // draws everything to screen
    usleep(500000);//half a second
    return blank;
}

void print_enter_button(int y_offset, int row, int col){
    //prints the enter button and waits for input, allows for blinking
    int pid = fork();
    int status;
    if(pid==0){ //child waits for enter key
        char key = 0;
        while(key != 10){
            key = getch(); //Wait for user input
        }
        exit(0);
    }
    else{//parent changes the color of the button, blinks
        bool phase = true;
        attron(A_DIM);
        while((waitpid(pid,&status,WNOHANG))<=0){
            attron(COLOR_PAIR(4));
            mvprintw(row/2+3+5+y_offset,(col-strlen("Press ENTER to start"))/2,"Press ENTER to start");
            refresh();
            phase = enter_button_color_change(phase,y_offset,row,col);
        }
        attroff(A_DIM);
    }
}

void print_game_info(int col){
    //prints the instructions for the game
    attron(COLOR_PAIR(4));
    clear();
    //puts all instructions into string
    string information = "SETUP:\n";
    information = information + ("1. When prompted choose the number of pancakes that will be in the stack: 2-9.\n");
    information = information + ("2. When prompted choose the difficulty level: 1-the number of pancakes chosen.\n");
    information = information + ("3. When prompted specify the initial order of the stack: random or list numbers 1-number of pancakes chosen in the order desired.\n");
    information = information + ("4. When prompted enter initials for score keeping.\n\n");
    information = information + ("HOW TO PLAY\n");
    information = information + ("1. Use the arrow keys (or \"WASD\") to move the cursor on the screen, move cursor to the lowest pancake to be flipped and press enter. The pancakes will blink and flip.\n");
    information = information + ("2. The computer will take its turn after the player.\n\n");
    information = information + ("HOW TO WIN\n");
    information = information + ("1. Order the stack of pancakes (largest pancake on top, smallest on the bottom) before the computer.\n");
    const char* print_out = information.c_str();
    mvprintw(1,(col-strlen("GAME INSTRUCTIONS"))/2,"GAME INSTURCTIONS");//title
    mvprintw(2,0,print_out);//instructions
    int x,y;
    getyx(stdscr,y,x);//gets cursor location
    mvprintw(y+1,(x+col-strlen("PRESS ANY KEY TO CONTINUE"))/2,"PRESS ANY KEY TO CONTINUE");
    refresh();


}
void draw_animation(vector<vector<int>> st,vector<vector<pancake_pos>> pan_st, int index){
    for(int i = 0; i<2; i++){
        for(int j = 0;j<index; j++){
            draw_rec(st[i][j], pan_st[i][j]);
        }
    }
}

void animation_setup(vector<vector<int>> &st){
    vector<int> order0 = {3,4,2,1};
    vector<int> order1 = {0,0,2,1};
    vector<int> order2 = {4,3,2,1};
    vector<int> order3 = {0,0,0,0};
    vector<int> order4 = {1,2,3,4};
    st = {order0,order1,order2,order3,order4};


}
bool animation_loop1(int i, int j,vector<vector<int>>st,vector<pancake_pos> pan_st,int pid2,int status2){
    draw_stack_animation(st[(0)+(i*2)],st[i*2], pan_st, pan_st,false);
    draw_stack_animation(st[(j%2)+(i*2)],st[i*2], pan_st, pan_st,true);
    if(!((waitpid(pid2,&status2,WNOHANG))<=0)){return false;}
    usleep(500000);
    if(!((waitpid(pid2,&status2,WNOHANG))<=0)){return false;}
    return true;
}
bool animation_cleanup1(int i,vector<vector<int>>st,vector<pancake_pos> pan_st,int pid2, int status2){
    draw_stack_animation(st[(0)+(i*2)],st[i], pan_st, pan_st,false);
    draw_stack_animation(st[(2*i)+2],st[2*i], pan_st, pan_st,true);
    draw_stack_animation(st[(2*i)+2],st[2*i], pan_st, pan_st,false);
    if(!((waitpid(pid2,&status2,WNOHANG))<=0)){return false;}
    return true;
}
bool animation_loop2(int i, int j,vector<vector<int>>st,vector<pancake_pos> pan_st,int pid2,int status2){
    draw_stack_animation(st[(2*i)+2],st[(0)+(i*2)], pan_st, pan_st,false);
    draw_stack_animation(st[(2*i)+2],st[(j%2)+(i*2)], pan_st, pan_st,true);
    if(!((waitpid(pid2,&status2,WNOHANG))<=0)){return false;}
    usleep(500000);
    if(!((waitpid(pid2,&status2,WNOHANG))<=0)){return false;}
    return true;
}
bool animation_cleanup2(int i,vector<vector<int>>st,vector<pancake_pos> pan_st,int pid2, int status2){
    draw_stack_animation(st[(2*i)+2],st[(0)+(i*2)], pan_st, pan_st,false);
    draw_stack_animation(st[(2*i)+2],st[(2*i)+2], pan_st, pan_st,true);
    if(!((waitpid(pid2,&status2,WNOHANG))<=0)){return false;}
    return true;
}
bool animation_end(vector<vector<int>>st,vector<pancake_pos> pan_st,int pid2, int status2){
    for(int i = 0; i<10; i++){
        if(!((waitpid(pid2,&status2,WNOHANG))<=0)){return false;}
        usleep(500000);
    }
    draw_stack_animation(st[4],st[4], pan_st, pan_st,false);
    return true;
}

void animation(int y_offset,int row,int col){
    int pid2 = fork();
    int status2;
    if(pid2==0){
        print_enter_button(y_offset,row,col);
        exit(1);}
    else{vector<vector<int>> st;
        vector<pancake_pos> pan_st;
        animation_setup(st);
        while(1){
            draw_stack_animation(st[0], st[0], pan_st, pan_st,true);
            if(!((waitpid(pid2,&status2,WNOHANG))<=0)){goto end;}
            for(int i = 0; i<2; i++){
                for(int j = 0;j<6; j++){
                    if(!animation_loop1(i,j,st,pan_st,pid2,status2)){goto end;}
                }
                if(!animation_cleanup1(i,st,pan_st, pid2,status2)){goto end;}
                for(int j = 0;j<6; j++){
                    if(!animation_loop2(i,j,st,pan_st,pid2,status2)){goto end;}
                }
                if(!animation_cleanup2(i,st,pan_st,pid2,status2)){goto end;}
            }
            if(!animation_end(st,pan_st,pid2,status2)){goto end;}
        }
    }end:;
}
void splash_screen(){
    //prints the title screen and instruction screen
    int row,col;
    initscr();  //Start Curses Mode
    curs_set(FALSE);//makes cursor invisible

    start_color();//Start color mode
    int y_offset=-3; //Y offset to output block

    //makes color choices
    init_pair(1, COLOR_WHITE, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_YELLOW);
    init_pair(3, COLOR_BLACK, COLOR_CYAN);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_BLACK, COLOR_BLACK);
    getmaxyx(stdscr,row,col);

    //calls functions for parts of title and instruction screens
    print_title(y_offset,row,col);//prints colorfuli
    print_team_info(y_offset,row,col);
    refresh();
    animation(y_offset,row,col);
    print_game_info(col);
    getch(); //Waits for user input

    endwin();
}
void print_high_scores( string initials, int col){
    fstream fs;
    fs.open("scores.txt",fstream::in | fstream::out | fstream::app);
    string x;

    //initscr();

    mvprintw(1,col/2-6,"%s","HIGH SCORES");
    int i=0;
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    string print = initials+" 000";
    while(getline(fs,x) && i<5){
        attron(COLOR_PAIR(1+i%2));
        mvprintw(3+i,(col-strlen(x.c_str()))/2,"%s",x.c_str());
        i+=1;
    }
    attron(COLOR_PAIR(1+i%2));
    mvprintw(3+i,(col-7)/2,"%s",print.c_str());
    mvprintw(10,(col-7)/2,"%s","");
    fs.close();
}
string get_initials(int row, int col){
    mvprintw(row-5,col/2-11,"%s","ENTER YOUR INITIALS \n");
    string initials = "";
    for(int i=0;i<3;i++){
        refresh();
        attron(COLOR_PAIR(5));
        initials += getch();
        attron(COLOR_PAIR(4));
        mvprintw(row-4,(col/2)-3,"%s",initials.c_str());
    }
    char temp2=0;
    while(temp2!=10){
        attron(COLOR_PAIR(5));
        temp2 = getch();
    }
    endwin();
    //cout<<initials<<endl;
    return initials;
}
string high_score_screen(){
    clear();
    refresh();
    int row,col;
    getmaxyx(stdscr,row,col);
    string initials = get_initials(row,col);

    attron(COLOR_PAIR(4));
    print_high_scores(initials,col);
    char temp2 = 0;
    while(temp2!=10){
        attron(COLOR_PAIR(5));
        temp2 = getch();
    }
    endwin();
    return initials;


}

//------------------------------TASK3----------------------

string randomize_first(string random1) {
    string randomize = random1;
    int row,col;
    getmaxyx(stdscr,row,col);
    string inputted;
    while (randomize != "y" && randomize != "n") {
        clear();
        randomize = "";
        mvprintw(row/2-1,col/2-25,"%s","Must be y or n");
        mvprintw(row/2,col/2-25,"%s","Would you like to choose the order? (y or n) ");
        refresh();
        inputted = getch();
        randomize += inputted;
    }
    return randomize;
}

int prompt_user_invalid(int x, int i) {
    int j = x;
    int row,col;
    getmaxyx(stdscr,row,col);
    clear();
    mvprintw(row/2-1,col/2-25,"%s","Invalid Pancake");
    while (!(1 <= j && j <= n)) {
        mvprintw(row/2,col/2-25,"Pancake size of %d position (1(Top)-%d): ",i+1,n);
        string initials = "";
        refresh();
        initials += getch();
        if (initials == "0" || initials == "1" || initials == "2" || initials == "3" || initials == "4" || initials == "5" || initials == "6" || initials == "7" || initials == "8" || initials == "9") {
            j = stoi(initials);
        }
        else {
            j = 0;
        }
        refresh();
        if (j < 1 || j > n) {
            clear();
            mvprintw(row/2-1,col/2-25,"%s","Invalid Pancake");
        }
    }
    return j;
}

void random_order() {
    int rand_num;
    for (int i = 0; i < n; i++ ) { order.push_back(-1); }
    for (int i = 0; i < n; i++) {
        rand_num = rand() % n + 1;
        bool already_inputted = false;
        for (long unsigned int j = 0; j < order.size(); j++ ) {
            if (order[j] == rand_num) {
                already_inputted = true;
                break;
            }	}
        if (already_inputted == true) {
            while (already_inputted == true) {
                rand_num = rand() % n + 1;
                for (long unsigned int k = 0; k < order.size(); k++ ) {
                    if (order[k] == rand_num) {
                        already_inputted = true;
                        break;
                    }
                    else if (k == order.size()-1) {
                        already_inputted = false;
                        order[i] = rand_num;
                        break;
                    }	}	}	}
        else {
            order[i] = rand_num;
        }	}
}

int prompt_user_first (int i) {
    int row,col;
    int j = 0;
    getmaxyx(stdscr,row,col);
    clear();
    mvprintw(row/2-1,col/2-25,"Pancake size of %d position (1(Top)-%d): ",i+1,n);
    string initials = "";
    refresh();
    initials += getch();
    if (initials == "0" || initials == "1" || initials == "2" || initials == "3" || initials == "4" || initials == "5" || initials == "6" || initials == "7" || initials == "8" || initials == "9") {
        j = stoi(initials);
    }
    else {
        j = 0;
    }
    return j;
}

string init_screen_task3 () {
    string randomize = "";
    clear();
    refresh();
    int row,col;
    initscr();
    getmaxyx(stdscr,row,col);
    mvprintw(row/2-1,col/2-25,"%s","Would you like to choose the order? (y or n) ");
    refresh();
    char inputted = getchar();
    randomize += inputted;
    return randomize;
}

int position_taken (int x, int i) {
    int j = x;
    int row,col;
    getmaxyx(stdscr,row,col);
    string initials;
    while(order[j-1] != -1) {
        mvprintw(row/2,col/2-25,"Pancake size of %d position (1(Top)-%d): ",i+1,n);
        initials = "";
        refresh();
        initials += getch();
        if (initials == "0" || initials == "1" || initials == "2" || initials == "3" || initials == "4" || initials == "5" || initials == "6" || initials == "7" || initials == "8" || initials == "9") {
            j = stoi(initials);
        }
        else {
            j = 0;
        }
        if (j < 1 || j > n) {
            j = prompt_user_invalid(j,i);
        }
        if (order[j-1] == -1) {
            order[j-1] = i+1;
            break;
        }
        if ((1 <= j && j <= n) && order[j-1] != -1) {
            clear();
            mvprintw(row/2-1,col/2-25,"%s","Pancake position taken");
        }
    }
    return j;
}

void ordering() {
    int row,col;
    getmaxyx(stdscr,row,col);
    string randomize = init_screen_task3();
    string initials;
    int j;

    randomize = randomize_first(randomize);
    if (randomize == "y") {
        for (int i = 0; i < n; i++ ) { order.push_back(-1); }
        for (int i = 0; i < n; i++) {
            j = prompt_user_first(i);
            if (j < 1 || j > n) {
                j = prompt_user_invalid(j,i);
            }
            if ((1 <= j && j <= n) && order[j-1] != -1) {
                clear();
                mvprintw(row/2-1,col/2-25,"%s","Pancake position taken");
            }
            if (order[j-1] != -1) { position_taken(j,i); }
            else { order[j-1] = i+1; }
        }
    }
    else { random_order(); }
    endwin();
}


//==============================task2===========================
int num_pancakes_Init(){
    int num_ACII, row, col;
    //string num_String;
    getmaxyx(stdscr, row, col);				//draw the window and print messages
    char prompt_S1[] = "=====How Many Pancakes Would You Like?=====\n";
    mvprintw(row/2,(col-strlen(prompt_S1))/2, prompt_S1);
    char prompt_S2[] = "ENTER HERE: ";
    mvprintw(row/2 + 3,(col-strlen(prompt_S2))/2, prompt_S2);
    refresh();
    num_ACII = getch();			            // Wait for user input
    refresh();
    getch();

    return num_ACII;
}

int diff_level_init(){
    int num_ACII, row, col;
    //string num_String;
    getmaxyx(stdscr, row, col);			    //draw the window and print messages
    char prompt_S1[] = "=====Enter Your Difficulty Level=====\n";
    mvprintw(row/2,(col-strlen(prompt_S1))/2, prompt_S1);
    char prompt_S2[] = "ENTER HERE: ";
    mvprintw(row/2 + 3,(col-strlen(prompt_S2))/2, prompt_S2);
    refresh();
    num_ACII = getch();                     // Wait for user input
    refresh();
    getch();
    return num_ACII;
}

int num_pancakes(){
    initscr();                      // Start curses mode
    clear();
    refresh();
    int row, col, num;
    getmaxyx(stdscr, row, col);
    char Error_Message[] = "Please enter a number between 2 - 9\n";
    int num_ACII = num_pancakes_Init();
    while(num_ACII < 50 || num_ACII > 57) {     //test if the number is in the range
        clear();
        mvprintw(row/2,(col-strlen(Error_Message))/2, Error_Message);
        //printw(Error_Message);
        refresh();
        getch();
        clear();
        num_ACII = num_pancakes_Init();
    }
    num = num_ACII - 48;
    //getch();
    clear();                        //clean the screen
    endwin();                       // end curses mode
    return num;
}

int diff_level(int numPac){
    initscr();                      // Start curses mode

    int diff_level_var, row, col;
    getmaxyx(stdscr, row, col);
    char Error_Message[] = "Please enter a number between One and Number of pancakes";
    int num_ACII = diff_level_init();
    while(num_ACII < 49 || num_ACII > (numPac+48)) {		//test if the number is in the range
        clear();
        mvprintw(row/2,(col-strlen(Error_Message))/2, Error_Message);
        //printw(Error_Message);
        refresh();
        getch();
        clear();
        num_ACII = diff_level_init();
    }
    diff_level_var = num_ACII - 48;		//convert from ascc to int
    //getch();
    clear();                         //clean the screen
    endwin();                        // end curses mode
    return diff_level_var;
}


void task2(int &num_pac, int &diff_lvl){

    num_pac = num_pancakes();		//Get the number of pancakes
    diff_lvl = diff_level(num_pac);	//Get the difficulty level
    if(diff_lvl == 9)
    {
        diff_lvl = 8;
    }

}
//==============================task2===========================


//==============================task6===========================


bool is_valid_move(int x, int y, vector<int> user_order, vector<pancake_pos> user_pos,int &pancake){
    pancake = 11;
    for(int i = 0; i<(int)user_pos.size(); i++){
        if(y>=user_pos[i].y && y<user_pos[i].y+3){
            pancake = i;
        }
    }
    if(pancake == 11){return false;}
    if(x >=user_pos[pancake].x && x<user_pos[pancake].x + (user_order[pancake]*2+1)){
        return true;
    }
    else{
        return false;
    }

}

void do_moving(int &cx, int &cy, int ch, bool &end, int row, int col){
    switch(ch){
        case 'w':
        case KEY_UP:
            if(cy-1 >=0){cy--;}
            break;
        case 's':
        case KEY_DOWN:
            if(cy+1 < row){cy++;}
            break;
        case 'a':
        case KEY_LEFT:
            if(cx-1>=0){cx--;}
            break;
        case 'd':
        case KEY_RIGHT:
            if(cx +1 < col){cx++;}
            break;
        case 10:
            end = true;
            break;
        default:
            clear();
    }
}
void is_not_valid_screen(){
    clear();
    int row, col;
    getmaxyx(stdscr, row, col);
    mvprintw(row/2,(col-strlen("Please move curser to one of the pancakes on the left"))/2,"Please move curser to one of the pancakes on the left");
    mvprintw(row/2+2, (col-strlen("Press any key to continue."))/2,"Press any key to continue.");
    refresh();
    getch();

}
void user_move_instructions(){
    int row,col;
    initscr();  //Start Curses Mode
    curs_set(FALSE);//makes cursor invisible
    start_color();//Start color mode
    getmaxyx(stdscr, row, col);
    clear();
    attron(COLOR_PAIR(4));
    mvprintw(row/2,(col-strlen("Use the arrow keys (or\"WASD\") to move cursor to chosen pancake."))/2,"Use the arrow keys (or\"WASD\") to move cursor to chosen pancake.");
    mvprintw(row/2+1,(col-strlen("Hit enter to flip."))/2,"Hit enter to flip.");
    mvprintw(row/2+3, (col-strlen("Press any key to start."))/2,"Press any key to start.");
    refresh();
    cbreak();
    wgetch(stdscr);
    endwin();
}
int user_move(vector<int> usr_order, vector<int> AI_order, vector<pancake_pos> &usr_position_vector, vector<pancake_pos> &AI_position_vector){
    int row,col;
    getmaxyx(stdscr, row, col);
    draw_stack(usr_order, AI_order, usr_position_vector, AI_position_vector);
    mvprintw(row/5,(col-strlen("PLAYER TURN"))/2,"PLAYER TURN");
    cbreak();
    keypad(stdscr, TRUE);
    int cx = 10,cy = 10, index;
    move(cy,cx);
    refresh();
    bool end = false;
    while(!end || !is_valid_move(cx,cy,usr_order,usr_position_vector,index)){
        end = false;
        int ch = getch();
        do_moving(cx,cy,ch,end,row,col);
        if(ch == 10 && !is_valid_move(cx,cy,usr_order,usr_position_vector,index)){
            is_not_valid_screen();}
        if(ch != KEY_DOWN  || ch != KEY_LEFT || ch != KEY_RIGHT || ch != KEY_UP) {
            draw_stack(usr_order, AI_order, usr_position_vector, AI_position_vector);
            mvprintw(row/5,(col-strlen("PLAYER TURN"))/2,"PLAYER TURN");
            refresh();}
        move(cy,cx);
        refresh();
    }return index;
}
void user_choice(int index, vector<int> &user_order){
    vector<int> flipping_vector;
    for(int i = index; i>=0;i--){
        flipping_vector.push_back(user_order[i]);
    }
    for(int i = 0; i<=index; i++){
        user_order[i] = flipping_vector[i];
    }
}
void user_blink(int index, vector<int> user_order, vector<pancake_pos> user_position, vector<int> AI_order, vector<pancake_pos> AI_position){
    int row = 0,col =0;
    getmaxyx(stdscr, row, col);
    vector<int> blanks(user_order);
    vector<pancake_pos> blanks_position;
    for(int i = 0; i<=index; i++){
        blanks[i] = 0;
    }
    for(int i = 0; i<3; i++){
        draw_stack(blanks, AI_order, blanks_position, AI_position);
        mvprintw(row/5,(col-strlen("PLAYER TURN"))/2,"PLAYER TURN");
        refresh();
        usleep(500000);
        draw_stack(user_order, AI_order, user_position, AI_position);
        mvprintw(row/5,(col-strlen("PLAYER TURN"))/2,"PLAYER TURN");
        refresh();
        usleep(500000);
    }

}

void user_turn(vector<int> &user_order, vector<pancake_pos> &user_position, vector<int> &AI_order, vector<pancake_pos> &AI_position ){
    int row = 0,col = 0;
    getmaxyx(stdscr, row, col);
    int index = user_move(user_order, AI_order, user_position, AI_position);
    user_blink(index,user_order,user_position,AI_order,AI_position);
    user_choice(index,user_order);
    draw_stack(user_order, AI_order, user_position, AI_position);
    mvprintw(row/5,(col-strlen("PLAYER TURN"))/2,"PLAYER TURN");
    endwin();
}




//==============================task6===========================
bool is_sorted(vector <int> order) {
    for (int i = 0; i < (int)order.size()-1; i++) {
        if (order[i] > order[i+1]) {
            return false;
        }
    }
    return true;
}
//==============================task7===========================
void AI_blink(int index, vector<int> user_order, vector<pancake_pos> user_position, vector<int> AI_order, vector<pancake_pos> AI_position){
    int row = 0,col = 0;
    getmaxyx(stdscr, row, col);
    vector<int> blanks(AI_order);
    vector<pancake_pos> blanks_position;
    for(int i = 0; i<=index; i++){
        blanks[i] = 0;
    }
    for(int i = 0; i<3; i++){
        draw_stack(user_order, blanks, user_position, blanks_position);
        mvprintw(row/5,(col-strlen("COMPUTER'S TURN"))/2,"COMPUTER'S TURN");
        refresh();
        usleep(500000);
        draw_stack(user_order, AI_order, user_position, AI_position);
        mvprintw(row/5,(col-strlen("COMPUTER'S TURN"))/2,"COMPUTER'S TURN");
        refresh();
        usleep(500000);
    }
}
void AI_turn(AI_computer AI,vector<int> &user_order, vector<pancake_pos> &user_position, vector<int> &AI_order, vector<pancake_pos> &AI_position){
    int row = 0,col = 0;
    getmaxyx(stdscr, row, col);
    draw_stack(user_order, AI_order, user_position, AI_position);
    mvprintw(row/5,(col-strlen("COMPUTER IS THINKING"))/2,"COMPUTER IS THINKING");
    refresh();
    int index = AI.get_best_flip(AI_order);
    AI_blink(index,user_order,user_position,AI_order,AI_position);
    AI_order = AI.cvt_2_int(AI.flip(index,AI.cvt_2_pan(AI_order),0));
    draw_stack(user_order, AI_order, user_position, AI_position);

    refresh();
    if(is_sorted(AI_order)){
        draw_stack(user_order, AI_order, user_position, AI_position);
        mvprintw(row/5,(col-strlen("PRESS ANY KEY TO CONTINUE"))/2,"PRESS ANY KEY TO CONTINUE");
        refresh();
        getchar();}
    endwin();
}
//==============================task7===========================

//==============================task8===========================

//Task8
vector<scores_vec> scores_in_vec(vector<scores_vec> scores) {
    fstream fs;
    fs.open("scores.txt",fstream::in | fstream::out | fstream::app);
    string x;
    int i = 0;
    while(getline(fs,x) && i<5){
        bool first_input = true;
        int j = 0;
        scores_vec input;
        string word = "";
        int len = x.length();
        while (j < len) {
            if (x[j] == ' ' && first_input == true) {
                input.initial = word;
                word = "";
                j++;
                first_input = false;
            } else if (j == len-1 && first_input == false) {
                word += x[j];
                input.score = atoi(word.c_str());
                j++;
            } else { word += x[j]; j++;
            }} scores.push_back(input); }
    fs.close();
    return scores;
}

vector<scores_vec> complete_scores_vec(vector<scores_vec> scores) {
    scores = scores_in_vec(scores);
    scores_vec new_input;
    new_input.initial = init_initial;
    new_input.score = player_score;
    scores.push_back(new_input);
    return scores;
}

void print_update_scores() {
    clear();
    refresh();
    int row,col;
    initscr();
    getmaxyx(stdscr,row,col); row = 1;
    fstream fs;
    vector<scores_vec> scores;
    scores = complete_scores_vec(scores);
    sort(scores.begin(), scores.end(), compareByLength);
    fs.open("scores.txt",ios::out);
    for (int i = 0; i < (int)scores.size(); i++) {
        if (i%2 == 1) { attron(COLOR_PAIR(2)); }
        else { attron(COLOR_PAIR(1)); }
        string output_word = scores[i].initial + " " + to_string(scores[i].score);
        mvprintw(row+i,col/2-3,"%s",output_word.c_str());
        fs << output_word << "\n";
        if (i == 4) { break; }}
    string print_val = "Your Score: " + init_initial + " " + to_string(player_score);
    mvprintw(10,col/2-10,"%s",print_val.c_str());
    fs.close();
    refresh();
    getchar();
    endwin();
}

bool play_again_task8 () {
    string randomize = "";
    clear();
    refresh();
    int row,col;
    initscr();
    getmaxyx(stdscr,row,col);
    attron(COLOR_PAIR(2));
    mvprintw(row/2-1,col/2-25,"%s","Would you like to play again? (y or n) ");
    refresh();
    char inputted = getchar();
    randomize += inputted;
    while (randomize != "y" && randomize != "n") {
        clear();
        randomize = "";
        mvprintw(row/2-1,col/2-25,"%s","Must be y or n");
        mvprintw(row/2,col/2-25,"%s","Would you like to play again? (y or n) ");
        refresh();
        inputted = getchar();
        randomize += inputted; }
    clear();
    if (randomize == "y") {return true;}
    else { system("clear"); return false; }
}


//int main()
//{
//    bool play_again = true;
//    while (play_again == true) {
//        splash_screen();//task 1
//        task2(n, diff); //task2
//        order.clear();
//        ordering(); //task3
//        init_initial = high_score_screen();//task 4
//        vector<int> user_order(order);
//        vector<int> AI_order(order);
//        vector<pancake_pos> user_position, AI_position;
//        user_move_instructions();
//        bool user_sorted = false;
//        bool ai_sorted = false;
//        while(true) {
//
//            user_turn(user_order, user_position,  AI_order, AI_position);
//            user_sorted = is_sorted(user_order);
//            AI_computer AI = AI_computer(diff);
//            AI_turn(AI,user_order, user_position,  AI_order, AI_position);
//            ai_sorted = is_sorted(AI_order);
//            if (user_sorted == true && ai_sorted == true) { player_score = (n * (diff + 1)); break; }
//            else if (user_sorted == true && ai_sorted == false) { player_score = (2 * n * (diff + 1)); break; }
//            else if (user_sorted == false && ai_sorted == true) { player_score = n; break; }}
//        print_update_scores(); //Task8
//        play_again = play_again_task8();
//
//
//    } return 0;
//}