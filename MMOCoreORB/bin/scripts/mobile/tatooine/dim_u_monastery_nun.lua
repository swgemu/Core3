dim_u_monastery_nun = Creature:new {
	objectName = "@mob/creature_names:dim_u_monastery_nun",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "dim_u",
	faction = "",
	level = 6,
	chanceHit = 0.25,
	damageMin = 50,
	damageMax = 55,
	baseXp = 113,
	baseHAM = 180,
	baseHAMmax = 220,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_tatooine_dim_u_monastery_nun.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4500000},
				{group = "wearables_common", chance = 2000000},
				{group = "tailor_components", chance = 1500000},
				{group = "loot_kit_parts", chance = 1500000},
				{group = "dim_u_common", chance = 500000}
			},
			lootChance = 2200000
		}
	},
	weapons = {},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/fancy",
	attacks = brawlernovice
}

CreatureTemplates:addCreatureTemplate(dim_u_monastery_nun, "dim_u_monastery_nun")
