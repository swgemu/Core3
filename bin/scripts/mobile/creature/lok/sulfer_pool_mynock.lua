sulfer_pool_mynock = Creature:new {
	objectName = "sulfer pool mynock",
	socialGroup = "Mynock",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.390000,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3005,
	baseHAM = 9300,
	baseHAMmax = 9300,
	armor = 0,
	resists = {-1,50,0,100,-1,0,100,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 57,
	hideType = "hide_leathery",
	hideAmount = 75,
	boneType = "bone_mammal",
	boneAmount = 27,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/riverside_sulfur_mynock.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(sulfer_pool_mynock, "sulfer_pool_mynock")