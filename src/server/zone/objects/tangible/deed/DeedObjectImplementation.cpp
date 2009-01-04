#include "../../../packets.h"
#include "../../../objects.h"

#include "DeedObject.h"
#include "DeedObjectImplementation.h"

#include "../../../managers/resource/ResourceHarvestType.h"

DeedObjectImplementation::DeedObjectImplementation(uint64 oid, uint32 tempCRC, const UnicodeString& n, const String& tempname)
	: DeedObjectServant(oid, tempCRC, n, tempname, DEED) {
	objectID = oid;
	objectCRC = tempCRC;
	templateTypeName = "deed";
	templateName = tempname;
	name = n;

	init();
}

DeedObjectImplementation::DeedObjectImplementation(CreatureObject* creature, uint32 tempCRC, const UnicodeString& n, const String& tempname)
	: DeedObjectServant(creature->getObjectID(), tempCRC, n, tempname, DEED) {
	objectCRC = tempCRC;
	templateTypeName = "deed";
	templateName = tempname;
	name = n;

	init();
}

DeedObjectImplementation::DeedObjectImplementation(uint64 oid, uint32 tempCRC, const UnicodeString& n, const String& tempname, int type)
	: DeedObjectServant(oid, tempCRC, n, tempname, type) {
	objectID = oid;
	objectCRC = tempCRC;
	templateTypeName = "deed";
	templateName = tempname;
	name = n;

	init();
}

DeedObjectImplementation::DeedObjectImplementation(CreatureObject* creature, uint32 tempCRC, const UnicodeString& n, const String& tempname, int type)
	: DeedObjectServant(creature->getObjectID(), tempCRC, n, tempname, type) {
	objectCRC = tempCRC;
	templateTypeName = "deed";
	templateName = tempname;
	name = n;

	init();
}

DeedObjectImplementation::DeedObjectImplementation(uint64 oid, int type)
	: DeedObjectServant(oid, type) {

}

DeedObjectImplementation::~DeedObjectImplementation(){

}

void DeedObjectImplementation::init(){
	objectSubType = getSubType(objectCRC);

	defaultTemplateName = "";
}

// This gets overwritten for Vehicle/Resource Deeds
int DeedObjectImplementation::useObject(Player* player) {

	if (player->isInANoBuildArea()) {
		player->sendSystemMessage("You can not build here.");
		return 1;
	}

	if(getLotSize() > player->getLotsRemaining()) {
		player->sendSystemMessage("You do not have enough lots to build this.");
		return 1;
	}
	//System::out << "Enter Placement Mode.  Target File: " << targetFile << endl;
	EnterStructurePlacementModeMessage * espmm = new EnterStructurePlacementModeMessage(objectID, targetFile); // targetFile
	player->sendMessage(espmm);

	return 1;
}



void DeedObjectImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;
	AttributeListMessage* alm = new AttributeListMessage((TangibleObject*) _this);

	addAttributes(alm);

	player->sendMessage(alm);
}

void DeedObjectImplementation::parseItemAttributes() {
	TangibleObjectImplementation::parseItemAttributes();
}

void DeedObjectImplementation::addHeaderAttributes(AttributeListMessage* alm) {
	alm->insertAttribute("volume", "1");

	if (!craftersName.isEmpty()){
		alm->insertAttribute("crafter", craftersName);
	}

	if (!craftedSerial.isEmpty()){
		alm->insertAttribute("serial_number", craftedSerial);
	}
}

void DeedObjectImplementation::addFooterAttributes(AttributeListMessage* alm) {
	//alm->insertAttribute("healing_ability", getMedicineUseRequired());
}

void DeedObjectImplementation::addAttributes(AttributeListMessage* alm) {
	addHeaderAttributes(alm);
	addFooterAttributes(alm);
}



/*
 *
 * 	static const int ENERGYGAS = 0x400001;
	static const int ENERGYLIQUID = 0x400002;
	static const int ENERGYRADIOACTIVE = 0x400003;
	static const int ENERGYSOLID = 0x400004;
	static const int INORGANICCHEMICAL = 0x400005;
	static const int INORGANICGAS = 0x400006;
	static const int INORGANICMINERAL = 0x400007;
	static const int WATER = 0x400008;
	static const int ORGANICFOOD = 0x400009;
	static const int ORGANICHIDE = 0x40000A;
	static const int ORGANICSTRUCTURAL = 0x40000B;
 *
 * */

int DeedObjectImplementation::getHarvesterType() {

	switch(objectCRC) {
		case 0xE296E887: //object/tangible/deed/harvester_deed/shared_harvester_creature_deed.iff
			return 0;
		case 0xA9557114: //object/tangible/deed/harvester_deed/shared_harvester_flora_deed.iff
		case 0xEEC52333: //object/tangible/deed/harvester_deed/shared_harvester_flora_deed_heavy.iff
		case 0x522BE74D: //object/tangible/deed/harvester_deed/shared_harvester_flora_deed_medium.iff
			return ResourceHarvestType::FLORA;
		case 0x85020A19: //object/tangible/deed/harvester_deed/shared_harvester_gas_deed.iff
		case 0x1090794C: //object/tangible/deed/harvester_deed/shared_harvester_gas_deed_heavy.iff
		case 0xB247C54E: //object/tangible/deed/harvester_deed/shared_harvester_gas_deed_medium.iff
			return ResourceHarvestType::GAS;
		case 0xC6CF0E82: //object/tangible/deed/harvester_deed/shared_harvester_liquid_deed.iff
		case 0x4FA6CDD8: //object/tangible/deed/harvester_deed/shared_harvester_liquid_deed_heavy.iff
		case 0xC42B47F4: //object/tangible/deed/harvester_deed/shared_harvester_liquid_deed_medium.iff
			return ResourceHarvestType::CHEMICAL;
		case 0x5E1B48A7: //object/tangible/deed/harvester_deed/shared_harvester_moisture_deed.iff
		case 0x0147A463: //object/tangible/deed/harvester_deed/shared_harvester_moisture_deed_heavy.iff
		case 0x2D4A2C89: //object/tangible/deed/harvester_deed/shared_harvester_moisture_deed_medium.iff
			return ResourceHarvestType::WATER;
		case 0xC02EBAB3: //object/tangible/deed/harvester_deed/shared_harvester_ore_heavy_deed.iff
		case 0x7EB8541F: //object/tangible/deed/harvester_deed/shared_harvester_ore_s1_deed.iff
		case 0xFBC8A901: //object/tangible/deed/harvester_deed/shared_harvester_ore_s2_deed.iff
			return ResourceHarvestType::MINERAL;
		case 0xE5A0F395: //object/tangible/deed/generator_deed/shared_generator_fusion_deed.iff
			return ResourceHarvestType::FUSION;
		case 0x26D63643: //object/tangible/deed/generator_deed/shared_generator_photo_bio_deed.iff
			return 0;
		case 0x4669B528: //object/tangible/deed/generator_deed/shared_generator_solar_deed.iff
			return ResourceHarvestType::SOLAR;
		case 0xE6C711A7: //object/tangible/deed/generator_deed/shared_generator_wind_deed.iff
			return ResourceHarvestType::WIND;
		default:
			return 0;
	}
}

