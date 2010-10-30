choku_packmaster = Creature:new {
	objectName = "@mob/creature_names:choku_packmaster",
	socialGroup = "Choku",
	pvpFaction = "",
	faction = "",
	level = 21,
	chanceHit = 0.340000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1803,
	baseHAM = 6550,
	baseHAMmax = 6550,
	armor = 0,
	resists = {10,0,0,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 10,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 8,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/choku.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(choku_packmaster, "choku_packmaster")