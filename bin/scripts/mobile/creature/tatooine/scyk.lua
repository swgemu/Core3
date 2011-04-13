scyk = Creature:new {
	objectName = "@mob/creature_names:scyk",
	socialGroup = "Scyk",
	pvpFaction = "",
	faction = "",
	level = 12,
	chanceHit = 0.290000,
	damageMin = 130,
	damageMax = 140,
	baseXp = 514,
	baseHAM = 1300,
	baseHAMmax = 1300,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 40,
	hideType = "hide_bristley",
	hideAmount = 25,
	boneType = "bone_mammal",
	boneAmount = 18,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/scyk.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"mediumpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(scyk, "scyk")