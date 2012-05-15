elder_mamien = Creature:new {
	objectName = "@mob/creature_names:mamien_elder",
	socialGroup = "mamien",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.33,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1609,
	baseHAM = 4500,
	baseHAMmax = 5500,
	armor = 0,
	resists = {5,20,5,5,5,5,5,-1,-1},
	meatType = "meat_wild",
	meatAmount = 18,
	hideType = "hide_wooly",
	hideAmount = 18,
	boneType = "bone_mammal",
	boneAmount = 18,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/mamien.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(elder_mamien, "elder_mamien")