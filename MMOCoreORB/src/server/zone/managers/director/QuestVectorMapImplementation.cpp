/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "server/zone/managers/director/QuestVectorMap.h"
#include "system/lang/String.h"
#include "system/util/VectorMap.h"

String QuestVectorMapImplementation::getMapKeyAtIndex(int idx) {
	VectorMapEntry<String, String>* entry = &questMap.elementAt(idx);

	return entry->getKey();
}
