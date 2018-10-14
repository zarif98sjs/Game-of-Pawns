#include<vector>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#define max(a,b)	((a)>(b))?(a):(b)
#define min(a,b)	((a)<(b))?(a):(b)

using namespace std;

/*
	10		20		King
	11		21		Minister
	12		22		Rook
	13		23		Bishop
	14		24		Knight
	15		25		Pawn

	1 Player-1
	2 Player-2

*/

//Else the variables and functions are named so that the code is readable

int occupy[8][8];
int pic_x, pic_y;
int des_x, des_y;
int des_x_final, des_y_final;

int whiteKnightOccupy[8][8];
int blackKnightOccupy[8][8];

int whiteRookOccupy[8][8];
int blackRookOccupy[8][8];

int whiteBishopOccupy[8][8];
int blackBishopOccupy[8][8];

int whiteMinisterOccupy[8][8];
int blackMinisterOccupy[8][8];

int whitePawnOccupy[8][8];
int blackPawnOccupy[8][8];

int whiteKingOccupy[8][8];
int blackKingOccupy[8][8];

int white_dev_all[8][8];
int black_dev_all[8][8];

int player_mode;

int SecondsTraversed;

int no_white_moves, iWhiteMoves, givenMovesOfWhite;
int no_black_moves, iBlackMoves, givenMovesOfBlack;

int whiteKingInCheck(void);
int blackKingInCheck(void);

int updatedWhiteKinginCheck(int bef_x, int bef_y, int up_x, int up_y);
int updatedBlackKinginCheck(int bef_x, int bef_y, int up_x, int up_y);

int moveforhypocrisy = 0;
int kothaThekeElo=1;

int isWhite(int q)
{
	if(q/9 == 1)		return 1;
	else				return 0;
}

int isBlack(int q)
{
	if(q/9 == 2)		return 1;
	else				return 0;
}

struct hypmove
{
	int from_x, from_y, to_x, to_y,self,dev,is_check;
};

struct hypmove abc;

int hypflag;

void init(void)
{
	int iforinit,jforinit;
	for(iforinit=0;iforinit<8;++iforinit){
		for(jforinit=0;jforinit<8;++jforinit)
			occupy[iforinit][jforinit]=0;
	}
	for(iforinit=0;iforinit<8;++iforinit)
		occupy[iforinit][1]=15,		occupy[iforinit][6]=25;
	occupy[0][0]=occupy[7][0]=12;
	occupy[1][0]=occupy[6][0]=14;
	occupy[2][0]=occupy[5][0]=13;
	occupy[3][0]=11;
	occupy[4][0]=10;
	occupy[0][7]=occupy[7][7]=22;
	occupy[1][7]=occupy[6][7]=24;
	occupy[2][7]=occupy[5][7]=23;
	occupy[3][7]=21;
	occupy[4][7]=20;

	no_white_moves=0, iWhiteMoves=0, givenMovesOfWhite=0;
	no_black_moves=0, iBlackMoves=0 ,givenMovesOfBlack=0;

	return;
}

void init_saved(void)
{
	FILE *fp2 = fopen("saved_game.txt","r+");
        for(int ii=7;ii>-1;--ii){
            for(int ij=0;ij<=7;++ij)
                fscanf(fp2,"%d",&occupy[ij][ii]);
        }
        fscanf(fp2,"%d%d",&player_mode,&moveforhypocrisy);
        fclose(fp2);
        return;
}



void init_hypo(void)
{
	FILE *fp2 = fopen("saved_hypo.txt","r+");
        for(int ii=7;ii>-1;--ii){
            for(int ij=0;ij<=7;++ij)
                fscanf(fp2,"%d",&occupy[ij][ii]);
        }
        fscanf(fp2,"%d%d",&player_mode,&moveforhypocrisy);
        fclose(fp2);
        return;
}

void DevouringColourforShowingMove(int i, int j)
{
	if(i<0 || j<0 || i>7 || j>7)	return;

	int colour = occupy[des_x][des_y]/9;

	if(colour==1){
			if(updatedWhiteKinginCheck(des_x,des_y,i,j) == 0){
					++no_white_moves;
			}
			else
					return;
	}

	else if(colour==2){
			if(updatedBlackKinginCheck(des_x,des_y,i,j) == 0){
					++no_black_moves;
			}
			else
					return;
	}

	iSetColor(255,0,0);
	iFilledRectangle(350+i*90,30+j*90,90,90);
	iRectangle(350+i*90+4,30+j*90+4,82,82);
	switch(occupy[des_x][des_y])
	{
	case 10:
		whiteKingOccupy[i][j]=8;
		break;
	case 11:
		whiteMinisterOccupy[i][j]=8;
		break;
	case 12:
		whiteRookOccupy[i][j]=8;
		break;
	case 13:
		whiteBishopOccupy[i][j]=8;
		break;
	case 14:
		whiteKnightOccupy[i][j]=8;
		break;
	case 15:
		whitePawnOccupy[i][j]=8;
		break;
	case 20:
		blackKingOccupy[i][j]=8;
		break;
	case 21:
		blackMinisterOccupy[i][j]=8;
		break;
	case 22:
		blackRookOccupy[i][j]=8;
		break;
	case 23:
		blackBishopOccupy[i][j]=8;
		break;
	case 24:
		blackKnightOccupy[i][j]=8;
		break;
	case 25:
		blackPawnOccupy[i][j]=8;
		break;
	}
	return;
}

