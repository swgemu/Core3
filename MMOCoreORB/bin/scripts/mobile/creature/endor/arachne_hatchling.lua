arachne_hatchling = Creature:new {
	objectName = "@mob/creature_names:arachne_hatchling",
	socialGroup = "Arachne",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.320000,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1257,
	baseHAM = 3900,
	baseHAMmax = 3900,
	armor = 0,
	resists = {10,10,0,-1,-1,0,85,0,-1},
	meatType = "meat_insect",
	meatAmount = 1,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/arachne_hatchling.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"mediumpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(arachne_hatchling, "arachne_hatchling")