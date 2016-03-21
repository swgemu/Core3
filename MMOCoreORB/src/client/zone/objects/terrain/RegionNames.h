/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

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