void ColourforShowingMove(int i, int j)
{
	if(i<0 || j<0 || i>7 || j>7)	return;

	int colour = occupy[des_x][des_y]/9;

	if(colour==1){
			if(updatedWhiteKinginCheck(des_x,des_y,i,j) == 0){
					++no_white_moves;
			}
			else
					return;
	}

	if(colour==2){
			if(updatedBlackKinginCheck(des_x,des_y,i,j) == 0){
					++no_black_moves;
			}
			else
					return;
	}

	iSetColor(0,162,255);
	iRectangle(350+i*90+5,30+j*90+5,80,80);
	iRectangle(350+i*90+3,30+j*90+3,84,84);
	iRectangle(350+i*90+4,30+j*90+4,82,82);
	iRectangle(350+i*90+2,30+j*90+2,86,86);

	switch(occupy[des_x][des_y])
	{
	case 10:
		whiteKingOccupy[i][j]=6;
		break;
	case 11:
		whiteMinisterOccupy[i][j]=6;
		break;
	case 12:
		whiteRookOccupy[i][j]=6;
		break;
	case 13:
		whiteBishopOccupy[i][j]=6;
		break;
	case 14:
		whiteKnightOccupy[i][j]=6;
		break;
	case 15:
		whitePawnOccupy[i][j]=6;
		break;
	case 20:
		blackKingOccupy[i][j]=6;
		break;
	case 21:
		blackMinisterOccupy[i][j]=6;
		break;
	case 22:
		blackRookOccupy[i][j]=6;
		break;
	case 23:
		blackBishopOccupy[i][j]=6;
		break;
	case 24:
		blackKnightOccupy[i][j]=6;
		break;
	case 25:
		blackPawnOccupy[i][j]=6;
		break;
	}
	return;
}

void whiteRookMoveShow(void)
{
	for(int ii=0;ii<8;++ii){
		for(int ij=0;ij<8;++ij)		whiteRookOccupy[ii][ij]=0;
	}
	whiteRookOccupy[des_x][des_y]=4;
	for(int i=des_x+1;i<8;++i){
			if(isWhite(occupy[i][des_y]))
				break;
			else if(isBlack(occupy[i][des_y])){
				DevouringColourforShowingMove(i,des_y);
				break;
			}
			else{
				ColourforShowingMove(i,des_y);
			}
		}
		for(int i=des_x-1;i>-1;i--){
			if(isWhite(occupy[i][des_y]))
				break;
			else if(isBlack(occupy[i][des_y])){
				DevouringColourforShowingMove(i,des_y);
				break;
			}
			else{
				ColourforShowingMove(i,des_y);
			}
		}
		for(int i=des_y+1;i<8;++i){
			if(isWhite(occupy[des_x][i]))
				break;
			else if(isBlack(occupy[des_x][i])){
				DevouringColourforShowingMove(des_x,i);
				break;
			}
			else{
				ColourforShowingMove(des_x,i);
			}
		}
		for(int i=des_y-1;i>-1;i--){
			if(isWhite(occupy[des_x][i]))
				break;
			else if(isBlack(occupy[des_x][i])){
				DevouringColourforShowingMove(des_x,i);
				break;
			}
			else{
				ColourforShowingMove(des_x,i);
			}
		}
		return;
}

void blackRookMoveShow(void)
{
	for(int ii=0;ii<8;++ii){
		for(int ij=0;ij<8;++ij)		blackRookOccupy[ii][ij]=0;
	}
	blackRookOccupy[des_x][des_y]=4;
	for(int i=des_x+1;i<8;++i){
			if(isBlack(occupy[i][des_y]))
				break;
			else if(isWhite(occupy[i][des_y])){
				DevouringColourforShowingMove(i,des_y);
				break;
			}
			else{
				ColourforShowingMove(i,des_y);
			}
		}
		for(int i=des_x-1;i>-1;i--){
			if(isBlack(occupy[i][des_y]) )
				break;
			else if(isWhite(occupy[i][des_y])){
				DevouringColourforShowingMove(i,des_y);
				break;
			}
			else{
				ColourforShowingMove(i,des_y);
			}
		}
		for(int i=des_y+1;i<8;++i){
			if(isBlack(occupy[des_x][i]))
				break;
			else if(isWhite(occupy[des_x][i])){
				DevouringColourforShowingMove(des_x,i);
				break;
			}
			else{
				ColourforShowingMove(des_x,i);
			}
		}
		for(int i=des_y-1;i>-1;i--){
			if(isBlack(occupy[des_x][i]))
				break;
			else if(isWhite(occupy[des_x][i])){
				DevouringColourforShowingMove(des_x,i);
				break;
			}
			else{
				ColourforShowingMove(des_x,i);
			}
		}
		return;
}

void whiteBishopMoveShow(void)
{
	for(int ii=0;ii<8;++ii){
		for(int ij=0;ij<8;++ij)		whiteBishopOccupy[ii][ij]=0;
	}
	whiteBishopOccupy[des_x][des_y]=4;
	for(int i=des_x+1, j=des_y+1; i<8 && j<8;++i,++j){
			if(isWhite(occupy[i][j]))
				break;
			else if(isBlack(occupy[i][j])){
				DevouringColourforShowingMove(i,j);
				break;
			}
			else{
				ColourforShowingMove(i,j);
			}
		}
		for(int i=des_x+1, j=des_y-1; i<8 && j>-1;++i,--j){
			if(isWhite(occupy[i][j]))
				break;
			else if(isBlack(occupy[i][j])){
				DevouringColourforShowingMove(i,j);
				break;
			}
			else{
				ColourforShowingMove(i,j);
			}
		}
		for(int i=des_x-1, j=des_y+1; i>-1 && j<8;--i,++j){
			if(isWhite(occupy[i][j]))
				break;
			else if(isBlack(occupy[i][j])){
				DevouringColourforShowingMove(i,j);
				break;
			}
			else{
				ColourforShowingMove(i,j);
			}
		}
		for(int i=des_x-1, j=des_y-1; i>-1 && j>-1;--i,--j){
			if(isWhite(occupy[i][j]))
				break;
			else if(isBlack(occupy[i][j])){
				DevouringColourforShowingMove(i,j);
				break;
			}
			else{
				ColourforShowingMove(i,j);
			}
		}
		return;
}

