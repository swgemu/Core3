fbase_dark_trooper_hard = Creature:new {
	objectName = "@mob/creature_names:fbase_dark_trooper_hard",
	randomNameType = NAME_DARKTROOPER,
	socialGroup = "imperial",
	faction = "imperial",
	level = 100,
	chanceHit = 1.0,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 10000,
	baseHAM = 24000,
	baseHAMmax = 30000,
	armor = 1,
	resists = {140,20,20,150,150,150,150,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + OVERT,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,
	scale = 1.5,

	templates = {"object/mobile/dark_trooper.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 300000},
				{group = "junk", chance = 6000000},
				{group = "holocron_dark", chance = 150000},
				{group = "holocron_light", chance = 150000},
				{group = "weapons_all", chance = 1050000},
				{group = "armor_all", chance = 1050000},
				{group = "clothing_attachments", chance = 150000},
				{group = "armor_attachments", chance = 150000},
				{group = "wearables_all", chance = 1000000}
			}
		}
	},
	weapons = {"dark_trooper_weapons"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/stormtrooper",
	attacks = merge(riflemanmaster,marksmanmaster,fencermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(fbase_dark_trooper_hard, "fbase_dark_trooper_hard")
