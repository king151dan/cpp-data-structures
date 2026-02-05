/*
Name: Daniel Hinga,
Description:Code a fully functional 2D version of Competitive CS:GO mode minus
 the Weapon Economy (just one gun everyone spawns with) and the Online multiplayer (1 human, 9 bots, or all bots)
Input: user imputs movement
Output: the game of csgo
*/

//Dedicated to all the competitive gamers out there.
//Compile as: g++ TerminalCSGO.cpp -lncurses

//#include<iostream>    //cin/cout NOT USED. DO NOT ENABLE!
#include<fstream>       //File Streams
#include<ncurses.h>     //N Curses Library
#include<stdlib.h>      //srand
#include<time.h>        //time
#include<vector>

//using namespace std;

void initCurses();
void endCurses();


class CharMap {
public:
    CharMap(char *arg);
    CharMap(char** c, std::string m, int w, int h) :
            map(c), mapName(m), width(w), height(h){}
    ~CharMap();
    void print();
    char ** map;
    std::string mapName;
    int width;
    int height;
};


class ent_t{
public:
    int x,y;

    virtual char WhatAmI(){return 'e';}
    virtual void setCoordinates(int xx, int yy){x = xx; y = yy;}
    ent_t(int x, int y) : x(x), y(x){}
};


class bomb_t : public ent_t {
public:
    bool isPlanted, isCarried, isDefused;
    bomb_t(int x, int y) : ent_t(x,y){

        isPlanted = false;
        isCarried = false;
        isDefused = false;

    }
    char WhatAmI(){return 'B';}
};
class player_t : public ent_t {
public:
    bool isHuman;

    bool isAlive;

    bomb_t * bomb;

    char previousDirection;

    char Team;
    player_t(bool isH, char ts, int x, int y) : ent_t(x,y) {

        isHuman = isH;
        isAlive = true;
        Team = ts;
        previousDirection = 'n';

    }
    void RIP(std::vector<ent_t*> & p_entList){
        if(bomb != NULL){

            bomb->isCarried = false;
            p_entList.push_back(bomb);
        }
    }
    char WhatAmI(){
        return 'P';}
};


class projectile_t : public ent_t {
public:
    char direction;
    player_t* owner;
    projectile_t(player_t* player, int x, int y) : ent_t(x, y){
        owner = player;
        direction = player->previousDirection;
    }
    char WhatAmI(){
        return '*';
    }
};


class point_t{
public:
    bool Bombsite;
    bool Obstacle;
    bool Wall;
    bool BridgeTunnel;
    char baseType, finalType;
    int x,y;
    std::vector<ent_t*> entList;


    point_t(char p, int xx, int yy){
        baseType = finalType = p;
        x = xx;
        y = yy;

        Wall = false;
        Obstacle = false;
        Bombsite = false;
        BridgeTunnel = false;
    }


