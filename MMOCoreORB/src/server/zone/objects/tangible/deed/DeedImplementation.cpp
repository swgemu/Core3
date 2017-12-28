/*
 * DeedImplementation.cpp
 *
 *  Created on: Apr 18, 2010
 *      Author: crush
 */

#include <stddef.h>

#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/tangible/deed/Deed.h"
#include "system/lang/String.h"
#include "templates/SharedObjectTemplate.h"
#include "templates/tangible/DeedTemplate.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
class CreatureObject;
}  // namespace creature
}  // namespace objects
namespace packets {
namespace scene {
class AttributeListMessage;
}  // namespace scene
}  // namespace packets
}  // namespace zone
}  // namespace server

void DeedImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	DeedTemplate* deedData = dynamic_cast<DeedTemplate*>(templateData);

	if (deedData == NULL)
		return;

	String generatetmpl = deedData->getGeneratedObjectTemplate();

	generatedObjectTemplate = generatetmpl;
}

void DeedImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(alm, object);
}

void DeedImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	setLoggingName("Deed");
}
