#include "base64.h"
#include <stdio.h>
#include <assert.h>

char * b64decode(char b64[],int len);
static char stringResult[MAX_MSG_LENGTH];

int main(int argc, char **argv) {
	char inputMsg[MAX_MSG_LENGTH] = "";
	int b64i=0;
	char in;
	while(1) {
		in=getchar();
		if (feof(stdin)) break;
		inputMsg[b64i++]=in;
	}
	assert(b64i<MAX_MSG_LENGTH);

	char * result=b64decode(inputMsg,b64i);
	int stri=0;
	for(stri=0; result[stri]; stri++) {
		putchar(result[stri]);
	}
	return 0;
}

char * b64decode(char b64[],int len) {
	int i =0;
	int charNum = 1;
	int count = 0;
	long holding = 0;
	long held = 0;
	char held2;
	int origCharNum = 1;
	int j =0;
	for(i = 0; i < len; i++){
		if(b64Index(b64[i]) != 64){
			holding = holding + b64Index(b64[i]);
	}
		if(charNum ==4){
			for(j = 0; j<3; j++){
				held = holding & 0xff0000;
				holding = holding << 8;
				held = held >>16;
				stringResult[count]= held;
				count++;
			}
			charNum = 1;
			holding = 0;
		}
		
		else{
		holding = holding<<6;
		charNum++;
		}
	}
		
	stringResult[count]=0; // Make sure result is null terminated
	return stringResult;
}
