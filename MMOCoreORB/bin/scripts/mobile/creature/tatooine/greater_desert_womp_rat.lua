greater_desert_womp_rat = Creature:new {
	objectName = "@mob/creature_names:great_desert_womp_rat",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.35,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2006,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {10,10,35,30,10,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 6,
	hideType = "hide_leathery",
	hideAmount = 5,
	boneType = "bone_mammal",
	boneAmount = 4,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 6,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/greater_desert_womp_rat.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(greater_desert_womp_rat, "greater_desert_womp_rat")