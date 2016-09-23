vornskr_quest_joz = Creature:new {
	objectName = "@mob/creature_names:narglatch_hunter",
	customName = "an Ancient Vornskr",
	socialGroup = "force",
	faction = "",
	level = 12,
	chanceHit = 0.29,
	damageMin = 130,
	damageMax = 140,
	baseXp = 66,
	baseHAM = 1200,
	baseHAMmax = 1400,
	armor = 0,
	resists = {66,66,66,66,66,66,66,66,166},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0,
	ferocity = 9,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/narglatch_hue.iff"},
	scale = 0.66,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"mildpoison",""},
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(vornskr_quest_joz, "vornskr_quest_joz")
