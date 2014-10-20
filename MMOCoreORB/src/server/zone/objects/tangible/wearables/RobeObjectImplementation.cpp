
#include "server/zone/objects/tangible/wearables/RobeObject.h"
#include "server/zone/templates/SharedTangibleObjectTemplate.h"

String RobeObjectImplementation::getSkillRequired() {
	Reference<SharedTangibleObjectTemplate* > tanoTemp = dynamic_cast<SharedTangibleObjectTemplate*>(templateObject.get());

	if (tanoTemp->getCertificationsRequired().size() > 0) {
		return tanoTemp->getCertificationsRequired().get(0);
	}

	return "";
}
