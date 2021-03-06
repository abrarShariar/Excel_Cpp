//ExcelC++
#include<iostream>
#include<dirent.h>
#include<cstdio>
#include<vector>
#include<fstream>
#include<set>
#include<map>
using namespace std;



//customers details fileName
string getDetailsFileName(){
const char *location=".\\customersDetails";
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
    return fileName;
}

//bills file name
string getBillsFileName(){
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
    return fileName;

}


//extract id from data
string searchId(string data){
    string id;
    size_t index=data.find_first_of(",");
    id=data.substr(0,index);
    return id;
}

//extract address from data
string searchAdd(string data){
        int commaCount=0;
        int start=-1;
        string temp;
        for(int j=0;j<data.length();j++){
            if(data[j]==','){
                commaCount++;
                if(commaCount==14){
                    temp=data.substr(start+1,j-start-1);
                    break;
                }
                start=j;
            }
    }
     return temp;
}

//extract first name from data
string searchFirstName(string data){
     int commaCount=0;
        int start=-1;
        string temp;
        for(int j=0;j<data.length();j++){
            if(data[j]==','){
                commaCount++;
                if(commaCount==3){
                    temp=data.substr(start+1,j-start-1);
                    break;
                }
                start=j;
            }
    }
     return temp;
}

//extract second name from data
string searchLastName(string data){
     int commaCount=0;
        int start=-1;
        string temp;
        for(int j=0;j<data.length();j++){
            if(data[j]==','){
                commaCount++;
                if(commaCount==4){
                    temp=data.substr(start+1,j-start-1);
                    break;
                }
                start=j;
            }
    }
     return temp;
}

//extract bill  from data
string searchBill(string data){
        string bill="";
        size_t index=data.find_first_of(",");
        bill=data.substr(index+1,data.length()-index+1);
        return bill;
}

//map phone number with customer id
map<string,string>mapPhone(vector<string>details){
    map<string,string>myMap;
      for(int i=0;i<details.size();i++){
            int start=-1;
            int commaCount=0;
           string id=searchId(details[i]);
           string temp=details[i];
            string data="";
            for(int j=0;j<temp.length();j++){
            if(temp[j]==','){
                commaCount++;
                if(commaCount==7){
                    data=temp.substr(start+1,j-start-1);
                    break;
                }
                start=j;
                }
            }
        myMap[id]=data;
    }
    return myMap;
}

//for reading customers name
vector<string>getCustomersDetails(string fileName){
    vector<string>customerName;
    string location="customersDetails\\"+fileName;
    //string fileName="customers.csv";
    ifstream read;
    read.open(location);

    while(read.good()){
        string name;
        getline(read,name);
        customerName.push_back(name);
    }
    read.close();
    return customerName;
}

//for reading all data from custometrs bills
vector<string>getCustomersBills(string fileName){
    vector<string>customerBills;
    string location="customersBills\\" + fileName;
    ifstream read;
    read.open(location);

    while(read.good()){
        string temp;
        getline(read,temp);
        customerBills.push_back(temp);
    }
    read.close();
    return customerBills;
}

//get address from the customer's details table
set<string>getAddress(){
       set<string>addressList;
       string fileName=getDetailsFileName();
       vector<string>details=getCustomersDetails(fileName);

        for(int i=1;i<details.size();i++){      //starting from 1 skipping the column labels
            string text=details[i];
            string temp=searchAdd(text);
            addressList.insert(temp);
        }
        return addressList;     //return all the address
}

//get id of customers specific to one address
vector<string>getAddressId(string address,vector<string>details){
        vector<string>resId;
        string tempAdd="";
       for(int i=1;i<details.size();i++){      //starting from 1 skipping the column labels
            string text=details[i];
            int commaCount=0;
            int start=-1;
            tempAdd=searchAdd(text);
            //if the address matches
            if(tempAdd==address){
                string id=searchId(text);
                resId.push_back(id);
            }
        }
        return resId;
    }

//match id from two table
string matchId(string id,vector<string>&bills){
    string data="";
    for(int i=0;i<bills.size();i++){
        string checkId=searchId(bills[i]);
        if(checkId==id){
            data=bills[i];
            bills.erase(bills.begin()+i);
            break;
        }
    }
    return data;
}

//check for duplicate address
int addressDuplicate(string add,set<string>addList){
        int duplicate=0;
        for(auto it=addList.begin();it!=addList.end();it++){
            if(add==*it){
                duplicate++;
            }
        }
        return duplicate;
}

//set Name=first_name+last_name
string getFullName(string id,vector<string>details){
    string fullName="";
    for(int i=0;i<details.size();i++){
            string checkId=searchId(details[i]);
            if(checkId==id){
                fullName=searchFirstName(details[i])+" "+searchLastName(details[i]);
                break;
            }
    }
    return fullName;
}

//clean string
string cleanString(string text){
    for(int i=0;i<text.length();i++){
        if(text[i]=='"'){
            text.erase(text.begin()+i);
        }
    }
    return text;
}



//test & trail
int main(){
    string customerDetailsFile=getDetailsFileName();
    string customerBillsFile=getBillsFileName();

    ofstream write;
    write.open("write.csv");
    //match id-address and write output to a file

    vector<string>customerDetails=getCustomersDetails(customerDetailsFile);
    vector<string>customerBills=getCustomersBills(customerBillsFile);
    set<string>address=getAddress();
    map<string,string>phoneMap=mapPhone(customerDetails);

    bool showAdd=false;
    for(auto it=address.begin();it!=address.end();++it){
        showAdd=false;
            if(it==address.begin()){
                write<<"Id,Name,Phone,Current_Bill,Due,Total\n"<<endl;
            }
        vector<string>addressIdList=getAddressId(*it,customerDetails);      //all id of a particular address
        for(int i=0;i<addressIdList.size();i++){
            string idData=matchId(addressIdList[i],customerBills);
            if(idData!=""){
                if(!showAdd){
                    string add=*it;
                    add=cleanString(add);
                    write<<"\nADDRESS: "<<add<<endl;
                    showAdd=true;
                }
                //preparing output data
                string id=searchId(idData);
                string phone=phoneMap[id];
                string name=getFullName(id,customerDetails);

                string bill=searchBill(idData);
                write<<id<<","<<name<<","<<phone<<","<<bill<<endl;
            }
        }
    }
    write.close();
    return 0;
}



