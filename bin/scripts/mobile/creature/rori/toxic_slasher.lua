toxic_slasher = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:vir_vur_toxic_slasher",
	socialGroup = "Vir Vur",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.310000,
	damageMin = 170,
	damageMax = 180,
	range = 0,
	baseXp = 831,
	baseHAM = 1300,
	armor = 0,
	resists = {10,0,0,0,0,-1,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 10,
	hideType = "hide_wooly",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 2,
	milk = 0.000000,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"mildpoison",""},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(toxic_slasher, "toxic_slasher")
