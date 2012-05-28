arachne_widow = Creature:new {
	objectName = "@mob/creature_names:arachne_widow",
	socialGroup = "arachne",
	pvpFaction = "",
	faction = "",
	level = 58,
	chanceHit = 0.53,
	damageMin = 400,
	damageMax = 510,
	baseXp = 5647,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {40,40,5,70,80,5,80,-1,-1},
	meatType = "meat_insect",
	meatAmount = 30,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.01,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/angler.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"strongpoison",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(arachne_widow, "arachne_widow")