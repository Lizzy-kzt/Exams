#include"lottery.h"
#include<fstream>
#include<iostream>
using namespace std;
using namespace N;

void lottery::welcome(){
cout<<"Welcome to our lottery"<<endl;
 loading();
option();
}
void lottery::option(){
    string myoption;
    cout<<"Press 1 to go to game "<<endl;
    cout<<"Press 2 to exit";
    cin>>myoption;

    if(myoption=="1"){
        showData();

    }else if(myoption=="2"){
        restoreData();

    }else{
     cout<<"Invalid"<<endl;
     option();

    }
}

void lottery::loading(){
string data;
string dataLine;

cout<<"Loading ..\n..\n."<<endl;

ifstream datafile;
datafile.open("number.txt");

if(datafile.is_open()){
    while(getline(datafile,dataLine)){
        dataLine=dataLine+",";
        for(auto &ch:dataLine){
            if(ch==','){
                _arrnumber[Index]=data;
                Index++;
                data="";
            }else{

            string st(1,ch);
            data=data+st;
            }
        }
    }
   Index--;

datafile.close();

}else{
    cout<<"File doesn't exist"<<endl;
}


}
void lottery::showData(){
cout<<"\nIndex"<<Index<<endl;
cout<<"Numbers you can pick:"<<endl;
for(int i=0;i<=Index;i++){
    cout<<_arrnumber[i]<<"  ";

 }
mainMenu();
}
void lottery::mainMenu(){
string number;
string name;
string phnum;

cout<<"\nPick a number: ";
cin>>number;
int result=findNumber(number);

if(result>=0){
    cout<<"Enter your name";
    cin>>name;
    cout<<"Enter your phnumber";
    cin>>phnum;

   record(number,name,phnum);

}else{
    cout<<"The number is already chosen Or Doesn't Exit .Try again!"<<endl;
    mainMenu();
}

}
int lottery::findNumber(string num){

    for(int i=0;i<=Index;i++){

        if(num==_arrnumber[i]){
            cout<<"You pick "<<num<<"successfully"<<endl;
            return i;
        }
    }
    return -1;
}

void lottery::record(string numb,string name,string ph){

for(int j=0;j<=Index;j++){
    if(numb==_arrnumber[j]){
        for(int i=j;i<=Index;i++){
            _arrnumber[i]=_arrnumber[i+1];

        }
    }
}
Index--;
cout<<"Your Record "<<endl;
cout<<"----------------------------"<<endl;
cout<<"Name: "<<name<<endl;
cout<<"Phone Number: "<<ph<<endl;
cout<<"Number: "<<numb<<endl;
//showData();

fstream recordfile;
recordfile.open("record_file.txt",ios::app);


   recordfile<<"Record"<<endl;
   recordfile<<"---------------------"<<endl;
   recordfile<<"Name:"<<name<<endl;
   recordfile<<"Lottery Number: "<<numb<<endl;
   recordfile<<"Phone Number: "<<ph<<endl<<endl;

recordfile.close();
option();
}
void lottery::restoreData(){

fstream restorefile;

restorefile.open("number.txt",ios::out);
for(int k=0;k<=Index;k++){

    if(k==Index){
      restorefile<<_arrnumber[k];
    }else{
    restorefile<<_arrnumber[k]<<",";
    }

}
cout<<"Finished Successfully"<<endl;
restorefile.close();
exit(1);
}




