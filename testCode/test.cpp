#include<iostream>
#include<vector>
#include<fstream>
#include<string>
using namespace std;

//class for first data table

class Data{
    private:
        string id;
        string firstName;
        string lastName;
        string address;
        string phone;
    public:
        //setters
        void setId(string id){
            this->id=id;
        }
        void setFirstName(string firstName){
            this->firstName=firstName;
        }
        void setLastName(string lastName){
            this->lastName=lastName;
        }
        void setAddress(string address){
            this->address=address;
        }
        void setPhone(string phone){
            this->phone=phone;
        }
        //getters
        string getId(){
            return this->id;
        }
        string getFirstName(){
            return this->firstName;
        }
        string getLastName(){
            return this->lastName;
        }
        string getAddress(){
            return this->address;
        }
        string getPhone(){
            return this->phone;
        }
};


vector<Data> firstFile(){
    vector<Data>dataSheet;
   string fileName;
   cout<<"Filename: ";
   cin>>fileName;
   fileName=fileName+".csv";

   ifstream read;
   read.open(fileName);

/*
   while(read.good()){
      string text;
      read>>text;
      cout<<text<<endl;
   }
  */

   while(read.good()){
        Data dataObj;
        string text;
        read>>text;
        int commaCount=0;
        int start=-1;
        string temp;
        //dataSheet.push_back(text);
        //iterate loop and find comma
        for(int i=0;i<text.length()+1;i++){
            if(text[i]==',' || text[i]=='\0'){
                temp=text.substr(start+1,i-start-1);
                commaCount++;
                start=i;
            }
            switch(commaCount){
                case 1:
                    dataObj.setId(temp);
                    break;
                case 2:
                    dataObj.setFirstName(temp);
                    break;
                case 3:
                    dataObj.setLastName(temp);
                    break;
                case 4:
                    dataObj.setAddress(temp);
                    break;
                case 5:
                    dataObj.setPhone(temp);
                    break;
            }
        }
        dataSheet.push_back(dataObj);
   }
   return dataSheet;

//print
/*
    for(int i=0;i<dataSheet.size();i++){
        Data myData=dataSheet[i];
        cout<<myData.getId()<<"  "<<myData.getFirstName()<<"  "<<myData.getLastName()<<"  "<<myData.getAddress()<<"  "<<myData.getPhone()<<endl;
    }
    */
}
