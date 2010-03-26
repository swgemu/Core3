/*
 * Boundary.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef BOUNDARY_H_
#define BOUNDARY_H_

class Boundary {

public:
	virtual ~Boundary() {

	}

	virtual bool containsPoint(float x, float y) {
		return false;
	}

	virtual float getLocalWaterTableHeight() {
		return -16000;
	}

};


#endif /* BOUNDARY_H_ */
