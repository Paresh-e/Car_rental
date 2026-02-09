#include "User.h"

User::User()
{
    id = 0;
    role = GUEST;
    blocked = false;
}

User::User(int id,
           const std::string& username,
           const std::string& passwordHash,
           UserRole role)
{
    this->id = id;
    this->username = username;
    this->passwordHash = passwordHash;
    this->role = role;
    this->blocked = false;
}