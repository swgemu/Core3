huurton_howler = Creature:new {
	objectName = "@mob/creature_names:huurton_howler",
	socialGroup = "huurton",
	pvpFaction = "",
	faction = "",
	level = 25,
	chanceHit = 0.35,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2637,
	baseHAM = 5400,
	baseHAMmax = 6600,
	armor = 0,
	resists = {15,15,10,40,60,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 15,
	hideType = "hide_wooly",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 15,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/huurton_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(huurton_howler, "huurton_howler")