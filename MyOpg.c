#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char zhongjian[1010],zhan[1010];
char ch,zh,input_c;
int syn,p,q,a,b,c,d,z,j;
FILE *fp;
int table[6][6]={
	{1,-1,-1,-1,1,1},
	{1,1,-1,-1,1,1},
	{1,1,0,0,1,1},
	{-1,-1,-1,-1,-1,0},
	{1,1,0,0,1,1},
	{-1,-1,-1,-1,0,0}
};

void push(char ch){
	zhan[z++]=ch;
}

void pop(){
	z--;
}
char ding(){
	char a;
	q=z-1;
	do{
		a=zhan[q--];
	}while(a=='N');
	return a;
}

char ding2(){
	char a;
	q=z-1;
	a=zhan[q];
	return a;
}

int findint(char ch){
	int t;
	switch(ch){
		case '+':t=0;break;
		case '*':t=1;break;
		case 'i':t=2;break;
		case '(':t=3;break;
		case ')':t=4;break;
		case '#':t=5;break;
//		default:syn=-1;break;
	}
	return t;
}

void chu(){
	zhan[0]='#';
	z=1;
	c=0;
	j=0;
	syn=0;
	zh=ding();
	ch=zhongjian[j];
}

void analyse(){
	while(zh!='#'||ch!='#'){
		a=findint(zh);
		b=findint(ch);
		if(a==-1||b==-1){
//			printf("E\n");
			return;
		}
		
		if(table[a][b]==-1){// 推进 
			push(ch);
			j++;
			printf("I%c\n",ch);
		}
		else if(table[a][b]==1){// 规约 
			int m,i;
			zh=ding2();
			if(zh=='i')
				pop();
			else if(zh=='*' || zh=='+'){
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
			syn=-1;
			break;
		}
		zh=ding();
		ch=zhongjian[j];
	}
}

void loadch(){
	// 读入句子到prog，并以 # 结尾 
//	scanf("%s",zhongjian);
//	zhongjian[strlen(zhongjian)]='#';
	int zi=0;
	do{
		input_c=fgetc(fp);//fgetc(fp)
		zhongjian[zi]=input_c;
		zi++;
	}while(input_c!='\r'&&zhongjian[zi-1]!='\n');
	zhongjian[zi-1]='#';
}

void scaner(){
	syn=1;
	ch=zhongjian[p++];
	switch(ch){
		case '+':
		case '*':
		case '(':
		case ')':
		case 'i':break;
		case '#':syn=0;break;
		// 若输入其他字符 
		default:syn=-1;break;
	} 
}

void saomiao(){
	p=0;
	q=0;
	do{
		scaner();
		if(syn==-1){
			printf("E\n");
			break; 
		} 
		//当读到末尾 # 时，使用syn标记，syn=0 
	}while(syn!=0);
	
}

int main(int argc, char *argv[]){
	//读入句子到prog，并以 # 结尾
	fp = fopen(argv[1], "r");
	loadch();
	
	//查看输入的句子中的字符是否合法，并把去掉空格的句子存入zhongjian[] 
	saomiao();
	
	//若读入的句子合法且完整 
	if(syn==0){
		//初始化 
		chu();
		//opg
		analyse();
		
		if(syn!=0) {
			printf("E\n");
			return 0;
		}
	} 
	
} 




