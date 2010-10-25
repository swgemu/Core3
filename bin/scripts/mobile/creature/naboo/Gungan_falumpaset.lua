Gungan_falumpaset = Creature:new {
	objectName = "Gungan falumpaset",
	socialGroup = "Gungan ",
	pvpFaction = "",
	faction = "",
	level = 26,
	chanceHit = 0.360000,
	damageMin = 250,
	damageMax = 260,
	range = 25,
	baseXp = 2637,
	baseHAM = 8550,
	armor = 0,
	resists = {25,0,0,35,35,-1,-1,1,-1},
	meatType = "meat_domesticated",
	meatAmount = 230,
	hideType = "hide_leathery",
	hideAmount = 130,
	boneType = "bone_mammal",
	boneAmount = 80,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(Gungan_falumpaset, "Gungan_falumpaset")
