#include<iostream>
#include<fstream>
#include<windows.h>
#include<vector>
using namespace std;


LPCTSTR getCustomerName(){
    vector<string> customerName;
    string fileName="customers.csv";
    ifstream read;
    read.open(fileName);
    while(read.good()){
        string name;
        getline(read,name);
        customerName.push_back(name);
    }
    string nameString="";
    for(int i=0;i<customerName.size();i++){
        nameString=nameString+"\n"+customerName[i];
    }
    LPCTSTR nameData=nameString.c_str();

    return nameData;
}

/*
int main(){
    cout<<getCustomerName()<<endl;

}
*/

