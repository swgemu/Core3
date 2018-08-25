lowland_brackaset = Creature:new {
	objectName = "@mob/creature_names:brackaset_lowlands",
	socialGroup = "brackaset",
	faction = "",
	level = 10,
	chanceHit = 0.28,
	damageMin = 120,
	damageMax = 130,
	baseXp = 292,
	baseHAM = 675,
	baseHAMmax = 825,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "meat_wild",
	meatAmount = 75,
	hideType = "hide_leathery",
	hideAmount = 65,
	boneType = "bone_mammal",
	boneAmount = 60,
	milkType = "milk_wild",
	milk = 65,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/brackaset_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	controlDeviceTemplate = "object/intangible/pet/brackaset_hue.iff",
	scale = 0.9,
	lootGroups = {
		{
			groups = {
				{group = "brackaset_common", chance = 10000000}
			},
			lootChance = 1200000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(lowland_brackaset, "lowland_brackaset")