    point_t(CharMap* map, int xx, int yy){
        x = xx;
        y = yy;


        if(map->map[yy][xx] == 'x'){

            baseType = finalType = 'x';

            Wall = true;
            Obstacle = false;
            Bombsite = false;
            BridgeTunnel = false;
        }

        else if(map->map[yy][xx] == 'o'){

            baseType = finalType = 'o';
            Wall = false;
            Obstacle = true;
            Bombsite = false;
            BridgeTunnel = false;

        }
        else if(map->map[yy][xx] == 'P'){
            baseType = finalType = 'P';
            Wall = false;
            Obstacle = false;
            Bombsite = true;
            BridgeTunnel = false;
        }
        else if(map->map[yy][xx] == '#'){
            baseType = finalType = '#';
            Wall = false;
            Obstacle = false;
            Bombsite = false;
            BridgeTunnel = true;
        }
        else if(map->map[yy][xx] == 'T'){
            baseType = finalType = 'T';
            Wall = false;
            Obstacle = false;
            Bombsite = false;
            BridgeTunnel = false;
        }
        else if(map->map[yy][xx] == 'C'){
            baseType = finalType = 'C';
            Wall = false;
            Obstacle = false;
            Bombsite = false;
            BridgeTunnel = false;
        }
        else if(map->map[yy][xx] == '@'){
            baseType = finalType = '@';
            Wall = false;
            Obstacle = false;
            Bombsite = false;
            BridgeTunnel = false;
        }
        else if(map->map[yy][xx] == '1'){
            baseType = finalType = '1';
            Wall = false;
            Obstacle = true;
            Bombsite = false;
            BridgeTunnel = false;
        }
        else if(map->map[yy][xx] == '2'){
            baseType = finalType =  '2';
            Wall = false;
            Obstacle = false;
            Bombsite = false;
            BridgeTunnel = false;
        }
        else if(map->map[yy][xx] == '3'){
            baseType = finalType = '3';
            Wall = false;
            Obstacle = false;
            Bombsite = false;
            BridgeTunnel = false;
        }
        else if(map->map[yy][xx] == 'n'){
            baseType = finalType = 'n';
            Wall = true;
            Obstacle = false;
            Bombsite = false;
            BridgeTunnel = false;
        }
        else if(map->map[yy][xx] == ' '){
            baseType = finalType = ' ';
            Wall = false;
            Obstacle = false;
            Bombsite = false;
            BridgeTunnel = false;
        }
        else if(map->map[yy][xx] == 'B'){
            baseType = finalType = 'B';
            Wall = false;
            Obstacle = false;
            Bombsite = false;
            BridgeTunnel = false;
        }
        else if(map->map[yy][xx] == '*'){
            baseType = finalType = '*';
            Wall = false;
            Obstacle = false;
            Bombsite = false;
            BridgeTunnel = false;
            //entList.push_back(new projectile_t(x,y));
        }
    }


    void renderPoint(){
        if(baseType == '@'){
            finalType = ' ';
            mvaddch(y, x, baseType);
        }
        else if(baseType == 'T'){
            finalType = ' ';
            mvaddch(y, x, baseType);
        }
        else if(baseType == 'C'){
            finalType = ' ';
            mvaddch(y, x, baseType);
        }
        else if(baseType == '*'){
            mvaddch(y, x, baseType);
        }
        else if(baseType == 'B'){
            finalType = ' ';
            mvaddch(y, x, baseType);
        }
        else if(baseType == '#'){
            finalType = ' ';
            mvaddch(y, x, baseType);
        }
        else if(baseType == 'P'){
            finalType = ' ';
            mvaddch(y, x, baseType);
        }
        else if(baseType == '1'){
            finalType = ' ';
            mvaddch(y, x, baseType);
        }
        else if(baseType == '2'){
            finalType = ' ';
            mvaddch(y, x, baseType);
        }
        else if(baseType == '3'){
            finalType = ' ';
            mvaddch(y, x, baseType);
        }
        else if(baseType == 'x'){
            mvaddch(y, x, baseType);
        }
        else if(baseType == 'o'){
            mvaddch(y, x, baseType);
        }
        else if(baseType == 'n'){
            mvaddch(y, x, baseType);
        }
        else if(baseType == ' '){
            mvaddch(y, x, baseType);
        }
    }
    void deleteEntFromPoint(ent_t* e){
        for(int i = 0; entList.size() > i; i++){

            if(e == entList[i]){

                delete entList[i];

                entList[i] = NULL;
            }
        }
    }
};


class Level{
public:
    point_t*** point;
    int height;
    int width;
    int bombX,bombY;

    int playerX,playerY;

    CharMap* mapreference;
    int roundTimer;
    int bombTimer;


    enum bombStatus {DROPPED, GRABBED, PLANTED, DEFUSED}status;

