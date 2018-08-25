greater_sludge_panther = Creature:new {
	objectName = "@mob/creature_names:greater_sludge_panther",
	socialGroup = "panther",
	faction = "",
	level = 25,
	chanceHit = 0.35,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2637,
	baseHAM = 7200,
	baseHAMmax = 8800,
	armor = 0,
	resists = {135,10,10,-1,-1,-1,145,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 80,
	hideType = "hide_leathery",
	hideAmount = 70,
	boneType = "bone_mammal",
	boneAmount = 70,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 7,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/greater_sludge_panther.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	controlDeviceTemplate = "object/intangible/pet/corellian_sand_panther_hue.iff",
	scale = 2.0,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(greater_sludge_panther, "greater_sludge_panther")