void blackBishopMoveShow(void)
{
	for(int ii=0;ii<8;++ii){
		for(int ij=0;ij<8;++ij)		blackBishopOccupy[ii][ij]=0;
	}
	blackBishopOccupy[des_x][des_y]=4;
	for(int i=des_x+1, j=des_y+1; i<8 && j<8;++i,++j){
			if(isBlack(occupy[i][j]))
				break;
			else if(isWhite(occupy[i][j])){
				DevouringColourforShowingMove(i,j);
				//blackBishopOccupy[i][j]=8;
				break;
			}
			else{
				ColourforShowingMove(i,j);
				//blackBishopOccupy[i][j]=6;
			}
		}
		for(int i=des_x+1, j=des_y-1; i<8 && j>-1;++i,--j){
			if(isBlack(occupy[i][j]))
				break;
			else if(isWhite(occupy[i][j])){
				DevouringColourforShowingMove(i,j);
				//blackBishopOccupy[i][j]=8;
				break;
			}
			else{
				ColourforShowingMove(i,j);
				//blackBishopOccupy[i][j]=6;
			}
		}
		for(int i=des_x-1, j=des_y+1; i>-1 && j<8;--i,++j){
			if(isBlack(occupy[i][j]))
				break;
			else if(isWhite(occupy[i][j])){
				DevouringColourforShowingMove(i,j);
				//blackBishopOccupy[i][j]=8;
				break;
			}
			else{
				ColourforShowingMove(i,j);
				//blackBishopOccupy[i][j]=6;
			}
		}
		for(int i=des_x-1, j=des_y-1; i>-1 && j>-1;--i,--j){
			if(isBlack(occupy[i][j]))
				break;
			else if(isWhite(occupy[i][j])){
				DevouringColourforShowingMove(i,j);
				//blackBishopOccupy[i][j]=8;
				break;
			}
			else{
				ColourforShowingMove(i,j);
				//blackBishopOccupy[i][j]=6;
			}
		}
		return;
}


void whiteKnightMoveShow(void)
{
	int i,j;
	//printf("\n\n\n");
	for(i=0;i<8;++i){
			for(j=0;j<8;++j)		whiteKnightOccupy[i][j]=0;
	}
	i=des_x, j=des_y;
	whiteKnightOccupy[des_x][des_y]=4;	 // 4 - it's here
	if(i+2 < 8 && j+1 < 8){
		if(isBlack(occupy[i+2][j+1]))  DevouringColourforShowingMove(i+2,j+1);//	whiteKnightOccupy[i+2][j+1]=8; //8 - opposite colour
		else if(isWhite(occupy[i+2][j+1]));
		else	ColourforShowingMove(i+2,j+1);//,		whiteKnightOccupy[i+2][j+1]=6;	//6 - same colour
	}
	if(i+2 < 8 && j-1 > -1){
		if(isBlack(occupy[i+2][j-1]))  DevouringColourforShowingMove(i+2,j-1);//, whiteKnightOccupy[i+2][j-1]=8;
		else if(isWhite(occupy[i+2][j-1]));
		else	ColourforShowingMove(i+2,j-1);//,	whiteKnightOccupy[i+2][j-1]=6;
	}
	if(i-2 > -1 && j+1 < 8){
		if(isBlack(occupy[i-2][j+1]))  DevouringColourforShowingMove(i-2,j+1);// whiteKnightOccupy[i-2][j+1]=8;
		else if(isWhite(occupy[i-2][j+1]));
		else	ColourforShowingMove(i-2,j+1);// whiteKnightOccupy[i-2][j+1]=6;
	}
	if(i-2 > -1 && j-1 > -1){
		if(isBlack(occupy[i-2][j-1]))  DevouringColourforShowingMove(i-2,j-1);//	whiteKnightOccupy[i-2][j-1]=8;
		else if(isWhite(occupy[i-2][j-1]));
		else	ColourforShowingMove(i-2,j-1);//	whiteKnightOccupy[i-2][j-1]=6;
	}
	if(i+1 < 8 && j+2 < 8){
		if(isBlack(occupy[i+1][j+2]))  DevouringColourforShowingMove(i+1,j+2);//	whiteKnightOccupy[i+1][j+2]=8;
		else if(isWhite(occupy[i+1][j+2]));
		else	ColourforShowingMove(i+1,j+2);//	whiteKnightOccupy[i+1][j+2]=6;
	}
	if(i+1 < 8 && j-2 > -1){
		if(isBlack(occupy[i+1][j-2]))  DevouringColourforShowingMove(i+1,j-2);//	whiteKnightOccupy[i+1][j-2]=8;
		else if(isWhite(occupy[i+1][j-2]));
		else	ColourforShowingMove(i+1,j-2);//		whiteKnightOccupy[i+1][j-2]=6;
	}
	if(i-1 > -1 && j+2 < 8){
		if(isBlack(occupy[i-1][j+2]))  DevouringColourforShowingMove(i-1,j+2);//	whiteKnightOccupy[i-1][j+2]=8;
		else if(isWhite(occupy[i-1][j+2]));
		else	ColourforShowingMove(i-1,j+2);//	whiteKnightOccupy[i-1][j+2]=6;
	}
	if(i-1 > -1 && j-2 > -1){
		if(isBlack(occupy[i-1][j-2]))  DevouringColourforShowingMove(i-1,j-2);//	whiteKnightOccupy[i+1][j-2]=8;
		else if(isWhite(occupy[i-1][j-2]));
		else	ColourforShowingMove(i-1,j-2);//	whiteKnightOccupy[i-1][j-2]=6;
	}
	/*for(i=7;i>=0;--i){
			for(j=0;j<8;++j)		printf("%d\t",whiteKnightOccupy[j][i]);
			printf("\n");
	}*/
	return;
}