    void getBombStatus(){
        if(mapSearchX('B') == -1 and mapSearchY('B') == -1){
            status = GRABBED;
        }
        else if(bombX == mapSearchX('B') and bombY == mapSearchY('B')){
            status = DROPPED;
        }
        else{
            status = PLANTED;
        }

    }
    int Talive;
    int CTalive;
    int endcondition;
    point_t* addpoint(char p, int x, int y){

    }
    Level(CharMap* map) : roundTimer(301), bombTimer(30), Talive(5), CTalive(5){
        mapreference = map;
        height = map->height;
        width = map->width;
        point = new point_t**[height];
        for(int i = 0; i < height; i++){
            point[i] = new point_t*[width];
            for(int j = 0; j < width; j++){
                if(point[i][j] == NULL){
                    point[i][j] = new point_t(map, j, i);
                }
            }
        }
    }
    void renderLevel(){
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                if(point[i][j] != NULL)
                    point[i][j]->renderPoint();
                refresh();
            }
        }
    }
    void clearScreen(){
        clear();
        if(status == PLANTED){
            mvprintw(52, 45, "Time Left: %d", bombTimer);
            mvprintw(53, 45, "Bomb status: PLANTED");
        }
        if(status == DROPPED){
            mvprintw(52, 45, "Time Left: %d", roundTimer);
            mvprintw(53, 45, "Bomb status: DROPPED");
        }
        if(status == GRABBED){
            mvprintw(52, 45, "Time Left: %d", roundTimer);
            mvprintw(53, 45, "Bomb status: GRABBED");
        }
        if(status == DEFUSED){
            mvprintw(52, 45, "Time Left: %d", bombTimer);
            mvprintw(53, 45, "Bomb status: DEFUSED");
        }
        mvprintw(54, 45, "T  Left: %d", Talive);
        mvprintw(55, 45, "CT Left: %d", CTalive);
        mvprintw(56, 45, "Player Coords: (%d,%d)", playerX, playerY);
    }


    int mapSearchX(char c){
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                if(point[i][j]->baseType == c)
                    return j;
            }
        }
        return -1;
    }
    int mapSearchY(char c){
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                if(point[i][j]->baseType == c)
                    return i;
            }
        }
        return -1;
    }
    void openNteamSelect(){
        int gamemode;
        int choice;
        int highlight = 0;
        int x,y;
        player_t* player;
        bomb_t* bomb;


        std::string choices[2] = {"Counter-Terrorist", "Terrorist"};
        WINDOW * cs302 = newwin(35, 100, 10, 10);
        WINDOW * select = newwin(10, 26, 50, 5);
        WINDOW * info = newwin(10, 50, 50, 65);
        keypad(select, true);
        refresh();
        wrefresh(cs302);
        wrefresh(select);
        wrefresh(info);
        while(1){
            for(int i = 0; i < 2; i++){
                if(i == highlight)
                    wattron(select, A_REVERSE);
                mvwprintw(select, i+4, 1, choices[i].c_str());
                wattroff(select, A_REVERSE);
            }
            choice = wgetch(select);
            switch(choice){
                case KEY_UP:
                    highlight--;
                    if(highlight == -1)
                        highlight = 0;
                    break;
                case KEY_DOWN:
                    highlight++;
                    if(highlight == 2)
                        highlight = 1;
                    break;
                default:
                    break;
            }
            if(choice == 10)
                break;
        }
        if(choices[highlight] == "Counter-Terrorist"){
            x = mapSearchX('C');
            y = mapSearchY('C');
            point[y][x] = new point_t('@', x, y);
            player = new player_t(true, 'C', x, y);
            point[y][x]->entList.push_back(player);
        }
        else if(choices[highlight] == "Terrorist"){
            x = mapSearchX('T');
            y = mapSearchY('T');
            point[y][x] = new point_t('@', x, y);
            player = new player_t(true, 'C', x, y);
            point[y][x]->entList.push_back(player);
        }
        playerX = x;
        playerY = y;
        x = mapSearchX('B');
        y = mapSearchY('B');
        bombX = x;
        bombY = y;
        point[y][x] = new point_t('B', x, y);
        bomb = new bomb_t(x,y);
        point[y][x]->entList.push_back(bomb);

        mvprintw(47, 40, "Game Starting! Side: %s", choices[highlight].c_str());
        mvprintw(48, 42, "Press any button to continue");
    }
    void secondTick(){
        if(status != PLANTED)
            roundTimer--;
    }
    void bombTick(){
        if(status == PLANTED)
            bombTimer--;
    }
    bool checkRoundStatus(){
        if(roundTimer == 0 && bombTimer > 0){
            endcondition = 5;
        }
        else if(Talive == 0 && status != PLANTED){
            endcondition = 4;
        }
        else if(CTalive == 0 && Talive > 0){
            endcondition = 3;
        }
        else if(bombTimer == 0 && status == PLANTED){
            endcondition = 2;
        }
        else if(bombTimer > 0 && status == DEFUSED){
            endcondition = 1;
        }
        else{
            endcondition = 0;
        }
        if(endcondition != 0){
            return true;
        }
        else{
            getBombStatus();
            secondTick();
            bombTick();
            return false;
        }
    }
    ~Level(){
        if(point == NULL) return;
        for(int i=0; i < height; i++)
            delete [] point[i];
        delete [] point;
    }
};
class BallisticDispatcher{
public:
    std::vector<projectile_t*>projList;
    Level* level;
    BallisticDispatcher(Level* og){
        level = og;
    }
    void addProjectile(projectile_t* proj){
        projList.push_back(proj);
    }
    void updateAll(){
        for(int i = 0; i < projList.size(); i++){
            if(projList[i]->direction == 'u'){
                projList[i]->y--;
            }
            else if(projList[i]->direction == 'd'){
                projList[i]->y++;
            }
            else if(projList[i]->direction == 'l'){
                projList[i]->x--;
            }
            else if(projList[i]->direction == 'r'){
                projList[i]->x++;
            }
        }
    }
};


