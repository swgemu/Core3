thune = Creature:new {
	objectName = "@monster_name:thune",
	socialGroup = "Thune",
	pvpFaction = "",
	faction = "",
	level = 26,
	chanceHit = 0.360000,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2637,
	baseHAM = 8550,
	baseHAMmax = 8550,
	armor = 0,
	resists = {20,0,0,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 115,
	hideType = "hide_wooly",
	hideAmount = 125,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/thune.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(thune, "thune")