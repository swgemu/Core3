fbase_swamp_trooper_hard = Creature:new {
	objectName = "@mob/creature_names:fbase_swamp_trooper_hard",
	randomNameType = NAME_SWAMPTROOPER,
	randomNameTag = true,
	socialGroup = "imperial",
	faction = "imperial",
	level = 82,
	chanceHit = 0.82,
	damageMin = 555,
	damageMax = 820,
	baseXp = 8200,
	baseHAM = 16000,
	baseHAMmax = 23000,
	armor = 1,
	resists = {15,15,140,-1,-1,-1,200,-1,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,
	scale = 1.05,

	templates = {"object/mobile/dressed_swamp_trooper.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 6000000},
				{group = "weapons_all", chance = 1200000},
				{group = "armor_all", chance = 1200000},
				{group = "clothing_attachments", chance = 150000},
				{group = "armor_attachments", chance = 150000},
				{group = "stormtrooper_common", chance = 200000},
				{group = "wearables_all", chance = 1000000}
			}
		}
	},
	weapons = {"stormtrooper_weapons"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/stormtrooper",
	attacks = merge(riflemanmaster,brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(fbase_swamp_trooper_hard, "fbase_swamp_trooper_hard")
