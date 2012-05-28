corsec_traitor = Creature:new {
	objectName = "@mob/creature_names:corsec_traitor",
	socialGroup = "rogue_corsec",
	pvpFaction = "rogue_corsec",
	faction = "rogue_corsec",
	level = 16,
	chanceHit = 0.31,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1102,
	baseHAM = 2900,
	baseHAMmax = 3500,
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_corsec_pilot_human_female_01.iff",
		"object/mobile/dressed_corsec_pilot_human_male_01.iff",
		"object/mobile/dressed_mercenary_destroyer_nikto_m.iff",
		"object/mobile/dressed_mercenary_elite_hum_m.iff",
		"object/mobile/dressed_mercenary_destroyer_hum_m.iff"
		},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 4000000},
				{group = "corsec_weapons", chance = 1500000},
				{group = "tailor_components", chance = 500000}
			},
			lootChance = 5000000
		}
	},
	weapons = {"corsec_police_weapons"},
	conversationTemplate = "",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(corsec_traitor, "corsec_traitor")
