mat_rags_bantha_matriarch = Creature:new {
	objectName = "@mob/creature_names:matriarch_bantha",
	socialGroup = "bantha",
	faction = "",
	level = 25,
	chanceHit = 0.35,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2543,
	baseHAM = 7700,
	baseHAMmax = 8550,
	armor = 0,
	resists = {35,10,10,50,-1,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 485,
	hideType = "hide_wooly",
	hideAmount = 365,
	boneType = "bone_mammal",
	boneAmount = 320,
	milkType = "milk_wild",
	milk = 265,
	tamingChance = 0,
	ferocity = 4,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/matriarch_bantha.iff"},
	lootGroups = {
	 {
	        groups = {
				{group = "task_loot_bantha_horns", chance = 10000000}
			},
			lootChance = 10000000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(mat_rags_bantha_matriarch, "mat_rags_bantha_matriarch")
