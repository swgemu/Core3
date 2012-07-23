gungan_falumpaset = Creature:new {
	objectName = "@mob/creature_names:gungan_falumpaset",
	socialGroup = "gungan",
	pvpFaction = "",
	faction = "gungan",
	level = 26,
	chanceHit = 0.36,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2637,
	baseHAM = 7700,
	baseHAMmax = 9400,
	armor = 0,
	resists = {25,15,15,35,35,-1,-1,1,-1},
	meatType = "meat_carnivore",
	meatAmount = 230,
	hideType = "hide_leathery",
	hideAmount = 130,
	boneType = "bone_mammal",
	boneAmount = 80,
	milk = 0,
	tamingChance = 0,
	ferocity = 8,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/falumpaset_hue.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(gungan_falumpaset, "gungan_falumpaset")