mammoth_thune = Creature:new {
	objectName = "@mob/creature_names:mammoth_thune",
	socialGroup = "thune",
	faction = "",
	level = 129,
	chanceHit = 4.75,
	damageMin = 720,
	damageMax = 1150,
	baseXp = 12235,
	baseHAM = 81000,
	baseHAMmax = 99000,
	armor = 2,
	resists = {35,35,25,25,25,25,25,25,-1},
	meatType = "meat_herbivore",
	meatAmount = 225,
	hideType = "hide_wooly",
	hideAmount = 190,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/thune_hue.iff"},
	scale = 1.4,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack",""},
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(mammoth_thune, "mammoth_thune")
