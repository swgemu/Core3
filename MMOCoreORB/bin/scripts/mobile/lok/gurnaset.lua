gurnaset = Creature:new {
	objectName = "@mob/creature_names:gurnaset",
	socialGroup = "gurnaset",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.31,
	damageMin = 160,
	damageMax = 170,
	baseXp = 831,
	baseHAM = 2400,
	baseHAMmax = 3000,
	armor = 0,
	resists = {10,5,5,5,5,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 352,
	hideType = "hide_leathery",
	hideAmount = 279,
	boneType = "bone_mammal",
	boneAmount = 304,
	milk = 1,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/gurnaset.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(gurnaset, "gurnaset")