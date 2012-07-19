skreeg_gatherer = Creature:new {
	objectName = "@mob/creature_names:skreeg_gatherer",
	socialGroup = "skreeg",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.31,
	damageMin = 160,
	damageMax = 170,
	baseXp = 831,
	baseHAM = 2400,
	baseHAMmax = 3500,
	armor = 0,
	resists = {5,15,5,-1,5,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 18,
	hideType = "hide_bristley",
	hideAmount = 9,
	boneType = "bone_mammal",
	boneAmount = 7,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/skreeg_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(skreeg_gatherer, "skreeg_gatherer")