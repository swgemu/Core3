fierce_borgle = Creature:new {
	objectName = "@mob/creature_names:fierce_borgle",
	socialGroup = "borgle",
	pvpFaction = "",
	faction = "",
	level = 32,
	chanceHit = 0.37,
	damageMin = 310,
	damageMax = 330,
	baseXp = 3279,
	baseHAM = 6300,
	baseHAMmax = 7700,
	armor = 0,
	resists = {40,30,30,-1,75,75,100,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 5,
	boneType = "bone_avian",
	boneAmount = 5,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/borgle_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(fierce_borgle, "fierce_borgle")