#ifndef SHIPDROIDDATA_H_
#define SHIPDROIDDATA_H_

#include "engine/engine.h"

class ShipDroidData {
public:
	enum DroidType : int {
			NONE = 0,
			ASTROMECH = 1,
			FLIGHTCOMPUTER = 2
	};

	static uint32 getShipDroidType(uint32 shipNameCRC) {
		switch (shipNameCRC) {
			case String::hashCode("player_awing"):					return FLIGHTCOMPUTER;
			case String::hashCode("player_basic_hutt_light"):		return FLIGHTCOMPUTER;
			case String::hashCode("player_basic_tiefighter"):		return FLIGHTCOMPUTER;
			case String::hashCode("player_basic_z95"):				return ASTROMECH;
			case String::hashCode("player_blacksun_heavy_s01"):		return FLIGHTCOMPUTER;
			case String::hashCode("player_blacksun_heavy_s02"):		return FLIGHTCOMPUTER;
			case String::hashCode("player_blacksun_heavy_s03"):		return FLIGHTCOMPUTER;
			case String::hashCode("player_blacksun_heavy_s04"):		return FLIGHTCOMPUTER;
			case String::hashCode("player_blacksun_light_s01"):		return FLIGHTCOMPUTER;
			case String::hashCode("player_blacksun_light_s02"):		return FLIGHTCOMPUTER;
			case String::hashCode("player_blacksun_light_s03"):		return FLIGHTCOMPUTER;
			case String::hashCode("player_blacksun_light_s04"):		return FLIGHTCOMPUTER;
			case String::hashCode("player_blacksun_medium_s01"):	return FLIGHTCOMPUTER;
			case String::hashCode("player_blacksun_medium_s02"):	return FLIGHTCOMPUTER;
			case String::hashCode("player_blacksun_medium_s03"):	return FLIGHTCOMPUTER;
			case String::hashCode("player_blacksun_medium_s04"):	return FLIGHTCOMPUTER;
			case String::hashCode("player_bwing"):					return FLIGHTCOMPUTER;
			case String::hashCode("player_decimator"):				return FLIGHTCOMPUTER;
			case String::hashCode("player_firespray"):				return FLIGHTCOMPUTER;
			case String::hashCode("player_hutt_heavy_s01"):			return FLIGHTCOMPUTER;
			case String::hashCode("player_hutt_heavy_s02"):			return FLIGHTCOMPUTER;
			case String::hashCode("player_hutt_light_s01"):			return FLIGHTCOMPUTER;
			case String::hashCode("player_hutt_light_s02"):			return FLIGHTCOMPUTER;
			case String::hashCode("player_hutt_medium_s01"):		return FLIGHTCOMPUTER;
			case String::hashCode("player_hutt_medium_s02"):		return FLIGHTCOMPUTER;
			case String::hashCode("player_sorosuub_space_yacht"):	return ASTROMECH;
			case String::hashCode("player_tie_in"):					return FLIGHTCOMPUTER;
			case String::hashCode("player_tie_light_duty"):			return FLIGHTCOMPUTER;
			case String::hashCode("player_tieadvanced"):			return FLIGHTCOMPUTER;
			case String::hashCode("player_tieaggressor"):			return FLIGHTCOMPUTER;
			case String::hashCode("player_tiebomber"):				return FLIGHTCOMPUTER;
			case String::hashCode("player_tiefighter"):				return FLIGHTCOMPUTER;
			case String::hashCode("player_tieinterceptor"):			return FLIGHTCOMPUTER;
			case String::hashCode("player_tieoppressor"):			return FLIGHTCOMPUTER;
			case String::hashCode("player_xwing"):					return ASTROMECH;
			case String::hashCode("player_ykl37r"):					return FLIGHTCOMPUTER;
			case String::hashCode("player_yt1300"):					return FLIGHTCOMPUTER;
			case String::hashCode("player_ywing"):					return ASTROMECH;
			case String::hashCode("player_ywing_longprobe"):		return ASTROMECH;
			case String::hashCode("player_z95"):					return ASTROMECH;
			case String::hashCode("player_hutt_turret_ship"):		return FLIGHTCOMPUTER;
			default :return NONE;
		}
	}

	static uint32 getDroidType(uint32 droidCrc) {
		switch (droidCrc) {
			case String::hashCode("object/mobile/r2_crafted.iff"):				return ASTROMECH;
			case String::hashCode("object/mobile/r3_crafted.iff"):				return ASTROMECH;
			case String::hashCode("object/mobile/r4_crafted.iff"):				return ASTROMECH;
			case String::hashCode("object/mobile/r5_crafted.iff"):				return ASTROMECH;
			case String::hashCode("object/tangible/droid/navicomputer_1.iff"):	return FLIGHTCOMPUTER;
			case String::hashCode("object/tangible/droid/navicomputer_2.iff"):	return FLIGHTCOMPUTER;
			case String::hashCode("object/tangible/droid/navicomputer_3.iff"):	return FLIGHTCOMPUTER;
			case String::hashCode("object/tangible/droid/navicomputer_4.iff"):	return FLIGHTCOMPUTER;
			case String::hashCode("object/tangible/droid/navicomputer_5.iff"):	return FLIGHTCOMPUTER;
			case String::hashCode("object/tangible/droid/navicomputer_6.iff"):	return FLIGHTCOMPUTER;
			default :return NONE;
		}
	}
};

#endif // SHIPDROIDDATA_H_
