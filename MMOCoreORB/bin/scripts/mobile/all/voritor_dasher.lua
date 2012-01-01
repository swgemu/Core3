voritor_dasher = Creature:new {
	objectName = "@mob/creature_names:voritor_dasher",
	socialGroup = "Voritor Lizard",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.39,
	damageMin = 345,
	damageMax = 400,
	baseXp = 3005,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,0},
	meatType = "meat_carnivore",
	meatAmount = 40,
	hideType = "hide_leathery",
	hideAmount = 30,
	boneType = "bone_avian",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 0,
	diet = NONE,

	templates = {"object/mobile/voritor_dasher.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareapoison",""},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(voritor_dasher, "voritor_dasher")