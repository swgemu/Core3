/*
 * PathEdge.h
 *
 *  Created on: Apr 4, 2015
 *      Author: TheAnswer
 */

#ifndef PATHEDGE_H_
#define PATHEDGE_H_

#include "engine/util/iffstream/IffStream.h"

class PathEdge {
	int from, to;

	float laneWidthRight;
	float laneWidthLeft;

public:
	PathEdge() : from(0), to(0), laneWidthRight(0), laneWidthLeft(0) {
	}

	void readObject(IffStream* iffStream) {
		from = iffStream->getInt();
		to = iffStream->getInt();
		laneWidthRight = iffStream->getFloat();
		laneWidthLeft = iffStream->getFloat();
	}

	inline int getFromConnection() const {
		return from;
	}

	inline int getToConnection() const {
		return to;
	}

	inline float getLaneWidthRight() const {
		return laneWidthRight;
	}

	inline float getLaneWidthLeft() const {
		return laneWidthLeft;
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		return false;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		return false;
	}


};

#endif /* PATHEDGE_H_ */
