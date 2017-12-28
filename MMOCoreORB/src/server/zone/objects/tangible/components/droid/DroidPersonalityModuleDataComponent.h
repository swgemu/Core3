/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef DROIDPERSONALITYMODULEDATACOMPONENT_H_
#define DROIDPERSONALITYMODULEDATACOMPONENT_H_

#include "BaseDroidModuleComponent.h"
#include "engine/core/ManagedReference.h"
#include "server/zone/objects/tangible/components/droid/DroidPersonalityObserver.h"
#include "system/lang/String.h"
#include "system/platform.h"

namespace engine {
namespace core {
class ManagedObject;
}  // namespace core
}  // namespace engine
namespace server {
namespace zone {
namespace objects {
namespace creature {
class CreatureObject;
namespace ai {
class DroidObject;
}  // namespace ai
}  // namespace creature
}  // namespace objects
namespace packets {
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


class DroidPersonalityModuleDataComponent : public BaseDroidModuleComponent {

protected:
	String personalityBase;
	String chipName;
	String convoTemplate;
	String personalityStf;
	ManagedReference<DroidPersonalityObserver*> observer;

public:
	DroidPersonalityModuleDataComponent();

	~DroidPersonalityModuleDataComponent();

	String getModuleName();

	void initializeTransientMembers();

	void initialize(DroidObject* droid);

	void fillAttributeList(AttributeListMessage* msg, CreatureObject* droid);

	void handlePetCommand(String cmd, CreatureObject* speaker);

	int getBatteryDrain();

	void deactivate();

	String toString();

	void onCall();

	void onStore();

	void copy(BaseDroidModuleComponent* other);

	void notifyEvent(unsigned int eventType, ManagedObject* arg1, int64 arg2,bool forced = false);

	void quip(String message,DroidObject* droid);

	String getPersonalityBase();

	uint32 getPersonalityConversationTemplate();

	String getPersonalityStf() { return personalityStf; }
};


} // droid
} // components
} // tangible
} // objects
} // zone
} // server
using namespace server::zone::objects::tangible::components::droid;
#endif /* DROIDPERSONALITYMODULEDATACOMPONENT_H_ */
