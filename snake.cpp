
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <fstream>

using namespace std;

//==== struct list;

typedef struct tailpos
{
       int x;                // x cordinate of the snake
       int y;                // y cordinate of the snake
       struct tailpos *next; // pointer to next node
       struct tailpos *prev; // pointer to previous node
} tail;

// d used to set the direction
int d = 4; // up = 1 , down = 2 , left =3 , right = 4;

/*
SNAKE CLASS 
            contain variable of tailpos structure
            this class handle movement of the snake
            contain the draw function

*/
class snake
{
public:
       int wallsX, wallsY; // wall start position can be use to define wall
       int walleX, walleY; // wall end position

       int score; // keep score

       int fruitx, fruity; // position of the fruit

       HANDLE console_handle; // handle for the console
       COORD cord_cur;        // COORD struct to keep the coordinate

       /*
       tail struct ==>
                      start = pointer to first part of body
                      current = pointer to last node
                      newtail = temp node for new tail
       
       */

       tail *start, *current, *newtail;
       snake();                   // construct to initalise tail variable to null
       void insert(int x, int y); // insert the body of snake append to next node
       void draw();               // draw the snake
       void drawWall();           // draw the wall
       void move();               // control the movement
       bool collision();          //check snake collision with itself or wall
       void drawfruit(int x = 0);  // draw fruit to new position if x==1
       void drawinit();           // inital setup like draw wall
       void labelDead();          // Draw when player is dead
       void menu();               // menu screen
       void help();               // menu for help
};

/*
=====================================
prototype for loop function
*/
void loop(snake &ob);

//================================
// implement snake class
snake::snake()
{

       score = 0; // set the initial score

       start = NULL;                                     // start node point to null
       current = NULL;                                   // same
       newtail = NULL;                                   // same
       console_handle = GetStdHandle(STD_OUTPUT_HANDLE); // getting console handle

       fruitx = 12; // starting fruit positions
       fruity = 14;

       wallsX = 2;
       wallsY = 2; // walls starting and ending position
       walleX = 70;
       walleY = 20; // dwar wall of 70x50

       cord_cur.X = 152;
       cord_cur.Y = 500;
       SetConsoleScreenBufferSize(console_handle, cord_cur); // setting up screen buffer
}
/*
this method is to insert new tail of snake at the current fruit position when snake eat it.

*/
void snake ::insert(int x, int y)
{
       // check if start is null
       if (start == NULL)
       {
              newtail = new tail;
              newtail->x = x;
              newtail->y = y;
              newtail->next = NULL;
              newtail->prev = NULL;
              start = newtail;
              current = newtail;
       }
       else // insert new node to start node
       {
              newtail = new tail;
              newtail->x = x;
              newtail->y = y;
              newtail->next = NULL;
              newtail->prev = current;
              current->next = newtail;
              current = newtail;
       }
}


void snake::move()
{
       tail *tmp, *cur;

       tmp = current; // point tmp to last node
       //cur =start->next;

       while (tmp->prev != NULL)
       {
              tmp->x = tmp->prev->x; // copy val from revious to last
              tmp->y = tmp->prev->y;
              tmp = tmp->prev; // set tmp to previous node
       }
       /*
check for the value of d in order to change its direction
increment and decrement value of x , y
*/
       if (d == 1)
              start->y--;

       if (d == 2)
              start->y++;

       if (d == 3)
              start->x--;

       if (d == 4)
              start->x++;
}

/*
draw :
      draw snake part according to their position
      traverse the node from start to end
*/
void snake::draw()
{
       /*
cord_cur.X=10;
cord_cur.Y=5;

SetConsoleCursorPosition(console_handle,cord_cur);
cout << "use above statement to to set cursor position";   
*/

       // putting score label
       cord_cur.X = 2;
       cord_cur.Y = 0;

       SetConsoleCursorPosition(console_handle, cord_cur);
       cout << "SCORE : " << score;

       tail *tmp, *last;
       tmp = start;
       last = current;

       while (tmp != NULL)
       {
              cord_cur.X = tmp->x;
              cord_cur.Y = tmp->y;
              SetConsoleCursorPosition(console_handle, cord_cur);
              //cout << "*" << cord_cur.X <<"-" <<  cord_cur.Y  ;
              cout << (char)219; // snake character
              tmp = tmp->next;
       }
       // remove tail
       cord_cur.X = last->x;
       cord_cur.Y = last->y;
       SetConsoleCursorPosition(console_handle, cord_cur);
       cout << ' ';
       //draw the fruit
       cord_cur.X = fruitx;
       cord_cur.Y = fruity;
       SetConsoleCursorPosition(console_handle, cord_cur);
       cout << (char)15; // fruit character
}

