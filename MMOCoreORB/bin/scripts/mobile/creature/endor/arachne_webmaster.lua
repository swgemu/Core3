arachne_webmaster = Creature:new {
	objectName = "@mob/creature_names:arachne_webmaster",
	socialGroup = "Arachne",
	pvpFaction = "",
	faction = "",
	level = 50,
	chanceHit = 0.5,
	damageMin = 405,
	damageMax = 520,
	baseXp = 4916,
	baseHAM = 9900,
	baseHAMmax = 12100,
	armor = 1,
	resists = {35,35,-1,60,60,-1,60,-1,-1},
	meatType = "meat_insect",
	meatAmount = 30,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/angler.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"strongpoison",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(arachne_webmaster, "arachne_webmaster")