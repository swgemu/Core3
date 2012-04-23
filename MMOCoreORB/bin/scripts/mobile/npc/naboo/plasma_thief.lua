plasma_thief = Creature:new {
	objectName = "@mob/creature_names:plasma_thief",
	socialGroup = "Plasma Thief",
	pvpFaction = "Plasma Thief",
	faction = "",
	level = 3,
	chanceHit = 0.230000,
	damageMin = 35,
	damageMax = 45,
	baseXp = 62,
	baseHAM = 90,
	baseHAMmax = 110,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
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
	weapons = {"pirate_weapons_light"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(plasma_thief, "plasma_thief")