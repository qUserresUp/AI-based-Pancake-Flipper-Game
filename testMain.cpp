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
#include <curses.h>
#include "mainChain.cpp"
using namespace std;

//to compile: g++-8.2.0 -std=c++2a -Wall -Wextra -pedantic -fsanitize=address,undefined,pointer-compare,pointer-subtract -fstack-clash-protection -g -fno-omit-frame-pointer testMain.cpp -lncurses
void task1_test_setup(int &y_offset,int &row,int &col){
    //needed information////////////////////////////
    initscr();  //Start Curses Mode/
    curs_set(FALSE);//makes cursor invisible

    start_color();//Start color mode
    y_offset=-3; //Y offset to output block

    //makes color choices
    init_pair(1, COLOR_WHITE, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_YELLOW);
    init_pair(3, COLOR_BLACK, COLOR_CYAN);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_BLACK, COLOR_BLACK);
    getmaxyx(stdscr,row,col);
    ///////////////////////////////////////////////

}

string task1_test1(int y_offset,int row,int col){
    print_title(y_offset,row,col);//prints colorful
    string line = "";
    for(int i =0 ;i<21;i++){
        char letter = (char) mvinch(row/2-4+y_offset,(col-strlen("PANCAKE SORTING GAME \n"))/2+i);
        line.push_back(letter);
    }

    if(!line.compare("PANCAKE SORTING GAME ")){
        line = "PASS";
    }
    else{
        line = "FAIL";
    }
    return line;

}

string task1_test2(int y_offset,int row,int col){
    string line = "";
    print_team_info(y_offset,row,col);
    for(int i =0 ;i<12;i++){
        char letter = (char) mvinch(row/2+2+1+y_offset,(col-strlen("Samantha Hay"))/2+i);
        line.push_back(letter);
    }

    if(!line.compare("Samantha Hay")){
        line = "PASS";
    }
    else{
        line = "FAIL";
    }
    return line;
}

string task1_test3(int y_offset,int row,int col){
    string line = "";
    enter_button_color_change(false,y_offset,row,col);
    for(int i =0 ;i<20;i++){
        char letter = (char) mvinch(row/2+3+5+y_offset,(col-strlen("Press ENTER to start"))/2+i);
        line.push_back(letter);
    }

    if(	!line.compare("Press ENTER to start")){
        line = "PASS";
    }
    else{
        line = "FAIL";
    }
    return line;
}

string task1_test4(int col){
    string line = "";
    print_game_info(col);
    for(int i =0 ;i<6;i++){
        char letter = (char) mvinch(2,0+i);
        line.push_back(letter);
    }

    if(	!line.compare("SETUP:")){
        line = "PASS";
    }
    else{
        line = "FAIL";
    }
    return line;
}
string task1_test5(int col){
    string line = "";
    print_game_info(col);
    for(int i =0 ;i<39;i++){
        char letter = (char) mvinch(3,0+i);
        line.push_back(letter);
    }

    if(	!line.compare("1. When prompted choose the number of p")){
        line = "PASS";
    }
    else{
        line = "FAIL";
    }
    return line;
}


void task1_tests(){
    int y_offset =0,row = 0,col=0;
    task1_test_setup(y_offset,row,col);
    string test1 = task1_test1(y_offset,row,col);
    string test2 = task1_test2(y_offset,row,col);
    string test3 = task1_test3(y_offset,row,col);
    string test4 = task1_test4(col);
    string test5 = task1_test5(col);
    endwin();
    cout<<"Testing for task 1:"<<endl;
    cout<<"Test 1: "<<test1<<endl;
    cout<<"Test 2: "<<test2<<endl;
    cout<<"Test 3: "<<test3<<endl;
    cout<<"Test 4: "<<test4<<endl;
    cout<<"Test 5: "<<test5<<endl;

}

