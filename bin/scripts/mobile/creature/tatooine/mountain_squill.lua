mountain_squill = Creature:new {
	objectName = "@mob/creature_names:mountain_squill",
	socialGroup = "Mtn. Squill",
	pvpFaction = "",
	faction = "",
	level = 34,
	chanceHit = 0.410000,
	damageMin = 315,
	damageMax = 340,
	baseXp = 3279,
	baseHAM = 9700,
	baseHAMmax = 9700,
	armor = 0,
	resists = {0,0,0,-1,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 3,
	hideType = "hide_leathery",
	hideAmount = 3,
	boneType = "bone_mammal",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER,
	diet = CARNIVORE,

	templates = {"object/mobile/mountain_squill.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mountain_squill, "mountain_squill")