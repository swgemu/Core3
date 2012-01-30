guf_drolg_female = Creature:new {
	objectName = "@mob/creature_names:guf_drolg_female",
	socialGroup = "Guf Drolg",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.3,
	damageMin = 150,
	damageMax = 160,
	baseXp = 831,
	baseHAM = 2000,
	baseHAMmax = 2400,
	armor = 0,
	resists = {15,5,0,0,0,0,0,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 325,
	hideType = "hide_leathery",
	hideAmount = 265,
	boneType = "bone_mammal",
	boneAmount = 190,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/guf_drolg.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(guf_drolg_female, "guf_drolg_female")