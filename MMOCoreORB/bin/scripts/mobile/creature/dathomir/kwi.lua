kwi = Creature:new {
	objectName = "@mob/creature_names:kwi",
	socialGroup = "Kwi",
	pvpFaction = "",
	faction = "",
	level = 10,
	chanceHit = 0.27,
	damageMin = 90,
	damageMax = 110,
	baseXp = 356,
	baseHAM = 270,
	baseHAMmax = 330,
	armor = 0,
	resists = {10,10,0,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 100,
	hideType = "hide_leathery",
	hideAmount = 85,
	boneType = "bone_mammal",
	boneAmount = 75,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 2,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/kwi.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kwi, "kwi")