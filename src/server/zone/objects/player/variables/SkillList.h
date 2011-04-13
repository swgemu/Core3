/*
 * SkillList.h
 *
 *  Created on: 28/12/2009
 *      Author: victor
 */

#ifndef SKILLLIST_H_
#define SKILLLIST_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/variables/DeltaVector.h"

class SkillList : public DeltaVector<String> {
public:
	bool contains(const String& element);
};


#endif /* SKILLLIST_H_ */
