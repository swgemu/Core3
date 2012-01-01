mammoth_thune = Creature:new {
	objectName = "@mob/creature_names:mammoth_thune",
	socialGroup = "Thune",
	pvpFaction = "",
	faction = "",
	level = 129,
	chanceHit = 4.75,
	damageMin = 720,
	damageMax = 1150,
	baseXp = 12235,
	baseHAM = 81000,
	baseHAMmax = 99000,
	armor = 0,
	resists = {55,55,45,45,45,45,45,45,-1},
	meatType = "meat_herbivore",
	meatAmount = 225,
	hideType = "hide_wooly",
	hideAmount = 190,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/thune.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mammoth_thune, "mammoth_thune")