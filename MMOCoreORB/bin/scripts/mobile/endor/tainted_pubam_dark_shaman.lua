tainted_pubam_dark_shaman = Creature:new {
	objectName = "@mob/creature_names:tainted_pubam_dark_shaman",
	socialGroup = "pubam",
	pvpFaction = "pubam",
	faction = "pubam",
	level = 35,
	chanceHit = 0.41,
	damageMin = 355,
	damageMax = 420,
	baseXp = 3551,
	baseHAM = 8200,
	baseHAMmax = 10000,
	armor = 0,
	resists = {15,15,15,40,40,40,40,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
			"object/mobile/dulok_male.iff",
			"object/mobile/dulok_female.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(tainted_pubam_dark_shaman, "tainted_pubam_dark_shaman")
