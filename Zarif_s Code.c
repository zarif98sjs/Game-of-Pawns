/*
	author: Prof. Ashikur rahman
	last modified: April 29, 2017
*/

#define _CRT_SECURE_NO_WARNINGS
#include "iGraphics.h"
#include "initializations.h"
#include<windows.h>
//#include "texture.h"
//#include "TextureList.h"

//#include "rook_001.h"


/*
	function iDraw() is called again and again by the system.
	*/


/*

MODE::

11. MENU // DEFAULT
21. NEW GAME
31. RESUME
41. INSTRUCTIONS



*/

//CLOCK STARTS

int t_sec_player1=300,minute_player1=5,sec_player1=0;
int t_sec_player2=300,minute_player2=5,sec_player2=0;

int len;
int siz;

double r=120,g=50,b=150;

int ara0[]= {0,1,1,1,1,1,1,0};
int ara1[]= {0,0,1,1,0,0,0,0};
int ara2[]= {0,1,1,0,1,1,0,1};
int ara3[]= {0,1,1,1,1,0,0,1};
int ara4[]= {0,0,1,1,0,0,1,1};
int ara5[]= {0,1,0,1,1,0,1,1};
int ara6[]= {0,1,0,1,1,1,1,1};
int ara7[]= {0,1,1,1,0,0,0,0};
int ara8[]= {0,1,1,1,1,1,1,1};
int ara9[]= {0,1,1,1,1,0,1,1};

int x1=60,y1=65,z=60;
int x2=170,y2=550;

void buildSegment(int ara[],int f,int x,int y)//factor
{
    for(int i=1; i<=7; i++)
    {
        if(i==1 && ara[i]==1)
            iFilledRectangle(x+f,y+70,50,10);
        if(i==2 &&ara[i]==1)
            iFilledRectangle(x+40+f,y+35,10,45);
        if(i==3 &&ara[i]==1)
            iFilledRectangle(x+40+f,y,10,45);
        if(i==4 &&ara[i]==1)
            iFilledRectangle(x+f,y,50,10);
        if(i==5 &&ara[i]==1)
            iFilledRectangle(x+f,y,10,45);
        if(i==6 &&ara[i]==1)
            iFilledRectangle(x+f,y+35,10,45);
        if(i==7 &&ara[i]==1)
            iFilledRectangle(x+f,y+35,50,10);

    }

}

void dekhano(char *str2,int x,int y)
{
    siz=strlen(str2);
    printf("**%s\n",str2);

    for(int i=0; i<strlen(str2); i++)
    {
        if(str2[i]=='0')
            buildSegment(ara0,z*i,x,y);
        if(str2[i]=='1')
            buildSegment(ara1,z*i,x,y);
        if(str2[i]=='2')
            buildSegment(ara2,z*i,x,y);
        if(str2[i]=='3')
            buildSegment(ara3,z*i,x,y);
        if(str2[i]=='4')
            buildSegment(ara4,z*i,x,y);
        if(str2[i]=='5')
            buildSegment(ara5,z*i,x,y);
        if(str2[i]=='6')
            buildSegment(ara6,z*i,x,y);
        if(str2[i]=='7')
            buildSegment(ara7,z*i,x,y);
        if(str2[i]=='8')
            buildSegment(ara8,z*i,x,y);
        if(str2[i]=='9')
            buildSegment(ara9,z*i,x,y);
    }
}

//CLOCK ENDS


int MODE=11;
int newMODE=11;

int iDrawNumber,iMove;

