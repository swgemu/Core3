graul_marauder = Creature:new {
	objectName = "@mob/creature_names:graul_marauder",
	socialGroup = "Graul",
	pvpFaction = "",
	faction = "",
	level = 173,
	chanceHit = 1.080000,
	damageMin = 1095,
	damageMax = 1900,
	baseXp = 16411,
	baseHAM = 100000,
	baseHAMmax = 100000,
	armor = 0,
	resists = {75,55,90,90,90,55,55,55,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 1000,
	boneType = "bone_mammal",
	boneAmount = 950,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/graul.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"creatureareableeding",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(graul_marauder, "graul_marauder")