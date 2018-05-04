/*
 * mjmplayer.h
 *
 *  Created on: Apr 16, 2018
 *      Author: mutian
 */

#ifndef MJMPLAYER_H_
#define MJMPLAYER_H_
#include "player.h"
#include "shedgame.h"
class MJMPlayer: public Player{
public:
	MJMPlayer(ShedGame&, const string&);
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
    bool ifPlayed;
    int myStage;
    int cardsToDraw;
    int cardToPlay;
    bool fillingContract;
    bool burning;
    Card burner;
};


#endif /* MJMPLAYER_H_ */
