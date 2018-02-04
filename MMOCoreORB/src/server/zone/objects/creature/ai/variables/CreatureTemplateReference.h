/*
 * CreatureTemplateReference.h
 *
 *  Created on: 29/04/2012
 *      Author: victor
 */

#ifndef CREATURETEMPLATEREFERENCE_H_
#define CREATURETEMPLATEREFERENCE_H_

#include "server/zone/objects/creature/ai/CreatureTemplate.h"

#include "engine/util/json_utils.h"

class CreatureTemplateReference : public Reference<CreatureTemplate*> {
public:
	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);
	CreatureTemplate* operator=(CreatureTemplate* obj);
};

void to_json(nlohmann::json& j, const CreatureTemplateReference& p);




#endif /* CREATURETEMPLATEREFERENCE_H_ */
