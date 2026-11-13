# ifndef CSV_HANDLER_H
# define CSV_HANDLER_H

# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>
# include <string>

using namespace std;

class CsvHandler {
public:
    // Fungsi untuk membaca isi file CSV dan mengembalikannya dalam bentuk vector 2D (baris dan kolom)
    static vector<vector<string>> readCSV(const string& filename) {
        vector<vector<string>> data;
        ifstream file(filename);
        string line;

        if (!file.is_open()) {
            // Kalau file belum ada, biarkan return kosong atau buat baru nanti
            return data;
        }

        while (getline(file, line)) {
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

    // Fungsi untuk menulis / menambah baris data baru ke file CSV (Append mode)
    static void appendToCSV(const string& filename, const vector<string>& rowData) {
        ofstream file(filename, ios::app); // ios::app agar data lama tidak tertimpa
        if (file.is_open()) {
            for (size_t i = 0; i < rowData.size(); ++i) {
                file << rowData[i];
                if (i < rowData.size() - 1) {
                    file << ",";
                }
            }
            file << "\n";
            file.close();
        } else {
            cout << "Gagal membuka file " << filename << " untuk ditulis!\n";
        }
    }

    // (Opsional) Fungsi rewrite seluruh file jika ada data yang di-update/hapus
    static void overwriteCSV(const string& filename, const vector<vector<string>>& allData) {
        ofstream file(filename, ios::trunc); // ios::trunc menghapus isi lama dan tulis ulang
        if (file.is_open()) {
            for (const auto& row : allData) {
                for (size_t i = 0; i < row.size(); ++i) {
                    file << row[i];
                    if (i < row.size() - 1) file << ",";
                }
                file << "\n";
            }
            file.close();
        }
    }
};

# endif