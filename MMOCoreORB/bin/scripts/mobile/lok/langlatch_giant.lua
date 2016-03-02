langlatch_giant = Creature:new {
	objectName = "@mob/creature_names:langlatch_giant",
	socialGroup = "langlatch",
	faction = "",
	level = 20,
	chanceHit = 0.33,
	damageMin = 210,
	damageMax = 220,
	baseXp = 1803,
	baseHAM = 2400,
	baseHAMmax = 3000,
	armor = 0,
	resists = {30,0,0,15,15,30,30,-1,0},
	meatType = "meat_carnivore",
	meatAmount = 20,
	hideType = "hide_wooly",
	hideAmount = 12,
	boneType = "bone_mammal",
	boneAmount = 12,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/langlatch_hue.iff"},
	scale = 1.5,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""},
		{"knockdownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(langlatch_giant, "langlatch_giant")
