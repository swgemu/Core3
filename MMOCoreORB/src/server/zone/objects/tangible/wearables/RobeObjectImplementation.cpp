
#include "server/zone/objects/tangible/wearables/RobeObject.h"
#include "templates/SharedTangibleObjectTemplate.h"

String RobeObjectImplementation::getSkillRequired() const {
	auto tanoTemp = dynamic_cast<const SharedTangibleObjectTemplate*>(templateObject.get());
	fatal(tanoTemp, "RobeObject must have a TANO template");

	if (tanoTemp->getCertificationsRequired().size() > 0) {
		return tanoTemp->getCertificationsRequired().get(0);
	}

	return "";
}
