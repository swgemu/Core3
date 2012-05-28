stoneskin_hanadak = Creature:new {
	objectName = "@mob/creature_names:stoneskin_hanadak",
	socialGroup = "hanadak",
	pvpFaction = "",
	faction = "",
	level = 139,
	chanceHit = 4.75,
	damageMin = 720,
	damageMax = 1150,
	baseXp = 13178,
	baseHAM = 88000,
	baseHAMmax = 107000,
	armor = 2,
	resists = {90,100,65,100,100,100,100,80,-1},
	meatType = "meat_carnivore",
	meatAmount = 40,
	hideType = "hide_bristley",
	hideAmount = 40,
	boneType = "bone_mammal",
	boneAmount = 40,
	milk = 0,
	tamingChance = 0,
	ferocity = 9,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/hanadak.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(stoneskin_hanadak, "stoneskin_hanadak")