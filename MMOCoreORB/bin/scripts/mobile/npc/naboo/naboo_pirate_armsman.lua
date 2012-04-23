naboo_pirate_armsman = Creature:new {
	objectName = "@mob/creature_names:naboo_pirate_armsman",
	socialGroup = "Naboo Pirate",
	pvpFaction = "Naboo Pirate",
	faction = "",
	level = 13,
	chanceHit = 0.300000,
	damageMin = 150,
	damageMax = 160,
	baseXp = 714,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 4000000},
				{group = "tailor_components", chance = 2000000},
				{group = "loot_kits", chance = 4000000}
			},
			lootChance = 4800000
		}				
	},
	weapons = {"pirate_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(naboo_pirate_armsman, "naboo_pirate_armsman")