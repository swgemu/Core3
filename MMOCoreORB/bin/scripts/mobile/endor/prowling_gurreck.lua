prowling_gurreck = Creature:new {
	objectName = "@mob/creature_names:gurreck_prowler",
	socialGroup = "gurreck",
	faction = "",
	level = 45,
	chanceHit = 0.44,
	damageMin = 365,
	damageMax = 440,
	baseXp = 4370,
	baseHAM = 8900,
	baseHAMmax = 10900,
	armor = 0,
	resists = {165,165,30,30,-1,30,30,30,-1},
	meatType = "meat_carnivore",
	meatAmount = 75,
	hideType = "hide_wooly",
	hideAmount = 45,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/gurreck_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/gurreck_hue.iff",
	scale = 1.1,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack",""},
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(prowling_gurreck, "prowling_gurreck")
