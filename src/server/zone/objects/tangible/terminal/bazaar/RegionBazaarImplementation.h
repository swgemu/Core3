
#ifndef REGIONBAZAARIMPLEMENTATION_H_
#define REGIONBAZAARIMPLEMENTATION_H_

#include "engine/engine.h"

#include "RegionBazaar.h"

#include "../../../player/Player.h"

#include "../../../../objects/auction/AuctionItem.h"
#include "../../../../packets/auction/IsVendorOwnerResponseMessage.h"
#include "../../../../packets/auction/BazaarDisplayUI.h"
#include "../../../../packets/auction/AuctionQueryHeadersResponseMessage.h"

#include "../../../../objects/terrain/PlanetNames.h"

class RegionBazaarImplementation : public RegionBazaarServant {
	Vector<AuctionItem*> items;
	string bazaarRegion;
	BazaarPlanetManager* planetManager;
	
public:
	RegionBazaarImplementation() : RegionBazaarServant() {
	
	}
	
	inline void addItem(AuctionItem* item) {
		items.add(item);
	}
	
	void setRegion(string& region) {
		bazaarRegion = region;
	}
	
	void setManager(BazaarPlanetManager* manager) {
		planetManager = manager;
	}
	
	void getBazaarData(Player* player, long objectid, int screen, int extent, int category, int count) {

		AuctionQueryHeadersResponseMessage* reply = new AuctionQueryHeadersResponseMessage(screen, count);

		if (screen == 2) {
			for(int i = 0; i < items.size(); i++) {
				reply->addItemToList(items.get(i));
			}
		} else if (screen == 3) {
			for(int i = 0; i < items.size(); i++) {
				if (items.get(i)->ownerID == player->getCharacterID())
					reply->addItemToList(items.get(i));
			}
		}
		
		reply->createMessage();
		
		player->sendMessage(reply);
	}
	
	void newBazaarRequest(long bazaarID, Player* player, int planet) {
		BazaarTerminalDetails* location;
		
		string planetString = PlanetNames[planet];

		IsVendorOwnerResponseMessage* msg = new IsVendorOwnerResponseMessage(false, bazaarID, planetString, bazaarRegion, 0, 0);
		player->sendMessage(msg);
		
		BazaarDisplayUI* msg2 = new BazaarDisplayUI(false, bazaarID, player);
		player->sendMessage(msg2);
	}


};

#endif /*REGIONBAZAARIMPLEMENTATION_H_*/
