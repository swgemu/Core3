fambaa = Creature:new {
	objectName = "@mob/creature_names:fambaa",
	socialGroup = "fambaa",
	faction = "",
	level = 34,
	chanceHit = 0.41,
	damageMin = 315,
	damageMax = 340,
	baseXp = 3370,
	baseHAM = 8700,
	baseHAMmax = 10700,
	armor = 0,
	resists = {20,20,20,20,160,160,-1,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 750,
	boneType = "bone_mammal",
	boneAmount = 675,
	milkType = "milk_wild",
	milk = 400,
	tamingChance = 0.25,
	ferocity = 7,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/fambaa.iff"},
	controlDeviceTemplate = "object/intangible/pet/fambaa_hue.iff",
	lootGroups = {
	 {
	        groups = {
				{group = "fambaa_common", chance = 10000000}
			},
			lootChance = 1680000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack",""},
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(fambaa, "fambaa")
