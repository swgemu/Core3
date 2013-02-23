domesticated_gurnaset = Creature:new {
	objectName = "@mob/creature_names:domesticated_gurnaset",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 13,
	chanceHit = 0.3,
	damageMin = 130,
	damageMax = 140,
	baseXp = 514,
	baseHAM = 2000,
	baseHAMmax = 2400,
	armor = 0,
	resists = {10,10,0,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 352,
	hideType = "hide_leathery",
	hideAmount = 279,
	boneType = "bone_mammal",
	boneAmount = 304,
	milkType = "milk_domesticated",
	milk = 200,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/gurnaset_hue.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(domesticated_gurnaset, "domesticated_gurnaset")
