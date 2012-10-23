rogue_bageraset = Creature:new {
	objectName = "@mob/creature_names:rogue_bageraset",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 13,
	chanceHit = 0.29,
	damageMin = 130,
	damageMax = 140,
	baseXp = 609,
	baseHAM = 1200,
	baseHAMmax = 1400,
	armor = 0,
	resists = {10,5,0,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 230,
	hideType = "hide_leathery",
	hideAmount = 130,
	boneType = "bone_mammal",
	boneAmount = 80,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 4,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/bageraset_hue.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(rogue_bageraset, "rogue_bageraset")