int DeedObjectImplementation::getSubType(uint32 objCRC) {

	switch(objCRC) {

		case 0x6C0893E5: //object/tangible/deed/factory_deed/shared_factory_clothing_deed.iff
		case 0xCFEC24E5: //object/tangible/deed/factory_deed/shared_factory_food_deed.iff
		case 0xFD1EF87A: //object/tangible/deed/factory_deed/shared_factory_item_deed.iff
		case 0x8E331C08: //object/tangible/deed/factory_deed/shared_factory_structure_deed.iff
			return TangibleObjectImplementation::FACTORY;

		case 0xE296E887: //object/tangible/deed/harvester_deed/shared_harvester_creature_deed.iff
		case 0xA9557114: //object/tangible/deed/harvester_deed/shared_harvester_flora_deed.iff
		case 0xEEC52333: //object/tangible/deed/harvester_deed/shared_harvester_flora_deed_heavy.iff
		case 0x522BE74D: //object/tangible/deed/harvester_deed/shared_harvester_flora_deed_medium.iff
		case 0x85020A19: //object/tangible/deed/harvester_deed/shared_harvester_gas_deed.iff
		case 0x1090794C: //object/tangible/deed/harvester_deed/shared_harvester_gas_deed_heavy.iff
		case 0xB247C54E: //object/tangible/deed/harvester_deed/shared_harvester_gas_deed_medium.iff
		case 0xC6CF0E82: //object/tangible/deed/harvester_deed/shared_harvester_liquid_deed.iff
		case 0x4FA6CDD8: //object/tangible/deed/harvester_deed/shared_harvester_liquid_deed_heavy.iff
		case 0xC42B47F4: //object/tangible/deed/harvester_deed/shared_harvester_liquid_deed_medium.iff
		case 0x5E1B48A7: //object/tangible/deed/harvester_deed/shared_harvester_moisture_deed.iff
		case 0x0147A463: //object/tangible/deed/harvester_deed/shared_harvester_moisture_deed_heavy.iff
		case 0x2D4A2C89: //object/tangible/deed/harvester_deed/shared_harvester_moisture_deed_medium.iff
		case 0xC02EBAB3: //object/tangible/deed/harvester_deed/shared_harvester_ore_heavy_deed.iff
		case 0x7EB8541F: //object/tangible/deed/harvester_deed/shared_harvester_ore_s1_deed.iff
		case 0xFBC8A901: //object/tangible/deed/harvester_deed/shared_harvester_ore_s2_deed.iff
			return TangibleObjectImplementation::HARVESTER;

		case 0xE5A0F395: //object/tangible/deed/generator_deed/shared_generator_fusion_deed.iff
		case 0x26D63643: //object/tangible/deed/generator_deed/shared_generator_photo_bio_deed.iff
		case 0x4669B528: //object/tangible/deed/generator_deed/shared_generator_solar_deed.iff
		case 0xE6C711A7: //object/tangible/deed/generator_deed/shared_generator_wind_deed.iff
			return TangibleObjectImplementation::GENERATOR;


		case 0x6C7A1232: //object/tangible/deed/faction_perk/turret/base/shared_faction_turret_deed.iff
		case 0x2587A8C0: //object/tangible/deed/faction_perk/turret/shared_block_lg_deed.iff
		case 0xFBA00806: //object/tangible/deed/faction_perk/turret/shared_block_med_deed.iff
		case 0xA3878091: //object/tangible/deed/faction_perk/turret/shared_block_sm_deed.iff
		case 0xF07B2F6E: //object/tangible/deed/faction_perk/turret/shared_dish_lg_deed.iff
		case 0x767B073F: //object/tangible/deed/faction_perk/turret/shared_dish_sm_deed.iff
		case 0xDE76DCB5: //object/tangible/deed/faction_perk/turret/shared_tower_lg_deed.iff
		case 0xA8274B6E: //object/tangible/deed/faction_perk/turret/shared_tower_med_deed.iff
		case 0x5876F4E4: //object/tangible/deed/faction_perk/turret/shared_tower_sm_deed.iff
		case 0xD192431D: //object/tangible/deed/shared_test_deed.iff
		case 0x2775B687: //object/tangible/deed/turret_deed/shared_turret_block_large_deed.iff
		case 0xE0C40914: //object/tangible/deed/turret_deed/shared_turret_block_medium_deed.iff
		case 0x67F3B024: //object/tangible/deed/turret_deed/shared_turret_block_small_deed.iff
			return TangibleObjectImplementation::TURRET;

		case 0x5D30CDF7: //object/tangible/deed/faction_perk/minefield/shared_field_1x1_deed.iff
			return TangibleObjectImplementation::MINEFIELD;


		case 0xBFBC4835: //object/tangible/deed/base/shared_deed_base.iff
		case 0xAB93C79D: //object/tangible/deed/base/shared_deed_building_base.iff
		case 0xC042EE23: //object/tangible/deed/base/shared_deed_installation_base.iff
			return 0;

		case 0x9899666C: //object/tangible/deed/vehicle_deed/shared_jetpack_deed.iff
		case 0xDF4F6F37: //object/tangible/deed/vehicle_deed/shared_landspeeder_av21_deed.iff
		case 0xBEAF4CA8: //object/tangible/deed/vehicle_deed/shared_landspeeder_x31_deed.iff
		case 0x35FF563D: //object/tangible/deed/vehicle_deed/shared_landspeeder_x34_deed.iff
		case 0xF2EAD531: //object/tangible/deed/vehicle_deed/shared_speederbike_deed.iff
		case 0x70CDB867: //object/tangible/deed/vehicle_deed/shared_speederbike_flash_deed.iff
		case 0x1D885457: //object/tangible/deed/vehicle_deed/shared_speederbike_swoop_deed.iff
		case 0x1E1853F0: //object/tangible/deed/vehicle_deed/shared_vehicle_deed_base.iff
		case 0x4B3CA4DE: //object/tangible/deed/vehicle_deed/shared_vehicular_prototype_bike_deed.iff
		case 0xEDDC0F5F: //object/tangible/deed/vehicle_deed/shared_vehicular_prototype_deed.iff
			return 0; // VEHICLE types?

		// City Buildings

		case 0x17EAC380: //object/tangible/deed/city_deed/shared_bank_corellia_deed.iff
		case 0xD40FCD49: //object/tangible/deed/city_deed/shared_bank_naboo_deed.iff
		case 0x24980999: //object/tangible/deed/city_deed/shared_bank_tatooine_deed.iff
			return BANK;
		case 0x82A983A9: //object/tangible/deed/city_deed/shared_cantina_corellia_deed.iff
		case 0x4F5A59D1: //object/tangible/deed/city_deed/shared_cantina_naboo_deed.iff
		case 0xB1DB49B0: //object/tangible/deed/city_deed/shared_cantina_tatooine_deed.iff
			return CANTINA;
		case 0xA5FE7FFF: //object/tangible/deed/city_deed/shared_cityhall_corellia_deed.iff
		case 0xDA53F690: //object/tangible/deed/city_deed/shared_cityhall_naboo_deed.iff
		case 0x968CB5E6: //object/tangible/deed/city_deed/shared_cityhall_tatooine_deed.iff
			return CITYHALL;
		case 0x6D60E4C7: //object/tangible/deed/city_deed/shared_cloning_corellia_deed.iff
		case 0x96EF7A06: //object/tangible/deed/city_deed/shared_cloning_naboo_deed.iff
		case 0x5E122EDE: //object/tangible/deed/city_deed/shared_cloning_tatooine_deed.iff
			return CLONING;
		case 0xA9B20B60: //object/tangible/deed/city_deed/shared_garage_corellia_deed.iff
		case 0xBF38BE5C: //object/tangible/deed/city_deed/shared_garage_naboo_deed.iff
		case 0x9AC0C179: //object/tangible/deed/city_deed/shared_garage_tatooine_deed.iff
			return GARAGE;
		case 0x9A8479F1: //object/tangible/deed/city_deed/shared_garden_corellia_lrg_01_deed.iff
		case 0x1FF484EF: //object/tangible/deed/city_deed/shared_garden_corellia_lrg_02_deed.iff
		case 0x9F642488: //object/tangible/deed/city_deed/shared_garden_corellia_lrg_03_deed.iff
		case 0x11D46364: //object/tangible/deed/city_deed/shared_garden_corellia_lrg_04_deed.iff
		case 0x9144C303: //object/tangible/deed/city_deed/shared_garden_corellia_lrg_05_deed.iff
		case 0xC5D89007: //object/tangible/deed/city_deed/shared_garden_corellia_med_01_deed.iff
		case 0x40A86D19: //object/tangible/deed/city_deed/shared_garden_corellia_med_02_deed.iff
		case 0xC038CD7E: //object/tangible/deed/city_deed/shared_garden_corellia_med_03_deed.iff
		case 0x4E888A92: //object/tangible/deed/city_deed/shared_garden_corellia_med_04_deed.iff
		case 0xCE182AF5: //object/tangible/deed/city_deed/shared_garden_corellia_med_05_deed.iff
		case 0x7CE996DF: //object/tangible/deed/city_deed/shared_garden_corellia_sml_01_deed.iff
		case 0xF9996BC1: //object/tangible/deed/city_deed/shared_garden_corellia_sml_02_deed.iff
		case 0x7909CBA6: //object/tangible/deed/city_deed/shared_garden_corellia_sml_03_deed.iff
		case 0xF7B98C4A: //object/tangible/deed/city_deed/shared_garden_corellia_sml_04_deed.iff
		case 0x77292C2D: //object/tangible/deed/city_deed/shared_garden_corellia_sml_05_deed.iff
		case 0x44BC3437: //object/tangible/deed/city_deed/shared_garden_dantooine_lrg_01_deed.iff
		case 0x1BE0DDC1: //object/tangible/deed/city_deed/shared_garden_dantooine_med_01_deed.iff
		case 0xA2D1DB19: //object/tangible/deed/city_deed/shared_garden_dantooine_sml_01_deed.iff
		case 0xC6813FAE: //object/tangible/deed/city_deed/shared_garden_dathomir_lrg_01_deed.iff
		case 0x99DDD658: //object/tangible/deed/city_deed/shared_garden_dathomir_med_01_deed.iff
		case 0x20ECD080: //object/tangible/deed/city_deed/shared_garden_dathomir_sml_01_deed.iff
		case 0xFE4BC6C5: //object/tangible/deed/city_deed/shared_garden_endor_lrg_01_deed.iff
		case 0xA1172F33: //object/tangible/deed/city_deed/shared_garden_endor_med_01_deed.iff
		case 0x182629EB: //object/tangible/deed/city_deed/shared_garden_endor_sml_01_deed.iff
		case 0x187D2021: //object/tangible/deed/city_deed/shared_garden_naboo_lrg_01_deed.iff
		case 0x9D0DDD3F: //object/tangible/deed/city_deed/shared_garden_naboo_lrg_02_deed.iff
		case 0x1D9D7D58: //object/tangible/deed/city_deed/shared_garden_naboo_lrg_03_deed.iff
		case 0x932D3AB4: //object/tangible/deed/city_deed/shared_garden_naboo_lrg_04_deed.iff
		case 0x13BD9AD3: //object/tangible/deed/city_deed/shared_garden_naboo_lrg_05_deed.iff
		case 0x4721C9D7: //object/tangible/deed/city_deed/shared_garden_naboo_med_01_deed.iff
		case 0xC25134C9: //object/tangible/deed/city_deed/shared_garden_naboo_med_02_deed.iff
		case 0x42C194AE: //object/tangible/deed/city_deed/shared_garden_naboo_med_03_deed.iff
		case 0xCC71D342: //object/tangible/deed/city_deed/shared_garden_naboo_med_04_deed.iff
		case 0x4CE17325: //object/tangible/deed/city_deed/shared_garden_naboo_med_05_deed.iff
		case 0xFE10CF0F: //object/tangible/deed/city_deed/shared_garden_naboo_sml_01_deed.iff
		case 0x7B603211: //object/tangible/deed/city_deed/shared_garden_naboo_sml_02_deed.iff
		case 0xFBF09276: //object/tangible/deed/city_deed/shared_garden_naboo_sml_03_deed.iff
		case 0x7540D59A: //object/tangible/deed/city_deed/shared_garden_naboo_sml_04_deed.iff
		case 0xF5D075FD: //object/tangible/deed/city_deed/shared_garden_naboo_sml_05_deed.iff
		case 0x57C36C6D: //object/tangible/deed/city_deed/shared_garden_tatooine_lrg_01_deed.iff
		case 0xD2B39173: //object/tangible/deed/city_deed/shared_garden_tatooine_lrg_02_deed.iff
		case 0x52233114: //object/tangible/deed/city_deed/shared_garden_tatooine_lrg_03_deed.iff
		case 0xDC9376F8: //object/tangible/deed/city_deed/shared_garden_tatooine_lrg_04_deed.iff
		case 0x5C03D69F: //object/tangible/deed/city_deed/shared_garden_tatooine_lrg_05_deed.iff
		case 0x089F859B: //object/tangible/deed/city_deed/shared_garden_tatooine_med_01_deed.iff
		case 0x8DEF7885: //object/tangible/deed/city_deed/shared_garden_tatooine_med_02_deed.iff
		case 0x0D7FD8E2: //object/tangible/deed/city_deed/shared_garden_tatooine_med_03_deed.iff
		case 0x83CF9F0E: //object/tangible/deed/city_deed/shared_garden_tatooine_med_04_deed.iff
		case 0x035F3F69: //object/tangible/deed/city_deed/shared_garden_tatooine_med_05_deed.iff
		case 0xB1AE8343: //object/tangible/deed/city_deed/shared_garden_tatooine_sml_01_deed.iff
		case 0x34DE7E5D: //object/tangible/deed/city_deed/shared_garden_tatooine_sml_02_deed.iff
		case 0xB44EDE3A: //object/tangible/deed/city_deed/shared_garden_tatooine_sml_03_deed.iff
		case 0x3AFE99D6: //object/tangible/deed/city_deed/shared_garden_tatooine_sml_04_deed.iff
		case 0xBA6E39B1: //object/tangible/deed/city_deed/shared_garden_tatooine_sml_05_deed.iff
			return GARDEN;
		case 0xA90A5290: //object/tangible/deed/city_deed/shared_hospital_corellia_deed.iff
		case 0x420134C6: //object/tangible/deed/city_deed/shared_hospital_naboo_deed.iff
		case 0x9A789889: //object/tangible/deed/city_deed/shared_hospital_tatooine_deed.iff
			return HOSPITAL;
		case 0xDB73A277: //object/tangible/deed/city_deed/shared_shuttleport_corellia_deed.iff
		case 0x523389B5: //object/tangible/deed/city_deed/shared_shuttleport_naboo_deed.iff
		case 0xE801686E: //object/tangible/deed/city_deed/shared_shuttleport_tatooine_deed.iff
			return SHUTTLEPORT;
		case 0x248F6CEF: //object/tangible/deed/city_deed/shared_theater_corellia_deed.iff
		case 0xB427B96E: //object/tangible/deed/city_deed/shared_theater_naboo_deed.iff
		case 0x17FDA6F6: //object/tangible/deed/city_deed/shared_theater_tatooine_deed.iff
			return THEATER;


		case 0x05B95500: //object/tangible/deed/event_perk/shared_atat_static_deed.iff
		case 0x33C26EB5: //object/tangible/deed/event_perk/shared_atst_static_deed.iff
		case 0x403E70E5: //object/tangible/deed/event_perk/shared_banner_style_1_static_deed.iff
		case 0x784B2302: //object/tangible/deed/event_perk/shared_banner_style_2_static_deed.iff
		case 0x1D3EDF24: //object/tangible/deed/event_perk/shared_bantha_static_deed.iff
		case 0xA4698A50: //object/tangible/deed/event_perk/shared_corellia_flag_deed.iff
		case 0x17838AB9: //object/tangible/deed/event_perk/shared_corellian_banner_static_deed.iff
		case 0x7E494DAB: //object/tangible/deed/event_perk/shared_corsec_1x10_honorguard_deed.iff
		case 0x85B9EB7D: //object/tangible/deed/event_perk/shared_corsec_2x10_honorguard_deed.iff
		case 0xD31676CF: //object/tangible/deed/event_perk/shared_corsec_3x10_honorguard_deed.iff
		case 0x7699BB66: //object/tangible/deed/event_perk/shared_corsec_4x10_honorguard_deed.iff
		case 0x27ED8E38: //object/tangible/deed/event_perk/shared_corsec_stage_theater_deed.iff
		case 0x109DA80B: //object/tangible/deed/event_perk/shared_crashed_tie_bomber_theater_deed.iff
		case 0xB938F953: //object/tangible/deed/event_perk/shared_crashed_tie_fighter_theater_deed.iff
		case 0x881BBB9D: //object/tangible/deed/event_perk/shared_crashed_xwing_theater_deed.iff
		case 0xB2AFCEAD: //object/tangible/deed/event_perk/shared_dantooine_flag_deed.iff
		case 0x0CC63752: //object/tangible/deed/event_perk/shared_dathomir_flag_deed.iff
		case 0x48DA4919: //object/tangible/deed/event_perk/shared_destroyed_atat_theater_deed.iff
		case 0xCAAE3D19: //object/tangible/deed/event_perk/shared_endor_flag_deed.iff
		case 0xB8B3773A: //object/tangible/deed/event_perk/shared_fed_dub_1x10_honorguard_deed.iff
		case 0x4343D1EC: //object/tangible/deed/event_perk/shared_fed_dub_2x10_honorguard_deed.iff
		case 0x15EC4C5E: //object/tangible/deed/event_perk/shared_fed_dub_3x10_honorguard_deed.iff
		case 0xB06381F7: //object/tangible/deed/event_perk/shared_fed_dub_4x10_honorguard_deed.iff
		case 0x1C8B36B0: //object/tangible/deed/event_perk/shared_fed_dub_stage_theater_deed.iff
		case 0x94921683: //object/tangible/deed/event_perk/shared_game_flag_deed.iff
		case 0x7B38D77A: //object/tangible/deed/event_perk/shared_imperial_1x10_honorguard_deed.iff
		case 0x80C871AC: //object/tangible/deed/event_perk/shared_imperial_2x10_honorguard_deed.iff
		case 0xD667EC1E: //object/tangible/deed/event_perk/shared_imperial_3x10_honorguard_deed.iff
		case 0x73E821B7: //object/tangible/deed/event_perk/shared_imperial_4x10_honorguard_deed.iff
		case 0x4783EDD8: //object/tangible/deed/event_perk/shared_imperial_banner_static_deed.iff
		case 0x38A6127D: //object/tangible/deed/event_perk/shared_imperial_landing_party_atat_theater_deed.iff
		case 0x4FF6961E: //object/tangible/deed/event_perk/shared_imperial_landing_party_lambda_theater_deed.iff
		case 0xEAFB0D23: //object/tangible/deed/event_perk/shared_imperial_recruiter_deed.iff
		case 0xB5102A73: //object/tangible/deed/event_perk/shared_imperial_recruiting_station_theater_deed.iff
		case 0x57576849: //object/tangible/deed/event_perk/shared_imperial_stage_theater_deed.iff
		case 0x2C1E28B5: //object/tangible/deed/event_perk/shared_lambda_shuttle_static_deed.iff
		case 0x099BD5E5: //object/tangible/deed/event_perk/shared_lok_flag_deed.iff
		case 0x258FA783: //object/tangible/deed/event_perk/shared_lottery_droid_deed.iff
		case 0xD055B38E: //object/tangible/deed/event_perk/shared_marble_gazebo_static_deed.iff
		case 0xD04315A0: //object/tangible/deed/event_perk/shared_naboo_flag_deed.iff
		case 0x70A48C36: //object/tangible/deed/event_perk/shared_naboo_gazebo_static_deed.iff
		case 0xEA628029: //object/tangible/deed/event_perk/shared_npc_actor_deed.iff
		case 0xE6C1AABC: //object/tangible/deed/event_perk/shared_party_stage_theater_deed.iff
		case 0x54864CFF: //object/tangible/deed/event_perk/shared_pavillion_1_static_deed.iff
		case 0x6CF31F18: //object/tangible/deed/event_perk/shared_pavillion_2_static_deed.iff
		case 0x12E04FF7: //object/tangible/deed/event_perk/shared_race_droid_deed.iff
		case 0x8833AD9F: //object/tangible/deed/event_perk/shared_radiologically_shielded_chest_deed.iff
		case 0x66BAD5CF: //object/tangible/deed/event_perk/shared_rebel_1x10_honorguard_deed.iff
		case 0x9D4A7319: //object/tangible/deed/event_perk/shared_rebel_2x10_honorguard_deed.iff
		case 0xCBE5EEAB: //object/tangible/deed/event_perk/shared_rebel_3x10_honorguard_deed.iff
		case 0x6E6A2302: //object/tangible/deed/event_perk/shared_rebel_4x10_honorguard_deed.iff
		case 0xC980100B: //object/tangible/deed/event_perk/shared_rebel_banner_static_deed.iff
		case 0xD55BC6D7: //object/tangible/deed/event_perk/shared_rebel_recruiter_deed.iff
		case 0xF5507DAD: //object/tangible/deed/event_perk/shared_rebel_recruiting_station_theater_deed.iff
		case 0xD954959A: //object/tangible/deed/event_perk/shared_rebel_stage_theater_deed.iff
		case 0x29E8F1BE: //object/tangible/deed/event_perk/shared_rori_flag_deed.iff
		case 0x688D8C10: //object/tangible/deed/event_perk/shared_rsf_1x10_honorguard_deed.iff
		case 0x937D2AC6: //object/tangible/deed/event_perk/shared_rsf_2x10_honorguard_deed.iff
		case 0xC5D2B774: //object/tangible/deed/event_perk/shared_rsf_3x10_honorguard_deed.iff
		case 0x605D7ADD: //object/tangible/deed/event_perk/shared_rsf_4x10_honorguard_deed.iff
		case 0x9E84FCBF: //object/tangible/deed/event_perk/shared_rsf_stage_theater_deed.iff
		case 0x84162F60: //object/tangible/deed/event_perk/shared_scavenger_droid_deed.iff
		case 0x6D599E6C: //object/tangible/deed/event_perk/shared_shuttle_beacon.iff
		case 0x1883DA99: //object/tangible/deed/event_perk/shared_shuttle_static_deed.iff
		case 0xBFCEFA8D: //object/tangible/deed/event_perk/shared_skeleton_chest_deed.iff
		case 0x7AC89E27: //object/tangible/deed/event_perk/shared_sparking_treasure_box_chest_deed.iff
		case 0x2F2A1D79: //object/tangible/deed/event_perk/shared_stone_base_banner_static_deed.iff
		case 0x453FC971: //object/tangible/deed/event_perk/shared_talus_flag_deed.iff
		case 0xCFD9DE1B: //object/tangible/deed/event_perk/shared_tatooine_banner_static_deed.iff
		case 0x5034B851: //object/tangible/deed/event_perk/shared_tatooine_flag_deed.iff
		case 0x9F8BB44E: //object/tangible/deed/event_perk/shared_technical_chest_deed.iff
		case 0xC2624F12: //object/tangible/deed/event_perk/shared_test_gaming_table_deed.iff
		case 0xEEA6E229: //object/tangible/deed/event_perk/shared_test_npc_deed.iff
		case 0xFAD73887: //object/tangible/deed/event_perk/shared_test_theater_deed.iff
		case 0xBF54E31B: //object/tangible/deed/event_perk/shared_tie_bomber_static_deed.iff
		case 0x852B3DCF: //object/tangible/deed/event_perk/shared_tie_fighter_static_deed.iff
		case 0xBCC4851A: //object/tangible/deed/event_perk/shared_treasure_box_chest_deed.iff
		case 0x8BB1F956: //object/tangible/deed/event_perk/shared_treasure_crate_chest_deed.iff
		case 0x5E7304B1: //object/tangible/deed/event_perk/shared_universe_flags_theater.iff
		case 0x2ADEB4AC: //object/tangible/deed/event_perk/shared_wedding_garden_imperial_large_theater_deed.iff
		case 0x735726E6: //object/tangible/deed/event_perk/shared_wedding_garden_rebel_large_theater_deed.iff
		case 0x288A7A87: //object/tangible/deed/event_perk/shared_xwing_static_deed.iff
		case 0x5DB98742: //object/tangible/deed/event_perk/shared_yavin_flag_deed.iff
			return 0; // MISC Stuff

		case 0xC786298D: //object/tangible/deed/faction_perk/covert_detector/shared_detector_32m_deed.iff
		case 0x87DD72EB: //object/tangible/deed/faction_perk/hq/shared_hq_deed_base.iff
		case 0x3085BEBA: //object/tangible/deed/faction_perk/hq/shared_hq_s01.iff
		case 0xEB92162D: //object/tangible/deed/faction_perk/hq/shared_hq_s02.iff
		case 0xA29F71A0: //object/tangible/deed/faction_perk/hq/shared_hq_s03.iff
		case 0x597C5AB4: //object/tangible/deed/faction_perk/hq/shared_hq_s04.iff
		case 0x10713D39: //object/tangible/deed/faction_perk/hq/shared_hq_s05.iff
			return BUILDING; // SF bases




		case 0xF5092D77: //object/tangible/deed/guild_deed/shared_corellia_guild_deed.iff
		case 0xC76A6970: //object/tangible/deed/guild_deed/shared_generic_guild_deed.iff
		case 0x8EF75108: //object/tangible/deed/guild_deed/shared_naboo_guild_deed.iff
		case 0x3287A7A2: //object/tangible/deed/guild_deed/shared_tatooine_guild_deed.iff
		case 0x63F71FE7: //object/tangible/deed/guild_deed/shared_tatooine_guild_style_02_deed.iff

		case 0x05F7BC15: //object/tangible/deed/corellia/player_house_deed/shared_corellia_house_large_deed.iff
		case 0xF36F169A: //object/tangible/deed/corellia/player_house_deed/shared_corellia_house_medium_deed.iff
		case 0x4571BAB6: //object/tangible/deed/corellia/player_house_deed/shared_corellia_house_small_deed.iff

		case 0x03CE0D00: //object/tangible/deed/naboo/player_house_deed/shared_naboo_house_large_deed.iff
		case 0xD0584E28: //object/tangible/deed/naboo/player_house_deed/shared_naboo_house_medium_deed.iff
		case 0x43480BA3: //object/tangible/deed/naboo/player_house_deed/shared_naboo_house_small_deed.iff
		case 0xAEA2F701: //object/tangible/deed/player_house_deed/shared_corellia_house_large_deed.iff
		case 0x0E051C75: //object/tangible/deed/player_house_deed/shared_corellia_house_large_style_02_deed.iff
		case 0x7C409FF5: //object/tangible/deed/player_house_deed/shared_corellia_house_medium_deed.iff
		case 0x9217CAC4: //object/tangible/deed/player_house_deed/shared_corellia_house_medium_style_02_deed.iff
		case 0xEE24F1A2: //object/tangible/deed/player_house_deed/shared_corellia_house_small_deed.iff
		case 0xFC820F50: //object/tangible/deed/player_house_deed/shared_corellia_house_small_floor_02_deed.iff
		case 0x8CD7386A: //object/tangible/deed/player_house_deed/shared_corellia_house_small_style_02_deed.iff
		case 0xBD4E39FA: //object/tangible/deed/player_house_deed/shared_corellia_house_small_style_02_floor_02_deed.iff
		case 0x67C936E3: //object/tangible/deed/player_house_deed/shared_generic_house_large_deed.iff
		case 0xD5D68F6C: //object/tangible/deed/player_house_deed/shared_generic_house_large_style_02_deed.iff
		case 0x68C21D63: //object/tangible/deed/player_house_deed/shared_generic_house_medium_deed.iff
		case 0x7B54534C: //object/tangible/deed/player_house_deed/shared_generic_house_medium_style_02_deed.iff
		case 0x274F3040: //object/tangible/deed/player_house_deed/shared_generic_house_small_deed.iff
		case 0x27519C49: //object/tangible/deed/player_house_deed/shared_generic_house_small_floor_02_deed.iff
		case 0x5704AB73: //object/tangible/deed/player_house_deed/shared_generic_house_small_style_02_deed.iff
		case 0x721D4D62: //object/tangible/deed/player_house_deed/shared_generic_house_small_style_02_floor_02_deed.iff
		case 0xA872D1FD: //object/tangible/deed/player_house_deed/shared_merchant_tent_style_01_deed.iff
		case 0x2D022CE3: //object/tangible/deed/player_house_deed/shared_merchant_tent_style_02_deed.iff
		case 0xAD928C84: //object/tangible/deed/player_house_deed/shared_merchant_tent_style_03_deed.iff
		case 0x9090CB14: //object/tangible/deed/player_house_deed/shared_naboo_house_large_deed.iff
		case 0xA6C0476F: //object/tangible/deed/player_house_deed/shared_naboo_house_medium_deed.iff
		case 0xEE65658A: //object/tangible/deed/player_house_deed/shared_naboo_house_medium_style_02_deed.iff
		case 0xD016CDB7: //object/tangible/deed/player_house_deed/shared_naboo_house_small_deed.iff
		case 0xEF0AAC25: //object/tangible/deed/player_house_deed/shared_naboo_house_small_style_02_deed.iff
		case 0x06FC884E: //object/tangible/deed/player_house_deed/shared_tatooine_house_large_deed.iff
		case 0xF5186B43: //object/tangible/deed/player_house_deed/shared_tatooine_house_medium_deed.iff
		case 0x467A8EED: //object/tangible/deed/player_house_deed/shared_tatooine_house_small_deed.iff
		case 0x83190387: //object/tangible/deed/player_house_deed/shared_tatooine_house_small_style_02_deed.iff
			return BUILDING; // Player House

		case 0xC43635AD: //object/intangible/pet/shared_pet_deed.iff
		case 0x95396146: //object/tangible/deed/base/shared_pet_deed_base.iff
		case 0xF32F271D: //object/tangible/deed/base/shared_pet_droid_deed_base.iff
		case 0x749E0A9B: //object/tangible/deed/pet_deed/shared_acklay_deed.iff
		case 0x93FC80F4: //object/tangible/deed/pet_deed/shared_angler_deed.iff
		case 0xD86A9900: //object/tangible/deed/pet_deed/shared_bageraset_deed.iff
		case 0x8D03DF17: //object/tangible/deed/pet_deed/shared_bantha_deed.iff
		case 0x04A7C039: //object/tangible/deed/pet_deed/shared_bearded_jax_deed.iff
		case 0xAF7FAE10: //object/tangible/deed/pet_deed/shared_blurrg_deed.iff
		case 0x2DED5FBD: //object/tangible/deed/pet_deed/shared_boar_wolf_deed.iff
		case 0x6A99DACF: //object/tangible/deed/pet_deed/shared_bocatt_deed.iff
		case 0xC5D4BDC1: //object/tangible/deed/pet_deed/shared_bol_deed.iff
		case 0x15369B33: //object/tangible/deed/pet_deed/shared_bolle_bol_deed.iff
		case 0xC451B9A3: //object/tangible/deed/pet_deed/shared_bolma_deed.iff
		case 0xE578C3E3: //object/tangible/deed/pet_deed/shared_bordok_deed.iff
		case 0xA24D2535: //object/tangible/deed/pet_deed/shared_brackaset_deed.iff
		case 0x5BC95CEA: //object/tangible/deed/pet_deed/shared_carrion_spat_deed.iff
		case 0x21E9B12D: //object/tangible/deed/pet_deed/shared_choku_deed.iff
		case 0x51D181A5: //object/tangible/deed/pet_deed/shared_cu_pa_deed.iff
		case 0xE93A50EA: //object/tangible/deed/pet_deed/shared_dalyrake_deed.iff
		case 0xC94C451F: //object/tangible/deed/pet_deed/shared_deed_3p0_advanced_basic.iff
		case 0x545EAD59: //object/tangible/deed/pet_deed/shared_deed_3p0_basic.iff
		case 0x7AA7823A: //object/tangible/deed/pet_deed/shared_deed_binary_load_lifter_advanced_basic.iff
		case 0x9B0C67E0: //object/tangible/deed/pet_deed/shared_deed_binary_load_lifter_basic.iff
		case 0xC0232FA2: //object/tangible/deed/pet_deed/shared_deed_droid_basic_base.iff
		case 0x22B44412: //object/tangible/deed/pet_deed/shared_deed_dz70_advanced_basic.iff
		case 0xBCD36E9C: //object/tangible/deed/pet_deed/shared_deed_dz70_basic.iff
		case 0x6DF29B8B: //object/tangible/deed/pet_deed/shared_deed_le_repair_advanced_basic.iff
		case 0x349C76F5: //object/tangible/deed/pet_deed/shared_deed_le_repair_basic.iff
		case 0xB862BB26: //object/tangible/deed/pet_deed/shared_deed_mse_advanced_basic.iff
		case 0x2A5A169A: //object/tangible/deed/pet_deed/shared_deed_mse_basic.iff
		case 0xEA8B55C8: //object/tangible/deed/pet_deed/shared_deed_power_advanced_basic.iff
		case 0xD18CDC06: //object/tangible/deed/pet_deed/shared_deed_power_basic.iff
		case 0x8A0F6B70: //object/tangible/deed/pet_deed/shared_deed_probot_advanced_basic.iff
		case 0xCC804878: //object/tangible/deed/pet_deed/shared_deed_probot_basic.iff
		case 0x53BEDD07: //object/tangible/deed/pet_deed/shared_deed_r2_advanced_basic.iff
		case 0xBB142A16: //object/tangible/deed/pet_deed/shared_deed_r2_basic.iff
		case 0x67BC52D1: //object/tangible/deed/pet_deed/shared_deed_r3_advanced_basic.iff
		case 0x42B8ADF8: //object/tangible/deed/pet_deed/shared_deed_r3_basic.iff
		case 0xEBB1FDF3: //object/tangible/deed/pet_deed/shared_deed_r4_advanced_basic.iff
		case 0xA77D011C: //object/tangible/deed/pet_deed/shared_deed_r4_basic.iff
		case 0xDFB37225: //object/tangible/deed/pet_deed/shared_deed_r5_advanced_basic.iff
		case 0x5ED186F2: //object/tangible/deed/pet_deed/shared_deed_r5_basic.iff
		case 0x6C66E751: //object/tangible/deed/pet_deed/shared_deed_surgical_advanced_basic.iff
		case 0xBE7D5CA6: //object/tangible/deed/pet_deed/shared_deed_surgical_basic.iff
		case 0x21638809: //object/tangible/deed/pet_deed/shared_deed_treadwell_advanced_basic.iff
		case 0x33CAC5DF: //object/tangible/deed/pet_deed/shared_deed_treadwell_basic.iff
		case 0x47987944: //object/tangible/deed/pet_deed/shared_dewback_deed.iff
		case 0x49A5A230: //object/tangible/deed/pet_deed/shared_dune_lizard_deed.iff
		case 0x21DD117D: //object/tangible/deed/pet_deed/shared_durni_deed.iff
		case 0xA864EB88: //object/tangible/deed/pet_deed/shared_eopie_deed.iff
		case 0x582AC810: //object/tangible/deed/pet_deed/shared_falumpaset_deed.iff
		case 0x8C850951: //object/tangible/deed/pet_deed/shared_fambaa_deed.iff
		case 0x4834D34F: //object/tangible/deed/pet_deed/shared_gnort_deed.iff
		case 0xF88FED19: //object/tangible/deed/pet_deed/shared_graul_deed.iff
		case 0x1252BAB6: //object/tangible/deed/pet_deed/shared_gronda_deed.iff
		case 0xD2EF4BBB: //object/tangible/deed/pet_deed/shared_gualama_deed.iff
		case 0x9B3B352F: //object/tangible/deed/pet_deed/shared_guf_drolg_deed.iff
		case 0x6DC3ADDA: //object/tangible/deed/pet_deed/shared_gurnaset_deed.iff
		case 0x72170C76: //object/tangible/deed/pet_deed/shared_gurrcat_deed.iff
		case 0x238A8DC9: //object/tangible/deed/pet_deed/shared_gurreck_deed.iff
		case 0xF6E1DA86: //object/tangible/deed/pet_deed/shared_hermit_spider_deed.iff
		case 0xA49BAC55: //object/tangible/deed/pet_deed/shared_huf_dun_deed.iff
		case 0x8CECBE1F: //object/tangible/deed/pet_deed/shared_huurton_deed.iff
		case 0xE9C49B02: //object/tangible/deed/pet_deed/shared_ikopi_deed.iff
		case 0xBD73DBD6: //object/tangible/deed/pet_deed/shared_kaadu_deed.iff
		case 0x58C24ED4: //object/tangible/deed/pet_deed/shared_kahmurra_deed.iff
		case 0x4C79BF55: //object/tangible/deed/pet_deed/shared_kima_deed.iff
		case 0x4C6F8ECD: //object/tangible/deed/pet_deed/shared_kimogila_deed.iff
		case 0xAEAC115A: //object/tangible/deed/pet_deed/shared_kliknik_deed.iff
		case 0x907440FC: //object/tangible/deed/pet_deed/shared_krahbu_deed.iff
		case 0xF0175405: //object/tangible/deed/pet_deed/shared_kusak_deed.iff
		case 0x0761F04A: //object/tangible/deed/pet_deed/shared_kwi_deed.iff
		case 0xD409C1C0: //object/tangible/deed/pet_deed/shared_langlatch_deed.iff
		case 0x417BE717: //object/tangible/deed/pet_deed/shared_malkloc_deed.iff
		case 0x85B4B1CD: //object/tangible/deed/pet_deed/shared_mawgax_deed.iff
		case 0x3E2AF509: //object/tangible/deed/pet_deed/shared_merek_deed.iff
		case 0x0A4EE0AA: //object/tangible/deed/pet_deed/shared_mott_deed.iff
		case 0xE75CA0DC: //object/tangible/deed/pet_deed/shared_narglatch_deed.iff
		case 0x3D2C46A7: //object/tangible/deed/pet_deed/shared_piket_deed.iff
		case 0x8533487A: //object/tangible/deed/pet_deed/shared_pugoriss_deed.iff
		case 0x4B296DA4: //object/tangible/deed/pet_deed/shared_rancor_deed.iff
		case 0x6FA340A2: //object/tangible/deed/pet_deed/shared_roba_deed.iff
		case 0x366D5CCA: //object/tangible/deed/pet_deed/shared_ronto_deed.iff
		case 0x4597D75D: //object/tangible/deed/pet_deed/shared_sand_panther_deed.iff
		case 0x0FE6FD79: //object/tangible/deed/pet_deed/shared_sharnaff_deed.iff
		case 0xDC414060: //object/tangible/deed/pet_deed/shared_shear_mite_deed.iff
		case 0xB5147BE1: //object/tangible/deed/pet_deed/shared_slice_hound_deed.iff
		case 0x77F39352: //object/tangible/deed/pet_deed/shared_snorbal_deed.iff
		case 0x1DA7FBFB: //object/tangible/deed/pet_deed/shared_squall_deed.iff
		case 0x586E8A62: //object/tangible/deed/pet_deed/shared_swirl_prong_deed.iff
		case 0xECFCE50A: //object/tangible/deed/pet_deed/shared_thune_deed.iff
		case 0x37D704A7: //object/tangible/deed/pet_deed/shared_torton_deed.iff
		case 0x1EDA4A80: //object/tangible/deed/pet_deed/shared_tybis_deed.iff
		case 0xA7ECCAD6: //object/tangible/deed/pet_deed/shared_veermok_deed.iff
		case 0xEC98662A: //object/tangible/deed/pet_deed/shared_vehicular_prototype.iff
		case 0x438DCA93: //object/tangible/deed/pet_deed/shared_vehicular_prototype_bike.iff
		case 0x68C0197F: //object/tangible/deed/pet_deed/shared_verne_deed.iff
		case 0x0492EF4F: //object/tangible/deed/pet_deed/shared_vesp_deed.iff
		case 0x90BF186D: //object/tangible/deed/pet_deed/shared_vir_vur_deed.iff
		case 0x92D66FA0: //object/tangible/deed/pet_deed/shared_woolamander_deed.iff
		case 0x4610E570: //object/tangible/deed/pet_deed/shared_zucca_boar_deed.iff
			return 0; // PET


		case 0x0BADF2FA: //object/tangible/ship/crafted/chassis/shared_awing_deed.iff
		case 0xE8F85768: //object/tangible/ship/crafted/chassis/shared_base_deed.iff
		case 0x78924BED: //object/tangible/ship/crafted/chassis/shared_blacksun_heavy_s01_deed.iff
		case 0xFDE2B6F3: //object/tangible/ship/crafted/chassis/shared_blacksun_heavy_s02_deed.iff
		case 0x7D721694: //object/tangible/ship/crafted/chassis/shared_blacksun_heavy_s03_deed.iff
		case 0xF3C25178: //object/tangible/ship/crafted/chassis/shared_blacksun_heavy_s04_deed.iff
		case 0xCA56EAD0: //object/tangible/ship/crafted/chassis/shared_blacksun_light_s01_deed.iff
		case 0x4F2617CE: //object/tangible/ship/crafted/chassis/shared_blacksun_light_s02_deed.iff
		case 0xCFB6B7A9: //object/tangible/ship/crafted/chassis/shared_blacksun_light_s03_deed.iff
		case 0x4106F045: //object/tangible/ship/crafted/chassis/shared_blacksun_light_s04_deed.iff
		case 0x458B410C: //object/tangible/ship/crafted/chassis/shared_blacksun_medium_s01_deed.iff
		case 0xC0FBBC12: //object/tangible/ship/crafted/chassis/shared_blacksun_medium_s02_deed.iff
		case 0x406B1C75: //object/tangible/ship/crafted/chassis/shared_blacksun_medium_s03_deed.iff
		case 0xCEDB5B99: //object/tangible/ship/crafted/chassis/shared_blacksun_medium_s04_deed.iff
		case 0xC3B5A1B9: //object/tangible/ship/crafted/chassis/shared_bwing_deed.iff
		case 0xEE5F28E8: //object/tangible/ship/crafted/chassis/shared_decimator_deed.iff
		case 0x821838BB: //object/tangible/ship/crafted/chassis/shared_firespray_deed.iff
		case 0xB425025B: //object/tangible/ship/crafted/chassis/shared_hutt_heavy_s01_deed.iff
		case 0x3155FF45: //object/tangible/ship/crafted/chassis/shared_hutt_heavy_s02_deed.iff
		case 0x06E1A366: //object/tangible/ship/crafted/chassis/shared_hutt_light_s01_deed.iff
		case 0x83915E78: //object/tangible/ship/crafted/chassis/shared_hutt_light_s02_deed.iff
		case 0x9A44FCF1: //object/tangible/ship/crafted/chassis/shared_hutt_medium_s01_deed.iff
		case 0x1F3401EF: //object/tangible/ship/crafted/chassis/shared_hutt_medium_s02_deed.iff
		case 0xA7F00335: //object/tangible/ship/crafted/chassis/shared_hutt_turret_ship_deed.iff
		case 0xA1142B2E: //object/tangible/ship/crafted/chassis/shared_tie_in_deed.iff
		case 0xEB101486: //object/tangible/ship/crafted/chassis/shared_tie_light_duty_deed.iff
		case 0x1FE78C32: //object/tangible/ship/crafted/chassis/shared_tieadvanced_deed.iff
		case 0x2C096954: //object/tangible/ship/crafted/chassis/shared_tieaggressor_deed.iff
		case 0x7FDD130B: //object/tangible/ship/crafted/chassis/shared_tiebomber_deed.iff
		case 0x56D3FEF8: //object/tangible/ship/crafted/chassis/shared_tiefighter_deed.iff
		case 0xCBA71C8A: //object/tangible/ship/crafted/chassis/shared_tieinterceptor_deed.iff
		case 0x1C14145B: //object/tangible/ship/crafted/chassis/shared_tieoppressor_deed.iff
		case 0x161EEB91: //object/tangible/ship/crafted/chassis/shared_xwing_deed.iff
		case 0x316AB9FC: //object/tangible/ship/crafted/chassis/shared_ykl37r_deed.iff
		case 0x9C7377A2: //object/tangible/ship/crafted/chassis/shared_yt1300_deed.iff
		case 0x51E92550: //object/tangible/ship/crafted/chassis/shared_ywing_deed.iff
		case 0xB475EC2B: //object/tangible/ship/crafted/chassis/shared_ywing_longprobe_deed.iff
		case 0x291AF89C: //object/tangible/ship/crafted/chassis/shared_z95_deed.iff
		case 0x87E877A4: //object/tangible/space/veteran_reward/shared_sorosuub_space_yacht_deed.iff
		default:
			return 0; // SPACE

	}


}


