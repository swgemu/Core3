flail_slayer = Creature:new {
	objectName = "@mob/creature_names:flail_slayer",
	socialGroup = "Flail",
	pvpFaction = "Flail",
	faction = "",
	level = 20,
	chanceHit = 0.330000,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1803,
	baseHAM = 5000,
	baseHAMmax = 6100,
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
				{group = "pistols", chance = 4000000},
				{group = "tailor_components", chance = 500000}
			},
			lootChance = 4500000
		}
	},
	weapons = {"pirate_weapons_medium"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(flail_slayer, "flail_slayer")