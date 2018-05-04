/*
 * NicePlayer.cpp
 *
 *  Created on: Apr 18, 2018
 *      Author: mutian
 */

#include "NicePlayer.h"

NicePlayer::NicePlayer(ShedGame& g, const string& nm):Player(g,nm){
	isQualified = true;
	playerStages.reserve(game.numPlayers());
	cardToPlay = -2;
}

void NicePlayer::reset(){
	// Issued just before dealing.
	while (!hand.empty()) hand.pop_back();
}
void NicePlayer::prepare(){
	// Issued just before game starts, after dealing.
	isQualified = true;


}
ShedGame::Option NicePlayer::ask(){
	// What do you want to do?
	//	return ShedGame::Done; // ??? what is this for???
	if (isQualified == false){
		return ShedGame::Done;
	}
	else if (this->hand.size() == 0 && playerStages[this->getId()] == 0){
		return ShedGame::Win;
	}
	if(game.getContract() > 0){
		bool have_cancel = false;
		for(int i = 0; i < this->hand.size();i++){
			if(game.isCancel(this->hand[i])){
				this->cardToPlay = i;
				have_cancel = true;
				return ShedGame::PlayCard;
			}

		}
		if(!have_cancel){
			for(int i = 0; i < this->hand.size();i++){
				if(game.isDrawFive(this->hand[i]) || game.isDrawTwo(this->hand[i])){ // brutal evil play who always prioritize drawFive
					this->cardToPlay = i;
					return ShedGame::PlayCard;
				}
			}
			cout << "no draw or cancel, drawing now.";
			return ShedGame::GetCard;
		}


	}
	else{ // if you do not have a contract
		for(int i = 0; i < this->hand.size(); i++){
			if(this->hand[i].getRank() == game.getCurRank() || this->hand[i].getSuit() == game.getCurSuit()){
				this->cardToPlay = i;
				cout << "Found the matching card !!!"<< endl;
				return ShedGame::PlayCard;


			}
		}
		return ShedGame::GetCard;

	}
	return ShedGame::Done;
}
void NicePlayer::take(const Card& c){
	this->hand.push_back(c);
	// Take this card.
}
Card::Suit NicePlayer::setSuit(){
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
void NicePlayer::updatePlayerStages(int p, int s){
	playerStages[p] = s;
}
Card NicePlayer::playCard(){
	cout << "This is player:" << getName()<<"\n";
	cout << "Card to Play Index:" << cardToPlay;
	cout << "Card to play:" << this->hand[cardToPlay];
//	hand.erase(hand.begin() + cardToPlay);
	return this->hand[cardToPlay]; // This will never happen, hand[0] is used as a placeholder

	// What card do you want to play?
}
void NicePlayer::inform(int p, int s, int t){
	// Player with id p is in stage s and has t cards.
	//	ShedGame::net[p] = t; // set the current size of the hand for this player
	//	game.stage[p] = s; // set the current stage for this player
	game.getPlayer(p)->updatePlayerStages(this->getId(), s);
}
void NicePlayer::disqualified(int p){
	// Player with id p has been disqualified.
	if (this->getId() == p){
		isQualified = false;
	}

}

