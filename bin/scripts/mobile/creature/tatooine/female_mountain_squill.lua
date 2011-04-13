female_mountain_squill = Creature:new {
	objectName = "@mob/creature_names:female_mountain_squill",
	socialGroup = "Mountain Squill",
	pvpFaction = "",
	faction = "",
	level = 34,
	chanceHit = 0.400000,
	damageMin = 305,
	damageMax = 320,
	baseXp = 3370,
	baseHAM = 9550,
	baseHAMmax = 9550,
	armor = 0,
	resists = {30,45,0,-1,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 4,
	hideType = "hide_leathery",
	hideAmount = 3,
	boneType = "bone_mammal",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/mountain_squill.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(female_mountain_squill, "female_mountain_squill")