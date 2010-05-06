/*
 * TemplateManager.cpp
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#include "TemplateManager.h"

#include "server/zone/templates/SharedObjectTemplate.h"
#include "server/zone/templates/intangible/SharedConstructionContractObjectTemplate.h"
#include "server/zone/templates/intangible/SharedManufactureSchematicObjectTemplate.h"
#include "server/zone/templates/intangible/SharedDraftSchematicObjectTemplate.h"
#include "server/zone/templates/intangible/SharedMissionDataObjectTemplate.h"
#include "server/zone/templates/intangible/SharedMissionListEntryObjectTemplate.h"
#include "server/zone/templates/intangible/SharedMissionObjectTemplate.h"
#include "server/zone/templates/intangible/SharedPlayerObjectTemplate.h"
#include "server/zone/templates/intangible/SharedTokenObjectTemplate.h"
#include "server/zone/templates/intangible/SharedWaypointObjectTemplate.h"
#include "server/zone/templates/tangible/SharedBattlefieldMarkerObjectTemplate.h"
#include "server/zone/templates/tangible/SharedBuildingObjectTemplate.h"
#include "server/zone/templates/tangible/SharedCountingObjectTemplate.h"
#include "server/zone/templates/tangible/SharedCreatureObjectTemplate.h"
#include "server/zone/templates/tangible/SharedFactoryObjectTemplate.h"
#include "server/zone/templates/tangible/SharedInstallationObjectTemplate.h"
#include "server/zone/templates/tangible/SharedResourceContainerObjectTemplate.h"
#include "server/zone/templates/tangible/SharedShipObjectTemplate.h"
#include "server/zone/templates/tangible/SharedWeaponObjectTemplate.h"
#include "server/zone/templates/tangible/CharacterBuilderTerminalTemplate.h"
#include "server/zone/templates/universe/SharedGroupObjectTemplate.h"
#include "server/zone/templates/universe/SharedGuildObjectTemplate.h"
#include "server/zone/templates/universe/SharedJediManagerTemplate.h"
#include "server/zone/templates/SharedCellObjectTemplate.h"
#include "server/zone/templates/SharedIntangibleObjectTemplate.h"
#include "server/zone/templates/SharedStaticObjectTemplate.h"
#include "server/zone/templates/SharedTangibleObjectTemplate.h"
#include "server/zone/templates/SharedUniverseObjectTemplate.h"

TemplateManager::TemplateManager() {
	registerTemplateObjects();

	setLogging("false");
	setGlobalLogging("true");
	setLoggingName("TemplateManager");
}

TemplateManager::~TemplateManager() {
	HashTableIterator<uint32, SharedObjectTemplate*> iterator(&templateCRCMap);

	while (iterator.hasNext())
		delete iterator.getNextValue();
}

void TemplateManager::addTemplate(uint32 key, const String& fullName, LuaObject* templateData) {
	uint32 templateType = templateData->getIntField("templateType");

	SharedObjectTemplate* templateObject = templateFactory.createObject(templateType);

	if (templateObject == NULL) {
		error("error creating template from lua with templateType 0x" + String::hexvalueOf((int)templateType));

		return;
	}

	//info("loading " + fullName);

	templateObject->setFullTemplateString(fullName);
	templateObject->readObject(templateData);

	//info("loaded " + fullName);

	if (templateCRCMap.put(key, templateObject) != NULL) {
		error("duplicate template for " + fullName);
	}
}

void TemplateManager::registerTemplateObjects() {
	templateFactory.registerObject<SharedObjectTemplate>(SharedObjectTemplate::SHOT);
	templateFactory.registerObject<SharedConstructionContractObjectTemplate>(SharedObjectTemplate::SCNC);
	templateFactory.registerObject<SharedDraftSchematicObjectTemplate>(SharedObjectTemplate::SDSC);
	templateFactory.registerObject<SharedManufactureSchematicObjectTemplate>(SharedObjectTemplate::SMSC);
	templateFactory.registerObject<SharedMissionDataObjectTemplate>(SharedObjectTemplate::SMSD);
	templateFactory.registerObject<SharedMissionListEntryObjectTemplate>(SharedObjectTemplate::SMLE);
	templateFactory.registerObject<SharedMissionObjectTemplate>(SharedObjectTemplate::SMSO);
	templateFactory.registerObject<SharedPlayerObjectTemplate>(SharedObjectTemplate::SPLY);
	templateFactory.registerObject<SharedTokenObjectTemplate>(SharedObjectTemplate::STOK);
	templateFactory.registerObject<SharedWaypointObjectTemplate>(SharedObjectTemplate::SWAY);
	templateFactory.registerObject<SharedBattlefieldMarkerObjectTemplate>(SharedObjectTemplate::SBMK);
	templateFactory.registerObject<SharedBuildingObjectTemplate>(SharedObjectTemplate::SBOT);
	templateFactory.registerObject<SharedCountingObjectTemplate>(SharedObjectTemplate::SCOU);
	templateFactory.registerObject<SharedCreatureObjectTemplate>(SharedObjectTemplate::SCOT);
	templateFactory.registerObject<SharedFactoryObjectTemplate>(SharedObjectTemplate::SFOT);
	templateFactory.registerObject<SharedInstallationObjectTemplate>(SharedObjectTemplate::SIOT);
	templateFactory.registerObject<SharedResourceContainerObjectTemplate>(SharedObjectTemplate::RCCT);
	templateFactory.registerObject<SharedShipObjectTemplate>(SharedObjectTemplate::SSHP);
	templateFactory.registerObject<SharedWeaponObjectTemplate>(SharedObjectTemplate::SWOT);
	templateFactory.registerObject<SharedGroupObjectTemplate>(SharedObjectTemplate::SGRP);
	templateFactory.registerObject<SharedGuildObjectTemplate>(SharedObjectTemplate::SGLD);
	templateFactory.registerObject<SharedJediManagerTemplate>(SharedObjectTemplate::SJED);
	templateFactory.registerObject<SharedCellObjectTemplate>(SharedObjectTemplate::CCLT);
	templateFactory.registerObject<SharedIntangibleObjectTemplate>(SharedObjectTemplate::SITN);
	templateFactory.registerObject<SharedStaticObjectTemplate>(SharedObjectTemplate::STAT);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::STOT);
	templateFactory.registerObject<SharedUniverseObjectTemplate>(SharedObjectTemplate::SUNI);
	templateFactory.registerObject<CharacterBuilderTerminalTemplate>(SharedObjectTemplate::CHARACTERBUILDERTERMINAL);

}
