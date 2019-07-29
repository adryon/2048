#include <iostream>
#include <windows.h>
#include <iomanip>
#include <math.h>
#include <conio.h>
using namespace std;

COORD Position;
int i,j,k,v[5][5],score=0,ok=1,a[14]={255,124,124,124,207,207,207,224,224,224,95,95,95},c[5][5],inc=3;
char ch,ci;

void DrawTable()
{
	for (i=1; i<=4; i++)
		for (j=1; j<=4; j++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a[v[i][j]]);
			Position.X=26+(j-1)*6; Position.Y=6+(i-1)*4; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position);
			cout<<"     "; Position.Y++; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position);
			if (v[i][j]!=0) cout<<setw(5)<<pow(2,v[i][j]);
			else cout<<"     "; Position.Y++; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position);
			cout<<"     ";
		}
}

void NewTileAnimation(int xx, int yy, int x, int y)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),124);
	COORD Position={xx+2, yy};
	for (Position.Y=yy; Position.Y<=yy+2; Position.Y++){ SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position); cout<<" ";}
	Sleep(70);
	for (Position.Y=yy; Position.Y<=yy+2; Position.Y++)
	{
		Position.X=xx+1; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position); cout<<" ";
		Position.X=xx+3; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position); cout<<" ";
	}
	Sleep(70);
	for (Position.Y=yy; Position.Y<=yy+2; Position.Y++)
	{
		Position.X=xx; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position); cout<<" ";
		Position.X=xx+4; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position); cout<<" ";
	}
}

void GetNewTile()
{
	i=rand()%16;
	while (v[i/4+1][i%4+1]) i=rand()%16;
	if (rand()%100>90) v[i/4+1][i%4+1]=2;
	else v[i/4+1][i%4+1]=1;
	NewTileAnimation(26+(i%4)*6,6+(i/4)*4,i/4+1,i%4+1); DrawTable();
}

void InitGame(int x, int y)
{
	cout<<"                                -2048 GAME-\n";
	cout<<"                           -Game made by Adryon-";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	for (i=x+1; i<=x+24; i++)
	{
		Position.X=i; Position.Y=y; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position); cout<<"-";
		Position.Y=y+16; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position); cout<<"-";
	}
	for (i=y+1; i<=y+15; i++)
	{
		Position.X=x; Position.Y=i; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position); cout<<"|";
		Position.X=x+24; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position); cout<<"|";
	}
	Position.X=x; Position.Y=y; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position); cout<<(char)218;
	Position.Y=y+16; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position); cout<<(char)192;
	Position.X=x+24; Position.Y=y; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position); cout<<(char)191;
	Position.Y=y+16; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position); cout<<(char)217;
	srand(time(0));
	GetNewTile(); GetNewTile();
	DrawTable();
}

void MoveTile(int g)
{
	if (g==1)
		for (i=1; i<=4; i++)
		{
			j=4; k=3;
			while (j>=2 && k>=1)
				if ((v[j][i]==0 && v[k][i]==0) || (v[j][i]!=0 && v[k][i]==0)) k--;
				else if (v[j][i]==0 && v[k][i]!=0)
				{ 
					v[j][i]=v[k][i];
					v[k][i]=ok=0;
					k=j-1;
				}
				else if (v[k][i]==v[j][i] && v[j][i]!=0)
				{
					score+=pow(2,v[j][i]);
					v[j--][i]++;
					v[k][i]=ok=0;
					k=j-1;
				}
				else if (v[k][i]!=v[j--][i]) k=j-1;
		}
	else if (g==2)
		for (i=1; i<=4; i++)
		{
			j=1; k=2;
			while (j<=3 && k<=4)
				if ((v[j][i]==0 && v[k][i]==0) || (v[j][i]!=0 && v[k][i]==0)) k++;
				else if (v[j][i]==0 && v[k][i]!=0)
				{ 
					v[j][i]=v[k][i];
					v[k][i]=ok=0;
					k=j+1;
				}
				else if (v[k][i]==v[j][i] && v[j][i]!=0)
				{
					score+=pow(2,v[j][i]);
					v[j++][i]++;
					v[k][i]=ok=0;
					k=j+1;
				}
				else if (v[k][i]!=v[j++][i]) k=j+1;
		}
	else if (g==3)
		for (i=1; i<=4; i++)
		{
			j=4; k=3;
			while (j>=2 && k>=1)
				if ((v[i][j]==0 && v[i][k]==0) || (v[i][j]!=0 && v[i][k]==0)) k--;
				else if (v[i][j]==0 && v[i][k]!=0)
				{ 
					v[i][j]=v[i][k];
					v[i][k]=ok=0;
					k=j-1;
				}	
				else if (v[i][k]==v[i][j] && v[i][j]!=0)
				{
					score+=pow(2,v[i][j]);
					v[i][j--]++;
					v[i][k]=ok=0;
					k=j-1;
				}
				else if (v[i][k]!=v[i][j--]) k=j-1;
		}
	else for (i=1; i<=4; i++)
	{
		j=1; k=2;
		while (j<=3 && k<=4)
			if ((v[i][j]==0 && v[i][k]==0) || (v[i][j]!=0 && v[i][k]==0)) k++;
			else if (v[i][j]==0 && v[i][k]!=0)
			{ 
				v[i][j]=v[i][k];
				v[i][k]=ok=0;
				k=j+1;
			}
			else if (v[i][k]==v[i][j] && v[i][j]!=0)
			{
				score+=pow(2,v[i][j]);
				v[i][j++]++;
				v[i][k]=ok=0;
				k=j+1;
			}
			else if (v[i][k]!=v[i][j++]) k=j+1;
	}
}

int EndGame()
{
	int ok=1;
	for (i=1; i<=3; i++)
		for (j=1; j<=3; j++)
			if ((v[i][j]==v[i][j+1] || v[j][i]==v[j+1][i] && ok==1) || (v[i][j]==0 || v[i][j+1]==0 || v[j][i]==0 || v[j+1][i]==0)) ok=0;
	return ok;
}

int main()
{
	InitGame(25,5);
	while(1)
	{
		Position.X=3; Position.Y=7; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15); cout<<"Score: "<<score<<"\n\n   [U] Undo: "<<inc;
		ci=_getch();
		if (ci==-32)
		{
			for (i=1; i<=4; i++)
				for (j=1; j<=4; j++) 
					c[i][j]=v[i][j];
			ch=_getch();
			if (ch==80) MoveTile(1);
			else if (ch==72) MoveTile(2);
			else if (ch==77) MoveTile(3);
			else if (ch==75) MoveTile(4);
			DrawTable();
			if (!ok){ GetNewTile(); ok=1;}
			if (EndGame()==1) break;
		}
		else if ((ci=='u' || ci=='U') && inc>0)
		{
			for (i=1; i<=4; i++)
				for (j=1; j<=4; j++)
					v[i][j]=c[i][j];
			inc--;
			DrawTable();
		}
	}
}
