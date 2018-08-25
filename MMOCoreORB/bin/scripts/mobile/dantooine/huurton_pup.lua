huurton_pup = Creature:new {
	objectName = "@mob/creature_names:huurton_pup",
	socialGroup = "huurton",
	faction = "",
	level = 2,
	chanceHit = 0.21,
	damageMin = 35,
	damageMax = 40,
	baseXp = 45,
	baseHAM = 68,
	baseHAMmax = 83,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 10,
	hideType = "hide_wooly",
	hideAmount = 10,
	boneType = "bone_mammal",
	boneAmount = 5,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/huurton_pup.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	scale = 0.65,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(huurton_pup, "huurton_pup")