void blackKnightMoveShow(void)
{
	int i,j;
	/*printf("\n\n\n");*/
	for(i=0;i<8;++i){
			for(j=0;j<8;++j)		blackKnightOccupy[i][j]=0;
	}
	i=des_x, j=des_y;
	blackKnightOccupy[i][j]=4;
	if(i+2 < 8 && j+1 < 8){
		if(isWhite(occupy[i+2][j+1]))  DevouringColourforShowingMove(i+2,j+1);//	blackKnightOccupy[i+2][j+1]=8;
		else if(isBlack(occupy[i+2][j+1]));
		else	ColourforShowingMove(i+2,j+1);//	blackKnightOccupy[i+2][j+1]=6;
	}
	if(i+2 < 8 && j-1 > -1){
		if(isWhite(occupy[i+2][j-1]))  DevouringColourforShowingMove(i+2,j-1);//	blackKnightOccupy[i+2][j-1]=8;
		else if(isBlack(occupy[i+2][j-1]));
		else	ColourforShowingMove(i+2,j-1);//		blackKnightOccupy[i+2][j-1]=6;
	}
	if(i-2 > -1 && j+1 < 8){
		if(isWhite(occupy[i-2][j+1]))  DevouringColourforShowingMove(i-2,j+1);//	blackKnightOccupy[i-2][j+1]=8;
		else if(isBlack(occupy[i-2][j+1]));
		else	ColourforShowingMove(i-2,j+1);//		blackKnightOccupy[i-2][j+1]=6;
	}
	if(i-2 > -1 && j-1 > -1){
		if(isWhite(occupy[i-2][j-1]))  DevouringColourforShowingMove(i-2,j-1);//		blackKnightOccupy[i-2][j-1]=8;
		else if(isBlack(occupy[i-2][j-1]));
		else	ColourforShowingMove(i-2,j-1);//	blackKnightOccupy[i-2][j-1]=6;
	}
	if(i+1 < 8 && j+2 < 8){
		if(isWhite(occupy[i+1][j+2]))  DevouringColourforShowingMove(i+1,j+2);// 	blackKnightOccupy[i+1][j+2]=8;
		else if(isBlack(occupy[i+1][j+2]));
		else	ColourforShowingMove(i+1,j+2);//	blackKnightOccupy[i+1][j+2]=6;
	}
	if(i+1 < 8 && j-2 > -1){
		if(isWhite(occupy[i+1][j-2]))  DevouringColourforShowingMove(i+1,j-2);//	blackKnightOccupy[i+1][j-2]=8;
		else if(isBlack(occupy[i+1][j-2]));
		else	ColourforShowingMove(i+1,j-2);//		blackKnightOccupy[i+1][j-2]=6;
	}
	if(i-1 > -1 && j+2 < 8){
		if(isWhite(occupy[i-1][j+2]))  DevouringColourforShowingMove(i-1,j+2);//	blackKnightOccupy[i-1][j+2]=8;
		else if(isBlack(occupy[i-1][j+2]));
		else	ColourforShowingMove(i-1,j+2);//	blackKnightOccupy[i-1][j+2]=6;
	}
	if(i-1 > -1 && j-2 > -1){
		if(isWhite(occupy[i-1][j-2]))  DevouringColourforShowingMove(i-1,j-2);//		blackKnightOccupy[i-1][j-2]=8;
		else if(isBlack(occupy[i-1][j-2]));
		else	ColourforShowingMove(i-1,j-2);//	blackKnightOccupy[i-1][j-2]=6;
	}
	/*for(i=7;i>-1;i--){
		for(j=0;j<8;++j)
			printf("%d\t",blackKnightOccupy[j][i]);
		printf("\n");
	}*/
	return;
}

void whiteMinisterMoveShow(void)
{
	for(int ii=0;ii<8;++ii){
		for(int ij=0;ij<8;++ij)		whiteMinisterOccupy[ii][ij]=0;
	}
	occupy[des_x][des_y]=13;
	whiteBishopMoveShow();
	occupy[des_x][des_y]=12;
	whiteRookMoveShow();
	occupy[des_x][des_y]=11;
      for(int ii=7;ii>=0;--ii){
		for(int ij=0;ij<=7;++ij){
			whiteMinisterOccupy[ii][ij]	= 	whiteBishopOccupy[ii][ij]	+	whiteRookOccupy[ii][ij];
		}
      }
      whiteMinisterOccupy[des_x][des_y]=4;
      //printf("\n\nWHITE MINISTER\n\n");
      /*for(int ii=7;ii>=0;--ii){
		for(int ij=0;ij<=7;++ij){
			printf("%d\t",whiteRookOccupy[ij][ii]);
		}
		printf("\n");
      }*/
}

