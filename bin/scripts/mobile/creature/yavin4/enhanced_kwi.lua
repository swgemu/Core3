enhanced_kwi = Creature:new {
	objectName = "@mob/creature_names:geonosian_enhanced_kwi",
	socialGroup = "Geon. Monster",
	pvpFaction = "",
	faction = "",
	level = 106,
	chanceHit = 1.750000,
	damageMin = 690,
	damageMax = 1090,
	baseXp = 10081,
	baseHAM = 30000,
	baseHAMmax = 30000,
	armor = 0,
	resists = {40,40,0,40,0,0,0,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 100,
	hideType = "hide_leathery",
	hideAmount = 85,
	boneType = "bone_mammal",
	boneAmount = 75,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = HERBIVORE,

	templates = {"object/mobile/kwi.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(enhanced_kwi, "enhanced_kwi")