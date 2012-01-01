ikopi_stag = Creature:new {
	objectName = "@mob/creature_names:ikopi_stag",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.39,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3005,
	baseHAM = 8400,
	baseHAMmax = 10300,
	armor = 0,
	resists = {30,30,20,20,20,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 100,
	hideType = "hide_bristley",
	hideAmount = 75,
	boneType = "bone_mammal",
	boneAmount = 75,
	milk = 0,
	tamingChance = 0,
	ferocity = 3,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/ikopi.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(ikopi_stag, "ikopi_stag")