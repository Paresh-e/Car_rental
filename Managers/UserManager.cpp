#include "UserManager.h"

UserManager::UserManager(string fileName)
{
    this->fileName = fileName;
}

void UserManager::loadUsersFromFile()
{
    ifstream inFile(fileName);

    if (!inFile)
    {
        cout << "Error: Cannot open file: " << fileName << endl;
        return;
    }

    string line;

    while (getline(inFile, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        int id;
        string username;
        string passwordHash;
        int roleInt;
        int blockedInt;

        ss >> id >> username >> passwordHash >> roleInt >> blockedInt;

        User user(id, username, passwordHash, (UserRole)roleInt);
        user.blocked = (blockedInt == 1);

      
        User* ptr = usersList.pushBack(user);

      
        userTable.insert(username, ptr);
    }

    inFile.close();
}

void UserManager::saveUsersToFile()
{
    ofstream outFile(fileName);

    if (!outFile)
    {
        cout << "Error: Cannot open file for writing: " << fileName << endl;
        return;
    }

    auto curr = usersList.getHead();

    while (curr != nullptr)
    {
        User user = curr->data;

        outFile << user.id << " "
                << user.username << " "
                << user.passwordHash << " "
                << (int)user.role << " "
                << (user.blocked ? 1 : 0)
                << endl;

        curr = curr->next;
    }

    outFile.close();
}

User* UserManager::searchUserByUsername(string username)
{
    return userTable.search(username);
}

bool UserManager::addUser(const User& user)
{
   
    if (userTable.search(user.username) != nullptr)
        return false;

    User* ptr = usersList.pushBack(user);
    userTable.insert(user.username, ptr);

    return true;
}
bool UserManager::hasManager()
{
    auto curr = usersList.getHead();
    while (curr != nullptr)
    {
        if (curr->data.role == MANAGER)
            return true;
        curr = curr->next;
    }
    return false;
}
bool UserManager::removeUserByUsername(string username)
{
    auto curr = usersList.getHead();

    while (curr != nullptr)
    {
        if (curr->data.username == username)
        {
           
            userTable.remove(username);

        
            usersList.remove(curr);

            return true;
        }

        curr = curr->next;
    }

    return false;
}

bool UserManager::login(string username, string passwordHash)
{
    User* user = userTable.search(username);

    if (user == nullptr)
        return false;

    if (user->blocked == true)
        return false;

    return user->passwordHash == passwordHash;
}

void UserManager::displayAllUsers()
{
    auto curr = usersList.getHead();

    while (curr != nullptr)
    {
        User user = curr->data;

        cout << "ID: " << user.id
             << " Username: " << user.username
             << " Role: " << user.role
             << " Blocked: " << (user.blocked ? "Yes" : "No")
             << endl;

        curr = curr->next;
    }
}
int UserManager::generateNewUserID()
{
    int maxID = 0;

    auto curr = usersList.getHead();
    while (curr != nullptr)
    {
        if (curr->data.id > maxID)
            maxID = curr->data.id;

        curr = curr->next;
    }

    return maxID + 1;
}
bool UserManager::registerUser(string username, string passwordHash, UserRole role)
{
    
    if (userTable.search(username) != nullptr)
        return false;

    int newID = generateNewUserID();

    User newUser(newID, username, passwordHash, role);

    bool result = addUser(newUser);

    if (result)
        saveUsersToFile();   

    return result;
}