corellian_butterfly_monarch = Creature:new {
	objectName = "@mob/creature_names:corellian_butterfly_monarch",
	socialGroup = "Cor. Butterfly",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.33,
	damageMin = 200,
	damageMax = 210,
	baseXp = 1803,
	baseHAM = 4500,
	baseHAMmax = 5500,
	armor = 0,
	resists = {-1,25,-1,5,5,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 27,
	hideType = "",
	hideAmount = 27,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/corellian_butterfly_monarch.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(corellian_butterfly_monarch, "corellian_butterfly_monarch")