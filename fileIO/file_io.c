/*
 * Authors: Pat McGee & Jordan Laney
 * Class: CSCI446
 * Assignment: Lab5
 * Professor: Hamouda
 *
 * @Brief: This program reads in a file and converts text to uppercase. 
 * 	   It then writes the converted text to a new file.
 *
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

//used to hold input from text
char buffer[256];

//main function read/write
int readWrite(char* filename) {
  int input = open(filename, O_RDONLY); //open file to read
  int output = open("file_io.up", O_WRONLY | O_CREAT, S_IRWXU); //open file to write
  int ret;
  if(input == -1) { //check for error opening read
    perror("open");
    return 1;
  }
  if(output == -1) { //check for error opening write
    perror("open");
    return 1;
  }
  while((ret = read(input, buffer, 256)) > 0) { //while read not return -1
    printf("%s", buffer);
    int i = 0;
    while(buffer[i]) { //ierate c string
      buffer[i] = toupper(buffer[i]); //convert c string to uppercase
      i++;
    }
    write(output, buffer, ret); //write converted to new file
  }	  
  close(input); //close read and write to ensure proper execution
  close(output);
  return 0;
}

int main(int argc, char* argv[])
{
 if(argc < 2) { //check for valid commandline arguments
   printf("Usage: expects argument for one file...\n");
   return 1;
 }
 readWrite(argv[1]); //call readWrite and pass filename
}
