#ifndef PESERTA_H
#define PESERTA_H

#include "User.h"

class Peserta : public User {
public:
    Peserta(string p_id, string p_uname, string p_pass) 
        : User(p_id, p_uname, p_pass, "PESERTA") {}

    void displayMenu() override {
        cout << "=== MENU PESERTA ===" << endl;
        cout << "1. Daftar Tim\n2. Lihat Jadwal\n3. Keluar\n";
    }

    void showProfile() override {
        cout << "Peserta ID: " << id << " | Username: " << username << endl;
    }

    // Method tambahan nanti diisi Orang ke-3
};
#endif