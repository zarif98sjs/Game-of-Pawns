
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
int x2=170,y2=585;

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

void dekhano2(char *str2,int x,int y)
{
    siz=strlen(str2);

    int i=0,j=0;

    if(strlen(str2)==1)
    {
        buildSegment(ara0,z*i,x,y);
        j++;
    }


    for(i=0; i<strlen(str2);i++,j++)
    {
        //printf("dhukseeeeeeee\n");

        if(str2[i]=='0')
            buildSegment(ara0,z*j,x,y);
        if(str2[i]=='1')
            buildSegment(ara1,z*j,x,y);
        if(str2[i]=='2')
            buildSegment(ara2,z*j,x,y);
        if(str2[i]=='3')
            buildSegment(ara3,z*j,x,y);
        if(str2[i]=='4')
            buildSegment(ara4,z*j,x,y);
        if(str2[i]=='5')
            buildSegment(ara5,z*j,x,y);
        if(str2[i]=='6')
            buildSegment(ara6,z*j,x,y);
        if(str2[i]=='7')
            buildSegment(ara7,z*j,x,y);
        if(str2[i]=='8')
            buildSegment(ara8,z*j,x,y);
        if(str2[i]=='9')
            buildSegment(ara9,z*j,x,y);
    }
}

void init_saved_blitz(void)
{
	FILE *fp2 = fopen("saved_blitz.txt","r+");
        for(int ii=7;ii>-1;--ii){
            for(int ij=0;ij<=7;++ij)
                fscanf(fp2,"%d",&occupy[ij][ii]),printf("D%d\t",occupy[ij][ii]);;
            printf("\n");
        }
        fscanf(fp2,"%d%d",&player_mode,&moveforhypocrisy);
        fscanf(fp2,"%d %d",&t_sec_player1,&t_sec_player2);
        for(int ii=7;ii>-1;--ii){
            for(int ij=0;ij<=7;++ij)
                printf("C%d\t",occupy[ij][ii]);
            printf("\n");
        }
        if(player_mode==1)
            iResumeTimer(1);
        else
            iResumeTimer(2);
        fclose(fp2);
        return;
}

//CLOCK ENDS
