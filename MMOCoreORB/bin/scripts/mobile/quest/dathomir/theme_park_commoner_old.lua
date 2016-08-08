theme_park_commoner_old = Creature:new {
  objectName = "@mob/creature_names:commoner",
  randomNameType = NAME_GENERIC,
  randomNameTag = true,
  socialGroup = "townsperson",
  faction = "townsperson",
  level = 4,
  chanceHit = 0.24,
  damageMin = 40,
  damageMax = 45,
  baseXp = 62,
  baseHAM = 113,
  baseHAMmax = 138,
  armor = 0,
  resists = {15,15,15,15,15,15,15,-1,-1},
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
  optionsBitmask = AIENABLED + CONVERSABLE,
  diet = HERBIVORE,

  templates = { "object/mobile/dressed_criminal_pirate_human_male_01.iff",
      "object/mobile/dressed_criminal_thug_human_male_01.iff",
      "object/mobile/dressed_criminal_thug_zabrak_male_01.iff"
      },

  lootGroups = {},
  weapons = {"pirate_weapons_light"},
  conversationTemplate = "theme_park_smc_zideera_mission_target_convotemplate",
  attacks = merge(marksmannovice,brawlernovice)
}

CreatureTemplates:addCreatureTemplate(theme_park_commoner_old, "theme_park_commoner_old")
