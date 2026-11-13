#ifndef SINGLE_ELIMINATION_TOURNAMENT_H
#define SINGLE_ELIMINATION_TOURNAMENT_H

#include "Tournament.h"
#include <iostream>

using namespace std;

class SingleEliminationTournament : public Tournament {
public:
    SingleEliminationTournament(string id, string t, int slots)
        : Tournament(id, t, slots) {}

    void generateBracket() override {
        cout << "\n--- GENERATING SINGLE ELIMINATI-ON BRACKET ---\n";
        cout << "Turnamen: " << title << " (Max Slot: " << maxSlots << ")\n";
        cout << "[INFO] Sistem Gugur: Tim yang kalah otomatis tereliminasi di babak ini.\n";
    }

    void calculatePrizePool(long totalMoney) override {
        cout << "\n=== DISTRIBUSI PRIZEPOOL (SINGLE ELIMINATION) ===\n";
        cout << "Total Prizepool: Rp " << totalMoney << "\n";
        cout << "1. Juara 1 (50%) : Rp " << (totalMoney * 0.50) << "\n";
        cout << "2. Juara 2 (30%) : Rp " << (totalMoney * 0.30) << "\n";
        cout << "3. Juara 3 (15%) : Rp " << (totalMoney * 0.15) << "\n";
        cout << "4. MVP Player (5%): Rp " << (totalMoney * 0.05) << "\n";
    }
};

#endif