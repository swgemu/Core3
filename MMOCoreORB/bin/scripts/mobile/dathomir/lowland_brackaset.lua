lowland_brackaset = Creature:new {
	objectName = "@mob/creature_names:brackaset_lowlands",
	socialGroup = "brackaset",
	pvpFaction = "",
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
	milk = "milk_wild",
	milkAmount = 65,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/brackaset_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/brackaset_hue.iff",
	scale = 0.9,
	lootGroups = {
	 {
	        groups = {
				{group = "brackaset_common", chance = 10000000}
			},
			lootChance = 2300000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(lowland_brackaset, "lowland_brackaset")
