#include<stdio.h>
#include<stdlib.h>
#include"./vm.h"
#define txtlenmax 400
#define addrspace 32
#define stacksize 32
typedef struct virtualmechine{
    int stack[stacksize][2];//1 single frame. first fun label, second program counter
    int stackpointer;
    unsigned char Reg[8];
    unsigned char Mem[256]; //RAM
    int Fnum;
}VM;
static VM vm;
unsigned char*AddrOf(int t,int v)   //4 data type 
{
    
    
    if(t==0){
        vm.Reg[4]=v; 
        return &(vm.Reg[4]);}
    else if(t==1){
        return &(vm.Reg[v]);}
    else if(t==2){
        return &(vm.Mem[vm.stackpointer*32+v]);}
    else if(t==3){
        return &(vm.Mem[vm.Mem[vm.stackpointer*32+v]]);}
    else{
        return NULL;}
    
}
int work()  //do one line of operation
{
    int i;
    oper curro;
    for(i=0;i<vm.Fnum;i++)
    {
        if(F[i].label==vm.stack[vm.stackpointer][0])        //find function label
        {
            curro=F[i].operation[vm.Reg[7]];            //find current operation
        }
    }
   
    
    if(curro.opcode ==0){ //MOV
        *(AddrOf(curro.type[0],curro.value[0]))=*(AddrOf(curro.type[1],curro.value[1]));
    }
    else if(curro.opcode ==1){//CAL
        vm.stack[vm.stackpointer][1]=vm.Reg[7];
        vm.stackpointer++;
        vm.stack[vm.stackpointer][0]=curro.value[0];
        vm.Reg[7]=-1;
    }
    else if(curro.opcode ==2){//RET
        vm.stackpointer--;
        if(vm.stackpointer==-1)
        {
            return 0;
        }
        vm.Reg[7]=vm.stack[vm.stackpointer][1];
    }
    else if(curro.opcode ==3){//REF
        *(AddrOf(curro.type[0],curro.value[0]))=AddrOf(curro.type[1],curro.value[1])-vm.Mem;
    }
    else if(curro.opcode ==4){//ADD
        vm.Reg[curro.value[0]]=vm.Reg[curro.value[0]]+vm.Reg[curro.value[1]];
    }
    else if(curro.opcode ==5){//PRINT
        printf("%d\n",*(AddrOf(curro.type[0],curro.value[0])));
    }
    else if(curro.opcode ==6){ //NOT
        vm.Reg[curro.value[0]]=~(vm.Reg[curro.value[0]]);
    }
    else if(curro.opcode ==7){ //EQU
        if((vm.Reg[curro.value[0]])==0){
            vm.Reg[curro.value[0]]=1;
        }
        else{
             vm.Reg[curro.value[0]]=0;
        }
        
    }
    else{
        return -1;
    }
    vm.Reg[7]+=1;
    return 0;
}
int main(int argc,char*argv[]){
    int i;
    F=(fun *)malloc(sizeof(fun)*32);
    if(argc==1){
        return 1;                      //check binary input
    }
    FILE *txt=fopen(argv[1],"rb");
    if(txt==NULL)
    {
        return 1;                           //have path but no content
    }
    fseek(txt,0,SEEK_END);
    size_t size=ftell(txt);
    int leftbit=size*8-1;
    unsigned char t[txtlenmax];         // array to store the bits (details in objdump)
    for(i=0;i<size;i++)
    {
        t[i]=0;
    }
    fseek(txt,0,SEEK_SET);
    fread(t,sizeof(unsigned char),size,txt);
    vm.Fnum=getF(t,&leftbit);
    while(vm.stackpointer>=0)
    {
        work();
        if(vm.stackpointer>7)
        {
            return 1;
        }
    }
    free(F);
    fclose(txt);
    return 0;
}