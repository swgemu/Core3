thracken_sal_solo = Creature:new {
	objectName = "",
	customName = "Thracken Sal Solo",
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
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_noble_old_human_male_02.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	outfit = "thracken_sal_solo_outfit",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(thracken_sal_solo, "thracken_sal_solo")