String& DeedObjectImplementation::getDefaultTemplateName(uint32 objCRC) {

/*
	1	weapon_station_deed_name	Deed for: Weapon Crafting Station
	2	food_station_deed_name	Deed for: Food Crafting Station
	3	structure_station_deed_name	Deed for: Structure crafting station
	4	fusion_generator_deed_name	Deed for: Fusion Power Generator
	5	photo_bio_generator_deed_name	Deed for: Photo/Bio Power Generator
	6	solar_generator_deed_name	Deed for: Solar Power Generator
	7	wind_generator_deed_name	Deed for: Wind Power Generator
	8	ore_s1_harvester_deed_name	Deed for: Personal Mineral Extractor
	9	ore_s2_harvester_deed_name	Deed for: Mineral Mining Installation
	10	liquid_harvester_deed_name	Deed for: Personal Chemical Extractor
	11	moisture_harvester_deed_name	Deed for: Personal Moisture Vaporator
	12	gas_harvester_deed_name	Deed for: Personal Natural Gas Processor
	13	item_factory	Deed for: Equipment Factory
	14	food_factory	Deed for: Food Factory
	15	structure_factory	Deed for: Structure Factory
	16	clothing_factory	Deed for: Wearables Factory
	17	creature_harvester_deed_name	Deed for: Automated Creature Farm
	18	flora_harvester_deed_name	Deed for: Micro Flora Farm
	19	test_deed	Test Deed
	20	tatooine_house_small_deed	Deed for: Small Tatooine House
	21	tatooine_house_medium_deed	Deed for: Medium Tatooine House
	22	tatooine_house_large_deed	Deed for: Large Tatooine House
	23	tatooine_guild_deed	Deed for: Tatooine Guildhall
	24	corellia_house_large_deed	Deed for: Large Corellia House
	25	corellia_house_medium_deed	Deed for: Medium Corellia House
	26	corellia_house_small_deed	Deed for: Small Corellia House
	27	naboo_house_large_deed	Deed for: Large Naboo House
	28	naboo_house_medium_deed	Deed for: Medium Naboo House
	29	naboo_house_small_deed	Deed for: Small Naboo House
	30	turret_block_large_deed_name	Deed for: Large Block Turret
	31	turret_block_medium_deed_name	Deed for: Medium Block Turret
	32	turret_block_small_deed_name	Deed for: Small Block Turret
	33	ore_heavy_harvester_deed_name	Deed for: Heavy Mineral Mining Installation
	34	flora_harvester_medium_deed_name	Deed for: Automated Flora Farm
	35	flora_harvester_heavy_deed_name	Deed for: High Capacity Flora Farm
	36	gas_harvester_medium_deed_name	Deed for: Natural Gas Processor
	37	gas_harvester_heavy_deed_name	Deed for: Heavy Natural Gas Processor
	38	moisture_harvester_heavy_deed_name	Deed for: High Efficiency Moisture Vaporator
	39	moisture_harvester_medium_deed_name	Deed for: Moisture Vaporator
	40	liquid_harvester_heavy_deed_name	Deed for: Deep Crust Chemical Extractor
	41	liquid_harvester_medium_deed_name	Deed for: Chemical Extractor
	42	covert_detector_32m	Deed for: Covert Faction Scanner
	43	naboo_house_medium_style_2_deed	Deed for: Medium Naboo House (Style 2)
	44	naboo_house_small_style_2_deed	Deed for: Small Naboo House (Style 2)
	45	tatooine_house_small_style_2_deed	Deed for: Small Tatooine House (Style 2)
	46	corellia_guild_deed	Deed for: Corellian Guild Hall
	47	generic_guild_deed	Deed for: Generic Planet Guild Hall
	48	naboo_guild_deed	Deed for: Naboo Guild Hall
	49	tatooine_guild_2_deed	Deed for: Tatooine Guild Hall
	50	generic_house_large_deed	Deed for: Large Generic Planet House
	51	generic_house_large_style_2_deed	Deed for: Large Generic Planet House (Style 2)
	52	generic_house_medium_deed	Deed for: Medium Generic Planet House
	53	generic_house_medium_style_2_deed	Deed for: Medium Generic Planet House (Style 2)
	54	generic_house_small_deed	Deed for: Small Generic Planet House
	55	generic_house_small_floor_2_deed	Deed for: Small Generic Planet House (Floorplan 2)
	56	generic_house_small_style_2_deed	Deed for: Small Generic Planet House (Style 2)
	57	generic_house_small_style_2_floor_2_deed	Deed for: Small Generic Planet House (Style 2, Floorplan 2)
	58	minefield_1x1	Deed for: Small Minefield
	59	corellia_house_small_floor_2	Deed for: Small Corellia House (Floorplan 2)
	60	corellia_house_small_style_2_floor_2_deed	Deed for: Small Corellia House (Style 2, Floorplan 2)
	61	corellia_house_small_style_2_deed	Deed for: Small Corellia House (Style 2)
	62	corellia_house_large_style_2_deed	Deed for: Large Corellia House (Style 2)
	63	corellia_house_small_floor_2_deed	Deed for: Small Corellia House (Floorplan 2)
	64	turret_tower_lg	Deed for: Large Turret Tower
	65	turret_tower_med	Deed for: Medium Turret Tower
	66	turret_tower_sm	Deed for: Small Turret Tower
	67	turret_block_lg	Deed for: Large Block Turret
	68	turret_dish_sm	Deed for: Small Dish Turret
	69	turret_dish_med	Deed for: Medium Dish Turret
	70	turret_dish_lg	Deed for: Large Dish Turret
	71	turret_block_med	Deed for: Medium Block Turret
	72	turret_block_sm	Deed for: Small Block Turret
	73	hq_base	Deed for: Unknown Factional HQ
	74	hq_s01	Deed for: Forward Outpost
	75	hq_s02	Deed for: Field Hospital
	76	hq_s03	Deed for: Tactical Center
	77	hq_s04	Deed for: Detachment HQ
	78	hq_s05	Deed for: Strategic Base
	79	treadwell_basic_deed	Deed for: Treadwell Droid
	80	p0_basic_deed	Deed for: Protocol Droid
	81	binary_load_lifter_basic_deed	Deed for: Binary Load Lifter Droid
	82	droid_basic_base_deed	Deed for: Droid Deed Base Object
	83	dz70_advanced_basic_deed	Deed for: DZ70 Droid, Advanced Model
	84	le_repair_advanced_basic_deed	Deed for: LE Repair Droid, Advanced Model
	85	le_repair_basic_deed	Deed for: LE Repair Droid
	86	mse_advanced_basic_deed	Deed for: MSE Droid, Advanced Model
	87	power_advanced_basic_deed	Deed for: Power Droid, Advanced Model
	88	power_basic_deed	Deed for: Power Droid
	89	probot_advanced_basic_deed	Deed for: Probot, Advanced Model
	90	r2_advanced_basic_deed	Deed for: R2 Droid, Advanced Model
	91	r2_basic_deed	Deed for: R2 Droid
	92	r3_advanced_basic_deed	Deed for: R3 Droid, Advanced Model
	93	r4_advanced_basic_deed	Deed for: R4 Droid, Advanced Model
	94	r4_basic_deed	Deed for: R4 Droid
	95	r5_basic_deed	Deed for: R5 Droid
	96	surgical_advanced_basic_deed	Deed for: Surgical Droid, Advanced Model
	97	surgical_basic_deed	Deed for: Surgical Droid
	98	p0_advanced_basic_deed	Deed for: Protocol Droid, Advanced Model
	99	binary_load_lifter_advanced_basic_deed	Deed for: Binary Load Lifter Droid, Advanced Model
	100	dz70_basic_deed	Deed for: DZ70 Droid
	101	mse_basic_deed	Deed for: MSE Droid
	102	probot_basic_deed	Deed for: Probot
	103	r3_basic_deed	Deed for: R3 Droid
	104	r5_advanced_basic_deed	Deed for: R5 Droid, Advanced Model
	105	treadwell_advanced_basic_deed	Deed for: WED Treadwell, Advanced Model
	106	tatooine_city_deed	Deed for: Tatooine City Hall
	107	naboo_city_deed	Deed for: Naboo City Hall
	108	corellia_city_deed	Deed for: Corellia City Hall
	109	tatooine_hospital_deed	Deed for: Tatooine Hospital
	110	naboo_hospital_deed	Deed for: Naboo Hospital
	111	corellia_hospital_deed	Deed for: Corellia Hospital
	112	naboo_theater_deed	Deed for: Naboo Theater
	113	tatooine_theater_deed	Deed for: Tatooine Theater
	114	corellia_theater_deed	Deed for: Corellia Theater
	115	tatooine_cantina_deed	Deed for: Tatooine Cantina
	116	naboo_cantina_deed	Deed for: Naboo Cantina
	117	corellia_cantina_deed	Deed for: Corellia Cantina
	118	tatooine_bank_deed	Deed for: Tatooine Bank
	119	corellia_bank_deed	Deed for: Corellia Bank
	120	naboo_bank_deed	Deed for: Naboo Bank
	121	naboo_shuttleport_deed	Deed for: Naboo Shuttleport
	122	corellia_shuttleport_deed	Deed for: Corellia Shuttleport
	123	tatooine_shuttleport_deed	Deed for: Tatooine Shuttleport
	124	corellia_cloning_deed	Deed for: Corellia Cloning Facility
	125	naboo_cloning_deed	Deed for: Naboo Cloning Facility
	126	tatooine_cloning_deed	Deed for: Tatooine Cloning Facility
	127	garden_corellia_lrg_01_deed	Deed for: Large Garden
	128	garden_corellia_lrg_02_deed	Deed for: Corellian Fountain Spire (Garden)
	129	garden_corellia_lrg_03_deed	Deed for: Corellian Decorative Path (Garden)
	130	garden_corellia_lrg_04_deed	Deed for: Corellian Planters (Garden)
	131	garden_corellia_lrg_05_deed	Deed for: Corellian Shrine (Garden)
	132	garden_corellia_med_01_deed	Deed for: Medium Garden
	133	garden_corellia_med_02_deed	Deed for: Corellian Spires (Garden)
	134	garden_corellia_med_03_deed	Deed for: Corellian Arches (Garden)
	135	garden_corellia_med_04_deed	Deed for: Corellian Simple Arrangement (Garden)
	136	garden_corellia_med_05_deed	Deed for: Corellian Fountain & Benches (Garden)
	137	garden_corellia_sml_01_deed	Deed for: Small Garden
	138	garden_corellia_sml_02_deed	Deed for: Corellian Artistic Arrangement (Garden)
	139	garden_corellia_sml_03_deed	Deed for: Corellian Globe Arrangement (Garden)
	140	garden_corellia_sml_04_deed	Deed for: Corellian Tree & Columns (Garden)
	141	garden_corellia_sml_05_deed	Deed for: Corellian Small Fountain & Benches (Garden)
	142	garden_dantooine_lrg_01_deed	Deed for: Dantooine Meditation Area (Garden)
	143	garden_dantooine_med_01_deed	Deed for: Dantooine Spirit Stone (Garden)
	144	garden_dantooine_sml_01_deed	Deed for: Dantooine Totem (Garden)
	145	garden_dathomir_lrg_01_deed	Deed for: Dathomir Obelisk (Garden)
	146	garden_dathomir_med_01_deed	Deed for: Dathomir Gnarled Tree (Garden)
	147	garden_dathomir_sml_01_deed	Deed for: Dathomir Brazier (Garden)
	148	garden_endor_lrg_01_deed	Deed for: Endor Huts (Garden)
	149	garden_endor_med_01_deed	Deed for: Endor Meditative Area (Garden)
	150	garden_endor_sml_01_deed	Deed for: Endor Small Arrangement (Garden)
	151	garden_naboo_lrg_01_deed	Deed for: Naboo Round Atrium (Garden)
	152	garden_naboo_lrg_02_deed	Deed for: Naboo Large Gazebo (Garden)
	153	garden_naboo_lrg_03_deed	Deed for: Naboo Honored Stone (Garden)
	154	garden_naboo_lrg_04_deed	Deed for: Naboo Rock Arrangement (Garden)
	155	garden_naboo_lrg_05_deed	Deed for: Naboo Gazebo & Fountains (Garden)
	156	garden_naboo_med_01_deed	Deed for: Naboo Decorative Path (Garden)
	157	garden_naboo_med_02_deed	Deed for: Naboo Curved Wall (Garden)
	158	garden_naboo_med_03_deed	Deed for: Naboo Trees & Spire (Garden)
	159	garden_naboo_med_04_deed	Deed for: Naboo Trees & Sphere (Garden)
	160	garden_naboo_med_05_deed	Deed for: Naboo Fountain & Benches (Garden)
	161	garden_naboo_sml_01_deed	Deed for: Naboo Small Gazebo (Garden)
	162	garden_naboo_sml_02_deed	Deed for: Naboo Small Arrangement (Garden)
	163	garden_naboo_sml_03_deed	Deed for: Naboo Small Curved Wall (Garden)
	164	garden_naboo_sml_04_deed	Deed for: Naboo Single Tree Arrangement (Garden)
	165	garden_naboo_sml_05_deed	Deed for: Naboo Gungan Guardians (Garden)
	166	garden_tatooine_lrg_01_deed	Deed for: Tatooine Arch Circle (Garden)
	167	garden_tatooine_lrg_02_deed	Deed for: Tatooine Desert Flora Arrangement (Garden)
	168	garden_tatooine_lrg_03_deed	Deed for: Tatooine Stone Arrangement (Garden)
	169	garden_tatooine_lrg_04_deed	Deed for: Tatooine Stones & Walls (Garden)
	170	garden_tatooine_lrg_05_deed	Deed for: Tatooine Shaded Place (Garden)
	171	garden_tatooine_med_01_deed	Deed for: Tatooine Stone Path (Garden)
	172	garden_tatooine_med_02_deed	Deed for: Tatooine Small Wall Arrangement (Garden)
	173	garden_tatooine_med_03_deed	Deed for: Tatooine Dry Flora with Arch (Garden)
	174	garden_tatooine_med_04_deed	Deed for: Tatooine Secluded Path (Garden)
	175	garden_tatooine_med_05_deed	Deed for: Tatooine Cafe Area (Garden)
	176	garden_tatooine_sml_01_deed	Deed for: Tatooine Palms (Garden)
	177	garden_tatooine_sml_02_deed	Deed for: Tatooine Short Column Arrangement (Garden)
	178	garden_tatooine_sml_03_deed	Deed for: Tatooine Palm & Stones (Garden)
	179	garden_tatooine_sml_04_deed	Deed for: Tatooine Dry Planter (Garden)
	180	garden_tatooine_sml_05_deed	Deed for: Tatooine Statue & Flowers (Garden)
	181	merchant_tent	Deed for: Merchant Tent
	182	merchant_tent_2	Deed for: Merchant Tent (Grey)
	183	merchant_tent_3	Deed for: Merchant Tent (Green)
	184	naboo_garage_deed	Deed for: Naboo Garage
	185	corellia_garage_deed	Deed for: Corellia Garage
	186	tatooine_garage_deed	Deed for: Tatooine Garage
	187	hq_s01_pvp	Deed for: S.F. Forward Outpost
	188	hq_s02_pvp	Deed for: S.F. Field Hospital
	189	hq_s03_pvp	Deed for: S.F. Tactical Center
	190	hq_s04_pvp	Deed for: S.F. Detachment HQ
	191	hq_s05_pvp	Deed for: S.F. Strategic Base
	192	hq_s01_rebel	Deed for: Alliance Forward Outpost
	193	hq_s01_imperial	Deed for: Imperial Forward Outpost
	194	hq_s01_pvp_rebel	Deed for: Alliance S.F. Forward Outpost
	195	hq_s01_pvp_imperial	Deed for: Imperial S.F. Forward Outpost
	196	hq_s02_rebel	Deed for: Alliance Field Hospital
	197	hq_s02_imperial	Deed for: Imperial Field Hospital
	198	hq_s02_pvp_rebel	Deed for: Alliance S.F. Field Hospital
	199	hq_s02_pvp_imperial	Deed for: Imperial S.F. Field Hospital
	200	hq_s03_imperial	Deed for: Imperial Tactical Center
	201	hq_s03_rebel	Deed for: Alliance Tactical Center
	202	hq_s03_pvp_imperial	Deed for: Imperial S.F. Tactical Center
	203	hq_s03_pvp_rebel	Deed for: Alliance S.F. Tactical Center
	204	hq_s04_imperial	Deed for: Imperial Detachment HQ
	205	hq_s04_rebel	Deed for: Alliance Detachment HQ
	206	hq_s04_pvp_imperial	Deed for: Imperial S.F. Detachment HQ
	207	hq_s04_pvp_rebel	Deed for: Alliance S.F. Detachment HQ
	208	hq_s05_imperial	Deed for: Imperial Strategic Base
	209	hq_s05_rebel	Deed for: Rebel Strategic Base
	210	hq_s05_pvp_imperial	Deed for: Imperial S.F. Strategic Base
	211	hq_s05_pvp_rebel	Deed for: Rebel S.F. Strategic Base
 */
	switch(objCRC) {
		// Factories
		case 0x6C0893E5: //object/tangible/deed/factory_deed/shared_factory_clothing_deed.iff
			defaultTemplateName = "clothing_factory";
		case 0xCFEC24E5: //object/tangible/deed/factory_deed/shared_factory_food_deed.iff
			defaultTemplateName = "food_factory";
		case 0xFD1EF87A: //object/tangible/deed/factory_deed/shared_factory_item_deed.iff
			defaultTemplateName = "item_factory";
		case 0x8E331C08: //object/tangible/deed/factory_deed/shared_factory_structure_deed.iff
			defaultTemplateName = "structure_factory";

		// Harvesters
		case 0xE296E887: //object/tangible/deed/harvester_deed/shared_harvester_creature_deed.iff
			defaultTemplateName = "creature_harvester_deed_name";
		case 0xA9557114: //object/tangible/deed/harvester_deed/shared_harvester_flora_deed.iff
			defaultTemplateName = "flora_harvester_deed_name";
		case 0xEEC52333: //object/tangible/deed/harvester_deed/shared_harvester_flora_deed_heavy.iff
			defaultTemplateName = "flora_harvester_heavy_deed_name";
		case 0x522BE74D: //object/tangible/deed/harvester_deed/shared_harvester_flora_deed_medium.iff
			defaultTemplateName = "flora_harvester_medium_deed_name";
		case 0x85020A19: //object/tangible/deed/harvester_deed/shared_harvester_gas_deed.iff
			defaultTemplateName = "gas_harvester_deed_name";
		case 0x1090794C: //object/tangible/deed/harvester_deed/shared_harvester_gas_deed_heavy.iff
			defaultTemplateName = "gas_harvester_heavy_deed_name";
		case 0xB247C54E: //object/tangible/deed/harvester_deed/shared_harvester_gas_deed_medium.iff
			defaultTemplateName = "gas_harvester_medium_deed_name";
		case 0xC6CF0E82: //object/tangible/deed/harvester_deed/shared_harvester_liquid_deed.iff
			defaultTemplateName = "liquid_harvester_deed_name";
		case 0x4FA6CDD8: //object/tangible/deed/harvester_deed/shared_harvester_liquid_deed_heavy.iff
			defaultTemplateName = "liquid_harvester_heavy_deed_name";
		case 0xC42B47F4: //object/tangible/deed/harvester_deed/shared_harvester_liquid_deed_medium.iff
			defaultTemplateName = "liquid_harvester_medium_deed_name";
		case 0x5E1B48A7: //object/tangible/deed/harvester_deed/shared_harvester_moisture_deed.iff
			defaultTemplateName = "moisture_harvester_deed_name";
		case 0x0147A463: //object/tangible/deed/harvester_deed/shared_harvester_moisture_deed_heavy.iff
			defaultTemplateName = "moisture_harvester_heavy_deed_name";
		case 0x2D4A2C89: //object/tangible/deed/harvester_deed/shared_harvester_moisture_deed_medium.iff
			defaultTemplateName = "moisture_harvester_medium_deed_name";
		case 0xC02EBAB3: //object/tangible/deed/harvester_deed/shared_harvester_ore_heavy_deed.iff
			defaultTemplateName = "ore_heavy_harvester_deed_name";
		case 0x7EB8541F: //object/tangible/deed/harvester_deed/shared_harvester_ore_s1_deed.iff
			defaultTemplateName = "ore_s1_harvester_deed_name";
		case 0xFBC8A901: //object/tangible/deed/harvester_deed/shared_harvester_ore_s2_deed.iff
			defaultTemplateName = "ore_s2_harvester_deed_name";

		// Generators
		case 0xE5A0F395: //object/tangible/deed/generator_deed/shared_generator_fusion_deed.iff
			defaultTemplateName = "fusion_generator_deed_name";
		case 0x26D63643: //object/tangible/deed/generator_deed/shared_generator_photo_bio_deed.iff
			defaultTemplateName = "photo_bio_generator_deed_name";
		case 0x4669B528: //object/tangible/deed/generator_deed/shared_generator_solar_deed.iff
			defaultTemplateName = "solar_generator_deed_name";
		case 0xE6C711A7: //object/tangible/deed/generator_deed/shared_generator_wind_deed.iff
			defaultTemplateName = "wind_generator_deed_name";

		// Turrets
		case 0x2587A8C0: //object/tangible/deed/faction_perk/turret/shared_block_lg_deed.iff
			defaultTemplateName = "turret_block_lg";
		case 0xFBA00806: //object/tangible/deed/faction_perk/turret/shared_block_med_deed.iff
			defaultTemplateName = "turret_block_med";
		case 0xA3878091: //object/tangible/deed/faction_perk/turret/shared_block_sm_deed.iff
			defaultTemplateName = "turret_block_sm";
		case 0xF07B2F6E: //object/tangible/deed/faction_perk/turret/shared_dish_lg_deed.iff
			defaultTemplateName = "turret_dish_lg";
		case 0x767B073F: //object/tangible/deed/faction_perk/turret/shared_dish_sm_deed.iff
			defaultTemplateName = "turret_dish_sm";
		case 0xDE76DCB5: //object/tangible/deed/faction_perk/turret/shared_tower_lg_deed.iff
			defaultTemplateName = "turret_tower_lg";
		case 0xA8274B6E: //object/tangible/deed/faction_perk/turret/shared_tower_med_deed.iff
			defaultTemplateName = "turret_tower_med";
		case 0x5876F4E4: //object/tangible/deed/faction_perk/turret/shared_tower_sm_deed.iff
			defaultTemplateName = "turret_tower_sm";
		case 0x2775B687: //object/tangible/deed/turret_deed/shared_turret_block_large_deed.iff
			defaultTemplateName = "turret_block_lg";
		case 0xE0C40914: //object/tangible/deed/turret_deed/shared_turret_block_medium_deed.iff
			defaultTemplateName = "turret_block_med";
		case 0x67F3B024: //object/tangible/deed/turret_deed/shared_turret_block_small_deed.iff
			defaultTemplateName = "turret_block_sm";

		// Minefields
		case 0x5D30CDF7: //object/tangible/deed/faction_perk/minefield/shared_field_1x1_deed.iff
			defaultTemplateName = "minefield_1x1";


		case 0x9899666C: //object/tangible/deed/vehicle_deed/shared_jetpack_deed.iff
		case 0xDF4F6F37: //object/tangible/deed/vehicle_deed/shared_landspeeder_av21_deed.iff
		case 0xBEAF4CA8: //object/tangible/deed/vehicle_deed/shared_landspeeder_x31_deed.iff
		case 0x35FF563D: //object/tangible/deed/vehicle_deed/shared_landspeeder_x34_deed.iff
		case 0xF2EAD531: //object/tangible/deed/vehicle_deed/shared_speederbike_deed.iff
		case 0x70CDB867: //object/tangible/deed/vehicle_deed/shared_speederbike_flash_deed.iff
		case 0x1D885457: //object/tangible/deed/vehicle_deed/shared_speederbike_swoop_deed.iff
		case 0x1E1853F0: //object/tangible/deed/vehicle_deed/shared_vehicle_deed_base.iff
		case 0x4B3CA4DE: //object/tangible/deed/vehicle_deed/shared_vehicular_prototype_bike_deed.iff
		case 0xEDDC0F5F: //object/tangible/deed/vehicle_deed/shared_vehicular_prototype_deed.iff
			defaultTemplateName = ""; // VEHICLE types?



		// City Buildings
		case 0x17EAC380: //object/tangible/deed/city_deed/shared_bank_corellia_deed.iff
			defaultTemplateName = "corellia_bank_deed";
		case 0xD40FCD49: //object/tangible/deed/city_deed/shared_bank_naboo_deed.iff
			defaultTemplateName = "naboo_bank_deed";
		case 0x24980999: //object/tangible/deed/city_deed/shared_bank_tatooine_deed.iff
			defaultTemplateName = "tatooine_bank_deed";

		case 0x82A983A9: //object/tangible/deed/city_deed/shared_cantina_corellia_deed.iff
			defaultTemplateName = "corellia_cantina_deed";
		case 0x4F5A59D1: //object/tangible/deed/city_deed/shared_cantina_naboo_deed.iff
			defaultTemplateName = "naboo_cantina_deed";
		case 0xB1DB49B0: //object/tangible/deed/city_deed/shared_cantina_tatooine_deed.iff
			defaultTemplateName = "tatooine_cantina_deed";

		case 0xA5FE7FFF: //object/tangible/deed/city_deed/shared_cityhall_corellia_deed.iff
			defaultTemplateName = "corellia_city_deed";
		case 0xDA53F690: //object/tangible/deed/city_deed/shared_cityhall_naboo_deed.iff
			defaultTemplateName = "naboo_city_deed";
		case 0x968CB5E6: //object/tangible/deed/city_deed/shared_cityhall_tatooine_deed.iff
			defaultTemplateName = "tatooine_city_deed";

		case 0x6D60E4C7: //object/tangible/deed/city_deed/shared_cloning_corellia_deed.iff
			defaultTemplateName = "corellia_cloning_deed";
		case 0x96EF7A06: //object/tangible/deed/city_deed/shared_cloning_naboo_deed.iff
			defaultTemplateName = "naboo_cloning_deed";
		case 0x5E122EDE: //object/tangible/deed/city_deed/shared_cloning_tatooine_deed.iff
			defaultTemplateName = "tatooine_cloning_deed";

		case 0xA9B20B60: //object/tangible/deed/city_deed/shared_garage_corellia_deed.iff
			defaultTemplateName = "corellia_garage_deed";
		case 0xBF38BE5C: //object/tangible/deed/city_deed/shared_garage_naboo_deed.iff
			defaultTemplateName = "naboo_garage_deed";
		case 0x9AC0C179: //object/tangible/deed/city_deed/shared_garage_tatooine_deed.iff
			defaultTemplateName = "tatooine_garage_deed";

		case 0x9A8479F1: //object/tangible/deed/city_deed/shared_garden_corellia_lrg_01_deed.iff
			defaultTemplateName = "garden_corellia_lrg_01_deed";
		case 0x1FF484EF: //object/tangible/deed/city_deed/shared_garden_corellia_lrg_02_deed.iff
			defaultTemplateName = "garden_corellia_lrg_02_deed";
		case 0x9F642488: //object/tangible/deed/city_deed/shared_garden_corellia_lrg_03_deed.iff
			defaultTemplateName = "garden_corellia_lrg_03_deed";
		case 0x11D46364: //object/tangible/deed/city_deed/shared_garden_corellia_lrg_04_deed.iff
			defaultTemplateName = "garden_corellia_lrg_04_deed";
		case 0x9144C303: //object/tangible/deed/city_deed/shared_garden_corellia_lrg_05_deed.iff
			defaultTemplateName = "garden_corellia_lrg_05_deed";
		case 0xC5D89007: //object/tangible/deed/city_deed/shared_garden_corellia_med_01_deed.iff
			defaultTemplateName = "garden_corellia_med_01_deed";
		case 0x40A86D19: //object/tangible/deed/city_deed/shared_garden_corellia_med_02_deed.iff
			defaultTemplateName = "garden_corellia_med_02_deed";
		case 0xC038CD7E: //object/tangible/deed/city_deed/shared_garden_corellia_med_03_deed.iff
			defaultTemplateName = "garden_corellia_med_03_deed";
		case 0x4E888A92: //object/tangible/deed/city_deed/shared_garden_corellia_med_04_deed.iff
			defaultTemplateName = "garden_corellia_med_04_deed";
		case 0xCE182AF5: //object/tangibl5/deed/city_deed/shared_garden_corellia_med_05_deed.iff
			defaultTemplateName = "garden_corellia_med_05_deed";
		case 0x7CE996DF: //object/tangible/deed/city_deed/shared_garden_corellia_sml_01_deed.iff
			defaultTemplateName = "garden_corellia_sml_01_deed";
		case 0xF9996BC1: //object/tangible/deed/city_deed/shared_garden_corellia_sml_02_deed.iff
			defaultTemplateName = "garden_corellia_sml_02_deed";
		case 0x7909CBA6: //object/tangible/deed/city_deed/shared_garden_corellia_sml_03_deed.iff
			defaultTemplateName = "garden_corellia_sml_03_deed";
		case 0xF7B98C4A: //object/tangible/deed/city_deed/shared_garden_corellia_sml_04_deed.iff
			defaultTemplateName = "garden_corellia_sml_04_deed";
		case 0x77292C2D: //object/tangible/deed/city_deed/shared_garden_corellia_sml_05_deed.iff
			defaultTemplateName = "garden_corellia_sml_05_deed";
		case 0x44BC3437: //object/tangible/deed/city_deed/shared_garden_dantooine_lrg_01_deed.iff
			defaultTemplateName = "garden_dantooine_lrg_01_deed";
		case 0x1BE0DDC1: //object/tangible/deed/city_deed/shared_garden_dantooine_med_01_deed.iff
			defaultTemplateName = "garden_dantooine_med_01_deed";
		case 0xA2D1DB19: //object/tangible/deed/city_deed/shared_garden_dantooine_sml_01_deed.iff
			defaultTemplateName = "garden_dantooine_sml_01_deed";
		case 0xC6813FAE: //object/tangible/deed/city_deed/shared_garden_dathomir_lrg_01_deed.iff
			defaultTemplateName = "garden_dathomir_lrg_01_deed";
		case 0x99DDD658: //object/tangible/deed/city_deed/shared_garden_dathomir_med_01_deed.iff
			defaultTemplateName = "garden_dathomir_med_01_deed";
		case 0x20ECD080: //object/tangible/deed/city_deed/shared_garden_dathomir_sml_01_deed.iff
			defaultTemplateName = "garden_dathomir_sml_01_deed";
		case 0xFE4BC6C5: //object/tangible/deed/city_deed/shared_garden_endor_lrg_01_deed.iff
			defaultTemplateName = "garden_endor_lrg_01_deed";
		case 0xA1172F33: //object/tangible/deed/city_deed/shared_garden_endor_med_01_deed.iff
			defaultTemplateName = "garden_endor_med_01_deed";
		case 0x182629EB: //object/tangible/deed/city_deed/shared_garden_endor_sml_01_deed.iff
			defaultTemplateName = "garden_endor_sml_01_deed";
		case 0x187D2021: //object/tangible/deed/city_deed/shared_garden_naboo_lrg_01_deed.iff
			defaultTemplateName = "garden_naboo_lrg_01_deed";
		case 0x9D0DDD3F: //object/tangible/deed/city_deed/shared_garden_naboo_lrg_02_deed.iff
			defaultTemplateName = "garden_naboo_lrg_02_deed";
		case 0x1D9D7D58: //object/tangible/deed/city_deed/shared_garden_naboo_lrg_03_deed.iff
			defaultTemplateName = "garden_naboo_lrg_03_deed";
		case 0x932D3AB4: //object/tangible/deed/city_deed/shared_garden_naboo_lrg_04_deed.iff
			defaultTemplateName = "garden_naboo_lrg_04_deed";
		case 0x13BD9AD3: //object/tangible/deed/city_deed/shared_garden_naboo_lrg_05_deed.iff
			defaultTemplateName = "garden_naboo_lrg_05_deed";
		case 0x4721C9D7: //object/tangible/deed/city_deed/shared_garden_naboo_med_01_deed.iff
			defaultTemplateName = "garden_naboo_med_01_deed";
		case 0xC25134C9: //object/tangible/deed/city_deed/shared_garden_naboo_med_02_deed.iff
			defaultTemplateName = "garden_naboo_med_02_deed";
		case 0x42C194AE: //object/tangible/deed/city_deed/shared_garden_naboo_med_03_deed.iff
			defaultTemplateName = "garden_naboo_med_03_deed";
		case 0xCC71D342: //object/tangible/deed/city_deed/shared_garden_naboo_med_04_deed.iff
			defaultTemplateName = "garden_naboo_med_04_deed";
		case 0x4CE17325: //object/tangible/deed/city_deed/shared_garden_naboo_med_05_deed.iff
			defaultTemplateName = "garden_naboo_med_05_deed";
		case 0xFE10CF0F: //object/tangible/deed/city_deed/shared_garden_naboo_sml_01_deed.iff
			defaultTemplateName = "garden_naboo_sml_01_deed";
		case 0x7B603211: //object/tangible/deed/city_deed/shared_garden_naboo_sml_02_deed.iff
			defaultTemplateName = "garden_naboo_sml_02_deed";
		case 0xFBF09276: //object/tangible/deed/city_deed/shared_garden_naboo_sml_03_deed.iff
			defaultTemplateName = "garden_naboo_sml_03_deed";
		case 0x7540D59A: //object/tangible/deed/city_deed/shared_garden_naboo_sml_04_deed.iff
			defaultTemplateName = "garden_naboo_sml_04_deed";
		case 0xF5D075FD: //object/tangible/deed/city_deed/shared_garden_naboo_sml_05_deed.iff
			defaultTemplateName = "garden_naboo_sml_05_deed";
		case 0x57C36C6D: //object/tangible/deed/city_deed/shared_garden_tatooine_lrg_01_deed.iff
			defaultTemplateName = "garden_tatooine_lrg_01_deed";
		case 0xD2B39173: //object/tangible/deed/city_deed/shared_garden_tatooine_lrg_02_deed.iff
			defaultTemplateName = "garden_tatooine_lrg_02_deed";
		case 0x52233114: //object/tangible/deed/city_deed/shared_garden_tatooine_lrg_03_deed.iff
			defaultTemplateName = "garden_tatooine_lrg_03_deed";
		case 0xDC9376F8: //object/tangible/deed/city_deed/shared_garden_tatooine_lrg_04_deed.iff
			defaultTemplateName = "garden_tatooine_lrg_04_deed";
		case 0x5C03D69F: //object/tangible/deed/city_deed/shared_garden_tatooine_lrg_05_deed.iff
			defaultTemplateName = "garden_tatooine_lrg_05_deed";
		case 0x089F859B: //object/tangible/deed/city_deed/shared_garden_tatooine_med_01_deed.iff
			defaultTemplateName = "garden_tatooine_med_01_deed";
		case 0x8DEF7885: //object/tangible/deed/city_deed/shared_garden_tatooine_med_02_deed.iff
			defaultTemplateName = "garden_tatooine_med_02_deed";
		case 0x0D7FD8E2: //object/tangible/deed/city_deed/shared_garden_tatooine_med_03_deed.iff
			defaultTemplateName = "garden_tatooine_med_03_deed";
		case 0x83CF9F0E: //object/tangible/deed/city_deed/shared_garden_tatooine_med_04_deed.iff
			defaultTemplateName = "garden_tatooine_med_04_deed";
		case 0x035F3F69: //object/tangible/deed/city_deed/shared_garden_tatooine_med_05_deed.iff
			defaultTemplateName = "garden_tatooine_med_05_deed";
		case 0xB1AE8343: //object/tangible/deed/city_deed/shared_garden_tatooine_sml_01_deed.iff
			defaultTemplateName = "garden_tatooine_sml_01_deed";
		case 0x34DE7E5D: //object/tangible/deed/city_deed/shared_garden_tatooine_sml_02_deed.iff
			defaultTemplateName = "garden_tatooine_sml_02_deed";
		case 0xB44EDE3A: //object/tangible/deed/city_deed/shared_garden_tatooine_sml_03_deed.iff
			defaultTemplateName = "garden_tatooine_sml_03_deed";
		case 0x3AFE99D6: //object/tangible/deed/city_deed/shared_garden_tatooine_sml_04_deed.iff
			defaultTemplateName = "garden_tatooine_sml_04_deed";
		case 0xBA6E39B1: //object/tangible/deed/city_deed/shared_garden_tatooine_sml_05_deed.iff
			defaultTemplateName = "garden_tatooine_sml_05_deed";

		case 0xA90A5290: //object/tangible/deed/city_deed/shared_hospital_corellia_deed.iff
			defaultTemplateName = "corellia_hospital_deed";
		case 0x420134C6: //object/tangible/deed/city_deed/shared_hospital_naboo_deed.iff
			defaultTemplateName = "naboo_hospital_deed";
		case 0x9A789889: //object/tangible/deed/city_deed/shared_hospital_tatooine_deed.iff
			defaultTemplateName = "tatooine_hospital_deed";

		case 0xDB73A277: //object/tangible/deed/city_deed/shared_shuttleport_corellia_deed.iff
			defaultTemplateName = "corellia_shuttleport_deed";
		case 0x523389B5: //object/tangible/deed/city_deed/shared_shuttleport_naboo_deed.iff
			defaultTemplateName = "naboo_shuttleport_deed";
		case 0xE801686E: //object/tangible/deed/city_deed/shared_shuttleport_tatooine_deed.iff
			defaultTemplateName = "tatooine_shuttleport_deed";

		case 0x248F6CEF: //object/tangible/deed/city_deed/shared_theater_corellia_deed.iff
			defaultTemplateName = "corellia_theater_deed";
		case 0xB427B96E: //object/tangible/deed/city_deed/shared_theater_naboo_deed.iff
			defaultTemplateName = "naboo_theater_deed";
		case 0x17FDA6F6: //object/tangible/deed/city_deed/shared_theater_tatooine_deed.iff
			defaultTemplateName = "tatooine_theater_deed";



		case 0x05B95500: //object/tangible/deed/event_perk/shared_atat_static_deed.iff
		case 0x33C26EB5: //object/tangible/deed/event_perk/shared_atst_static_deed.iff
		case 0x403E70E5: //object/tangible/deed/event_perk/shared_banner_style_1_static_deed.iff
		case 0x784B2302: //object/tangible/deed/event_perk/shared_banner_style_2_static_deed.iff
		case 0x1D3EDF24: //object/tangible/deed/event_perk/shared_bantha_static_deed.iff
		case 0xA4698A50: //object/tangible/deed/event_perk/shared_corellia_flag_deed.iff
		case 0x17838AB9: //object/tangible/deed/event_perk/shared_corellian_banner_static_deed.iff
		case 0x7E494DAB: //object/tangible/deed/event_perk/shared_corsec_1x10_honorguard_deed.iff
		case 0x85B9EB7D: //object/tangible/deed/event_perk/shared_corsec_2x10_honorguard_deed.iff
		case 0xD31676CF: //object/tangible/deed/event_perk/shared_corsec_3x10_honorguard_deed.iff
		case 0x7699BB66: //object/tangible/deed/event_perk/shared_corsec_4x10_honorguard_deed.iff
		case 0x27ED8E38: //object/tangible/deed/event_perk/shared_corsec_stage_theater_deed.iff
		case 0x109DA80B: //object/tangible/deed/event_perk/shared_crashed_tie_bomber_theater_deed.iff
		case 0xB938F953: //object/tangible/deed/event_perk/shared_crashed_tie_fighter_theater_deed.iff
		case 0x881BBB9D: //object/tangible/deed/event_perk/shared_crashed_xwing_theater_deed.iff
		case 0xB2AFCEAD: //object/tangible/deed/event_perk/shared_dantooine_flag_deed.iff
		case 0x0CC63752: //object/tangible/deed/event_perk/shared_dathomir_flag_deed.iff
		case 0x48DA4919: //object/tangible/deed/event_perk/shared_destroyed_atat_theater_deed.iff
		case 0xCAAE3D19: //object/tangible/deed/event_perk/shared_endor_flag_deed.iff
		case 0xB8B3773A: //object/tangible/deed/event_perk/shared_fed_dub_1x10_honorguard_deed.iff
		case 0x4343D1EC: //object/tangible/deed/event_perk/shared_fed_dub_2x10_honorguard_deed.iff
		case 0x15EC4C5E: //object/tangible/deed/event_perk/shared_fed_dub_3x10_honorguard_deed.iff
		case 0xB06381F7: //object/tangible/deed/event_perk/shared_fed_dub_4x10_honorguard_deed.iff
		case 0x1C8B36B0: //object/tangible/deed/event_perk/shared_fed_dub_stage_theater_deed.iff
		case 0x94921683: //object/tangible/deed/event_perk/shared_game_flag_deed.iff
		case 0x7B38D77A: //object/tangible/deed/event_perk/shared_imperial_1x10_honorguard_deed.iff
		case 0x80C871AC: //object/tangible/deed/event_perk/shared_imperial_2x10_honorguard_deed.iff
		case 0xD667EC1E: //object/tangible/deed/event_perk/shared_imperial_3x10_honorguard_deed.iff
		case 0x73E821B7: //object/tangible/deed/event_perk/shared_imperial_4x10_honorguard_deed.iff
		case 0x4783EDD8: //object/tangible/deed/event_perk/shared_imperial_banner_static_deed.iff
		case 0x38A6127D: //object/tangible/deed/event_perk/shared_imperial_landing_party_atat_theater_deed.iff
		case 0x4FF6961E: //object/tangible/deed/event_perk/shared_imperial_landing_party_lambda_theater_deed.iff
		case 0xEAFB0D23: //object/tangible/deed/event_perk/shared_imperial_recruiter_deed.iff
		case 0xB5102A73: //object/tangible/deed/event_perk/shared_imperial_recruiting_station_theater_deed.iff
		case 0x57576849: //object/tangible/deed/event_perk/shared_imperial_stage_theater_deed.iff
		case 0x2C1E28B5: //object/tangible/deed/event_perk/shared_lambda_shuttle_static_deed.iff
		case 0x099BD5E5: //object/tangible/deed/event_perk/shared_lok_flag_deed.iff
		case 0x258FA783: //object/tangible/deed/event_perk/shared_lottery_droid_deed.iff
		case 0xD055B38E: //object/tangible/deed/event_perk/shared_marble_gazebo_static_deed.iff
		case 0xD04315A0: //object/tangible/deed/event_perk/shared_naboo_flag_deed.iff
		case 0x70A48C36: //object/tangible/deed/event_perk/shared_naboo_gazebo_static_deed.iff
		case 0xEA628029: //object/tangible/deed/event_perk/shared_npc_actor_deed.iff
		case 0xE6C1AABC: //object/tangible/deed/event_perk/shared_party_stage_theater_deed.iff
		case 0x54864CFF: //object/tangible/deed/event_perk/shared_pavillion_1_static_deed.iff
		case 0x6CF31F18: //object/tangible/deed/event_perk/shared_pavillion_2_static_deed.iff
		case 0x12E04FF7: //object/tangible/deed/event_perk/shared_race_droid_deed.iff
		case 0x8833AD9F: //object/tangible/deed/event_perk/shared_radiologically_shielded_chest_deed.iff
		case 0x66BAD5CF: //object/tangible/deed/event_perk/shared_rebel_1x10_honorguard_deed.iff
		case 0x9D4A7319: //object/tangible/deed/event_perk/shared_rebel_2x10_honorguard_deed.iff
		case 0xCBE5EEAB: //object/tangible/deed/event_perk/shared_rebel_3x10_honorguard_deed.iff
		case 0x6E6A2302: //object/tangible/deed/event_perk/shared_rebel_4x10_honorguard_deed.iff
		case 0xC980100B: //object/tangible/deed/event_perk/shared_rebel_banner_static_deed.iff
		case 0xD55BC6D7: //object/tangible/deed/event_perk/shared_rebel_recruiter_deed.iff
		case 0xF5507DAD: //object/tangible/deed/event_perk/shared_rebel_recruiting_station_theater_deed.iff
		case 0xD954959A: //object/tangible/deed/event_perk/shared_rebel_stage_theater_deed.iff
		case 0x29E8F1BE: //object/tangible/deed/event_perk/shared_rori_flag_deed.iff
		case 0x688D8C10: //object/tangible/deed/event_perk/shared_rsf_1x10_honorguard_deed.iff
		case 0x937D2AC6: //object/tangible/deed/event_perk/shared_rsf_2x10_honorguard_deed.iff
		case 0xC5D2B774: //object/tangible/deed/event_perk/shared_rsf_3x10_honorguard_deed.iff
		case 0x605D7ADD: //object/tangible/deed/event_perk/shared_rsf_4x10_honorguard_deed.iff
		case 0x9E84FCBF: //object/tangible/deed/event_perk/shared_rsf_stage_theater_deed.iff
		case 0x84162F60: //object/tangible/deed/event_perk/shared_scavenger_droid_deed.iff
		case 0x6D599E6C: //object/tangible/deed/event_perk/shared_shuttle_beacon.iff
		case 0x1883DA99: //object/tangible/deed/event_perk/shared_shuttle_static_deed.iff
		case 0xBFCEFA8D: //object/tangible/deed/event_perk/shared_skeleton_chest_deed.iff
		case 0x7AC89E27: //object/tangible/deed/event_perk/shared_sparking_treasure_box_chest_deed.iff
		case 0x2F2A1D79: //object/tangible/deed/event_perk/shared_stone_base_banner_static_deed.iff
		case 0x453FC971: //object/tangible/deed/event_perk/shared_talus_flag_deed.iff
		case 0xCFD9DE1B: //object/tangible/deed/event_perk/shared_tatooine_banner_static_deed.iff
		case 0x5034B851: //object/tangible/deed/event_perk/shared_tatooine_flag_deed.iff
		case 0x9F8BB44E: //object/tangible/deed/event_perk/shared_technical_chest_deed.iff
		case 0xC2624F12: //object/tangible/deed/event_perk/shared_test_gaming_table_deed.iff
		case 0xEEA6E229: //object/tangible/deed/event_perk/shared_test_npc_deed.iff
		case 0xFAD73887: //object/tangible/deed/event_perk/shared_test_theater_deed.iff
		case 0xBF54E31B: //object/tangible/deed/event_perk/shared_tie_bomber_static_deed.iff
		case 0x852B3DCF: //object/tangible/deed/event_perk/shared_tie_fighter_static_deed.iff
		case 0xBCC4851A: //object/tangible/deed/event_perk/shared_treasure_box_chest_deed.iff
		case 0x8BB1F956: //object/tangible/deed/event_perk/shared_treasure_crate_chest_deed.iff
		case 0x5E7304B1: //object/tangible/deed/event_perk/shared_universe_flags_theater.iff
		case 0x2ADEB4AC: //object/tangible/deed/event_perk/shared_wedding_garden_imperial_large_theater_deed.iff
		case 0x735726E6: //object/tangible/deed/event_perk/shared_wedding_garden_rebel_large_theater_deed.iff
		case 0x288A7A87: //object/tangible/deed/event_perk/shared_xwing_static_deed.iff
		case 0x5DB98742: //object/tangible/deed/event_perk/shared_yavin_flag_deed.iff

		case 0xC786298D: //object/tangible/deed/faction_perk/covert_detector/shared_detector_32m_deed.iff
			defaultTemplateName = "covert_detector_32m";
		case 0x87DD72EB: //object/tangible/deed/faction_perk/hq/shared_hq_deed_base.iff

		// Faction Bases won't work for this since the imp/rebel share the CRC
		case 0x3085BEBA: //object/tangible/deed/faction_perk/hq/shared_hq_s01.iff
			defaultTemplateName = "hq_s01_pvp";
		case 0xEB92162D: //object/tangible/deed/faction_perk/hq/shared_hq_s02.iff
			defaultTemplateName = "hq_s02_pvp";
		case 0xA29F71A0: //object/tangible/deed/faction_perk/hq/shared_hq_s03.iff
			defaultTemplateName = "hq_s03_pvp";
		case 0x597C5AB4: //object/tangible/deed/faction_perk/hq/shared_hq_s04.iff
			defaultTemplateName = "hq_s04_pvp";
		case 0x10713D39: //object/tangible/deed/faction_perk/hq/shared_hq_s05.iff
			defaultTemplateName = "hq_s05_pvp";

		case 0xF5092D77: //object/tangible/deed/guild_deed/shared_corellia_guild_deed.iff
			defaultTemplateName = "corellia_guild_deed";
		case 0xC76A6970: //object/tangible/deed/guild_deed/shared_generic_guild_deed.iff
			defaultTemplateName = "generic_guild_deed";
		case 0x8EF75108: //object/tangible/deed/guild_deed/shared_naboo_guild_deed.iff
			defaultTemplateName = "naboo_guild_deed";
		case 0x3287A7A2: //object/tangible/deed/guild_deed/shared_tatooine_guild_deed.iff
		case 0x63F71FE7: //object/tangible/deed/guild_deed/shared_tatooine_guild_style_02_deed.iff
			defaultTemplateName = "tatooine_guild_2_deed";
		case 0x05F7BC15: //object/tangible/deed/corellia/player_house_deed/shared_corellia_house_large_deed.iff
		case 0xAEA2F701: //object/tangible/deed/player_house_deed/shared_corellia_house_large_deed.iff
			defaultTemplateName = "corellia_house_large_deed";
		case 0xF36F169A: //object/tangible/deed/corellia/player_house_deed/shared_corellia_house_medium_deed.iff
		case 0x7C409FF5: //object/tangible/deed/player_house_deed/shared_corellia_house_medium_deed.iff
			defaultTemplateName = "corellia_house_medium_deed";
		case 0x4571BAB6: //object/tangible/deed/corellia/player_house_deed/shared_corellia_house_small_deed.iff
			defaultTemplateName = "corellia_house_small_deed";
		case 0x03CE0D00: //object/tangible/deed/naboo/player_house_deed/shared_naboo_house_large_deed.iff
			defaultTemplateName = "naboo_house_large_deed";
		case 0xD0584E28: //object/tangible/deed/naboo/player_house_deed/shared_naboo_house_medium_deed.iff
			defaultTemplateName = "naboo_house_medium_deed";
		case 0x43480BA3: //object/tangible/deed/naboo/player_house_deed/shared_naboo_house_small_deed.iff
			defaultTemplateName = "naboo_house_small_deed";
		case 0x0E051C75: //object/tangible/deed/player_house_deed/shared_corellia_house_large_style_02_deed.iff
			defaultTemplateName = "corellia_house_large_style_2_deed";
		case 0x9217CAC4: //object/tangible/deed/player_house_deed/shared_corellia_house_medium_style_02_deed.iff
			defaultTemplateName = "";
		case 0xFC820F50: //object/tangible/deed/player_house_deed/shared_corellia_house_small_floor_02_deed.iff
			defaultTemplateName = "corellia_house_small_floor_2";
		case 0x8CD7386A: //object/tangible/deed/player_house_deed/shared_corellia_house_small_style_02_deed.iff
			defaultTemplateName = "corellia_house_small_style_2_deed";
		case 0xBD4E39FA: //object/tangible/deed/player_house_deed/shared_corellia_house_small_style_02_floor_02_deed.iff
			defaultTemplateName = "corellia_house_small_style_2_floor_2_deed";
		case 0x67C936E3: //object/tangible/deed/player_house_deed/shared_generic_house_large_deed.iff
			defaultTemplateName = "generic_house_large_deed";
		case 0xD5D68F6C: //object/tangible/deed/player_house_deed/shared_generic_house_large_style_02_deed.iff
			defaultTemplateName = "generic_house_large_style_2_deed";
		case 0x68C21D63: //object/tangible/deed/player_house_deed/shared_generic_house_medium_deed.iff
			defaultTemplateName = "generic_house_medium_deed";
		case 0x7B54534C: //object/tangible/deed/player_house_deed/shared_generic_house_medium_style_02_deed.iff
			defaultTemplateName = "generic_house_medium_style_2_deed";
		case 0x274F3040: //object/tangible/deed/player_house_deed/shared_generic_house_small_deed.iff
			defaultTemplateName = "generic_house_small_deed";
		case 0x27519C49: //object/tangible/deed/player_house_deed/shared_generic_house_small_floor_02_deed.iff
			defaultTemplateName = "generic_house_small_floor_2_deed";
		case 0x5704AB73: //object/tangible/deed/player_house_deed/shared_generic_house_small_style_02_deed.iff
			defaultTemplateName = "generic_house_small_style_2_deed";
		case 0x721D4D62: //object/tangible/deed/player_house_deed/shared_generic_house_small_style_02_floor_02_deed.iff
			defaultTemplateName = "generic_house_small_style_2_deed";
		case 0xA872D1FD: //object/tangible/deed/player_house_deed/shared_merchant_tent_style_01_deed.iff
			defaultTemplateName = "merchant_tent";
		case 0x2D022CE3: //object/tangible/deed/player_house_deed/shared_merchant_tent_style_02_deed.iff
			defaultTemplateName = "merchant_tent_2";
		case 0xAD928C84: //object/tangible/deed/player_house_deed/shared_merchant_tent_style_03_deed.iff
			defaultTemplateName = "merchant_tent_3";
		case 0x9090CB14: //object/tangible/deed/player_house_deed/shared_naboo_house_large_deed.iff
			defaultTemplateName = "naboo_house_large_deed";
		case 0xA6C0476F: //object/tangible/deed/player_house_deed/shared_naboo_house_medium_deed.iff
			defaultTemplateName = "naboo_house_medium_deed";
		case 0xEE65658A: //object/tangible/deed/player_house_deed/shared_naboo_house_medium_style_02_deed.iff
			defaultTemplateName = "naboo_house_medium_style_2_deed";
		case 0xD016CDB7: //object/tangible/deed/player_house_deed/shared_naboo_house_small_deed.iff
			defaultTemplateName = "naboo_house_small_deed";
		case 0xEF0AAC25: //object/tangible/deed/player_house_deed/shared_naboo_house_small_style_02_deed.iff
			defaultTemplateName = "naboo_house_small_style_2_deed";
		case 0x06FC884E: //object/tangible/deed/player_house_deed/shared_tatooine_house_large_deed.iff
			defaultTemplateName = "tatooine_house_large_deed";
		case 0xF5186B43: //object/tangible/deed/player_house_deed/shared_tatooine_house_medium_deed.iff
			defaultTemplateName = "tatooine_house_medium_deed";
		case 0x467A8EED: //object/tangible/deed/player_house_deed/shared_tatooine_house_small_deed.iff
			defaultTemplateName = "tatooine_house_small_deed";
		case 0x83190387: //object/tangible/deed/player_house_deed/shared_tatooine_house_small_style_02_deed.iff
			defaultTemplateName = "tatooine_house_small_style_2_deed";

		case 0xC43635AD: //object/intangible/pet/shared_pet_deed.iff
		case 0x95396146: //object/tangible/deed/base/shared_pet_deed_base.iff
		case 0xF32F271D: //object/tangible/deed/base/shared_pet_droid_deed_base.iff
		case 0x749E0A9B: //object/tangible/deed/pet_deed/shared_acklay_deed.iff
		case 0x93FC80F4: //object/tangible/deed/pet_deed/shared_angler_deed.iff
		case 0xD86A9900: //object/tangible/deed/pet_deed/shared_bageraset_deed.iff
		case 0x8D03DF17: //object/tangible/deed/pet_deed/shared_bantha_deed.iff
		case 0x04A7C039: //object/tangible/deed/pet_deed/shared_bearded_jax_deed.iff
		case 0xAF7FAE10: //object/tangible/deed/pet_deed/shared_blurrg_deed.iff
		case 0x2DED5FBD: //object/tangible/deed/pet_deed/shared_boar_wolf_deed.iff
		case 0x6A99DACF: //object/tangible/deed/pet_deed/shared_bocatt_deed.iff
		case 0xC5D4BDC1: //object/tangible/deed/pet_deed/shared_bol_deed.iff
		case 0x15369B33: //object/tangible/deed/pet_deed/shared_bolle_bol_deed.iff
		case 0xC451B9A3: //object/tangible/deed/pet_deed/shared_bolma_deed.iff
		case 0xE578C3E3: //object/tangible/deed/pet_deed/shared_bordok_deed.iff
		case 0xA24D2535: //object/tangible/deed/pet_deed/shared_brackaset_deed.iff
		case 0x5BC95CEA: //object/tangible/deed/pet_deed/shared_carrion_spat_deed.iff
		case 0x21E9B12D: //object/tangible/deed/pet_deed/shared_choku_deed.iff
		case 0x51D181A5: //object/tangible/deed/pet_deed/shared_cu_pa_deed.iff
		case 0xE93A50EA: //object/tangible/deed/pet_deed/shared_dalyrake_deed.iff
		case 0xC94C451F: //object/tangible/deed/pet_deed/shared_deed_3p0_advanced_basic.iff
		case 0x545EAD59: //object/tangible/deed/pet_deed/shared_deed_3p0_basic.iff
		case 0x7AA7823A: //object/tangible/deed/pet_deed/shared_deed_binary_load_lifter_advanced_basic.iff
		case 0x9B0C67E0: //object/tangible/deed/pet_deed/shared_deed_binary_load_lifter_basic.iff
		case 0xC0232FA2: //object/tangible/deed/pet_deed/shared_deed_droid_basic_base.iff
		case 0x22B44412: //object/tangible/deed/pet_deed/shared_deed_dz70_advanced_basic.iff
		case 0xBCD36E9C: //object/tangible/deed/pet_deed/shared_deed_dz70_basic.iff
		case 0x6DF29B8B: //object/tangible/deed/pet_deed/shared_deed_le_repair_advanced_basic.iff
		case 0x349C76F5: //object/tangible/deed/pet_deed/shared_deed_le_repair_basic.iff
		case 0xB862BB26: //object/tangible/deed/pet_deed/shared_deed_mse_advanced_basic.iff
		case 0x2A5A169A: //object/tangible/deed/pet_deed/shared_deed_mse_basic.iff
		case 0xEA8B55C8: //object/tangible/deed/pet_deed/shared_deed_power_advanced_basic.iff
		case 0xD18CDC06: //object/tangible/deed/pet_deed/shared_deed_power_basic.iff
		case 0x8A0F6B70: //object/tangible/deed/pet_deed/shared_deed_probot_advanced_basic.iff
		case 0xCC804878: //object/tangible/deed/pet_deed/shared_deed_probot_basic.iff
		case 0x53BEDD07: //object/tangible/deed/pet_deed/shared_deed_r2_advanced_basic.iff
		case 0xBB142A16: //object/tangible/deed/pet_deed/shared_deed_r2_basic.iff
		case 0x67BC52D1: //object/tangible/deed/pet_deed/shared_deed_r3_advanced_basic.iff
		case 0x42B8ADF8: //object/tangible/deed/pet_deed/shared_deed_r3_basic.iff
		case 0xEBB1FDF3: //object/tangible/deed/pet_deed/shared_deed_r4_advanced_basic.iff
		case 0xA77D011C: //object/tangible/deed/pet_deed/shared_deed_r4_basic.iff
		case 0xDFB37225: //object/tangible/deed/pet_deed/shared_deed_r5_advanced_basic.iff
		case 0x5ED186F2: //object/tangible/deed/pet_deed/shared_deed_r5_basic.iff
		case 0x6C66E751: //object/tangible/deed/pet_deed/shared_deed_surgical_advanced_basic.iff
		case 0xBE7D5CA6: //object/tangible/deed/pet_deed/shared_deed_surgical_basic.iff
		case 0x21638809: //object/tangible/deed/pet_deed/shared_deed_treadwell_advanced_basic.iff
		case 0x33CAC5DF: //object/tangible/deed/pet_deed/shared_deed_treadwell_basic.iff
		case 0x47987944: //object/tangible/deed/pet_deed/shared_dewback_deed.iff
		case 0x49A5A230: //object/tangible/deed/pet_deed/shared_dune_lizard_deed.iff
		case 0x21DD117D: //object/tangible/deed/pet_deed/shared_durni_deed.iff
		case 0xA864EB88: //object/tangible/deed/pet_deed/shared_eopie_deed.iff
		case 0x582AC810: //object/tangible/deed/pet_deed/shared_falumpaset_deed.iff
		case 0x8C850951: //object/tangible/deed/pet_deed/shared_fambaa_deed.iff
		case 0x4834D34F: //object/tangible/deed/pet_deed/shared_gnort_deed.iff
		case 0xF88FED19: //object/tangible/deed/pet_deed/shared_graul_deed.iff
		case 0x1252BAB6: //object/tangible/deed/pet_deed/shared_gronda_deed.iff
		case 0xD2EF4BBB: //object/tangible/deed/pet_deed/shared_gualama_deed.iff
		case 0x9B3B352F: //object/tangible/deed/pet_deed/shared_guf_drolg_deed.iff
		case 0x6DC3ADDA: //object/tangible/deed/pet_deed/shared_gurnaset_deed.iff
		case 0x72170C76: //object/tangible/deed/pet_deed/shared_gurrcat_deed.iff
		case 0x238A8DC9: //object/tangible/deed/pet_deed/shared_gurreck_deed.iff
		case 0xF6E1DA86: //object/tangible/deed/pet_deed/shared_hermit_spider_deed.iff
		case 0xA49BAC55: //object/tangible/deed/pet_deed/shared_huf_dun_deed.iff
		case 0x8CECBE1F: //object/tangible/deed/pet_deed/shared_huurton_deed.iff
		case 0xE9C49B02: //object/tangible/deed/pet_deed/shared_ikopi_deed.iff
		case 0xBD73DBD6: //object/tangible/deed/pet_deed/shared_kaadu_deed.iff
		case 0x58C24ED4: //object/tangible/deed/pet_deed/shared_kahmurra_deed.iff
		case 0x4C79BF55: //object/tangible/deed/pet_deed/shared_kima_deed.iff
		case 0x4C6F8ECD: //object/tangible/deed/pet_deed/shared_kimogila_deed.iff
		case 0xAEAC115A: //object/tangible/deed/pet_deed/shared_kliknik_deed.iff
		case 0x907440FC: //object/tangible/deed/pet_deed/shared_krahbu_deed.iff
		case 0xF0175405: //object/tangible/deed/pet_deed/shared_kusak_deed.iff
		case 0x0761F04A: //object/tangible/deed/pet_deed/shared_kwi_deed.iff
		case 0xD409C1C0: //object/tangible/deed/pet_deed/shared_langlatch_deed.iff
		case 0x417BE717: //object/tangible/deed/pet_deed/shared_malkloc_deed.iff
		case 0x85B4B1CD: //object/tangible/deed/pet_deed/shared_mawgax_deed.iff
		case 0x3E2AF509: //object/tangible/deed/pet_deed/shared_merek_deed.iff
		case 0x0A4EE0AA: //object/tangible/deed/pet_deed/shared_mott_deed.iff
		case 0xE75CA0DC: //object/tangible/deed/pet_deed/shared_narglatch_deed.iff
		case 0x3D2C46A7: //object/tangible/deed/pet_deed/shared_piket_deed.iff
		case 0x8533487A: //object/tangible/deed/pet_deed/shared_pugoriss_deed.iff
		case 0x4B296DA4: //object/tangible/deed/pet_deed/shared_rancor_deed.iff
		case 0x6FA340A2: //object/tangible/deed/pet_deed/shared_roba_deed.iff
		case 0x366D5CCA: //object/tangible/deed/pet_deed/shared_ronto_deed.iff
		case 0x4597D75D: //object/tangible/deed/pet_deed/shared_sand_panther_deed.iff
		case 0x0FE6FD79: //object/tangible/deed/pet_deed/shared_sharnaff_deed.iff
		case 0xDC414060: //object/tangible/deed/pet_deed/shared_shear_mite_deed.iff
		case 0xB5147BE1: //object/tangible/deed/pet_deed/shared_slice_hound_deed.iff
		case 0x77F39352: //object/tangible/deed/pet_deed/shared_snorbal_deed.iff
		case 0x1DA7FBFB: //object/tangible/deed/pet_deed/shared_squall_deed.iff
		case 0x586E8A62: //object/tangible/deed/pet_deed/shared_swirl_prong_deed.iff
		case 0xECFCE50A: //object/tangible/deed/pet_deed/shared_thune_deed.iff
		case 0x37D704A7: //object/tangible/deed/pet_deed/shared_torton_deed.iff
		case 0x1EDA4A80: //object/tangible/deed/pet_deed/shared_tybis_deed.iff
		case 0xA7ECCAD6: //object/tangible/deed/pet_deed/shared_veermok_deed.iff
		case 0xEC98662A: //object/tangible/deed/pet_deed/shared_vehicular_prototype.iff
		case 0x438DCA93: //object/tangible/deed/pet_deed/shared_vehicular_prototype_bike.iff
		case 0x68C0197F: //object/tangible/deed/pet_deed/shared_verne_deed.iff
		case 0x0492EF4F: //object/tangible/deed/pet_deed/shared_vesp_deed.iff
		case 0x90BF186D: //object/tangible/deed/pet_deed/shared_vir_vur_deed.iff
		case 0x92D66FA0: //object/tangible/deed/pet_deed/shared_woolamander_deed.iff
		case 0x4610E570: //object/tangible/deed/pet_deed/shared_zucca_boar_deed.iff


		case 0x0BADF2FA: //object/tangible/ship/crafted/chassis/shared_awing_deed.iff
		case 0xE8F85768: //object/tangible/ship/crafted/chassis/shared_base_deed.iff
		case 0x78924BED: //object/tangible/ship/crafted/chassis/shared_blacksun_heavy_s01_deed.iff
		case 0xFDE2B6F3: //object/tangible/ship/crafted/chassis/shared_blacksun_heavy_s02_deed.iff
		case 0x7D721694: //object/tangible/ship/crafted/chassis/shared_blacksun_heavy_s03_deed.iff
		case 0xF3C25178: //object/tangible/ship/crafted/chassis/shared_blacksun_heavy_s04_deed.iff
		case 0xCA56EAD0: //object/tangible/ship/crafted/chassis/shared_blacksun_light_s01_deed.iff
		case 0x4F2617CE: //object/tangible/ship/crafted/chassis/shared_blacksun_light_s02_deed.iff
		case 0xCFB6B7A9: //object/tangible/ship/crafted/chassis/shared_blacksun_light_s03_deed.iff
		case 0x4106F045: //object/tangible/ship/crafted/chassis/shared_blacksun_light_s04_deed.iff
		case 0x458B410C: //object/tangible/ship/crafted/chassis/shared_blacksun_medium_s01_deed.iff
		case 0xC0FBBC12: //object/tangible/ship/crafted/chassis/shared_blacksun_medium_s02_deed.iff
		case 0x406B1C75: //object/tangible/ship/crafted/chassis/shared_blacksun_medium_s03_deed.iff
		case 0xCEDB5B99: //object/tangible/ship/crafted/chassis/shared_blacksun_medium_s04_deed.iff
		case 0xC3B5A1B9: //object/tangible/ship/crafted/chassis/shared_bwing_deed.iff
		case 0xEE5F28E8: //object/tangible/ship/crafted/chassis/shared_decimator_deed.iff
		case 0x821838BB: //object/tangible/ship/crafted/chassis/shared_firespray_deed.iff
		case 0xB425025B: //object/tangible/ship/crafted/chassis/shared_hutt_heavy_s01_deed.iff
		case 0x3155FF45: //object/tangible/ship/crafted/chassis/shared_hutt_heavy_s02_deed.iff
		case 0x06E1A366: //object/tangible/ship/crafted/chassis/shared_hutt_light_s01_deed.iff
		case 0x83915E78: //object/tangible/ship/crafted/chassis/shared_hutt_light_s02_deed.iff
		case 0x9A44FCF1: //object/tangible/ship/crafted/chassis/shared_hutt_medium_s01_deed.iff
		case 0x1F3401EF: //object/tangible/ship/crafted/chassis/shared_hutt_medium_s02_deed.iff
		case 0xA7F00335: //object/tangible/ship/crafted/chassis/shared_hutt_turret_ship_deed.iff
		case 0xA1142B2E: //object/tangible/ship/crafted/chassis/shared_tie_in_deed.iff
		case 0xEB101486: //object/tangible/ship/crafted/chassis/shared_tie_light_duty_deed.iff
		case 0x1FE78C32: //object/tangible/ship/crafted/chassis/shared_tieadvanced_deed.iff
		case 0x2C096954: //object/tangible/ship/crafted/chassis/shared_tieaggressor_deed.iff
		case 0x7FDD130B: //object/tangible/ship/crafted/chassis/shared_tiebomber_deed.iff
		case 0x56D3FEF8: //object/tangible/ship/crafted/chassis/shared_tiefighter_deed.iff
		case 0xCBA71C8A: //object/tangible/ship/crafted/chassis/shared_tieinterceptor_deed.iff
		case 0x1C14145B: //object/tangible/ship/crafted/chassis/shared_tieoppressor_deed.iff
		case 0x161EEB91: //object/tangible/ship/crafted/chassis/shared_xwing_deed.iff
		case 0x316AB9FC: //object/tangible/ship/crafted/chassis/shared_ykl37r_deed.iff
		case 0x9C7377A2: //object/tangible/ship/crafted/chassis/shared_yt1300_deed.iff
		case 0x51E92550: //object/tangible/ship/crafted/chassis/shared_ywing_deed.iff
		case 0xB475EC2B: //object/tangible/ship/crafted/chassis/shared_ywing_longprobe_deed.iff
		case 0x291AF89C: //object/tangible/ship/crafted/chassis/shared_z95_deed.iff
		case 0x87E877A4: //object/tangible/space/veteran_reward/shared_sorosuub_space_yacht_deed.iff
		default:
			defaultTemplateName = ""; // hmm

	}

	return defaultTemplateName;
}
