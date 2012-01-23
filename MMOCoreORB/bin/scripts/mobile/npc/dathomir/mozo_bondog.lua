mozo_bondog = Creature:new {
	objectName = "",
	customName = "Mozo Bondog",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
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

	templates = {"object/mobile/dressed_mozo_bondog.iff"},
	lootgroups = {},
	weapons = {"rebel_weapons_light"},
	conversationTemplate = "mozo_bondog_convotemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(mozo_bondog, "mozo_bondog")