#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
// S - Values
int top=-1,topop=-1;
int tokeni,tokenj;
// E - Values 
// S - Functions and Arrays
void pushnum(double x);
double popnum();
void pushop(char x);
char popop();
double stack[100];
char spack[100];
char token[100][100];//for tokenizing
char tokenize(char im[100]);
char poken(char im[100]);
void mohasebe();
int olaviat(char x);
int er();
double power(double base,double exponent);
// E - Funcions
//int nearop(char token[100][100]);
int main(){
	int i,count=0;
	char in[100]="0+";
	char im[100];
	printf("Expressions will be calculated by this program!!\ntype %s to exit\n","quit");
	
	while(1){
		
	// S - Getting Expression
	fgets(in+2,100,stdin);
	in[strlen(in)-1]='\0';
	// E - Getting Expression
	
	// S - If Done
	if( (in[0]=='q' || in[0] == 'Q') && (in[1]=='u' || in[1] == 'U') && (in[2]=='i' || in[2] == 'I') && (in[3]=='t' || in[3] == 'T') ){
		printf("project is done");
		return 0;
	}
 	else{
 	// S - LenGet
		int imlen=0;
	for(i=0;in[i]!='\0';i++){
        if(in[i]!=' '){
            im[imlen]=in[i];
            imlen++;
        }
        
	}
	// E - LenGet
	
	im[imlen]='\0';
	tokenize(im);
	int x,y;// baraye barresie syntax error
	if(token[0][0]=='+'||token[0][0]=='/'||token[0][0]=='*'||token[0][0]=='-'){
		printf("Syntax error!!\nNext time Enter a correct expression");
		return 0;
	}
	if(!er()){
	printf("Syntax error!!\nNext time Enter a correct expression");
	return 0;
	}
	while(count<tokeni){
	if(token[count][0]=='('){
		pushop('(');
		count++;
	}
	
	else if(token[count][0]==')'){
		while(spack[topop]!='('){
			mohasebe();
		}
		popop();
		count++;
	}
	else if(token[count][0]=='c'||token[count][0]=='s'||token[count][0]=='t'||token[count][0]=='+'||token[count][0]=='-'||token[count][0]=='*'||token[count][0]=='/'||token[count][0]=='^'){
		while((topop!=-1)&&(olaviat(token[count][0])<=olaviat(spack[topop]))&&(top>=1)){
				mohasebe();
		}
		pushop(token[count][0]);
		count++;
	}
	else if(token[count][0]=='c'||token[count][0]=='s'||token[count][0]=='t'||token[count][0]=='+'||token[count][0]=='-'||token[count][0]=='*'||token[count][0]=='/'||token[count][0]=='^'){
		while((topop!=-1)&&(olaviat(token[count][0])>olaviat(spack[topop]))&&(top>=1)){
		mohasebe();
	}
	count++;
	}
	else {
		double d=strtod(token[count],NULL);
		pushnum(d);
		count++;
	}
}
while(topop!=-1){
	mohasebe();
}
printf("%lf\n",stack[top]);
}
count=0;
}
}
char tokenize(char im[100]){
	tokeni=0,tokenj=0;
	int	i=0;
	while(im[i]!='\0'){
		if(!isdigit(im[i])&&im[i]!='.'){
			if(im[i]=='c'||im[i]=='s'||im[i]=='t'){
			token[tokeni][0]=im[i];
			token[tokeni][1]='\0';
			tokeni++;
			i++;
			i++;
			i++;
			}
			else {
			
			token[tokeni][0]=im[i];
			token[tokeni][1]='\0';
			i++;
			tokeni++;
		}
	}
	else if(isdigit(im[i])){
			token[tokeni][0]=im[i];
			i++;
			tokenj=1;
			while(isdigit(im[i])||im[i]=='.'){
				token[tokeni][tokenj]=im[i];
				tokenj++;
				i++;
			}
			token[tokeni][tokenj]='\0';
			tokeni++;
			tokenj=0;	
		}
	else if(im[i]=='.'){
		token[tokeni][0]=im[i];
			i++;
			tokenj=1;
		while(isdigit(im[i])){
			token[tokeni][tokenj]=im[i];
			i++;
			tokenj++;
		}
		token[tokeni][tokenj]='\0';
		tokeni++;
		tokenj=0;
	}	
	}
}
void pushop(char x){
	spack[++topop]=x;
}
char popop(){
	return spack[topop--];
}
void pushnum(double x){
	stack[++top]=x;
}
double popnum(){
	return stack[top--];
}
void mohasebe(){
	
	if(top>=1){
	char u=popop();
	if(u!='c'&&u!='s'&&u!='t'&&u!='o'){
	
	double m=popnum();
	double n=popnum();
	
	if(u=='+'){
		pushnum(m+n+0.0);
	}
	if(u=='-'){
		pushnum(n-m+0.0);
	}
	if(u=='*'){
		pushnum(n*m*1.0);
	}
	if(u=='/'){
		if(m!=0){
		pushnum(n/m*1.0);
	}
/*	if(u=='^'){
		pushnum(power(n,m)*1.0);
	}*/ 
	else {
	printf("Syntax error!\ndivided by zero is not defined!");
	exit(0);
	}
}
}
if(u=='c'||u=='s'||u=='t'){
	double m=popnum();
	if(u=='c'){
	pushnum(1.0*cos(m*0.01745329251994))	;
	}
	if(u=='s'){
	pushnum(1.0*sin(m*0.01745329251994))	;
	}
	if(u=='t'){
	pushnum(1.0*tan(m*0.01745329251994))	;
	}
}
else return;
}
}
int olaviat(char x){
	if(x=='c'||x=='s'||x=='t')
	return 3;
	if(x=='^') return 3;
	if(x=='('||x==')'){return 0;
	}
	if(x=='*'||x=='/'){return 2;
	}
	if(x=='+'||x=='-'){return 1;
	}
}
int er(){
	int i,flag=1;
	for(i=0;i<tokeni-1;i++){
		if((token[i][0]=='/'||token[i][0]=='*'||token[i][0]=='-'||token[i][0]=='+')&&(token[i+1][0]=='/'||token[i+1][0]=='*'||token[i+1][0]=='-'||token[i+1][0]=='+')){
			flag=0;
			break;
		}
		if(token[i][0]=='('&&((token[i+1][0]=='/'||token[i+1][0]=='*'||token[i+1][0]=='-'||token[i+1][0]=='+')||token[i+1][0]==')')){
			flag=0;
			break;
		}
	}
	if(flag==0){return 0;
	}
	else return 1;
}
double power(double base,double exponent){
	return exp(exponent*log(base));
}
