ferine_razorfang = Creature:new {
	objectName = "@mob/creature_names:kima_ferine_razorfang",
	socialGroup = "kima",
	pvpFaction = "",
	faction = "",
	level = 21,
	chanceHit = 0.32,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2006,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {20,20,10,10,10,10,10,10,-1},
	meatType = "meat_herbivore",
	meatAmount = 7,
	hideType = "hide_bristley",
	hideAmount = 8,
	boneType = "bone_mammal",
	boneAmount = 7,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 8,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	aiTemplate = "default",

	templates = {"object/mobile/kima.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(ferine_razorfang, "ferine_razorfang")