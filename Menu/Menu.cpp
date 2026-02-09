//
// Created by asus on 2/9/2026.
//

#include "Menu.h"
#include <iostream>
using namespace std;
void Menu::start() {

    int choice = 0 ;
    while(true){
        cout<<"------------------------------"<<endl;
        cout<<"Welcome..||CarRentalSystem||"<<endl;
        cout<<"------------------------------"<<endl;
        cout<<"1.Guest\n"<<"2.Customer\n"<<"3.Staff\n" <<"4.Maintenace\n"<<"5.Manager"<<endl;
        cin>>choice;
        if(choice == 1){

        }
        else if (choice==2){

        }
        else if (choice ==3 ){

        }
        else if(choice == 4){

        }
        else if (choice == 50){

        }
        else{
            std::cout << "Invalid choice.\n";
            _sleep(2000);
        }

    }





}