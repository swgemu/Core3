/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
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

#ifndef ZONEIMPLEMENTATION_H_
#define ZONEIMPLEMENTATION_H_

#include "engine/engine.h"

#include "managers/planet/HeightMap.h"

class ZoneProcessServerImplementation;

class ZoneServer;

class CreatureManager;

class CombatManager;
class ChatManager;

class RadialManager;

class PlanetManager;

class SceneObject;

class ZoneImplementation : public ZoneServant, public QuadTree {
	int zoneID;

	ZoneProcessServerImplementation* processor;

	ZoneServer* server;
	ScheduleManager* scheduler;

	CreatureManager* creatureManager;

	RadialManager* radialManager;

	PlanetManager* planetManager;

	HeightMap heightMap;

	Time galacticTime;

	//Weather
	float weatherWindX; //1.0 = east, -1.0 = west
	float weatherWindY; //1.0 = north, -1.0 = south
	uint32 weatherID;
	bool weatherEnabled;

public:
	ZoneImplementation(ZoneServer* serv, ZoneProcessServerImplementation* srv, int id);

	~ZoneImplementation() {
	}

	void startManagers();

	void stopManagers();

	void registerObject(SceneObject* obj);

	SceneObject* lookupObject(uint64 oid);

	SceneObject* deleteObject(uint64 oid);
	SceneObject* deleteObject(SceneObject* obj);

	SceneObject* deleteCachedObject(SceneObject* obj);

	// zone cell methods
	float getHeight(float x, float y);

	// setters and getters
	inline int getZoneID() {
		return zoneID;
	}

	inline ZoneServer* getZoneServer() {
		return server;
	}

	inline CreatureManager* getCreatureManager() {
		return creatureManager;
	}

	inline PlanetManager* getPlanetManager() {
		return planetManager;
	}

	ChatManager* getChatManager();

	inline uint64 getGalacticTime() {
		return (uint64) galacticTime.miliDifference() / 1000;
	}

	inline uint32 getWeatherID() {
		return weatherID;
	}

	inline void setWeatherID(uint32 value) {
		weatherID = value;
	}

	inline void changeWeatherID(int value) {
		if (weatherID == 0 && value < 0) {
			weatherID = 0;
			return;
		}

		weatherID += value;

		if (weatherID > 4) {
			weatherID = 4;
			return;
		}
	}

	inline bool isWeatherEnabled() {
		return weatherEnabled;
	}

	inline void setWeatherEnabled(bool value) {
		weatherEnabled = value;
	}

	inline void setWeatherWindX(float value) {
		weatherWindX = value;
	}

	inline void setWeatherWindY(float value) {
		weatherWindY = value;
	}

	inline float getWeatherWindX() {
		return weatherWindX;
	}

	inline float getWeatherWindY() {
		return weatherWindY;
	}

};

#endif /*ZONEIMPLEMENTATION_H_*/
