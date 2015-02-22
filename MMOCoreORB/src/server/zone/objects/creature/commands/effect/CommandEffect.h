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
	enum {
		INVALID,
		BLIND,
		DIZZY,
		INTIMIDATE,
		STUN,
		KNOCKDOWN,
		POSTUREUP,
		POSTUREDOWN,
		NEXTATTACKDELAY,
		HEALTHDEGRADE,
		ACTIONDEGRADE,
		MINDDEGRADE
	};
};


#endif /* COMMANDEFFECT_H_ */
