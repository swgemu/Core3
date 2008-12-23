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
				String location = "anchorhead";
				bazaarLocations->put(3945353, new BazaarTerminalDetails(8, location, 60, -5350));
				bazaarLocations->put(3945352, new BazaarTerminalDetails(8, location, 64, -5350));

				// Tatooine Bestine
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

				// Tatooine Mos Eisley
				location = "mos_eisley";
				bazaarLocations->put(3945362, new BazaarTerminalDetails(8, location, 3693, -4816));
				bazaarLocations->put(3945363, new BazaarTerminalDetails(8, location, 3693, -4813));
				bazaarLocations->put(3945364, new BazaarTerminalDetails(8, location, 3693, -4786));
				bazaarLocations->put(3945365, new BazaarTerminalDetails(8, location, 3693, -4783));
				bazaarLocations->put(4685571, new BazaarTerminalDetails(8, location, 3485, -4961));
				bazaarLocations->put(4685572, new BazaarTerminalDetails(8, location, 3512, -4927));
				bazaarLocations->put(4685573, new BazaarTerminalDetails(8, location, 3516, -4958));
				bazaarLocations->put(4685574, new BazaarTerminalDetails(8, location, 3481, -4930));

				// Tatooine Mos Entha
				location = "mos_entha";
				bazaarLocations->put(3945376, new BazaarTerminalDetails(8, location, 1590, 3026));
				bazaarLocations->put(3945377, new BazaarTerminalDetails(8, location, 1590, 3023));
				bazaarLocations->put(4005560, new BazaarTerminalDetails(8, location, 1205, 2993));
				bazaarLocations->put(4005561, new BazaarTerminalDetails(8, location, 1209, 2990));
				bazaarLocations->put(4005562, new BazaarTerminalDetails(8, location, 1181, 3010));
				bazaarLocations->put(4005563, new BazaarTerminalDetails(8, location, 1184, 3008));
				bazaarLocations->put(4685580, new BazaarTerminalDetails(8, location, 1284, 3159));
				bazaarLocations->put(4685582, new BazaarTerminalDetails(8, location, 1432, 3322));
				bazaarLocations->put(4685581, new BazaarTerminalDetails(8, location, 1435, 3265));
				bazaarLocations->put(4685580, new BazaarTerminalDetails(8, location, 1284, 3159));
				bazaarLocations->put(6076306, new BazaarTerminalDetails(8, location, 1284, 2952));
				bazaarLocations->put(6076307, new BazaarTerminalDetails(8, location, 1257, 2925));
				bazaarLocations->put(6076308, new BazaarTerminalDetails(8, location, 1258, 2952));
				bazaarLocations->put(6076309, new BazaarTerminalDetails(8, location, 1284, 2925));

				// Tatooine Mos Espa
				location = "mos_espa";
				bazaarLocations->put(3945383, new BazaarTerminalDetails(8, location, -2774, 2025));
				bazaarLocations->put(3945384, new BazaarTerminalDetails(8, location, -2773, 2027));
				bazaarLocations->put(3945385, new BazaarTerminalDetails(8, location, -2758, 2050));
				bazaarLocations->put(3945386, new BazaarTerminalDetails(8, location, -2757, 2053));
				bazaarLocations->put(4685589, new BazaarTerminalDetails(8, location, -2987, 2315));
				bazaarLocations->put(4685590, new BazaarTerminalDetails(8, location, -2971, 2342));
				bazaarLocations->put(4685591, new BazaarTerminalDetails(8, location, -2998, 2358));
				bazaarLocations->put(4685592, new BazaarTerminalDetails(8, location, -3014, 2331));
				bazaarLocations->put(4685593, new BazaarTerminalDetails(8, location, -2813, 2200));
				bazaarLocations->put(7495394, new BazaarTerminalDetails(8, location, -3115, 2158));
				bazaarLocations->put(7495607, new BazaarTerminalDetails(8, location, -2908, 1927));

				// Tatooine Mos Taike
				location = "mos_taike";
				bazaarLocations->put(3945387, new BazaarTerminalDetails(8, location, 3790, 2337));
				bazaarLocations->put(3945388, new BazaarTerminalDetails(8, location, 3790, 2340));

				// Tatooine Wayfar
				location = "wayfar";
				bazaarLocations->put(3945394, new BazaarTerminalDetails(8, location, -5177, -6485));
				bazaarLocations->put(3945395, new BazaarTerminalDetails(8, location, -5174, -6485));

				// Corellia Coronet
				location = "coronet";
				bazaarLocations->put(1439951, new BazaarTerminalDetails(0, location, -363, -4533));
				bazaarLocations->put(7755375, new BazaarTerminalDetails(0, location, -312, -4644));
				bazaarLocations->put(7755372, new BazaarTerminalDetails(0, location, -340, -4644));
				bazaarLocations->put(5625468, new BazaarTerminalDetails(0, location, -77, -4599));
				bazaarLocations->put(5625467, new BazaarTerminalDetails(0, location, -55, -4621));
				bazaarLocations->put(5625469, new BazaarTerminalDetails(0, location, -55, -4577));
				bazaarLocations->put(5625470, new BazaarTerminalDetails(0, location, -34, -4599));

				// Corellia Bella Vistal
				location = "bela_vistal";
				bazaarLocations->put(3695501, new BazaarTerminalDetails(0, location, 6645, -5943));
				bazaarLocations->put(3695502, new BazaarTerminalDetails(0, location, 6648, -5943));

				// Corellia Doaba Guerfel
				location = "doaba_guerfel";
				bazaarLocations->put(4395373, new BazaarTerminalDetails(0, location, 3413, 5670));
				bazaarLocations->put(4395374, new BazaarTerminalDetails(0, location, 3409, 5672));
				bazaarLocations->put(5316176, new BazaarTerminalDetails(0, location, 3225, 5371));
				bazaarLocations->put(5316177, new BazaarTerminalDetails(0, location, 3194, 5402));
				bazaarLocations->put(5316178, new BazaarTerminalDetails(0, location, 3225, 5402));
				bazaarLocations->put(5316179, new BazaarTerminalDetails(0, location, 3194, 5371));
				bazaarLocations->put(5585534, new BazaarTerminalDetails(0, location, 3088, 5013));

				// Corellia Tyrena
				location = "tyrena";
				bazaarLocations->put(5625462, new BazaarTerminalDetails(0, location, -5122, -2368));
				bazaarLocations->put(5625463, new BazaarTerminalDetails(0, location, -5091, -2368));
				bazaarLocations->put(5625464, new BazaarTerminalDetails(0, location, -5090, -2399));
				bazaarLocations->put(5625465, new BazaarTerminalDetails(0, location, -5121, -2399));

				// Corellia Vreni Island
				location = "vreni_island";
				bazaarLocations->put(4705376, new BazaarTerminalDetails(0, location, -5541, -6211));
				bazaarLocations->put(4705377, new BazaarTerminalDetails(0, location, -5541, -6208));
				bazaarLocations->put(6035457, new BazaarTerminalDetails(0, location, -5567, -6052));

				// Corellia Kor Vella
				location = "kor_vella";
				bazaarLocations->put(6035509, new BazaarTerminalDetails(0, location, -3116, 2968));
				bazaarLocations->put(6035510, new BazaarTerminalDetails(0, location, -3120, 2968));
				bazaarLocations->put(6035511, new BazaarTerminalDetails(0, location, -3146, 2969));
				bazaarLocations->put(6035512, new BazaarTerminalDetails(0, location, -3150, 2969));
				bazaarLocations->put(6035513, new BazaarTerminalDetails(0, location, -3150, 2784));
				bazaarLocations->put(6035514, new BazaarTerminalDetails(0, location, -3150, 2780));
				bazaarLocations->put(6035515, new BazaarTerminalDetails(0, location, -3790, 3178));
				bazaarLocations->put(6035516, new BazaarTerminalDetails(0, location, -3776, 3192));

				// Dathomir Science outpost
				location = "science_outpost";
				bazaarLocations->put(2835653, new BazaarTerminalDetails(2, location, -70, -1598));
				bazaarLocations->put(2835652, new BazaarTerminalDetails(2, location, -81, -1589));

				// Dathomir Trade outpost
				location = "trade_outpost";
				bazaarLocations->put(1392905, new BazaarTerminalDetails(2, location, 573, 3092));

				// Dathomir Imperial Prison
				location = "a_restricted_area";
				bazaarLocations->put(4865404, new BazaarTerminalDetails(2, location, -6313, 874));
				bazaarLocations->put(4865405, new BazaarTerminalDetails(2, location, -6326, 874));

				// Dantooine Imperial Outpost
				location = "an_imperial_outpost";
				//TODO: -4252, -2412
				bazaarLocations->put(1365895, new BazaarTerminalDetails(1, location, -4252, -2412)); //I cant get this bazaar to initialize, have to take a look at it some other time.
				bazaarLocations->put(1365910, new BazaarTerminalDetails(1, location, -4263, -2404)); //inside a cell

				// Dantooine Mining Outpost
				location = "an_outpost";
				bazaarLocations->put(1366001, new BazaarTerminalDetails(1, location, -618, 2490));
				bazaarLocations->put(7275354, new BazaarTerminalDetails(1, location, -607, 2468)); //inside a cell

				// Dantooine Agro Outpost
				//location = "an_outpost";
				bazaarLocations->put(8605394, new BazaarTerminalDetails(1, location, 1615, -6366));
				bazaarLocations->put(8605395, new BazaarTerminalDetails(1, location, 1560, -6366));

				// Naboo Theed
				location = "theed";
				bazaarLocations->put(2776044, new BazaarTerminalDetails(5, location, -5010, 4256));
				bazaarLocations->put(2776045, new BazaarTerminalDetails(5, location, -5018, 4246));
				bazaarLocations->put(2776043, new BazaarTerminalDetails(5, location, -5705, 4193));
				bazaarLocations->put(2776042, new BazaarTerminalDetails(5, location, -5727, 4171));
				bazaarLocations->put(2776041, new BazaarTerminalDetails(5, location, -5705, 4149));
				bazaarLocations->put(2776040, new BazaarTerminalDetails(5, location, -5683, 4171));
				bazaarLocations->put(2776039, new BazaarTerminalDetails(5, location, -5147, 4174));
				bazaarLocations->put(2776038, new BazaarTerminalDetails(5, location, -5145, 4143));
				bazaarLocations->put(2776037, new BazaarTerminalDetails(5, location, -5114, 4145));
				bazaarLocations->put(2776036, new BazaarTerminalDetails(5, location, -5116, 4176));
				bazaarLocations->put(3955353, new BazaarTerminalDetails(5, location, -5014, 4251));
				bazaarLocations->put(3955363, new BazaarTerminalDetails(5, location, -5350, 4141));
				bazaarLocations->put(3955364, new BazaarTerminalDetails(5, location, -5350, 4147));
				bazaarLocations->put(4105355, new BazaarTerminalDetails(5, location, -5118, 4334));
				bazaarLocations->put(4105356, new BazaarTerminalDetails(5, location, -5076, 4298));

				// Naboo Moenia
				location = "moenia";
				bazaarLocations->put(3955372, new BazaarTerminalDetails(5, location, 4878, -4850));

				// Naboo Keren
				location = "keren";
				bazaarLocations->put(3955374, new BazaarTerminalDetails(5, location, 1277, 2770));
				bazaarLocations->put(3955375, new BazaarTerminalDetails(5, location, 1277, 2773));
				bazaarLocations->put(3955376, new BazaarTerminalDetails(5, location, 1278, 2758));
				bazaarLocations->put(3955377, new BazaarTerminalDetails(5, location, 1278, 2761));
				bazaarLocations->put(4776047, new BazaarTerminalDetails(5, location, 1808, 2614));
				bazaarLocations->put(4776048, new BazaarTerminalDetails(5, location, 1765, 2614));
				bazaarLocations->put(4776049, new BazaarTerminalDetails(5, location, 1786, 2635));
				bazaarLocations->put(4776050, new BazaarTerminalDetails(5, location, 1787, 2592));

				// Naboo Kaadara
				location = "kaadara";
				bazaarLocations->put(4105632, new BazaarTerminalDetails(5, location, 5368, 6645));
				bazaarLocations->put(4105633, new BazaarTerminalDetails(5, location, 5368, 6648));
				bazaarLocations->put(4105634, new BazaarTerminalDetails(5, location, 5369, 6656));
				bazaarLocations->put(4105635, new BazaarTerminalDetails(5, location, 5370, 6679));
				bazaarLocations->put(4776016, new BazaarTerminalDetails(5, location, 5060, 6723));
				bazaarLocations->put(4776017, new BazaarTerminalDetails(5, location, 5063, 6727));
				bazaarLocations->put(4776018, new BazaarTerminalDetails(5, location, 5094, 6696));
				bazaarLocations->put(4776019, new BazaarTerminalDetails(5, location, 5091, 6692));

				// Naboo Moenia
				location = "moenia";
				bazaarLocations->put(4776020, new BazaarTerminalDetails(5, location, 4787, -4852));
				bazaarLocations->put(4776021, new BazaarTerminalDetails(5, location, 4817, -4849));
				bazaarLocations->put(4776022, new BazaarTerminalDetails(5, location, 4821, -4880));
				bazaarLocations->put(4776023, new BazaarTerminalDetails(5, location, 4790, -4883));
				bazaarLocations->put(4855366, new BazaarTerminalDetails(5, location, 4656, -4617));
				bazaarLocations->put(4855367, new BazaarTerminalDetails(5, location, 4653, -4621));
				bazaarLocations->put(4855368, new BazaarTerminalDetails(5, location, 4674, -4592));
				bazaarLocations->put(4855369, new BazaarTerminalDetails(5, location, 4671, -4597));

				// Naboo Deeja Peak
				location = "deeja_peak";
				bazaarLocations->put(4776039, new BazaarTerminalDetails(5, location, 5339, -1560));
				bazaarLocations->put(4776042, new BazaarTerminalDetails(5, location, 4936, -1501));
				bazaarLocations->put(4776043, new BazaarTerminalDetails(5, location, 4937, -1444));
				bazaarLocations->put(4776044, new BazaarTerminalDetails(5, location, 4730, -1342));

				// Naboo Lake Retreat
				location = "lake_retreat";
				bazaarLocations->put(4655386, new BazaarTerminalDetails(5, location, -5488, -5));

				// Rori Rebel Outpost
				location = "a_rebel_outpost";
				bazaarLocations->put(4505545, new BazaarTerminalDetails(6, location, 3663, -6421));

				// Rori Restuss
				location = "restuss";
				bazaarLocations->put(4695458, new BazaarTerminalDetails(6, location, 5304, 5831));
				bazaarLocations->put(4695459, new BazaarTerminalDetails(6, location, 5301, 5828));
				bazaarLocations->put(4695462, new BazaarTerminalDetails(6, location, 5306, 5823));
				bazaarLocations->put(4695463, new BazaarTerminalDetails(6, location, 5309, 5826));
				bazaarLocations->put(4695483, new BazaarTerminalDetails(6, location, 5180, 5562));
				bazaarLocations->put(4695484, new BazaarTerminalDetails(6, location, 5181, 5605));
				bazaarLocations->put(6445440, new BazaarTerminalDetails(6, location, 5241, 5789));
				bazaarLocations->put(6445441, new BazaarTerminalDetails(6, location, 5241, 5786));

				// Rori Narmle
				location = "narmle";
				bazaarLocations->put(4695696, new BazaarTerminalDetails(6, location, -5431, -2113));
				bazaarLocations->put(4695697, new BazaarTerminalDetails(6, location, -5437, -2119));
				bazaarLocations->put(4695698, new BazaarTerminalDetails(6, location, -5434, -2117));
				bazaarLocations->put(4695699, new BazaarTerminalDetails(6, location, -5428, -2110));
				bazaarLocations->put(4725481, new BazaarTerminalDetails(6, location, -5088, -2474));
				bazaarLocations->put(4725482, new BazaarTerminalDetails(6, location, -5132, -2474));
				bazaarLocations->put(5265435, new BazaarTerminalDetails(6, location, -5281, -2170));

				// Talus Nashal
				location = "nashal";
				bazaarLocations->put(4385489, new BazaarTerminalDetails(7, location, 4520, 5430));
				bazaarLocations->put(4385490, new BazaarTerminalDetails(7, location, 4516, 5431));
				bazaarLocations->put(4385491, new BazaarTerminalDetails(7, location, 4491, 5439));
				bazaarLocations->put(4385492, new BazaarTerminalDetails(7, location, 4487, 5441));
				bazaarLocations->put(4636084, new BazaarTerminalDetails(7, location, 4332, 5444));
				bazaarLocations->put(4795397, new BazaarTerminalDetails(7, location, 4525, 5066));
				bazaarLocations->put(4795398, new BazaarTerminalDetails(7, location, 4105, 5289));
				bazaarLocations->put(4795402, new BazaarTerminalDetails(7, location, 4349, 5150));
				bazaarLocations->put(4795403, new BazaarTerminalDetails(7, location, 4347, 5179));

				// Talus Dearic
				location = "dearic";
				bazaarLocations->put(4775555, new BazaarTerminalDetails(7, location, 170, -2948));
				bazaarLocations->put(4775556, new BazaarTerminalDetails(7, location, 170, -2943));
				bazaarLocations->put(4775557, new BazaarTerminalDetails(7, location, 170, -2918));
				bazaarLocations->put(4775558, new BazaarTerminalDetails(7, location, 170, -2913));
				bazaarLocations->put(4795392, new BazaarTerminalDetails(7, location, 553, -3003));
				bazaarLocations->put(4795393, new BazaarTerminalDetails(7, location, 526, -2976));
				bazaarLocations->put(6255435, new BazaarTerminalDetails(7, location, 715, -3048));

				// Talus Imperial Outpost
				location = "an_imperial_outpost";
				bazaarLocations->put(5315984, new BazaarTerminalDetails(7, location, -2170, 2344));

				// Endor Research Outpost
				location = "an_outpost";
				bazaarLocations->put(3606001, new BazaarTerminalDetails(3, location, 3231, -3501));
				bazaarLocations->put(3606003, new BazaarTerminalDetails(3, location, 3243, -3501));
				// Endor Smuggler Outpost
				bazaarLocations->put(6645628, new BazaarTerminalDetails(3, location, -867, 1557));
				bazaarLocations->put(6645630, new BazaarTerminalDetails(3, location, -868, 1554));

				// Lok Nyms Stronghold
				location = "nyms_stronghold";
				bazaarLocations->put(4705366, new BazaarTerminalDetails(4, location, 459, 5506));
				bazaarLocations->put(4705367, new BazaarTerminalDetails(4, location, 461, 5506));
				bazaarLocations->put(5705412, new BazaarTerminalDetails(4, location, 443, 5050));
				bazaarLocations->put(5705413, new BazaarTerminalDetails(4, location, 421, 5028));
				bazaarLocations->put(5705414, new BazaarTerminalDetails(4, location, 399, 5050));
				bazaarLocations->put(5705415, new BazaarTerminalDetails(4, location, 421, 5072));

				// Yavin IV Labor Outpost
				location = "an_outpost";
				bazaarLocations->put(3035821, new BazaarTerminalDetails(9, location, -6917, -5741));
				bazaarLocations->put(3035822, new BazaarTerminalDetails(9, location, -6917, -5736));

				// Yavin IV Mining Outpost
				location = "an_outpost";
				bazaarLocations->put(7925512, new BazaarTerminalDetails(9, location, -311, 4854));
				bazaarLocations->put(7925513, new BazaarTerminalDetails(9, location, -315, 4854));


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
