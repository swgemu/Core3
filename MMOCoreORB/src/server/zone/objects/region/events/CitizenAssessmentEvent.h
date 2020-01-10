#ifndef CITIZENASSESSMENTEVENT_H_
#define CITIZENASSESSMENTEVENT_H_

#include "server/zone/ZoneServer.h"

namespace server {
	namespace zone {
		namespace objects {
			namespace region {
				class CityRegion;
			}
		}
	}
}

class CitizenAssessmentEvent : public Task {
	Reference<ZoneServer*> zoneServer;
	WeakReference<server::zone::objects::region::CityRegion*> cityRegion;

public:
	CitizenAssessmentEvent(server::zone::objects::region::CityRegion* city, ZoneServer* zserv);

	void run();
};

#endif /* CITIZENASSESSMENTEVENT_H_ */
