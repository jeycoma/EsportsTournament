#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "CsvHandler.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Admin : public User {
public:
    Admin(string p_id, string p_uname, string p_pass)
        : User(p_id, p_uname, p_pass, "ADMIN") {}

    void displayMenu() override {
        cout << "\n=== MENU ADMIN / PENYELENGGARA ===" << endl;
        cout << "1. Buat Turnamen Baru" << endl;
        cout << "2. Atur Jadwal Pertandingan" << endl;
        cout << "3. Input / Update Hasil Pertandingan" << endl;
        cout << "4. Keluar" << endl;
    }

    void showProfile() override {
        cout << "Admin ID: " << id << " | Username: " << username << " | Role: ADMIN" << endl;
    }

    // Fitur 1: Membuat Turnamen Baru
    void createTournament() {
        string tId, title, formatStr;
        int formatChoice, maxSlots;
        long fee, prizepool;

        cout << "\n--- BUAT TURNAMEN BARU ---\n";
        cout << "Masukkan ID Turnamen (Contoh: TRN01): ";
        cin >> tId;
        cin.ignore();
        cout << "Masukkan Nama Turnamen: ";
        getline(cin, title);

        cout << "Pilih Format (1. SingleElimination / 2. RoundRobin): ";
        cin >> formatChoice;
        formatStr = (formatChoice == 2) ? "RoundRobin" : "SingleElimination";

        cout << "Maksimal Slot Tim: ";
        cin >> maxSlots;
        cout << "Biaya Registrasi (Rp): ";
        cin >> fee;
        cout << "Total Prizepool (Rp): ";
        cin >> prizepool;

        vector<string> row = {tId, title, formatStr, to_string(maxSlots), to_string(fee), to_string(prizepool), "ONGOING"};
        CsvHandler::appendToCSV("data/tournaments.csv", row);
        cout << "[SUKSES] Turnamen \"" << title << "\" (" << formatStr << ") berhasil dibuat!\n";
    }

    // Fitur 2: Atur Jadwal Pertandingan Baru
    void scheduleMatch() {
        string matchId, trnId, round, tId1, tId2;

        cout << "\n--- ATUR JADWAL PERTANDINGAN ---\n";
        cout << "Masukkan Match ID (Contoh: M01): ";
        cin >> matchId;
        cout << "Masukkan Tournament ID (Contoh: TRN01): ";
        cin >> trnId;
        cin.ignore();
        cout << "Babak / Round (Contoh: Round 1): ";
        getline(cin, round);
        cout << "ID Tim 1: ";
        cin >> tId1;
        cout << "ID Tim 2: ";
        cin >> tId2;

        // Skor awal 0 vs 0, pemenang TBD
        vector<string> row = {matchId, trnId, round, tId1, tId2, "0", "0", "TBD"};
        CsvHandler::appendToCSV("data/matches.csv", row);
        cout << "[SUKSES] Jadwal match " << matchId << " (" << tId1 << " vs " << tId2 << ") tersimpan!\n";
    }

    // Fitur 3: Update Hasil Match yang Sudah Dijadwalkan
    void inputMatchResult() {
        string matchId, winnerId;
        int score1, score2;

        cout << "\n--- INPUT HASIL PERTANDINGAN ---\n";
        cout << "Masukkan Match ID yang ingin diupdate (Contoh: M01): ";
        cin >> matchId;

        vector<vector<string>> matches = CsvHandler::readCSV("data/matches.csv");
        bool found = false;

        for (size_t i = 1; i < matches.size(); ++i) {
            if (matches[i].size() >= 8 && matches[i][0] == matchId) {
                found = true;
                cout << "Match Ditemukan: " << matches[i][3] << " vs " << matches[i][4] << " (" << matches[i][2] << ")\n";
                cout << "Skor " << matches[i][3] << ": ";
                cin >> score1;
                cout << "Skor " << matches[i][4] << ": ";
                cin >> score2;
                cout << "Masukkan ID Tim Pemenang: ";
                cin >> winnerId;

                matches[i][5] = to_string(score1);
                matches[i][6] = to_string(score2);
                matches[i][7] = winnerId;
                break;
            }
        }

        if (found) {
            CsvHandler::overwriteCSV("data/matches.csv", matches);
            cout << "[SUKSES] Hasil pertandingan " << matchId << " berhasil diperbarui!\n";
        } else {
            cout << "[GAGAL] Match ID " << matchId << " tidak ditemukan di jadwal!\n";
        }
    }
};

#endif