narglatch_matriarch = Creature:new {
	objectName = "@mob/creature_names:narglatch_matriarch",
	socialGroup = "Narglatch",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.36,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2822,
	baseHAM = 7700,
	baseHAMmax = 9400,
	armor = 0,
	resists = {30,25,15,-1,15,65,-1,-1,-1},
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
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/narglatch.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(narglatch_matriarch, "narglatch_matriarch")