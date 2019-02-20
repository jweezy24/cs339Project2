#include <stdio.h>
#include <stdlib.h>

//Pretty much a copy str method except it filters out unwanted characters from the json parse
char* create_string_attr(char* attr, char* type){
  attr = (char*)malloc(sizeof(char)*strlen(type)+1);
  int count = 0;
  int attrCount = 0;
  while(type[count] != '\0'){
    if (type[count] == '\'' || type[count] == ',' || type[count] == '\"' ){
      count+=1;
    }else{
      attr[attrCount] = type[count];
      type+=1;
      attrCount+=1;
    }
  }
  return attr;
}

/*
 * error - wrapper for perror
 */
void error(char *msg) {
  perror(msg);
  exit(1);
}

void no_exit_error(char* msg){
  printf("%s\n",msg);
  printf("\n");
}

void timeout(){
  printf("Timeout occured.\n");
}
