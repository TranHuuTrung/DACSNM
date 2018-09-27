#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1024*10
#define MAX 100

//STACK
typedef struct stack_t {
	char elements[MAX];
	int top;
} stack;

int isEmpty(stack S) {
	return S.top <= -1;
}

int isFull(stack S){
	return S.top >= MAX-1;
}
//create stack
void create(stack *S) {
	S->top = -1;
}

void push(stack *S, char a){
	if(!isFull(*S)){
		S->elements[++S->top] = a;
	}
}

char pop(stack *S){
	if(!isEmpty(*S)){
		return S->elements[S->top--];
	}
	return 0;
}

char peek(stack *S){
	if (!isEmpty(*S)){
		return S->elements[S->top];
	}
	return 0;
}

void print(stack S) {
	int i;
	for (int i = 0; i <= S.top; ++i){
		printf("%c", S.elements[i]);
	}
}

//END STACK

//KIEM TRA THU TU UU TIEN TOAN TU
int checkUuTien(char a){
	if(a == '-' || a == '+'){
		return 0;
	}
	if(a == '/' || a == '*'){
		return 1;
	}
}

//check so
int checkSo(char a) {
	if((a >= '0' && a <= '9') || a == '.') {
		return 1;
	}
	return 0;
}

//check toan tu
int checkToanTu(char ch){
	if(ch == '+' || ch == '-' || ch == '/' || ch == '*'){
		return 1;
	}
	return 0;
}

int toanhang(char a){
	if(a >= 48 && a <= 57){
		return 1;
	}
	return 0;
}

//CHUYEN BIEU THUC TRUNG TO THANH BIEU THUC HAU TO

int InfixToPostfix(char infix[], char postfix[]) {
	stack st;
	create(&st);
	int dem = 0;
	for (int i = 0; i < strlen(infix); i++){
		if(checkToanTu(infix[i]) && checkToanTu(infix[i+1])) return 0; // check du lieu dau vao
		if((infix[i] >= 97 && infix[i] < 122) || (infix[i] >= 65 && infix[i] < 90)) return 0;
	}
	for (int i = 0; i < strlen(infix); i++){
		char token = infix[i];
		if(checkSo(token)) {
			postfix[dem++] = token;
			if(checkToanTu(infix[i+1])){
				postfix[dem++] = ' '; // phan biet so co nhieu chu so
			}
		}
		if(token == '(') {
			push(&st, token);
		}
		if(checkToanTu(token)){
			if (!isEmpty(st)){
				if((checkToanTu(peek(&st))) && (checkUuTien(token) == checkUuTien(peek(&st)) || checkUuTien(token) < checkUuTien(peek(&st)))) {
					//neu toan tu hien tai co do uu tien nho hon toan tu o dinh stack
					char ch;
					ch = pop(&st);
					//lay toan tu do ra, dong thoi day toan tu hien tai vao
					postfix[dem++] = ch;
					push(&st, token);
				} else {
					push(&st, token);
				}
			} else {
				push(&st, token);
			}
		}
		if(token == ')'){
			char c;
			//pop cho den khi gap dau (
			while(1){
				c = pop(&st);
			}
			if(c == '(') break;
			postfix[dem++] = c;
		}

	}

	//neu doc het token ma trong stack con thi lay ra het theo thu tu
	while(!isEmpty(st)) {
		char lt;
		lt = pop(&st);
		postfix[dem++] = lt;
	}

	postfix[dem] = '\0';
}

//change format number
int formatToNumber(char token) {
	switch(token){
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		case '0': return 0;
	}
}


// change string to number
float changeStringToNumber(char ch[]){
	float d = 0;
	int n = strlen(ch);
	if(strlen(ch)) {
		for (int i = 0; i < n; i++){
			if(ch[i] == '.'){
				int dem = 1;
				float bd1 = 1, bd= 0;
				for (int j = i+1; i < n; j++){
					for(int k = 0; k < dem; k++){
						bd1 = bd1 *10;
					}
					bd = bd + formatToNumber(ch[j]) / bd1;
				}
				d = d + bd;
				break;
			} else {
				d = d *10 + formatToNumber(ch[i]);
			}
		}
		return d;
	}
	return 0;
}

//TINH GIA TRI BIEU THUC HAU TO

