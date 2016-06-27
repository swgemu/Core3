
#ifndef EVENTPERKDEEDTEMPLATE_H_
#define EVENTPERKDEEDTEMPLATE_H_

#include "templates/tangible/DeedTemplate.h"

class EventPerkDeedTemplate : public DeedTemplate {
private:
	int perkType;
	uint64 generatedTimeToLive;
	SortedVector<String> allowedZones;

public:
	const static int UNKNOWN = 0;
	const static int STATIC = 1;
	const static int THEATER = 2;
	const static int RECRUITER = 3;
	const static int GAME = 4;
	const static int HONORGUARD = 5;

	const static uint64 TIME_TO_LIVE = 28800000; // 8 hours

	EventPerkDeedTemplate() {
		perkType = UNKNOWN;
		generatedTimeToLive = 0;
		allowedZones.removeAll();
	}

	~EventPerkDeedTemplate() {

	}

	void readObject(LuaObject* templateData) {
		DeedTemplate::readObject(templateData);
		perkType = templateData->getIntField("perkType");
		generatedTimeToLive = templateData->getLongField("generatedTimeToLive");

		LuaObject allowzones = templateData->getObjectField("allowedZones");

		if (allowzones.isValidTable()) {
			for (int i = 1; i <= allowzones.getTableSize(); ++i) {
				allowedZones.put(allowzones.getStringAt(i));
			}
		}

		allowzones.pop();
    }

	int getPerkType() {
		return perkType;
	}

	uint64 getGeneratedTimeToLive() {
		return generatedTimeToLive;
	}

	inline bool isAllowedZone(const String& zoneName) {
		return allowedZones.isEmpty() || allowedZones.contains(zoneName);
	}

};


#endif /* EVENTPERKDEEDTEMPLATE_H_ */
