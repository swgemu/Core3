boar_wolf_ravager = Creature:new {
	objectName = "@mob/creature_names:boar_wolf_ravager",
	socialGroup = "Boar Wolf",
	pvpFaction = "",
	faction = "",
	level = 34,
	chanceHit = 0.4,
	damageMin = 305,
	damageMax = 320,
	baseXp = 3460,
	baseHAM = 8600,
	baseHAMmax = 10500,
	armor = 0,
	resists = {50,20,50,20,20,20,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/boar_wolf.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(boar_wolf_ravager, "boar_wolf_ravager")