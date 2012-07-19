mature_reptilian_flier = Creature:new {
	objectName = "@mob/creature_names:mature_reptilian_flier",
	socialGroup = "repilian_flier",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.32,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1609,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {5,10,5,35,35,-1,5,-1,-1},
	meatType = "meat_avian",
	meatAmount = 130,
	hideType = "hide_leathery",
	hideAmount = 85,
	boneType = "bone_avian",
	boneAmount = 80,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 6,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/reptilian_flier_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mature_reptilian_flier, "mature_reptilian_flier")