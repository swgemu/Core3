/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "server/zone/managers/director/QuestVectorMap.h"

String QuestVectorMapImplementation::getMapKeyAtIndex(int idx) {
	VectorMapEntry<String, String>* entry = &questMap.elementAt(idx);

	return entry->getKey();
}
