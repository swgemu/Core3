blood_thirsty_monarch = Creature:new {
	objectName = "@mob/creature_names:corellian_butterfly_monarch_bloodthirsty",
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
	resists = {5,15,5,5,5,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 27,
	hideType = "hide_scaley",
	hideAmount = 27,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/corellian_butterfly_monarch.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(blood_thirsty_monarch, "blood_thirsty_monarch")