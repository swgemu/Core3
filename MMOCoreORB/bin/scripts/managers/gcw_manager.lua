--frequency of sanity check in seconds
gcwCheckTimer = 3600

--Amount of time in seconds that a base will be vulnerable
vulnerabilityDuration = 10800

-- Amount of time in seconds between base vulnerabilities.
vulnerabilityFrequency = 172800

powerSwitchCount = 7

-- amount of time before waiting to reset vulnerability
resetTimer = 1209600

-- amount of time in seconds to wait when a slice fails
sliceCooldown = 120

dnaNucleotides = { "A", "G", "C", "T" }
dnaPairs = { "AT", "TA", "GC", "CG" }

totalDNASamples = 44

dnaStrandLength = 23

-- Amount of time in seconds that a base destruction takes after the countdown is initiated
destructionTimer = 600

-- maximum bases per planet
maxBases = 25

-- time in seconds that a player must be overt before aborting a facility shutdown
overtCooldown = 300

-- time in seconds to wait before reactivating the overload after the shutdown is aborted
reactivationTimer = 300

-- time that a player can maintain control of a turret before another player can take it
--(removed)turretInactivityTimer = 15

-- amount of time in seconds that a turret must wait after the last manual turret activity
-- X seconds after the last manual activity the turret will be able to auto fire
turretAutoFireTimeout = 20

maxBasesPerPlayer = 3

-- Enable Alarms on player GCW bases
spawnBaseAlarms = true

-- xp bonus for faction controlling a planet
bonusXP = 15

-- Crackdown settings
crackdownScansEnabled = true
-- thresholds for scaling crackdown npc's difficulty, first threshold should always be 0.
difficutlyScalingThresholds = {0, 64}
crackdownScanPrivilegedPlayers = false
--crackdownPlayerScanCooldown = 24 * 60 * 60  -- In seconds
crackdownPlayerScanCooldown = 2 * 60  -- In seconds, remove this row when testing is completed.
crackdownContrabandFineCredits = 10000
crackdownContrabandFineFactionPoints = 100
crackdownPlanetsWithWildScans = { "corellia", "dantooine", "dathomir", "endor", "lok", "naboo", "rori", "talus", "tatooine", "yavin4"}
-- Radius for the area in which all players are retrieved in order to select one of them randomly to be scanned in the wild.
-- All objects in the octree in that radius will be iterated.
crackdownPerformanceWildScanPlayerFindRadius = 10240  -- Tweak this in order to decrease the load on the server when a wild scan is tried.

-- discount percentage for side losing&winning the gcw.  negative value of increase in price (penality).  positive for a decrease (Bonus)

winnerBonus = 0
loserBonus = -30

-- Spawn turrets and minefields when base is placed 1=true 0=false
spawnDefenses = 1

-- Amount of time to delay vulnerability in seconds afer placing base
initialVulnerabilityDelay = 0

racialPenaltyEnabled = 1

-- assign points to each type of base
-- s01=Forward Outpost, s02 = Field Hospital , s03 = Tactical Center, s04 = Detach HQ
HQValues = {
	{"object/building/faction_perk/hq/hq_s01_imp_pvp.iff", 2},
	{"object/building/faction_perk/hq/hq_s01_imp.iff", 1},
	{"object/building/faction_perk/hq/hq_s02_imp_pvp.iff", 6},
	{"object/building/faction_perk/hq/hq_s02_imp.iff" , 3},
	{"object/building/faction_perk/hq/hq_s03_imp_pvp.iff" , 8},
	{"object/building/faction_perk/hq/hq_s03_imp.iff", 4},
	{"object/building/faction_perk/hq/hq_s04_imp_pvp.iff", 20},
	{"object/building/faction_perk/hq/hq_s04_imp.iff", 10},
	{"object/building/faction_perk/hq/hq_s01_rebel_pvp.iff", 2},
	{"object/building/faction_perk/hq/hq_s01_rebel.iff", 1},
	{"object/building/faction_perk/hq/hq_s02_rebel_pvp.iff", 6},
	{"object/building/faction_perk/hq/hq_s02_rebel.iff" , 3},
	{"object/building/faction_perk/hq/hq_s03_rebel_pvp.iff" , 8},
	{"object/building/faction_perk/hq/hq_s03_rebel.iff", 4},
	{"object/building/faction_perk/hq/hq_s04_rebel_pvp.iff", 20},
	{"object/building/faction_perk/hq/hq_s04_rebel.iff", 10},
	{"object/building/general/rori_hyperdrive_research_facility.iff", 2},
	{"object/building/general/bunker_imperial_weapons_research_facility_01.iff", 2},
	{"object/building/general/bunker_imperial_detainment_center_01.iff", 2},
	{"object/building/general/bunker_rebel_weapons_depot.iff", 2},

}

