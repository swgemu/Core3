/*
 * TemplateManager.cpp
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#include "TemplateManager.h"
#include "TemplateCRCMap.h"
#include "PortalLayoutMap.h"

#include "server/zone/templates/SharedObjectTemplate.h"
#include "server/zone/templates/intangible/SharedConstructionContractObjectTemplate.h"
#include "server/zone/templates/intangible/SharedManufactureSchematicObjectTemplate.h"
#include "server/zone/templates/intangible/SharedDraftSchematicObjectTemplate.h"
#include "server/zone/templates/intangible/DraftSchematicObjectTemplate.h"
#include "server/zone/templates/intangible/SharedMissionDataObjectTemplate.h"
#include "server/zone/templates/intangible/SharedMissionListEntryObjectTemplate.h"
#include "server/zone/templates/intangible/SharedMissionObjectTemplate.h"
#include "server/zone/templates/intangible/SharedPlayerObjectTemplate.h"
#include "server/zone/templates/intangible/SharedTokenObjectTemplate.h"
#include "server/zone/templates/intangible/SharedWaypointObjectTemplate.h"
#include "server/zone/templates/tangible/SharedBattlefieldMarkerObjectTemplate.h"
#include "server/zone/templates/tangible/SharedBuildingObjectTemplate.h"
#include "server/zone/templates/tangible/SharedCountingObjectTemplate.h"
#include "server/zone/templates/tangible/NonPlayerCreatureObjectTemplate.h"
#include "server/zone/templates/tangible/SharedCreatureObjectTemplate.h"
#include "server/zone/templates/tangible/SharedFactoryObjectTemplate.h"
#include "server/zone/templates/tangible/SharedInstallationObjectTemplate.h"
#include "server/zone/templates/tangible/SharedResourceContainerObjectTemplate.h"
#include "server/zone/templates/tangible/SharedShipObjectTemplate.h"
#include "server/zone/templates/tangible/SharedWeaponObjectTemplate.h"
#include "server/zone/templates/tangible/StimPackTemplate.h"
#include "server/zone/templates/tangible/ConsumableTemplate.h"
#include "server/zone/templates/tangible/InstrumentObjectTemplate.h"
#include "server/zone/templates/tangible/RangedStimPackTemplate.h"
#include "server/zone/templates/tangible/EnhancePackTemplate.h"
#include "server/zone/templates/tangible/CurePackTemplate.h"
#include "server/zone/templates/tangible/StatePackTemplate.h"
#include "server/zone/templates/tangible/DotPackTemplate.h"
#include "server/zone/templates/tangible/WoundPackTemplate.h"
#include "server/zone/templates/tangible/ArmorObjectTemplate.h"
#include "server/zone/templates/tangible/CharacterBuilderTerminalTemplate.h"
#include "server/zone/templates/tangible/LootkitObjectTemplate.h"
#include "server/zone/templates/tangible/LightsaberCrystalObjectTemplate.h"
#include "server/zone/templates/tangible/LootSchematicTemplate.h"
#include "server/zone/templates/tangible/GamblingTerminalTemplate.h"
#include "server/zone/templates/tangible/FireworkObjectTemplate.h"
#include "server/zone/templates/tangible/CampKitTemplate.h"
#include "server/zone/templates/tangible/CampStructureTemplate.h"
#include "server/zone/templates/tangible/TrapTemplate.h"
#include "server/zone/templates/tangible/DiceTemplate.h"
#include "server/zone/templates/tangible/CamoKitTemplate.h"
#include "server/zone/templates/universe/SharedGroupObjectTemplate.h"
#include "server/zone/templates/universe/SharedGuildObjectTemplate.h"
#include "server/zone/templates/universe/SharedJediManagerTemplate.h"
#include "server/zone/templates/SharedCellObjectTemplate.h"
#include "server/zone/templates/SharedIntangibleObjectTemplate.h"
#include "server/zone/templates/SharedStaticObjectTemplate.h"
#include "server/zone/templates/SharedTangibleObjectTemplate.h"
#include "server/zone/templates/SharedUniverseObjectTemplate.h"
#include "server/zone/templates/tangible/tool/SurveyToolTemplate.h"
#include "server/zone/templates/tangible/tool/CraftingToolTemplate.h"
#include "server/zone/templates/tangible/tool/CraftingStationTemplate.h"
#include "server/zone/templates/tangible/tool/SlicingToolTemplate.h"
#include "server/zone/templates/tangible/CloningBuildingObjectTemplate.h"
#include "server/zone/templates/tangible/HospitalBuildingObjectTemplate.h"
#include "server/zone/templates/tangible/RecreationBuildingObjectTemplate.h"
#include "server/zone/templates/resource_container/ResourceSpawnTemplate.h"
#include "server/zone/templates/tangible/DeedTemplate.h"
#include "server/zone/templates/tangible/StructureDeedTemplate.h"
#include "server/zone/templates/tangible/VehicleDeedTemplate.h"
#include "server/zone/templates/tangible/MissionTerminalTemplate.h"
#include "server/zone/templates/tangible/RobeObjectTemplate.h"
#include "server/zone/templates/tangible/PlayerCreatureTemplate.h"
#include "server/zone/templates/tangible/VendorCreatureTemplate.h"
#include "server/zone/templates/tangible/ContainerTemplate.h"
#include "server/zone/templates/tangible/ElevatorTerminalTemplate.h"
#include "server/zone/templates/tangible/PowerupTemplate.h"
#include "server/zone/templates/tangible/LiveSampleTemplate.h"
#include "server/zone/templates/tangible/CreatureHabitatTemplate.h"
#include "server/zone/templates/tangible/tool/RepairToolTemplate.h"

#include "server/conf/ConfigManager.h"
#include "server/zone/templates/installation/FactoryObjectTemplate.h"

#include "server/zone/objects/tangible/wearables/ArmorObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/creature/CreatureState.h"
#include "server/zone/objects/creature/CreatureFlag.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/templates/customization/AssetCustomizationManagerTemplate.h"
#include "server/zone/templates/appearance/PortalLayout.h"
#include "server/zone/templates/appearance/PaletteTemplate.h"
#include "server/zone/templates/appearance/AppearanceRedirect.h"
#include "server/zone/templates/appearance/FloorMesh.h"
#include "server/zone/templates/appearance/MeshAppearanceTemplate.h"
#include "server/zone/templates/appearance/DetailAppearanceTemplate.h"
#include "server/zone/templates/appearance/ComponentAppearanceTemplate.h"
#include "server/zone/templates/footprint/StructureFootprint.h"
#include "server/zone/templates/slots/SlotId.h"
#include "server/zone/managers/customization/CustomizationIdManager.h"
#include "server/zone/templates/params/PaletteColorCustomizationVariable.h"

#include "tre3/TreeArchive.h"

#include "server/zone/managers/director/DirectorManager.h"
#include "server/zone/managers/components/ComponentManager.h"

#include "server/conf/ConfigManager.h"

Lua* TemplateManager::luaTemplatesInstance = NULL;

AtomicInteger TemplateManager::loadedTemplatesCount;

TemplateManager::TemplateManager() {
	setLogging(false);
	setGlobalLogging(true);
	setLoggingName("TemplateManager");

	// preload lua files for component checks
	DirectorManager::instance()->getLuaInstance();

	registerTemplateObjects();

	luaTemplatesInstance = new Lua();
	luaTemplatesInstance->init();

	templateCRCMap = new TemplateCRCMap();
	clientTemplateCRCMap = new ClientTemplateCRCMap();

	portalLayoutMap = new PortalLayoutMap();
	floorMeshMap = new FloorMeshMap();
	appearanceMap = new AppearanceMap();
	treeDirectory = NULL;

	registerFunctions();
	registerGlobals();

	loadTreArchive();
	loadSlotDefinitions();
	loadPlanetMapCategories();
	loadAssetCustomizationManager();
}

TemplateManager::~TemplateManager() {
	delete templateCRCMap;
	templateCRCMap = NULL;

	delete clientTemplateCRCMap;
	clientTemplateCRCMap = NULL;

	delete luaTemplatesInstance;
	luaTemplatesInstance = NULL;

	delete portalLayoutMap;
	portalLayoutMap = NULL;

	delete floorMeshMap;
	floorMeshMap = NULL;
}

void TemplateManager::loadSlotDefinitions() {
	info("Loading slot definitions");

	IffStream* iffStream = openIffFile("abstract/slot/slot_definition/slot_definitions.iff");

	if (iffStream == NULL) {
		error("Slot definitions can't be found.");
		return;
	}

	//TODO: Should we fool with encapsulating this within a SlotDefinitionsMap?
	//Note: There is no parent form type, just the version: 0006...

	iffStream->openForm('0006');

	Chunk* data = iffStream->openChunk('DATA');

	while (data->hasData()) {
		Reference<SlotId*> slotId = new SlotId();
		slotId->readObject(data);

		slotDefinitions.put(slotId->getSlotName(), slotId);
	}

	iffStream->closeChunk('DATA');
	iffStream->closeForm('0006');

	delete iffStream;

	info("Loaded " + String::valueOf(slotDefinitions.size()) + " slot definitions.", true);
}

void TemplateManager::loadAssetCustomizationManager() {
	info("loading asset customization manager", true);

	IffStream* iffStream = openIffFile("customization/asset_customization_manager.iff");

	if (iffStream == NULL) {
		error("Asset customization manager data not found.");
		return;
	}

	AssetCustomizationManagerTemplate::instance()->readObject(iffStream);

	delete iffStream;

	/*printf("getting cust vars\n");
	//uint32 appearanceFileCRC, VectorMap<String, Reference<CustomizationVariable*> >& variables, bool skipShared
	VectorMap<String, Reference<CustomizationVariable*> > variables;
	AssetCustomizationManagerTemplate::instance()->getCustomizationVariables(String("appearance/wp_mle_sword_lightsaber_blade_anakin.lsb").hashCode(), variables, false);

	for (int i = 0; i < variables.size(); ++i) {
		printf("%s\n", variables.elementAt(i).getKey().toCharArray());
	}*/

	info("loading customization id manager", true);

	iffStream = openIffFile("customization/customization_id_manager.iff");

	if (iffStream == NULL) {
		error("Customization Id manager data not found.");
		return;
	}

	CustomizationIdManager::instance()->readObject(iffStream);

	delete iffStream;

	iffStream = openIffFile("datatables/customization/palette_columns.iff");

	if (iffStream == NULL) {
		error("Customization palette columns data not found.");
		return;
	}

	CustomizationIdManager::instance()->loadPaletteColumns(iffStream);

	delete iffStream;

	iffStream = openIffFile("datatables/customization/hair_assets_skill_mods.iff");

	if (iffStream == NULL) {
		error("Hair assets data not found.");
		return;
	}

	CustomizationIdManager::instance()->loadHairAssetsSkillMods(iffStream);

	delete iffStream;

	iffStream = openIffFile("datatables/customization/allow_bald.iff");

	if (iffStream == NULL) {
		error("allow bald data not found");
		return;
	}

	CustomizationIdManager::instance()->loadAllowBald(iffStream);

	delete iffStream;
}

