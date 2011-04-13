guf_drolg_female = Creature:new {
	objectName = "@mob/creature_names:guf_drolg_female",
	socialGroup = "Guf Drolg",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.300000,
	damageMin = 150,
	damageMax = 160,
	baseXp = 831,
	baseHAM = 2200,
	baseHAMmax = 2200,
	armor = 0,
	resists = {15,5,0,0,0,0,0,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 325,
	hideType = "hide_leathery",
	hideAmount = 265,
	boneType = "bone_mammal",
	boneAmount = 190,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/guf_drolg.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(guf_drolg_female, "guf_drolg_female")