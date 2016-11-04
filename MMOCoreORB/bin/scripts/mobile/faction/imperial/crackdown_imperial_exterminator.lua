crackdown_imperial_exterminator = Creature:new {
	objectName = "@mob/creature_names:crackdown_imperial_exterminator",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "imperial",
	faction = "imperial",
	level = 19,
	chanceHit = 0.37,
	damageMin = 290,
	damageMax = 300,
	baseXp = 450,
	baseHAM = 7700,
	baseHAMmax = 9400,
	armor = 0,
	resists = {5,5,5,-1,30,-1,30,-1,-1},
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

	templates = {"object/mobile/dressed_imperial_exterminator.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 200000},
				{group = "junk", chance = 6000000},
				{group = "weapons_all", chance = 1250000},
				{group = "armor_all", chance = 1250000},
				{group = "clothing_attachments", chance = 150000},
				{group = "armor_attachments", chance = 150000},
				{group = "wearables_all", chance = 1000000}
			}
		}
	},
	weapons = {"imperial_weapons_heavy"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/military",
	personalityStf = "@hireling/hireling_military",
	attacks = merge(brawlermaster,marksmanmid,pikemanmid)
}

CreatureTemplates:addCreatureTemplate(crackdown_imperial_exterminator, "crackdown_imperial_exterminator")