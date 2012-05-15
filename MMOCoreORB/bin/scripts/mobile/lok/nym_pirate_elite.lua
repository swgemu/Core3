nym_pirate_elite = Creature:new {
	objectName = "@mob/creature_names:nym_pirate_elite",
	socialGroup = "nym",
	pvpFaction = "nym",
	faction = "nym",
	level = 31,
	chanceHit = 0.39,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3188,
	baseHAM = 8600,
	baseHAMmax = 10600,
	armor = 1,
	resists = {15,15,15,15,40,-1,-1,-1,-1},
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

	templates = {"object/mobile/dressed_nym_pirate_elite_rod_m.iff",
				"object/mobile/dressed_nym_pirate_elite_nikto_m.iff",
				"object/mobile/dressed_nym_pirate_elite_hum_m.iff",
				"object/mobile/dressed_nym_pirate_elite_wee_m.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "nyms_common", chance = 2500000},
				{group = "pistols", chance = 2500000},
				{group = "rifles", chance = 2500000},
				{group = "tailor_components", chance = 2500000}
			},
			lootChance = 6500000
		}
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(nym_pirate_elite, "nym_pirate_elite")