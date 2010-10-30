female_narglatch = Creature:new {
	objectName = "@mob/creature_names:narglatch_female",
	socialGroup = "Narglatch",
	pvpFaction = "",
	faction = "",
	level = 23,
	chanceHit = 0.350000,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2443,
	baseHAM = 6550,
	baseHAMmax = 6550,
	armor = 0,
	resists = {25,0,0,0,-1,-1,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/narglatch_female.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(female_narglatch, "female_narglatch")