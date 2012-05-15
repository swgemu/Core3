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
#include "server/zone/objects/auction/Vendor.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/terminal/vendor/VendorTerminal.h"
#include "server/zone/objects/creature/vendor/VendorCreature.h"

class IsVendorOwnerResponseMessage : public BaseMessage {
public:
    IsVendorOwnerResponseMessage(SceneObject* sceno, CreatureObject* player, const String& planet, const String& header, uint32 errorCode = 0) {
		insertShort(3);
		insertInt(0xCE04173E);

		// Make sure sceno is a valid Vendor Object.
		if (!sceno->isVendor())
			return;

		// And now we figure out what Vendor Class
		Vendor* vendor = NULL;
		String vendorName = "unknown";

		if (sceno->isTerminal()) {
			Terminal* term = cast<Terminal*>( sceno);
			if (term->isVendorTerminal()) {
				VendorTerminal* terminal = cast<VendorTerminal*>( term);
				vendor = terminal->getVendor();
				if (!terminal->getCustomObjectName().isEmpty())
					vendorName = terminal->getCustomObjectName().toString();
			}

		} else if (sceno->isCreatureObject()) {
			CreatureObject* cero = cast<CreatureObject*>( sceno);
			if (!cero->isVendorCreature())
				return;

			VendorCreature* vendorCreature = cast<VendorCreature*>( sceno);
			vendor = vendorCreature->getVendor();
			if (!vendorCreature->getCustomObjectName().isEmpty())
				vendorName = vendorCreature->getCustomObjectName().toString();

		} else
			return;

		if (vendor == NULL)
			return;

		uint64 objectID = sceno->getObjectID();

		// 0: own vendor, 1: someone else owns the vendor, 2: the galaxy owns the vendor (bazaar)
		insertInt(vendor->getOwnershipRightsOf(player));

		insertInt(errorCode);
		
		insertLong(objectID);

		StringBuffer title;
		title << planet << ".";
		
		int x = sceno->getWorldPositionX();
		int y = sceno->getWorldPositionY();

		if (!vendor->isBazaarTerminal())
			title << "@planet_n:" << planet <<  ".Vendor: " << vendorName; // VendorName
		else
			title << header << "." << sceno->getDisplayedName();
		
		title << "." << objectID << "#" << x << "," << y;
		
		insertAscii(title.toString());
		
		insertShort(0x64); // ?? 64
	}
};

#endif /*ISVENDOROWNERRESPONSEMESSAGE_H_*/
