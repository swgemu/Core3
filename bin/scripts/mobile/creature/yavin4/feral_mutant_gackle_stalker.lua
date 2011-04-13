feral_mutant_gackle_stalker = Creature:new {
	objectName = "@mob/creature_names:feral_mutant_gackle_stalker",
	socialGroup = "Gacklebat",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.310000,
	damageMin = 160,
	damageMax = 170,
	baseXp = 831,
	baseHAM = 2700,
	baseHAMmax = 2700,
	armor = 0,
	resists = {15,15,0,-1,-1,-1,-1,-1,-1},
	meatType = "meat_avian",
	meatAmount = 9,
	hideType = "hide_leathery",
	hideAmount = 9,
	boneType = "bone_avian",
	boneAmount = 9,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/gackle_bat.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"milddisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(feral_mutant_gackle_stalker, "feral_mutant_gackle_stalker")