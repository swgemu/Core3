/*
 * CommandEffect.h
 *
 *  Created on: Jan 18, 2012
 *      Author: da
 */

#ifndef COMMANDEFFECT_H_
#define COMMANDEFFECT_H_

class CommandEffect {
public:
	static const uint8 INVALID = 0;
	static const uint8 BLIND = 1;
	static const uint8 DIZZY = 2;
	static const uint8 INTIMIDATE = 3;
	static const uint8 STUN = 4;
	static const uint8 KNOCKDOWN = 5;
	static const uint8 POSTUREUP = 6;
	static const uint8 POSTUREDOWN = 7;
	static const uint8 NEXTATTACKDELAY = 8;
};


#endif /* COMMANDEFFECT_H_ */
