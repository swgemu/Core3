/*
 * TemplateManager.cpp
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#include "TemplateManager.h"
#include "TemplateCRCMap.h"
#include "PortalLayoutMap.h"

#include "zone/templates/SharedObjectTemplate.h"
//#include "zone/templates/intangible/SharedConstructionContractObjectTemplate.h"
//#include "zone/templates/intangible/SharedManufactureSchematicObjectTemplate.h"
//#include "zone/templates/intangible/SharedDraftSchematicObjectTemplate.h"
//#include "zone/templates/intangible/DraftSchematicObjectTemplate.h"
//#include "zone/templates/intangible/SharedMissionDataObjectTemplate.h"
//#include "zone/templates/intangible/SharedMissionListEntryObjectTemplate.h"
//#include "zone/templates/intangible/SharedMissionObjectTemplate.h"
#include "zone/templates/intangible/SharedPlayerObjectTemplate.h"
//#include "zone/templates/intangible/SharedTokenObjectTemplate.h"
//#include "zone/templates/intangible/SharedWaypointObjectTemplate.h"
//#include "zone/templates/tangible/SharedBattlefieldMarkerObjectTemplate.h"
#include "zone/templates/tangible/SharedBuildingObjectTemplate.h"
//#include "zone/templates/tangible/SharedCountingObjectTemplate.h"
//#include "zone/templates/tangible/NonPlayerCreatureObjectTemplate.h"
#include "zone/templates/tangible/SharedCreatureObjectTemplate.h"
#include "zone/templates/tangible/SharedFactoryObjectTemplate.h"
#include "zone/templates/tangible/SharedInstallationObjectTemplate.h"
//#include "zone/templates/tangible/SharedResourceContainerObjectTemplate.h"
#include "zone/templates/tangible/SharedShipObjectTemplate.h"
//#include "zone/templates/tangible/SharedWeaponObjectTemplate.h"
//S#include "zone/templates/tangible/VehicleObjectTemplate.h"
//#include "zone/templates/tangible/XpPurchaseTemplate.h"
//#include "zone/templates/universe/SharedGroupObjectTemplate.h"
//#include "zone/templates/universe/SharedGuildObjectTemplate.h"
//#include "zone/templates/universe/SharedJediManagerTemplate.h"
#include "zone/templates/SharedCellObjectTemplate.h"
#include "zone/templates/SharedIntangibleObjectTemplate.h"
#include "zone/templates/SharedStaticObjectTemplate.h"
#include "zone/templates/SharedTangibleObjectTemplate.h"
#include "zone/templates/SharedUniverseObjectTemplate.h"
//#include "zone/templates/tangible/tool/SurveyToolTemplate.h"
//#include "zone/templates/tangible/tool/RecycleToolTemplate.h"
//#include "zone/templates/tangible/tool/CraftingToolTemplate.h"
//#include "zone/templates/tangible/tool/CraftingStationTemplate.h"
//#include "zone/templates/tangible/tool/SlicingToolTemplate.h"
#include "zone/templates/tangible/HospitalBuildingObjectTemplate.h"
#include "zone/templates/tangible/RecreationBuildingObjectTemplate.h"
//#include "zone/templates/resource_container/ResourceSpawnTemplate.h"
//#include "zone/templates/tangible/DeedTemplate.h"
//#include "zone/templates/tangible/StructureDeedTemplate.h"
//#include "zone/templates/tangible/VehicleDeedTemplate.h"
//#include "zone/templates/tangible/PetDeedTemplate.h"
//#include "zone/templates/tangible/DroidDeedTemplate.h"
//#include "zone/templates/tangible/EventPerkDeedTemplate.h"
//#include "zone/templates/tangible/MissionTerminalTemplate.h"
#include "zone/templates/tangible/PlayerCreatureTemplate.h"
//#include "zone/templates/tangible/VendorCreatureTemplate.h"
#include "zone/templates/tangible/ContainerTemplate.h"
//#include "zone/templates/tangible/ElevatorTerminalTemplate.h"
////#include "zone/templates/tangible/PowerupTemplate.h"
//#include "zone/templates/tangible/LiveSampleTemplate.h"
//#include "zone/templates/tangible/CreatureHabitatTemplate.h"
//#include "zone/templates/tangible/tool/RepairToolTemplate.h"
//#include "zone/templates/tangible/VehicleCustomKitTemplate.h"
//#include "zone/templates/tangible/DroidCustomKitTemplate.h"
#include "zone/objects/tangible/TangibleObject.h"
#include "conf/ConfigManager.h"
#include "zone/templates/installation/FactoryObjectTemplate.h"

//#include "zone/objects/tangible/deed/eventperk/EventPerkDeed.h"
//#include "zone/objects/tangible/wearables/ArmorObject.h"
//#include "zone/objects/tangible/weapon/WeaponObject.h"
#include "zone/objects/creature/CreatureState.h"
#include "zone/objects/creature/CreatureFlag.h"
#include "zone/objects/creature/CreatureAttribute.h"
//#include "zone/templates/customization/AssetCustomizationManagerTemplate.h"
#include "zone/templates/appearance/PortalLayout.h"
#include "zone/templates/appearance/PaletteTemplate.h"
#include "zone/templates/appearance/AppearanceRedirect.h"
#include "zone/templates/appearance/FloorMesh.h"
#include "zone/templates/appearance/MeshAppearanceTemplate.h"
#include "zone/templates/appearance/DetailAppearanceTemplate.h"
#include "zone/templates/appearance/ComponentAppearanceTemplate.h"
#include "zone/templates/footprint/StructureFootprint.h"
#include "zone/templates/slots/SlotId.h"
//
//#include "zone/managers/customization/CustomizationIdManager.h"
//#include "zone/templates/params/PaletteColorCustomizationVariable.h"

#include "tre3/TreeArchive.h"

//#include "zone/managers/director/DirectorManager.h"
//#include "zone/managers/components/ComponentManager.h"
//#include "zone/managers/crafting/CraftingManager.h"

#include "conf/ConfigManager.h"

#include "DataArchiveStore.h"

Lua* TemplateManager::luaTemplatesInstance = NULL;

AtomicInteger TemplateManager::loadedTemplatesCount;

int TemplateManager::ERROR_CODE = NO_ERROR;

TemplateManager::TemplateManager() {
	setLogging(false);
	setGlobalLogging(true);
	setLoggingName("TemplateManager");
//
//	// preload lua files for component checks
//	DirectorManager::instance()->getLuaInstance();

	registerTemplateObjects();

	luaTemplatesInstance = new Lua();
	luaTemplatesInstance->init();

	templateCRCMap = new TemplateCRCMap();
	clientTemplateCRCMap = new ClientTemplateCRCMap();

	portalLayoutMap = new PortalLayoutMap();
	floorMeshMap = new FloorMeshMap();
	appearanceMap = new AppearanceMap();

	registerFunctions();
	registerGlobals();

	loadTreArchive();
	loadSlotDefinitions();
	loadPlanetMapCategories();
//	loadAssetCustomizationManager();
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

	HashTableIterator<String, AppearanceTemplate* > iterator = appearanceMap->iterator();

	while (iterator.hasNext()) {
		delete iterator.getNextValue();
	}

	delete appearanceMap;
	appearanceMap = NULL;
}

void TemplateManager::loadSlotDefinitions() {
	info("Loading slot definitions");

	IffStream* iffStream = openIffFile("abstract/slot/slot_definition/slot_definitions.iff");

	if (iffStream == NULL) {
		error("Slot definitions can't be found.");
		ERROR_CODE = SLOT_DEFINITION_FILE_NOT_FOUND;
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
//
//void TemplateManager::loadAssetCustomizationManager() {
//	info("loading asset customization manager", true);
//
//	IffStream* iffStream = openIffFile("customization/asset_customization_manager.iff");
//
//	if (iffStream == NULL) {
//		error("Asset customization manager data not found.");
//		ERROR_CODE = ASSETCUSTOMIZATIONMANAGER_FILE_NOT_FOUND;
//		return;
//	}
//
//	AssetCustomizationManagerTemplate::instance()->readObject(iffStream);
//
//	delete iffStream;
//
//	/*printf("getting cust vars\n");
//	//uint32 appearanceFileCRC, VectorMap<String, Reference<CustomizationVariable*> >& variables, bool skipShared
//	VectorMap<String, Reference<CustomizationVariable*> > variables;
//	AssetCustomizationManagerTemplate::instance()->getCustomizationVariables(STRING_HASHCODE("appearance/wp_mle_sword_lightsaber_blade_anakin.lsb"), variables, false);
//
//	for (int i = 0; i < variables.size(); ++i) {
//		printf("%s\n", variables.elementAt(i).getKey().toCharArray());
//	}*/
//
//	info("loading customization id manager", true);
//
//	iffStream = openIffFile("customization/customization_id_manager.iff");
//
//	if (iffStream == NULL) {
//		error("Customization Id manager data not found.");
//		ERROR_CODE = CUSTOMIZATION_ID_MANAGER_FILE_NOT_FOUND;
//		return;
//	}
//
//	CustomizationIdManager::instance()->readObject(iffStream);
//
//	delete iffStream;
//
//	iffStream = openIffFile("datatables/customization/palette_columns.iff");
//
//	if (iffStream == NULL) {
//		error("Customization palette columns data not found.");
//		ERROR_CODE = PALLETE_COLUMNS_FILE_NOT_FOUND;
//		return;
//	}
//
//	CustomizationIdManager::instance()->loadPaletteColumns(iffStream);
//
//	delete iffStream;
//
//	iffStream = openIffFile("datatables/customization/hair_assets_skill_mods.iff");
//
//	if (iffStream == NULL) {
//		error("Hair assets data not found.");
//		ERROR_CODE = HAIR_ASSETS_FILE_NOT_FOUND;
//		return;
//	}
//
//	CustomizationIdManager::instance()->loadHairAssetsSkillMods(iffStream);
//
//	delete iffStream;
//
//	iffStream = openIffFile("datatables/customization/allow_bald.iff");
//
//	if (iffStream == NULL) {
//		error("allow bald data not found");
//		ERROR_CODE = HAIR_ASSETS_FILE_NOT_FOUND;
//		return;
//	}
//
//	CustomizationIdManager::instance()->loadAllowBald(iffStream);
//
//	delete iffStream;
//}

