blurrg_pup = Creature:new {
	objectName = "@mob/creature_names:blurrg_pup",
	socialGroup = "blurrg",
	faction = "",
	level = 15,
	chanceHit = 0.31,
	damageMin = 160,
	damageMax = 170,
	baseXp = 831,
	baseHAM = 2400,
	baseHAMmax = 3000,
	armor = 0,
	resists = {5,5,5,5,5,5,5,5,-1},
	meatType = "meat_carnivore",
	meatAmount = 30,
	hideType = "hide_leathery",
	hideAmount = 20,
	boneType = "bone_avian",
	boneAmount = 20,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/blurrg_pup.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	scale = 0.7,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(blurrg_pup, "blurrg_pup")
