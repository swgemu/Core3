huurton_pup = Creature:new {
	objectName = "@mob/creature_names:huurton_pup",
	socialGroup = "huurton",
	pvpFaction = "",
	faction = "",
	level = 2,
	chanceHit = 0.21,
	damageMin = 35,
	damageMax = 40,
	baseXp = 45,
	baseHAM = 68,
	baseHAMmax = 83,
	armor = 0,
	resists = {15,15,15,0,0,0,0,-1,-1},
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
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/huurton_pup.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(huurton_pup, "huurton_pup")