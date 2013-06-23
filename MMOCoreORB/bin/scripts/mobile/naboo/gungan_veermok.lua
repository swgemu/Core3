gungan_veermok = Creature:new {
	objectName = "@mob/creature_names:gungan_veermok",
	socialGroup = "gungan",
	pvpFaction = "",
	faction = "gungan",
	level = 22,
	chanceHit = 0.35,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2006,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {10,10,10,10,10,10,10,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 150,
	hideType = "hide_bristley",
	hideAmount = 150,
	boneType = "bone_mammal",
	boneAmount = 60,
	milk = 0,
	tamingChance = 0,
	ferocity = 4,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/veermok.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(gungan_veermok, "gungan_veermok")