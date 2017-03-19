#ifndef SHUTTLEBEACONSUICALLBACK_H_
#define SHUTTLEBEACONSUICALLBACK_H_


#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/tangible/eventperk/ShuttleBeacon.h"

class ShuttleBeaconSuiCallback : public SuiCallback {
public:
	ShuttleBeaconSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isListBox() || cancelPressed)
			return;

		SuiListBox* listBox = cast<SuiListBox*>(suiBox);

		ManagedReference<SceneObject*> beacon = listBox->getUsingObject().get();

		if (beacon == NULL)
			return;

		ManagedReference<ShuttleBeacon*> shuttleBeacon = cast<ShuttleBeacon*>(beacon.get());

		if (shuttleBeacon == NULL)
			return;

		if (args->size() < 1)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		if (index == -1)
			return;

		shuttleBeacon->spawnShuttle(player, index);
	}
};

#endif /* SHUTTLEBEACONSUICALLBACK_H_ */
