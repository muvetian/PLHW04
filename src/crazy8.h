/*
 * crazy8.h
 *
 *  Created on: Apr 16, 2018
 *      Author: mutian
 */
#include "shedgame.h"
#include "card.h"
#ifndef CRAZY8_H_
#define CRAZY8_H_

class Crazy8: public ShedGame{
public:
	 Crazy8();
	 bool isDrawTwo(const Card&) const;
	 bool isDrawFive(const Card&) const;
	 bool isBurner(const Card&) const;
	 bool isReverser(const Card&) const;
	 bool isSkipper(const Card&) const;
	 bool isWild(const Card&) const;
	 bool isCancel(const Card&) const;
	 int handSize() const;


};



#endif /* CRAZY8_H_ */
