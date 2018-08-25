brackaset_female = Creature:new {
	objectName = "@mob/creature_names:brackaset_female",
	socialGroup = "brackaset",
	faction = "",
	level = 29,
	chanceHit = 0.37,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2914,
	baseHAM = 8300,
	baseHAMmax = 10100,
	armor = 0,
	resists = {130,130,120,15,15,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 100,
	hideType = "hide_leathery",
	hideAmount = 90,
	boneType = "bone_mammal",
	boneAmount = 80,
	milkType = "milk_wild",
	milk = 50,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/brackaset_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	controlDeviceTemplate = "object/intangible/pet/brackaset_hue.iff",
	scale = 1.05,
	lootGroups = {
		 {
	        groups = {
				{group = "brackaset_common", chance = 10000000}
			},
			lootChance = 1580000
		}
	   },
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(brackaset_female, "brackaset_female")
