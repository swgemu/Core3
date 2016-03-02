cannibal_dewback = Creature:new {
	objectName = "@mob/creature_names:dewback_cannibal",
	socialGroup = "dewback",
	faction = "",
	level = 21,
	chanceHit = 0.33,
	damageMin = 230,
	damageMax = 240,
	baseXp = 1609,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {10,10,10,-1,10,-1,10,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 340,
	hideType = "hide_leathery",
	hideAmount = 260,
	boneType = "bone_mammal",
	boneAmount = 185,
	milk = 0,
	tamingChance = 0,
	ferocity = 6,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/dewback_hue.iff"},
	scale = 1.1,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"dizzyattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(cannibal_dewback, "cannibal_dewback")
