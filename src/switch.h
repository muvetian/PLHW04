/*
 * switch.h
 *
 *  Created on: Apr 16, 2018
 *      Author: mutian
 */

#ifndef SWITCH_H_
#define SWITCH_H_
#include "card.h"
#include "shedgame.h"
class Switch: public ShedGame{
public:
	 Switch();
	 bool isDrawTwo(const Card&) const;
	 bool isDrawFive(const Card&) const;
	 bool isBurner(const Card&) const;
	 bool isReverser(const Card&) const;
	 bool isSkipper(const Card&) const;
	 bool isWild(const Card&) const;
	 bool isCancel(const Card&) const;
	 int handSize() const;


};




#endif /* SWITCH_H_ */
