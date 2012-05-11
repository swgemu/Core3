tortur = Creature:new {
	objectName = "@mob/creature_names:tortur",
	socialGroup = "tortur",
	pvpFaction = "",
	faction = "",
	level = 21,
	chanceHit = 0.34,
	damageMin = 260,
	damageMax = 270,
	baseXp = 1803,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {10,10,10,10,-1,-1,-1,45,-1},
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
		{"dizzyattack","dizzyChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(tortur, "tortur")