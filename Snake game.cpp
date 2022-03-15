#include<iostream>
#include <stdio.h>
#include <conio.h>
#include<ctime> 
#include "windows.h" 
#define KEY_NONE	-1
#define MAX 100
using namespace std;
int whereX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}
int whereY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}
void gotoXY(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x, y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
int sl=3;
void ve_tuong_tren() {
	int x=10,y=1;
	while(x<=70) {
		gotoXY(x,y);
		cout<<"+";
		x++;
	}
}
void ve_tuong_duoi() {
	int x=10,y=20;
	while(x<=70) {
		gotoXY(x,y);
		cout<<"+";
		x++;
	}
}
void ve_tuong_phai() {
	int x=70,y=1;
	while(y<=20) {
		gotoXY(x,y);
		cout<<"+";
		y++;
	}
}
void ve_tuong_trai() {
	int x=10,y=1;
	while(y<=20) {
		gotoXY(x,y);
		cout<<"+";
		y++;
	}
}
void ve_tuong() {
	ve_tuong_tren();
	ve_tuong_duoi();
	ve_tuong_phai();
	ve_tuong_trai();
}
void ve_ran(int toadox[],int toadoy[]) {
	for(int i=0;i<sl;i++) {
		gotoXY(toadox[i],toadoy[i]);
		if(i==0) {
			cout<<"O";
		}
		else {
			cout<<"o";
		}
	}
}
void xoa_du_lieu_cu(int toadox[],int toadoy[]) {
	for(int i=0;i<sl;i++) {
		gotoXY(toadox[i],toadoy[i]);
		cout<<" ";
	}
}
void khoi_tao_ran(int toadox[],int toadoy[]) {
	int x=30,y=10;
	for(int i=0;i<sl;i++) {
		toadox[i]=x;
		toadoy[i]=y;
		x--;
	}
}
void them(int a[],int x) {
	for(int i=sl;i>0;i--) {
		a[i]=a[i-1];
	}
	a[0]=x;
	sl++;
}
void xoa(int a[],int vt) {
	for(int i=vt;i<sl;i++) {
		a[i]=a[i+1];
	}
	sl--;
}
bool ran_cham_tuong(int x,int y) {
	if(y==1 &&(x>=10 && x<=70)) {
		return true;
	}
	else if(y==20 &&(x>=10 && x<=70)) {
		return true;
	}
	else if(x==70 &&(y>=1 && y<=20)) {
		return true;
	}
	else if(x==10 &&(y>=1 && y<=20)) {
		return true;
	}
	return false;
}
bool ran_cham_duoi(int toadox[],int toadoy[]) {
	for(int i=1;i<sl;i++) {
		if(toadox[0]==toadox[i] && toadoy[0]==toadoy[i]) {
			return true;
		}
	}
	return false;
}
bool kt_ran(int toadox[],int toadoy[]) {
	bool kt1=ran_cham_duoi(toadox,toadoy);
	bool kt2=ran_cham_tuong(toadox[0],toadoy[0]);
	if(kt1==true || kt2==true) {
		return true;
	}
	return false;
}
bool kt_ran_de_an_qua(int x,int y,int toadox[],int toadoy[]) {
	for(int i=0;i<sl;i++) {
		if((x==toadox[i])&&(y=toadoy[i])) {
			return true;
		}
	}
	return false;
}
void tao_qua(int &xqua,int &yqua,int toadox[],int toadoy[]) {
	do {
		xqua=rand()%(69-11+1)+11;
		yqua=rand()%(19-2+1)+2;	
	}while(kt_ran_de_an_qua(xqua,yqua,toadox,toadoy)==true);
	gotoXY(xqua,yqua);
	cout<<"*";
}
bool kt_ran_an_qua(int xqua,int yqua,int x,int y) {
	if((x==xqua)&&(y==yqua)) {
		return true;
	}
	return false;
}
void xu_li_ran(int toadox[],int toadoy[],int x,int y,int &xqua,int &yqua) {
	them(toadox,x);
	them(toadoy,y);
	if(kt_ran_an_qua(xqua,yqua,toadox[0],toadoy[0])==false) {
		xoa(toadox,sl-1);
		xoa(toadoy,sl-1);
	}
	else {
		sl--;
		tao_qua(xqua,yqua,toadox,toadoy);	
	}
	ve_ran(toadox,toadoy);
}
int main() {
	srand(time(NULL));
	bool gameover=false;
	int xqua=0,yqua=0;
	int toadox[MAX],toadoy[MAX];
	ve_tuong();
	khoi_tao_ran(toadox,toadoy);	
	ve_ran(toadox,toadoy);
	tao_qua(xqua,yqua,toadox,toadoy);
	int x=30,y=10;
	int check=2;
	while(gameover==false) {
		xoa_du_lieu_cu(toadox,toadoy);
		if(kbhit()) {
			char kitu=getch();
			if(kitu==-32) {
				kitu=getch();
				if(kitu== 72 && check!=0) { //di len
					check=1;
				}
				else if(kitu==80 && check!=1)  { //di xuong
					check=0;
				}
				else if(kitu==75 && check!=2) { //di qua trai
					check=3;
				}
				else if(kitu==77 && check!=3) {//di qua phai
					check=2;
				}
			}
		}
		if(check==0) {
			y++;//di len
		}
		else if(check==1) {
			y--;//di xuong
		}
		else if(check==2) {
			x++; // di qua phai
		}
		else if(check==3) {
			x--;//di qua trai
		}
		xu_li_ran(toadox,toadoy,x,y,xqua,yqua);
		gameover=kt_ran(toadox,toadoy);
		Sleep(150);
	}
	getch();
	return 0;
}