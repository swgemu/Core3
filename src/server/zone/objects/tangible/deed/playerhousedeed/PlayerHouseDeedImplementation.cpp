#include "../../../player/Player.h"
#include "../../../../packets.h"

#include "PlayerHouseDeed.h"
#include "PlayerHouseDeedImplementation.h"
#include "../DeedObject.h"
#include "../DeedObjectImplementation.h"

PlayerHouseDeedImplementation::PlayerHouseDeedImplementation(CreatureObject* creature, uint32 tempcrc, const UnicodeString& n, const String& tempn)
	: PlayerHouseDeedServant(creature->getNewItemID(), tempcrc, n, tempn, BUILDINGDEED) {
	objectCRC = tempcrc;
	name = n;
	templateName = tempn;

	init();
}

PlayerHouseDeedImplementation::PlayerHouseDeedImplementation(uint64 objid, uint32 tempcrc, const UnicodeString& n, const String& tempn)
	: PlayerHouseDeedServant(objid, tempcrc, n, tempn, BUILDINGDEED) {
	objectID = objid;
	objectCRC = tempcrc;
	name = n;
	templateName = tempn;

	init();
}

PlayerHouseDeedImplementation::~PlayerHouseDeedImplementation() {

}

void PlayerHouseDeedImplementation::init() {
	objectSubType = TangibleObjectImplementation::BUILDINGDEED;

	//if (templateName == "corellia_house_large_deed"){
		targetTemplate = "naboo_house_medium";
		targetName = UnicodeString("Medium Naboo House");
		targetTempFile = "object/building/player/construction/shared_construction_player_house_naboo_medium_style_01.iff";
		targetFile = "object/building/player/shared_player_house_naboo_medium_style_01.iff";
		cellCount = 7;
	//}
}
