/*
 * BuffType.h
 *
 *  Created on: 03/06/2010
 *      Author: victor
 */

#ifndef BUFFTYPE_H_
#define BUFFTYPE_H_

#include "../BuffAttribute.h"
#include "BuffCRC.h"

class BuffType {
public:
	static const int OTHER = 0;
	static const int FOOD = 1;
	static const int MEDICAL = 3;
	static const int PERFORMANCE = 4;
	static const int SPICE = 5;
	static const int SKILL = 6;
	static const int JEDI = 7;
	static const int INNATE = 8;
	static const int STATE = 9;
};


#endif /* BUFFTYPE_H_ */
