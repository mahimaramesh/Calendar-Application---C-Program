#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

#define SPACE 32
#define Horizontal_Line 196
#define Vertical_Line 179
#define Top_T 194
#define Bottom_T 193
#define Left_T 218
#define Right_T 191
#define Left_Side_T 195
#define Right_Side_T 180
#define Left_Bottom 192
#define Right_Bottom 217
#define CROSS 197
#define Back_Space 8
#define TOTCOL 80
#define TOTROW 25
#define WIDTH 5
#define DIM 7
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int isLeap(int yr)
{
	return ((yr%4==0) && (yr%100!=0) || (yr%400==0)) ? TRUE : FALSE;
}

void colHeading(void)
{
	int col;
	int row;
	char * colNames[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
	col = (TOTCOL - ((WIDTH * DIM) + (DIM + 1))) / 2; //18
	row = (TOTROW - (DIM + (DIM + 1))) / 2; //5 
	row += 1;
	col += 2;
	int ctr;
	for(ctr = 0; ctr < DIM; ctr += 1)
	{
		gotoxy(col + (ctr * (WIDTH + 1)), row); //0,0...
		printf("%s",colNames[ ctr ]);
	}
}

int DayOfWeek( int y, int m, int d ) /* returns Day of Week:
0 = Sunday, 1= Monday...
*/
{
static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
y -= m < 3; // for Jan & Feb
return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7; //Tomohiko Sakamoto’s Algorithm (find day of the week)
} 

void calendar(int month, int year)
{
	int days_in_month[] = {0,31,28,30,31,30,31,31,30,31,30,31};
	char *monthName[] = {"","January","February","March","April","May","June",\
	"July","August","September","October","November","December"};
	int row;
	int col;
	col = (TOTCOL - ((WIDTH * DIM) + (DIM + 1))) / 2; //18
	row = (TOTROW - (DIM + (DIM + 1))) / 2; //5
	row += 3;
	col += 3;
	int ctr;
	int day;
	gotoxy(30, 3);
	printf("%10s, %d",monthName[month], year);
	cleaner();
	if(isLeap(year) == TRUE)
	{
		days_in_month[2] = 29;
	}
	else
	    days_in_month[2] = 28;
	for(day = 1, ctr = DayOfWeek(year,month,1); day <= days_in_month[month]; day += 1)
	{
		gotoxy(col + (ctr * (WIDTH+1)), row);
		printf("%02d",day);
		ctr += 1;
		if(ctr == DIM)
		{
			row += 2;
			ctr = 0;
		}
	}
	
}

void cleaner(  )
{
	int col;
	int row;
	char * colNames[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
	col = (TOTCOL - ((WIDTH * DIM) + (DIM + 1))) / 2; //18
	row = (TOTROW - (DIM + (DIM + 1))) / 2; //5 
	row += 3;
	col += 3;
	int ctr;
	int week;
	for(week = 0; week < 6; week += 1)
	{
		for(ctr = 0; ctr < DIM; ctr +=1)
		{
		gotoxy(col + (ctr * (WIDTH + 1)), row); 
		printf("  ");
	   }
	}
}

void drawBox(void)
{
	int col, row;
	int ctr1, ctr2, ctr3;
	col = (TOTCOL - ((WIDTH * DIM) + (DIM + 1))) / 2; //18
	row = (TOTROW - (DIM + (DIM + 1))) / 2; //5
	gotoxy(col, row);
	printf("%c",Left_T);
	for(ctr2 = 0; ctr2 < DIM; ctr2 += 1)
	{
		for(ctr1 = 0; ctr1 < WIDTH; ctr1 +=1)
			printf("%c",Horizontal_Line);
		printf("%c",Top_T);
    }
    printf("%c",Back_Space);
    printf("%c",Right_T);
    // 1st line end
    
	for( ctr3 = 0; ctr3 < DIM ; ctr3 += 1)
    {
	    row+=1;
	    gotoxy(col, row);
	    for( ctr2 = 0;ctr2 <= DIM; ctr2 += 1)
	    {
		    printf("%c", Vertical_Line);
		    for( ctr1 = 0; ctr1 < WIDTH; ctr1+=1)
		    	printf("%c", SPACE);
	    }
	    row+=1;
	    gotoxy(col, row);
	    printf("%c", Left_Side_T);
	    for( ctr2 = 0; ctr2 < DIM; ctr2 +=1)
	    {
		    for( ctr1 = 0; ctr1 < WIDTH; ctr1+=1)
		    	printf("%c", Horizontal_Line);
		    printf("%c", CROSS);
	    }
	    printf("%c%c", Back_Space, Right_Side_T);
    }
    gotoxy(col, row);
    printf("%c",Left_Bottom);
    for(ctr2 = 0; ctr2 < DIM; ctr2 += 1)
    {
	    for(ctr1 = 0; ctr1 < WIDTH; ctr1 += 1)
	       printf("%c",Horizontal_Line);
	    printf("%c",Bottom_T);
    }
    printf("%c%c",Back_Space,Right_Bottom);
}

int main()
{
	int month;
	int year;
	int key;
	month = 5;
	year = 2004;
	drawBox();
	colHeading();
	
	do
	{
		calendar(month, year);
		key = getch();
		if(key != 27)
		key = getch();
		switch(key)
		{
			case LEFT : month-=1; break;
			case RIGHT : month+=1; break;
			case DOWN : year-=1; break;
			case UP : year+=1; 
		}
		if(month == 0)
		{
			year -= 1;
			month = 12;
		}
		else if(month > 12)
		{
			year += 1;
			month = 1;
		}
	}
	while(key != 27);
	getch();
	
	return EXIT_SUCCESS;
}
