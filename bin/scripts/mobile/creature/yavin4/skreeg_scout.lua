skreeg_scout = Creature:new {
	objectName = "@mob/creature_names:skreeg_scout",
	socialGroup = "Skreeg",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.320000,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1257,
	baseHAM = 3900,
	baseHAMmax = 3900,
	armor = 0,
	resists = {0,15,0,-1,0,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 5,
	hideType = "hide_bristley",
	hideAmount = 9,
	boneType = "bone_mammal",
	boneAmount = 7,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/skreeg.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(skreeg_scout, "skreeg_scout")