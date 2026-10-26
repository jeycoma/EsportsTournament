#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <string>
#include <vector>

using namespace std;

class Tournament {
protected:
    string tournamentId;
    string title;
    int maxSlots;

public:
    Tournament(string id, string t, int slots) : tournamentId(id), title(t), maxSlots(slots) {}
    virtual ~Tournament() {}

    // Pure Virtual Function untuk Polimorfisme skema turnamen
    virtual void generateBracket() = 0;
    virtual void calculatePrizePool(long totalMoney) = 0;
};

#endif