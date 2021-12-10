#include<graphics.h>
#include<iostream>
#include<stdio.h>
#include <stdlib.h>
#include<time.h>

//devloper options
#define bsize 10
#define no_of_bombs 12

using namespace std;
int x,y;
bool won=false;
int blast=0;
char number;
char *c=&number;




void board(){
    //setcolor(0);
    //settextstyle(10,0,4);
    //outtextxy(100 + (bsize)*30-160,40,"MINESWEEPER");
    setcolor(15);
    rectangle(100,100,100+bsize*30,100+bsize*30);
    setfillstyle(1,COLOR(162,209,73));
    floodfill(105,105,15);



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
int printed[bsize+2][bsize+2]={0};
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
    ele[a+1][b+1]=-1;
    cout<<a+1<<b+1<<" "; // bomb
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
x=rand()%(bsize-1)+1;
y=rand()%(bsize-1)+1;
if(planted[x+1][y+1]==1){
i--;
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
    cout<<endl;

    //cout<<*c;
}

void adopener(int a,int b){
    for(int i=0;i<3;i++){

        if( ele[a-1+1][b-1+i+1]!=-5 && ele[a-1+1][b-1+i+1]!=-1 && shown[a-1][b-1+i]!=1 && (a-1+1>=0 && b-1+i+1>=0 && a-1+1<=bsize && b-1+i+1<=bsize) ){
            number=ele[a-1+1][b-1+i+1]+ 48;
            floodfill(100+30*(b-1+i)+15,100+30*(a-1)+9,15);
            outtextxy(100+30*(b-1+i)+12,100+30*(a-1)+9,c);
            printed[a-1][b-1+i]=1;
        }

        if( ele[a+1+1][b-1+i+1]!=-5 && ele[a+1+1][b-1+i+1]!=-1 && shown[a+1][b-1+i]!=1 && (a+1+1>=0 && b-1+i+1>=0 && a+1+1<=bsize && b-1+i+1<=bsize) ){
            number=ele[a+1+1][b-1+i+1]+48;
            floodfill(100+30*(b-1+i)+15,100+30*(a+1)+9,15);
            outtextxy(100+30*(b-1+i)+12,100+30*(a+1)+9,c);
            printed[a+1][b-1+i]=1;
        }

    }

         if( ele[a+1][b-1+1]!=-5 && ele[a+1][b-1+1]!=-1 && shown[a][b-1]!=1 && (a+1>=0 && b-1+1>=0 && a+1<=bsize && b-1+1<=bsize) ){
            number=ele[a+1][b-1+1]+ 48;
            floodfill(100+30*(b-1)+15,100+30*(a)+9,15);
            outtextxy(100+30*(b-1)+12,100+30*(a)+9,c);
            printed[a][b-1]=1;
        }
        if( ele[a+1][b+1+1]!=-5 && ele[a+1][b+1+1]!=-1 && shown[a][b+1]!=1 && (a+1>=0 && b+1+1>=0 && a+1<=bsize && b+1+1<=bsize) ){
            number=ele[a+1][b+1+1]+ 48;
            floodfill(100+30*(b+1)+15,100+30*(a)+9,15);
            outtextxy(100+30*(b+1)+12,100+30*(a)+9,c);
            printed[a][b+1]=1;
        }
        shown[a][b]=1;

        for(int i=0;i<3;i++){

        if( ele[a-1+1][b-1+i+1]==0 && shown[a-1][b-1+i]==0)
        adopener(a-1,b-1+i);
        if( printed[a-1][b-1+i]==1 )
        shown[a-1][b-1+i]=1;

        if( ele[a+1+1][b-1+i+1]==0 && shown[a+1][b-1+i]==0)
        adopener(a+1,b-1+i);
        if( printed[a+1][b-1+i]==1)
        shown[a+1][b-1+i]=1;

        }

        if( ele[a+1][b-1+1]==0 && shown[a][b-1]==0)
        adopener(a,b-1);
        if( printed[a][b-1]==1)
        shown[a][b-1]=1;

        if( ele[a+1][b+1+1]==0 && shown[a][b+1]==0)
        adopener(a,b+1);
        if( printed[a][b+1]=1)
        shown[a][b+1]=1;

}

//reveals to user when he clicks a tile
void reveal(){
while (!ismouseclick(WM_LBUTTONDOWN))
    {
    continue;
    }
    getmouseclick(WM_LBUTTONDOWN, x, y);
    if(x>=100 +bsize*30 || y>=100 +bsize*30 || x<100 || y<100){
    return;
    }
    int m=(y-100)/30;
    int n=(x-100)/30;
    //cout<<m<<n<<" ";

    if(ele[m+1][n+1]==-1){
    blast=1;
    setfillstyle(1,COLOR(229,194,159));
    floodfill(100+30*(n)+15,100+30*(m)+9,15);
    //outtextxy(100+30*(n)+12,100+30*(m)+9,"-1");
    setcolor(0);
    circle(100+30*(n)+15,100+30*(m)+15,8);
    setfillstyle(1,0);
    floodfill(100+30*(n)+15,100+30*(m)+15,0);
    printed[m][n]=1;
    }
    else{
    number=ele[m+1][n+1]+ 48;
    setfillstyle(1,COLOR(229,194,159));
    floodfill(100+30*(n)+15,100+30*(m)+9,15);
    outtextxy(100+30*(n)+12,100+30*(m)+9,c);
    shown[m][n]=1;
    if(number=='0')
    adopener(m,n);
    }

}
/*void displayboard(){
     for(int i=0;i<bsize;i++){

        for(int j=0;j<bsize;j++){

        if(printed[i][j]==1){
            if(ele[i+1][j+1]==-1){
            outtextxy(100+30*(j)+12,100+30*(i)+9,"-1");
            }
            else{
            number=ele[i+1][j+1]+ 48;
            outtextxy(100+30*(j)+12,100+30*(i)+9,c);
            }
        }

        }

}
}*/

void checkwin(){
    int opened=0;
    for(int i=0;i<bsize;i++){

        for(int j=0;j<bsize;j++){
        if(shown[i][j]==1)
        opened++;
        }
    }
    if(opened>=bsize*bsize-no_of_bombs){
        won=1;
    }

}




int main(){
int gd=DETECT,gm;
    initgraph(&gd,&gm,"C:\Program Files (x86)\Simple CodeBlocks\MinGW\include");
    setfillstyle(1,COLOR(229,194,159));
    setbkcolor(COLOR(229,194,159));//rgb(229,194,159)

    board();
    setcolor(0);
    wall();
    plantbomb();
    revealdata();


    while(blast==0 && won==false){
    reveal();
    checkwin();
    }
    setbkcolor(0);//changing main bk before clearing bcz bk is not cleared
    settextstyle(8,0,5);
    setcolor(15);

    if(blast==1){

    delay(2000);
    cleardevice();
    setbkcolor(3);
    outtextxy(200,200,"YOU LOST!");
    }
    else{
    delay(2000);
    cleardevice();
    setbkcolor(3);
    outtextxy(200,200,"YOU WON!");
    }

    getch();
    closegraph();

    return 0;
}

