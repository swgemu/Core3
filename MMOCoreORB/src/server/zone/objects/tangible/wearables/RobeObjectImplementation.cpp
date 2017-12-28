
#include "server/zone/objects/tangible/wearables/RobeObject.h"
#include "system/lang/String.h"
#include "system/lang/ref/Reference.h"
#include "system/util/Vector.h"
#include "templates/SharedObjectTemplate.h"
#include "templates/SharedTangibleObjectTemplate.h"

String RobeObjectImplementation::getSkillRequired() {
	Reference<SharedTangibleObjectTemplate* > tanoTemp = dynamic_cast<SharedTangibleObjectTemplate*>(templateObject.get());

	if (tanoTemp->getCertificationsRequired().size() > 0) {
		return tanoTemp->getCertificationsRequired().get(0);
	}

	return "";
}
