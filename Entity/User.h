//
// Created by asus on 2/9/2026.
//

#ifndef CAR_RENTAL_USER_H
#define CAR_RENTAL_USER_H
#include <string>
enum UserRole
{
    GUEST,
    CUSTOMER,
    STAFF,
    MANAGER
};

class User {
public :
    int id;
    std::string username;
    std::string passwordHash;
    UserRole role;
    bool blocked;
    User();
    User(int id,
         const std::string& username,
         const std::string& passwordHash,
         UserRole role);
};


#endif //CAR_RENTAL_USER_H
