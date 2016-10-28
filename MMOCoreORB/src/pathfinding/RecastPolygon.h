/*
 * RecastPolygon.h
 *
 *  Created on: April 29, 2016
 *      Author: gslomin
 */

#ifndef RECASTPOLYGON_H_
#define RECASTPOLYGON_H_

enum SamplePolyAreas
{
	SAMPLE_POLYAREA_GROUND,
	SAMPLE_POLYAREA_WATER,
	SAMPLE_POLYAREA_ROAD,
	SAMPLE_POLYAREA_DOOR,
	SAMPLE_POLYAREA_GRASS,
	SAMPLE_POLYAREA_JUMP,
};
enum SamplePolyFlags
{
	SAMPLE_POLYFLAGS_WALK		= 0x01,		// Ability to walk (ground, grass, road)
	SAMPLE_POLYFLAGS_SWIM		= 0x02,		// Ability to swim (water).
	SAMPLE_POLYFLAGS_DOOR		= 0x04,		// Ability to move through doors.
	SAMPLE_POLYFLAGS_JUMP		= 0x08,		// Ability to jump.
	SAMPLE_POLYFLAGS_DISABLED	= 0x10,		// Disabled polygon
	SAMPLE_POLYFLAGS_ALL		= 0xffff	// All abilities.
};

class RecastPolygon : public Object {
public:
	RecastPolygon(int numVerts) {
		verts = new float[numVerts*3];
		this->numVerts = numVerts;
		hmin = 0;
		hmax = 0;
		type = SAMPLE_POLYAREA_GROUND;
	}

	~RecastPolygon() {
		delete[] verts;
	}

	RecastPolygon(const RecastPolygon& rhs) : Object(rhs) {
		*this = rhs;
	}

	RecastPolygon& operator=(const RecastPolygon& rhs) {
		if (this == &rhs)
			return *this;

		verts = new float[rhs.numVerts*3];
		memcpy(verts, rhs.verts, sizeof(float)*rhs.numVerts);
		type = rhs.type;
		numVerts = rhs.numVerts;
		hmin = rhs.hmin;
		hmax = rhs.hmax;
		return *this;
	}

	SamplePolyAreas type;
	float *verts;
	int numVerts;
	float hmin, hmax;
};

#endif /* RECASTPOLYGON_H_ */
