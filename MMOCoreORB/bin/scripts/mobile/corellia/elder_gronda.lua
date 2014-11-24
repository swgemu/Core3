elder_gronda = Creature:new {
	objectName = "@mob/creature_names:gronda_elder",
	socialGroup = "gronda",
	pvpFaction = "",
	faction = "",
	level = 33,
	chanceHit = 0.39,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3370,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {160,20,180,20,20,20,-1,125,-1},
	meatType = "meat_carnivore",
	meatAmount = 360,
	hideType = "hide_leathery",
	hideAmount = 270,
	boneType = "bone_mammal",
	boneAmount = 180,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/gronda_hue.iff"},
	scale = 1.15,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(elder_gronda, "elder_gronda")
