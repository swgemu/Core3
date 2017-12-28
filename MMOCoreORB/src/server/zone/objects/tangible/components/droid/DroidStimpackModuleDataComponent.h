/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef DROIDSTIMPACKMODULEDATACOMPONENT_H_
#define DROIDSTIMPACKMODULEDATACOMPONENT_H_

#include "BaseDroidModuleComponent.h"
#include "server/zone/objects/tangible/pharmaceutical/StimPack.h"
#include "system/lang/String.h"
#include "system/platform.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
class CreatureObject;
namespace ai {
class DroidObject;
}  // namespace ai
}  // namespace creature
namespace intangible {
class PetControlDevice;
}  // namespace intangible
namespace manufactureschematic {
namespace craftingvalues {
class CraftingValues;
}  // namespace craftingvalues
}  // namespace manufactureschematic
namespace scene {
class SceneObject;
}  // namespace scene
namespace tangible {
namespace pharmaceutical {
class StimPack;
}  // namespace pharmaceutical
}  // namespace tangible
}  // namespace objects
namespace packets {
namespace object {
class ObjectMenuResponse;
}  // namespace object
namespace scene {
class AttributeListMessage;
}  // namespace scene
}  // namespace packets
}  // namespace zone
}  // namespace server

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace components {
namespace droid {


class DroidStimpackModuleDataComponent : public BaseDroidModuleComponent {

protected:
	int capacity;
	int speed;
	int loaded;
public:
	int rate;

	DroidStimpackModuleDataComponent();

	~DroidStimpackModuleDataComponent();

	String getModuleName();

	void initializeTransientMembers();

	void fillAttributeList(AttributeListMessage* msg, CreatureObject* droid);

	int getBatteryDrain();

	String toString();

	void onCall();

	void onStore();

	bool isStackable() { return true; }

	void copy(BaseDroidModuleComponent* other);

	void addToStack(BaseDroidModuleComponent* other);

	void updateCraftingValues(CraftingValues* values, bool firstUpdate);

	void fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player);

	int handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller);

	void initialize(DroidObject* droid);

	void sendLoadUI(CreatureObject* player);

	void handleInsertStimpack(CreatureObject* player, StimPack* pack);

	void countUses();

	StimPack* compatibleStimpack(float power);

	StimPack* findStimPack();
};


} // droid
} // components
} // tangible
} // objects
} // zone
} // server
using namespace server::zone::objects::tangible::components::droid;
#endif /* DROIDSTIMPACKMODULEDATACOMPONENT_H_ */
