#include <iostream>
#include <vector>
#include <string>
#include "User.h"
#include "Admin.h"
#include "Peserta.h"
#include "Tournament.h"
#include "SingleEliminationTournament.h"
#include "RoundRobinTournament.h"
#include "CsvHandler.h"

using namespace std;

void tampilkanHeader() {
    cout << "\n=========================================" << endl;
    cout << "   SISTEM MANAGEMENT TURNAMEN ESPORTS    " << endl;
    cout << "   Object Oriented Programming Project   " << endl;
    cout << "=========================================" << endl;
}

// Fungsi helper untuk validasi input angka agar tidak infinite loop
int getValidIntInput() {
    int input;
    while (!(cin >> input)) {
        cout << "[ERROR] Masukkan angka yang valid: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    return input;
}

// Fungsi cek login langsung dari data/users.csv
bool authenticateUser(const string& uname, const string& pass, const string& targetRole, string& outUserId) {
    vector<vector<string>> users = CsvHandler::readCSV("data/users.csv");
    for (size_t i = 1; i < users.size(); ++i) { // Mulai indeks 1 untuk skip header CSV
        if (users[i].size() >= 4) {
            if (users[i][1] == uname && users[i][2] == pass && users[i][3] == targetRole) {
                outUserId = users[i][0];
                return true;
            }
        }
    }
    return false;
}

int main() {
    int pilihan;

    do {
        tampilkanHeader();
        cout << "Pilih Login / Menu Utama:" << endl;
        cout << "1. Login sebagai Admin" << endl;
        cout << "2. Login sebagai Peserta (Kapten Tim)" << endl;
        cout << "3. Simulasi Polimorfisme Turnamen (Demo)" << endl;
        cout << "4. Keluar Program" << endl;
        cout << "Pilihan Anda (1-4): ";
        pilihan = getValidIntInput();

        if (pilihan == 1) {
            string username, password, userId;
            cout << "\n--- LOGIN ADMIN ---" << endl;
            cout << "Username: "; cin >> username;
            cout << "Password: "; cin >> password;

            if (authenticateUser(username, password, "ADMIN", userId)) {
                Admin adminObj(userId, username, password);
                int adminMenu;
                do {
                    adminObj.displayMenu();
                    cout << "Pilih opsi Admin: ";
                    adminMenu = getValidIntInput();

                    if (adminMenu == 1) {
                        adminObj.createTournament();
                    } else if (adminMenu == 2) {
                        cout << "[INFO] Fitur generate jadwal otomatis diproses di Engine.\n";
                        adminObj.scheduleMatch(); // Panggil method atur jadwal jika sudah ditambahkan di Admin.h
                        // Panggil method atur jadwal jika sudah ditambahkan di Admin.h
                    } else if (adminMenu == 3) {
                        adminObj.inputMatchResult();
                    } else if (adminMenu != 4) {
                        cout << "[ERROR] Opsi tidak valid!\n";
                    }
                } while (adminMenu != 4);
            } else {
                cout << "[GAGAL] Akun Admin tidak ditemukan atau password salah!\n";
            }

        } else if (pilihan == 2) {
            string username, password, userId;
            cout << "\n--- LOGIN PESERTA ---" << endl;
            cout << "Username: "; cin >> username;
            cout << "Password: "; cin >> password;

            if (authenticateUser(username, password, "PESERTA", userId)) {
                Peserta pesertaObj(userId, username, password);
                int pesertaMenu;
                do {
                    pesertaObj.displayMenu();
                    cout << "Pilih opsi Peserta: ";
                    pesertaMenu = getValidIntInput();

                    if (pesertaMenu == 1) {
                        pesertaObj.registerTeam();
                    } else if (pesertaMenu == 2) {
                        cout << "[INFO] Silakan hubungi Admin atau cek status di teams.csv.\n";
                        pesertaObj.confirmPayment(); // Panggil method konfirmasi pembayaran jika sudah ditambahkan di Peserta.h
                        // Panggil method konfirmasi pembayaran jika sudah ditambahkan di Peserta.h
                    } else if (pesertaMenu == 3) {
                        cout << "[INFO] Menampilkan data dari matches.csv...\n";
                        pesertaObj.viewMatches(); // Panggil method lihat jadwal jika sudah ditambahkan di Peserta.h
                        // Panggil method lihat jadwal jika sudah ditambahkan di Peserta.h
                    } else if (pesertaMenu != 4) {
                        cout << "[ERROR] Opsi tidak valid!\n";
                    }
                } while (pesertaMenu != 4);
            } else {
                cout << "[GAGAL] Akun Peserta tidak ditemukan atau password salah!\n";
            }

        } else if (pilihan == 3) {
            cout << "\n--- DEMO POLIMORFISME & PRIZEPOOL ENGINE ---" << endl;
            
            // Array of Base Class Pointers untuk menunjukkan Polimorfisme nyata
            Tournament* daftarTurnamen[2];
            daftarTurnamen[0] = new SingleEliminationTournament("TRN01", "Predator League 2026", 16);
            daftarTurnamen[1] = new RoundRobinTournament("TRN02", "Samarinda Pro Series", 8);

            for (int i = 0; i < 2; i++) {
                daftarTurnamen[i]->generateBracket();
                daftarTurnamen[i]->calculatePrizePool(5000000);
                delete daftarTurnamen[i]; // Bersihkan memory
            }

        } else if (pilihan == 4) {
            cout << "\nTerima kasih telah menggunakan program ini, bro!\n";
        } else {
            cout << "[INFO] Pilihan tidak valid, coba lagi.\n";
        }

    } while (pilihan != 4);

    return 0;
}