midnight_vir_vur = Creature:new {
	objectName = "@mob/creature_names:midnight_vir_vur",
	socialGroup = "Vir Vur",
	pvpFaction = "",
	faction = "",
	level = 16,
	chanceHit = 0.320000,
	damageMin = 160,
	damageMax = 170,
	baseXp = 960,
	baseHAM = 3900,
	baseHAMmax = 3900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 10,
	hideType = "hide_wooly",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/vir_vur.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(midnight_vir_vur, "midnight_vir_vur")