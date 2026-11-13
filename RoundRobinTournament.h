#ifndef ROUND_ROBIN_TOURNAMENT_H
#define ROUND_ROBIN_TOURNAMENT_H

#include "Tournament.h"
#include <iostream>

using namespace std;

class RoundRobinTournament : public Tournament {
public:
    RoundRobinTournament(string id, string t, int slots)
        : Tournament(id, t, slots) {}

    void generateBracket() override {
        cout << "\n--- GENERATING ROUND ROBIN (GROUP STAGE) ---\n";
        cout << "Turnamen: " << title << " (Max Slot: " << maxSlots << ")\n";
        cout << "[INFO] Sistem Liga: Setiap tim akan saling bertemu dalam klasemen grup.\n";
    }

    void calculatePrizePool(long totalMoney) override {
        cout << "\n=== DISTRIBUSI PRIZEPOOL (ROUND ROBIN) ===\n";
        cout << "Total Prizepool: Rp " << totalMoney << "\n";
        cout << "1. Juara Grup (60%): Rp " << (totalMoney * 0.60) << "\n";
        cout << "2. Runner Up (30%) : Rp " << (totalMoney * 0.30) << "\n";
        cout << "3. Best Fair Play(10%): Rp " << (totalMoney * 0.10) << "\n";
    }
};

#endif