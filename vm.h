typedef struct operation{
    unsigned char opcode;
    unsigned char type[2];
    unsigned char value[2];
}oper;
typedef struct function{
    unsigned char count;
    unsigned char label;
    oper operation[32];
}fun;
//fun F[32];
static fun* F;
unsigned char getbit(int bitN,unsigned char*text,int *currbit)
{
    unsigned char N=0;
    int i=0;
    while(i<bitN)
    {
        int and=(1<<(7-(*currbit)%8))&(text[(*currbit)/8]);
        if(and==0){
            N+=0;
        }
        else{
            N+=1<<i;
        }
        
        i++;
        *(currbit)=*(currbit)-1;
    }
    return N;
}
int judgebit(unsigned char type)
{
    if(type>1)
    {
        return 5;
    }
    else if( type==0)
    {
        return 8;
        
    }
    else{
        return 3;
    }
}
int getF(unsigned char*txt,int *currbit)
{
    int Findex=0;
    while((*currbit)>7)
    {
        F[Findex].count=getbit(5,txt,currbit);   //how many operation
        int opindex=0;
        while(opindex<F[Findex].count)
        {
            F[Findex].operation[F[Findex].count-opindex-1].opcode=getbit(3,txt,currbit); //last line of operation
            int currcode=F[Findex].operation[F[Findex].count-opindex-1].opcode;
            int valnum=0;
            if(currcode==0||currcode==3||currcode==4)
            {
                valnum=2;
            }
            else if(currcode==1||currcode==5||currcode==6||currcode==7)
            {
                valnum=1;
            }
            else if(currcode==2)
            {
                valnum=0;
            }
            int i;
            for(i=0;i<valnum;i++)
            {
                F[Findex].operation[F[Findex].count-opindex-1].type[i]=getbit(2,txt,currbit);
                F[Findex].operation[F[Findex].count-opindex-1].value[i]=getbit(judgebit(F[Findex].operation[F[Findex].count-opindex-1].type[i]),txt,currbit);
            }
            opindex++;
        }
        F[Findex].label=getbit(3,txt,currbit);
        Findex++;
    }
    return Findex;
}