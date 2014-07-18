thrackan_sal_solo = Creature:new {
	objectName = "",
	customName = "Thrackan Sal Solo",
	socialGroup = "townsperson",
	pvpFaction = "townsperson",
	faction = "townsperson",
	level = 100,
	chanceHit = 1,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 9429,
	baseHAM = 24000,
	baseHAMmax = 30000,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = PACK,
	optionsBitmask = 136,
	diet = HERBIVORE,

	templates = {"object/mobile/mos_taike_mayor.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "thrackan_sal_solo_mission_giver_convotemplate",
	outfit = "thracken_sal_solo_outfit",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(thrackan_sal_solo, "thrackan_sal_solo")
