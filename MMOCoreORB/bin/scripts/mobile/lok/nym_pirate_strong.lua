nym_pirate_strong = Creature:new {
	objectName = "@mob/creature_names:nym_pirate_strong",
	socialGroup = "nym",
	pvpFaction = "nym",
	faction = "nym",
	level = 26,
	chanceHit = 0.36,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2730,
	baseHAM = 7700,
	baseHAMmax = 9400,
	armor = 0,
	resists = {25,10,25,25,25,-1,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	aiTemplate = "default",

	templates = {"object/mobile/dressed_nym_pirate_strong_hum_f.iff", 
				"object/mobile/dressed_nym_pirate_strong_rod_m.iff",
				"object/mobile/dressed_nym_pirate_strong_nikto_m.iff",
				"object/mobile/dressed_nym_pirate_strong_hum_m.iff",
				"object/mobile/dressed_nym_pirate_strong_rod_f.iff",
				"object/mobile/dressed_nym_pirate_strong_wee_m.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 6500000},
				{group = "nyms_common", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "carbines", chance = 1000000},
				{group = "tailor_components", chance = 500000}
			},
			lootChance = 3500000
		}
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(nym_pirate_strong, "nym_pirate_strong")