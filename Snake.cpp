#include<iostream>
#include<Windows.h>
#include<conio.h>
#include <cstdlib> 
#include <ctime> 

using namespace std;

void recombine(int posx[1000],int posy[1000],char &a,int &posX,int &posY,int &lastX,int &lastY,char &b,int rex[1000],int rey[1000]){
	posx[0]=posX;
	posy[0]=posY;
for(int i=0;i<1000;i++){

	rex[i]=posx[i];
	rey[i]=posy[i];
}
	
	for(int j=0;j<1000;j++){
	posx[j]=rex[j-1];
	posy[j]=rey[j-1];	
	}
	
}

void lose(int posX,int posY,int len,int posx[1000],int posy[1000]){
	if(posX<=0 or posY<=0 or posX>=19 or posY>=49  ){
		system("cls");
	cout<<"Your score is:"<<len-1<<endl;	
	getch();
		exit(0);
	}
	for(int i=1;i<len;i++){
		if(posX==posx[i] and posY==posy[i]){
		system("cls");
	cout<<"Your score is:"<<len-1<<endl;	
	getch();
		exit(0);	
		}
	}
}

void control(int posx[1000],int posy[1000],char &a,int &posX,int &posY,int &lastX,int &lastY,char &b){
	if(_kbhit()){
		a=getch();
		if(a=='w' or a=='a' or a=='s' or a=='d'){
			if(a=='w' and b!='s'){
				b=a;
			}	
			if(a=='a' and b!='d'){
				b=a;
			}
			if(a=='s' and b!='w'){
				b=a;
			}
			if(a=='d' and b!='a'){
				b=a;
			}		
}
		
	if(b=='w'){
		lastY=posY;
		lastX=posX;
		posX--;
	}
	
	if(b=='d'){
		lastY=posY;
		lastX=posX;
		posY++;
	}
	
	if(b=='a'){
		lastY=posY;
		lastX=posX;
		posY--;
	}
	
	if(b=='s'){
		lastY=posY;
		lastX=posX;
		posX++;
	}
	}
	else{
		if(b=='w'){
		lastY=posY;
		lastX=posX;
		posX--;
	}
	
	if(b=='d'){
		lastY=posY;
		lastX=posX;
		posY++;
	}
	
	if(b=='a'){
		lastY=posY;
		lastX=posX;
		posY--;
	}
	
	if(b=='s'){
		lastY=posY;
		lastX=posX;
		posX++;
	}
	}	
}
	
	
	
	
	



void matrix(int pos[1000]){
	for(int i=0;i<1000;i++){
		pos[i]=255;
	}
}
	



void construct(char M[20][50],int posx[1000],int posy[1000],int posX,int posY,int foodX,int foodY,int len,int &lastX,int &lastY){
	for(int i=0;i<20;i++){
		for(int j=0;j<50;j++){
			if(i==0 or i==19 or j==0 or j==49){
				M[i][j]='#';
			}
			else if(foodX==i and foodY==j){
				M[i][j]='!';
			}
			else if(i==posX and j==posY){
				M[i][j]='O';
			}
			else{	
				M[i][j]=' ';
			}
			for(int k=0;k<len;k++){
				if(i==posx[k] and j==posy[k] and posx[k]<255 and posy[k]<255){
					M[i][j]='o';
					}
			}
				
		}
	}
}
	

void eat(int posX,int posY,int &foodX,int &foodY,int &len){
	if(posX==foodX and posY==foodY){
			len=len+1;
			srand((unsigned)time(0)); 	
			foodY= (rand()%47)+1;
			srand((unsigned)time(0)); 	
			foodX= (rand()%17)+1;
			if(foodY<1 or foodY>49 or foodX<1 or foodX>19){
				srand((unsigned)time(0)); 	
				foodY= (rand()%47)+1;
				srand((unsigned)time(0)); 	
				foodX= (rand()%17)+1;
		}
	}
}


void print(char M[20][50],int len,int posx[1000],int posy[1000],int posX,int posY){
	system("cls");
	for(int i=0;i<20;i++){
		for(int j=0;j<50;j++){
			cout<<M[i][j];
		}
		cout<<endl;
	}
	Sleep(120);
}

int main(){
	system("Color 0A");
	srand((unsigned)time(0)); 	
	
	int posX=10;
	int posY=25;
	int posx[1000];
	int posy[1000];
	int lastX;
	int lastY;
	int rex[1000];
	int rey[1000];
	int len=1;
	int foodY= (rand()%50)+1;
	int foodX= (rand()%20)+1;
	char M[20][50];
	char a;
	char b='w';

	matrix(posx);
	matrix(posy);

	cout<<"You control the snake with 'w','a','s','d'.\n\nPRESS ANY KEY TO CONTINUE"<<endl;
	getch();

	while (true){
		construct(M,posx,posy,posX,posY,foodX,foodY,len,lastX,lastY);
		print(M,len,posx,posy,posX,posY);	
		recombine(posx,posy,a,posX,posY,lastX,lastY,b,rex,rey);
		control(posx,posy,a,posX,posY,lastX,lastY,b);
		eat(posX,posY,foodX,foodY,len);
		lose(posX,posY,len,posx,posy);
	}
}
