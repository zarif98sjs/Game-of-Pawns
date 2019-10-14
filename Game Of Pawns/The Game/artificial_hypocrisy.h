/*
	By which definition, is this program computer-generated?
	This is the most lame part of the code
	A rather GREEDY approach to find a solution
	So, everything regarding automation is a hypocrisy
*/


//the STL vector to keep the possible moves
vector<hypmove> letsmove;

//the comparison function
bool comp(hypmove A, hypmove B)
{
	//It first checks for potential checks
	if(A.is_check != B.is_check)
								return A.is_check>B.is_check;

	//If one can devour a piece, but the other one can't, then devour
	if(A.dev <= 0)			return 0;
	if(B.dev <= 0)			return 1;

	//A pawn devouring a queen, dream scenario
	if(A.dev != B.dev)		return A.dev<B.dev;
	if(A.self != B.self)		return A.self>B.self;

	//Else randomly written some calls will work randomly
	if(rand() % 2)			return A.from_x>B.to_x;
	else						return A.to_y>B.from_y;
}

void artificialHypocrisy(void)
{
	int tx,ty;
	letsmove.clear();
	hypflag = 0;
	for(int ii=0; ii<8; ++ii){
		for(int ij=0;ij<8;++ij){
			hypflag=0;
			if(isBlack(occupy[ii][ij])){
				abc.from_x = ii;
				abc.from_y = ij;
				abc.self = occupy[ii][ij];
				des_x = ii;
				des_y = ij;
				tx = des_x;
				ty = des_y;
				switch(occupy[ii][ij])
				  {
					  case 20:
						blackKingMoveShow();
						for(int jj=0;jj<8;++jj){
							for(int jk=0;jk<8;++jk){
								if(blackKingOccupy[jj][jk]==8 || blackKingOccupy[jj][jk]==6 || blackKingOccupy[jj][jk]==10){
									abc.to_x = jj;
									abc.to_y = jk;
									abc.dev = occupy[jj][jk];
									if(abc.dev == 0 )	abc.dev=-1;
									if(updatedWhiteKinginCheck(ii,ij,jj,jk))	abc.is_check=1;
									else											abc.is_check=0;
									letsmove.push_back(abc);
									++hypflag;
								}
							}
						}
						break;
					  case 22:
						blackRookMoveShow();
						for(int jj=0;jj<8;++jj){
							for(int jk=0;jk<8;++jk){
								if(blackRookOccupy[jj][jk]==8 || blackRookOccupy[jj][jk]==6){
									abc.to_x = jj;
									abc.to_y = jk;
									abc.dev = occupy[jj][jk];
									if(updatedWhiteKinginCheck(ii,ij,jj,jk))	abc.is_check=1;
									else											abc.is_check=0;
									letsmove.push_back(abc);
									++hypflag;
								}
							}
						}
						break;
					  case 23:
						blackBishopMoveShow();
						for(int jj=0;jj<8;++jj){
							for(int jk=0;jk<8;++jk){
								if(blackBishopOccupy[jj][jk]==8 || blackBishopOccupy[jj][jk]==6){
									abc.to_x = jj;
									abc.to_y = jk;
									abc.dev = occupy[jj][jk];
									if(updatedWhiteKinginCheck(ii,ij,jj,jk))	abc.is_check=1;
									else											abc.is_check=0;
									letsmove.push_back(abc);
									++hypflag;
								}
							}
						}
						break;
					  case 21:
						blackMinisterMoveShow();
						for(int jj=0;jj<8;++jj){
							for(int jk=0;jk<8;++jk){
								if(blackMinisterOccupy[jj][jk]==8 || blackMinisterOccupy[jj][jk]==6){
									abc.to_x = jj;
									abc.to_y = jk;
									abc.dev = occupy[jj][jk];
									if(updatedWhiteKinginCheck(ii,ij,jj,jk))	abc.is_check=1;
									else											abc.is_check=0;
									++hypflag;
									letsmove.push_back(abc);
								}
							}
						}
						break;
					  case 24:
						blackKnightMoveShow();
						for(int jj=0;jj<8;++jj){
							for(int jk=0;jk<8;++jk){
								if(blackKnightOccupy[jj][jk]==8 || blackKnightOccupy[jj][jk]==6){
									abc.to_x = jj;
									abc.to_y = jk;
									abc.dev = occupy[jj][jk];
									if(updatedWhiteKinginCheck(ii,ij,jj,jk))	abc.is_check=1;
									else											abc.is_check=0;
									letsmove.push_back(abc);
									++hypflag;
								}
							}
						}
						break;
					  case 25:
						blackPawnMoveShow();
						for(int jj=0;jj<8;++jj){
							for(int jk=0;jk<8;++jk){
								if(blackPawnOccupy[jj][jk]==8  || blackPawnOccupy[jj][jk]==6){
									abc.to_x = jj;
									abc.to_y = jk;
									abc.dev = occupy[jj][jk];
									if(updatedWhiteKinginCheck(ii,ij,jj,jk))	abc.is_check=1;
									else											abc.is_check=0;
									letsmove.push_back(abc);
									++hypflag;
								}
							}
						}
						break;
				  }
				  if(hypflag)	letsmove.push_back(abc);
				  des_x = tx, des_y=ty;
			}
		}
	}

	//sorting them in-place with the comp function
	stable_sort(letsmove.begin(),letsmove.end(),comp);
}


