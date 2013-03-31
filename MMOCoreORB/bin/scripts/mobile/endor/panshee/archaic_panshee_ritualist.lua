archaic_panshee_ritualist = Creature:new {
	objectName = "@mob/creature_names:archaic_panshee_ritualist",
	socialGroup = "panshee_tribe",
	pvpFaction = "panshee_tribe",
	faction = "panshee_tribe",
	level = 60,
	chanceHit = 0.6,
	damageMin = 445,
	damageMax = 600,
	baseXp = 5738,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {25,25,45,45,45,45,45,45,-1},
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
				{group = "ewok", chance = 10000000}
			},
			lootChance = 3000000
		}
	},
	weapons = {"ewok_weapons"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,brawlernovice)
}

CreatureTemplates:addCreatureTemplate(archaic_panshee_ritualist, "archaic_panshee_ritualist")
