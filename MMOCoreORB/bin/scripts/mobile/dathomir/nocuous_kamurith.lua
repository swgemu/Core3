nocuous_kamurith = Creature:new {
	objectName = "@mob/creature_names:kamurith_nocuous",
	socialGroup = "kamurith",
	faction = "",
	level = 46,
	chanceHit = 0.48,
	damageMin = 395,
	damageMax = 500,
	baseXp = 4552,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 1,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 90,
	hideType = "hide_leathery",
	hideAmount = 65,
	boneType = "bone_avian",
	boneAmount = 60,
	milk = 0,
	tamingChance = 0,
	ferocity = 2,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/voritor_lizard_hue.iff"},
	scale = 1.2,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack",""},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(nocuous_kamurith, "nocuous_kamurith")
