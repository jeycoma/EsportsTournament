#ifndef PESERTA_H
#define PESERTA_H

#include "User.h"
#include "CsvHandler.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Team {
private:
    string teamId;
    string teamName;
    string captainId;
    vector<string> rosterPemain;
    string paymentStatus;

public:
    Team(string tId, string tName, string cId, vector<string> players) {
        teamId = tId;
        teamName = tName;
        captainId = cId;
        rosterPemain = players;
        paymentStatus = "PENDING";
    }

    string getTeamId() const { return teamId; }
    string getTeamName() const { return teamName; }
    string getPaymentStatus() const { return paymentStatus; }
    void setPaymentStatus(string status) { paymentStatus = status; }

    vector<string> toCsvRow() const {
        vector<string> row = {teamId, teamName, captainId};
        for (const string& p : rosterPemain) {
            row.push_back(p);
        }
        row.push_back(paymentStatus);
        return row;
    }
};

class Peserta : public User {
private:
    string registeredTeamId;

public:
    Peserta(string p_id, string p_uname, string p_pass)
        : User(p_id, p_uname, p_pass, "PESERTA") {
        registeredTeamId = "";
    }

    void displayMenu() override {
        cout << "\n=== MENU PESERTA / KAPTEN TIM ===" << endl;
        cout << "1. Buat / Daftarkan Tim & Roster" << endl;
        cout << "2. Konfirmasi Pembayaran Registrasi" << endl;
        cout << "3. Lihat Jadwal & Hasil Pertandingan" << endl;
        cout << "4. Keluar" << endl;
    }

    void showProfile() override {
        cout << "Peserta ID: " << id << " | Username: " << username
             << " | Team ID: " << (registeredTeamId.empty() ? "Belum Ada" : registeredTeamId) << endl;
    }

    // Fitur 1: Mendaftarkan Tim Baru
    void registerTeam() {
        string tId, tName;
        vector<string> players(4);

        cout << "\n--- PENDAFTARAN TIM BARU ---\n";
        cout << "Masukkan ID Tim (Contoh: T001): ";
        cin >> tId;
        cin.ignore();
        cout << "Masukkan Nama Tim Esports: ";
        getline(cin, tName);

        cout << "Masukkan Nama 4 Anggota Roster (Kapten otomatis: " << username << "):\n";
        for (int i = 0; i < 4; i++) {
            cout << "Pemain " << (i + 2) << ": ";
            getline(cin, players[i]);
        }

        Team newTeam(tId, tName, this->id, players);
        CsvHandler::appendToCSV("data/teams.csv", newTeam.toCsvRow());
        registeredTeamId = tId;

        cout << "[SUKSES] Tim " << tName << " (" << tId << ") terdaftar dengan status PENDING.\n";
    }

    // Fitur 2: Konfirmasi Pembayaran Tim Milik Kapten Ini
    void confirmPayment() {
        vector<vector<string>> teams = CsvHandler::readCSV("data/teams.csv");
        bool updated = false;

        for (size_t i = 1; i < teams.size(); ++i) {
            if (teams[i].size() >= 8 && teams[i][2] == this->id) {
                if (teams[i][7] == "PAID") {
                    cout << "[INFO] Pembayaran untuk tim " << teams[i][1] << " sudah lunas (PAID) sebelumnya.\n";
                    return;
                }
                teams[i][7] = "PAID";
                registeredTeamId = teams[i][0];
                updated = true;
                cout << "[SUKSES] Pembayaran untuk tim " << teams[i][1] << " (" << teams[i][0] << ") berhasil dikonfirmasi (PAID)!\n";
                break;
            }
        }

        if (updated) {
            CsvHandler::overwriteCSV("data/teams.csv", teams);
        } else {
            cout << "[GAGAL] Kamu belum mendaftarkan tim! Silakan pilih menu 1 dulu.\n";
        }
    }

    // Fitur 3: Lihat Jadwal & Hasil Pertandingan
    void viewMatches() {
        vector<vector<string>> matches = CsvHandler::readCSV("data/matches.csv");
        cout << "\n=== JADWAL & HASIL PERTANDINGAN ===\n";

        if (matches.size() <= 1) {
            cout << "[INFO] Belum ada jadwal pertandingan yang dibuat Admin.\n";
            return;
        }

        for (size_t i = 1; i < matches.size(); ++i) {
            if (matches[i].size() >= 8) {
                cout << "[" << matches[i][0] << "] " << matches[i][1] << " - " << matches[i][2]
                     << " | " << matches[i][3] << " (" << matches[i][5] << ") vs (" << matches[i][6] << ") " << matches[i][4]
                     << " | Winner: " << matches[i][7] << "\n";
            }
        }
    }
};

#endif