Reference<SlotDescriptor*> TemplateManager::getSlotDescriptor(const String& filename) {
	//If the slot descriptor doesn't already exist, attempt to load it.
	if (!slotDescriptors.contains(filename)) {
		IffStream* iffStream = openIffFile(filename);

		if (iffStream == NULL)
			return NULL; //Descriptor does not exist.

		Reference<SlotDescriptor*> slotDesc = new SlotDescriptor();
		slotDesc->readObject(iffStream);

		slotDescriptors.put(filename, slotDesc);
	}

	return slotDescriptors.get(filename);
}

PaletteTemplate* TemplateManager::getPaletteTemplate(const String& fileName) {
	PaletteTemplate* palette = NULL;

	ObjectInputStream* stream = openTreFile(fileName);

	if (stream == NULL)
		return NULL;

	palette = new PaletteTemplate();

	try {
		palette->readObject(stream);
	} catch (Exception& e) {
		error("could not parse palette template: " + String::valueOf(fileName));
		error(e.getMessage());

		delete palette;
		palette = NULL;
	}

	delete stream;

	return palette;
}

Reference<ArrangementDescriptor*> TemplateManager::getArrangementDescriptor(const String& filename) {
	//If the slot descriptor doesn't already exist, attempt to load it.
	if (!arrangementDescriptors.contains(filename)) {
		IffStream* iffStream = openIffFile(filename);

		if (iffStream == NULL)
			return NULL; //Descriptor does not exist.

		Reference<ArrangementDescriptor*> slotDesc = new ArrangementDescriptor();
		slotDesc->readObject(iffStream);

		arrangementDescriptors.put(filename, slotDesc);
	}

	return arrangementDescriptors.get(filename);
}

