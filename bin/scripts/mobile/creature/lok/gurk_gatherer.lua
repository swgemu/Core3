gurk_gatherer = Creature:new {
	objectName = "@mob/creature_names:gurk_gatherer",
	socialGroup = "Gurk",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.370000,
	damageMin = 270,
	damageMax = 280,
	baseXp = 3005,
	baseHAM = 9100,
	baseHAMmax = 9100,
	armor = 0,
	resists = {35,30,0,0,0,0,40,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 350,
	hideType = "hide_leathery",
	hideAmount = 275,
	boneType = "bone_mammal",
	boneAmount = 300,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/gurk.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(gurk_gatherer, "gurk_gatherer")