void Task4_test_setup(){
    clear();
    initscr();
    refresh();
}
string task4_test1( int row, int col){
    string line = "";
    FILE* fd = fopen("test.txt","r" );
    string s = "asa";
    newterm(NULL, stdout, fd);
    string initials = get_initials(row,col);
    fclose(fd);
    endwin();
    if(initials == s){
        line = "PASS";
    }
    else{
        line = "FAIL";
    }

    return line;
}
string task4_test2( int row, int col){
    string line = "";
    FILE* fd = fopen("test.txt","r" );
    string s = "asaasasasa";
    newterm(NULL, stdout, fd);
    string initials = get_initials(row,col);
    fclose(fd);
    endwin();

    if(initials == "asa"){
        line = "PASS";
    }
    else{
        line = "FAIL";
    }

    return line;
}
void task4_tests(){
    int row,col;
    getmaxyx(stdscr,row,col);
    string test = task4_test1(row,col);
    string test2 = task4_test2(row,col);
    cout<<"Testing for task 4:"<<endl;
    cout<<"Test 1: "<<test<<endl;
    cout<<"Test 2: "<<test2<<endl;
}
string task3_test1() {
    string line = "";
    string randomize = init_screen_task3();

    if (randomize != "") {
        line = "PASS";
    }
    else {
        line = "FAIL";
    }
    return line;
}

string task3_test2() {
    string line = "";
    string returns = randomize_first(line);

    if (returns == "y" || returns == "n") {
        line = "PASS";
    }
    else {
        line = "FAIL";
    }
    return line;
}

string task3_test3() {
    string line = "";
    int returns = prompt_user_first(1);

    if (returns == 0 || returns == 1 || returns == 2 || returns == 3 || returns == 4 || returns == 5 || returns == 6 || returns == 7 || returns == 8 || returns == 9) {
        line = "PASS";
    }
    else {
        line = "FAIL";
    }

    return line;
}

string task3_test4() {
    string line = "";
    int returns = position_taken(1,1);

    if (returns == 0 || returns == 1 || returns == 2 || returns == 3 || returns == 4 || returns == 5 || returns == 6 || returns == 7 || returns == 8 || returns == 9) {
        line = "PASS";
    }
    else {
        line = "FAIL";
    }

    return line;
}

string task3_test5() {
    string line = "";
    int returns = prompt_user_invalid(1,1);

    if (returns == 0 || returns == 1 || returns == 2 || returns == 3 || returns == 4 || returns == 5 || returns == 6 || returns == 7 || returns == 8 || returns == 9) {
        line = "PASS";
    }
    else {
        line = "FAIL";
    }

    return line;
}

void task3_tests() {
    n = 9;
    for (int i = 0; i < n; i++ ) { order.push_back(-1); }
    string test1 = task3_test1();
    string test2 = task3_test2();
    string test3 = task3_test3();
    string test4 = task3_test4();
    string test5 = task3_test5();
    endwin();
    cout<<"Testing for task 3:"<<endl;
    cout<<"Test 1: "<<test1<<endl;
    cout<<"Test 2: "<<test2<<endl;
    cout<<"Test 3: "<<test3<<endl;
    cout<<"Test 4: "<<test4<<endl;
    cout<<"Test 5: "<<test5<<endl;
}

string Task2_test1(int &num_Pac){
    string line = "";

    num_Pac = num_pancakes();

    if(num_Pac > 2 || num_Pac < 9)
    {
        line = "PASS";
    }
    else{
        line = "FAIL";
    }

    return line;

}

string Task2_test2(int n){
    string line = "";

    int diff_Lvl = diff_level(n);

    if(diff_Lvl > 1 || diff_Lvl < n)
    {
        line = "PASS";
    }
    else{
        line = "FAIL";
    }

    return line;

}

void Task2_tests() {
    int num_Pac = 0;
    string return1 = Task2_test1(num_Pac);
    string return2 = Task2_test2(num_Pac);
    cout<<"Testing for task 2:"<<endl;
    cout <<"Test 1: "<< return1 <<endl;
    cout <<"Test 2: "<< return2 << endl;


}

