#include<iostream>
#include"Newbank.h"
#include<fstream>
#include<string>
#include<ctime>
using namespace N;

void NewBank::welcome(){

cout<<"Hello This is my bank"<<endl;
_loading();
}
void NewBank::_loading(){
int coUnt=0;
string Line;
string data;

cout<<"Loading ........"<<endl;

ifstream userfile("userdata.txt");

if(userfile.is_open()){

    while(getline(userfile,Line)){
        Line=Line+" ";
        for(auto &ch:Line){
            if(ch==' '){
              if(coUnt==0){
                _username[_index]=data;
                data="";
                coUnt++;
              }else if(coUnt==1){
              _password[_index]=data;
              data="";
              coUnt++;
              }else if(coUnt==2){
              _amount[_index]=data;
              data="";
              coUnt=0;
              _index++;
              }

        }else{

            string st(1,ch);
            data=data+st;

            }
        }
    }

 }else{
  cout<<"Userfile is empty"<<endl;
}
userfile.close();
cout<<"Done"<<endl;
//showallData();
MainMenu();
}
void NewBank::MainMenu(){
string mainoption;
cout<<"Press 1 to register"<<endl;
cout<<"Press 2 to login"<<endl;
cout<<"Press 3 to exit ";
cin>>mainoption;

    if(mainoption=="1"){
        _register();

    }else if(mainoption=="2"){
        _login();

    }else if(mainoption=="3"){
        restoredata();
        exit(1);
    }else{
    cout<<"Invalid"<<endl;

    MainMenu();
    }

}
void NewBank::_register(){
cout<<"This is register function"<<endl;
string r_username;
string r_password;
string r_amount;

cout<<"Enter username:  ";
cin>>r_username;
 int user_result=usernamecheck(r_username);

         if(user_result==-1){

            cout<<"Enter password: ";
            cin>>r_password;
            cout<<"Enter amount: ";
            cin>>r_amount;

            _username[_index]=r_username;
            _password[_index]=r_password;
            _amount[_index]=r_amount;
            _index++;           //index will always point next
           // showallData();
            MainMenu();
         }else{

         cout<<"Username already exist! Try again: "<<endl;
         _register();
         }

}
int NewBank::usernamecheck(string username){

    for(int i=0;i<_index;i++){

        if(_username[i]==username){
            return i;
        }
    }
    return -1;
}
void NewBank::_login(){
    string l_username;
    string l_password;
cout<<"This is login function"<<endl;

cout<<"Enter username :";
cin>>l_username;
cout<<"Enter password :";
cin>>l_password;

    for(int i=0;i<5;i++){

        if(l_username==admin_name[i]&&l_password==admin_pw[i]){

                admin_index=i;
                adminview();
        }
    }

    for(int k=0;k<_index;k++){

        if(l_username==_username[k]&&l_password==_password[k]){
            cout<<"Match username & password"<<endl;
            current_index=k;
            userview();
        }

    }
     cout<<"Invalid !"<<endl;
            MainMenu();
}
void NewBank::userview(){

    string useroption;

    cout<<"Welcome "+_username[current_index]<<endl;
    cout<<"Your  Balance is"+_amount[current_index]<<endl;
    cout<<"--------------------------------------"<<endl;
    cout<<"Press 0 to go previous stage"<<endl;
    cout<<"Press 1 to transfer:"<<endl;
    cout<<"Press 2 to withdraw:"<<endl;
    cout<<"Press 3 to save money"<<endl;
    cout<<"Press 4 to change your account Info:";
    cin>>useroption;

    if(useroption=="1"){
        transfer();
    }else if(useroption=="2"){
        withdraw();
    }else if(useroption=="3"){
       saving();
    }else if(useroption=="4"){
       changeInfo();

    }else if(useroption=="0"){
        MainMenu();

    }
    else{
    cout<<"Invalid option"<<endl;
    userview();
    }

}
void NewBank::transfer(){

    int checkresult=0;

    string transfername;
    string transferamount;
    cout<<"Enter username to transfer: ";
    cin>>transfername;

    for(int i=0;i<_index;i++){

        if(_username[i]==transfername){

            cout<<"Enter amount to transfer: ";
            cin>>transferamount;
            checkresult=amountcheck(transferamount);

                if(checkresult==1){ //check amount

                            string receiverStr=_amount[i];
                             int  receiverInt=stoi(receiverStr);
                            int  transferInt=stoi(transferamount);

                            receiverInt=receiverInt+transferInt;

                            string str=to_string(receiverInt);
                            _amount[i]=str;

                            cout<<"Successfully Transfered!..."<<endl;
                            transition_record(transfername,transferamount);
                            //showallData();
                            userview();


                }else if(checkresult==0){

                    cout<<"Your amount is not enough to transfer! "<<endl;
                    transfer();

                }// check amount end


         //for checking username
        }

    }//for loop ending
         cout<<"No match username! Please Try again!"<<endl;
        transfer();

}
int NewBank::amountcheck(string balance){     //checking amount and password for transfer and withdraw

    int balanceInt=stoi(balance);
    string amountStr=_amount[current_index];
    int amountInt=stoi(amountStr);

    if(amountInt>balanceInt){

        cout<<"You can transfer! "<<endl;

        string confirm_password;
        cout<<"Enter your  account password to transfer:" ;
        cin>>confirm_password;

        int passwordresult=passwordcheck(confirm_password);

        if(passwordresult==0){

        amountInt=amountInt-balanceInt;
        string str=to_string(amountInt);
        _amount[current_index]=str;
        return 1;

        }else if(passwordresult=1){

        cout<<"Your password is incorrect"<<endl;
        transfer();
        }


    }
    return 0;


}
int NewBank::passwordcheck(string password){

    if(password==_password[current_index]){

        return 0;
    }

    return 1;
}
void NewBank::withdraw(){

string withdrawamount;
  cout<<"Enter amount to withdraw:";
  cin>>withdrawamount;

 int result=amountcheck(withdrawamount);

 if(result==1){
    cout<<withdrawamount+" is successfully withdrawed from your account"<<endl;
    transition_record(" ",withdrawamount);
    //showallData();
    userview();
 }else{
  cout<<" Your amount is not enough"<<endl;
  userview();
 }
}
void NewBank::saving(){
 string saveamount;
 string savepassword;
cout<<"Enter amount to save:";
cin>>saveamount;

cout<<"Confrim your password to save";
cin>>savepassword;
 int passresult=passwordcheck(savepassword);

 if(passresult==0){

    string currentamount=_amount[current_index];
    int currentamountInt=stoi(currentamount);
    int saveamountInt=stoi(saveamount);

    currentamountInt=currentamountInt+saveamountInt;

  _amount[current_index]=to_string(currentamountInt);

  cout<<"Successfully  saved!"<<endl;
  transition_record("$",saveamount);
 // showallData();
  userview();

 }else{

    cout<<"Wrong password! "<<endl;
    saving();
 }
}
void NewBank::transition_record(string name,string amount){

time_t now=time(0);
char *time=ctime(&now);

fstream recordfile;
recordfile.open("record.txt",ios::app);

  if(name==" "){

    recordfile<<_username[current_index]+" withdrawed  "+amount+"  at  "+time;
  }else if(name=="$"){

    recordfile<<_username[current_index]+"  saved  "+amount+"  at  "+time;
   }

  else{

   recordfile<<_username[current_index]+"  transfered  "+amount+"  to  "+name+"  at  "+time;


  }
cout<<"Successfully record!"<<endl;
  recordfile.close();
}
void NewBank::changeInfo(){

    string option;
    string newusername;
    string newpassword;

cout<<"Press 1 to change username:"<<endl;
cout<<"Press 2 to change password:";
cin>>option;

if(option=="1"){

    cout<<"Enter new username";
    cin>>newusername;

    _username[current_index]=newusername;
    cout<<"Username successfully changed!"<<endl;
    userview();
}else if(option=="2"){

    cout<<"Enter new password:";
    cin>>newpassword;

    _password[current_index]=newpassword;
    cout<<"Password successfully changed! "<<endl;
    userview();
}else{

  cout<<"Invalid! "<<endl;
  userview();

}

}
void NewBank::adminview(){
 cout<<"Welcome to admin view"<<endl;

 if(admin_index==0){


    cout<<" Your admin level is 1 "<<endl;
    cout<<"---------------------------"<<endl;
    admin1();

 }else {

    cout<<"Your admin level is 2(YOU CAN ONLY SEE TRANSITION RECORD)"<<endl;
    cout<<"-----------------------"<<endl;
    transition_view();
 }
}
void NewBank::admin1(){
string aORs;
string adminoption;

    cout<<"Press 1 to see  user Info "<<endl;
    cout<<"Press 2 to see  transistion record: ";
    cin>>adminoption;

    if(adminoption=="1"){

   cout<<"All or specific (Press a or s): ";
    cin>>aORs;

            if(aORs=="a"||aORs=="A"){
               showallData();
               continueorback();
            }else if(aORs=="s"||aORs=="S"){

                specificfind();
            }else{
                admin1();
            }

    }else if(adminoption=="2"){

        transition_view();
    }else{

    cout<<"Invalid"<<endl;
    admin1();
    }
}
void NewBank::showallData(){

for(int j=0;j<_index;j++){

    cout<<"Name is:"<<_username[j]<<endl;
    cout<<"Password is"<<_password[j]<<endl;
    cout<<"Amount is: "<<_amount[j]<<endl;
}

}
void NewBank::specificfind(){
string specificname;
cout<<"Enter specific username to find";
cin>>specificname;

for(int i=0;i<_index;i++){
    if(_username[i]==specificname){
        cout<<"Name is:"+_username[i]<<endl;
        cout<<"Password is: "+_password[i]<<endl;
        cout<<"Amount is: "+_amount[i]<<endl;
    }
}
continueorback();
}
void NewBank::transition_view(){

 char info;
    cout<<"All or specific (Press a or s): ";
    cin>>info;

    if(info=='a'||info=='A'){

     string mytext;
    ifstream readfile;
    readfile.open("record.txt");

            while (getline (readfile, mytext)) {

          cout << mytext<<endl;
        }

    readfile.close();
     continueorback();
    }else if(info=='s'|| info=='S'){
    string name;
    string data;
    string specificname;
    cout<<"Enter specific username to find record:";
    cin>>specificname;

    ifstream readspecific;
    readspecific.open("record.txt");

            while(getline(readspecific,data)){

               for(auto &ch:data){


                  if(ch!=' '){

                    string st(1,ch);
                    name=name+st;


                  }else{

                   if(name==specificname){
                        cout<<data<<endl;
                        name="";

                       break;
                    }else{

                       // cout<<"Next Line"<<endl;
                        name="";
                        break;

                    }

                  }

                   continue;
                    }
                     // name="";


                }
              readspecific.close();
              continueorback();

            }else{
            cout<<"Invalid"<<endl;
            transition_view();

            }

        }


void NewBank::continueorback(){

    string choice;
     cout<<"Press 1 to continue"<<endl;
     cout<<"Press 2 to log out from admin level";
     cin>>choice;

     if(choice=="1"){
        adminview();
     }else if(choice=="2"){
        MainMenu();
     }else{
        continueorback();
     }

}
void NewBank::restoredata(){

fstream restorefile;

restorefile.open("userdata.txt",ios::out);

for(int i=0;i<_index;i++){

    restorefile<<_username[i]+" "+_password[i]+" "+_amount[i]<<endl;
}
cout<<"Restored File"<<endl;
restorefile.close();
}

