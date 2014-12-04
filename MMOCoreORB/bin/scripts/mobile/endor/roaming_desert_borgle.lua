roaming_desert_borgle = Creature:new {
	objectName = "@mob/creature_names:borgle_desert_roamer",
	socialGroup = "borgle",
	pvpFaction = "",
	faction = "",
	level = 32,
	chanceHit = 0.38,
	damageMin = 280,
	damageMax = 290,
	baseXp = 3188,
	baseHAM = 8300,
	baseHAMmax = 10100,
	armor = 0,
	resists = {130,140,15,155,-1,170,15,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 5,
	hideType = "hide_leathery",
	hideAmount = 5,
	boneType = "bone_avian",
	boneAmount = 5,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/borgle_hue.iff"},
	scale = 1.2,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(roaming_desert_borgle, "roaming_desert_borgle")
