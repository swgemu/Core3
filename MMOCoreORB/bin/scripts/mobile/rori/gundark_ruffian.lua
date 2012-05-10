gundark_ruffian = Creature:new {
	objectName = "@mob/creature_names:gundark_ruffian",
	socialGroup = "gundark_gang",
	pvpFaction = "thug",
	faction = "thug",
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

	templates = {
		"object/mobile/dressed_ruffian_zabrak_female_01.iff",
		"object/mobile/dressed_ruffian_zabrak_male_01.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 5000000},
				{group = "tailor_components", chance = 500000},
				{group = "loot_kits", chance = 4500000}
			},
			lootChance = 5500000
		}					
	},
	weapons = {"pirate_weapons_light"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(gundark_ruffian, "gundark_ruffian")