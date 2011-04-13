boar_wolf_ravager = Creature:new {
	objectName = "@mob/creature_names:boar_wolf_ravager",
	socialGroup = "Boar Wolf",
	pvpFaction = "",
	faction = "",
	level = 34,
	chanceHit = 0.400000,
	damageMin = 305,
	damageMax = 320,
	baseXp = 3460,
	baseHAM = 9550,
	baseHAMmax = 9550,
	armor = 0,
	resists = {50,0,50,0,0,0,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/boar_wolf.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(boar_wolf_ravager, "boar_wolf_ravager")