enraged_tabage_mother = Creature:new {
	objectName = "@mob/creature_names:enraged_tabage_mother",
	socialGroup = "Tabage",
	pvpFaction = "",
	faction = "",
	level = 17,
	chanceHit = 0.310000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1257,
	baseHAM = 3200,
	baseHAMmax = 3200,
	armor = 0,
	resists = {0,15,0,0,0,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 16,
	hideType = "hide_bristley",
	hideAmount = 16,
	boneType = "bone_mammal",
	boneAmount = 16,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/tabage.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(enraged_tabage_mother, "enraged_tabage_mother")