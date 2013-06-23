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

#ifndef REGIONNAMES_H_
#define REGIONNAMES_H_

const static char* RegionNames[] = {
    "@corellia_region_names:coronet",
    "@corellia_region_names:tyrena",
    "@corellia_region_names:kor_vella",
    "@corellia_region_names:bela_vistal",
    "@corellia_region_names:doaba_guerfel",
    "@corellia_region_names:vreni_island",
    "@dantooine_region_names:an_outpost",
    "@dantooine_region_names:an_outpost",
    "@dantooine_region_names:an_imperial_outpost",
    "@dathomir_region_names:a_restricted_area",
    "@dathomir_region_names:trade_outpost",
    "@dathomir_region_names:science_outpost",
    "@endor_region_names:an_outpost",
    "@lok_region_names:nyms_stronghold",
    "@lok_region_names:an_imperial_outpost",
    "@naboo_region_names:theed",
    "@naboo_region_names:keren",
    "@naboo_region_names:moenia",
    "@naboo_region_names:deeja_peak",
    "@naboo_region_names:kaadara",
    "@rori_region_names:narmle",
    "@rori_region_names:restuss",
    "@rori_region_names:a_rebel_outpost",
    "@talus_region_names:dearic",
    "@talus_region_names:nashal",
    "@talus_region_names:an_imperial_outpost",
    "@tatooine_region_names:bestine",
    "@tatooine_region_names:mos_espa",
    "@tatooine_region_names:mos_eisley",
    "@tatooine_region_names:mos_entha",
    "@tatooine_region_names:mos_taike",
    "@tatooine_region_names:anchorhead",
    "@tatooine_region_names:wayfar",
    "@yavin4_region_names:an_outpost",
};

class Region {
public:
	inline const static char* getRegionName(int regionid) {
		return RegionNames[regionid];
	}
	
};
#endif /*REGIONNAMES_H_*/
