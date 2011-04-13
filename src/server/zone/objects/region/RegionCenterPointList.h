/*
 * RegionCenterPointList.h
 *
 *  Created on: 14/03/2010
 *      Author: victor
 */

#ifndef REGIONCENTERPOINTLIST_H_
#define REGIONCENTERPOINTLIST_H_

#include "RegionCenterPoint.h"
#include "engine/engine.h"

class RegionCenterPointList : public Vector<RegionCenterPoint> {
public:
	void addRegion(float x, float y, float radius) {
		RegionCenterPoint point(x, y, radius);
		add(point);
	}
};

#endif /* REGIONCENTERPOINTLIST_H_ */
