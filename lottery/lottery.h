#ifndef LOTTERY_H_INCLUDED
#define LOTTERY_H_INCLUDED
#include<string>
 namespace N{

class lottery{

public://attributes
        int Index=0;

        std::string _arrnumber[100];
        std::string _arrname[100];
        std::string _arrphno[100];
        //method declaration
       void welcome();
       void option();
        void loading();
        void showData();
        void mainMenu();
        int findNumber(std::string num);
       void record(std::string numb,std::string name,std::string ph);
       void restoreData();
};


}


#endif // LOTTERY_H_INCLUDED
