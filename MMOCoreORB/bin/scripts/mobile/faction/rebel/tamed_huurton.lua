tamed_huurton = Creature:new {
	objectName = "@mob/creature_names:rebel_tamed_huurton",
	socialGroup = "rebel",
	faction = "rebel",
	level = 12,
	chanceHit = 0.29,
	damageMin = 130,
	damageMax = 140,
	baseXp = 514,
	baseHAM = 1200,
	baseHAMmax = 1400,
	armor = 0,
	resists = {10,10,10,10,10,10,10,-1,-1},
	meatType = "meat_wild",
	meatAmount = 12,
	hideType = "hide_wooly",
	hideAmount = 12,
	boneType = "bone_mammal",
	boneAmount = 12,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/huurton_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(tamed_huurton, "tamed_huurton")
