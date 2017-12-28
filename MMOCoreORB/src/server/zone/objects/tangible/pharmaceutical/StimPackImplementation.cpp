
#include <stddef.h>
#include <algorithm>

#include "engine/core/ManagedReference.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/objects/tangible/pharmaceutical/PharmaceuticalObject.h"
#include "server/zone/objects/tangible/pharmaceutical/StimPack.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "system/lang/Math.h"
#include "system/lang/String.h"
#include "system/lang/ref/Reference.h"
#include "system/lang/ref/WeakReference.h"
#include "system/platform.h"
#include "system/thread/Locker.h"
#include "system/util/Vector.h"
#include "templates/SharedObjectTemplate.h"
#include "templates/params/creature/CreatureAttribute.h"
#include "templates/tangible/StimPackTemplate.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
class CreatureObject;
}  // namespace creature
}  // namespace objects
}  // namespace zone
}  // namespace server

bool StimPackImplementation::isPetStimPack() {
	return getObjectNameStringIdName().contains("pet_stimpack");
}

bool StimPackImplementation::isDroidRepairKit() {
	return getObjectNameStringIdName().contains("droid_damage_kit");
}

bool StimPackImplementation::isClassA() {
	return getMedicineClass() == StimPackTemplate::STIM_A;
}

bool StimPackImplementation::isClassB() {
	return getMedicineClass() == StimPackTemplate::STIM_B;
}

bool StimPackImplementation::isClassC() {
	return getMedicineClass() == StimPackTemplate::STIM_C;
}

bool StimPackImplementation::isClassD() {
	return getMedicineClass() == StimPackTemplate::STIM_D;
}

bool StimPackImplementation::isClassE() {
	return getMedicineClass() == StimPackTemplate::STIM_E;
}

StimPack* StimPackImplementation::split(int charges) {

	Locker locker(_this.getReferenceUnsafeStaticCast());
	ObjectManager* objectManager = ObjectManager::instance();
	ManagedReference<StimPack*> protoclone = cast<StimPack*>( objectManager->cloneObject(_this.getReferenceUnsafeStaticCast()));
	if (protoclone != NULL) {
		Locker cloneLocker(protoclone);

		if(protoclone->hasAntiDecayKit()){
			protoclone->removeAntiDecayKit();
		}

		protoclone->setParent(NULL);
		protoclone->setUseCount(charges);
		decreaseUseCount(charges);
		return protoclone;
	}
	return NULL;
}

void StimPackImplementation::fillAttributeList(AttributeListMessage* msg, CreatureObject* object) {
	PharmaceuticalObjectImplementation::fillAttributeList(msg, object);

	if (!isRangedStimPack() && !isDroidRepairKit()) {
		Vector<byte> atts = getAttributes();

		if (atts.contains(CreatureAttribute::HEALTH)) {
			msg->insertAttribute("examine_heal_damage_health", Math::getPrecision(effectiveness, 0));
		}

		if (atts.contains(CreatureAttribute::ACTION)) {
			msg->insertAttribute("examine_heal_damage_action", Math::getPrecision(effectiveness, 0));
		}

		if (atts.contains(CreatureAttribute::MIND)) {
			msg->insertAttribute("examine_heal_damage_mind", Math::getPrecision(effectiveness, 0));
		}

		if (!isPetStimPack()) {
			msg->insertAttribute("healing_ability", medicineUseRequired);
		}
	} else if (isDroidRepairKit()) {
		msg->insertAttribute("examine_repair_energy", Math::getPrecision(effectiveness, 0));
	}
}

Vector<uint8> StimPackImplementation::getAttributes() {
	if (templateObject->isStimPackTemplate()) {
		StimPackTemplate* stimPackTemplate = templateObject.castTo<StimPackTemplate*>();

		return stimPackTemplate->getAttributes();
	}

	Vector<uint8> vec;

	return vec;
}
