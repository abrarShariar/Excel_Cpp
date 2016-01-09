#include<iostream>
#include<dirent.h>
#include<cstdio>
#include<fstream>
using namespace std;

//Shows all the subdirectories and files in mentioned location
void showFile(char directory){

   const char *location=".\\customersBills";
    DIR *dir;
    struct dirent *ent;
    int index=0;
    string fileName;

    if ((dir = opendir (location)) != NULL) {
    /* print all the files and directories within directory */
    while ((ent = readdir (dir)) != NULL) {
        if(index!=0 && index!=1){
            fileName=ent->d_name;
        }
        index++;
    }
    closedir (dir);
    } else {
    /* could not open directory */
    perror ("");
    }

    cout<<fileName<<endl;
}

int main(){
    string dir=".\\customersBills";
    showFile(dir);

}

