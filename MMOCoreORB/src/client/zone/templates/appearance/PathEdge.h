/*
 * PathEdge.h
 *
 *  Created on: Apr 4, 2015
 *      Author: TheAnswer
 */

#ifndef SRC_SERVER_ZONE_TEMPLATES_APPEARANCE_PATHEDGE_H_
#define SRC_SERVER_ZONE_TEMPLATES_APPEARANCE_PATHEDGE_H_

#include "engine/engine.h"

class PathEdge : public Object  {


public:
	int from, to;
	
	float laneWidthRight;
	float laneWidthLeft;
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
	
	int compareTo(const PathEdge& rhs) const {
		if(from == rhs.from && to == rhs.to)
			return 0;
		return -1;
	}

};

#endif /* SRC_SERVER_ZONE_TEMPLATES_APPEARANCE_PATHEDGE_H_ */
