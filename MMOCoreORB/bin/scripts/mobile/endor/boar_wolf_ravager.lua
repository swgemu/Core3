boar_wolf_ravager = Creature:new {
	objectName = "@mob/creature_names:boar_wolf_ravager",
	socialGroup = "boar",
	faction = "",
	level = 34,
	chanceHit = 0.4,
	damageMin = 305,
	damageMax = 320,
	baseXp = 3460,
	baseHAM = 8600,
	baseHAMmax = 10500,
	armor = 0,
	resists = {150,20,150,20,20,20,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 80,
	hideType = "hide_leathery",
	hideAmount = 55,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/boar_wolf_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/boar_wolf_hue.iff",
	scale = 1.1,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""},
		{"blindattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(boar_wolf_ravager, "boar_wolf_ravager")
