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

#ifndef ISVENDOROWNERRESPONSEMESSAGE_H_
#define ISVENDOROWNERRESPONSEMESSAGE_H_

#include "engine/engine.h"

#include "../BaseLineMessage.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"

class IsVendorOwnerResponseMessage : public BaseMessage {
public:
    IsVendorOwnerResponseMessage(SceneObject* vendor, CreatureObject* player, const String& planet, const String& region, uint32 errorCode = 0) {
		insertShort(3);
		insertInt(0xCE04173E);

		// Make sure sceno is a valid Vendor Object.
		if (!vendor->isVendor() && !vendor->isBazaarTerminal())
			return;

		int rights = 2;

		if(vendor->isVendor()) {


			DataObjectComponentReference* data = vendor->getDataObjectComponent();
			if(data == NULL || data->get() == NULL || !data->get()->isVendorData()) {
				return;
			}

			VendorDataComponent* vendorData = cast<VendorDataComponent*>(data->get());
			if(vendorData == NULL) {
				return;
			}

			rights = vendorData->getOwnershipRightsOf(player);
		}

		uint64 objectID = vendor->getObjectID();

		// 0: own vendor, 1: someone else owns the vendor, 2: the galaxy owns the vendor (bazaar)
		insertInt(rights);

		insertInt(errorCode);
		
		insertLong(objectID);

		StringBuffer title;
		title << planet << ".";
		
		int x = vendor->getWorldPositionX();
		int y = vendor->getWorldPositionY();

		Reference<AuctionManager*> auctionManager = player->getZoneServer()->getAuctionManager();
		String uuid = auctionManager->getVendorUID(vendor);

		insertAscii(uuid);
		
		insertShort(0x64); // ?? 64
	}
};

#endif /*ISVENDOROWNERRESPONSEMESSAGE_H_*/
