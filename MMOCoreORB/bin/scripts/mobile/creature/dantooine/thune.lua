thune = Creature:new {
	objectName = "@mob/creature_names:thune",
	socialGroup = "Thune",
	pvpFaction = "",
	faction = "",
	level = 26,
	chanceHit = 0.36,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2637,
	baseHAM = 7700,
	baseHAMmax = 10000,
	armor = 0,
	resists = {20,15,15,15,15,15,15,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 115,
	hideType = "hide_wooly",
	hideAmount = 125,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/thune.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(thune, "thune")