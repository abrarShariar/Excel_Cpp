#include<iostream>
#include<vector>
#include<fstream>
#include<set>
using namespace std;


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
                if(commaCount==3){
                    temp=data.substr(start+1,j-start-1);
                    break;
                }
                start=j;
            }
    }
     return temp;
}

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
       vector<string>details=getCustomersDetails();

        for(int i=1;i<details.size();i++){      //starting from 1 skipping the column labels
            string text=details[i];
            string temp=searchAdd(text);
            addressList.insert(temp);
        }
        return addressList;     //return all the address
}

//get id of customers specific to one address
vector<string> getAddressId(string address,vector<string>details){
        vector<string> resId;
        string tempAdd;
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
    string data;
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

//test & trail
int main(){
    ofstream write;
    write.open("write.csv");

//match id-address and write output to a file
    vector<string>customerDetails=getCustomersDetails();
    vector<string>customerBills=getCustomersBills();
    set<string>address=getAddress();
    for(auto it=address.begin();it!=address.end();++it){
        write<<"\nAddress: "<<*it<<endl;
            if(it==address.begin()){
                write<<"Id,Name,Current_Bill,Due,Total"<<endl;
            }
        vector<string>addressIdList=getAddressId(*it,customerDetails);
        for(int i=0;i<addressIdList.size();i++){
            string idData=matchId(addressIdList[i],customerBills);
            write<<idData<<endl;
        }
    }
    return 0;
}

/*
    vector<string>myBill=getCustomersBills();
    string chk;
    cin>>chk;
    cout<<matchId(chk,myBill)<<endl;
    */

/*
    vector<string>bills=getCustomersBills();
    for(int i=0;i<bills.size();i++){
        cout<<bills[i]<<endl;
    }
   */



/*
    vector<string>details=getCustomersDetails();
    string add;
    getline(cin,add);
    cout<<getAddressId(add,details)<<endl;
*/



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




