pubam_dark_shaman = Creature:new {
	objectName = "@mob/creature_names:pubam_dark_shaman",
	socialGroup = "pubam",
	pvpFaction = "pubam",
	faction = "pubam",
	level = 48,
	chanceHit = 0.47,
	damageMin = 390,
	damageMax = 490,
	baseXp = 4734,
	baseHAM = 9400,
	baseHAMmax = 11400,
	armor = 1,
	resists = {35,35,0,60,60,60,-1,80,-1},
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
	creatureBitmask = PACK + KILLER + HEALER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	aiTemplate = "default",

	templates = {
			"object/mobile/dulok_male.iff",
			"object/mobile/dulok_female.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(pubam_dark_shaman, "pubam_dark_shaman")