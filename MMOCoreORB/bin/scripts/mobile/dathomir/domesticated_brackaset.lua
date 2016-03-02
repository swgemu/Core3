domesticated_brackaset = Creature:new {
	objectName = "@mob/creature_names:domesticated_brackaset",
	socialGroup = "self",
	faction = "",
	level = 23,
	chanceHit = 0.35,
	damageMin = 170,
	damageMax = 180,
	baseXp = 2006,
	baseHAM = 8550,
	baseHAMmax = 8550,
	armor = 0,
	resists = {115,115,0,0,-1,0,0,-1,-1},
	meatType = "meat_domesticated",
	meatAmount = 100,
	hideType = "hide_leathery",
	hideAmount = 90,
	boneType = "bone_mammal",
	boneAmount = 80,
	milkType = "milk_domesticated",
	milk = 50,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/brackaset_hue.iff"},
	lootGroups = {
		{
			groups = {
				{group = "brackaset_common", chance = 10000000}
			},
			lootChance = 1460000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(domesticated_brackaset, "domesticated_brackaset")
