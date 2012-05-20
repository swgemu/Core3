rorgungan_boss = Creature:new {
	objectName = "@mob/creature_names:rorgungan_boss",
	socialGroup = "rorgungan",
	pvpFaction = "rorgungan",
	faction = "rorgungan",
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

	templates = {"object/mobile/gungan_s03_male.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 3000000},
				{group = "tailor_components", chance = 500000},
				{group = "loot_kit_parts", chance = 1500000},
				{group = "color_crystals", chance = 200000},
				{group = "crystals_poor", chance = 200000}
			},
			lootChance = 3200000
		}					
	},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(rorgungan_boss, "rorgungan_boss")