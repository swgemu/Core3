furious_devastator = Creature:new {
	objectName = "@mob/creature_names:fambaa_furious_devastator",
	socialGroup = "Fambaa",
	pvpFaction = "",
	faction = "",
	level = 38,
	chanceHit = 0.4,
	damageMin = 375,
	damageMax = 460,
	baseXp = 3824,
	baseHAM = 8600,
	baseHAMmax = 10600,
	armor = 0,
	resists = {25,45,-1,-1,60,60,-1,0,-1},
	meatType = "meat_reptilian",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 750,
	boneType = "bone_mammal",
	boneAmount = 675,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/fambaa.iff"},
	lootGroups = {
	 {
	        groups = {
				{group = "fambaa_common", chance = 3300000}
			},
			lootChance = 7000000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(furious_devastator, "furious_devastator")