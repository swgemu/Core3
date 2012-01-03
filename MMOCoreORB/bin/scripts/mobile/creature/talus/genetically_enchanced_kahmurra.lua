genetically_enchanced_kahmurra = Creature:new {
	objectName = "@mob/creature_names:genetically_enhanced_kahmurra",
	socialGroup = "Kahmurra",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.39,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3097,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {20,20,20,20,20,20,20,20,-1},
	meatType = "meat_herbivore",
	meatAmount = 50,
	hideType = "hide_bristley",
	hideAmount = 30,
	boneType = "bone_mammal",
	boneAmount = 35,
	milk = 1,
	tamingChance = 0.25,
	ferocity = 6,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/kahmurra.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(genetically_enchanced_kahmurra, "genetically_enchanced_kahmurra")