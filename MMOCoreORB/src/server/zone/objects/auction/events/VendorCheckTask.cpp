/*
 Copyright (C) 2007 <SWGEmu>

 This File is part of Core3.

 This program is free software; you can redistribute
 it and/or modify it under the terms of the GNU Lesser
 General Public License as published by the Free Software
 Foundation; either version 3 of the License,
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

#include "VendorCheckTask.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/creature/vendor/VendorCreature.h"
#include "server/zone/objects/tangible/terminal/vendor/VendorTerminal.h"
#include "server/zone/objects/auction/Vendor.h"

void VendorCheckTask::run() {
	if (!vendorObj->isVendor() || vendorObj == NULL)
			return;

		Vendor* vendor = NULL;

		if (vendorObj->isTerminal()) {
			VendorTerminal* terminal = dynamic_cast<VendorTerminal*>(vendorObj.get());

			if (terminal == NULL)
				return;

			vendor = terminal->getVendor();
		} else if (vendorObj->isCreatureObject()) {
			VendorCreature* vendorCreature = dynamic_cast<VendorCreature*>(vendorObj.get());

			if (vendorCreature == NULL)
				return;

			vendor = vendorCreature->getVendor();
		}

		if (vendor == NULL)
			return;

		if (vendor->isBazaarTerminal())
			return;

		int itemCount = vendor->getVendorItemCount();
		int itemWarningLevel = vendor->getItemWarningLevel();

		Locker vendorLocker(vendorObj);

		if (itemCount > 0) {
			vendor->setItemWarningLevel(0);
			return;
		}

		vendor->setItemWarningLevel(itemWarningLevel + 1);

		if (itemWarningLevel == 0x02) {
			vendor->sendVendorDestroyMail();
			vendorObj->removeFromZone();
			vendorObj->destroyObjectFromDatabase(true);
			return;
		}

		vendor->sendVendorUpdateMail(true);

		if (this->isScheduled())
			this->reschedule(((Vendor::CHECKINTERVAL * 60000) * 60) * 24);
		else
			this->schedule(((Vendor::CHECKINTERVAL * 60000) * 60) * 24);

		vendor->setNextCheckTime(this->getNextExecutionTime());

}
