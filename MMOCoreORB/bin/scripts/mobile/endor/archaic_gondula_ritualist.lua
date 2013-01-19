archaic_gondula_ritualist = Creature:new {
	objectName = "@mob/creature_names:archaic_gondula_ritualist",
	socialGroup = "gondula_tribe",
	pvpFaction = "gondula_tribe",
	faction = "gondula_tribe",
	level = 30,
	chanceHit = 0.39,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3005,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {0,0,0,50,50,-1,-1,-1,-1},
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
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_ewok_f_02.iff",
		"object/mobile/dressed_ewok_f_10.iff",
		"object/mobile/dressed_ewok_f_11.iff",
		"object/mobile/dressed_ewok_m_02.iff"},
	lootGroups = {
		 {
	        groups = {
				{group = "ewok", chance = 3300000}
			},
			lootChance = 1000000
		}
	},
	weapons = {"ewok_weapons"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster)
}

CreatureTemplates:addCreatureTemplate(archaic_gondula_ritualist, "archaic_gondula_ritualist")
