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

#ifndef AUCTIONQUERYHEADERSRESPONSEMESSAGE_H_
#define AUCTIONQUERYHEADERSRESPONSEMESSAGE_H_

#include "engine/engine.h"

#include "../../objects/auction/AuctionItem.h"

class AuctionQueryHeadersResponseMessage : public BaseMessage {
	Vector<AuctionItem*> itemList;
	
	Vector<string> locationList;
	
public:
	AuctionQueryHeadersResponseMessage(int screen, int counter) : BaseMessage() {	
		insertShort(0x08);
		insertInt(0xFA500E52);  // opcode
		
		insertInt(counter);
		insertInt(screen); // Vendor screen number
	}
	
	void addAuctionItem(uint64 id, string& name, int price, bool auction, int time, int type,
			int ownerid, string& owner, bool vendor, string& planet, string& header, long long vendorid, int x, int z) {

		AuctionItem* ai = new AuctionItem();
		
		ai->id = id;
		ai->itemName = name;
		ai->price = price;
		ai->remainingTime = time;
		ai->auction = auction;
		ai->itemType = type;
		ai->ownerName = owner;
		
		ai->setLocation(planet, header, vendorid, x, z, vendor);
		
		addItemToList(ai);
	}
	
	void addItemToList(AuctionItem* ai) {
		ai->locationPointer = -1;
		
		for (int i = 0; i < locationList.size(); i++) {
			if (locationList.get(i) == ai->terminalTitle)
				ai->locationPointer = i;
		}
		
		if (ai->locationPointer == -1) {
			ai->locationPointer = locationList.size();
			
			locationList.add(locationList.size(), ai->terminalTitle);
		}
		
		ai->ownerPointer = -1;
		
		for (int i = 0; i < locationList.size(); i++) {
			if (locationList.get(i) == ai->ownerName)
				ai->ownerPointer = i;
		}
		
		if (ai->ownerPointer == -1) {
			ai->ownerPointer = locationList.size();
			
			locationList.add(locationList.size(), ai->ownerName);
		}
		
		itemList.add(ai);
	}
	
	void dumpLocationList() {
		int llSize = locationList.size();
		
		insertInt(llSize);
		
		for (int i = 0; i < locationList.size(); i++) {
			insertAscii(locationList.get(i));
		}
	}
	
	void dumpItemNameList() {
		int ilSize = itemList.size();
		
		insertInt(ilSize);

		for (int i = 0; i < itemList.size(); i++) {
			AuctionItem* il = itemList.get(i);
			
	    	unicode name = il->itemName;
	    	insertUnicode(name); //name
		}
	}
	
	void dumpItemInfoList() {
		int ilSize = itemList.size();
		
		insertInt(ilSize);

		for (int i = 0; i < itemList.size(); i++) {
			AuctionItem* il = itemList.get(i);
	    	
			insertLong(il->id); //item id
			insertByte(i);  // List item string number
	    	
			insertInt(il->price); //item cost.
	    	
			Time* expireTime = new Time();
			uint32 expire = il->expireTime - expireTime->getMiliTime() / 1000;

			insertInt(expire);
	    	
	    	if (il->auction)
	    		insertByte(0);
	    	else
	    		insertByte(1);
	    	
	    	insertShort(il->locationPointer);
	    	
	    	insertLong(il->ownerID); // seller ID
	    	insertShort(il->ownerPointer);

	    	insertLong(il->buyerID); // buyer ID
	    	
	    	insertInt(0); 
	    	insertInt(0);
	    	insertShort(0);

	    	insertInt(il->itemType); 
	    	
	    	insertInt(0);
	    	insertInt(0);
		}
	}
	
	void createMessage(int offset = 0, bool continues = false) {
		dumpLocationList();

		dumpItemNameList();
		
		dumpItemInfoList();
		
		insertShort(offset); // Item list start offset
		
		insertByte(continues); // more to come?
	}

	inline int getListSize() {
		return itemList.size();
	}

};

#endif /*AUCTIONQUERYHEADERSRESPONSEMESSAGE_H_*/
