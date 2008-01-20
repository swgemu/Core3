/*
Copyright (C) 2007 <SWGEmu>
 
This File is part of Core3.
 
This program is free software; you can redistribute 
it and/or modify it under the terms of the GNU Lesser 
General Public License as published by the Free Software
Foundation; either version 2 of the License, 
or (at your option) any later version.
 
This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU Lesser General Public License for
more details.
 
You should have received a copy of the GNU Lesser General 
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 
Linking Engine3 statically or dynamically with other modules 
is making a combined work based on Engine3. 
Thus, the terms and conditions of the GNU Lesser General Public License 
cover the whole combination.
 
In addition, as a special exception, the copyright holders of Engine3 
give you permission to combine Engine3 program with free software 
programs or libraries that are released under the GNU LGPL and with 
code included in the standard release of Core3 under the GNU LGPL 
license (or modified versions of such code, with unchanged license). 
You may copy and distribute such a system following the terms of the 
GNU LGPL for Engine3 and the licenses of the other code concerned, 
provided that you include the source code of that other code when 
and as the GNU LGPL requires distribution of source code.
 
Note that people who make modified versions of Engine3 are not obligated 
to grant this special exception for their modified versions; 
it is their choice whether to do so. The GNU Lesser General Public License 
gives permission to release a modified version without this exception; 
this exception also makes it possible to release a modified version 
which carries forward this exception.
*/

#ifndef AUCTIONCONTROLLER_H_
#define AUCTIONCONTROLLER_H_

#include "engine/engine.h"

#include "AuctionItem.h"

#include "../../packets/auction/AuctionQueryHeadersResponseMessage.h"
#include "../../objects/player/Player.h"

class AuctionController {

public:
	VectorMap<uint64, AuctionItem*> items;

	AuctionController() {
		
	}
	
	inline void addItem(AuctionItem* item) {
		items.put(item->id, item);
	}
	
	inline void removeItem(long long objectid) {
		if (items.contains(objectid))
			items.drop(objectid);
	}
	
	inline AuctionItem* getItem(long long objectid) {
		if (items.contains(objectid)) {
			int index = items.find(objectid);
			return items.get(index);
		}
		else
			return NULL;
	}
	
	void getBazaarData(Player* player, long long objectid, int screen, int extent, unsigned int category, int count, int offset) {

		AuctionQueryHeadersResponseMessage* reply = new AuctionQueryHeadersResponseMessage(screen, count);

		int displaying = 0;
		if (screen == 2) {
			
			for (int i = 0; (i < items.size()) && (displaying < (offset + 100)); i++) {
				AuctionItem* item = items.get(i);
				
				if (!item->sold)
					if (item->itemType & category) {
						if (displaying >= offset)
							reply->addItemToList(items.get(i));
						displaying++;
					} else if ((category == 8192) && (item->itemType < 256)) {
						if (displaying >= offset)
							reply->addItemToList(items.get(i));
						displaying++;
					}				
			}
			
		} else if (screen == 3) {
			
			for (int i = 0; i < items.size(); i++) {
				if ((items.get(i)->ownerID == player->getCharacterID()) && !items.get(i)->sold)
					reply->addItemToList(items.get(i));
			}
			
		} else if (screen == 5) {

			for (int i = 0; i < items.size(); i++) {
				if ((items.get(i)->ownerID == player->getCharacterID()) && items.get(i)->sold)
					reply->addItemToList(items.get(i));
			}
			
		}
		
		if(displaying == (offset + 100))
			reply->createMessage(offset, true);
		else
			reply->createMessage(offset);
		
		player->sendMessage(reply);
	}
};

#endif /*AUCTIONCONTROLLER_H_*/
