pigmy_pugoriss = Creature:new {
	objectName = "@mob/creature_names:pigmy_pugoriss",
	socialGroup = "pugoriss",
	faction = "",
	level = 8,
	chanceHit = 0.27,
	damageMin = 90,
	damageMax = 110,
	baseXp = 187,
	baseHAM = 180,
	baseHAMmax = 220,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 300,
	hideType = "hide_leathery",
	hideAmount = 350,
	boneType = "bone_mammal",
	boneAmount = 300,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/pigmy_pugoriss.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	scale = 0.8,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(pigmy_pugoriss, "pigmy_pugoriss")
