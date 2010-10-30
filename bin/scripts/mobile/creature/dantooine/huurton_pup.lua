huurton_pup = Creature:new {
	objectName = "@mob/creature_names:huurton_pup",
	socialGroup = "Huurton",
	pvpFaction = "",
	faction = "",
	level = 2,
	chanceHit = 0.210000,
	damageMin = 35,
	damageMax = 40,
	baseXp = 45,
	baseHAM = 75,
	baseHAMmax = 75,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 10,
	hideType = "hide_wooly",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 5,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/huurton_pup.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(huurton_pup, "huurton_pup")