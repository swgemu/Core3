/*
 * AiTrackingTask.h
 *
 *  Created on: Aug 8, 2014
 *      Author: swgemu
 */

#ifndef AITRACKINGTASK_H_
#define AITRACKINGTASK_H_

#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"

#include "system/thread/atomic/AtomicInteger.h"
#include "system/thread/atomic/AtomicLong.h"
#include "system/util/HashTable.h"
#include "system/util/Vector.h"
#include "system/lang/String.h"
#include "system/lang/StringBuffer.h"

#include "engine/core/ManagedReference.h"
#include "engine/core/ManagedWeakReference.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

#ifdef AI_DEBUG
#undef AI_DEBUG
#endif

class AiTrackingTask : public Task {
	ManagedWeakReference<AiAgent*> creature;
	HashTable<String, AtomicInteger> luaCalls;
	HashTable<String, AtomicLong> luaTimes;
	Vector<String> callsToList;

public:
	AiTrackingTask(AiAgent* pl) : Task(300000) {
		creature = pl;
		luaCalls.setNullValue(0);
		luaTimes.setNullValue(0);
	}

	virtual ~AiTrackingTask() {
	}

	void run() {
#ifdef AI_DEBUG
		ManagedReference<AiAgent*> strongRef = creature.get();

		if (strongRef == NULL)
			return;

		for (int i = 0; i < callsToList.size(); i++) {
			String key = callsToList.get(i);
			AtomicInteger call = luaCalls.get(key);
			if (call.get() <= 0)
				continue;

			AtomicLong nextTime = luaTimes.get(key);

			float averageTime = (float)nextTime.get()/1000.f / (float)call.get();
			strongRef->info("Average time spent in " + key + ": " + String::valueOf(averageTime) + "ms with " + String::valueOf(call.get()) + " calls totaling " + String::valueOf((float)nextTime.get()/1000.f) + "ms.");
		}

		strongRef->rescheduleTrackingTask();
#endif
	}

	void schedule(uint64 delay = 0) {
#ifdef AI_DEBUG
		Task::schedule(delay);
#endif
	}

	void incrementCall(const String& key) {
		if (luaCalls.containsKey(key)) {
			luaCalls.get(key).increment();
			return;
		}

		luaCalls.put(key, AtomicInteger(1));
	}

	void addTime(const String& key, uint32 time) {
		if (luaTimes.containsKey(key)) {
			luaTimes.get(key).add(time);

			if (luaCalls.get(key).get() <= 0)
				return;

			float averageTime = (float)luaTimes.get(key).get()/1000.f / (float)luaCalls.get(key).get();

			if (averageTime > 10 && !callsToList.contains(key))
				callsToList.add(key);

			if (averageTime < 10)
				callsToList.removeElement(key);

			return;
		}

		luaTimes.put(key, AtomicLong((uint64)time));
	}

	void outputTimes(CreatureObject* caller) {
		ManagedReference<AiAgent*> strongRef = creature.get();

		if (strongRef == NULL)
			return;

		ManagedReference<SuiMessageBox*> list = new SuiMessageBox(caller, 0);
		list->setPromptTitle(strongRef->getDisplayedName()+ "[" + String::valueOf(strongRef->getObjectID()) + "]");
		StringBuffer msg;

		SortedVector<float> averages;
		Vector<String> keys;

		HashTableIterator<String, AtomicInteger> iter(&luaCalls);
		iter.resetIterator();

		while (iter.hasNext()) {
			String key = "";
			AtomicInteger call;

			iter.getNextKeyAndValue(key, call);

			if (call.get() <= 0)
				continue;

			AtomicLong nextTime = luaTimes.get(key);

			float averageTime = (float)nextTime.get()/1000.f / (float)call.get();

			averages.put(averageTime);
			keys.add(averages.find(averageTime), key);
		}

		for (int i = keys.size() - 1; i >= 0; i--) {
			String key = keys.get(i);
			float averageTime = averages.get(i);

			msg << key + "\r\n";
			msg << "    Average:\\#FF0000 " + String::valueOf(averageTime) + "ms\\#.\r\n";
			msg << "    Calls:\\#FF0000 " + String::valueOf(luaCalls.get(key).get()) + "\\#.\r\n";
			msg << "    Total:\\#FF0000 " + String::valueOf((float)luaTimes.get(key).get()/1000.f) + "ms.\\#.\r\n\r\n";
		}

		list->setPromptText(msg.toString());
		caller->sendMessage(list->generateMessage());
	}
};

}
}
}
}
}

using namespace server::zone::objects::creature::events;



#endif /* AITRACKINGTASK_H_ */