float CalculatePostfix(char pos[SIZE]) {
	char ch ='\0';
	int dem1 = 0;
	float data[1000000]; //chua gia trij moi khi doc token la so hay ket qua tinh toan
	char postfix[10000];

	InfixToPostfix(pos, postfix);
	pos = postfix;
	int n = strlen(pos);
	for (int i = 0; i < n; ++i){
	 	char b[100];
	 	int dem = 0;
	 	while(pos[i] != ' ' && i < n && !checkToanTu(pos[i])){
	 		b[dem++] = pos[i++];
	 	}
	 	if (dem){
	 		b[dem] = '\0';
	 		data[dem1++] = changeStringToNumber(b);
	 	}
	 	if (checkToanTu(pos[i])){
	 		switch(pos[i]){
	 			case '+':
	 				{
	 					float temp = data[dem1 - 2] + data[dem1 - 1];
	 	 				data[dem1 - 2] = temp;
	 					dem1 --;
	 				}
	 				break;
	 			case '-':
	 				{
	 					float temp = data[dem1 - 2] - data[dem1 - 1];
		 				data[dem1 - 2] = temp;
		 				dem1 --;
	 				}
	 				break;
	 			case '*':
	 				{
	 					float temp = data[dem1 - 2] * data[dem1 - 1];
	 					data[dem1 - 2] = temp;
	 					dem1 --;
	 				}
	 				break;
	 			case '/':
	 				{
	 					float temp = data[dem1 - 2] / data[dem1 - 1];
	 					data[dem1 - 2] = temp;
	 					dem1 --;
	 				}
	 				break;
	 		}
	 	}
	 	i++;
	}
	return data[0];
}

void reader(FILE * stream){
	char buffer[SIZE];
	if(!feof(stream) && !ferror(stream) && fgets(buffer, sizeof(buffer), stream) != NULL){
		fputs(buffer, stdout);
	} else {
		fputs("Something when wrong(ex: Invalid expression,..\n", stdout);
	}
}

int main(){
	int fds_1[2]; //pipe1 (result)
	int fds_2[2]; //pipe2 (intputString)

	pid_t pid;
	pipe(fds_1);
	pipe(fds_2);

	// 0: read, 1: write
	/**
	fds_1[0] : Cha doc
	fds_1[1] : Con ghi
	fds_2[1] : Cha ghi
	fds_2[0] : Con doc
	*/

	pid = fork(); //tach tien trinh
	if (pid == (pid_t) 0){
		/*tien trinh Con*/
		sleep(1);
		FILE* stream;
		close(fds_2[1]); // dong Cha ghi inputString
		stream = fdopen(fds_2[0], "r");
		char buffer[SIZE];
		fgets(buffer, sizeof(buffer), stream);
		if (sizeof(buffer)> 0){
			printf("\n%s\n","------ START TIEN TRINH CON -------" );
		}
		char strReceived[SIZE];
		char result[SIZE] = "Ket qua: ";
		char tmpStr[SIZE];

		//doc inputString tu cha
		sscanf(buffer, "%s", &strReceived); //sscanf: input da duoc dinh dang string
		printf("Tien trinh con nhan chuoi sau: %s \n", strReceived);
		close(fds_2[0]);
		printf("%s\n", "Dang tinh toan ...");

		sprintf(tmpStr, "%3.3f", CalculatePostfix(strReceived));
		strcat(result, tmpStr); //them ket qua vao sau chuoi -> in ra ketqua cuoi cung

		printf("%s\n", "Tinh toan xong!");
		printf("%s\n", "Gui ket qua cho tien trinh CHA ...");

		//gui ketqua cho Cha
		close(fds_1[0]);
		stream = fdopen(fds_1[1], "w");
		fprintf(stream, "%s\n", result);
		fflush(stream);
		printf("%s\n", "------ KET THUC TIEN TRINH CON ---------" );
		close(fds_1[1]);
	}else {
		/*Tien trinh Cha*/
		FILE* stream;
		close(fds_2[0]); //dong Con doc inputString
		stream = fdopen(fds_2[1], "w");
		//inputString ghi de tien trinh CON tinh toan
		printf("%s\n","============== START TIEN TRINH CHA ===============" );
		char inputString[SIZE];
		printf("\nNhap bieu thuc tinh: ");
		fflush(stdin);
		gets(inputString); // doc chuoi tu stdin
		printf("Gui bieu thuc str = %s cho tien trinh CON tinh toan. \n", inputString);
		fprintf(stream, "%s\n", inputString);
		fflush(stream);
		close(fds_2[1]);
		sleep(1);

		// Nhan ket qua tinh toan tu tien trinh CON
		close(fds_1[1]);
		stream = fdopen(fds_1[0], "r");
		printf("\n%s\n", "Tien trinh CHA nhan ket qua tu tien trinh CON");
		reader(stream);
		printf("%s\n","================= KET THUC TIEN TRINH CHA =============" );
		close(fds_1[0]);
	}
	return 0;
}
