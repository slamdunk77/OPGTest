#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char str[1010],stack[1010];
char str_c,stack_c,input_c;
int dex,stack_p,str_p,stack_p1,a,b;
FILE *fp;
// -1表示小于等于 0表示不可比较 1表示大于 
int table[6][6]={
	{1,-1,-1,-1,1,1},
	{1,1,-1,-1,1,1},
	{1,1,0,0,1,1},
	{-1,-1,-1,-1,-1,0},
	{1,1,0,0,1,1},
	{-1,-1,-1,-1,0,0}
};

void push(char str_c){
	stack[stack_p++]=str_c;
}

void pop(){
	stack_p--;
}
char get_stack1(){
	char c;
	stack_p1=stack_p-1;
	do{
		c=stack[stack_p1--];
	}while(c=='N');
	return c;
}

char get_stack2(){
	char c;
	stack_p1=stack_p-1;
	c=stack[stack_p1];
	return c;
}

int f_int(char str_c){
	int t;
	if(str_c=='+')
		t=0;
	else if(str_c=='*')
		t=1;
	else if(str_c=='(')
		t=2;
	else if(str_c==')')
		t=3;
	else if(str_c=='i')
		t=4;
	else if(str_c=='#')
		t=5;
	else t=-1;
	return t;
}

void init_(){
	stack[0]='#';
	stack_p=1;
	str_p=0;
	dex=0;
	stack_c=get_stack1();
	str_c=str[str_p];
}

void analyse(){
	while(stack_c!='#'||str_c!='#'){
		a=f_int(stack_c);
		b=f_int(str_c);
		if(a==-1||b==-1){
			printf("E\n");
			return;
		}
		
		if(table[a][b]==-1){// 推进 
			push(str_c);
			str_p++;
			printf("I%c\n",str_c);
		}
		else if(table[a][b]==1){// 规约 
			int m,i;
			stack_c=get_stack2();
			if(stack_c=='i')
				pop();
			else if(stack_c=='*' || stack_c=='+'){
				printf("RE\n");
				return;
			}
			else{
				pop();pop();pop();
			}
			push('N');
			printf("R\n");
		}
		else{
			dex=-1;
			break;
		}
		stack_c=get_stack1();
		str_c=str[str_p];
	}
}

void get_str(){
	// 读入句子到prog
	int zi=0;
	do{
		input_c=fgetc(fp);//fgetc(fp)
		str[zi]=input_c;
		zi++;
	}while(input_c!='\r'&&str[zi-1]!='\n');
	str[zi-1]='#';
}

void scaner(char str_c1){
	dex=1;
	if(str_c1=='#') dex=0;
	else if(str_c1!='+'&&str_c1!='*'&&str_c1!='('&&str_c1!=')'&&str_c1!='i') dex=-1;
}


int main(int argc, char *argv[]){
	//读入句子到prog，并以 # 结尾
	fp = fopen(argv[1], "r");
	get_str();
	if(dex==0){
		//初始化 
		init_();
		//opg
		analyse();
		if(dex!=0) {
			printf("E\n");
			return 0;
		}
	} 
	
} 