Reference<SlotDescriptor*> TemplateManager::getSlotDescriptor(const String& filename) {
	//If the slot descriptor doesn't already exist, attempt to load it.
	if (!slotDescriptors.contains(filename)) {
		IffStream* iffStream = openIffFile(filename);

		if (iffStream == NULL)
			return NULL; //Descriptor does not exist.

		Reference<SlotDescriptor*> slotDesc = new SlotDescriptor();
		slotDesc->readObject(iffStream);

		slotDescriptors.put(filename, slotDesc);

		delete iffStream;
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
		error("could not parse palette template: " + String(fileName));
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

		delete iffStream;
	}

	return arrangementDescriptors.get(filename);
}

void TemplateManager::loadPlanetMapCategories() {
	IffStream* iffStream = openIffFile("datatables/player/planet_map_cat.iff");

	if (iffStream == NULL) {
		error("Planet map categories could not be found.");
		ERROR_CODE = PLANET_CAT_FILE_NOT_FOUND;
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

//	int count = ComponentManager::instance()->size();

	try {
		bool val = luaTemplatesInstance->runFile("scripts/object/main.lua");

		if (!val)
			ERROR_CODE = LOAD_LUA_TEMPLATE_ERROR;
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();

		ERROR_CODE = LOAD_LUA_TEMPLATE_ERROR;
	}

	printf("\n");
	info("Finished loading object templates", true);
//	info(String::valueOf(ComponentManager::instance()->size() - count) + " ObjectMenuComponents loaded", true);
	info(String::valueOf(portalLayoutMap->size()) + " portal layouts loaded", true);
	info(String::valueOf(floorMeshMap->size()) + " floor meshes loaded", true);
	info(String::valueOf(structureFootprints.size()) + " structure footprints.", true);

	delete luaTemplatesInstance;
	luaTemplatesInstance = NULL;
}

void TemplateManager::loadTreArchive() {
	String path = ConfigManager::instance()->getTrePath();

	if (path.length() <= 1) {
		ERROR_CODE = NO_TRE_PATH;
		return;
	}

	Vector<String> treFilesToLoad = ConfigManager::instance()->getTreFiles();

	if (treFilesToLoad.size() == 0) {
		ERROR_CODE = NO_TRE_FILES;
		return;
	}

	int res = DataArchiveStore::instance()->loadTres(path, treFilesToLoad);

	if (res != 0) {
		ERROR_CODE = LOAD_TRES_ERROR;
	}

/*	info("Loading TRE archives...", true);



	treeDirectory = new TreeArchive();

	int j = 0;

	for (int i = 0; i < treFilesToLoad.size(); ++i) {
		String file = treFilesToLoad.get(i);

		String fullPath = path + "/";
		fullPath += file;

		treeDirectory->unpackFile(fullPath);
	}


	info("Finished loading TRE archives.", true);*/
}

void TemplateManager::addTemplate(uint32 key, const String& fullName, LuaObject* templateData) {
	uint32 templateType = templateData->getIntField("templateType");
	String clientTemplateFile = templateData->getStringField("clientTemplateFileName");

	SharedObjectTemplate* templateObject = templateFactory.createObject(templateType);

	if (templateObject == NULL) {
		error("error creating " + clientTemplateFile + " from lua with templateType " + String::hexvalueOf((int)templateType));

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

			delete iffStream;
		}
	}

	templateObject->readObject(templateData);

	if (!clientTemplateFile.isEmpty())
		templateObject->addDerivedFile(clientTemplateFile);

	info("loaded " + fullName);

	if (templateCRCMap->put(key, templateObject) != NULL) {
		//error("duplicate template for " + fullName);
	}
}

