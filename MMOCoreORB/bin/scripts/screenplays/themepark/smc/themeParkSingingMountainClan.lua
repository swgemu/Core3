
vhaunda_missions =
{
  { 
    missionType = "confiscate",
    primarySpawns =
    {
      { npcTemplate = "stormtrooper_squad_leader", planetName = "dathomir", npcName = "LX-613" }
    },
    secondarySpawns =
    {
      { npcTemplate = "stormtrooper", planetName = "dathomir", npcName = "" },
      { npcTemplate = "stormtrooper", planetName = "dathomir", npcName = "" },
      { npcTemplate = "stormtrooper", planetName = "dathomir", npcName = "" }
    },
    itemSpawns =
    {
      { itemTemplate = "object/tangible/mission/quest_item/vhaunda_q1_needed.iff", itemName = "a Stormtrooper Sergeant Shoulder Pad" }
    },
    rewards =
    {
      { rewardType = "faction", faction = "mtn_clan", amount = 10 },
      { rewardType = "credits", amount = 50 }
    }
  },
  { 
    missionType = "assassinate",
    primarySpawns =
    {
      { npcTemplate = "theme_park_singing_mountain_clan_arch_witch_peila", planetName = "dathomir", npcName = "Peila" }
    },
    secondarySpawns =
    {

    },
    itemSpawns =
    {

    },
    rewards =
    {
      { rewardType = "faction", faction = "mtn_clan", amount = 10 },
      { rewardType = "credits", amount = 75 },
      --DO WE NEED A NEW TEMPLATE FOR THIS and SPECIAL STATS???...
      { rewardType = "loot",  lootGroup = "object/weapon/melee/polearm/lance_vibrolance.iff" }
    }
  }
}

izaryx_missions =
{
  { 
    missionType = "escort",
    primarySpawns =
    {
      { npcTemplate = "theme_park_singing_mountain_clan_rancor_tamer", planetName = "dathomir", npcName = "a Singing Mountain Clan Scout" }
    },
    secondarySpawns =
    {
      { npcTemplate = "nightsister_rancor_tamer", planetName = "dathomir", npcName = "" },
      { npcTemplate = "nightsister_sentry", planetName = "dathomir", npcName = "" },
      { npcTemplate = "nightsister_sentry", planetName = "dathomir", npcName = "" }
    },
    itemSpawns =
    {

    },
    rewards =
    {
      { rewardType = "faction", faction = "mtn_clan", amount = 10 },
      { rewardType = "credits", amount = 800 }
    }
  },
  { 
    missionType = "assassinate",
    primarySpawns =
    {
      { npcTemplate = "nightsister_spell_weaver", planetName = "dathomir", npcName = "a Nightsister War-Party Leader" }
    },
    secondarySpawns =
    {
      { npcTemplate = "singing_mountain_clan_rancor_tamer", planetName = "dathomir", npcName = "a Singing Mountain Clan Scout" },
      { npcTemplate = "nightsister_stalker", planetName = "dathomir", npcName = "" },
      { npcTemplate = "nightsister_stalker", planetName = "dathomir", npcName = "" },
      { npcTemplate = "nightsister_rancor_tamer", planetName = "dathomir", npcName = "" },
      { npcTemplate = "nightsister_rancor_tamer", planetName = "dathomir", npcName = "" }
    },
    itemSpawns =
    {

    },
    rewards =
    {
      { rewardType = "faction", faction = "mtn_clan", amount = 10 },
      { rewardType = "credits", amount = 850 }
    }
  }
}

zideera_missions =
{
  { 
    missionType = "escort",
    primarySpawns =
    {
      { npcTemplate = "theme_park_commoner_old", planetName = "dathomir", npcName = "a Stranded Pirate" }
    },
    secondarySpawns =
    {
      { npcTemplate = "lurking_shear_mite", planetName = "dathomir", npcName = "" },
      { npcTemplate = "lurking_shear_mite", planetName = "dathomir", npcName = "" }
    },
    itemSpawns =
    {

    },
    rewards =
    {
      { rewardType = "faction", faction = "mtn_clan", amount = 10 },
      { rewardType = "credits", amount = 300 }
    }
  },
  { 
    missionType = "escort",
    primarySpawns =
    {
      { npcTemplate = "theme_park_commoner_old", planetName = "dathomir", npcName = "a Pirate Crewmate" }
    },
    secondarySpawns =
    {

    },
    itemSpawns =
    {

    },
    rewards =
    {
      { rewardType = "faction", faction = "mtn_clan", amount = 10 },
      { rewardType = "credits", amount = 450 }
    }
  }
}

