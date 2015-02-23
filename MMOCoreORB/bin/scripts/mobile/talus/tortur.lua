tortur = Creature:new {
	objectName = "@mob/creature_names:tortur",
	socialGroup = "tortur",
	faction = "",
	level = 21,
	chanceHit = 0.34,
	damageMin = 260,
	damageMax = 270,
	baseXp = 1803,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {10,10,10,10,-1,-1,-1,145,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 1000,
	boneType = "bone_mammal",
	boneAmount = 1000,
	milk = 0,
	tamingChance = 0,
	ferocity = 7,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/meager_tortur.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"knockdownattack",""},
		{"dizzyattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(tortur, "tortur")
