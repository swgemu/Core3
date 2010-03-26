/*
 * RegionImplementation.cpp
 *
 *  Created on: 12/03/2010
 *      Author: victor
 */

#include "Region.h"

bool RegionImplementation::containsPoint(float px, float py) {
	for (int i = 0; i < points.size(); ++i) {
		RegionCenterPoint point = points.get(i);

		if (((px - point.x) * (px - point.x)) + ((py - point.y) * (py - point.y)) <= point.radius2 )
			return true;
	}

	return false;
}

