spooky_donkuwah_spiritmaster = Creature:new {
	objectName = "@mob/creature_names:spooky_donkuwah_spiritmaster",
	socialGroup = "donkuwah_tribe",
	pvpFaction = "donkuwah_tribe",
	faction = "donkuwah_tribe",
	level = 26,
	chanceHit = 0.36,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2730,
	baseHAM = 6300,
	baseHAMmax = 7700,
	armor = 0,
	resists = {25,15,0,50,50,-1,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	aiTemplate = "default",

	templates = {
			"object/mobile/dulok_male.iff",
			"object/mobile/dulok_female.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(spooky_donkuwah_spiritmaster, "spooky_donkuwah_spiritmaster")