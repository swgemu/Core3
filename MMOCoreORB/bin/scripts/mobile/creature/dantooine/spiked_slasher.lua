spiked_slasher = Creature:new {
	objectName = "@mob/creature_names:voritor_spiked_slasher",
	socialGroup = "Voritor Lizard",
	pvpFaction = "",
	faction = "",
	level = 58,
	chanceHit = 0.53,
	damageMin = 430,
	damageMax = 570,
	baseXp = 5647,
	baseHAM = 10000,
	baseHAMmax = 13000,
	armor = 0,
	resists = {65,40,0,0,50,-1,20,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "hide_leathery",
	hideAmount = 40,
	boneType = "bone_avian",
	boneAmount = 50,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/voritor_lizard.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareapoison",""},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(spiked_slasher, "spiked_slasher")