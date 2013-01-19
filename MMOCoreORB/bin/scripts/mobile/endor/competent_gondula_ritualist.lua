competent_gondula_ritualist = Creature:new {
	objectName = "@mob/creature_names:competent_gundula_ritualist",
	socialGroup = "gondula_tribe",
	pvpFaction = "gondula_tribe",
	faction = "gondula_tribe",
	level = 17,
	chanceHit = 0.32,
	damageMin = 150,
	damageMax = 170,
	baseXp = 1102,
	baseHAM = 3500,
	baseHAMmax = 4300,
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

CreatureTemplates:addCreatureTemplate(competent_gondula_ritualist, "competent_gondula_ritualist")
