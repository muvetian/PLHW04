/*
 * mjmplayer.cpp
 *
 *  Created on: Apr 18, 2018
 *      Author: mutian
 */

#include "mjmplayer.h"

MJMPlayer::MJMPlayer(ShedGame& g, const string& nm):Player(g,nm){
}

void MJMPlayer::reset(){
	// Issued just before dealing.
}
void MJMPlayer::prepare(){           // Issued just before game starts, after dealing.

}
ShedGame::Option MJMPlayer::ask(){
	// What do you want to do?
}
void MJMPlayer::take(const Card& c){
	hand.push_back(c);
	// Take this card.
}
Card::Suit MJMPlayer::setSuit(){

	// Issued after playing a wild card.
}
Card MJMPlayer::playCard(){
	// What card do you want to play?
}
void MJMPlayer::inform(int p, int s, int t){
	// Player with id p is in stage s and has t cards.
}
void MJMPlayer::disqualified(int p){
	// Player with id p has been disqualified.
}

