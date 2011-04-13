salt_mynock = Creature:new {
	objectName = "@monster_name:salt_mynock",
	socialGroup = "Mynock",
	pvpFaction = "",
	faction = "",
	level = 23,
	chanceHit = 0.350000,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2219,
	baseHAM = 6550,
	baseHAMmax = 6550,
	armor = 0,
	resists = {0,20,0,40,40,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 50,
	hideType = "hide_leathery",
	hideAmount = 70,
	boneType = "bone_mammal",
	boneAmount = 20,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/salt_mynock.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(salt_mynock, "salt_mynock")