mammoth_thune = Creature:new {
	objectName = "@mob/creature_names:mammoth_thune",
	socialGroup = "Thune",
	pvpFaction = "",
	faction = "",
	level = 129,
	chanceHit = 4.750000,
	damageMin = 720,
	damageMax = 1150,
	baseXp = 12235,
	baseHAM = 90000,
	baseHAMmax = 90000,
	armor = 0,
	resists = {35,35,0,0,0,0,0,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 225,
	hideType = "hide_wooly",
	hideAmount = 190,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/thune.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mammoth_thune, "mammoth_thune")