nym_guard_elite = Creature:new {
	objectName = "@mob/creature_names:nym_guard_elite",
	socialGroup = "nym",
	pvpFaction = "nym",
	faction = "nym",
	level = 38,
	chanceHit = 0.43,
	damageMin = 335,
	damageMax = 380,
	baseXp = 3824,
	baseHAM = 9100,
	baseHAMmax = 11100,
	armor = 2,
	resists = {15,15,15,15,60,-1,-1,-1,-1},
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

	templates = {"object/mobile/dressed_nym_guard_elite_rod_m.iff",
				"object/mobile/dressed_nym_guard_elite_nikto_m.iff",
				"object/mobile/dressed_nym_guard_elite_hum_m.iff"},
	lootGroups = {
	    {
			groups = {
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

CreatureTemplates:addCreatureTemplate(nym_guard_elite, "nym_guard_elite")