/*
 * DeedImplementation.cpp
 *
 *  Created on: Apr 18, 2010
 *      Author: crush
 */

#include "server/zone/objects/tangible/deed/Deed.h"
#include "templates/tangible/DeedTemplate.h"

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
