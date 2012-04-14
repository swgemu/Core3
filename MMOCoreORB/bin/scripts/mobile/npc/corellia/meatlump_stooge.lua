meatlump_stooge = Creature:new {
	objectName = "@mob/creature_names:meatlump_stooge",
	socialGroup = "Meatlump",
	pvpFaction = "Meatlump",
	faction = "",
	level = 7,
	chanceHit = 0.260000,
	damageMin = 55,
	damageMax = 65,
	baseXp = 187,
	baseHAM = 270,
	baseHAMmax = 330,
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

CreatureTemplates:addCreatureTemplate(meatlump_stooge, "meatlump_stooge")