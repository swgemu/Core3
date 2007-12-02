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

#include "AuctionItem.h"

class AuctionQueryHeadersResponseMessage : public Message {
	Vector<AuctionItem*> itemList;
public:
   AuctionQueryHeadersResponseMessage(const string& vendorinfo, const string& vendorowner) : Message() {
		insertShort(0x08);
		insertInt(0xFA500E52);  // opcode
		
		insertInt(0); //??
		insertInt(0); //??
		insertInt(0); //??
		insertAscii(vendorinfo);
		insertAscii(vendorowner);
		insertShort(0); //??
		
		//insertInt(0); //Item List Count Names
		//insertUnicode("test"); //unicode item name
		
		//insertInt(0); //Item List Count Info
		//insertLong(0); //Item ID
		//insertByte(0); //??
		//insertInt(0); //Item Cost
				
	}

	void addAuctionItem(uint64 id, unicode name, int price) {
		AuctionItem* ai = new AuctionItem();
		ai->id = id;
		ai->itemname = name;
		ai->price = price;
		itemList.add(ai);
	}
	
	void dumpItemNameList() {
		int ilSize = itemList.size();
		insertInt(ilSize);

		for (int i = 0; i < itemList.size(); i++) {
			AuctionItem* il = itemList.get(i);
	    	insertUnicode(il->itemname); //name
		}
	}
	
	void dumpItemInfoList() {
		int ilSize = itemList.size();
		insertInt(ilSize);

		for (int i = 0; i < itemList.size(); i++) {
			AuctionItem* il = itemList.get(i);
	    	insertLong(il->id); //item id
	    	insertByte(0); //??
	    	insertInt(il->price); //item cost.
		}
	}
	
	inline int getListSize() {
		return itemList.size();
	}
};
#endif /*AUCTIONQUERYHEADERSRESPONSEMESSAGE_H_*/
