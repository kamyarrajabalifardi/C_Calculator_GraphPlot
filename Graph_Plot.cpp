#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<ctype.h>
char in[100]="0+";
char im[100];
int top=-1,topop=-1;
int tokeni,tokenj;
void pushnum(double x);
double popnum();
void pushop(char x);
char popop();
double stack[100];
char spack[100];
char token[100][100];//for tokenizing
char tokenizemanfi(char im[100]);
char tokenize(char im[100]);
char poken(char im[100]);
void mohasebe();
int olaviat(char x);
int er();
double getinput(double a);
void write_bitmap(char *plot, int width, int height, const char *filename) {
  FILE *f;
  unsigned char *img = NULL;
  int filesize = 54 + 3 * width * height;

  img = (unsigned char *) malloc(3 * width * height);
  memset(img, 0, 3 * width * height);

  for(int i = 0; i < width; i++) {
    for(int j = 0; j < height; j++) {
      int x = i, y = j;
      int r = plot[i * width + j] * 255;
      int g = r;
      int b = r;
      if (x == height / 2 || y == width / 2)  // axis lines
        b = g = 255;
      if (r > 255) r = 255;
      if (g > 255) g = 255;
      if (b > 255) b = 255;
      img[(x + y * width) * 3 + 2] = (unsigned char)(r);
      img[(x + y * width) * 3 + 1] = (unsigned char)(g);
      img[(x + y * width) * 3 + 0] = (unsigned char)(b);
    }
  }

  unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
  unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
  unsigned char bmppad[3] = {0,0,0};

  bmpfileheader[ 2] = (unsigned char)(filesize    );
  bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
  bmpfileheader[ 4] = (unsigned char)(filesize>>16);
  bmpfileheader[ 5] = (unsigned char)(filesize>>24);

  bmpinfoheader[ 4] = (unsigned char)(    width    );
  bmpinfoheader[ 5] = (unsigned char)(    width>> 8);
  bmpinfoheader[ 6] = (unsigned char)(    width>>16);
  bmpinfoheader[ 7] = (unsigned char)(    width>>24);
  bmpinfoheader[ 8] = (unsigned char)(   height    );
  bmpinfoheader[ 9] = (unsigned char)(   height>> 8);
  bmpinfoheader[10] = (unsigned char)(   height>>16);
  bmpinfoheader[11] = (unsigned char)(   height>>24);

  f = fopen(filename, "wb");
  fwrite(bmpfileheader, 1, 14, f);
  fwrite(bmpinfoheader, 1, 40, f);
  for(int i = 0; i < height; i++) {
    fwrite(img + (width * i * 3), 3, width, f);
    fwrite(bmppad, 1, (4 - (width * 3) % 4) % 4, f);
  }

  free(img);
  fclose(f);

}
#define SIZE 1000
int main() {
	int i,count=0;
	
	// S - Getting Expression
	fgets(in+2,100,stdin);
	in[strlen(in)-1]='\0';
	// E - Getting Expression
	
	// S - If Done
	if( (in[0]=='q' || in[0] == 'Q') && (in[1]=='u' || in[1] == 'U') && (in[2]=='i' || in[2] == 'I') && (in[3]=='t' || in[3] == 'T') ){
		printf("project is done");
		return 0;
	}
 	else{//paranthes moadel 
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
//	tokenize(im);
  char plot[SIZE][SIZE] = {0};
  double w = 5.0, step = 2 * w / SIZE;
  for (double x =(-1.0)*w; x < w; x += step) {
    double y =getinput(x); //x * x;
    top=-1;
    int i = (x + w) / step;
    if (i > SIZE - 1) i = SIZE - 1;
    if (i < 0) i = 0;
    int j = (y + w) / step;
    if (j > SIZE - 1 || j < 0) continue;

    plot[i][j] = 1;
  }
  write_bitmap((char *)plot, SIZE, SIZE, "sine.bmp");

  return 0;
}
}
double getinput(double a){
	if(a<0){
	
	tokenizemanfi(im);
	int count=0;
	char mtoken[100][100];
	for(int i=0;i<tokeni;i++){
		strcpy(mtoken[i],token[i]);
	}
	for(int i=0;i<tokeni;i++){
	if(mtoken[i][0]=='x'){
		sprintf(mtoken[i],"%lf",(-1.0)*a);
	}
	}	
	int x,y;// baraye barresie syntax error
	while(count<tokeni){
	if(mtoken[count][0]=='('){
		pushop('(');
		count++;
	}
	
	else if(mtoken[count][0]==')'){
		while(spack[topop]!='('){
			mohasebe();
		}
		popop();
		count++;
	}
	else if(token[count][0]=='c'||token[count][0]=='s'||token[count][0]=='t'||mtoken[count][0]=='+'||mtoken[count][0]=='-'||mtoken[count][0]=='*'||mtoken[count][0]=='/'){
		while((topop!=-1)&&(olaviat(mtoken[count][0])<=olaviat(spack[topop]))&&(top>=1)){
				mohasebe();
		}
		pushop(mtoken[count][0]);
		count++;
	}
	else if(token[count][0]=='c'||token[count][0]=='s'||token[count][0]=='t'||mtoken[count][0]=='+'||mtoken[count][0]=='-'||mtoken[count][0]=='*'||mtoken[count][0]=='/'){
		while((topop!=-1)&&(olaviat(mtoken[count][0])>olaviat(spack[topop]))&&(top>=1)){
		mohasebe();
	}
	count++;
	}
	else {
		double d=strtod(mtoken[count],NULL);
		pushnum(d);
		count++;
	}
}
while(topop!=-1){
	mohasebe();
}
return stack[top];
}
if(a>0){
	tokenize(im);
		int count=0;
	char mtoken[100][100];
	for(int i=0;i<tokeni;i++){
		strcpy(mtoken[i],token[i]);
	}
	for(int i=0;i<tokeni;i++){
	if(mtoken[i][0]=='x'){
		sprintf(mtoken[i],"%lf",a);
	}
	}	
	int x,y;// baraye barresie syntax error
	while(count<tokeni){
	if(mtoken[count][0]=='('){
		pushop('(');
		count++;
	}
	
	else if(mtoken[count][0]==')'){
		while(spack[topop]!='('){
			mohasebe();
		}
		popop();
		count++;
	}
	else if(token[count][0]=='c'||token[count][0]=='s'||token[count][0]=='t'||mtoken[count][0]=='+'||mtoken[count][0]=='-'||mtoken[count][0]=='*'||mtoken[count][0]=='/'){
		while((topop!=-1)&&(olaviat(mtoken[count][0])<=olaviat(spack[topop]))&&(top>=1)){
				mohasebe();
		}
		pushop(mtoken[count][0]);
		count++;
	}
	else if(token[count][0]=='c'||token[count][0]=='s'||token[count][0]=='t'||mtoken[count][0]=='+'||mtoken[count][0]=='-'||mtoken[count][0]=='*'||mtoken[count][0]=='/'){
		while((topop!=-1)&&(olaviat(mtoken[count][0])>olaviat(spack[topop]))&&(top>=1)){
		mohasebe();
	}
	count++;
	}
	else {
		double d=strtod(mtoken[count],NULL);
		pushnum(d);
		count++;
	}
}
while(topop!=-1){
	mohasebe();
}
return stack[top];
}
}
char tokenize(char im[100]){
	tokeni=0,tokenj=0;
	int	i=0;
	while(im[i]!='\0'){
		if(!isdigit(im[i])&&im[i]!='.'&&im[i]!='x'){
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
			tokeni++;
		}
		token[tokeni][tokenj]='\0';
		tokeni++;
		tokenj=0;
	}
	else if(im[i]=='x'){
		token[tokeni][0]=im[i];
		token[tokeni][1]='\0';
		i++;
		tokeni++;
	}	
	}
}
char tokenizemanfi(char im[100]){
	tokeni=0,tokenj=0;
	int	i=0;
	while(im[i]!='\0'){
		if(!isdigit(im[i])&&im[i]!='.'&&im[i]!='x'){
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
			tokeni++;
		}
		token[tokeni][tokenj]='\0';
		tokeni++;
		tokenj=0;
	}
	else if(im[i]=='x'){
		token[tokeni][0]='(';
		tokeni++;
		token[tokeni][0]='0';
		tokeni++;
		token[tokeni][0]='-';
		tokeni++;
		token[tokeni][0]='x';
		tokeni++;
		token[tokeni][0]=')';
		tokeni++;
	//	token[tokeni][0]=im[i];
	//	token[tokeni][1]='\0';
		i++;
	//	tokeni++;
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
    pushnum(n/(m+0.0001)*1.0);
	}
}
}
if(u=='c'||u=='s'||u=='t'){
	double m=popnum();
	if(u=='c'){
	pushnum(1.0*cos(m))	;
	}
	if(u=='s'){
	pushnum(1.0*sin(m))	;
	}
	if(u=='t'){
	pushnum(1.0*tan(m))	;
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
