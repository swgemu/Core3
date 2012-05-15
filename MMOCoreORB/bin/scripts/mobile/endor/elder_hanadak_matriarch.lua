elder_hanadak_matriarch = Creature:new {
	objectName = "@mob/creature_names:elder_hanadak_matriarch",
	socialGroup = "Hanadak",
	pvpFaction = "",
	faction = "",
	level = 35,
	chanceHit = 0.41,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3551,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {25,25,-1,80,80,80,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 35,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/elder_hanadak_matriarch.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(elder_hanadak_matriarch, "elder_hanadak_matriarch")