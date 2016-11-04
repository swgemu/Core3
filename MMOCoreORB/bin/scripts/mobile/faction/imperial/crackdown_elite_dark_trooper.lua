crackdown_elite_dark_trooper = Creature:new {
	objectName = "@mob/creature_names:crackdown_elite_dark_trooper",
	randomNameType = NAME_DARKTROOPER,
	randomNameTag = false,
	socialGroup = "imperial",
	faction = "imperial",
	level = 50,
	chanceHit = 0.9,
	damageMin = 465,
	damageMax = 640,
	baseXp = 4500,
	baseHAM = 13000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {140,115,115,150,150,150,150,-1,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,
	scale = 1.5,

	templates = {"object/mobile/dark_trooper.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 7650000},
				{group = "rifles", chance = 550000},
				{group = "pistols", chance = 550000},
				{group = "melee_weapons", chance = 550000},
				{group = "carbines", chance = 550000},
				{group = "clothing_attachments", chance = 25000},
				{group = "armor_attachments", chance = 25000}
			},
			lootChance = 2800000
		}						
	},
	weapons = {"dark_trooper_weapons"},
	conversationTemplate = "",
	attacks = merge(riflemanmid,brawlermaster,fencermid,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(crackdown_elite_dark_trooper, "crackdown_elite_dark_trooper")
