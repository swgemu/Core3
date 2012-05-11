stunted_huf_dun = Creature:new {
	objectName = "@mob/creature_names:stunted_huf_dun",
	socialGroup = "huf_dun",
	pvpFaction = "",
	faction = "",
	level = 9,
	chanceHit = 0.27,
	damageMin = 90,
	damageMax = 110,
	baseXp = 235,
	baseHAM = 675,
	baseHAMmax = 825,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 775,
	hideType = "hide_leathery",
	hideAmount = 800,
	boneType = "bone_mammal",
	boneAmount = 775,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/stunted_huf_dun.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(stunted_huf_dun, "stunted_huf_dun")