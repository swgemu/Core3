donkuwah_chieftain = Creature:new {
	objectName = "@mob/creature_names:donkuwah_chieftan",
	socialGroup = "Donkuwah Tr.",
	pvpFaction = "Donkuwah Tr.",
	faction = "",
	level = 58,
	chanceHit = 0.57,
	damageMin = 430,
	damageMax = 570,
	baseXp = 5647,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 0,
	resists = {15,50,0,0,0,-1,-1,0,-1},
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
	weapons = {""},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(donkuwah_chieftain, "donkuwah_chieftain")