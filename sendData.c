// C library headers
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

struct App
{
    char* name;
    char* version;
};

int getFileSize();
struct App* getApps(int length);
void printApps(struct App apps[], int size);

int main()
{
  int noOfLines = getFileSize();
  
  struct App* apps = getApps(noOfLines);   
  
  printApps(apps,noOfLines);
  
  free(apps);
  
  return 0;
}


int getFileSize(){
  FILE *fp = fopen("tr300.txt", "r");
  char *line = NULL;    
  size_t len = 0;
  ssize_t read1;
  int noOfLines = 0;

  if (fp == NULL)
    exit(EXIT_FAILURE);

  while ((read1 = getline(&line, &len, fp)) != -1) {
	  noOfLines++;
  }

  return noOfLines;
}

struct App* getApps(int length){
  FILE *fp1 = fopen("tr300.txt", "r");
  struct App* apps = malloc(sizeof(struct App) * length); 
  char buf[1000];
  
  int counter = 0;
  while(fgets(buf,1000, fp1)!= NULL){
    char* n = strtok(buf,": ");
    char* v = strtok(NULL,": ");
    apps[counter].name = strdup(n);
    apps[counter].version = strdup(v); 
    counter++;
  }
  
  return apps;
}

void printApps(struct App apps[], int size) {
    for (unsigned i = 0; i <size ; ++i) {
        printf("%s  %s\n", apps[i].name, apps[i].version);
    }
}