class MovementDispatcher{
public:
    static char readkeyinput(){
        keypad(stdscr, true);
        char choose;
        switch(wgetch(stdscr)){
            case KEY_UP:{
                choose = 'u';
                break;
            }
            case KEY_DOWN:{
                choose = 'd';
                break;
            }
            case KEY_LEFT:{
                choose = 'l';
                break;
            }
            case KEY_RIGHT:{
                choose = 'r';
                break;
            }
            case 'W':
            case 'w':{
                choose = 'u';
                break;
            }
            case 'A':
            case 'a':{
                choose = 'l';
                break;
            }

            case 'S':
            case 's':{
                choose = 'd';
                break;
            }
            case 'D':
            case 'd':{
                choose = 'r';
                break;
            }
            case 'Q':
            case 'q':{
                choose = 'q';
                break;
            }
            case 'C':
            case 'c':{
                choose = 'n';
                break;
            }
            case 'I':
            case 'i':{
                choose = 'n';
                break;
            }
            default:
                readkeyinput();
                break;
        }
        return choose;
    }
    static char makeMove(Level* lvl, player_t* p, char dir, BallisticDispatcher* ball){
        char temp;
        if(dir == 'u'){
            temp = lvl->point[lvl->playerY-1][lvl->playerX]->baseType;
            if(temp != 'x' && temp != 'o'){
                lvl->point[lvl->playerY-1][lvl->playerX]->baseType = lvl->point[lvl->playerY][lvl->playerX]->baseType;
                lvl->point[lvl->playerY][lvl->playerX]->baseType = temp;
                lvl->playerY--;
                p->y--;
            }
            p->previousDirection = dir;

        }
        else if(dir == 'd'){
            temp = lvl->point[lvl->playerY+1][lvl->playerX]->baseType;
            if(temp != 'x' && temp != 'o'){
                lvl->point[lvl->playerY+1][lvl->playerX]->baseType = lvl->point[lvl->playerY][lvl->playerX]->baseType;
                lvl->point[lvl->playerY][lvl->playerX]->baseType = temp;
                lvl->playerY++;
                p->y++;
            }
            p->previousDirection = dir;
        }
        else if(dir == 'l'){
            temp = lvl->point[lvl->playerY][lvl->playerX-1]->baseType;
            if(temp != 'x' && temp != 'o'){
                lvl->point[lvl->playerY][lvl->playerX-1]->baseType = lvl->point[lvl->playerY][lvl->playerX]->baseType;
                lvl->point[lvl->playerY][lvl->playerX]->baseType = temp;
                lvl->playerX--;
                p->x--;
            }
            p->previousDirection = dir;
        }
        else if(dir == 'r'){
            temp = lvl->point[lvl->playerY][lvl->playerX+1]->baseType;
            if(temp != 'x' && temp != 'o'){
                lvl->point[lvl->playerY][lvl->playerX+1]->baseType = lvl->point[lvl->playerY][lvl->playerX]->baseType;
                lvl->point[lvl->playerY][lvl->playerX]->baseType = temp;
                lvl->playerX++;
                p->x++;
            }
            p->previousDirection = dir;
        }
        else if(dir == 'n'){
            p->previousDirection = dir;
        }
        postMovementchecks(lvl, p);
        return dir;
    }
    static void postMovementchecks(Level* lvl, player_t *p){
        if(p->previousDirection == 'u'){
            if(lvl->point[lvl->playerY+1][lvl->playerX]->baseType == 'B'){
                lvl->point[lvl->playerY+1][lvl->playerX]->baseType = ' ';
                p->bomb =  dynamic_cast<bomb_t*>(lvl->point[lvl->playerY][lvl->playerX]->entList[0]);
                p->bomb->isCarried = true;
            }
            if(lvl->point[lvl->playerY+1][lvl->playerX]->baseType == 'P'){
                lvl->point[lvl->playerY+1][lvl->playerX]->baseType = lvl->point[lvl->playerY][lvl->playerX]->baseType;
                lvl->point[lvl->playerY][lvl->playerX]->baseType = 'P';
                if(p->bomb->isCarried == true){
                    lvl->point[lvl->playerY][lvl->playerX]->baseType = 'B';
                    p->bomb->isCarried = false;
                    p->bomb->isPlanted = true;
                }
                lvl->playerY++;
                p->y++;
            }
        }
        else if(p->previousDirection == 'd'){
            if(lvl->point[lvl->playerY-1][lvl->playerX]->baseType == 'B'){
                lvl->point[lvl->playerY-1][lvl->playerX]->baseType = ' ';
                p->bomb =  dynamic_cast<bomb_t*>(lvl->point[lvl->playerY][lvl->playerX]->entList[0]);
                p->bomb->isCarried = true;
            }
            if(lvl->point[lvl->playerY-1][lvl->playerX]->baseType == 'P'){
                lvl->point[lvl->playerY-1][lvl->playerX]->baseType = lvl->point[lvl->playerY][lvl->playerX]->baseType;
                lvl->point[lvl->playerY][lvl->playerX]->baseType = 'P';
                lvl->playerY--;
                p->y--;
            }
        }
        else if(p->previousDirection == 'l'){
            if(lvl->point[lvl->playerY][lvl->playerX+1]->baseType == 'B'){
                lvl->point[lvl->playerY][lvl->playerX+1]->baseType = ' ';
                p->bomb =  dynamic_cast<bomb_t*>(lvl->point[lvl->playerY][lvl->playerX]->entList[0]);
                p->bomb->isCarried = true;
            }
            if(lvl->point[lvl->playerY][lvl->playerX+1]->baseType == 'P'){
                lvl->point[lvl->playerY][lvl->playerX+1]->baseType = lvl->point[lvl->playerY][lvl->playerX]->baseType;
                lvl->point[lvl->playerY][lvl->playerX]->baseType = 'P';
                lvl->playerX++;
                p->x++;
            }
        }
        else if(p->previousDirection == 'r'){
            if(lvl->point[lvl->playerY][lvl->playerX-1]->baseType == 'B'){
                lvl->point[lvl->playerY][lvl->playerX-1]->baseType = ' ';
                p->bomb =  dynamic_cast<bomb_t*>(lvl->point[lvl->playerY][lvl->playerX]->entList[0]);
                p->bomb->isCarried = true;
            }
            if(lvl->point[lvl->playerY][lvl->playerX-1]->baseType == 'P'){
                lvl->point[lvl->playerY][lvl->playerX-1]->baseType = lvl->point[lvl->playerY][lvl->playerX]->baseType;
                lvl->point[lvl->playerY][lvl->playerX]->baseType = 'P';
                lvl->playerX--;
                p->x--;
            }
        }
    }
};


