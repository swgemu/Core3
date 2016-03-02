stoneskin_hanadak = Creature:new {
	objectName = "@mob/creature_names:stoneskin_hanadak",
	socialGroup = "hanadak",
	faction = "",
	level = 139,
	chanceHit = 4.75,
	damageMin = 720,
	damageMax = 1150,
	baseXp = 13178,
	baseHAM = 88000,
	baseHAMmax = 107000,
	armor = 2,
	resists = {190,200,165,200,200,200,175,180,-1},
	meatType = "meat_carnivore",
	meatAmount = 40,
	hideType = "hide_bristley",
	hideAmount = 40,
	boneType = "bone_mammal",
	boneAmount = 40,
	milk = 0,
	tamingChance = 0,
	ferocity = 9,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/hanadak_hue.iff"},
	scale = 1.25,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"knockdownattack",""},
		{"blindattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(stoneskin_hanadak, "stoneskin_hanadak")
