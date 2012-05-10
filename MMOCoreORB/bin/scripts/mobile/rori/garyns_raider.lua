garyns_raider = Creature:new {
	objectName = "@mob/creature_names:garyn_raider",
	socialGroup = "garyn",
	pvpFaction = "garyn",
	faction = "garyn",
	level = 20,
	chanceHit = 0.33,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1609,
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
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_garyn_raider_twk_female_01.iff",
		"object/mobile/dressed_garyn_raider_twk_male_01.iff"},
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
	weapons = {"ranged_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(garyns_raider, "garyns_raider")