meatlump_cretin = Creature:new {
	objectName = "@mob/creature_names:meatlump_cretin",
	socialGroup = "Meatlump",
	pvpFaction = "Meatlump",
	faction = "",
	level = 9,
	chanceHit = 0.270000,
	damageMin = 80,
	damageMax = 90,
	baseXp = 292,
	baseHAM = 675,
	baseHAMmax = 825,
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
				{group = "junk", chance = 5500000},
				{group = "crystals", chance = 4000000},
				{group = "tailor_components", chance = 500000}
			},
			lootChance = 4500000
		}
	},
	weapons = {"pirate_weapons_light"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(meatlump_cretin, "meatlump_cretin")