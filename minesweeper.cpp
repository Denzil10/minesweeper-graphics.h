#include<graphics.h>
#include<iostream>
#include<stdio.h>
#include <stdlib.h>
#include<time.h>

//devloper options
#define bsize 12
#define no_of_bombs 2
#define difficulty 3
#define timer 30
#define bonus time 30

using namespace std;
int x,y,openedblocks=0;
bool won=false;
int blast=0;
char number;
char *c=&number;
void board(){


    rectangle(100,100,100+bsize*30,100+bsize*30);

    int y=100,x=100;
    for(int i=1;i<=bsize;i++){
        line(100,y,100+bsize*30,y);
        y= y+30;

        line(x,100,x,100+bsize*30);
        x=x+30;
    }
}


//starting work on database

int ele[bsize+2][bsize+2]={0};
int shown[bsize+2][bsize+2]={0};
int planted[bsize+2][bsize+2]={0};

void wall(){

    for(int i=0;i<bsize+2;i++){
    ele[0][i]=-5;
    ele[bsize+1][i]=-5;
    ele[i][0]=-5;
    ele[i][bsize+1]=-5;
    }
}

void bombcount(int a,int b){
    ele[a+1][b+1]=-1; // bomb
    for(int i=0;i<3;i++){

        if( ele[a-1+1][b-1+i+1]!=-5){
            ele[a-1+1][b-1+i+1]++;
        }
        if( ele[a+1+1][b-1+i+1]!=-5){
            ele[a+1+1][b-1+i+1]++;
        }

    }

        if( ele[a+1][b-1+1]!=-5){
            ele[a+1][b-1+1]++;
        }
        if(  ele[a+1][b+1+1]!=-5){
            ele[a+1][b+1+1]++;
        }
}

void plantbomb(){
int x,y;
srand(time(0));
for(int i=0;i<no_of_bombs;i++){
x=rand()%bsize;
y=rand()%bsize;
if(planted[x+1][y+1]==1){
no_of_bombs;
}
else{
bombcount(x,y);
planted[x+1][y+1]=1;
}

}

}

//preview tool for creator
void revealdata(){

    for(int i=0;i<bsize+2;i++){

        for(int j=0;j<bsize+2;j++){

        cout<<ele[i][j]<<" ";

        }

       cout<<endl;
    }
    cout<<*c;
}

void adopener(int a,int b){


    for(int i=0;i<3;i++){

        if( ele[a-1+1][b-1+i+1]!=-5 && ele[a-1+1][b-1+i+1]!=-1 && shown[a-1+1][b-1+i+1]!=1){
            number=ele[a-1+1][b-1+i+1]+ 48;
            outtextxy(100+30*(b-1+i)+12,100+30*(a-1)+9,c);
            openedblocks++;
        }

        if( ele[a+1+1][b-1+i+1]!=-5 && ele[a+1+1][b-1+i+1]!=-1 && shown[a+1+1][b-1+i+1]!=1){
            number=ele[a+1+1][b-1+i+1]+48;
            outtextxy(100+30*(b-1+i)+12,100+30*(a+1)+9,c);
            openedblocks++;
        }

    }

         if( ele[a+1][b-1+1]!=-5 && ele[a+1][b-1+1]!=-1 && shown[a+1][b-1+1]!=1){
            number=ele[a+1][b-1+1]+ 48;
            outtextxy(100+30*(b-1)+12,100+30*(a)+9,c);
            openedblocks++;
        }
        if( ele[a+1][b+1+1]!=-5 && ele[a+1][b+1+1]!=-1 && shown[a+1][b+1+1]!=1){
            number=ele[a+1][b+1+1]+ 48;
            outtextxy(100+30*(b+1)+12,100+30*(a)+9,c);
            openedblocks++;
        }
        shown[a][b]=1;

        for(int i=0;i<3;i++){

        if( ele[a-1+1][b-1+i+1]!=-5 && ele[a-1+1][b-1+i+1]!=-1 ){
            if( ele[a-1+1][b-1+i+1]==0 && shown[a-1][b-1+i]==0)
            {adopener(a-1,b-1+i);
            shown[a-1][b-1+i]=1;}
        }

        if( ele[a+1+1][b-1+i+1]!=-5 && ele[a+1+1][b-1+i+1]!=-1){
            if( ele[a+1+1][b-1+i+1]==0 && shown[a+1][b-1+i]==0)
            {adopener(a+1,b-1+i);
            shown[a+1][b-1+i]=1;}
        }

        }
        if( ele[a+1][b-1+1]!=-5 && ele[a+1][b-1+1]!=-1){
            if( ele[a+1][b-1+1]==0 && shown[a][b-1]==0)
            {adopener(a,b-1);
            shown[a][b-1]=1;}
        }
        if( ele[a+1][b+1+1]!=-5 && ele[a+1][b+1+1]!=-1){
            if( ele[a+1][b+1+1]==0 && shown[a][b+1]==0)
            {adopener(a,b+1);
            shown[a][b+1]=1;}
        }

}

//reveals to user when he clicks a tile
void reveal(){
while (!ismouseclick(WM_LBUTTONDOWN))
    {
    continue;
    }
    getmouseclick(WM_LBUTTONDOWN, x, y);
    int m=(y-100)/30;
    int n=(x-100)/30;

    if(ele[m+1][n+1]=='-1'){
    blast=1;
    outtextxy(100+30*(n)+12,100+30*(m)+9,"-1");
    openedblocks++;
    }
    else {
    number=ele[m+1][n+1]+ 48;
    outtextxy(100+30*(n)+12,100+30*(m)+9,c);
    openedblocks++;
    if(number=='0')
    adopener(m,n);
    }


}






int main(){
int gd=DETECT,gm;
    initgraph(&gd,&gm,"C:\Program Files (x86)\Simple CodeBlocks\MinGW\include");

    wall();
    plantbomb();
    revealdata();

    board();
    while(blast==0 && won==false){
    reveal();
    cout<<openedblocks<<" ";
    if(openedblocks==bsize*bsize-no_of_bombs){
    won=true;
    }
    }
    if(blast==1){
    cout<<"oh no you lost";
    }
    else{
    cout<<"oh wow you won";
    }
    getch();
    closegraph();

    return 0;
}
