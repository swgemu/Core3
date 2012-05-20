pubam_chieftan = Creature:new {
	objectName = "@mob/creature_names:pubam_chieftan",
	socialGroup = "pubam",
	pvpFaction = "pubam",
	faction = "pubam",
	level = 51,
	chanceHit = 0.6,
	damageMin = 445,
	damageMax = 600,
	baseXp = 5007,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {-1,-1,70,70,70,70,70,100,-1},
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
			"object/mobile/dulok_male.iff",
			"object/mobile/dulok_female.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(pubam_chieftan, "pubam_chieftan")