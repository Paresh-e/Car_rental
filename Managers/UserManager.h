#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "../Entity/User.h"
#include "../Containers/DoublyLL.h"
#include "../Containers/Hashtable.h"

using namespace std;

class UserManager
{
private:
    string fileName;

    DoublyLinkedList<User> usersList;            
    HashTable<string, User*> userTable;          

public:
    UserManager(string fileName);
    bool hasManager();
    void loadUsersFromFile();
    void saveUsersToFile();

    User* searchUserByUsername(string username);

    bool addUser(const User& user);
    bool removeUserByUsername(string username);

    bool login(string username, string passwordHash);

    void displayAllUsers();
    int generateNewUserID();
    bool registerUser(string username, string passwordHash, UserRole role);
};

#endif