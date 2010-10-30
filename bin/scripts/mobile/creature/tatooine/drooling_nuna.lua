drooling_nuna = Creature:new {
	objectName = "@mob/creature_names:dwarf_nuna_drooling",
	socialGroup = "Dwarf Nuna",
	pvpFaction = "",
	faction = "",
	level = 6,
	chanceHit = 0.250000,
	damageMin = 80,
	damageMax = 90,
	baseXp = 147,
	baseHAM = 150,
	baseHAMmax = 150,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 2,
	hideType = "hide_leathery",
	hideAmount = 3,
	boneType = "bone_avian",
	boneAmount = 1,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/nuna.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(drooling_nuna, "drooling_nuna")