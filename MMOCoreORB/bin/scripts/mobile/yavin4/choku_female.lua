choku_female = Creature:new {
	objectName = "@mob/creature_names:choku_female",
	socialGroup = "choku",
	pvpFaction = "",
	faction = "",
	level = 13,
	chanceHit = 0.3,
	damageMin = 130,
	damageMax = 140,
	baseXp = 609,
	baseHAM = 2000,
	baseHAMmax = 2400,
	armor = 0,
	resists = {15,0,0,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 10,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 8,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/choku.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(choku_female, "choku_female")