void iDraw()
{
    //place your drawing codes here
    iClear();
    iSetColor(0,200,200);
    //printf("MODE is %d\n",MODE);
    if(SecondsTraversed<1)
    {
        iShowBMP(0,0,"1001.bmp");
        return;
    }

    if(newMODE==11)
    {
        iShowBMP(0,0,"menu_page.bmp");
        //iFilledRectangle(550,505,410,65);
        //iFilledRectangle(550,380,410,65);
        //iFilledRectangle(550,250,410,65);
        //iShowBMP(0,0,"1001.bmp");
        //return;
    }

    if(newMODE==21)
    {
        iShowBMP(0,0,"General_back.bmp");
        //iShowBMP(100,100,"erty.bmp");
        iRectangle(340,20,740,740);
        //iSetColor();
        iRectangle(350,30,720,720);

        /*   if(SecondsTraversed<=1)
               init();*/

        // iSetColor(255,0,0);
        //printf("\nSomething : %d \n",max(2,5));
        //printf("\niMove: %5d iDraw:	%5d mode: %5d des_x: %d des_x-final: %d %d %d\n",iMove,iDrawNumber++,MODE,des_x,des_x_final,des_y,des_y_final);

        for(int i=350; i<1000; i+=90)
        {
            int chessboxwhiteorblack=i%4;
            for(int j=30; j<700; j+=90)
            {
                int checkboxwhiteorblack=j%4+chessboxwhiteorblack;
                if(checkboxwhiteorblack%4 == 2)
                {
                    iSetColor(238,189,222);
                    iFilledRectangle(i,j,90,90);
                }
                else
                {
                    iSetColor(41,36,33);
                    iFilledRectangle(i,j,90,90);
                }
            }
        }
        //iShowBMP(500,400,"25.bmp");
        //drawTexture(500,300,var);

        //printf("Outta loop:	%d %d %d\n",des_x,des_y,occupy[0][7]);
        if(player_mode==1)
        {
            switch(occupy[des_x][des_y])
            {
            case 10:
                whiteKingMoveShow();
                break;
            case 12:
                whiteRookMoveShow();
                break;
            case 13:
                whiteBishopMoveShow();
                break;
            case 11:
                whiteMinisterMoveShow();
                break;
            case 14:
                whiteKnightMoveShow();
                break;
            case 15:
                whitePawnMoveShow();
                break;
            }
        }
        if(player_mode==2)
        {
            switch(occupy[des_x][des_y])
            {
            case 20:
                blackKingMoveShow();
                break;
            case 22:
                blackRookMoveShow();
                break;
            case 23:
                blackBishopMoveShow();
                break;
            case 21:
                blackMinisterMoveShow();
                break;
            case 24:
                blackKnightMoveShow();
                break;
            case 25:
                blackPawnMoveShow();
                break;
            }
        }
        if(MODE==25)
        {
            if(player_mode==1)
            {
                int qq=0;
                switch(occupy[des_x][des_y])
                {
                case 10:
                    qq=whiteKingMoveHappen();
                    break;
                case 12:
                    qq=whiteRookMoveHappen();
                    break;
                case 13:
                    qq=whiteBishopMoveHappen();
                    break;
                case 11:
                    qq=whiteMinisterMoveHappen();
                    break;
                case 14:
                    qq=whiteKnightMoveHappen();
                    break;
                case 15:
                    qq=whitePawnMoveHappen();
                    break;
                }
                if(qq)
                {
                    player_mode=2;
                    ++givenMovesOfWhite;
                    iPauseTimer(1);
                    iResumeTimer(2);
                }
            }
            if(player_mode==2)
            {
                int qq=0;
                switch(occupy[des_x][des_y])
                {
                case 20:
                    qq=blackKingMoveHappen();
                    break;
                case 22:
                    qq=blackRookMoveHappen();
                    break;
                case 23:
                    qq=blackBishopMoveHappen();
                    break;
                case 21:
                    qq=blackMinisterMoveHappen();
                    break;
                case 24:
                    qq=blackKnightMoveHappen();
                    break;
                case 25:
                    qq=blackPawnMoveHappen();
                    break;
                }
                if(qq)
                {
                    player_mode=1;
                    ++givenMovesOfBlack;
                    iResumeTimer(1);
                    iPauseTimer(2);
                }
            }
            iWhiteMoves = whiteMoveCounter();
            iBlackMoves = blackMoveCounter();
            printf("\n\nWAITING FOR A BLUNDER:   \nWHITE:\t%d\tBLACK:\t%d\n\n",iWhiteMoves,iBlackMoves);
            MODE=0;
            printf("Chessboard\n\n");
            for(int ii=7; ii>-1; --ii)
            {
                for(int ij=0; ij<8; ++ij)
                {
                    printf("%d\t",occupy[ij][ii]);
                    //tempShowbyString(ii,ij);
                }
                printf("\n\n");
            }
        }
        //printf("Chessboard\n\n");
        for(int ii=7; ii>-1; --ii)
        {
            for(int ij=0; ij<8; ++ij)
            {
                //printf("%d\t",occupy[ij][ii]);
                tempShowbyString(ii,ij);
            }
            //printf("\n\n");
        }

        iSetColor(255,0,0);

        if(player_mode==1)
        {
            iText(1120,395,"TURN FOR WHITE",GLUT_BITMAP_TIMES_ROMAN_24);
        }
        else if(player_mode==2)
        {
            iText(1120,395,"TURN FOR BLACK",GLUT_BITMAP_TIMES_ROMAN_24);
        }

        iSetColor(255,235,255);
        if(whiteKingInCheck())
        {
            iText(100,500,"White King in Check",GLUT_BITMAP_TIMES_ROMAN_24);
            printf("\n\a\a\a\a\n");
        }
        if(blackKingInCheck())
        {
            iText(100,700,"Black King in Check",GLUT_BITMAP_TIMES_ROMAN_24);
            printf("\n\a\a\a\a\n");
        }

        if(iWhiteMoves==0 && givenMovesOfBlack && whiteKingInCheck())
        {
            iText(100,400,"BLACK WINS");
            int time=11e2;
            while(time--)
                printf("a");
            iShowBMP(0,0,"black_wins.bmp");
        }
        else if(iBlackMoves==0 && givenMovesOfWhite && blackKingInCheck())
        {
            iText(100,300,"WHITE WINS");
            int time=5e2;
            while(time--)
                printf("a"),    iText(100,350,"Checkmate !!! WHITE WINS");
            iShowBMP(0,0,"white_wins.bmp");
        }
        else if(((iWhiteMoves==0 && !whiteKingInCheck()) || (iBlackMoves==0 && !blackKingInCheck())) && givenMovesOfBlack && givenMovesOfWhite)
        {
            iText(100,350,"STALEMATE DRAW");
        }

        // TIME FOR PLAYER 1
        //iSetColor(66, 203, 244);
        iSetColor(0,0,0);
        iFilledRectangle(20,30,150,150);

        char temp1[10];
        sprintf(temp1, "%d", minute_player1);

        iSetColor(255,255,255);
        dekhano(temp1,x1,y1);

        iSetColor(255,255,255);
        iFilledRectangle(150,30,150,150);

        // printf("%d\t%d\n",minute,sec);


        char temp2[10];
        sprintf(temp2, "%d", sec_player1);

        iSetColor(0,0,0);
        //iText(50,100,temp1, GLUT_BITMAP_TIMES_ROMAN_24);


        //iText(150,100,temp2, GLUT_BITMAP_TIMES_ROMAN_24);
        dekhano(temp2,x2,y1);

        iSetColor(255,255,255);
        iFilledRectangle(140,115,10,10);
        iFilledRectangle(140,80,10,10);

        iSetColor(0,0,0);
        iFilledRectangle(150,115,10,10);
        iFilledRectangle(150,80,10,10);




        // TIME FOR PLAYER 2
        iSetColor(66, 203, 244);
        iFilledRectangle(20,500,300,200);

        // printf("%d\t%d\n",minute,sec);
        char temp3[10];
        sprintf(temp3, "%d", minute_player2);

        char temp4[10];
        sprintf(temp4, "%d", sec_player2);

        iSetColor(120,25,150);
        //iText(50,100,temp1, GLUT_BITMAP_TIMES_ROMAN_24);
        dekhano(temp3,x1,y2);

        //iText(150,100,temp2, GLUT_BITMAP_TIMES_ROMAN_24);
        dekhano(temp4,x2,y2);


    }

    if(newMODE==31)
    {
        //RESUME
        init();
        init_saved();
        newMODE=21;
        printf("Chessboard\n\n");
        /*for(int ii=7; ii>-1; --ii)
        {
            for(int ij=0; ij<8; ++ij)
            {
                printf("%d\t",occupy[ij][ii]);
                //tempShowbyString(ii,ij);
            }
            printf("\n\n");
        }*/
    }

    if(newMODE==41)
    {
        //INSTRUCTIONS
        iShowBMP(0,0,"INSTRUCTIONS.bmp");
    }

    iSetColor(255,0,0);

}
/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my)
{
    //place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //int temp_MODE;

        if(newMODE==11)
        {
            if(mx >= 550 && mx <= 960 && my >= 505 && my <= 570)
            {
                newMODE=21;
                SecondsTraversed=0;
                //player_mode = rand();
                //printf("P Mode: %d\n",player_mode);
                //player_mode %= 2 + 1;
                player_mode=1;
                init();
                //temp_MODE=21;
                printf("NEW GAMEEEEEEEEE\n");
            }

            else if(mx >= 550 && mx <= 960 && my >= 380 && my <= 475)
                newMODE=31;
            else if(mx >= 550 && mx <= 960 && my >= 250 && my <= 315)
                newMODE=41;

        }
        des_x = (mx - 350)/90;
        des_y = (my -   30)/90;
        MODE=2;
    }
    if (button == GLUT_RIGHT_BUTTON /*&& state == GLUT_DOWN*/ && MODE==2)
    {
        //place your codes here
        MODE=25;
        des_x_final = (mx - 350)/90;
        des_y_final = (my - 30)/90;
        /*if(des_x != des_x_final || des_y!=des_y_final)
            player_mode = (player_mode%2)+1;*/
    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key)
{
    if (key == 'x')
    {
        //do something with 'x'
        FILE *fp1 = fopen("saved_game.txt","w+");
        for(int ii=7; ii>-1; --ii)
        {
            for(int ij=0; ij<8; ++ij)
                fprintf(fp1,"%d\t",occupy[ij][ii]);
            fprintf(fp1,"\n");
        }
        fprintf(fp1,"%d\n",player_mode);
        fclose(fp1);
        iDraw();
        exit(0);
    }
    else if (key == 's')
    {
        //do something with 'x'
        FILE *fp1 = fopen("saved_game.txt","w+");
        for(int ii=7; ii>-1; --ii)
        {
            for(int ij=0; ij<8; ++ij)
                fprintf(fp1,"%d\t",occupy[ij][ii]);
            fprintf(fp1,"\n");
        }
        fprintf(fp1,"%d\n",player_mode);
        fclose(fp1);
        iDraw();
        //exit(0);
    }
    else if (key == 'p')
    {
        //do something with 'x'
        FILE *fp1 = fopen("saved_game.txt","w+");
        for(int ii=7; ii>-1; --ii)
        {
            for(int ij=0; ij<8; ++ij)
                fprintf(fp1,"%d\t",occupy[ij][ii]);
            fprintf(fp1,"\n");
        }
        fprintf(fp1,"%d\n",player_mode);
        fclose(fp1);
        newMODE=11;
        iDraw();
        //exit(0);
    }
    else if(key == 'n')
    {
        init_saved();
        //iDraw();
    }
    else if(key=='q')
    {
        newMODE=11;
    }
    //place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/

void iSpecialKeyboard(unsigned char key)
{

    if (key == GLUT_KEY_END)
    {
        exit(0);
    }
    if (key == GLUT_KEY_LEFT)
    {
        pic_x--;
    }
    if (key == GLUT_KEY_RIGHT)
    {
        pic_x++;
    }
    if (key == GLUT_KEY_UP)
    {
        pic_y++;
    }
    if (key == GLUT_KEY_DOWN)
    {
        pic_y--;
    }
    //place your codes for other keys here
}

void second_counter(void)
{
    ++SecondsTraversed;

}

void komche_player1()
{
    t_sec_player1--;
    minute_player1=t_sec_player1/60;
    sec_player1=t_sec_player1%60;
}

void komche_player2()
{
    t_sec_player2--;
    minute_player2=t_sec_player2/60;
    sec_player2=t_sec_player2%60;
}

int main()
{
    //place your own initialization codes here.

    PlaySound(TEXT("chess.wav"),NULL,SND_LOOP|SND_ASYNC);

    SecondsTraversed=0;
    iSetTimer(1000,second_counter);
    iSetTimer(1000,komche_player1);
    iSetTimer(1000,komche_player2);
    iPauseTimer(1);
    iPauseTimer(2);

    player_mode=0;
    srand(time(NULL));
    init();
    player_mode=1;
    pic_x = 30;
    pic_y = 20;
    iInitialize(1400, 790, "Queen of Thorns");
    return 0;
}