void TemplateManager::loadPlanetMapCategories() {
	IffStream* iffStream = openIffFile("datatables/player/planet_map_cat.iff");

	if (iffStream == NULL) {
		error("Planet map categories could not be found.");
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	delete iffStream;

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		DataTableRow* row = dtiff.getRow(i);

		Reference<PlanetMapCategory*> planetMapCategory = new PlanetMapCategory();
		planetMapCategory->parseFromDataTableRow(row);

		planetMapCategoryList.put(planetMapCategory->getName(), planetMapCategory);
	}

	info("Loaded " + String::valueOf(planetMapCategoryList.size()) + " planet map categories.", true);
}

void TemplateManager::loadLuaTemplates() {
	info("Loading object templates", true);

	int count = ComponentManager::instance()->size();

	try {
		luaTemplatesInstance->runFile("scripts/object/main.lua");
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}

	printf("\n");
	info("Finished loading object templates", true);
	info(String::valueOf(ComponentManager::instance()->size() - count) + " ObjectMenuComponents loaded", true);
	info(String::valueOf(portalLayoutMap->size()) + " portal layouts loaded", true);
	info(String::valueOf(floorMeshMap->size()) + " floor meshes loaded", true);
	info(String::valueOf(structureFootprints.size()) + " structure footprints.", true);
}

void TemplateManager::loadTreArchive() {
	String path = ConfigManager::instance()->getTrePath();

	if (path.length() <= 1)
		return;

	Vector<String> treFilesToLoad = ConfigManager::instance()->getTreFiles();

	if (treFilesToLoad.size() == 0)
		return;

	info("Loading TRE archives...", true);

	treeDirectory = new TreeArchive();

	int j = 0;

	for (int i = 0; i < treFilesToLoad.size(); ++i) {
		String file = treFilesToLoad.get(i);

		String fullPath = path + "/";
		fullPath += file;

		treeDirectory->unpackFile(fullPath);
	}

	info("Finished loading TRE archives.", true);
}