vurlene_missions =
{
  { 
    missionType = "deliver",
    primarySpawns =
    {
    --THIS NPC NEEDS TO HAVE A SPECIFIC DESIGNATED WAYPOINT...BUT WE NEED NEW WP LOGIC FIRST??
      { npcTemplate = "theme_park_naboo_holy_man", planetName = "naboo", npcName = "Skub" }
    },
    secondarySpawns =
    {

    },
    itemSpawns =
    {
      { itemTemplate = "object/tangible/mission/quest_item/vurlene_q1_needed.iff", itemName = "Jar of Algae" }
    },
    rewards =
    {
      { rewardType = "faction", faction = "mtn_clan", amount = 10 },
      { rewardType = "credits", amount = 75 },
      --DO WE NEED A NEW TEMPLATE FOR THIS 'STIMPACK B' REWARD ITEM WITH SPECIAL STATS and MIND heal??
      { rewardType = "loot",  lootGroup = "object/tangible/medicine/crafted/medpack_damage_b.iff" }
    }
  },
  { 
    missionType = "deliver",
    primarySpawns =
    {
      { npcTemplate = "theme_park_singing_mountain_clan_arch_witch", planetName = "dathomir", npcName = "Selia" }
    },
    secondarySpawns =
    {

    },
    itemSpawns =
    {
      { itemTemplate = "object/tangible/mission/quest_item/vurlene_q2_needed.iff", itemName = "Jar of Healing Salve" }
    },
    rewards =
    {
      { rewardType = "faction", faction = "mtn_clan", amount = 10 },
      { rewardType = "credits", amount = 75 },
      --DO WE NEED A NEW TEMPLATE FOR THIS 'STIMPACK C' REWARD ITEM WITH SPECIAL STATS and MIND HEAL??
      { rewardType = "loot",  lootGroup = "object/tangible/medicine/crafted/medpack_damage_c.iff" }
    }
  },
  {
    missionType = "confiscate",
    primarySpawns =
    {
      { npcTemplate = "nightsister_ranger", planetName = "dathomir", npcName = "a Nightsister Patrol Leader" }
    },
    secondarySpawns =
    {
      { npcTemplate = "nightsister_initiate", planetName = "dathomir", npcName = "" },
      { npcTemplate = "nightsister_initiate", planetName = "dathomir", npcName = "" }
    },
    itemSpawns =
    {
      { itemTemplate = "object/tangible/mission/quest_item/vurlene_q3_needed.iff", itemName = "Jar of Healing Salve" }
    },
    rewards =
    {
      { rewardType = "faction", faction = "mtn_clan", amount = 10 },
      { rewardType = "credits", amount = 100 },
      --DO WE NEED A NEW TEMPLATE FOR THIS 'STIMPACK D' REWARD ITEM WITH SPECIAL STATS and MIND HEAL??
      { rewardType = "loot",  lootGroup = "object/tangible/medicine/crafted/medpack_damage_d.iff" }
    }
  }
}

