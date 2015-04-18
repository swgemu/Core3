/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/**
 * \file SpawnDensityMap.h
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#ifndef SPAWNDENSITYMAP_H_
#define SPAWNDENSITYMAP_H_

#include "engine/engine.h"
//#include "system/lang/simplexnoise/SimplexNoise.h"
#include "simplexnoise/SimplexNoise.h"

/*
 * This class represents the Simplex Noise map of a resource
 */
class SpawnDensityMap : public Serializable {
protected:

	uint32 seed;  /// Random value to determine map shape
	float modifier; /// Value to determine map type (ore, or other)
	float density; /// Max density of map

	float minX, maxX, minY, maxY;

	uint32 totalUnits;  /// Total units that can be mined
	uint32 unitsHarvested;  /// Number of units already mined

public:
	enum {
		HIGHDENSITY   = 1,
		MEDIUMDENSITY = 2,
		LOWDENSITY    = 3
	};
		

public:
	SpawnDensityMap() : Object(), Serializable() {
		addSerializableVariables();
	}

	SpawnDensityMap(const SpawnDensityMap& map) : Object(), Serializable() {
		seed = map.seed;
		modifier = map.modifier;
		density = map.density;
		minX = map.minX;
		maxX = map.maxX;
		minY = map.minY;
		maxY = map.maxY;

		totalUnits = map.totalUnits;
		unitsHarvested = map.unitsHarvested;

		addSerializableVariables();
	}

	SpawnDensityMap(bool ore, short concentration,
			float minx, float maxx, float miny, float maxy) : Object(), Serializable() {
		initialize(ore, concentration);
		minX = minx;
		maxX = maxx;
		minY = miny;
		maxY = maxy;
	}

	~SpawnDensityMap() {

	}

	SpawnDensityMap& operator=(const SpawnDensityMap& map) {
		if (this == &map)
			return *this;

		seed = map.seed;
		modifier = map.modifier;
		density = map.density;
		minX = map.minX;
		maxX = map.maxX;
		minY = map.minY;
		maxY = map.maxY;

		totalUnits = map.totalUnits;
		unitsHarvested = map.unitsHarvested;

		return *this;
	}


	float getDensityAt(float x, float y) {
		x -= minX;
		y = maxY - y;
		float value = SimplexNoise::noise(x * modifier, y * modifier, seed * modifier);

		if(value < 0)
			return 0;

		return value * density;
	}

	void print() {
		System::out << "Seed: " << seed << " Modifier: "
				<< modifier << " Density: " << density << endl;
	}

private:
	/**
	 * Initializes class
	 * \param ore Boolean value to see if map is ore
	 * \param concentration to determine density
	 */
	void initialize(bool ore, short concentration) {
		seed = System::random(time(0));

		if(ore)
			modifier = .00015;
		else
			modifier = .0006;

		switch(concentration) {
		case 1:
			density = (System::random(9) + 90) / 100.0f;
			break;
		case 2:
			density = (System::random(20) + 75) / 100.0f;
			break;
		case 3:
			density = (System::random(25) + 50) / 100.0f;
			break;
		default:
			density = (System::random(25) + 50) / 100.0f;
		}

		totalUnits = System::random(5000000) + 5000000;

		addSerializableVariables();
	}

	/**
	 * Adds the variables needing to be serialized
	 */
	void addSerializableVariables() {
		addSerializableVariable("seed", &seed);
		addSerializableVariable("modifier", &modifier);
		addSerializableVariable("density", &density);
		addSerializableVariable("totalUnits", &totalUnits);
		addSerializableVariable("unitsHarvested", &unitsHarvested);
		addSerializableVariable("minX", &minX);
		addSerializableVariable("maxX", &maxX);
		addSerializableVariable("minY", &minY);
		addSerializableVariable("maxY", &maxY);
	}
};


#endif /* SPAWNDENSITYMAP_H_ */
