#include "lnode.h"
#include <stdio.h>
#include <ctype.h>

int normalize(char *w);
int isGreater(char * s1, char *s2);
lnode insertWord(char * word, lnode head);

int main(int argc, char **argv) {

	lnode head=NULL;
	char word[1024];
	while(!feof(stdin)) {
		if (1== scanf("%s",word)) { // If we can read another white space terminated string
			if (normalize(word)) { // And if that string is non-empty after normalization...
				head=insertWord(word,head);
				printf ("Read word %s\n",word);
			}
		}
	}

	lnode node;
	int i=1;
	for(node=head; node; node=getNextLnode(node)) {
		printf("%3d. - %3d - %s\n",i++,getLnodeCount(node),getLnodeValue(node));
	}

	lnode next;
	for(node=head; node; node=next) {
			next=getNextLnode(node);
			deleteLnode(node);
	}
	return 0;
}

int normalize(char *r) {
	int ret=0;
	char *w=r;
	while(*r) {
		if (!isalpha((int)*r)) { r++; continue; }
		(*w++)=tolower((int)*r++);
		ret=1;
	}
	(*w)=0;
	return ret;
}

lnode insertWord(char * word, lnode head) {
	lnode current;
	current = makeLnode(word);
	lnode prev;
	prev = head;
	if(!head){
		head = makeLnode(word);
		word++;
	}
	
	else if(isGreater(getLnodeValue(head),word)== 0){
		addLnodeCount(head);
		head = makeLnode(word++);
	}
	
	else if(isGreater(getLnodeValue(head),word) <0){
		head = current;
		setNextLnode(head,prev);
		//printf("%c",*word);
		//
	}
	
	else{
		if(getNextLnode(head)){
			if(isGreater(getLnodeValue(getNextLnode(head)),word) == 0){
				addLnodeCount(getNextLnode(head));
				head = makeLnode(word++);
			}
			else if(isGreater(getLnodeValue(getNextLnode(head)),word) <0){
				insertWord(word++,getNextLnode(head));
			}
		}
		else{
			setNextLnode(head,current);
			//printf("set next");
		}
			
	}
	//deleteLnode(current);
	return head;
}

int isGreater(char *s1,char *s2) {
	while(*s1) {
		if ((*s1)>(*s2)) return 1;
		if ((*s1)<(*s2)) return -1;
		s1++; s2++;
	}
	if ((*s2)==0) return 0;
	return -1;
}