/*
 * CreatureTemplateReference.cpp
 *
 *  Created on: 29/04/2012
 *      Author: victor
 */

#include "CreatureTemplateReference.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"

bool CreatureTemplateReference::toBinaryStream(ObjectOutputStream* stream) {
	CreatureTemplate* obj = get();

	if (obj != NULL) {
		obj->getTemplateName().toBinaryStream(stream);
	} else
		stream->writeShort(0);

	return true;
}

bool CreatureTemplateReference::parseFromBinaryStream(ObjectInputStream* stream) {
	String templateName;
	templateName.parseFromBinaryStream(stream);

	CreatureTemplate* obj = CreatureTemplateManager::instance()->getTemplate(templateName);

	if (obj != NULL) {
		updateObject(obj);

		return true;
	}

	updateObject(obj);

	return false;
}

CreatureTemplate* CreatureTemplateReference::operator=(CreatureTemplate* obj) {
	updateObject(obj);

	return obj;
}
