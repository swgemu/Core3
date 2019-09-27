/*
 * Param.h
 *
 *  Created on: 23-feb-2009
 *      Author: TheAnswer
 */

#ifndef PARAM_H_
#define PARAM_H_

#include "system/lang.h"
#include "engine/util/iffstream/IffStream.h"

class Param {
	uint32 type;

public:
	const static uint32 BOOL = 0x01;
	const static uint32 FLOAT = 0x02;
	const static uint32 INTEGER = 0x04;
	const static uint32 STRING = 0x08;
	const static uint32 STRINGID = 0x10;
	const static uint32 VECTOR = 0x12;
	const static uint32 DYNAMICVARIABLE = 0x014;
	const static uint32 TRIGGERVOLUME = 0x16;
	const static uint32 PALETTECOLORCUSTOMIZATION = 0x18;
	const static uint32 RANGEDINTCUSTOMIZATIONVARIABLE = 0x20;
	const static uint32 CUSTOMIZATIONVARIABLEMAP = 0x22;
public:
	Param() {
		type = (uint32)-1;
	}

	virtual ~Param() {

	}

	virtual bool parse(engine::util::Chunk* source) = 0;

	virtual String toString() const = 0;

	inline uint32 getType() const {
		return type;
	}

	inline void setType(uint32 tp) {
		type = tp;
	}

	inline bool isBool() const {
		return type == BOOL;
	}

	inline bool isFloat() const {
		return type == FLOAT;
	}

	inline bool isInteger() const {
		return type == INTEGER;
	}

	inline bool isString() const {
		return type == STRING;
	}

	inline bool isStringId() const {
		return type == STRINGID;
	}
};

#endif /* PARAM_H_ */
