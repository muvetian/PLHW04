/*
 * NicePlayer.h
 *
 *  Created on: Apr 16, 2018
 *      Author: mutian
 */

#ifndef NicePlayer_H_
#define NicePlayer_H_
#include "player.h"
#include "shedgame.h"
class NicePlayer: public Player{
public:
	NicePlayer(ShedGame&, const string&);
    void reset();              // Issued just before dealing.
    void prepare();            // Issued just before game starts, after dealing.
    ShedGame::Option ask();    // What do you want to do?
    void take(const Card&);    // Take this card.
    Card::Suit setSuit();      // Issued after playing a wild card.
    Card playCard();           // What card do you want to play?
    void inform(int p, int s, int t); // Player with id p is in stage s and has t cards.
    void updatePlayerStages(int p, int s);
    void disqualified(int p);  // Player with id p has been disqualified.
private:
    bool isQualified;
    vector<int> playerStages;
    int cardToPlay;
};


#endif /* NicePlayer_H_ */