void TemplateManager::addTemplate(uint32 key, const String& fullName, LuaObject* templateData) {
	uint32 templateType = templateData->getIntField("templateType");
	String clientTemplateFile = templateData->getStringField("clientTemplateFileName");

	SharedObjectTemplate* templateObject = templateFactory.createObject(templateType);

	if (templateObject == NULL) {
		error("error creating template from lua with templateType 0x" + String::hexvalueOf((int)templateType));

		return;
	}

	//info("loading " + fullName, true);

	String fileName = fullName.subString(fullName.lastIndexOf('/') + 1, fullName.lastIndexOf('.'));

	templateObject->setFullTemplateString(fullName);
	templateObject->setTemplateFileName(fileName);

	if (!clientTemplateFile.isEmpty()) {
		IffStream* iffStream = openIffFile(clientTemplateFile);

		if (iffStream != NULL) {
			templateObject->readObject(iffStream);
		}

		delete iffStream;
	}

	templateObject->readObject(templateData);

	if (!clientTemplateFile.isEmpty())
		templateObject->addDerivedFile(clientTemplateFile);

	//info("loaded " + fullName);

	if (templateCRCMap->put(key, templateObject) != NULL) {
		//error("duplicate template for " + fullName);
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
	templateFactory.registerObject<LootkitObjectTemplate>(SharedObjectTemplate::LOOTKIT);
	templateFactory.registerObject<LootSchematicTemplate>(SharedObjectTemplate::LOOTSCHEMATIC);
	templateFactory.registerObject<GamblingTerminalTemplate>(SharedObjectTemplate::GAMBLINGTERMINAL);
	templateFactory.registerObject<FireworkObjectTemplate>(SharedObjectTemplate::FIREWORK);
	templateFactory.registerObject<SurveyToolTemplate>(SharedObjectTemplate::SURVEYTOOL);
	templateFactory.registerObject<CraftingToolTemplate>(SharedObjectTemplate::CRAFTINGTOOL);
	templateFactory.registerObject<CraftingStationTemplate>(SharedObjectTemplate::CRAFTINGSTATION);
	templateFactory.registerObject<ResourceSpawnTemplate>(SharedObjectTemplate::RESOURCESPAWN);
	templateFactory.registerObject<ArmorObjectTemplate>(SharedObjectTemplate::ARMOROBJECT);
	templateFactory.registerObject<DeedTemplate>(SharedObjectTemplate::DEED);
	templateFactory.registerObject<StructureDeedTemplate>(SharedObjectTemplate::STRUCTUREDEED);
	templateFactory.registerObject<VehicleDeedTemplate>(SharedObjectTemplate::VEHICLEDEED);
	templateFactory.registerObject<MissionTerminalTemplate>(SharedObjectTemplate::MISSIONTERMINAL);
	templateFactory.registerObject<RobeObjectTemplate>(SharedObjectTemplate::ROBEOBJECT);
	templateFactory.registerObject<CloningBuildingObjectTemplate>(SharedObjectTemplate::CLONINGBUILDING);
	templateFactory.registerObject<HospitalBuildingObjectTemplate>(SharedObjectTemplate::HOSPITALBUILDING);
	templateFactory.registerObject<RecreationBuildingObjectTemplate>(SharedObjectTemplate::RECREATIONBUILDING);
	templateFactory.registerObject<DraftSchematicObjectTemplate>(SharedObjectTemplate::DRAFTSCHEMATIC);
	templateFactory.registerObject<NonPlayerCreatureObjectTemplate>(SharedObjectTemplate::NPCCREATURE);
	templateFactory.registerObject<FactoryObjectTemplate>(SharedObjectTemplate::FACTORY);
	templateFactory.registerObject<StimPackTemplate>(SharedObjectTemplate::STIMPACK);
	templateFactory.registerObject<RangedStimPackTemplate>(SharedObjectTemplate::RANGEDSTIMPACK);
	templateFactory.registerObject<EnhancePackTemplate>(SharedObjectTemplate::ENHANCEPACK);
	templateFactory.registerObject<CurePackTemplate>(SharedObjectTemplate::CUREPACK);
	templateFactory.registerObject<DotPackTemplate>(SharedObjectTemplate::DOTPACK);
	templateFactory.registerObject<WoundPackTemplate>(SharedObjectTemplate::WOUNDPACK);
	templateFactory.registerObject<StatePackTemplate>(SharedObjectTemplate::STATEPACK);
	templateFactory.registerObject<ConsumableTemplate>(SharedObjectTemplate::CONSUMABLE);
	templateFactory.registerObject<InstrumentObjectTemplate>(SharedObjectTemplate::INSTRUMENT);
	templateFactory.registerObject<CampKitTemplate>(SharedObjectTemplate::CAMPKIT);
	templateFactory.registerObject<PlayerCreatureTemplate>(SharedObjectTemplate::PLAYERCREATURE);
	templateFactory.registerObject<SlicingToolTemplate>(SharedObjectTemplate::SLICINGTOOL);
	templateFactory.registerObject<ContainerTemplate>(SharedObjectTemplate::CONTAINER);
	templateFactory.registerObject<ElevatorTerminalTemplate>(SharedObjectTemplate::ELEVATORTERMINAL);
	templateFactory.registerObject<VendorCreatureTemplate>(SharedObjectTemplate::VENDORCREATURE);
	templateFactory.registerObject<CampStructureTemplate>(SharedObjectTemplate::CAMPSTRUCTURE);
	templateFactory.registerObject<TrapTemplate>(SharedObjectTemplate::TRAP);
	templateFactory.registerObject<CamoKitTemplate>(SharedObjectTemplate::CAMOKIT);
	templateFactory.registerObject<PowerupTemplate>(SharedObjectTemplate::POWERUP);
	templateFactory.registerObject<DiceTemplate>(SharedObjectTemplate::DICE);
	templateFactory.registerObject<LiveSampleTemplate>(SharedObjectTemplate::LIVESAMPLE);
	templateFactory.registerObject<CreatureHabitatTemplate>(SharedObjectTemplate::CREATUREHABITAT);
	templateFactory.registerObject<RepairToolTemplate>(SharedObjectTemplate::REPAIRTOOL);
	templateFactory.registerObject<LightsaberCrystalObjectTemplate>(SharedObjectTemplate::LIGHTSABERCRYSTAL);
}

void TemplateManager::registerFunctions() {
	//lua generic
	lua_register(luaTemplatesInstance->getLuaState(), "includeFile", includeFile);
	lua_register(luaTemplatesInstance->getLuaState(), "crcString", crcString);
	lua_register(luaTemplatesInstance->getLuaState(), "addTemplateCRC", addTemplateCRC);
	lua_register(luaTemplatesInstance->getLuaState(), "addClientTemplate", addClientTemplate);
}

void TemplateManager::registerGlobals() {
	luaTemplatesInstance->setGlobalLong("DISEASED", CreatureState::DISEASED);
	luaTemplatesInstance->setGlobalLong("ONFIRE", CreatureState::ONFIRE);
	luaTemplatesInstance->setGlobalLong("POISONED", CreatureState::POISONED);
	luaTemplatesInstance->setGlobalLong("BLINDED", CreatureState::BLINDED);
	luaTemplatesInstance->setGlobalLong("STUNNED", CreatureState::STUNNED);
	luaTemplatesInstance->setGlobalLong("DIZZY", CreatureState::DIZZY);
	luaTemplatesInstance->setGlobalLong("INTIMIDATED", CreatureState::INTIMIDATED);
	luaTemplatesInstance->setGlobalLong("IMMOBILIZED", CreatureState::IMMOBILIZED);
	luaTemplatesInstance->setGlobalLong("FROZEN", CreatureState::FROZEN);

	luaTemplatesInstance->setGlobalShort("HEALTH", CreatureAttribute::HEALTH);
	luaTemplatesInstance->setGlobalShort("ACTION", CreatureAttribute::ACTION);
	luaTemplatesInstance->setGlobalShort("MIND", CreatureAttribute::MIND);

	luaTemplatesInstance->setGlobalInt("KINETIC", WeaponObject::KINETIC);
	luaTemplatesInstance->setGlobalInt("ENERGY", WeaponObject::ENERGY);
	luaTemplatesInstance->setGlobalInt("ELECTRICITY", WeaponObject::ELECTRICITY);
	luaTemplatesInstance->setGlobalInt("STUN", WeaponObject::STUN);
	luaTemplatesInstance->setGlobalInt("BLAST", WeaponObject::BLAST);
	luaTemplatesInstance->setGlobalInt("HEAT", WeaponObject::HEAT);
	luaTemplatesInstance->setGlobalInt("COLD", WeaponObject::COLD);
	luaTemplatesInstance->setGlobalInt("ACID", WeaponObject::ACID);
	luaTemplatesInstance->setGlobalInt("LIGHTSABER", WeaponObject::LIGHTSABER);
	luaTemplatesInstance->setGlobalInt("FORCE", WeaponObject::FORCE);

	luaTemplatesInstance->setGlobalInt("NONE", WeaponObject::NONE);
	luaTemplatesInstance->setGlobalInt("LIGHT", WeaponObject::LIGHT);
	luaTemplatesInstance->setGlobalInt("MEDIUM", WeaponObject::MEDIUM);
	luaTemplatesInstance->setGlobalInt("HEAVY", WeaponObject::HEAVY);

	luaTemplatesInstance->setGlobalInt("ATTACKABLE", CreatureFlag::ATTACKABLE);
	luaTemplatesInstance->setGlobalInt("AGGRESSIVE", CreatureFlag::AGGRESSIVE);
	luaTemplatesInstance->setGlobalInt("OVERT", CreatureFlag::OVERT);
	luaTemplatesInstance->setGlobalInt("TEF", CreatureFlag::TEF);
	luaTemplatesInstance->setGlobalInt("PLAYER", CreatureFlag::PLAYER);
	luaTemplatesInstance->setGlobalInt("ENEMY", CreatureFlag::ENEMY);
	luaTemplatesInstance->setGlobalInt("CHANGEFACTIONSTATUS", CreatureFlag::CHANGEFACTIONSTATUS);
	luaTemplatesInstance->setGlobalInt("BLINK_GREEN", CreatureFlag::BLINK_GREEN);

	luaTemplatesInstance->setGlobalInt("MELEEATTACK", WeaponObject::MELEEATTACK);
	luaTemplatesInstance->setGlobalInt("RANGEDATTACK", WeaponObject::RANGEDATTACK);
	luaTemplatesInstance->setGlobalInt("FORCEATTACK", WeaponObject::FORCEATTACK);
	luaTemplatesInstance->setGlobalInt("TRAPATTACK", WeaponObject::TRAPATTACK);
	luaTemplatesInstance->setGlobalInt("GRENADEATTACK", WeaponObject::GRENADEATTACK);
	luaTemplatesInstance->setGlobalInt("HEAVYACIDBEAMATTACK", WeaponObject::HEAVYACIDBEAMATTACK);
	luaTemplatesInstance->setGlobalInt("HEAVYLIGHTNINGBEAMATTACK", WeaponObject::HEAVYLIGHTNINGBEAMATTACK);
	luaTemplatesInstance->setGlobalInt("HEAVYPARTICLEBEAMATTACK", WeaponObject::HEAVYPARTICLEBEAMATTACK);
	luaTemplatesInstance->setGlobalInt("HEAVYROCKETLAUNCHERATTACK", WeaponObject::HEAVYROCKETLAUNCHERATTACK);
	luaTemplatesInstance->setGlobalInt("HEAVYLAUNCHERATTACK", WeaponObject::HEAVYLAUNCHERATTACK);

	luaTemplatesInstance->setGlobalInt("OBJECTDESTRUCTION", ObserverEventType::OBJECTDESTRUCTION);
	luaTemplatesInstance->setGlobalInt("DAMAGERECEIVED", ObserverEventType::DAMAGERECEIVED);
	luaTemplatesInstance->setGlobalInt("PLAYERKILLED", ObserverEventType::PLAYERKILLED);
	luaTemplatesInstance->setGlobalInt("PLAYERCLONED", ObserverEventType::PLAYERCLONED);
	luaTemplatesInstance->setGlobalInt("CRAFTINGASSEMBLY", ObserverEventType::CRAFTINGASSEMBLY);
	luaTemplatesInstance->setGlobalInt("CRAFTINGEXPERIMENTATION", ObserverEventType::CRAFTINGEXPERIMENTATION);
	luaTemplatesInstance->setGlobalInt("HEALINGPERFORMED", ObserverEventType::HEALINGPERFORMED);
	luaTemplatesInstance->setGlobalInt("ENHANCINGPERFORMED", ObserverEventType::ENHANCINGPERFORMED);
	luaTemplatesInstance->setGlobalInt("WOUNDHEALINGPERFORMED", ObserverEventType::WOUNDHEALINGPERFORMED);
	luaTemplatesInstance->setGlobalInt("XPAWARDED", ObserverEventType::XPAWARDED);
	luaTemplatesInstance->setGlobalInt("SPICEDOWNERACTIVATED", ObserverEventType::SPICEDOWNERACTIVATED);

	luaTemplatesInstance->setGlobalInt("SHOT", SharedObjectTemplate::SHOT);
	luaTemplatesInstance->setGlobalInt("STOT", SharedObjectTemplate::STOT);
	luaTemplatesInstance->setGlobalInt("SBMK", SharedObjectTemplate::SBMK);
	luaTemplatesInstance->setGlobalInt("SBOT", SharedObjectTemplate::SBOT);
	luaTemplatesInstance->setGlobalInt("STAT", SharedObjectTemplate::STAT);
	luaTemplatesInstance->setGlobalInt("SIOT", SharedObjectTemplate::SIOT);
	luaTemplatesInstance->setGlobalInt("CCLT", SharedObjectTemplate::CCLT);
	luaTemplatesInstance->setGlobalInt("SCOU", SharedObjectTemplate::SCOU);
	luaTemplatesInstance->setGlobalInt("SDSC", SharedObjectTemplate::SDSC);
	luaTemplatesInstance->setGlobalInt("SFOT", SharedObjectTemplate::SFOT);
	luaTemplatesInstance->setGlobalInt("SGRP", SharedObjectTemplate::SGRP);
	luaTemplatesInstance->setGlobalInt("SITN", SharedObjectTemplate::SITN);
	luaTemplatesInstance->setGlobalInt("SGLD", SharedObjectTemplate::SGLD);
	luaTemplatesInstance->setGlobalInt("SJED", SharedObjectTemplate::SJED);
	luaTemplatesInstance->setGlobalInt("SMSC", SharedObjectTemplate::SMSC);
	luaTemplatesInstance->setGlobalInt("SMSO", SharedObjectTemplate::SMSO);
	luaTemplatesInstance->setGlobalInt("SMSD", SharedObjectTemplate::SMSD);
	luaTemplatesInstance->setGlobalInt("SMLE", SharedObjectTemplate::SMLE);
	luaTemplatesInstance->setGlobalInt("SPLY", SharedObjectTemplate::SPLY);
	luaTemplatesInstance->setGlobalInt("RCCT", SharedObjectTemplate::RCCT);
	luaTemplatesInstance->setGlobalInt("SSHP", SharedObjectTemplate::SSHP);
	luaTemplatesInstance->setGlobalInt("SUNI", SharedObjectTemplate::SUNI);
	luaTemplatesInstance->setGlobalInt("SWAY", SharedObjectTemplate::SWAY);
	luaTemplatesInstance->setGlobalInt("STOK", SharedObjectTemplate::STOK);
	luaTemplatesInstance->setGlobalInt("SWOT", SharedObjectTemplate::SWOT);
	luaTemplatesInstance->setGlobalInt("SCNC", SharedObjectTemplate::SCNC);
	luaTemplatesInstance->setGlobalInt("SCOT", SharedObjectTemplate::SCOT);
	luaTemplatesInstance->setGlobalInt("CHARACTERBUILDERTERMINAL", SharedObjectTemplate::CHARACTERBUILDERTERMINAL);
	luaTemplatesInstance->setGlobalInt("LOOTKIT", SharedObjectTemplate::LOOTKIT);
	luaTemplatesInstance->setGlobalInt("LOOTSCHEMATIC", SharedObjectTemplate::LOOTSCHEMATIC);
	luaTemplatesInstance->setGlobalInt("GAMBLINGTERMINAL", SharedObjectTemplate::GAMBLINGTERMINAL);
	luaTemplatesInstance->setGlobalInt("FIREWORK", SharedObjectTemplate::FIREWORK);
	luaTemplatesInstance->setGlobalInt("SURVEYTOOL", SharedObjectTemplate::SURVEYTOOL);
	luaTemplatesInstance->setGlobalInt("CRAFTINGTOOL", SharedObjectTemplate::CRAFTINGTOOL);
	luaTemplatesInstance->setGlobalInt("CRAFTINGSTATION", SharedObjectTemplate::CRAFTINGSTATION);
	luaTemplatesInstance->setGlobalInt("RESOURCESPAWN", SharedObjectTemplate::RESOURCESPAWN);
	luaTemplatesInstance->setGlobalInt("ARMOROBJECT", SharedObjectTemplate::ARMOROBJECT);
	luaTemplatesInstance->setGlobalInt("ROBEOBJECT", SharedObjectTemplate::ROBEOBJECT);
	luaTemplatesInstance->setGlobalInt("LIGHTSABERCRYSTAL", SharedObjectTemplate::LIGHTSABERCRYSTAL);
	luaTemplatesInstance->setGlobalInt("DEED", SharedObjectTemplate::DEED);
	luaTemplatesInstance->setGlobalInt("STRUCTUREDEED", SharedObjectTemplate::STRUCTUREDEED);
	luaTemplatesInstance->setGlobalInt("VEHICLEDEED", SharedObjectTemplate::VEHICLEDEED);
	luaTemplatesInstance->setGlobalInt("MISSIONTERMINAL", SharedObjectTemplate::MISSIONTERMINAL);
	luaTemplatesInstance->setGlobalInt("CLONINGBUILDING", SharedObjectTemplate::CLONINGBUILDING);
	luaTemplatesInstance->setGlobalInt("DRAFTSCHEMATIC", SharedObjectTemplate::DRAFTSCHEMATIC);
	luaTemplatesInstance->setGlobalInt("NPCCREATURE", SharedObjectTemplate::NPCCREATURE);
	luaTemplatesInstance->setGlobalInt("LAIRTEMPLATE", SharedObjectTemplate::LAIRTEMPLATE);
	luaTemplatesInstance->setGlobalInt("FACTORY", SharedObjectTemplate::FACTORY);
	luaTemplatesInstance->setGlobalInt("STIMPACK", SharedObjectTemplate::STIMPACK);
	luaTemplatesInstance->setGlobalInt("RANGEDSTIMPACK", SharedObjectTemplate::RANGEDSTIMPACK);
	luaTemplatesInstance->setGlobalInt("ENHANCEPACK", SharedObjectTemplate::ENHANCEPACK);
	luaTemplatesInstance->setGlobalInt("CUREPACK", SharedObjectTemplate::CUREPACK);
	luaTemplatesInstance->setGlobalInt("DOTPACK", SharedObjectTemplate::DOTPACK);
	luaTemplatesInstance->setGlobalInt("WOUNDPACK", SharedObjectTemplate::WOUNDPACK);
	luaTemplatesInstance->setGlobalInt("STATEPACK", SharedObjectTemplate::STATEPACK);
	luaTemplatesInstance->setGlobalInt("CONSUMABLE", SharedObjectTemplate::CONSUMABLE);
	luaTemplatesInstance->setGlobalInt("INSTRUMENT", SharedObjectTemplate::INSTRUMENT);
	luaTemplatesInstance->setGlobalInt("CAMPKIT", SharedObjectTemplate::CAMPKIT);
	luaTemplatesInstance->setGlobalInt("PLAYERCREATURE", SharedObjectTemplate::PLAYERCREATURE);
	luaTemplatesInstance->setGlobalInt("SLICINGTOOL", SharedObjectTemplate::SLICINGTOOL);
	luaTemplatesInstance->setGlobalInt("CONTAINER", SharedObjectTemplate::CONTAINER);
	luaTemplatesInstance->setGlobalInt("ELEVATORTERMINAL", SharedObjectTemplate::ELEVATORTERMINAL);
	luaTemplatesInstance->setGlobalInt("VENDORCREATURE", SharedObjectTemplate::VENDORCREATURE);
	luaTemplatesInstance->setGlobalInt("CAMPSTRUCTURE", SharedObjectTemplate::CAMPSTRUCTURE);
	luaTemplatesInstance->setGlobalInt("HOSPITALBUILDING", SharedObjectTemplate::HOSPITALBUILDING);
	luaTemplatesInstance->setGlobalInt("RECREATIONBUILDING", SharedObjectTemplate::RECREATIONBUILDING);
	luaTemplatesInstance->setGlobalInt("TRAP", SharedObjectTemplate::TRAP);
	luaTemplatesInstance->setGlobalInt("CAMOKIT", SharedObjectTemplate::CAMOKIT);
	luaTemplatesInstance->setGlobalInt("POWERUP", SharedObjectTemplate::POWERUP);
	luaTemplatesInstance->setGlobalInt("DICE", SharedObjectTemplate::DICE);
	luaTemplatesInstance->setGlobalInt("LIVESAMPLE", SharedObjectTemplate::LIVESAMPLE);
	luaTemplatesInstance->setGlobalInt("CREATUREHABITAT", SharedObjectTemplate::CREATUREHABITAT);
	luaTemplatesInstance->setGlobalInt("REPAIRTOOL", SharedObjectTemplate::REPAIRTOOL);

	luaTemplatesInstance->setGlobalInt("NO_HITLOCATION", CombatManager::NOLOCATION);
	luaTemplatesInstance->setGlobalInt("CHEST_HITLOCATION", CombatManager::CHEST);
	luaTemplatesInstance->setGlobalInt("ARMS_HITLOCATION", CombatManager::ARMS);
	luaTemplatesInstance->setGlobalInt("LEGS_HITLOCATION", CombatManager::LEGS);
	luaTemplatesInstance->setGlobalInt("HEAD_HITLOCATION", CombatManager::HEAD);
}

String TemplateManager::getTemplateFile(uint32 key) {
	SharedObjectTemplate* templateData = templateCRCMap->get(key);

	if (templateData == NULL) {
		String ascii = clientTemplateCRCMap->get(key);

		if (ascii.isEmpty())
			throw Exception("TemplateManager::getTemplateFile exception unknown template key 0x" + String::hexvalueOf((int)key));
		else
			return ascii;
	}

	return templateData->getFullTemplateString();
}

ObjectInputStream* TemplateManager::openTreFile(const String& fileName) {
	if (fileName.isEmpty())
		return NULL;

	IffStream* iffStream = NULL;

	if (treeDirectory == NULL)
		return NULL;

	int size = 0;
	byte* data = treeDirectory->getBytes(fileName, size);

	if (size == 0)
		return NULL;

	ObjectInputStream* stream = new ObjectInputStream((char*)data, size);

	delete [] data;

	return stream;
}

IffStream* TemplateManager::openIffFile(const String& fileName) {
	if (fileName.isEmpty())
		return NULL;

	IffStream* iffStream = NULL;

	if (treeDirectory == NULL)
		return NULL;

	int size = 0;
	byte* data = treeDirectory->getBytes(fileName, size);

	if (size == 0)
		return NULL;

	iffStream = new IffStream();

	if (iffStream != NULL) {
		try {
			if (!iffStream->parseChunks(data, size, fileName)) {
				delete iffStream;
				iffStream = NULL;
			}
		} catch (Exception& e) {
			delete iffStream;
			iffStream = NULL;
		}
	}

	delete [] data;

	return iffStream;
}

FloorMesh* TemplateManager::getFloorMesh(const String& fileName) {
	FloorMesh* floorMesh = floorMeshMap->get(fileName);

	if (floorMesh == NULL) {
		// read file

		IffStream* iffStream = openIffFile(fileName);

		if (iffStream != NULL) {
			try {
				floorMesh = new FloorMesh();

				floorMesh->readObject(iffStream);

				info("parsed " + fileName);
			} catch (Exception& e) {
				info("could not parse " + fileName);

				delete floorMesh;
				floorMesh = NULL;
			}

			delete iffStream;
			iffStream = NULL;

			floorMeshMap->put(fileName, floorMesh);
		}
	}

	return floorMesh;
	//return NULL;
}

AppearanceTemplate* TemplateManager::getAppearanceTemplate(const String& fileName) {
	AppearanceTemplate* meshAppearance = NULL;

	Locker locker(&appearanceMapLock);

	try {
		meshAppearance = appearanceMap->get(fileName);
	} catch (...) {
		error("unreported exception caught in AppearanceTemplate* TemplateManager::getAppearanceTemplate(const String& fileName)");
	}

	if (meshAppearance == NULL) {
		IffStream* iffStream = openIffFile(fileName);

		if (iffStream != NULL) {
			meshAppearance = instantiateAppearanceTemplate(iffStream);

			delete iffStream;
			iffStream = NULL;

			appearanceMap->put(fileName, meshAppearance);
		}
	}

	return meshAppearance;
}

AppearanceTemplate* TemplateManager::instantiateAppearanceTemplate(IffStream* iffStream) {
	uint32 formType = iffStream->getNextFormType();
	AppearanceTemplate* appTemplate = NULL;

	try {
		switch (formType) {
		case 'MESH':
			appTemplate = new MeshAppearanceTemplate();
			break;
		case 'CMPA':
			appTemplate = new ComponentAppearanceTemplate();
			break;
		case 'DTLA':
			appTemplate = new DetailAppearanceTemplate();
			break;
		case 'SMAT':
			break;
		case 'PEFT':
			break;
		case 'APT ': {
			AppearanceRedirect redirect;
			redirect.readObject(iffStream);

			return getAppearanceTemplate(redirect.getRedirectFile());
			break;
		}
		default:
			error("unknown appearance type " + String::hexvalueOf((int)formType));
			break;
		}

		if (appTemplate != NULL)
			appTemplate->readObject(iffStream);

	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}

	return appTemplate;
}

PortalLayout* TemplateManager::getPortalLayout(const String& fileName) {
	Locker _locker(&appearanceMapLock);

	PortalLayout* portalLayout = portalLayoutMap->get(fileName);

	if (portalLayout == NULL) {
		IffStream* iffStream = openIffFile(fileName);

		if (iffStream != NULL) {
			try {
				portalLayout = new PortalLayout();

				portalLayout->readObject(iffStream);

				info("parsed " + fileName);
			} catch (Exception& e) {
				info("could not parse " + fileName);

				delete portalLayout;
				portalLayout = NULL;
			}

			delete iffStream;
			iffStream = NULL;

			portalLayoutMap->put(fileName, portalLayout);
		}
	}

	return portalLayout;
	//return NULL;
}

SharedObjectTemplate* TemplateManager::getTemplate(uint32 key) {
	return templateCRCMap->get(key);
}

bool TemplateManager::existsTemplate(uint32 key) {
	return templateCRCMap->containsKey(key);
}

int TemplateManager::includeFile(lua_State* L) {
	String filename = Lua::getStringParameter(L);

	Lua::runFile("scripts/object/" + filename, L);

	return 0;
}

LuaObject* TemplateManager::getLuaObject(const String& iffTemplate) {
	if (templateCRCMap->get(iffTemplate.hashCode()) == NULL) {
		String luaFileName = iffTemplate.replaceAll(".iff", ".lua");

		luaTemplatesInstance->runFile("scripts/" + luaFileName);
	}

	if (templateCRCMap->get(iffTemplate.hashCode()) == NULL)
		return NULL;

	LuaFunction getObject(luaTemplatesInstance->getLuaState(), "getTemplate", 1);
	getObject << iffTemplate.hashCode(); // push first argument
	luaTemplatesInstance->callFunction(&getObject);

	LuaObject* result = new LuaObject(luaTemplatesInstance->getLuaState());

	if (!result->isValidTable()) {
		System::out << "Unknown lua object template " << iffTemplate << endl;

		delete result;

		return NULL;
	}

	return result;
}

int TemplateManager::crcString(lua_State* L) {
	String ascii = Lua::getStringParameter(L);

	uint32 crc = ascii.hashCode();

	lua_pushnumber(L, crc);

	return 1;
}

int TemplateManager::addTemplateCRC(lua_State* L) {
	String ascii =  lua_tostring(L, -2);

	LuaObject obj(L);

	uint32 crc = (uint32) ascii.hashCode();

	TemplateManager::instance()->addTemplate(crc, ascii, &obj);

//	uint64 seconds = Logger::getElapsedTime();

	int val = loadedTemplatesCount.increment();

	if (ConfigManager::instance()->isProgressMonitorActivated())
		if (val % 38 == 0)
			//printf("\r(%llu s) Loaded templates: [%d] / [15998]:", seconds, val);
			printf("\r\tLoading templates: [%d] / [15998]\t", val);

	//System::out << str;

	return 0;
}

int TemplateManager::addClientTemplate(lua_State* L) {
	String ascii = lua_tostring(L, -2);

	uint32 crc = (uint32) ascii.hashCode();

	TemplateManager::instance()->clientTemplateCRCMap->put(crc, ascii);
	return 0;
}

StructureFootprint* TemplateManager::loadStructureFootprint(const String& filePath) {
	if (filePath.isEmpty())
		return NULL;

	Reference<StructureFootprint*> structureFootprint = structureFootprints.get(filePath);

	if (structureFootprint != NULL)
		return structureFootprint;

	IffStream* iffStream = openIffFile(filePath);

	if (iffStream == NULL) {
		warning("Could not find referenced Structure Footprint file: " + filePath);
		return NULL;
	}

	structureFootprint = new StructureFootprint();
	structureFootprint->readObject(iffStream);

	delete iffStream;

	structureFootprints.put(filePath, structureFootprint);

	return structureFootprint;
}
