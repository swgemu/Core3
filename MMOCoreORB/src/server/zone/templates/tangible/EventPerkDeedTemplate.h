
#ifndef EVENTPERKDEEDTEMPLATE_H_
#define EVENTPERKDEEDTEMPLATE_H_

#include "DeedTemplate.h"

class EventPerkDeedTemplate : public DeedTemplate {
private:
	int perkType;
	SortedVector<String> allowedZones;

public:
	const static int UNKNOWN = 0;
	const static int STATIC = 1;
	const static int THEATER = 2;
	const static int PERSONNEL = 3;
	const static int GAME = 4;

	const static uint64 TIME_TO_LIVE = 28800000; // 8 hours

	EventPerkDeedTemplate() {
		perkType = UNKNOWN;
		allowedZones.removeAll();
	}

	~EventPerkDeedTemplate() {

	}

	void readObject(LuaObject* templateData) {
		DeedTemplate::readObject(templateData);
		perkType = templateData->getIntField("perkType");

		LuaObject allowzones = templateData->getObjectField("allowedZones");

		if (allowzones.isValidTable()) {
			for (int i = 1; i <= allowzones.getTableSize(); ++i) {
				allowedZones.put(allowzones.getStringAt(i));
			}
		}

		allowzones.pop();
    }

	int getPerkType()
	{
		return perkType;
	}

	inline bool isAllowedZone(const String& zoneName) {
		return allowedZones.isEmpty() || allowedZones.contains(zoneName);
	}

};


#endif /* EVENTPERKDEEDTEMPLATE_H_ */