-- race (raceid, penalty_multiplier)
-- raceid found in creatureobject
--HUMAN = 0; RODIAN = 1; TRANDOSHAN = 2; MONCAL = 3; WOOKIE = 4; BOTHAN = 5; TWILEK = 6; ZABRAK = 7; ITHORIAN = 0x21; SULLUSTAN = 0x31;
imperial_racial_penalty = {
	{0, 1},
	{1, 3}, --rodian
	{2, 2}, -- trando
	{3, 3}, -- moncal
	{4, 3}, -- wookie
	{5, 2},  -- bothan
	{6, 1.5}, -- twilek
	{7, 2},  -- zabrack
	{33, 2}, --ithorian
	{49, 2}, -- sullustan

}

strongholdCities = {
	imperial = {"bela_vistal", "deeja_peak", "bestine"},
	rebel = {"vreni_island", "moenia", "anchorhead"}
}

terminalTemplates = {
	"object/tangible/hq_destructible/override_terminal.iff",
	"object/tangible/hq_destructible/power_regulator.iff",
	"object/tangible/hq_destructible/security_terminal.iff",
	"object/tangible/hq_destructible/uplink_terminal.iff"
}

-- { x, z, y, ox, oy, oz, ow, cell }
terminalSpawns = {
	-- Imperial Forward Outpost
	{ "hq_s01_imp",
		{
			{ -3.67, 0.13, 4.73, 0, 1, 0, 0, 1 },
			{ -5.61, 0.13, 2.96, 0, 0.707, 0, 0.707, 2 },
			{ -5.11, 0.13, 0.88, 0, 0, 0, 1, 2 },
			{ -2.37, 0.13, 0.88, 0, 0, 0, 1, 2 },
			{ 5.69, 0.13, 3.06, 0, 0.707, 0, -0.707, 4 },
			{ 5.65, 0.13, -2.69, 0, 0.707, 0, -0.707, 5 },
			{ 5.68, 0.13, -4.83, 0, 0.707, 0, -0.707, 5 },
			{ -2.83, 0.13, -5.94, 0, 0, 0, 1, 6 }
		}
	},
	-- Rebel Forward Outpost
	{ "hq_s01_rebel",
		{
			{ -2.38, 0.1, 0.6, 0, 0, 0, 1, 2 },
			{ 0.59, 0.1, 2.4, 0, 1, 0, 0, 3 },
			{ -1.2, 0.1, -0.69, 0, 0.707, 0, 0.707, 3 },
			{ 5.92, 0.1, -0.3, 0, -0.707, 0, 0.707, 4 },
			{ 2.85, 0.1, -0.89, 0, 0, 0, 1, 4 },
			{ 5.1, 0.1, -6.17, 0, 0, 0, 1, 5 },
			{ 5.92, 0.1, -4.7, 0, -0.707, 0, 0.707, 5 },
			{ -2.9, 0.1, -6.17, 0, 0, 0, 1, 6 },
		}
	},
	-- Imperial Field Hospital
	{ "hq_s02_imp",
		{
			{ 1.06, 0.25, 3.25, 0, 0.707, 0, -0.707, 2 },
			{ -4.93, 0.25, -2.54, 0, 0.707, 0, 0.707, 2 },
			{ -0.09, 0.25, -5.2, 0, 0, 0, 1, 3 },
			{ -8.2, -6.75, -3.94, 0, 0.707, 0, 0.707, 5 },
			{ -0.79, -6.75, -4.06, 0, 0.707, 0, -0.707, 5 },
			{ -6.99, -6.77, -17.94, 0, 0, 0, 1, 6 },
			{ 7.98, -6.77, -17.94, 0, 0, 0, 1, 6 },
			{ 3.43, -6.75, 0.47, 0, 1, 0, 0, 7 },
			{ 0.67, -13.75, -17.18, 0, 0, 0, 1, 9 },
			{ -5.69, -13.75, -17.18, 0, 0, 0, 1, 9 },
		}
	},
	-- Rebel Field Hospital
	{ "hq_s02_rebel",
		{
			{ -5.15, 0.3, 3.25, 0, 0.707, 0, 0.707, 2 },
			{ -2.79, -6.8, -10.35, 0, 0, 0, 1, 5 },
			{ -9.29, -6.8, -4.9, 0, 0, 0, 1, 5 },
			{ -6.71, -6.8, -12, 0, 0, 0, 1, 6 },
			{ 7.4, -6.8, -12, 0, 0, 0, 1, 6 },
			{ 1.67, -6.8, -8.98, 0, 0.707, 0, 0.707, 7 },
			{ 5.16, -13.8, -13.13, 0, -0.707, 0, 0.707, 9 },
			{ -10.16, -13.8, -13.13, 0, 0.707, 0, 0.707, 9 },
			{ 3.82, -13.8, -3.5, 0, -0.707, 0, 0.707, 9 },
		}
	},
	-- Imperial Tactical Center
	{ "hq_s03_imp",
		{
			{ -0.8, 0.25, 1.58, 0, 0, 0, 1, 2 },
			{ 3.47, 0.25, -5.7, 0, 0, 0, 1, 3 },
			{ -0.11, 0.25, -2.82, 0, 1, 0, 0, 3 },
			{ 4.54, -13.75, 1.95, 0, 0.707, 0, -0.707, 6 },
			{ 4.34, -13.75, 10.44, 0, 1, 0, 0, 7 },
			{ -7.32, -13.75, 10.44, 0, 1, 0, 0, 7 },
			{ 3.26, -20.73, 1.3, 0, 0, 0, 1, 9 },
			{ -5.22, -20.75, 16.75, 0, 0.707, 0, 0.707, 10 },
			{ 8.22, -20.75, 16.75, 0, 0.707, 0, -0.707, 10 },
		}
	},
	-- Rebel Tactical Center
	{ "hq_s03_rebel",
		{
			{ -0.14, 0.3, -2.61, 0, 1, 0, 0, 3 },
			{ -4.83, -13.8, 4.12, 0, 0, 0, 1, 7 },
			{ 8.14, -13.8, 7.3, 0, -0.707, 0, 0.707, 7 },
			{ -1.2, -20.7, 12.45, 0, 1, 0, 0, 9 },
			{ 5.36, -20.7, 7.69, 0, -0.707, 0, 0.707, 9 },
			{ -5.3, -20.8, 31.78, 0, 0.707, 0, 0.707, 10 },
			{ 8.27, -20.8, 34.2, 0, -0.707, 0, 0.707, 10 },
			{ -5.3, -20.8, 34.26, 0, 0.707, 0, 0.707, 10 },
		}
	},
	-- Imperial Detachment HQ
	{ "hq_s04_imp",
		{
			{ -1.08, 0.25, 3.22, 0, 0.707, 0, 0.707, 2 },
			{ 4.96, 0.25, 3.07, 0, 0.707, 0, -0.707, 2 },
			{ -0.5, 0.25, -2.77, 0, 1, 0, 0, 3 },
			{ -3.48, 0.25, -5.7, 0, 0, 0, 1, 3 },
			{ 6.22, -6.75, -10.44, 0, 0, 0, 1, 5 },
			{ 0.21, -13.75, -1.81, 0, 0.707, 0, -0.707, 7 },
			{ 10.78, -13.76, 13.69, 0, 1, 0, 0, 8 },
			{ 18.41, -13.76, 8.56, 0, 0.707, 0, -0.707, 9 },
			{ 18.41, -13.76, 5.43, 0, 0.707, 0, -0.707, 9 },
			{ 13.77, -13.76, -4.1, 0, 1, 0, 0, 10 },
		}
	},
	-- Rebel Detachment HQ
	{ "hq_s04_rebel",
		{
			{ 5.15, 0.3, -1.88, 0, -0.707, 0, 0.707, 2 },
			{ 6.21, -6.8, -10.58, 0, 0, 0, 1, 5 },
			{ 0.3, -13.7, -5.53, 0, -0.707, 0, 0.707, 7 },
			{ 0.3, -13.7, -11.9, 0, -0.707, 0, 0.707, 7 },
			{ 10.8, -13.8, 13.78, 0, 1, 0, 0, 8 },
			{ 18.57, -13.8, 8.89, 0, -0.707, 0, 0.707, 9 },
			{ 18.57, -13.8, 5.07, 0, -0.707, 0, 0.707, 9 },
			{ 17.21, -13.8, -3.71, 0, 1, 0, 0, 10 },
			{ 13.81, -13.8, -3.71, 0, 1, 0, 0, 10 },
		}
	}
}

