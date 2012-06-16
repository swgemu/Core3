brackaset_male = Creature:new {
	objectName = "@mob/creature_names:brackaset_male",
	socialGroup = "brackaset",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.39,
	damageMin = 280,
	damageMax = 290,
	baseXp = 3005,
	baseHAM = 8500,
	baseHAMmax = 10300,
	armor = 0,
	resists = {30,30,20,20,20,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 100,
	hideType = "hide_leathery",
	hideAmount = 91,
	boneType = "bone_mammal",
	boneAmount = 81,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	aiTemplate = "default",

	templates = {"object/mobile/brackaset.iff"},
	lootGroups = {
		 {
	        groups = {
				{group = "brackaset_common", chance = 3300000}
			},
			lootChance = 7000000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(brackaset_male, "brackaset_male")