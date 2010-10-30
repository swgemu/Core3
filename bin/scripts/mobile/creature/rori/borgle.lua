borgle = Creature:new {
	objectName = "@monster_name:borgle",
	socialGroup = "Borgle",
	pvpFaction = "",
	faction = "",
	level = 12,
	chanceHit = 0.290000,
	damageMin = 120,
	damageMax = 130,
	baseXp = 514,
	baseHAM = 1100,
	baseHAMmax = 1100,
	armor = 0,
	resists = {0,15,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 5,
	hideType = "hide_leathery",
	hideAmount = 5,
	boneType = "bone_avian",
	boneAmount = 5,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/borgle.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(borgle, "borgle")