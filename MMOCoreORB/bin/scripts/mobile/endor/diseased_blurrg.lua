diseased_blurrg = Creature:new {
	objectName = "@mob/creature_names:diseased_blurrg",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 37,
	chanceHit = 0.41,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3551,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {40,40,-1,50,50,25,50,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = NONE,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/blurrg_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareableeding",""},
		{"mediumdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(diseased_blurrg, "diseased_blurrg")