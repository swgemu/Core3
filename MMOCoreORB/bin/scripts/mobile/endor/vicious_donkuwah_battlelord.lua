vicious_donkuwah_battlelord = Creature:new {
	objectName = "@mob/creature_names:vicious_donkuwah_battlelord",
	socialGroup = "Donkuwah Tr.",
	pvpFaction = "Donkuwah Tr.",
	faction = "",
	level = 51,
	chanceHit = 0.51,
	damageMin = 425,
	damageMax = 560,
	baseXp = 5007,
	baseHAM = 10000,
	baseHAMmax = 12200,
	armor = 0,
	resists = {35,0,0,50,50,-1,0,-1,-1},
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

	templates = {"object/mobile/dulok_male.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(vicious_donkuwah_battlelord, "vicious_donkuwah_battlelord")