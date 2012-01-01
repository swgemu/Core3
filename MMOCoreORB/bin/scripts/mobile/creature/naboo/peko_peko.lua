peko_peko = Creature:new {
	objectName = "@mob/creature_names:peko_peko",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 14,
	chanceHit = 0.3,
	damageMin = 150,
	damageMax = 160,
	baseXp = 609,
	baseHAM = 2000,
	baseHAMmax = 2400,
	armor = 0,
	resists = {0,0,25,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 105,
	hideType = "hide_wooly",
	hideAmount = 40,
	boneType = "bone_avian",
	boneAmount = 30,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 6,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/peko_peko.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(peko_peko, "peko_peko")