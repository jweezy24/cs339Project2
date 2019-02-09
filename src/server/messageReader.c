#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <fnmatch.h>

typedef struct DM{
  char* objects;
  char* user;
}DM;

char* getIP(char* args){
  regex_t re;
  regcomp(&re, "[[0-9]*.[0-9]*.[0-9]*.[0-9]*]", REG_EXTENDED|REG_NOSUB);
  int count = 0;
  int status = -1;
  char buffer[100];
  int bufferPos = 0;
  while(args[count] != '\0'){
    if(args[count] == ','){
      //reseting buffer
      status = regexec(&re, buffer, 0, NULL, 0);
      if (status != 0 || status != -1){
        return buffer;
      }
      bufferPos = 0;
      for(int i =0; i < 100; i++){
        buffer[i] = '\0';
       }
       count+=1;
    }else{
      buffer[bufferPos] = args[count];
      count+=1;
    }

  }
  return "none";
}
//parsing json to readable code for the server boys
void parseJson(char* args){
  regex_t re;
  regcomp(&re, "[[0-9]*.[0-9]*.[0-9]*.[0-9]*,]", REG_EXTENDED|REG_NOSUB);
  int status = regexec(&re, args, 0, NULL, 0);
  if (status != 0){
    printf("%s\n", getIP(args));
  }
  printf("Status: %d", status);
  printf("%s\n", re);
  regfree(&re);

}
