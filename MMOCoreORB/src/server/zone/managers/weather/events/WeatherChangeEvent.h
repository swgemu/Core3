/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef WEATHERCHANGEEVENT_H_
#define WEATHERCHANGEEVENT_H_


#include"server/zone/managers/weather/WeatherManager.h"

namespace server {
namespace zone {
namespace managers {
namespace weather {
namespace events {

class WeatherChangeEvent : public Task {

	ManagedReference<WeatherManager*> weatherManager;

public:
	WeatherChangeEvent(WeatherManager* weatherManager) : Task() {
		this->weatherManager = weatherManager;
	}

	void run() {

		if (weatherManager != NULL) {
			weatherManager->createNewWeatherPattern();
		}
	}

};

}
}
}
}
}


using namespace server::zone::managers::weather::events;

#endif /* WEATHERCHANGEEVENT_H_ */
