flail_butcher = Creature:new {
	objectName = "@mob/creature_names:flail_butcher",
	socialGroup = "Flail",
	pvpFaction = "Flail",
	faction = "",
	level = 22,
	chanceHit = 0.350000,
	damageMin = 220,
	damageMax = 230,
	baseXp = 2219,
	baseHAM = 6300,
	baseHAMmax = 7700,
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
	pvpBitmask = ATTACKABLE + AGGRESSIVE,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {},
	lootGroups = {
			{
			groups = {
				{group = "junk", chance = 5500000},
				{group = "carbines", chance = 4000000},
				{group = "crystals", chance = 500000}
			},
			lootChance = 4500000
		}
	},
	weapons = {"pirate_weapons_medium"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(flail_butcher, "flail_butcher")