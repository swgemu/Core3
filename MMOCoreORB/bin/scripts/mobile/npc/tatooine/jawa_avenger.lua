jawa_avenger = Creature:new {
	objectName = "@mob/creature_names:jawa_avenger",
	socialGroup = "Jawa",
	pvpFaction = "Jawa",
	faction = "",
	level = 21,
	chanceHit = 0.33,
	damageMin = 190,
	damageMax = 200,
	baseXp = 2006,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {20,15,0,0,-1,0,0,-1,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/jawa_male.iff"},
	lootgroups = {},
	weapons = {"rebel_weapons_medium"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(jawa_avenger, "jawa_avenger")