void blackMinisterMoveShow(void)
{
	for(int ii=0;ii<8;++ii){
		for(int ij=0;ij<8;++ij)		blackMinisterOccupy[ii][ij]=0;
	}
	occupy[des_x][des_y]=23;
	blackBishopMoveShow();
	occupy[des_x][des_y]=22;
	blackRookMoveShow();
	occupy[des_x][des_y]=21;
      for(int ii=7;ii>=0;--ii){
		for(int ij=0;ij<=7;++ij){
			blackMinisterOccupy[ii][ij]	= 	blackBishopOccupy[ii][ij]	+	blackRookOccupy[ii][ij];
		}
      }
      blackMinisterOccupy[des_x][des_y]=4;
}

void whitePawnMoveShow(void)
{
	for(int ii=0;ii<8;++ii){
		for(int ij=0;ij<8;++ij)		whitePawnOccupy[ii][ij]=0;
	}
	if(des_y==1 && occupy[des_x][2]==0 && occupy[des_x][3]==0){
		ColourforShowingMove(des_x,3);
		//whitePawnOccupy[des_x][3]=6;

		/*if(whitePawnOccupy[des_x][3]==6)
			printf("\n\nPRINTING A GOOD GARBAGE\n\n");
		else
			printf("\n\ndfjkczhJEGYKUEXJEKUqGKexzGHDdwxDKUREJHFGUhkerzehvjfgbHHXGREx %d\n\n",whitePawnOccupy[des_x][3]==6);*/
	}
	if(occupy[des_x][des_y+1]==0){
		ColourforShowingMove(des_x,des_y+1);
		;//whitePawnOccupy[des_x][des_y+1]=6;
	}
	if(isBlack(occupy[des_x+1][des_y+1])){
		DevouringColourforShowingMove(des_x+1,des_y+1);
		;//whitePawnOccupy[des_x+1][des_y+1]=8;
	}
	if(isBlack(occupy[des_x-1][des_y+1])){
		DevouringColourforShowingMove(des_x-1,des_y+1);
		;//whitePawnOccupy[des_x-1][des_y+1]=8;
	}
	return;
}

void blackPawnMoveShow(void)
{
	for(int ii=0;ii<8;++ii){
		for(int ij=0;ij<8;++ij)		blackPawnOccupy[ii][ij]=0;
	}
	if(des_y==6 && occupy[des_x][5]==0 && occupy[des_x][4]==0){
		ColourforShowingMove(des_x,4);
		;//blackPawnOccupy[des_x][4]=6;
	}
	if(occupy[des_x][des_y-1]==0){
		ColourforShowingMove(des_x,des_y-1);
		;//blackPawnOccupy[des_x][des_y-1]=6;
	}
	if(isWhite(occupy[des_x-1][des_y-1])){
		DevouringColourforShowingMove(des_x-1,des_y-1);
		;//blackPawnOccupy[des_x-1][des_y-1]=8;
	}
	if(isWhite(occupy[des_x+1][des_y-1])){
		DevouringColourforShowingMove(des_x+1,des_y-1);
		;//blackPawnOccupy[des_x+1][des_y-1]=8;
	}
	return;
}

void whiteKingMoveShow()
{
	for(int ii=0;ii<8;++ii)	for(int ij=0;ij<8;++ij)	whiteKingOccupy[ii][ij]=0;
      for(int i=(des_x-1);i<=(des_x+1);++i){
		for(int j=(des_y-1);j<=(des_y+1);++j){
			if(isBlack(occupy[i][j]))
				/*whiteKingOccupy[i][j]=8, */DevouringColourforShowingMove(i,j);
			else if(i==des_x && j==des_y)
				whiteKingOccupy[i][j]=4;
			else if(occupy[i][j]==0)
				/*whiteKingOccupy[i][j]=6, */ColourforShowingMove(i,j);
		}
      }
      if(occupy[4][0]==10 && occupy[0][0]==12&& (occupy[2][0]|occupy[3][0])==0 && !whiteKingInCheck()){
		ColourforShowingMove(2,0);
		whiteKingOccupy[2][0]=10;
      }
      else if(occupy[4][0]==10 && occupy[7][0]==12&& (occupy[5][0]|occupy[6][0])==0 && !whiteKingInCheck()){
		ColourforShowingMove(6,0);
		whiteKingOccupy[6][0]=10;
      }
}

void blackKingMoveShow()
{
	//printf("blabla %d %d\n",des_x,des_y);
	for(int ii=0;ii<8;++ii)	for(int ij=0;ij<8;++ij)	blackKingOccupy[ii][ij]=0;
      for(int i=(des_x-1);i<=(des_x+1);++i){
		for(int j=(des_y-1);j<=(des_y+1);++j){
				//printf("In BLACK KING: %d %d\n",i,j);
			if(isWhite(occupy[i][j]))
				/*blackKingOccupy[i][j]=8, */DevouringColourforShowingMove(i,j);
			else if(i==des_x && j==des_y)
				blackKingOccupy[i][j]=4;
			else if(occupy[i][j]==0)
				/*blackKingOccupy[i][j]=6,*/ ColourforShowingMove(i,j);
		}
      }
      if(occupy[4][7]==20 && occupy[0][7]==22 && (occupy[2][7]|occupy[3][7])==0 && !blackKingInCheck()){
		ColourforShowingMove(1,0);
		blackKingOccupy[2][7]=10;
      }
      else if(occupy[4][7]==20 && occupy[7][7]==22 && (occupy[5][7]|occupy[6][7])==0 && !blackKingInCheck()){
		ColourforShowingMove(6,0);
		blackKingOccupy[6][7]=10;
      }
}

