#include "read.cpp"
using namespace std;


int main(){

    /*
    for(int i=0;i<details.size();i++){
        string idName=searchId(details[i]);
        cout<<idName<<endl;
    }
    */
/*
    vector<string>details=getCustomersDetails();
    for(int i=0;i<details.size();i++){
        string address=searchAdd(details[i]);
        cout<<address<<endl;
    }
   */
    vector<string>details=getCustomersDetails();
   map<string,string>idPhoneMap=mapPhone(details);
   for(auto it=idPhoneMap.begin();it!=idPhoneMap.end();it++){
        cout<<it->first<<" : "<<it->second<<endl;
   }
}
