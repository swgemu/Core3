tabage_protector = Creature:new {
	objectName = "@mob/creature_names:tabage_protector",
	socialGroup = "Tabage",
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
	resists = {0,15,0,0,0,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 14,
	hideType = "hide_leathery",
	hideAmount = 14,
	boneType = "bone_mammal",
	boneAmount = 14,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/tabage.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"mildpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(tabage_protector, "tabage_protector")