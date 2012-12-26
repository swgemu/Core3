greater_sludge_panther = Creature:new {
	objectName = "@mob/creature_names:greater_sludge_panther",
	socialGroup = "panther",
	pvpFaction = "",
	faction = "",
	level = 25,
	chanceHit = 0.35,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2637,
	baseHAM = 7200,
	baseHAMmax = 8800,
	armor = 0,
	resists = {60,-1,35,35,35,-1,75,-1,-1},
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
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/greater_sludge_panther.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(greater_sludge_panther, "greater_sludge_panther")