void snake::drawWall()
{
       /*
     for drawing wall you can use variables to store wall starting and ending position
     */
       //int size = sizeof(wall)/sizeof(wall[0][0]);
       // draw left column
       cord_cur.X = wallsX;
       for (int y = wallsY; y <= walleY; y++)
       {
              cord_cur.Y = y;
              SetConsoleCursorPosition(console_handle, cord_cur);
              cout << '#';
       }
       // draw top row
       cord_cur.Y = wallsY;
       for (int x = wallsX; x <= walleX; x++)
       {
              cord_cur.X = x;
              SetConsoleCursorPosition(console_handle, cord_cur);
              cout << '#';
       }
       // draw right column
       cord_cur.X = walleX;
       for (int y = wallsY; y <= walleY; y++)
       {
              cord_cur.Y = y;
              SetConsoleCursorPosition(console_handle, cord_cur);
              cout << '#';
       }

       // draw bottom row
       cord_cur.Y = walleY;
       for (int x = wallsX; x <= walleX; x++)
       {
              cord_cur.X = x;
              SetConsoleCursorPosition(console_handle, cord_cur);
              cout << '#';
       }
}

void snake::drawfruit(int x) // no use of int x here
{
       tail *tmp;
       tmp = start;
       if (x == 1) // draw new fruit
       {
              fruitx = rand() % 2 + 39; // rand number between 2-39
              fruity = rand() % 2 + 16; // it will better to use wall ends position walleX,Y
              /*check if fruit not created on snake body
                         so we will loop through all snake node and check 
                         if snake body pos meet with fruit position
                         if yes the generate new position else continue
                         */
              while (tmp->next != NULL)
              {
                     if (fruitx == tmp->x && fruity == tmp->y)
                     {
                            drawfruit(1);
                            cout << "drawn";
                     }

                     tmp = tmp->next;
              }
       }
}

void snake::drawinit()
{
       drawWall();
}

/*
decect if snake collided with it self or wall or fruit
*/
bool snake::collision()
{
       tail *tmp;
       tmp = start->next;
       //check collision with itself
       while (tmp->next != NULL)
       {
              if (start->x == tmp->x && start->y == tmp->y)
                     return true;

              tmp = tmp->next;
       }
       //check collision with fruit
       if (start->x == fruitx && start->y == fruity)
       {
              insert(fruitx, fruity); // insert new tail
              drawfruit(1);          // get new fruit position
              score++;              // update score
       }

       //check collision with wall
       //collision top row
       for (int x = wallsX; x <= walleX; x++)          // getting x coordinadte
       {                                               // y cordinate remain same y=0 because in row x increase in same y
              if (start->x == x && start->y == wallsY) // getting y coordinte to get complete x,y cordinate
              {
                     return true;
              }
       }
       //collision left column
       for (int y = wallsY; y <= walleY; y++)
       {
              if (start->x == wallsX && start->y == y) // x same y chamge x=0
              {
                     return true;
              }
       }
       //collision right column
       for (int y = wallsY; y <= walleY; y++)
       {
              if (start->x == walleX && start->y == y) // right column threfore x ending point(same) with y changing
              {
                     return true;
              }
       }
       //collision bottom row
       for (int x = wallsX; x <= walleX; x++)
       {
              if (start->x == x && start->y == walleY)
              {
                     return true;
              }
       }

       return false; // return false no collison
}
/*
draw thing when player is dead
*/
void snake::labelDead()
{

       cord_cur.X = (walleX / 2);
       cord_cur.Y = (walleY / 2);

       SetConsoleCursorPosition(console_handle, cord_cur);

       cout << "YOU ARE DEAD\n";

       cord_cur.Y = (walleY / 2) + 1;
       SetConsoleCursorPosition(console_handle, cord_cur);
       cout << "YOUR HIGH SCORE IS " << score;
}

/*
	menu screen of the game
*/

void snake::menu()
{
       char word;
       ifstream iFile("menu.txt");
       word = iFile.get();
       while (iFile)
       {

              cout << word;
              word = iFile.get();
       }
       iFile.close();
       // get the menu
}

/*
help menu for snake
*/
void snake::help()
{
       char word;
       ifstream iFile("help.txt");
       word = iFile.get();
       while (iFile)
       {

              cout << word;
              word = iFile.get();
       }
       iFile.close();

       getch(); // wait for key to press
}

//===== main function
int main()
{
       // displaying the menu
       snake obc;
       obc.menu();
       switch (getch())
       {
       case 'z':
              system("CLS");
              loop(obc);
              break;
       case 'h':
              system("CLS");
              obc.help();
              system("CLS");
              main();
              break;
       case 'q':
              break;
       default:
              system("CLS");
              main();
       }

       return 0;
}

// loop controls the game
void loop(snake &ob)
{
       ob.insert(10, 6); // first is head  snake drawn from first to last
       ob.insert(10, 7);
       ob.insert(10, 8);
       ob.insert(10, 9);

       ob.drawinit(); // this will just draw wall
       int dir = 1;
       while (1)
       {
              ob.draw();
              Sleep(200); // waiting time
                          //system("CLS");
                          //clearScreen();

              if (ob.collision()) // chek if collision with wall or itselfoccur
              {
                     ob.labelDead(); // do when snake is dead
                     break;
              }

              if (kbhit()) // check if keyboard key is pressed
              {
                     switch (getch())
                     {
                     case 'w':
                            d = 1;
                            break;
                     case 's':
                            d = 2;
                            break;
                     case 'a':
                            d = 3;
                            break;
                     case 'd':
                            d = 4;
                            break;
                     case 'm':
                            ob.insert(10, 7);
                            break;
                     }
                     // cout << "fruit";		// not needed
              }

              ob.move();
       }
       int x;
       cin >> x;
}
