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
	enum {
		OTHER,
		FOOD,
		MEDICAL,
		PERFORMANCE,
		SPICE,
		SKILL,
		JEDI,
		INNATE,
		STATE
	};
};


#endif /* BUFFTYPE_H_ */
