/*
Copyright (C) 2010 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 3 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

/**
 * \file WeatherMap.h
 * \author Kyle Burkhardt
 * \date 2-10-12
 */

#ifndef WEATHERMAP_H_
#define WEATHERMAP_H_

#include "engine/engine.h"
#include "server/zone/objects/resource/simplexnoise/SimplexNoise.h"

/*
 * This class represents the Simplex Noise map of planetary weather
 */
class WeatherMap : public Serializable {
protected:

	uint32 seed;  /// Random value to determine map shape
	float modifier; /// Value to determine map type (ore, or other)
	float density; /// Max density of map
	uint64 startTime;
	uint64 endTime;

	float minX, maxX, minY, maxY;

public:
	WeatherMap() : Object(), Serializable() {
		addSerializableVariables();
	}

	WeatherMap(const WeatherMap& map) : Object(), Serializable() {
		seed = map.seed;
		modifier = map.modifier;
		density = map.density;
		startTime = map.startTime;
		endTime = map.endTime;
		minX = map.minX;
		maxX = map.maxX;
		minY = map.minY;
		maxY = map.maxY;

		addSerializableVariables();
	}

	WeatherMap(int weatherStability, float minx, float maxx, float miny, float maxy, int stop) : Object(), Serializable() {
		initialize(weatherStability);
		minX = minx;
		maxX = maxx;
		minY = miny;
		maxY = maxy;

		endTime = time(0) + stop;
	}

	~WeatherMap() {

	}

	WeatherMap& operator=(const WeatherMap& map) {
		if (this == &map)
			return *this;

		seed = map.seed;
		modifier = map.modifier;
		density = map.density;
		minX = map.minX;
		maxX = map.maxX;
		minY = map.minY;
		maxY = map.maxY;
		startTime = map.startTime;
		endTime = map.endTime;

		return *this;
	}


	byte getWeatherAt(float x, float y) {

		if(time(0) > endTime || time(0) < startTime)
			return 0;

		float current = time(0) - startTime; // cannot be negative
		float end = endTime - startTime;
		float mid = end / 2.f;

		if(current > mid)
			current = end - current;

		float currentDensity = (current / mid) * density;
		x -= minX;
		y = maxY - y;

		// [0,1]
		float value = (SimplexNoise::noise(x * modifier, y * modifier, seed * modifier) + 1) / 2.0f;

		byte weather = (byte)(((value * currentDensity) * 100) / 20.f);

		return weather;
	}

	uint64 getEndTime() {
		return endTime;
	}

	String printInfo(float x, float y) {

		float current = time(0) - startTime;
		float end = endTime - startTime;
		float mid = end / 2.f;

		if(current > mid)
			current = end - current;

		float currentDensity = (current / mid) * density;
		x -= minX;
		y = maxY - y;

		// [0,1]
		float value = (SimplexNoise::noise(x * modifier, y * modifier, seed * modifier) + 1) / 2.0f;

		StringBuffer valueString;
		valueString << "Density: " << density << " Density: " << currentDensity
				//<< " Value: " << String::valueOf(value)
				<< " Equation: " << String::valueOf((((value * currentDensity) * 100) / 20.f))
				<< " Weather: " << String::valueOf((byte)(((value * currentDensity) * 100) / 20.f))
				<< " Seed: " << seed
				<< " time: " << time(0) - startTime << "/" << endTime - startTime;

		return valueString.toString();
	}

private:
	/**
	 * Initializes class
	 * \param stormIntensity to determine storm intensity
	 */
	void initialize(short weatherStability) {
		startTime = time(0);
		seed = System::random(startTime);

		modifier = .00017;

		if(System::random(100) > weatherStability) {
			density = (System::random(30) + 60) / 100.0f;
		} else {
			density = (System::random(100 - weatherStability + 30) + 20) / 100.0f;
		}

		if(density > 1)
			density = 1;
		if(density < 0)
			density = 0;

		addSerializableVariables();
	}

	/**
	 * Adds the variables needing to be serialized
	 */
	void addSerializableVariables() {
		addSerializableVariable("seed", &seed);
		addSerializableVariable("modifier", &modifier);
		addSerializableVariable("density", &density);
		addSerializableVariable("minX", &minX);
		addSerializableVariable("maxX", &maxX);
		addSerializableVariable("minY", &minY);
		addSerializableVariable("maxY", &maxY);
		addSerializableVariable("startTime", &startTime);
		addSerializableVariable("endTime", &endTime);
	}
};


#endif /* WEATHERMAP_H_ */
