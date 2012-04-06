/*
 * RobeObjectImplementation.cpp
 *
 *  Created on: Apr 5, 2012
 *      Author: katherine
 */

#include "RobeObject.h"
#include "server/zone/objects/creature/CreatureObject.h"

void RobeObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {

	TangibleObjectImplementation::fillAttributeList(alm, object);

	alm->insertAttribute("jedi_robe_power", "+250");

	alm->insertAttribute("jedi_robe_regen", "+10");

	if (skillRequired != "force_title_jedi_rank_02"){
	alm->insertAttribute("jedi_rank_required", "@skl_n:" + skillRequired);
	}

}
