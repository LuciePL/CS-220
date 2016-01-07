#include "base64.h"
#include <stdio.h>
#include <assert.h>

char * b64encode(char string[],int len);
static char b64Result[MAX_MSG_LENGTH];

int main(int argc, char **argv) {
	char inputMsg[MAX_MSG_LENGTH] = "";
	int stri=0;
	char in;
	while(1) {
		in=getchar();
		if (feof(stdin)) break;
		inputMsg[stri++]=in;
	}
	inputMsg[stri]=0;
	assert(stri<MAX_MSG_LENGTH);

	char * result=b64encode(inputMsg,stri);
	int b64i=0;
	for(b64i=0; result[b64i]; b64i++) {
		putchar(result[b64i]);
	}
	return 0;
}

char * b64encode(char string[],int len) {
	int i =0;
	int charNum = 1;
	int count = 0;
	long holding = 0;
	int held = 0;
	int origCharNum = 0;
	int j =0;
	for(i = 0; i < len; i++){
		holding = holding + string[i];
		 if((i == len-1)&& (charNum == 2)){
			holding = holding << 8;
			origCharNum = 2;
			charNum = 3;
		}
		else if((i == len-1)&& (charNum== 1)){
			holding = holding << 16;
			origCharNum = 1;
			charNum = 3;
		}
		if(charNum ==3){
			//printf("%d \n",origCharNum);
			for(j = 0; j<4; j++){
				held = holding & 0xfc0000;
				holding = holding << 6;
				held = held >>18;
				b64Result[count]= base64[held];
				if((origCharNum == 2) && j ==3){
					b64Result[count] = base64Pad;
				}
				else if(origCharNum == 1 && j >=2){
					b64Result[count] = base64Pad;
				}
				count++;
			}
			charNum = 1;
			holding = 0;
			origCharNum ==0;
		}
		
		else{
		holding = holding<<8;
		charNum++;
		}
		
	}

	b64Result[count]=0; // Make sure result is null terminated
	return b64Result;
	
}
