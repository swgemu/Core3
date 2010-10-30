tabage = Creature:new {
	objectName = "@mob/creature_names:tabage",
	socialGroup = "Tabage",
	pvpFaction = "",
	faction = "",
	level = 11,
	chanceHit = 0.290000,
	damageMin = 120,
	damageMax = 130,
	baseXp = 356,
	baseHAM = 1100,
	baseHAMmax = 1100,
	armor = 0,
	resists = {0,0,0,10,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 18,
	hideType = "hide_bristley",
	hideAmount = 24,
	boneType = "bone_mammal",
	boneAmount = 7,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = NONE,
	diet = CARNIVORE,

	templates = {"object/mobile/tabage.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(tabage, "tabage")