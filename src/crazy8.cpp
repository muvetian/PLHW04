/*
 * crazy8.cpp
 *
 *  Created on: Apr 18, 2018
 *      Author: mutian
 */
#include "crazy8.h"

Crazy8::Crazy8():ShedGame("CrazyEight"){

}
bool Crazy8::isWild(const Card& c) const{
	if(c.getRank() == Card::eight){
		return true;
	}
	else{
		return false;
	}
}

bool Crazy8::isDrawTwo(const Card& c) const{
	if(c.getRank() == Card::two){
		return true;
	}
	else{
		return false;
	}

}

bool Crazy8::isDrawFive(const Card& c) const{
	if(c.getRank() == Card::queen && c.getSuit() == Card::spades){
		return true;
	}
	else{
		return false;
	}

}
bool Crazy8::isBurner(const Card& c) const{
	if((c.getRank() == Card::four && (c.getSuit() == Card::hearts || c.getSuit() == Card::diamonds)) ||
			(c.getRank() == Card::five &&(c.getSuit() == Card::spades || c.getSuit() == Card::clubs))){
		return true;
	}
	else{
		return false;
	}
}
bool Crazy8::isReverser(const Card& c) const{
	if(c.getRank() == Card::queen){
		return true;
	}
	else{
		return false;
	}
}
bool Crazy8::isSkipper(const Card& c) const{
	if(c.getRank() == Card::ace){
		return true;
	}
	else{
		return false;
	}
}
bool Crazy8::isCancel(const Card& c) const{
	if(c.getRank() == Card::king && c.getSuit() == Card::diamonds){
		return true;
	}
	else{
		return false;
	}
}
int Crazy8::handSize() const{
	return 8;
}
