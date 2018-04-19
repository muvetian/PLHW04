/*
 * switch.cpp
 *
 *  Created on: Apr 18, 2018
 *      Author: mutian
 */
#include "switch.h"
Switch::Switch():ShedGame("IrishSwitch"){

}
bool Switch::isWild(const Card& c) const{
	if(c.getRank() == Card::ace){
		return true;
	}
	else{
		return false;
	}
}

bool Switch::isDrawTwo(const Card& c) const{
	if(c.getRank() == Card::four){
		return true;
	}
	else{
		return false;
	}

}

bool Switch::isDrawFive(const Card& c) const{
	if(c.getRank() == Card::king && (c.getSuit() == Card::spades || c.getSuit() == Card::clubs)){
		return true;
	}
	else{
		return false;
	}

}
bool Switch::isBurner(const Card& c) const{
	return false;
}
bool Switch::isReverser(const Card& c) const{
	if(c.getRank() == Card::jack){
		return true;
	}
	else{
		return false;
	}
}
bool Switch::isSkipper(const Card& c) const{
	if(c.getRank() == Card::seven){
		return true;
	}
	else{
		return false;
	}
}
bool Switch::isCancel(const Card& c) const{
	if(c.getRank() == Card::king && (c.getSuit() == Card::diamonds || c.getSuit() == Card::hearts)){
		return true;
	}
	else{
		return false;
	}
}
int Switch::handSize() const{
	return 7;
}