void TemplateManager::registerTemplateObjects() {
	templateFactory.registerObject<SharedObjectTemplate>(SharedObjectTemplate::SHOT);
	templateFactory.registerObject<SharedIntangibleObjectTemplate>(SharedObjectTemplate::SCNC);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::SDSC);
	templateFactory.registerObject<SharedIntangibleObjectTemplate>(SharedObjectTemplate::SMSC);
	templateFactory.registerObject<SharedIntangibleObjectTemplate>(SharedObjectTemplate::SMSD);
	templateFactory.registerObject<SharedIntangibleObjectTemplate>(SharedObjectTemplate::SMLE);
	templateFactory.registerObject<SharedIntangibleObjectTemplate>(SharedObjectTemplate::SMSO);
	templateFactory.registerObject<SharedPlayerObjectTemplate>(SharedObjectTemplate::SPLY);
	templateFactory.registerObject<SharedIntangibleObjectTemplate>(SharedObjectTemplate::STOK);
	templateFactory.registerObject<SharedIntangibleObjectTemplate>(SharedObjectTemplate::SWAY);
	templateFactory.registerObject<SharedIntangibleObjectTemplate>(SharedObjectTemplate::SBMK);
	templateFactory.registerObject<SharedBuildingObjectTemplate>(SharedObjectTemplate::SBOT);
	templateFactory.registerObject<SharedObjectTemplate>(SharedObjectTemplate::SCOU);
	templateFactory.registerObject<SharedCreatureObjectTemplate>(SharedObjectTemplate::SCOT);
	templateFactory.registerObject<SharedFactoryObjectTemplate>(SharedObjectTemplate::SFOT);
	templateFactory.registerObject<SharedInstallationObjectTemplate>(SharedObjectTemplate::SIOT);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::RCCT);
	templateFactory.registerObject<SharedShipObjectTemplate>(SharedObjectTemplate::SSHP);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::SWOT);
	templateFactory.registerObject<SharedObjectTemplate>(SharedObjectTemplate::SGRP);
	templateFactory.registerObject<SharedObjectTemplate>(SharedObjectTemplate::SGLD);
	templateFactory.registerObject<SharedObjectTemplate>(SharedObjectTemplate::SJED);
	templateFactory.registerObject<SharedCellObjectTemplate>(SharedObjectTemplate::CCLT);
	templateFactory.registerObject<SharedIntangibleObjectTemplate>(SharedObjectTemplate::SITN);
	templateFactory.registerObject<SharedStaticObjectTemplate>(SharedObjectTemplate::STAT);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::STOT);
	templateFactory.registerObject<SharedUniverseObjectTemplate>(SharedObjectTemplate::SUNI);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::LOOTKIT);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::LOOTSCHEMATIC);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::GAMBLINGTERMINAL);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::FIREWORK);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::SURVEYTOOL);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::RECYCLETOOL);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::CRAFTINGTOOL);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::CRAFTINGSTATION);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::RESOURCESPAWN);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::ARMOROBJECT);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::DEED);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::STRUCTUREDEED);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::PETDEED);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::VEHICLEDEED);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::DROIDDEED);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::EVENTPERKDEED);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::MISSIONTERMINAL);
	templateFactory.registerObject<SharedBuildingObjectTemplate>(SharedObjectTemplate::CLONINGBUILDING);
	templateFactory.registerObject<HospitalBuildingObjectTemplate>(SharedObjectTemplate::HOSPITALBUILDING);
	templateFactory.registerObject<RecreationBuildingObjectTemplate>(SharedObjectTemplate::RECREATIONBUILDING);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::DRAFTSCHEMATIC);
	templateFactory.registerObject<SharedCreatureObjectTemplate>(SharedObjectTemplate::NPCCREATURE);
	templateFactory.registerObject<SharedInstallationObjectTemplate>(SharedObjectTemplate::FACTORY);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::STIMPACK);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::RANGEDSTIMPACK);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::ENHANCEPACK);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::CUREPACK);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::DOTPACK);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::WOUNDPACK);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::STATEPACK);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::SKILLBUFF);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::CONSUMABLE);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::INSTRUMENT);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::CAMPKIT);
	templateFactory.registerObject<PlayerCreatureTemplate>(SharedObjectTemplate::PLAYERCREATURE);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::SLICINGTOOL);
	templateFactory.registerObject<ContainerTemplate>(SharedObjectTemplate::CONTAINER);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::ELEVATORTERMINAL);
	templateFactory.registerObject<SharedCreatureObjectTemplate>(SharedObjectTemplate::VENDORCREATURE);
	templateFactory.registerObject<SharedStructureObjectTemplate>(SharedObjectTemplate::CAMPSTRUCTURE);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::TRAP);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::CAMOKIT);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::POWERUP);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::DICE);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::LIVESAMPLE);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::CREATUREHABITAT);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::REPAIRTOOL);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::VEHICLECUSTOMKIT);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::DROIDCUSTOMKIT);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::LIGHTSABERCRYSTAL);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::DNASAMPLE);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::DROIDCOMPONENT);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::DROIDMODULECRAFTING);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::DROIDMODULEEFFECTS);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::DROIDMODULEPERSONALITY);
	templateFactory.registerObject<SharedTangibleObjectTemplate>(SharedObjectTemplate::VEHICLE);
	templateFactory.registerObject<SharedObjectTemplate>(SharedObjectTemplate::XPPURCHASE);
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

	luaTemplatesInstance->setGlobalInt("KINETIC", 1);//WeaponObject::KINETIC);
	luaTemplatesInstance->setGlobalInt("ENERGY", 1);//WeaponObject::ENERGY);
	luaTemplatesInstance->setGlobalInt("ELECTRICITY", 1);//WeaponObject::ELECTRICITY);
	luaTemplatesInstance->setGlobalInt("STUN", 1);//WeaponObject::STUN);
	luaTemplatesInstance->setGlobalInt("BLAST", 1);//WeaponObject::BLAST);
	luaTemplatesInstance->setGlobalInt("HEAT", 1);//WeaponObject::HEAT);
	luaTemplatesInstance->setGlobalInt("COLD", 1);//WeaponObject::COLD);
	luaTemplatesInstance->setGlobalInt("ACID", 1);//WeaponObject::ACID);
	luaTemplatesInstance->setGlobalInt("LIGHTSABER", 1);//WeaponObject::LIGHTSABER);

	luaTemplatesInstance->setGlobalInt("NONE", 1);//WeaponObject::NONE);
	luaTemplatesInstance->setGlobalInt("LIGHT", 1);//WeaponObject::LIGHT);
	luaTemplatesInstance->setGlobalInt("MEDIUM", 1);//WeaponObject::MEDIUM);
	luaTemplatesInstance->setGlobalInt("HEAVY", 1);//WeaponObject::HEAVY);

	luaTemplatesInstance->setGlobalInt("ATTACKABLE", CreatureFlag::ATTACKABLE);
	luaTemplatesInstance->setGlobalInt("AGGRESSIVE", CreatureFlag::AGGRESSIVE);
	luaTemplatesInstance->setGlobalInt("OVERT", CreatureFlag::OVERT);
	luaTemplatesInstance->setGlobalInt("TEF", CreatureFlag::TEF);
	luaTemplatesInstance->setGlobalInt("PLAYER", CreatureFlag::PLAYER);
	luaTemplatesInstance->setGlobalInt("ENEMY", CreatureFlag::ENEMY);
	luaTemplatesInstance->setGlobalInt("CHANGEFACTIONSTATUS", CreatureFlag::CHANGEFACTIONSTATUS);
	luaTemplatesInstance->setGlobalInt("BLINK_GREEN", CreatureFlag::BLINK_GREEN);

	luaTemplatesInstance->setGlobalInt("CONVERSABLE", OptionBitmask::CONVERSE);
	luaTemplatesInstance->setGlobalInt("AIENABLED", OptionBitmask::AIENABLED);
	luaTemplatesInstance->setGlobalInt("INVULNERABLE", OptionBitmask::INVULNERABLE);
	luaTemplatesInstance->setGlobalInt("FACTIONAGGRO", OptionBitmask::FACTIONAGGRO);
	luaTemplatesInstance->setGlobalInt("INTERESTING", OptionBitmask::INTERESTING);
	luaTemplatesInstance->setGlobalInt("JTLINTERESTING", OptionBitmask::JTLINTERESTING);

	luaTemplatesInstance->setGlobalInt("MELEEATTACK", 1);//WeaponObject::MELEEATTACK);
	luaTemplatesInstance->setGlobalInt("RANGEDATTACK", 1);//WeaponObject::RANGEDATTACK);
	luaTemplatesInstance->setGlobalInt("FORCEATTACK", 1);//WeaponObject::FORCEATTACK);
	luaTemplatesInstance->setGlobalInt("TRAPATTACK", 1);//WeaponObject::TRAPATTACK);
	luaTemplatesInstance->setGlobalInt("GRENADEATTACK", 1);//WeaponObject::GRENADEATTACK);
	luaTemplatesInstance->setGlobalInt("HEAVYACIDBEAMATTACK", 1);//WeaponObject::HEAVYACIDBEAMATTACK);
	luaTemplatesInstance->setGlobalInt("HEAVYLIGHTNINGBEAMATTACK", 1);//WeaponObject::HEAVYLIGHTNINGBEAMATTACK);
	luaTemplatesInstance->setGlobalInt("HEAVYPARTICLEBEAMATTACK", 1);//WeaponObject::HEAVYPARTICLEBEAMATTACK);
	luaTemplatesInstance->setGlobalInt("HEAVYROCKETLAUNCHERATTACK", 1);//WeaponObject::HEAVYROCKETLAUNCHERATTACK);
	luaTemplatesInstance->setGlobalInt("HEAVYLAUNCHERATTACK", 1);//WeaponObject::HEAVYLAUNCHERATTACK);

	luaTemplatesInstance->setGlobalInt("ANYWEAPON", 1);//CombatManager::ANYWEAPON);
	luaTemplatesInstance->setGlobalInt("THROWNWEAPON", 1);//CombatManager::THROWNWEAPON);
	luaTemplatesInstance->setGlobalInt("HEAVYWEAPON", 1);//CombatManager::HEAVYWEAPON);
	luaTemplatesInstance->setGlobalInt("MINEWEAPON", 1);//CombatManager::MINEWEAPON);
	luaTemplatesInstance->setGlobalInt("SPECIALHEAVYWEAPON", 1);//CombatManager::SPECIALHEAVYWEAPON);
	luaTemplatesInstance->setGlobalInt("UNARMEDWEAPON", 1);//CombatManager::UNARMEDWEAPON);
	luaTemplatesInstance->setGlobalInt("ONEHANDMELEEWEAPON", 1);//CombatManager::ONEHANDMELEEWEAPON);
	luaTemplatesInstance->setGlobalInt("TWOHANDMELEEWEAPON", 1);//CombatManager::TWOHANDMELEEWEAPON);
	luaTemplatesInstance->setGlobalInt("POLEARMWEAPON", 1);//CombatManager::POLEARMWEAPON);
	luaTemplatesInstance->setGlobalInt("PISTOLWEAPON", 1);//CombatManager::PISTOLWEAPON);
	luaTemplatesInstance->setGlobalInt("CARBINEWEAPON", 1);//CombatManager::CARBINEWEAPON);
	luaTemplatesInstance->setGlobalInt("RIFLEWEAPON", 1);//CombatManager::RIFLEWEAPON);
	luaTemplatesInstance->setGlobalInt("GRENADEWEAPON", 1);//CombatManager::GRENADEWEAPON);
	luaTemplatesInstance->setGlobalInt("LIGHTNINGRIFLEWEAPON", 1);//CombatManager::LIGHTNINGRIFLEWEAPON);
	luaTemplatesInstance->setGlobalInt("ONEHANDJEDIWEAPON", 1);//CombatManager::ONEHANDJEDIWEAPON);
	luaTemplatesInstance->setGlobalInt("TWOHANDJEDIWEAPON", 1);//CombatManager::TWOHANDJEDIWEAPON);
	luaTemplatesInstance->setGlobalInt("POLEARMJEDIWEAPON", 1);//CombatManager::POLEARMJEDIWEAPON);
	luaTemplatesInstance->setGlobalInt("MELEEWEAPON", 1);//CombatManager::MELEEWEAPON);
	luaTemplatesInstance->setGlobalInt("RANGEDWEAPON", 1);//CombatManager::RANGEDWEAPON);
	luaTemplatesInstance->setGlobalInt("JEDIWEAPON", 1);//CombatManager::JEDIWEAPON);

	luaTemplatesInstance->setGlobalInt("OBJECTDESTRUCTION", 1);//ObserverEventType::OBJECTDESTRUCTION);
	luaTemplatesInstance->setGlobalInt("DAMAGERECEIVED", 1);//ObserverEventType::DAMAGERECEIVED);
	luaTemplatesInstance->setGlobalInt("PLAYERKILLED", 1);//ObserverEventType::PLAYERKILLED);
	luaTemplatesInstance->setGlobalInt("PLAYERCLONED", 1);//ObserverEventType::PLAYERCLONED);
	luaTemplatesInstance->setGlobalInt("CRAFTINGASSEMBLY", 1);//ObserverEventType::CRAFTINGASSEMBLY);
	luaTemplatesInstance->setGlobalInt("CRAFTINGEXPERIMENTATION", 1);//ObserverEventType::CRAFTINGEXPERIMENTATION);
	luaTemplatesInstance->setGlobalInt("HEALINGPERFORMED", 1);//ObserverEventType::HEALINGPERFORMED);
	luaTemplatesInstance->setGlobalInt("ENHANCINGPERFORMED", 1);//ObserverEventType::ENHANCINGPERFORMED);
	luaTemplatesInstance->setGlobalInt("WOUNDHEALINGPERFORMED", 1);//ObserverEventType::WOUNDHEALINGPERFORMED);
	luaTemplatesInstance->setGlobalInt("XPAWARDED", 1);//ObserverEventType::XPAWARDED);
	luaTemplatesInstance->setGlobalInt("SPICEDOWNERACTIVATED", 1);//ObserverEventType::SPICEDOWNERACTIVATED);
	luaTemplatesInstance->setGlobalInt("MEDPACKUSED", 1);//ObserverEventType::MEDPACKUSED);

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
	luaTemplatesInstance->setGlobalInt("RECYCLETOOL", SharedObjectTemplate::RECYCLETOOL);
	luaTemplatesInstance->setGlobalInt("CRAFTINGTOOL", SharedObjectTemplate::CRAFTINGTOOL);
	luaTemplatesInstance->setGlobalInt("CRAFTINGSTATION", SharedObjectTemplate::CRAFTINGSTATION);
	luaTemplatesInstance->setGlobalInt("RESOURCESPAWN", SharedObjectTemplate::RESOURCESPAWN);
	luaTemplatesInstance->setGlobalInt("ARMOROBJECT", SharedObjectTemplate::ARMOROBJECT);
	luaTemplatesInstance->setGlobalInt("LIGHTSABERCRYSTAL", SharedObjectTemplate::LIGHTSABERCRYSTAL);
	luaTemplatesInstance->setGlobalInt("DEED", SharedObjectTemplate::DEED);
	luaTemplatesInstance->setGlobalInt("STRUCTUREDEED", SharedObjectTemplate::STRUCTUREDEED);
	luaTemplatesInstance->setGlobalInt("VEHICLEDEED", SharedObjectTemplate::VEHICLEDEED);
	luaTemplatesInstance->setGlobalInt("PETDEED", SharedObjectTemplate::PETDEED);
	luaTemplatesInstance->setGlobalInt("DROIDDEED", SharedObjectTemplate::DROIDDEED);
	luaTemplatesInstance->setGlobalInt("EVENTPERKDEED", SharedObjectTemplate::EVENTPERKDEED);
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
	luaTemplatesInstance->setGlobalInt("SKILLBUFF", SharedObjectTemplate::SKILLBUFF);
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
	luaTemplatesInstance->setGlobalInt("VEHICLECUSTOMKIT", SharedObjectTemplate::VEHICLECUSTOMKIT);
	luaTemplatesInstance->setGlobalInt("DROIDCUSTOMKIT", SharedObjectTemplate::DROIDCUSTOMKIT);
	luaTemplatesInstance->setGlobalInt("DNASAMPLE", SharedObjectTemplate::DNASAMPLE);
	luaTemplatesInstance->setGlobalInt("DROIDCOMPONENT", SharedObjectTemplate::DROIDCOMPONENT);
	luaTemplatesInstance->setGlobalInt("DROIDCRAFTINGMODULE", SharedObjectTemplate::DROIDMODULECRAFTING);
	luaTemplatesInstance->setGlobalInt("DROIDEFFECTSMODULE", SharedObjectTemplate::DROIDMODULEEFFECTS);
	luaTemplatesInstance->setGlobalInt("DROIDPERSONALITYCHIP", SharedObjectTemplate::DROIDMODULEPERSONALITY);
	luaTemplatesInstance->setGlobalInt("VEHICLE", SharedObjectTemplate::VEHICLE);
	luaTemplatesInstance->setGlobalInt("XPPURCHASE", SharedObjectTemplate::XPPURCHASE);

	luaTemplatesInstance->setGlobalInt("NO_HITLOCATION", 0);//WearablesDeltaVector::NOLOCATION);
	luaTemplatesInstance->setGlobalInt("CHEST_HITLOCATION", 1);//WearablesDeltaVector::CHEST);
	luaTemplatesInstance->setGlobalInt("ARMS_HITLOCATION", 2);//WearablesDeltaVector::ARMS);
	luaTemplatesInstance->setGlobalInt("LEGS_HITLOCATION", 3);//WearablesDeltaVector::LEGS);
	luaTemplatesInstance->setGlobalInt("HEAD_HITLOCATION", 4);//WearablesDeltaVector::HEAD);

	luaTemplatesInstance->setGlobalInt("GENETIC_LAB", 1);//CraftingManager::GENETIC_LAB);
	luaTemplatesInstance->setGlobalInt("RESOURCE_LAB", 2);//CraftingManager::RESOURCE_LAB);

	luaTemplatesInstance->setGlobalInt("STATIC", 1);//EventPerkDeedTemplate::STATIC);
	luaTemplatesInstance->setGlobalInt("THEATER", 1);//EventPerkDeedTemplate::THEATER);
	luaTemplatesInstance->setGlobalInt("RECRUITER", 1);//EventPerkDeedTemplate::RECRUITER);
	luaTemplatesInstance->setGlobalInt("GAME", 1);//EventPerkDeedTemplate::GAME);
	luaTemplatesInstance->setGlobalInt("HONORGUARD", 1);//EventPerkDeedTemplate::HONORGUARD);

	luaTemplatesInstance->setGlobalInt("STIM_A", 1);//StimPackTemplate::STIM_A);
	luaTemplatesInstance->setGlobalInt("STIM_B", 1);//StimPackTemplate::STIM_B);
	luaTemplatesInstance->setGlobalInt("STIM_C", 1);//StimPackTemplate::STIM_C);
	luaTemplatesInstance->setGlobalInt("STIM_D", 1);//StimPackTemplate::STIM_D);
	luaTemplatesInstance->setGlobalInt("STIM_E", 1);//StimPackTemplate::STIM_E);

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

	int size = 0;
	//byte* data = treeDirectory->getBytes(fileName, size);

	byte* data = DataArchiveStore::instance()->getData(fileName, size);

	if (size == 0)
		return NULL;

	ObjectInputStream* stream = new ObjectInputStream((char*)data, size);

	delete [] data;

	return stream;
}

IffStream* TemplateManager::openIffFile(const String& fileName) {
	return DataArchiveStore::instance()->openIffFile(fileName);
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

	bool val = Lua::runFile("scripts/object/" + filename, L);

	if (!val)
		ERROR_CODE = LOAD_LUA_TEMPLATE_ERROR;

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
	getObject.callFunction();

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

	if (ConfigManager::instance()->isProgressMonitorActivated()) {
		if (val % 159 == 0)
			printf("\r\tLoading templates: [%d%%]\t", (int) (float(val) / 15998.f * 100.f));
	}

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
