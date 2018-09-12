//name:Eric Rogers
//email:ejr140230@utdallas.edu
//course number:CS3376.001

#include<iostream>
#include<sstream>
#include<cstdio>
#include<stdio.h>
#include<stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

bool is_modole_exist(string modole_name){   // Chack if modole_name exist in /usr/bin
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("/usr/bin")) != NULL) {
      while ((ent = readdir (dir)) != NULL) {
        if (modole_name ==  string(ent->d_name)){
            return true;
        }
      }
      closedir (dir);
    }
    return false;
}

int main(int argc, char* argv[])
{
  if (!is_modole_exist("gawk")){    // If gawk not installd exit program
    cout << "gawk is missing" << endl;
    cout << "sudo apt install gawk" << endl;
    return 1;
  }
  
  stringstream value; //used to store the output of the gawk program

  int num1; //the first number produced by the gawk program, sum of column 1
  int num2; //the second number produced by the gawk program, sum of column 2

  cout << "gawk at: /usr/bin/gawk" << endl;
  cout << "Shellcmd1: /usr/bin/gawk --version" << endl;
  cout << "Shellcmd2: /usr/bin/gawk -f gawk.code numbers.txt" << "\n\n";

  FILE *fp = popen("/usr/bin/gawk --version", "r"); //popen returns pointer to an open stream that can be read or wrote to based on the second parameter, the first
                                                                            //is a string that is executed on the command line
  char buff[BUFSIZ]; //buffer for our stream(fp) used when reading from stream

  while((fgets(buff, BUFSIZ, fp)) != NULL) //loop and get all of the lines from the output of our popen(command in shell) save in buff
  {
    value << buff; //append each line onto the stringstream value
  }

  cout << "The first call to gawk returned: " << "\n\n" << value.str() << endl; //print to screen all output from first shell command

  value.str(""); //set string in stringstream to an empty string
  value.clear(); //clear other data ossociated with the stream

  fp = popen("/usr/bin/gawk -f gawk.code numbers.txt", "r"); //run second command(our gawk program) on the command line and store the output
  while((fgets(buff, BUFSIZ, fp)) != NULL) //loop and get all of the lines from the output of our popen(command in shell) save in buff

  {
    value << buff; //append each line onto the stringstream value
  }

  string hold = value.str(); //used to hold the stringstream value as a string
  cout << "The second call to gawk returned: " << hold << endl;

  string token; //stores the tokens(numbers) for conversion to int
  int spaceLocation = hold.find(" "); //holds the location of the space seperating our two numbers

  token = hold.substr(0, spaceLocation); //substring of the first number
  num1 = atoi(token.c_str()); //convert the first number to an int and store

  token = hold.substr(spaceLocation, hold.size()); //substring of the second number
  num2 = atoi(token.c_str()); //convert the second number to an int and store

  cout << "The sum of column 1 is: " << num1 << endl << "The sum of column 4 is: " << num2 << endl;
  cout << "The sum of the two numbers is: " << (num1+num2) << endl;

  pclose(fp); //close the stream

  return 0;
}