-- {x, z, y, ox, oy, oz, ow, cell}
baseAlarmLocations = {
	-- Forward Outpost
	{"hq_s01",
		{
			{"alarm_destruct",
				{
					{-5, 3.1, 3, 0, 0, 0, 1, 2},
					{0, 3.6, -2, 0, 0, 0, 1, 3},
				}
			},
			{"alarm_hack",
				{
					{-6, 2.8, 3, 0.005, 0.707, 0.707, 0.005, 2},
				}
			},
			{"alarm_hack_no_sound",
				{
					{0, 3.2, 2.5, 0.700, -0.700, 0.04, -0.04, 3},
				}
			},
		}
	},
	-- Field Hospital
	{"hq_s02",
		{
			{"alarm_destruct",
				{
					{-3.69, 3.75, 3.19, -0.011, 0.99, 0.017, 0.002550, 2},
					{-4.5, -8.3, -1.7, 0, 0, 0, 1, 5},
					{-8.2, -2.0, -15, 0, 0, 0, 1, 6},
					{5.5, -0.9, -1.7, 0, 0, 0, 1, 7},
					{-2.49, -13.64, -8.72, -0.01, -0.01, 0.994, -0.028, 9},
				}
			},
			{"alarm_destruct_no_sound",
				{
					{-3.7, 3.75, -4.7, 0, 0, 0, 1, 2},
					{3.5, -5.3, 4.1, 0, 0, 0, 1, 3},
					{-4.49, -1.66, -2.44, -0.009, 0.009, -0.009, 1, 5},
					{0.2, -1.8, -15, 0, 0, 0, 1, 6},
					{5.5, -1.8, -1.7, 0, 0, 0, 1, 7},
					{-2.49, -13.64, -8.72, -0.01, -0.01, 0.994, -0.028, 9},
				}
			},
			{"alarm_hack",
				{
					{1.3245, 2.882, 3.227, 0.728, -0.005, -0.005, 0.686, 2},
				}
			},
			{"alarm_hack_no_sound",
				{
					{-5.2, 3.4, 0.8, 0.005, 0.707, 0.707, 0.005, 2},
					{-0.3, 3.3, -5.5, -0.010, 0.009, 0.716, 0.700, 3},
					{-0.5, -3.51, -3.09, -0.510, 0.504, -0.500, -0.500, 5},
					{0.818, -3.44, -11.834, -0.028, -0.042, 0.718, -0.694, 6},
					{1.488, -3.47, -3.09, 0.508, 0.495, 0.5001, -0.495, 7},
					{-2.44, -9.15, 3.502, 0.0003, 0.014, -0.704, 0.710, 9},
				}
			},
		}
	},
	-- Tactical Center
	{"hq_s03",
		{
			{"alarm_destruct",
				{
					{1.5, -15.65, 3.6, 0, 0, 0, 1, 9},
					{-3.69, 3.75, 3.19, -0.011, 0.99, 0.017, 0.002550, 2},
					{3.5, 4.25, -5.3, 0, 0, 0, 1, 3},
					{3.2, -9, 8.9, 0, 0, 0, 1, 7},
				}
			},
			{"alarm_destruct_no_sound",
				{
					{1.5, -15.65, 10.5, 0, 0, 0, 1, 9},
					{-3.7, 3.75, -4.7, 0, 0, 0, 1, 2},
					{3.4, -9.8, -0.7, 0, 0, 0, 1, 6},
					{-8.5, -9, 9, 0, 0, 0, 1, 7},
				}
			},
			{"alarm_hack",
				{
					{1.4, 2.97, 3.21, 0.008, -0.699, 0.714, -0.008, 2},
				}
			},
			{"alarm_hack_no_sound",
				{
					{5.48, -16.32, 9.03, 0.508, 0.509, -0.491, 0.490, 9},
					{-5.25, 3.4, -0.8, 0.005, 0.707, 0.707, 0.005, 2},
					{0.07, 3.40, -5.50, 0, 0, 0.724, 0.689, 3},
					{2.1, -10.2, 0.7, 0.005, 0.707, 0.707, 0.005, 6},
					{-1.446, -10.43, 10.489, 0, 0, -0.689, 0.724, 7},
				}
			},
		}
	},
	-- Detachment HQ
	{"hq_s04",
		{
			{"alarm_destruct",
				{
					{0, 4.2, 1.8, 0, 0, 0, 1, 2},
					{4.5, -1.65, -8.3, 0, 0, 0, 1, 5},
					{-3.5, -8.65, -5.6, 0, 0, 0, 1, 7},
					{-7.6, -9, 12, 0, 0, 0, 1, 8},
					{15.49, -5.01, -3.48, 0, 0, -0.700, 0.713, 10},
				}
			},
			{"alarm_destruct_no_sound",
				{
					{15.5, -9, -1.8, 0, 0, 0, 1, 9},
					{-3.5, 4.25, -5.5, 0, 0, 0, 1, 3},
					{4.5, -1.65, -0.9, 0, 0, 0, 1, 5},
					{-3.5, -8.65, -5.6, 0, 0, 0, 1, 7},
					{10.2, -9, 12, 0, 0, 0, 1, 8},
					{15.5, -9.7, -3.9, 0, 0, -0.700, 0.713, 10},
				}
			},
			{"alarm_hack",
				{
					{5.24, 3.29, 3.03, 0.011, -0.681, 0.731, -0.010, 2},
				}
			},
			{"alarm_hack_no_sound",
				{
					{18.74, -10.18, 6.98, -0.013, 0.707, -0.706, -0.013, 9},
					{1.8, -9, 10, 0, 0, 0, 1, 8},
					{0.4, -5, -3, 0.005, 0.707, 0.707, 0.005, 5},
					{0.525, -9.34, -5.55, -0.013, 0.707, -0.706, 0.012, 7},
					{0.04, 3.31, -5.49, 0.018, -0.018, 0.702, 0.710, 3},
					{15.5, -3.5, -9.8, 0, 0, 0, 1, 10},
				}
			},
		}
	}
}


