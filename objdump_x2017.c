#include<stdio.h>
#include<stdlib.h>
#include"./vm.h"
#define txtlenmax 400
#define addrspace 32
int showF(int Fnum)
{
    while(Fnum-->0)
    {
        char *types[]={"VAL","REG","STK","PTR"};   
        char *insts[]={"MOV","CAL","RET","REF","ADD","PRINT","NOT","EQU"};
        printf("FUNC LABEL %d\n",F[Fnum].label);
        int opN=0;
        int occupid[addrspace];
        int alpha[addrspace]; //store the A-Z-a-u
        int j;
        for(j=0;j<addrspace;j++)
        {
            occupid[j]=-1;
            if(j<26)
            {
                alpha[j]='A'+j;
            }
            else
            {
                alpha[j]='a'+j-26;
            }
        }
        while(opN<F[Fnum].count)
        {
            int currcode=F[Fnum].operation[opN].opcode;
            printf("    %s",insts[currcode]);
            int valnum=2;
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
                printf(" %s",types[F[Fnum].operation[opN].type[i]]);
                if(F[Fnum].operation[opN].type[i]>1)
                {
                    int k;
                    for(k=0;k<addrspace;k++)
                    {
                        if(occupid[k]==F[Fnum].operation[opN].value[i])
                        {
                            printf(" %c",alpha[k]);
                            break;
                        }
                        else if(occupid[k]==-1)
                        {
                            occupid[k]=F[Fnum].operation[opN].value[i];
                            printf(" %c",alpha[k]);
                            break;
                        }
                    }
                }
                else
                {
                    printf(" %d",F[Fnum].operation[opN].value[i]);
                }
            }
            printf("\n");
            opN++;
        }
    }
    return 0;
}
int main(int argc,char*argv[])
{
    int i;
    F = (fun*)malloc(sizeof(fun)*32);
    FILE *txt=fopen(argv[1],"rb");    //read the file
    if(txt==NULL)
    {
        return -1;                     //file empty
    }
    //printf("%d",argv[1]);
    fseek(txt,0,SEEK_END);      //get cursor to the end
    size_t size=ftell(txt);     // from that cursor to the start
    int leftbit=size*8-1;           // how many bits in total
    unsigned char t[txtlenmax];    // array to store the bits 
    for(i=0;i<size;i++)
    {
        t[i]=0;
    }
    fseek(txt,0,SEEK_SET);
    fread(t,sizeof(unsigned char),size,txt);
    showF(getF(t,&leftbit));     
    fclose(txt);
    free(F);
    return 0;
}