aujante_klee_missions =
{
  {
    missionType = "escort",
    primarySpawns =
    {
      { npcTemplate = "theme_park_singing_mountain_clan_dragoon", planetName = "dathomir", npcName = "Aldiae" }
    },
    secondarySpawns =
    {

    },
    itemSpawns =
    {

    },
    rewards =
    {
      { rewardType = "faction", faction = "nightsister", amount = 10 },
      { rewardType = "credits", amount = 200 }
    }
  },
  {
    missionType = "confiscate",
    primarySpawns =
    {
      { npcTemplate = "nightsister_stalker", planetName = "dathomir", npcName = "Vhuransa" }
    },
    secondarySpawns =
    {

    },
    itemSpawns =
    {
      { itemTemplate = "object/tangible/mission/quest_item/aujante_klee_q2_needed.iff", itemName = "a Sacred Tome" }
    },
    rewards =
    {
      { rewardType = "faction", faction = "nightsister", amount = 450 },
      { rewardType = "credits", amount = 500 }
    }
  },
  {
    missionType = "escort",
    primarySpawns =
    {
      { npcTemplate = "theme_park_singing_mountain_clan_initiate", planetName = "dathomir", npcName = "Jhuryx" }
    },
    secondarySpawns =
    {
      { npcTemplate = "nightsister_stalker", planetName = "dathomir", npcName = "" },
      { npcTemplate = "nightsister_rancor_tamer", planetName = "dathomir", npcName = "" }
    },
    itemSpawns =
    {

    },
    rewards =
    {
      { rewardType = "faction", faction = "nightsister", amount = 10 },
      { rewardType = "credits", amount = 300 }
    }
  },
  {
    missionType = "assassinate",
    primarySpawns =
    {
      { npcTemplate = "nightsister_spell_weaver", planetName = "dathomir", npcName = "Morathax" }
    },
    secondarySpawns =
    {
      { npcTemplate = "nightsister_initiate", planetName = "dathomir", npcName = "" },
      { npcTemplate = "nightsister_initiate", planetName = "dathomir", npcName = "" },
      { npcTemplate = "nightsister_outcast", planetName = "dathomir", npcName = "" },
      { npcTemplate = "nightsister_outcast", planetName = "dathomir", npcName = "" }
    },
    itemSpawns =
    {

    },
    rewards =
    {
      { rewardType = "faction", faction = "mtn_clan", amount = 410 },
      { rewardType = "credits", amount = 500 }
    }
  }
}

npcMapSingingMountainClan =
{
  {
    spawnData = { planetName = "dathomir", npcTemplate = "vhaunda", x = -22.3, z = 2, y = 5.05, direction = 5, cellID = 2665881, position = STAND },
    npcNumber = 1,
    stfFile = "@static_npc/dathomir/vhaunda",
    missions = vhaunda_missions
  },
  {
    spawnData = { planetName = "dathomir", npcTemplate = "izaryx", x = -12, z = 2, y = -4, direction = -110, cellID = 2665882, position = STAND },
    npcNumber = 2,
    stfFile = "@static_npc/dathomir/dathomir_singingmountainclanstronghold_izaryx",
    missions = izaryx_missions
  },
  {
    spawnData = { planetName = "dathomir", npcTemplate = "zideera", x = -14.2, z = 1.9, y = -21, direction = -20, cellID = 2665883, position = STAND },
    npcNumber = 4,
    stfFile = "@static_npc/dathomir/dathomir_singingmountainclanstronghold_zideera",
    missions = zideera_missions
  },
  {
    spawnData = { planetName = "dathomir", npcTemplate = "vurlene", x = -12, z = 3, y = 9.5, direction = 72, cellID = 2665880, position = STAND },
    npcNumber = 8,
    stfFile = "@static_npc/dathomir/vurlene",
    missions = vurlene_missions
  },
  {
    spawnData = { planetName = "dathomir", npcTemplate = "aujante_klee", x = 3, z = 3, y = -5.2, direction = 176, cellID = 2665884, position = STAND },
    npcNumber = 16,
    stfFile = "@static_npc/dathomir/dathomir_singingmountainclanstronghold_aujante_klee",
    missions = aujante_klee_missions
  }
}

ThemeParkSingingMountainClan = ThemeParkLogic:new {
  numberOfActs = 1,
  npcMap = npcMapSingingMountainClan,
  className = "ThemeParkSingingMountainClan",
  screenPlayState = "singing_mountain_clan_theme_park"
}

registerScreenPlay("ThemeParkSingingMountainClan", true)

theme_park_singing_mountain_clan_mission_giver_conv_handler = mission_giver_conv_handler:new {
  themePark = ThemeParkSingingMountainClan
}
theme_park_singing_mountain_clan_mission_target_conv_handler = mission_target_conv_handler:new {
  themePark = ThemeParkSingingMountainClan
}