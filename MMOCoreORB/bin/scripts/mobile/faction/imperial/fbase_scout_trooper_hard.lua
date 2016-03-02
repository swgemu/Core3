fbase_scout_trooper_hard = Creature:new {
	objectName = "@mob/creature_names:fbase_scout_trooper_hard",
	randomNameType = NAME_SCOUTTROOPER,
	randomNameTag = true,
	socialGroup = "imperial",
	faction = "imperial",
	level = 66,
	chanceHit = 0.66,
	damageMin = 475,
	damageMax = 660,
	baseXp = 6600,
	baseHAM = 12500,
	baseHAMmax = 18500,
	armor = 1,
	resists = {115,115,10,10,10,-1,10,-1,-1},
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
	creatureBitmask = NONE,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,
	scale = 1.05,

	templates = {"object/mobile/dressed_scout_trooper_white_white.iff"},
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
	weapons = {"imperial_weapons_light"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/stormtrooper",
	attacks = merge(brawlermaster,marksmanmaster,pistoleermid)
}

CreatureTemplates:addCreatureTemplate(fbase_scout_trooper_hard, "fbase_scout_trooper_hard")
