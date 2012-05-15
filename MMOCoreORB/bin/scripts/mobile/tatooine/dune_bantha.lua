dune_bantha = Creature:new {
	objectName = "@mob/creature_names:dune_bantha",
	socialGroup = "bantha",
	pvpFaction = "",
	faction = "",
	level = 17,
	chanceHit = 0.32,
	damageMin = 160,
	damageMax = 170,
	baseXp = 960,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {5,5,5,40,-1,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 375,
	hideType = "hide_wooly",
	hideAmount = 275,
	boneType = "bone_mammal",
	boneAmount = 175,
	milk = 1,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/bantha.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(dune_bantha, "dune_bantha")