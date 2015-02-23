large_berzerk_ikopi = Creature:new {
	objectName = "@mob/creature_names:mountain_ikopi",
	customName = "Large Berzerk Ikopi",
	socialGroup = "self",
	faction = "",
	level = 17,
	chanceHit = 0.31,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1102,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 1,
	resists = {10,10,10,10,10,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 75,
	hideType = "hide_bristley",
	hideAmount = 60,
	boneType = "bone_mammal",
	boneAmount = 50,
	milk = 0,
	tamingChance = 0,
	ferocity = 3,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/ikopi_hue.iff"},
	scale = 1.2,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(large_berzerk_ikopi, "large_berzerk_ikopi")
