#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin : public User {
public:
    Admin(string p_id, string p_uname, string p_pass) 
        : User(p_id, p_uname, p_pass, "ADMIN") {}

    void displayMenu() override {
        cout << "=== MENU ADMIN ===" << endl;
        cout << "1. Buat Turnamen\n2. Atur Jadwal\n3. Keluar\n";
    }

    void showProfile() override {
        cout << "Admin ID: " << id << " | Username: " << username << endl;
    }

    // Method tambahan nanti diisi Orang ke-2
};
#endif 