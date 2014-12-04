rogue_falumpaset = Creature:new {
	objectName = "@mob/creature_names:rogue_falumpaset",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.32,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1102,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {5,110,5,-1,-1,-1,5,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 190,
	hideType = "hide_leathery",
	hideAmount = 110,
	boneType = "bone_mammal",
	boneAmount = 80,
	milkType = "milk_wild",
	milk = 100,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = NONE,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/falumpaset_hue.iff"},
	scale = 1.1,
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(rogue_falumpaset, "rogue_falumpaset")
