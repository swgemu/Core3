ragtag_thug = Creature:new {
	objectName = "@mob/creature_names:ragtag_thug",
	socialGroup = "ragtag",
	pvpFaction = "thug",
	faction = "thug",
	level = 8,
	chanceHit = 0.270000,
	damageMin = 70,
	damageMax = 75,
	baseXp = 235,
	baseHAM = 405,
	baseHAMmax = 495,
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
	pvpBitmask = NONE,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_hooligan_rodian_female_01.iff",
				"object/mobile/dressed_criminal_thug_human_female_01.iff"
				},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 5500000},
				{group = "loot_kits", chance = 3500000},
				{group = "crystals_poor", chance = 500000},
				{group = "tailor_components", chance = 500000}
			},
			lootChance = 6500000
		}
	},
	weapons = {"pirate_weapons_medium"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(ragtag_thug, "ragtag_thug")
