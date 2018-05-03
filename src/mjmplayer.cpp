/*
 * mjmplayer.cpp
 *
 *  Created on: Apr 18, 2018
 *      Author: mutian
 */

#include "mjmplayer.h"

MJMPlayer::MJMPlayer(ShedGame& g, const string& nm):Player(g,nm){
	isQualified = true;
}

void MJMPlayer::reset(){
	// Issued just before dealing.
	while (!hand.empty()) hand.pop_back();
}
void MJMPlayer::prepare(){
	// Issued just before game starts, after dealing.
	isQualified = true;


}
ShedGame::Option MJMPlayer::ask(){
	// What do you want to do?

	//	return ShedGame::Done; // ??? what is this for???
	if (isQualified == false){
		return ShedGame::Done;
	}
	else if (hand.size() == 0){
		return ShedGame::Win;
	}
	else{
		for(int i = 0; i < hand.size(); i++){
			if(hand[i].getRank() == game.getCurRank() || hand[i].getSuit() == game.getCurSuit()){
				return ShedGame::PlayCard;
			}
			else{
				return ShedGame::GetCard;
			}
		}
		return ShedGame::Done;

	}



}
void MJMPlayer::take(const Card& c){
	hand.push_back(c);
	// Take this card.
}
Card::Suit MJMPlayer::setSuit(){
	vector<int> suitCount(4,0);

	for (int i = 0; i < hand.size(); i++){
		if(hand[i].getSuit() == Card::spades){
			suitCount[0] ++;
		}
		else if(hand[i].getSuit() == Card::clubs){
			suitCount[1] ++;
		}
		else if(hand[i].getSuit() == Card::diamonds){
			suitCount[2] ++;

		}
		else{
			suitCount[3] ++;

		}
	}
	int highest_index = -1;
	int highest_count = 0;
	for(int i = 0; i < suitCount.size(); i++){
		if (suitCount[i] > highest_count){
			highest_index = i;
			highest_count = suitCount[i];
		}
	}
	if(highest_index == 0){
		return Card::spades;
	}
	else if(highest_index == 1){
		return Card::clubs;
	}
	else if(highest_index == 2){
		return Card::diamonds;
	}
	else{
		return Card::hearts;
	}

	// Issued after playing a wild card.
}
Card MJMPlayer::playCard(){
	for(int i = 0; i < hand.size(); i++){
		if(hand[i].getRank() == game.getCurRank() || hand[i].getSuit() == game.getCurSuit()){
			hand.erase(hand.begin() + i); // delete this entry from the hand
			return hand[i];
		}
	}
	return hand[0]; // This will never happen, hand[0] is used as a placeholder

	// What card do you want to play?
}
void MJMPlayer::inform(int p, int s, int t){
	// Player with id p is in stage s and has t cards.
	game.net[p] = t; // set the current size of the hand for this player
	game.stage[p] = s; // set the current stage for this player
}
void MJMPlayer::disqualified(int p){
	// Player with id p has been disqualified.
	if (this->getId() == p){
		isQualified = false;
	}

}