int whitePawnMoveHappen()
{
	if(whitePawnOccupy[des_x_final][des_y_final]==6 ||whitePawnOccupy[des_x_final][des_y_final]==8)
	{
		occupy[des_x_final][des_y_final]=occupy[des_x][des_y];
		occupy[des_x][des_y]=0;
		if(des_y_final==7){
			occupy[des_x_final][7]=11;
		}
		return 1;
	}
	return 0;
}

int blackPawnMoveHappen()
{
	if(blackPawnOccupy[des_x_final][des_y_final]==6 ||blackPawnOccupy[des_x_final][des_y_final]==8)
	{
		occupy[des_x_final][des_y_final]=occupy[des_x][des_y];
		occupy[des_x][des_y]=0;
		if(des_y_final==0){
			occupy[des_x_final][0]=21;
		}
		return 1;
	}
	return 0;
}

int whiteKingMoveHappen()
{
	if(whiteKingOccupy[des_x_final][des_y_final]==10)
	{
		occupy[des_x_final][des_y_final]=occupy[des_x][des_y];
		occupy[des_x][des_y]=0;
		if(des_x_final==2){
			occupy[0][0]=0;
			occupy[3][0]=12;
		}
		else{
			occupy[7][0]=0;
			occupy[5][0]=12;
		}
		return 1;
	}
	if(whiteKingOccupy[des_x_final][des_y_final]==6 ||whiteKingOccupy[des_x_final][des_y_final]==8)
	{
		occupy[des_x_final][des_y_final]=occupy[des_x][des_y];
		occupy[des_x][des_y]=0;
		return 1;
	}
	return 0;
}

int blackKingMoveHappen()
{
	if(blackKingOccupy[des_x_final][des_y_final]==10)
	{
		occupy[des_x_final][des_y_final]=occupy[des_x][des_y];
		occupy[des_x][des_y]=0;
		if(des_x_final==2){
			occupy[0][7]=0;
			occupy[3][7]=12;
		}
		else{
			occupy[7][7]=0;
			occupy[5][7]=12;
		}
		return 1;
	}
	if(blackKingOccupy[des_x_final][des_y_final]==6 ||blackKingOccupy[des_x_final][des_y_final]==8)
	{
		occupy[des_x_final][des_y_final]=occupy[des_x][des_y];
		occupy[des_x][des_y]=0;
		return 1;
	}
	return 0;
}

int whiteMinisterMoveHappen()
{
	if(whiteMinisterOccupy[des_x_final][des_y_final]==6 ||whiteMinisterOccupy[des_x_final][des_y_final]==8)
	{
		occupy[des_x_final][des_y_final]=occupy[des_x][des_y];
		occupy[des_x][des_y]=0;
		return 1;
	}
	return 0;
}

int blackMinisterMoveHappen()
{
	if(blackMinisterOccupy[des_x_final][des_y_final]==6 ||blackMinisterOccupy[des_x_final][des_y_final]==8)
	{
		occupy[des_x_final][des_y_final]=occupy[des_x][des_y];
		occupy[des_x][des_y]=0;
		return 1;
	}
	return 0;
}

int whiteRookMoveHappen()
{
	if(whiteRookOccupy[des_x_final][des_y_final]==6 ||whiteRookOccupy[des_x_final][des_y_final]==8)
	{
		occupy[des_x_final][des_y_final]=occupy[des_x][des_y];
		occupy[des_x][des_y]=0;
		return 1;
	}
	return 0;
}

int blackRookMoveHappen()
{
	if(blackRookOccupy[des_x_final][des_y_final]==6 ||blackRookOccupy[des_x_final][des_y_final]==8)
	{
		occupy[des_x_final][des_y_final]=occupy[des_x][des_y];
		occupy[des_x][des_y]=0;
		return 1;
	}
	return 0;
}

int whiteKnightMoveHappen()
{
	if(whiteKnightOccupy[des_x_final][des_y_final]==6 ||whiteKnightOccupy[des_x_final][des_y_final]==8)
	{
		occupy[des_x_final][des_y_final]=occupy[des_x][des_y];
		occupy[des_x][des_y]=0;
		return 1;
	}
	return 0;
}

int blackKnightMoveHappen()
{
	if(blackKnightOccupy[des_x_final][des_y_final]==6 ||blackKnightOccupy[des_x_final][des_y_final]==8)
	{
		occupy[des_x_final][des_y_final]=occupy[des_x][des_y];
		occupy[des_x][des_y]=0;
		return 1;
	}
	return 0;
}

int whiteBishopMoveHappen()
{
	if(whiteBishopOccupy[des_x_final][des_y_final]==6 ||whiteBishopOccupy[des_x_final][des_y_final]==8)
	{
		occupy[des_x_final][des_y_final]=occupy[des_x][des_y];
		occupy[des_x][des_y]=0;
		return 1;
	}
	return 0;
}

int blackBishopMoveHappen()
{
	if(blackBishopOccupy[des_x_final][des_y_final]==6 ||blackBishopOccupy[des_x_final][des_y_final]==8)
	{
		occupy[des_x_final][des_y_final]=occupy[des_x][des_y];
		occupy[des_x][des_y]=0;
		return 1;
	}
	return 0;
}

