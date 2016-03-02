roaming_bordok_stud = Creature:new {
	objectName = "@mob/creature_names:roaming_bordok_stud",
	socialGroup = "bordok",
	faction = "",
	level = 34,
	chanceHit = 0.41,
	damageMin = 330,
	damageMax = 370,
	baseXp = 3370,
	baseHAM = 9000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {20,-1,20,200,200,20,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 150,
	hideType = "hide_leathery",
	hideAmount = 95,
	boneType = "bone_mammal",
	boneAmount = 65,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/bordok_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack",""},
		{"dizzyattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(roaming_bordok_stud, "roaming_bordok_stud")
