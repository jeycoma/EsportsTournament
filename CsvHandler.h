#ifndef CSV_HANDLER_H
#define CSV_HANDLER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(dir) _mkdir(dir)
#else
    #include <sys/stat.h>
    #define MKDIR(dir) mkdir(dir, 0777)
#endif

using namespace std;

class CsvHandler {
private:
    static void ensureDirectoryExists(const string& filename) {
        size_t pos = filename.find_last_of("/\\");
        if (pos != string::npos) {
            string dir = filename.substr(0, pos);
            MKDIR(dir.c_str()); // Otomatis bikin folder jika belum ada
        }
    }

public:
    static vector<vector<string>> readCSV(const string& filename) {
        vector<vector<string>> data;
        ifstream file(filename);
        string line;

        if (!file.is_open()) return data;

        while (getline(file, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string cell;
            vector<string> row;

            while (getline(ss, cell, ',')) {
                row.push_back(cell);
            }
            data.push_back(row);
        }
        file.close();
        return data;
    }

    static void appendToCSV(const string& filename, const vector<string>& rowData) {
        ensureDirectoryExists(filename);
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            for (size_t i = 0; i < rowData.size(); ++i) {
                file << rowData[i];
                if (i < rowData.size() - 1) file << ",";
            }
            file << "\n";
            file.close();
        } else {
            cout << "[ERROR] Gagal membuka file " << filename << "\n";
        }
    }

    static void overwriteCSV(const string& filename, const vector<vector<string>>& allData) {
        ensureDirectoryExists(filename);
        ofstream file(filename, ios::trunc);
        if (file.is_open()) {
            for (const auto& row : allData) {
                for (size_t i = 0; i < row.size(); ++i) {
                    file << row[i];
                    if (i < row.size() - 1) file << ",";
                }
                file << "\n";
            }
            file.close();
        } else {
            cout << "[ERROR] Gagal menulis ulang file " << filename << "\n";
        }
    }
};

#endif