/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef PERFORMANCEMANAGER_H_
#define PERFORMANCEMANAGER_H_

#include "Performance.h"
#include "PerformEffect.h"
#include "engine/log/Logger.h"
#include "server/zone/objects/creature/CreatureObject.h"

class PerformanceManager: public Logger {
	HashTable<String, String> danceMap;
	HashTable<String, int> instrumentIdMap;

	Vector<Performance*>* performances;
	Vector<PerformEffect*>* performEffects;
	int loadedCount;
	void loadPerformances();
	void loadPerformEffects();

public:
	PerformanceManager();

	~PerformanceManager();

	static const int HEAL_RANGE = 60;

	Performance* getDance(const String& name);
	Performance* getSong(const String& name, int instrumentType);
	Performance* getPerformanceFromIndex(int index);

	PerformEffect* getPerformEffect(int effectId, int effectLevel);

	int getPerformanceIndex(int type, const String& name, int instrumentType);
	int getMatchingPerformanceIndex(int type, int instrumentType);
	String getInstrumentFromIndex(int performanceIndex);

	Vector<Performance*> getPerformanceListFromMod(const String& requiredSkillMod, int playerSkillModValue,	int instrument);

	String getInstrumentAnimation(int instrumentType);
	String getInstrument(int instrumentType);
	String getProperInstrumentName(int instrumentType);
	int getInstrumentId(const String& instrument);

	String getDanceAnimation(int performanceIndex);

	void sendAvailablePerformances(CreatureObject* player, int performanceType, bool bandCommand);

	bool canPlaySong(CreatureObject* player, const String& name);
	bool canPlaySong(CreatureObject* player, int performanceIndex);
	bool canPlayInstrument(CreatureObject* player, int instrumentType);
	bool canPerformDance(CreatureObject* player, int performanceIndex);


	void performanceMessageToSelf(CreatureObject* actor, CreatureObject* target, const String& table, const String& text);
	void performanceMessageToPlayer(CreatureObject* player, CreatureObject* actor, CreatureObject* target, const String& table, const String& text);
	void performanceMessageToBand(CreatureObject* actor, CreatureObject* target, const String& table, const String& text);
	void performanceMessageToBandPatrons(CreatureObject* actor, CreatureObject* target, const String& table, const String& text);
	void performanceMessageToPatrons(CreatureObject* actor, CreatureObject* target, const String& table, const String& text);
	void performanceMessageToDroidOwner(CreatureObject* droid, CreatureObject* target, const String& table, const String& text);

};

#endif /*PERFORMANCEMANAGER_H_*/
