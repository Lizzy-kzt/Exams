#ifndef NEWBANK_H_INCLUDED
#define NEWBANK_H_INCLUDED
#include<iostream>
using namespace std;

namespace N{

class NewBank{

public: int _index=0;
        int admin_index=0;
        int current_index=0;
        string admin_name[5]={"johny","lizzy"};
        string admin_pw[5]={"1001","9090"};
       string _username[100];
       string _password[100];
       string _amount[100];

       void welcome();
       void _loading();
       void MainMenu();
       void _register();
       int usernamecheck(string username);
       void _login();
       void userview();
       void transfer();
       int amountcheck(string balance);
       int passwordcheck(string password);
       void withdraw();
       void saving();
       void changeInfo();
       void transition_record(string name,string amount);
       void adminview();
       void admin1();
       void specificfind();
       void transition_view();
       void continueorback();
       void restoredata();
      void showallData();
};

}


#endif // NEWBANK_H_INCLUDED
