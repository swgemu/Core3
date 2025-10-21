/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#ifndef SHIPFLAG_H_
#define SHIPFLAG_H_

class ShipFlag {
public:
	enum {
		ESCORT						= 0x000001,
		FOLLOW						= 0x000002,
		TURRETSHIP					= 0x000004,
		GUARD_PATROL				= 0x000008,
		RANDOM_PATROL				= 0x000010,
		FIXED_PATROL				= 0x000020,
		WAVE_ATTACK					= 0x000040,
		DISABLED_INVULNERABLE		= 0x000080,
		ATTACKABLE_SPACE_STATION	= 0x000100,
		SINGLE_PATROL_ROTATION		= 0x000200,
		TEST 						= 0x000400,
		LASTAIMASK 					= 0x000800, // keep this updated so we can loop through the masks
	};
};

/*
	ESCORT - for quest escorts for ships and specific behaviors during
	FOLLOW - For ships following a target outside of escorts.alignas
	TURRETSHIP - Behavior flag for turret ships.
	GUARD_PATROL - For ships that patrol a specific area in a spherical pattern where they will have a min range and max range to stay within
					used for ships in patrol around a point or object such as a space station.
	RANDOM_PATROL - Default method for patrolling. Randomly generates points around its home location.alignas
	FIXED_PATROL - For ships that have specific set of patrol points assigned to them and will only navigate to those points.alignas
	WAVE_ATTACK - Ships that are spawned for wave attacks during escort missions.
	DISABLED_INVULNERABLE - Used to flag ships invulnerable for a brief period after being disabled.
*/

#endif /* SHIPFLAG_H_ */
