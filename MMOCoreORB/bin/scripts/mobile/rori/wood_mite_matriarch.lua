wood_mite_matriarch = Creature:new {
	objectName = "@mob/creature_names:wood_mite_matriarch",
	socialGroup = "mite",
	faction = "",
	level = 15,
	chanceHit = 0.3,
	damageMin = 140,
	damageMax = 150,
	baseXp = 831,
	baseHAM = 2000,
	baseHAMmax = 2400,
	armor = 0,
	resists = {125,115,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 10,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/wood_mite_matriarch.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	scale = 1.1,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(wood_mite_matriarch, "wood_mite_matriarch")