int whiteKingInCheck(void)
{
	int i,j,white_king_x,white_king_y,black_king_x,black_king_y;
	for(i=0;i<8;++i){
		for(j=0;j<8;++j){
			if(occupy[i][j]==10){
				white_king_x=i,	white_king_y=j;
			}
			else if(occupy[i][j]==20){
				black_king_x=i,		black_king_y=j;
			}
		}
	}
	//printf("\nWHITE KING x=%d y=%d\n",white_king_x,white_king_y);
	for(i=white_king_x+1;i<8;++i){
		if(occupy[i][white_king_y] == 21 || occupy[i][white_king_y] == 22){
			return 1;
		}
		else if(occupy[i][white_king_y] == 0)
			continue;
		else
			break;
	}
	for(i=white_king_x-1;i>=0;--i){
		if(occupy[i][white_king_y] == 21 || occupy[i][white_king_y] == 22){
			return 1;
		}
		else if(occupy[i][white_king_y] == 0)
			continue;
		else
			break;
	}
	for(j=white_king_y+1;j<8;++j){
		if(occupy[white_king_x][j] == 21 || occupy[white_king_x][j] == 22)
			return 1;
		else if(occupy[white_king_x][j] == 0)
			continue;
		else
			break;
	}
	for(j=white_king_y-1;j>=0;--j){
		if(occupy[white_king_x][j] == 21 || occupy[white_king_x][j] == 22)
			return 1;
		else if(occupy[white_king_x][j] == 0)
			continue;
		else
			break;
	}
	for(i=white_king_x+1,j=white_king_y+1;i<8 && j<8;++i,++j){
		if(occupy[i][j] == 21 || occupy[i][j] == 23)
			return 1;
		else if(occupy[i][j] == 0)
			continue;
		else
			break;
	}
	for(i=white_king_x+1,j=white_king_y-1;i<8 && j>=0;++i,--j){
		if(occupy[i][j] == 21 || occupy[i][j] == 23)
			return 1;
		else if(occupy[i][j] == 0)
			continue;
		else
			break;
	}
	for(i=white_king_x-1,j=white_king_y+1;i>=0 && j<8;--i,++j){
		if(occupy[i][j] == 21 || occupy[i][j] == 23)
			return 1;
		else if(occupy[i][j] == 0)
			continue;
		else
			break;
	}
	for(i=white_king_x-1,j=white_king_y-1;i>=0 && j>=0;--i,--j){
		if(occupy[i][j] == 21 || occupy[i][j] == 23)
			return 1;
		else if(occupy[i][j] == 0)
			continue;
		else
			break;
	}
	i=white_king_x,	j=white_king_y;
	if((i+2<8 && j+1<8 && occupy[i+2][j+1]==24) || (i+2<8 && j-1>=0 && occupy[i+2][j-1]==24) || (i-2>=0 && j+1<8 && occupy[i-2][j+1]==24) || (i-2>=0 && j-1>=0 && occupy[i-2][j-1]==24))
		return 1;
	if((j+2<8 && i+1<8 && occupy[i+1][j+2]==24) || (j+2<8 && i-1>=0 && occupy[i-1][j+2]==24) || (j-2>=0 && i+1<8 && occupy[i+1][j-2]==24) || (j-2>=0 && i-1>=0 && occupy[i-1][j-2]==24))
		return 1;
	if(j+1<8 && (i+1<8 &&occupy[i+1][j+1]==25) ||(i-1>=0 && occupy[i-1][j+1]==25))
		return 1;
	if(abs(white_king_x-black_king_x)<2 && abs(white_king_y-black_king_y)<2)
		return 1;
	return 0;
}


int blackKingInCheck(void)
{
	int i,j,white_king_x,white_king_y,black_king_x,black_king_y;
	for(i=0;i<8;++i){
		for(j=0;j<8;++j){
			if(occupy[i][j]==10){
				white_king_x=i,	white_king_y=j;
			}
			else if(occupy[i][j]==20){
				black_king_x=i,		black_king_y=j;
			}
		}
	}
	for(i=black_king_x+1;i<8;++i){
		if(occupy[i][black_king_y] == 11 || occupy[i][black_king_y] == 12){
			return 1;
		}
		else if(occupy[i][black_king_y] == 0)
			continue;
		else
			break;
	}
	for(i=black_king_x-1;i>=0;--i){
		if(occupy[i][black_king_y] == 11 || occupy[i][black_king_y] == 12){
			return 1;
		}
		else if(occupy[i][black_king_y] == 0)
			continue;
		else
			break;
	}
	for(j=black_king_y+1;j<8;++j){
		if(occupy[black_king_x][j] == 11 || occupy[black_king_x][j] == 12)
			return 1;
		else if(occupy[black_king_x][j] == 0)
			continue;
		else
			break;
	}
	for(j=black_king_y-1;j>=0;--j){
		if(occupy[black_king_x][j] == 11 || occupy[black_king_x][j] == 12)
			return 1;
		else if(occupy[black_king_x][j] == 0)
			continue;
		else
			break;
	}
	for(i=black_king_x+1,j=black_king_y+1;i<8 && j<8;++i,++j){
		if(occupy[i][j] == 11 || occupy[i][j] == 13)
			return 1;
		else if(occupy[i][j] == 0)
			continue;
		else
			break;
	}
	for(i=black_king_x+1,j=black_king_y-1;i<8 && j>=0;++i,--j){
		if(occupy[i][j] == 11 || occupy[i][j] == 13)
			return 1;
		else if(occupy[i][j] == 0)
			continue;
		else
			break;
	}
	for(i=black_king_x-1,j=black_king_y+1;i>=0 && j<8;--i,++j){
		if(occupy[i][j] == 11 || occupy[i][j] == 13)
			return 1;
		else if(occupy[i][j] == 0)
			continue;
		else
			break;
	}
	for(i=black_king_x-1,j=black_king_y-1;i>=0 && j>=0;--i,--j){
		if(occupy[i][j] == 11 || occupy[i][j] == 13)
			return 1;
		else if(occupy[i][j] == 0)
			continue;
		else
			break;
	}
	i=black_king_x,	j=black_king_y;
	if((i+2<8 && j+1<8 && occupy[i+2][j+1]==14) || (i+2<8 && j-1>=0 && occupy[i+2][j-1]==14) || (i-2>=0 && j+1<8 && occupy[i-2][j+1]==14) || (i-2>=0 && j-1>=0 && occupy[i-2][j-1]==14))
		return 1;
	if((j+2<8 && i+1<8 && occupy[i+1][j+2]==14) || (j+2<8 && i-1>=0 && occupy[i-1][j+2]==14) || (j-2>=0 && i+1<8 && occupy[i+1][j-2]==14) || (j-2>=0 && i-1>=0 && occupy[i-1][j-2]==14))
		return 1;
	if(j+1<8 && (i+1<8 && occupy[i+1][j-1]==15) ||(i-1>=0 && occupy[i-1][j-1]==15))
		return 1;
	if(abs(white_king_x-black_king_x)<2 && abs(white_king_y-black_king_y)<2)
		return 1;
	return 0;
}

