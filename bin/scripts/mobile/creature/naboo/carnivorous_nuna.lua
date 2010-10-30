carnivorous_nuna = Creature:new {
	objectName = "@mob/creature_names:carnivorous_nuna",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 13,
	chanceHit = 0.300000,
	damageMin = 140,
	damageMax = 150,
	baseXp = 714,
	baseHAM = 1700,
	baseHAMmax = 1700,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 5,
	hideType = "hide_leathery",
	hideAmount = 5,
	boneType = "bone_avian",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/nuna.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(carnivorous_nuna, "carnivorous_nuna")