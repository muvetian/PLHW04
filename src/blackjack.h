/*
 * blackjack.h
 *
 *  Created on: Apr 16, 2018
 *      Author: mutian
 */
#include "shedgame.h"
#include "card.h"
#ifndef BLACKJACK_H_
#define BLACKJACK_H_
class BlackJack: public ShedGame{
public:
	 BlackJack();
	 bool isDrawTwo(const Card&) const;
	 bool isDrawFive(const Card&) const;
	 bool isBurner(const Card&) const;
	 bool isReverser(const Card&) const;
	 bool isSkipper(const Card&) const;
	 bool isWild(const Card&) const;
	 bool isCancel(const Card&) const;
	 int handSize() const;


};





#endif /* BLACKJACK_H_ */
