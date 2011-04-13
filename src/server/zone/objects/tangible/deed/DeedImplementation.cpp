/*
 * DeedImplementation.cpp
 *
 *  Created on: Apr 18, 2010
 *      Author: crush
 */

#include "Deed.h"
#include "server/zone/templates/tangible/DeedTemplate.h"

void DeedImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	DeedTemplate* deedData = dynamic_cast<DeedTemplate*>(templateData);

	if (deedData == NULL)
		return;

	String generatetmpl = deedData->getGeneratedObjectTemplate();

	generatedObjectTemplate = generatetmpl;
}

void DeedImplementation::fillAttributeList(AttributeListMessage* alm, PlayerCreature* object) {
	TangibleObjectImplementation::fillAttributeList(alm, object);
}

void DeedImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	setLoggingName("Deed");
}
