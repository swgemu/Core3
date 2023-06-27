theme_park_imperial_sergeant = Creature:new {
  objectName = "@mob/creature_names:imperial_sergeant",
  randomNameType = NAME_GENERIC,
  randomNameTag = true,
	mobType = MOB_NPC,
  socialGroup = "imperial",
  faction = "imperial",
  level = 16,
  chanceHit = 0.31,
  damageMin = 170,
  damageMax = 180,
  baseXp = 960,
  baseHAM = 2900,
  baseHAMmax = 3500,
  armor = 0,
  resists = {5,5,5,5,5,5,5,-1,-1},
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
  creatureBitmask = PACK,
  optionsBitmask = AIENABLED + CONVERSABLE,
  diet = HERBIVORE,

  templates = {"imperial_officer"},
  lootGroups = {},
  primaryWeapon = "unarmed",
	secondaryWeapon = "none",
  conversationTemplate = "theme_park_nightsister_mission_target_convotemplate",
  reactionStf = "@npc_reaction/military",
  personalityStf = "@hireling/hireling_military",
  
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(brawlermaster,marksmanmaster),
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(theme_park_imperial_sergeant, "theme_park_imperial_sergeant")