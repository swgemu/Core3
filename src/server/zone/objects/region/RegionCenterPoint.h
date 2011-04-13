/*
 * RegionCenterPoint.h
 *
 *  Created on: 14/03/2010
 *      Author: victor
 */

#ifndef REGIONCENTERPOINT_H_
#define REGIONCENTERPOINT_H_

class RegionCenterPoint : public Object {
public:
	float x, y, radius, radius2;

	RegionCenterPoint() {
		x = 0, y = 0, radius = 0, radius2 = 0;
	}

	RegionCenterPoint(float px, float py, float rad) {
		x = px;
		y = py;
		radius = rad;
		radius2 = radius * radius;
	}

	RegionCenterPoint(const RegionCenterPoint& reg) : Object() {
		x = reg.x;
		y = reg.y;
		radius = reg.radius;
		radius2 = reg.radius2;
	}

	RegionCenterPoint& operator=(const RegionCenterPoint& reg) {
		if (this == &reg)
			return *this;

		x = reg.x;
		y = reg.y;
		radius = reg.radius;
		radius2 = reg.radius2;

		return *this;
	}

};

#endif /* REGIONCENTERPOINT_H_ */