int updatedWhiteKinginCheck(int bef_x, int bef_y, int up_x, int up_y)
{
	int mode1=occupy[bef_x][bef_y],mode2=occupy[up_x][up_y];
	occupy[up_x][up_y]=mode1;
	occupy[bef_x][bef_y]=0;	//THIS LINE TOOK 4 DAYS TO BE DEBUGGED
	int q=whiteKingInCheck();
	occupy[bef_x][bef_y]=mode1;
	occupy[up_x][up_y]=mode2;
	return q;
}

int updatedBlackKinginCheck(int bef_x, int bef_y, int up_x, int up_y)
{
	int mode1=occupy[bef_x][bef_y],mode2=occupy[up_x][up_y];
	occupy[up_x][up_y]=mode1;
	occupy[bef_x][bef_y]=0;
	int q=blackKingInCheck();
	occupy[bef_x][bef_y]=mode1;
	occupy[up_x][up_y]=mode2;
	return q;
}

//Counting moves for white
//Only use is, if it is zero, we can consider checkmate or stalemate draw

int whiteMoveCounter()
{
	int store_x=des_x, store_y=des_y, store_mode=occupy[des_x][des_y];
	no_white_moves=0;
	for(des_x=0;des_x<=7;++des_x){
		for(des_y=0;des_y<=7;++des_y){
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
	}
	des_x=store_x;
	des_y=store_y;
	occupy[des_x][des_y]=store_mode;
	printf("\n\n");
	return no_white_moves;
}

//Counting moves as in white

int blackMoveCounter()
{
	int store_x=des_x, store_y=des_y, store_mode=occupy[des_x][des_y];
	no_black_moves=0;
	for(des_x=0;des_x<=7;++des_x){
		for(des_y=0;des_y<=7;++des_y){
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
		}
	des_x=store_x;
	des_y=store_y;
	occupy[des_x][des_y]=store_mode;
	return no_black_moves;
}

//Showing the Pictures
//For historical reasons, the name never changed

void tempShowbyString (int i, int j)
{
	int mode=occupy[i][j];
	if(mode>16){
		iSetColor(10,0,57);
	}
	else{
		iSetColor(0,72,0);
	}
	switch(mode)
	{
	case 10:
		//iText(350+i*90+10,30+j*90+10,"White King");
		iShowBMP(350+i*90+5,30+j*90+5,"10.bmp");
		break;
	case 11:
		//iText(350+i*90+10,30+j*90+10,"White Queen");
		iShowBMP(350+i*90+5,30+j*90+5,"11.bmp");
		break;
	case 12:
		//iText(350+i*90+10,30+j*90+10,"White Rook");
		iShowBMP(350+i*90+5,30+j*90+5,"12.bmp");
		break;
	case 13:
		//iText(350+i*90+10,30+j*90+10,"White Bishop");
		iShowBMP(350+i*90+5,30+j*90+5,"13.bmp");
		break;
	case 14:
		//iText(350+i*90+10,30+j*90+10,"White Knight");
		iShowBMP(350+i*90+5,30+j*90+5,"14.bmp");
		break;
	case 15:
		//iText(350+i*90+10,30+j*90+10,"White Pawn");
		iShowBMP(350+i*90+5,30+j*90+5,"15.bmp");
		break;
	case 20:
		//iText(350+i*90+10,30+j*90+10,"Black King");
		iShowBMP(350+i*90+5,30+j*90+5,"20.bmp");
		break;
	case 21:
		//iText(350+i*90+10,30+j*90+10,"Black Queen");
		iShowBMP(350+i*90+5,30+j*90+5,"21.bmp");
		break;
	case 22:
		//iText(350+i*90+10,30+j*90+10,"Black Rook");
		iShowBMP(350+i*90+5,30+j*90+5,"22.bmp");
		break;
	case 23:
		//iText(350+i*90+10,30+j*90+10,"Black Bishop");
		iShowBMP(350+i*90+5,30+j*90+5,"23.bmp");
		break;
	case 24:
		//iText(350+i*90+10,30+j*90+10,"Black Knight");
		iShowBMP(350+i*90+5,30+j*90+5,"24.bmp");
		break;
	case 25:
		//iText(350+i*90+10,30+j*90+10,"Black Pawn");
		iShowBMP(350+i*90+5,30+j*90+5,"25.bmp");
		break;
	case 0:
		break;
	default:
		iText(350+i*90+10,30+j*90+10,"Problem Pawn");
		break;
	}
	return;
}
