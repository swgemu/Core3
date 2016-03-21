/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef PERFORMANCEMANAGER_H_
#define PERFORMANCEMANAGER_H_

#include "engine/engine.h"

#include "server/zone/ZoneServer.h"
#include "server/zone/ZoneProcessServer.h"
#include "Performance.h"

class PerformanceManager: public Logger {
	HashTable<String, String> danceMap;
	HashTable<String, int> instrumentIdMap;

	Vector<Performance*>* performances;
	int loadedCount;
	void loadPerformances();

public:
	PerformanceManager();

	~PerformanceManager();

	Performance* getDance(const String& name);
	Performance* getSong(const String& name, int instrumentType);

	Vector<Performance*> getPerformanceListFromMod(
			const String& requiredSkillMod, int playerSkillModValue,
			int instrument);

	int getInstrumentAnimation(int instrumentType, String& instrumentAnimation);

	String getInstrument(int instrumentType);

	inline String getDanceAnimation(const String& dance) {
		return danceMap.get(dance);
	}

	inline int getInstrumentId(const String& song) {
		return instrumentIdMap.get(song);
	}

	inline bool hasInstrumentId(const String& song) {
		return instrumentIdMap.containsKey(song);
	}

	inline bool hasDanceAnimation(const String& dance) {
		return danceMap.containsKey(dance);
	}

};

#endif /*PERFORMANCEMANAGER_H_*/
