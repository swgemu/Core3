computer_scientist = Creature:new {
	objectName = "@mob/creature_names:warren_insane_comp_sci",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "warren_scientist",
	faction = "",
	level = 33,
	chanceHit = 0.37,
	damageMin = 270,
	damageMax = 280,
	baseXp = 2822,
	baseHAM = 8200,
	baseHAMmax = 10000,
	armor = 0,
	resists = {20,20,0,0,0,-1,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/warren_insane_comp_sci.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4000000},
				{group = "wearables_common", chance = 3000000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "tailor_components", chance = 1000000},
			}
		}
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(computer_scientist, "computer_scientist")
