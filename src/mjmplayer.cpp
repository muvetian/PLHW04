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
	// What do you want to do?
	//	return ShedGame::Done; // ??? what is this for???
	cout << "THe contract on me is:" << game.getContract()<< endl;
	cout << "The first fille for me is:" << firstFill << endl;
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
		cout << "Played and not burning";
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
						cout << "Canceld contract using cancel" << endl;
						return ShedGame::PlayCard;
					}

				}

			}
			if(!have_cancel){

				for(int i = 0; i < hand.size();i++){
					if(game.isDrawFive(currentCard) && game.isDrawFive(hand[i])){
						cardToPlay = i;
						ifPlayed = true;
						cout << "Canceld contract using draw 5" << endl;
						return ShedGame::PlayCard;
					}
					if(game.isDrawTwo(currentCard) && game.isDrawTwo(hand[i])){ // brutal evil play who always prioritize drawFive
						cardToPlay = i;
						ifPlayed = true;
						cout << "Canceld contract using draw 2" << endl;
						return ShedGame::PlayCard;
					}
				}

			}
			cout << "no draw or cancel, drawing now.";
			fillingContract = true;
			return ShedGame::GetCard;

		}
		else{
			cout << "not the first time filling contract";
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
					cout << "burning finished because of wild card"<<endl;
					return ShedGame::PlayCard;
				}
				else if(hand[i].getSuit() == burner.getSuit()){
					cardToPlay = i;
					ifPlayed = true;
					return ShedGame::PlayCard;
				}

			}
			else{
				//				cout << "the size of the hand right now :" << hand.size() << endl;
				//				cout << "the hand[i] right now:" << hand[i] << endl;
				//				cout << "card to play is :" << cardToPlay<<endl;
				if(hand[i].getRank() == game.getCurRank() || hand[i].getSuit() == game.getCurSuit()){
					//				cout << "PLAYER:"<< getName()<<" ";
					cout << "I am here!" << endl;
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

		cout << "Do not have card to play" <<endl;
		printHand();
		if(burning){
			burning = false;
			ifPlayed = false;
			cout << "burning finished"<<endl;
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
void MJMPlayer::updatePlayerStages(int p, int s){

}
Card MJMPlayer::playCard(){
	//	cout << "This is player:" << getName()<<"\n";
	//	cout << "Card to Play Index:" << cardToPlay;
	//	cout << "Card to play:" << hand[cardToPlay];
	//	hand.erase(hand.begin() + cardToPlay);
	//	return hand[cardToPlay]; // This will never happen, hand[0] is used as a placeholder
	//	for(int i = 0; i < hand.size(); i++){
	//		if(hand[i].getRank() == game.getCurRank() || hand[i].getSuit() == game.getCurSuit()){
	//
	//			Card cardToReturn = hand[i];
	//			hand.erase(hand.begin() + i);
	//			return cardToReturn;
	//
	//
	//		}
	//	}

	Card cardToReturn = hand[cardToPlay];
	hand.erase(hand.begin()+cardToPlay);
	return cardToReturn;

	// What card do you want to play?
}
void MJMPlayer::inform(int p, int s, int t){
	// Player with id p is in stage s and has t cards.
	//	ShedGame::net[p] = t; // set the current size of the hand for this player
	//	game.stage[p] = s; // set the current stage for this player
	//	game.getPlayer(p)->updatePlayerStages(getId(), s);
}
void MJMPlayer::disqualified(int p){
	// Player with id p has been disqualified.
	if (getId() == p){
		isQualified = false;
	}

}