void task5_test(){
    vector<int> usr_order = {1,2,3,4,5,6,7,8,9};
    vector<int> AI_order = {9,8,7,6,5,4,3,2,1};
    vector<pancake_pos> usr_pos_vector = {};
    vector<pancake_pos> AI_pos_vector = {};
    vector<int> test_usr_order = {};
    vector<int> test_AI_order = {};
    draw_stack(usr_order, AI_order, usr_pos_vector, AI_pos_vector);
    endwin();
    for(int i = 0; i < (int)usr_order.size(); i ++)
    {
        char letter = (char) mvinch(usr_pos_vector[i].y + 1, usr_pos_vector[i].x + usr_order[i]);
        test_usr_order.push_back((int)letter - 48);
    }
    for(int i = 0; i < (int)AI_order.size(); i ++)
    {
        char letter = (char) mvinch(AI_pos_vector[i].y + 1, AI_pos_vector[i].x + AI_order[i]);
        test_AI_order.push_back((int)letter - 48);
    }
    cout << "Testing for task 5" << endl;
    if(usr_order == test_usr_order && AI_order == test_AI_order){cout << "Test: PASS" << endl;}
    else{cout << "fail!" << endl;}
}

string task6_test1(){
    string line;
    vector<int> test1 = {1,2,3,4,5,6};
    user_choice(3,test1);
    vector<int> check = {4,3,2,1,5,6};
    if(test1 == check){
        line = "PASS";
    }
    else{
        line = "FAIL";
    }
    return line;
}

string task6_test2(){
    string line;
    vector<int> test1 = {1,2,3,4,5,6};
    user_choice(3,test1);
    vector<int> check = {1,2,3,4,5,6};
    if(test1 != check){
        line = "PASS";
    }
    else{
        line = "FAIL";
    }
    return line;
}

string task6_test3(){
    int x = 0;
    int y = 0;
    string line;
    vector<int> test = {4};
    pancake_pos testp(y,x);
    vector<pancake_pos> test_pos;
    test_pos.push_back(testp);
    if(is_valid_move(x,y,test,test_pos,x)){
        line = "PASS";
    }
    else{
        line = "FAIL";
    }
    return line;
}

string task6_test4(){
    int x = 11;
    int y = 20;
    string line;
    vector<int> test = {4};
    pancake_pos testp(0,0);
    vector<pancake_pos> test_pos;
    test_pos.push_back(testp);
    if(!is_valid_move(x,y,test,test_pos,x)){
        line = "PASS";
    }
    else{
        line = "FAIL";
    }
    return line;
}
string task6_test5(){
    int x = 0;
    int y = 0;
    string line;
    vector<int> test = {4};
    pancake_pos testp(0,0);
    vector<pancake_pos> test_pos;
    test_pos.push_back(testp);
    is_valid_move(x,y,test,test_pos,x);
    if(x == 0){
        line = "PASS";
    }
    else{
        line = "FAIL";
    }
    return line;
}
void task6_tests(){
    initscr();  //Start Curses Mode
    curs_set(FALSE);
    string test1 = task6_test1();
    string test2 = task6_test2();
    string test3 = task6_test3();
    string test4 = task6_test4();
    string test5 = task6_test5();
    endwin();
    cout<<"Testing for task 6:"<<endl;
    cout<<"Test 1: "<<test1<<endl;
    cout<<"Test 2: "<<test2<<endl;
    cout<<"Test 3: "<<test3<<endl;
    cout<<"Test 4: "<<test4<<endl;
    cout<<"Test 5: "<<test5<<endl;
}

void task8_tests() {
    cout << "Testing for task 8" << endl;
    vector<int> order1 = {1,2,3,4,5,6,7,8,9};
    vector<int> order2 = {1,2,3,4,6,7,8,9,5};
    vector<int> order3 = {9,8,7,6,5,4,3,2,1};
    bool sorted = is_sorted(order1);
    if (sorted == true) {
        cout << "Test 1: PASS" << endl;
    } else {
        cout << "Test 1: FAIL" << endl;
    }
    sorted = is_sorted(order2);
    if (sorted == false) {
        cout << "Test 2: PASS" << endl;
    } else {
        cout << "Test 2: FAIL" << endl;
    }
    sorted = is_sorted(order3);
    if (sorted == false) {
        cout << "Test 3: PASS" << endl;
    } else {
        cout << "Test 3: FAIL" << endl;
    }
    vector<scores_vec> scores;
    scores = scores_in_vec(scores);
    if (scores.size() < 6) {
        cout << "Test 4: PASS" << endl;
    } else {
        cout << "Test 4: FAIL" << endl;
    }
}

int main(){
    //Testing for Task 1
    task1_tests();
    Task2_tests();
    task3_tests();
    //task4_tests();
    task5_test();
    task6_tests();
    task8_tests();

}