class AIDispatcher{
public:
    std::vector<player_t*> botList;
    player_t* human;
    bomb_t* bomb;
    Level* levelref;
    int totalBots;
    BallisticDispatcher* ballref;
    AIDispatcher(Level* lvl){
        levelref = lvl;
    }
    void addHuman(){
    }
    void addBot();
    void addBomb();
    AIDispatcher();
    void printStatus();
    void checkForNewDead();
    void updateAll();
};


int main(int argc, char **argv){
	srand(time(NULL)); //Comment out to always have the same RNG for debugging
    CharMap *map = (argc == 2) ? new CharMap(argv[1]) : NULL; //Read in input file
    if(map == NULL){printf("Invalid Map File\n"); return 1;}  //close if no file given
    initCurses();
    Level* dust_2 = new Level(map);
    AIDispatcher AI(dust_2);


    BallisticDispatcher* BD = new BallisticDispatcher(dust_2);
    MovementDispatcher* MD = new MovementDispatcher;
    dust_2->openNteamSelect();


    dust_2->bombX = dust_2->mapSearchX('B');
    dust_2->bombY = dust_2->mapSearchY('B');
    player_t* player1 = dynamic_cast<player_t*>(dust_2->point[dust_2->playerY][dust_2->playerX]->entList[0]);


    while(!dust_2->checkRoundStatus() && MD->makeMove(dust_2, player1, MD->readkeyinput(), BD) != 'q'){
        dust_2->clearScreen();
        dust_2->renderLevel();
    }

    delete map; map = NULL;
    printw("\n\nGame Over! Press ' esc ' to exit: \n");
    endCurses(); //END CURSES
    return 0;
}


void initCurses(){

    initscr();
    cbreak();

    keypad(stdscr, TRUE);
    noecho();
}


void endCurses(){
    refresh();
    do{
    }while(getch() != 27);//Make user press the esc key to close
    endwin();
}


//CharMap Functions
CharMap::CharMap(char *arg) {
    char temp;
    std::ifstream fin(arg);
    fin >> mapName;
    fin >> height;
    fin >> temp;
    fin >> width;
    map = new char *[height];
    //Allocate our 2D array
    for (int i = 0; i < height; i++) {
        map[i] = new char[width];

        for (int j = 0; j < width; j++) //Read into our array while we're at it!
            fin >> (map[i][j]) >> std::noskipws; //dont skip whitespace
        fin >> std::skipws; //skip it again just so we skip linefeed
    }
}

CharMap::~CharMap(){
    if(map == NULL) return;
    for(int i=0; i<height; i++)
        delete [] map[i];
    delete [] map;
}

void CharMap::print(){ //call only after curses is initialized!
    printw("Read Map: '%s' with dimensions %dx%d!\n",
           mapName.c_str(), height, width);
    //Note the c_str is required for C++ Strings to print with printw
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++)
            printw("%c", map[i][j]);
        printw("\n");
    }
}