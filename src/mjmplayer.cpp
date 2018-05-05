/*
 * mjmplayer.cpp
 *
 *  Created on: Apr 18, 2018
 *      Author: mutian
 */

#include "mjmplayer.h"

MJMPlayer::MJMPlayer(ShedGame& g, const string& nm):Player(g,nm){
	isQualified = true;
	cardToPlay = -2;
	ifPlayed = false;
	myStage = game.handSize();
	cardsToDraw = 0;
	fillingContract = false;
	burning = false;
	firstFill = false;
	isRestocked = false;
	for(int i = 0; i < game.numPlayers();i++){
		playerStages.push_back(0);

	}
}

void MJMPlayer::restocked(){
	isRestocked = true;
}
void MJMPlayer::reset(){
	// Issued just before dealing.
	while (!hand.empty()) hand.pop_back();
}
void MJMPlayer::prepare(){
	// Issued just before game starts, after dealing.
	isQualified = true;
	cardToPlay = -2;
	ifPlayed = false;
	myStage = game.handSize();
	cardsToDraw = 0;
	fillingContract = false;
	burning = false;
	firstFill = true;


}
ShedGame::Option MJMPlayer::ask(){
	if (hand.size() == 0 && myStage > 0){
		myStage = myStage - 1;
		cout << "["<< getName()<<":Stage "<< myStage <<"!]"<<endl;
		cardsToDraw = myStage;
	}
	if(cardsToDraw > 0){
		cardsToDraw = cardsToDraw - 1;
		return ShedGame::GetCard;
	}
	else if (hand.size() == 0 && myStage == 0){
		return ShedGame::Win;
	}
	else if(ifPlayed == true && !burning){
		ifPlayed = false;
		firstFill = true;
		return ShedGame::Done;
	}
	if(game.getContract() > 0 && cardsToDraw == 0){
		Card currentCard = Card(game.getCurRank(), game.getCurSuit());
		if(firstFill){
			firstFill = false;
			bool have_cancel = false;
			for(int i = 0; i < hand.size();i++){
				if(game.isCancel(hand[i])){
					if(game.isDrawFive(currentCard)){
						cardToPlay = i;
						have_cancel = true;
						ifPlayed = true;
						return ShedGame::PlayCard;
					}

				}

			}
			if(!have_cancel){

				for(int i = 0; i < hand.size();i++){
					if(game.isDrawFive(currentCard) && game.isDrawFive(hand[i])){
						cardToPlay = i;
						ifPlayed = true;
						return ShedGame::PlayCard;
					}
					if(game.isDrawTwo(currentCard) && game.isDrawTwo(hand[i])){ // brutal evil play who always prioritize drawFive
						cardToPlay = i;
						ifPlayed = true;
						return ShedGame::PlayCard;
					}
				}

			}
			fillingContract = true;
			return ShedGame::GetCard;

		}
		else{
			fillingContract = true;
			firstFill = false;
			return ShedGame::GetCard;
		}










	}
	else if(fillingContract == false){ // if you do not have a contract
		for(int i = 0; i < hand.size(); i++){

			if(burning){
				if (game.isWild(hand[i])){
					cardToPlay = i;
					ifPlayed = true;
					burning = false;
					return ShedGame::PlayCard;
				}
				else if(hand[i].getSuit() == burner.getSuit()){
					cardToPlay = i;
					ifPlayed = true;
					return ShedGame::PlayCard;
				}

			}
			else{
				if(hand[i].getRank() == game.getCurRank() || hand[i].getSuit() == game.getCurSuit()){
					cardToPlay = i;
					if(game.isBurner(hand[i])){
						burner = hand[i];
						burning = true;
					}


					ifPlayed = true;
					return ShedGame::PlayCard;


				}
				else if (game.isWild(hand[i])){
					cardToPlay = i;
					ifPlayed = true;
					return ShedGame::PlayCard;
				}
			}
		}
		if(burning){
			burning = false;
			ifPlayed = false;
			firstFill = true;
			return ShedGame::Done;
		}
		else{

			return ShedGame::GetCard;
		}




	}
	fillingContract = false;
	firstFill = true;
	return ShedGame::Done;
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

	Card cardToReturn = hand[cardToPlay];
	hand.erase(hand.begin()+cardToPlay);
	return cardToReturn;
}
void MJMPlayer::inform(int p, int s, int t){
	cout << "The Player "<< p << " is at Stage "<< s<<" and has " << t <<" cards."<<endl;

}
void MJMPlayer::disqualified(int p){
	if (getId() == p){
		isQualified = false;
	}

}

