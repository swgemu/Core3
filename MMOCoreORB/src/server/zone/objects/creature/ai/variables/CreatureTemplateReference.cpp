/*
 * CreatureTemplateReference.cpp
 *
 *  Created on: 29/04/2012
 *      Author: victor
 */

#include "CreatureTemplateReference.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"

bool CreatureTemplateReference::toBinaryStream(ObjectOutputStream* stream) {
#ifdef ODB_SERIALIZATION
	templateString.toBinaryStream(stream);
#else
	CreatureTemplate* obj = get();

	if (obj != nullptr) {
		obj->getTemplateName().toBinaryStream(stream);
	} else
		stream->writeShort(0);

#endif
	return true;
}

bool CreatureTemplateReference::parseFromBinaryStream(ObjectInputStream* stream) {
#ifdef ODB_SERIALIZATION
	templateString.parseFromBinaryStream(stream);

	return true;
#else
	String templateName;
	templateName.parseFromBinaryStream(stream);

	CreatureTemplate* obj = CreatureTemplateManager::instance()->getTemplate(templateName);

	if (obj != nullptr) {
		updateObject(obj);

		return true;
	}

	updateObject(obj);

	return false;
#endif
}

CreatureTemplate* CreatureTemplateReference::operator=(CreatureTemplate* obj) {
	updateObject(obj);

	return obj;
}

void to_json(nlohmann::json& j, const CreatureTemplateReference& r) {
#ifdef ODB_SERIALIZATION
	j = r.templateString;
#else
	CreatureTemplate* obj = r.get();

	if (obj != nullptr) {
		j = obj->getTemplateName();
	} else
		j = "";
#endif
}
