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

#ifndef BAZAARTERMINALS_H_
#define BAZAARTERMINALS_H_

#include "engine/engine.h"

#include "BazaarTerminalDetails.h"

class BazaarTerminals {
	BazaarMap* bazaarLocations;

public:
	BazaarTerminals() {
		bazaarLocations = new BazaarMap(200);

		// Tatooine Anchorhead
		string location = "anchorhead";
		bazaarLocations->put(3945353, new BazaarTerminalDetails(8, location, 60, -5350));
		bazaarLocations->put(3945352, new BazaarTerminalDetails(8, location, 64, -5350));

		// Tattoine Bestine
		location = "bestine";
		bazaarLocations->put(5515502, new BazaarTerminalDetails(8, location, -1252, -3659));
		bazaarLocations->put(4235514, new BazaarTerminalDetails(8, location, -1290, -3578));
		bazaarLocations->put(3945361, new BazaarTerminalDetails(8, location, -1452, -3580));
		bazaarLocations->put(3945360, new BazaarTerminalDetails(8, location, -1452, -3577));
		bazaarLocations->put(3945359, new BazaarTerminalDetails(8, location, -1447, -3551));
		bazaarLocations->put(3945356, new BazaarTerminalDetails(8, location, -1447, -3548));
		bazaarLocations->put(5515501, new BazaarTerminalDetails(8, location, -1294, -3669));
		bazaarLocations->put(4235511, new BazaarTerminalDetails(8, location, -1293, -3601));
		bazaarLocations->put(683510, new BazaarTerminalDetails(8, location, -1103, -3532));
		bazaarLocations->put(683509, new BazaarTerminalDetails(8, location, -1105, -3535));
		bazaarLocations->put(683508, new BazaarTerminalDetails(8, location, -1107, -3537));
		bazaarLocations->put(683457, new BazaarTerminalDetails(8, location, -1392, -3716));
		bazaarLocations->put(683458, new BazaarTerminalDetails(8, location, -1393, -3707));
		bazaarLocations->put(683459, new BazaarTerminalDetails(8, location, -1398, -3707));
		bazaarLocations->put(683456, new BazaarTerminalDetails(8, location, -1396, -3717));
		bazaarLocations->put(1250246, new BazaarTerminalDetails(8, location, -1105, -3692));
		bazaarLocations->put(1250243, new BazaarTerminalDetails(8, location, -1124, -3676));

		// Corellia Coronet
		location = "coronet";
		bazaarLocations->put(7755375, new BazaarTerminalDetails(0, location, -312, -4644));
		bazaarLocations->put(7755372, new BazaarTerminalDetails(0, location, -340, -4644));
		bazaarLocations->put(5625468, new BazaarTerminalDetails(0, location, -77, -4599));
		bazaarLocations->put(5625467, new BazaarTerminalDetails(0, location, -55, -4621));
		bazaarLocations->put(5625469, new BazaarTerminalDetails(0, location, -55, -4577));
		bazaarLocations->put(5625470, new BazaarTerminalDetails(0, location, -34, -4599));

		// Dathomir Science outpost
		location = "science_outpost";
		bazaarLocations->put(2835653, new BazaarTerminalDetails(2, location, -70, -1598));
		bazaarLocations->put(2835652, new BazaarTerminalDetails(2, location, -81, -1589));

		// Dathomir Trade outpost
		location = "trade_outpost";
		bazaarLocations->put(1392905, new BazaarTerminalDetails(2, location, 573, 3092));

	}

	~BazaarTerminals() {
		bazaarLocations->resetIterator();

		while (bazaarLocations->hasNext()) {
			BazaarTerminalDetails* btd = bazaarLocations->next();

			delete btd;
		}

		delete bazaarLocations;
		bazaarLocations = NULL;
	}

	BazaarTerminalDetails* isBazaarTerminal(uint64 objectid) {
		return bazaarLocations->get(objectid);
	}

	BazaarMap* getBazaarMap() {
		return bazaarLocations;
	}
};

#endif /*BAZAARTERMINALS_H_*/
