rorgungan_boss = Creature:new {
	objectName = "@mob/creature_names:rorgungan_boss",
	socialGroup = "Rorgungan",
	pvpFaction = "Rorgungan",
	faction = "",
	level = 22,
	chanceHit = 0.330000,
	damageMin = 190,
	damageMax = 200,
	baseXp = 2006,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {25,25,0,-1,30,0,-1,-1,-1},
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
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 4000000},
				{group = "tailor_components", chance = 500000},
				{group = "loot_kits", chance = 3500000},
				{group = "color_crystals", chance = 1000000},
				{group = "crystals_poor", chance = 1000000}
			},
			lootChance = 4800000
		}					
	},
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(rorgungan_boss, "rorgungan_boss")