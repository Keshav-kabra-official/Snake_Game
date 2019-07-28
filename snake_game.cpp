/*
 <iostream> and (namespace)'std' are included in header file -> FileHandle_SnakeGame.h
*/

#include<cstdlib>
#include<ctime>
#include<conio.h>
#include<windows.h>
#include "FileHandle_SnakeGame.h"

fstream fs;
bool game_over;
const int width=50,height=25;
int x,y,targetX,targetY,score;
int tailX[50],tailY[50],nTail; //for tail of snake
enum direction{STOP,LEFT,RIGHT,UP,DOWN};
direction dir;

void Score()
{
	cout<<"\n\n\n";
	cout<<"_____________________________________________"<<endl;
	cout<<"                SCORE = "<<score<<endl;
	cout<<"_____________________________________________";
}

void setup()
{
	game_over=false;
	
	nTail=0;
	//use the for/while loop to completely initialize the arrays
	//this will eliminate the warnings
	tailX[50]={0};
	tailY[50]={0};
	
	dir=STOP;
	
	//positioning snake at middle of box
	x=width/2;
	y=height/2;
	
	//generating fruit at random place within the box
	srand((unsigned)time(NULL));
	targetX=rand()%width;
	targetY=rand()%height;
	
	score=0;
}

void draw()
{
	system("cls");
	int i,j;
	
	for(i=0;i<width+2;i++) //top wall
		cout<<"_";
	cout<<endl;
	
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			if(j==0) //left wall
				cout<<(char)179; //for vertical lines
			if(i==y && j==x)
				cout<<"O";
			else if(i==targetY && j==targetX)
				cout<<"F";
			else
			{
				bool isPrint=false;
				for(int k=0;k<nTail;k++)
				{
					if(tailX[k]==j && tailY[k]==i)
					{
						cout<<"o";
						isPrint=true;
					}
				}
				if(isPrint==false)
					cout<<" ";
			}
				
			if(j==width-1) //right wall
				cout<<(char)179;
		}
		cout<<endl;
	}
	for(i=0;i<width+2;i++) //bottom wall
		cout<<(char)196; //horizontal line
		
	cout<<endl;
	
	Score();
	cout<<endl;
}

void input()
{
	if(kbhit())
	{
		switch(getch())
		{
			case 'K': //use left arrow
			case 'a':
				dir=LEFT;
				break;
			case 'M': //use right arrow
			case 'd':
				dir=RIGHT;
				break;
			case 'H': //use up arrow
			case 'w':
				dir=UP;
				break;
			case 'P': //use down arrow
			case 's':
				dir=DOWN;
				break;
			case 'x':
				game_over=true;
				break;
			
		}
	}
}

void logic()
{
	// for the movement of tail
	int prev_x_coord=tailX[0];
	int prev_y_coord=tailY[0];
	int x_coord_temp,y_coord_temp;
	tailX[0]=x;
	tailY[0]=y;
	for(int i=1;i<=nTail;i++)
	{
		x_coord_temp = tailX[i];
		y_coord_temp = tailY[i];
		tailX[i] = prev_x_coord;
		tailY[i] = prev_y_coord;
		prev_x_coord = x_coord_temp;
		prev_y_coord = y_coord_temp;
	}
	
	switch(dir)
	{
		case(LEFT):
			x--;
			break;
		case(RIGHT):
			x++;
			break;
		case(UP):
			y--;
			break;
		case(DOWN):
			y++;
			break;
	}
	
	if(x>width || x<0 || y>height || y<0) //if hitted by walls
		game_over=true;
	
	for(int i=0;i<nTail;i++)  //if hitted by its own body
		if(tailX[i]==x && tailY[i]==y)
			game_over=true;
	
	//if fruit is eaten
	if(x==targetX && y==targetY)
	{
		score+=10;
		srand((unsigned)time(NULL));
		targetX=rand()%width;
		targetY=rand()%height;
		nTail++;
	}
}

int main()
{
	int again,first_time=0,flag=0;
	cout<<"CONTROLS :\n\n";
	cout<<" 'w' or up-arrow for moving up\n";
	cout<<" 's' or down-arrow for moving down\n";
	cout<<" 'a' or left-arrow for moving left\n";
	cout<<" 'a' or right-arrow for moving right\n";
	cout<<" 'x' to halt the game at any time\n";
	cout<<"\nPress any key to get started : ";
	getch();
	
	while(1)
	{
		setup();
		while(game_over!=true)
		{
			draw();
			input();
			logic();
			Sleep(10); //slowing console(declared in windows.h)
		}
		
		file_handle(fs,first_time,score,flag);
		
		cout<<"\nTry again (1 for YES) : ";
		cin>>again;
		
		if(again!=1)
		{
			file_close(fs);
			cout<<"\n\nProgram designed by : KESHAV KABRA\n";
			cout<<"\nPress any key to halt the game ...";
			getch();
			exit(0);
		}
	}
}
