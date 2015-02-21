adolescent_pygmy_torton = Creature:new {
	objectName = "@mob/creature_names:torton_pygmy_adolescent",
	socialGroup = "torton",
	faction = "",
	level = 14,
	chanceHit = 0.3,
	damageMin = 160,
	damageMax = 170,
	baseXp = 714,
	baseHAM = 1000,
	baseHAMmax = 1200,
	armor = 0,
	resists = {110,110,0,0,0,-1,0,150,-1},
	meatType = "meat_carnivore",
	meatAmount = 500,
	hideType = "hide_wooly",
	hideAmount = 300,
	boneType = "bone_mammal",
	boneAmount = 500,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/torton_hue.iff"},
	scale = .5,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(adolescent_pygmy_torton, "adolescent_pygmy_torton")
