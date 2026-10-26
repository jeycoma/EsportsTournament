#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

using namespace std;

// Abstract Base Class
class User {
protected:
    // Enkapsulasi: Atribut diset protected agar bisa diakses turunan
    string id;
    string username;
    string password;
    string role;

public:
    // Constructor
    User(string p_id, string p_uname, string p_pass, string p_role) {
        id = p_id;
        username = p_uname;
        password = p_pass;
        role = p_role;
    }

    virtual ~User() {} // Virtual destructor

    // Getter (Enkapsulasi)
    string getId() const { return id; }
    string getUsername() const { return username; }
    string getRole() const { return role; }
    bool verifyPassword(string pass) { return password == pass; }

    // Pure Virtual Functions (Abstraksi - Wajib di-override oleh turunan)
    virtual void displayMenu() = 0;
    virtual void showProfile() = 0;
};

#endif