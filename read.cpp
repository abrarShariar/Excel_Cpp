#include<iostream>
#include<vector>
#include<fstream>
#include<set>
using namespace std;


//for reading customers name
vector<string>getCustomersDetails(){
    vector<string>customerName;
    string fileName="a.csv";
    ifstream read;
    read.open(fileName);

    while(read.good()){
        string name;
        getline(read,name);
        customerName.push_back(name);
    }
    return customerName;
    read.close();
}

//for reading all data from custometrs bills
vector<string>getCustomersBills(){
    vector<string>customerBills;
    ifstream read;
    read.open("b.csv");

    while(read.good()){
        string temp;
        getline(read,temp);
        customerBills.push_back(temp);
    }
    return customerBills;
}


//get address from the customer's details table
set<string>getAddress(){
       set<string>addressList;
       int commaCount=0;
       int start=-1;
       vector<string>details=getCustomersDetails();

        for(int i=1;i<details.size();i++){      //starting from 1 skipping the column labels
            string text=details[i];
            commaCount=0;
            start=-1;
            for(int j=0;j<text.length();j++){
                if(text[j]==','){
                    commaCount++;
                     if(commaCount==3){
                    string temp=text.substr(start+1,j-start-1);
                    addressList.insert(temp);
                    break;
                }
                    start=j;
                }

            }
        }
        return addressList;     //return all the address
}


//get id of customers specific to one address
string getAddressId(string address,vector<string>details){
        string resId="";
        string tempAdd;
       for(int i=1;i<details.size();i++){      //starting from 1 skipping the column labels
            string text=details[i];
            int commaCount=0;
            int start=-1;
            for(int j=0;j<text.length();j++){
                if(text[j]==','){
                    commaCount++;
                     if(commaCount==3){
                     tempAdd=text.substr(start+1,j-start-1);
                    break;
                }
                    start=j;
                }
            }
            //if the address matches
            if(tempAdd==address){
                string id;
                size_t index=text.find_first_of(",");
                id=text.substr(0,index);
                resId=resId+" "+id;
            }
        }
        return resId;
    }



//test & trail
int main(){
    set<string>address=getAddress();
    for(auto it=address.begin();it!=address.end();it++){
        cout<<*it<<endl;
    }
    cout<<"\n\n\n"<<endl;

    vector<string>details=getCustomersDetails();
    string add;
    getline(cin,add);
    cout<<getAddressId(add,details)<<endl;




    /*
    vector<string>myVec=getCustomersDetails();
    for(int i=0;i<myVec.size();i++){
        cout<<myVec[i]<<endl;
    }
    cout<<"\n\n\n"<<endl;
    vector<string>bills=getCustomersBills();
    for(int i=0;i<bills.size();i++){
        cout<<bills[i]<<endl;
    }
    */
}



