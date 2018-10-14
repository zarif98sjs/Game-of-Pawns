/*
	picture demo
	author: Prof. Ashikur rahman
	last modified: April 29, 2017

	used as template for this project

*/

#define _CRT_SECURE_NO_WARNINGS
#include "iGraphics.h"
#include "initializations.h"
#include "blitz.h"
#include "artificial_hypocrisy.h"
#include<windows.h>

/*
	function iDraw() is called again and again by the system.
*/

/*

MODE::

11.MENU //DEFAULT
111. MENU2
21. NEW GAME
31. RESUME
41. INSTRUCTIONS
51.BLITZ

*/

/*
    kothaThekeElo 1 -->>  from newgame
    kothaThekeElo 2-->>  from resume
*/


int MODE=11;
int newMODE=11;

int iDrawNumber,iMove;

void iDraw()
{
    //place your drawing codes here
    iClear();
    iSetColor(0,200,200);

    //to show the opening "Game of Pawns" scene

    if(SecondsTraversed<2)
    {
        iShowBMP(0,0,"opening.bmp");
        return;
    }

    // for showing the menu bars

    if(newMODE==11)
    {
        iShowBMP(0,0,"menu.bmp");
        return;
    }

    if(newMODE==111)
    {
        iShowBMP(0,0,"menu2.bmp");
        return;
    }

    // chess board

    if(newMODE==21)
    {

        iShowBMP(0,0,"General_back.bmp");

        //dimensions for chess board

        iRectangle(340,20,740,740);

        iRectangle(350,30,720,720);

        //each square

        for(int i=350; i<1000; i+=90)
        {
            int chessboxwhiteorblack=i%4;
            for(int j=30; j<700; j+=90)
            {
                int checkboxwhiteorblack=j%4+chessboxwhiteorblack;

                //fixing the two colours

                if(checkboxwhiteorblack%4 == 2)
                {
                    iSetColor(182, 155, 76);
                    iFilledRectangle(i,j,90,90);
                }
                else
                {
                    iSetColor(120,72,1);
                    iFilledRectangle(i,j,90,90);
                }
            }
        }

        //showing possible moves

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
                if(!(des_x == des_x_final && des_y == des_y_final)){
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
                }
                if(qq)
                {
                    player_mode=2;
                    ++givenMovesOfWhite;
                }
                if(qq && moveforhypocrisy)
                {
                    //generating the automated mood

                    FILE *fff = fopen("debugging.txt","w+");

                    //the respective function is called

                    artificialHypocrisy();

                    //Showing checkmate

                    if(letsmove.empty() && blackKingInCheck())
                    {
                        iShowBMP(0,0,"white_wins.bmp");
                        return;
                    }

                    //printing probable moves

                    for(auto zxc:letsmove)
                    {
                        fprintf(fff,"%4d%4d%4d%4d%4d%4d\n",zxc.from_x,zxc.from_y,zxc.to_x,zxc.to_y,zxc.self,zxc.dev);
                    }
                    fprintf(fff,"\n%d\n\n",player_mode);
                    fclose(fff);

                    if(letsmove[0].dev == 0 && letsmove[0].is_check == 0)
                    {
                        swap(letsmove[0],letsmove[rand() % letsmove.size()]);
                    }

                    des_x = letsmove[0].from_x;
                    des_y = letsmove[0].from_y;
                    des_x_final = letsmove[0].to_x;
                    des_y_final = letsmove[0].to_y;
                    iDelay(1);
                    qq=0;
                    switch(occupy[des_x][des_y])
                    {
                    case 20:
                        if(letsmove[0].dev)
                            blackKingOccupy[des_x_final][des_y_final]=8;
                        else
                            blackKingOccupy[des_x_final][des_y_final]=6;
                        qq=blackKingMoveHappen();
                        break;
                    case 22:
                        if(letsmove[0].dev)
                            blackRookOccupy[des_x_final][des_y_final]=8;
                        else
                            blackRookOccupy[des_x_final][des_y_final]=6;
                        qq=blackRookMoveHappen();
                        break;
                    case 23:
                        if(letsmove[0].dev)
                            blackBishopOccupy[des_x_final][des_y_final]=8;
                        else
                            blackBishopOccupy[des_x_final][des_y_final]=6;
                        qq=blackBishopMoveHappen();
                        break;
                    case 21:
                        if(letsmove[0].dev)
                            blackMinisterOccupy[des_x_final][des_y_final]=8;
                        else
                            blackMinisterOccupy[des_x_final][des_y_final]=6;
                        qq=blackMinisterMoveHappen();
                        break;
                    case 24:
                        if(letsmove[0].dev)
                            blackKnightOccupy[des_x_final][des_y_final]=8;
                        else
                            blackKnightOccupy[des_x_final][des_y_final]=6;
                        qq=blackKnightMoveHappen();
                        break;
                    case 25:
                        if(letsmove[0].dev)
                            blackPawnOccupy[des_x_final][des_y_final]=8;
                        else
                            blackPawnOccupy[des_x_final][des_y_final]=6;
                        qq=blackPawnMoveHappen();
                        break;
                    }
                    if(qq)
                    {
                        player_mode=1;
                        ++givenMovesOfBlack;
                    }
                    for(int ii=7; ii>-1; --ii)
                {
                    for(int ij=0; ij<8; ++ij)
                    {
                        printf("%d\t",occupy[ij][ii]);
                    }
                    printf("\n\n");
                }
                }
            }
            else if(player_mode==2)
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
                }
            }
            iWhiteMoves = whiteMoveCounter();
            iBlackMoves = blackMoveCounter();
            MODE=0;
            printf("Chessboard\n\n");
            for(int ii=7; ii>-1; --ii)
            {
                for(int ij=0; ij<8; ++ij)
                {
                    printf("%d\t",occupy[ij][ii]);
                }
                printf("\n\n");
            }
        }
        for(int ii=7; ii>-1; --ii)
        {
            for(int ij=0; ij<8; ++ij)
            {
                tempShowbyString(ii,ij);
            }
        }

        iSetColor(255,0,0);

        //Showing player's turns

        if(player_mode==1)
        {
            //iText(1120,395,"TURN FOR WHITE",GLUT_BITMAP_TIMES_ROMAN_24);
            iShowBMP(1125,380,"turnwhite.bmp");
        }
        else if(player_mode==2)
        {
            //iText(1120,395,"TURN FOR BLACK",GLUT_BITMAP_TIMES_ROMAN_24);
            iShowBMP(1125,380,"turnblack.bmp");
        }

        //Declaring checkmate

        iSetColor(255,235,255);
        if(whiteKingInCheck())
        {
            //iText(100,500,"White King in Check",GLUT_BITMAP_TIMES_ROMAN_24);
            iShowBMP(1155,180,"whitecheck.bmp");
            printf("\n\a\a\a\a\n");
        }
        if(blackKingInCheck())
        {
            //iText(100,700,"Black King in Check",GLUT_BITMAP_TIMES_ROMAN_24);
            iShowBMP(1155,500,"blackcheck.bmp");
            printf("\n\a\a\a\a\n");
        }

        if(iWhiteMoves==0 && givenMovesOfBlack && whiteKingInCheck())
        {
            iText(100,400,"BLACK WINS");
            int time=11e2;
            while(time--)
                printf(" ");
            iShowBMP(0,0,"black_wins.bmp");
        }
        else if(iBlackMoves==0 && givenMovesOfWhite && blackKingInCheck())
        {
            iText(100,300,"WHITE WINS");
            int time=5e2;
            while(time--)
                printf("  "),    iText(100,350,"Checkmate !!! WHITE WINS");
            iShowBMP(0,0,"white_wins.bmp");
        }
        else if(((iWhiteMoves==0 && !whiteKingInCheck()) || (iBlackMoves==0 && !blackKingInCheck())) && givenMovesOfBlack && givenMovesOfWhite)
        {
            iText(100,350,"STALEMATE DRAW");
        }

    }

    //Same code repeated
    //So comments omitted
    //It reflects our immature coding
    //It should have been more structured

    if(newMODE==51)
    {
        moveforhypocrisy = 0;

        iShowBMP(0,0,"General_back.bmp");

        iRectangle(340,20,740,740);

        iRectangle(350,30,720,720);

        for(int i=350; i<1000; i+=90)
        {
            int chessboxwhiteorblack=i%4;
            for(int j=30; j<700; j+=90)
            {
                int checkboxwhiteorblack=j%4+chessboxwhiteorblack;
                if(checkboxwhiteorblack%4 == 2)
                {
                    iSetColor(182, 155, 76);
                    iFilledRectangle(i,j,90,90);
                }
                else
                {
                    iSetColor(120,72,1);
                    iFilledRectangle(i,j,90,90);
                }
            }
        }

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
                if(moveforhypocrisy)
                {
                    FILE *fff = fopen("debugging.txt","w+");
                    artificialHypocrisy();
                    if(letsmove.empty() && blackKingInCheck())
                    {
                        iShowBMP(0,0,"white_wins.bmp");
                        return;
                    }
                    for(auto zxc:letsmove)
                    {
                        fprintf(fff,"%4d%4d%4d%4d%4d%4d\n",zxc.from_x,zxc.from_y,zxc.to_x,zxc.to_y,zxc.self,zxc.dev);
                    }
                    fprintf(fff,"\n%d\n\n",player_mode);
                    fclose(fff);

                    if(letsmove[0].dev == 0 && letsmove[0].is_check == 0)
                    {
                        swap(letsmove[0],letsmove[rand() % letsmove.size()]);
                    }

                    des_x = letsmove[0].from_x;
                    des_y = letsmove[0].from_y;
                    des_x_final = letsmove[0].to_x;
                    des_y_final = letsmove[0].to_y;
                    iDelay(2);
                    qq=0;

                    switch(occupy[des_x][des_y])
                    {
                    case 20:
                        if(letsmove[0].dev)
                            blackKingOccupy[des_x_final][des_y_final]=8;
                        else
                            blackKingOccupy[des_x_final][des_y_final]=6;
                        qq=blackKingMoveHappen();
                        break;
                    case 22:
                        if(letsmove[0].dev)
                            blackRookOccupy[des_x_final][des_y_final]=8;
                        else
                            blackRookOccupy[des_x_final][des_y_final]=6;
                        qq=blackRookMoveHappen();
                        break;
                    case 23:
                        if(letsmove[0].dev)
                            blackBishopOccupy[des_x_final][des_y_final]=8;
                        else
                            blackBishopOccupy[des_x_final][des_y_final]=6;
                        qq=blackBishopMoveHappen();
                        break;
                    case 21:
                        if(letsmove[0].dev)
                            blackMinisterOccupy[des_x_final][des_y_final]=8;
                        else
                            blackMinisterOccupy[des_x_final][des_y_final]=6;
                        qq=blackMinisterMoveHappen();
                        break;
                    case 24:
                        if(letsmove[0].dev)
                            blackKnightOccupy[des_x_final][des_y_final]=8;
                        else
                            blackKnightOccupy[des_x_final][des_y_final]=6;
                        qq=blackKnightMoveHappen();
                        break;
                    case 25:
                        if(letsmove[0].dev)
                            blackPawnOccupy[des_x_final][des_y_final]=8;
                        else
                            blackPawnOccupy[des_x_final][des_y_final]=6;
                        qq=blackPawnMoveHappen();
                        break;
                    }
                    if(qq)
                    {
                        player_mode=1;
                        ++givenMovesOfBlack;
                    }
                }
            }
            else if(player_mode==2)
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
            MODE=0;
            printf("Chessboard\n\n");
            for(int ii=7; ii>-1; --ii)
            {
                for(int ij=0; ij<8; ++ij)
                {
                    printf("%d\t",occupy[ij][ii]);
                }
                printf("\n\n");
            }
        }
        printf("Chessboard\n\n");
        for(int ii=7; ii>-1; --ii)
        {
            for(int ij=0; ij<8; ++ij)
            {
                tempShowbyString(ii,ij);
            }
            //printf("\n\n");
        }

        iSetColor(255,0,0);

        if(player_mode==1)
        {
            //iText(1120,395,"TURN FOR WHITE",GLUT_BITMAP_TIMES_ROMAN_24);
            iShowBMP(1125,380,"turnwhite.bmp");
        }
        else if(player_mode==2)
        {
            //iText(1120,395,"TURN FOR BLACK",GLUT_BITMAP_TIMES_ROMAN_24);
            iShowBMP(1125,380,"turnblack.bmp");
        }

        iSetColor(255,235,255);
        if(whiteKingInCheck())
        {
            //iText(100,500,"White King in Check",GLUT_BITMAP_TIMES_ROMAN_24);
            iShowBMP(1155,180,"whitecheck.bmp");
            printf("\n\a\a\a\a\n");
        }
        if(blackKingInCheck())
        {
            //iText(100,700,"Black King in Check",GLUT_BITMAP_TIMES_ROMAN_24);
            iShowBMP(1155,500,"blackcheck.bmp");
            printf("\n\a\a\a\a\n");
        }


        // TIME FOR PLAYER 1
        iSetColor(0,0,0);
        iFilledRectangle(20,30,150,150);
        iSetColor(255,255,255);
        iFilledRectangle(150,30,150,150);

        char temp1[10];
        sprintf(temp1, "%d", minute_player1);

        iSetColor(255,255,255);
        dekhano(temp1,x1,y1);


        char temp2[10];
        sprintf(temp2, "%d", sec_player1);

        iSetColor(0,0,0);
        //iText(50,100,temp1, GLUT_BITMAP_TIMES_ROMAN_24);
        //iText(150,100,temp2, GLUT_BITMAP_TIMES_ROMAN_24);
        dekhano2(temp2,x2,y1);

        iSetColor(255,255,255);
        iFilledRectangle(140,115,10,10);
        iFilledRectangle(140,80,10,10);

        iSetColor(0,0,0);
        iFilledRectangle(150,115,10,10);
        iFilledRectangle(150,80,10,10);

        // TIME FOR PLAYER 2
        iSetColor(0,0,0);
        iFilledRectangle(20,550,150,150);
        iSetColor(255,255,255);
        iFilledRectangle(150,550,150,150);

        // printf("%d\t%d\n",minute,sec);
        char temp3[10];
        sprintf(temp3, "%d", minute_player2);

        char temp4[10];
        sprintf(temp4, "%d", sec_player2);
        //iText(50,100,temp1, GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(255,255,255);
        dekhano(temp3,x1,y2);

        //iText(150,100,temp2, GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(0,0,0);
        dekhano2(temp4,x2,y2);

        iSetColor(255,255,255);
        iFilledRectangle(140,600,10,10);
        iFilledRectangle(140,635,10,10);

        iSetColor(0,0,0);
        iFilledRectangle(150,600,10,10);
        iFilledRectangle(150,635,10,10);

        if((iWhiteMoves==0 && givenMovesOfBlack && whiteKingInCheck()) || (t_sec_player1 <= 0))
        {
            iText(100,400,"BLACK WINS");
            int time=11e2;
            while(time--)
                printf("a");
            iShowBMP(0,0,"black_wins.bmp");
            return;
        }
        else if((iBlackMoves==0 && givenMovesOfWhite && blackKingInCheck()) || (t_sec_player2 <= 0))
        {
            iText(100,300,"WHITE WINS");
            iShowBMP(0,0,"white_wins.bmp");
            return;
        }
        else if(((iWhiteMoves==0 && !whiteKingInCheck()) || (iBlackMoves==0 && !blackKingInCheck())) && givenMovesOfBlack && givenMovesOfWhite)
        {
            iText(100,350,"STALEMATE DRAW");
        }
    }

    if(newMODE==31)
    {
        iShowBMP(0,0,"menu2.bmp");
        return;
    }


    iSetColor(255,0,0);
    iShowBMP(10,740,"menubar.bmp");

    if(newMODE==41)
    {
        //INSTRUCTIONS
        iShowBMP(0,0,"instruct.bmp");
    }

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
        if(newMODE==11)
        {
            if(mx >= 585 && mx <= 905 && my >= 470 && my <= 545)
                newMODE=111;
            else if(mx >= 605 && mx <= 885 && my >= 345 && my <= 420)
                newMODE=31,kothaThekeElo=2;
            else if(mx >= 550 && mx <= 970 && my >= 230 && my <= 310)
                newMODE=41;

		return;
        }

        if(newMODE==111)
        {
            if(mx >= 665 && mx <= 895 && my >= 485 && my <= 575 && kothaThekeElo==1)
            {
                moveforhypocrisy = 1;
                player_mode = 1;
                newMODE=21;
                init();
            }
            else if(mx >= 665 && mx <= 885 && my >= 345 && my <= 435 && kothaThekeElo==1)
            {
                newMODE=21;
                player_mode=1;
                init();
            }
            else if(mx >= 610 && mx <= 940 && my >= 200 && my <= 290 && kothaThekeElo==1)
            {
                newMODE=51;
                player_mode=1;
                init();
                t_sec_player1=300,minute_player1=5,sec_player1=0;
                t_sec_player2=300,minute_player2=5,sec_player2=0;
            }
        }


        if(newMODE==31)
        {

            if(mx >= 665 && mx <= 895 && my >= 485 && my <= 575 && kothaThekeElo==2)
            {
                init_hypo();
                moveforhypocrisy=1;
                newMODE=21;
            }
            else if(mx >= 665 && mx <= 885 && my >= 345 && my <= 435 && kothaThekeElo==2)
            {
                init_saved();
                moveforhypocrisy=0;
                newMODE=21;
            }
            else if(mx >= 610 && mx <= 940 && my >= 200 && my <= 290 && kothaThekeElo==2)
            {
                init_saved_blitz();
                 moveforhypocrisy=0;
                newMODE=51;
            }
        }

        des_x = (mx - 350)/90;
        des_y = (my -   30)/90;
        MODE=2;
    }
    if (button == GLUT_RIGHT_BUTTON  && MODE==2)
    {
        //place your codes here
        MODE=25;
        des_x_final = (mx - 350)/90;
        des_y_final = (my - 30)/90;

    }

    //Refer to iKeyboard function to know the purpose of the function calls

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx<113 && my>740)
    {
		if(newMODE == 51){
			iKeyboard('b');
		}
		else if(moveforhypocrisy){
			iKeyboard('h');
		}
		else{
			iKeyboard('p');
		}
		iKeyboard('q');
    }

     if(newMODE==41 && mx >= 1150 && mx <= 1250 && my >= 670 && my <= 780 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		newMODE = 11;
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
        FILE *fp1;
        fp1 = fopen("saved_game.txt","w+");
        for(int ii=7; ii>-1; --ii)
        {
            for(int ij=0; ij<8; ++ij)
                fprintf(fp1,"%d\t",occupy[ij][ii]);
            fprintf(fp1,"\n");
        }
        fprintf(fp1,"%d %d\n",player_mode,moveforhypocrisy);
        fclose(fp1);
        iDraw();
        exit(0);
    }
    else if (key == 's')
    {
        FILE *fp1 = fopen("saved_game.txt","w+");
        for(int ii=7; ii>-1; --ii)
        {
            for(int ij=0; ij<8; ++ij)
                fprintf(fp1,"%d\t",occupy[ij][ii]);
            fprintf(fp1,"\n");
        }
        fprintf(fp1,"%d %d\n",player_mode,moveforhypocrisy);
        fclose(fp1);
        iDraw();
    }
    else if (key == 'p')
    {
        FILE *fp1 = fopen("saved_game.txt","w+");
        for(int ii=7; ii>-1; --ii)
        {
            for(int ij=0; ij<8; ++ij)
                fprintf(fp1,"%d\t",occupy[ij][ii]);
            fprintf(fp1,"\n");
        }
        fprintf(fp1,"%d %d\n",player_mode,moveforhypocrisy);
        fclose(fp1);
        newMODE=11;
        iDraw();
    }
    else if(key == 'n')
    {
        init_saved();
    }
    else if(key=='q')
    {
        newMODE=11;
        kothaThekeElo=1;
        moveforhypocrisy = 0;
    }
    else if(key=='b')
    {
        FILE *fp1 = fopen("saved_blitz.txt","w+");
        iPauseTimer(1);
        iPauseTimer(2);
        for(int ii=7; ii>-1; --ii)
        {
            for(int ij=0; ij<8; ++ij)
                fprintf(fp1,"%d\t",occupy[ij][ii]);
            fprintf(fp1,"\n");
        }
        fprintf(fp1,"%d %d\n",player_mode,moveforhypocrisy);
        fprintf(fp1,"%d %d",t_sec_player1,t_sec_player2);
        fclose(fp1);
        iDraw();
    }
    else if(key=='h')
    {
        FILE *fp1 = fopen("saved_hypo.txt","w+");
        for(int ii=7; ii>-1; --ii)
        {
            for(int ij=0; ij<8; ++ij)
                fprintf(fp1,"%d\t",occupy[ij][ii]);
            fprintf(fp1,"\n");
        }
        fprintf(fp1,"%d %d\n",player_mode,moveforhypocrisy);
        fclose(fp1);
        iDraw();
    }
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

    //The Light of the Seven - Ramin Djawndi
    //Game of Thrones - Season Six Finale
    PlaySound(TEXT("chess.wav"),NULL,SND_LOOP|SND_ASYNC);

    //Initializing the Traversed Second Count
    SecondsTraversed=0;

    //Fixing the counters and pausing the blitz counters
    iSetTimer(1000,second_counter);
    iSetTimer(1000,komche_player1);
    iSetTimer(1000,komche_player2);
    iPauseTimer(1);
    iPauseTimer(2);

    //So far the best way to generate randomness
    srand(time(NULL));

    //The function for initializing the board
    init();

    //White Plays First
    player_mode=1;

    //Initializing the screen
    iInitialize(1400, 790, "Game of Pawns");

    //The main function should return zero, as always
    return 0;

    //Ending in the name of Allah
}
