corellian_butterfly_monarch = Creature:new {
	objectName = "@mob/creature_names:corellian_butterfly_monarch",
	socialGroup = "butterfly",
	faction = "",
	level = 20,
	chanceHit = 0.33,
	damageMin = 200,
	damageMax = 210,
	baseXp = 1803,
	baseHAM = 4500,
	baseHAMmax = 5500,
	armor = 0,
	resists = {-1,125,-1,5,5,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 27,
	hideType = "hide_scaley",
	hideAmount = 27,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/corellian_butterfly_monarch.iff"},
	scale = 1.25,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"knockdownattack",""},
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(corellian_butterfly_monarch, "corellian_butterfly_monarch")
