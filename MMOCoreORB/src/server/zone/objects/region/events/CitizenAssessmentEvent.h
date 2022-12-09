#ifndef CITIZENASSESSMENTEVENT_H_
#define CITIZENASSESSMENTEVENT_H_

#include "server/zone/ZoneServer.h"

namespace server {
	namespace zone {
		namespace objects {
			namespace region {
				class NewCityRegion;
			}
		}
	}
}

class CitizenAssessmentEvent : public Task {
	Reference<ZoneServer*> zoneServer;
	WeakReference<server::zone::objects::region::NewCityRegion*> cityRegion;

public:
	CitizenAssessmentEvent(server::zone::objects::region::NewCityRegion* city, ZoneServer* zserv);

	void run();
};

#endif /* CITIZENASSESSMENTEVENT_H_ */
