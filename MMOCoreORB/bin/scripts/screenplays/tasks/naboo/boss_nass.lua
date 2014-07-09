boss_nass_missions =
  {
    {
      missionType = "deliver",
      primarySpawns =
      {
        { npcTemplate = "pol_revver", planetName = "naboo", npcName = "Pol Revver" }
      },
      secondarySpawns =
      {
        { npcTemplate = "stormtrooper", planetName = "naboo", npcName = "" },
        { npcTemplate = "stormtrooper", planetName = "naboo", npcName = "" },
      },
      itemSpawns =
      {
        { itemTemplate = "object/tangible/mission/quest_item/nass_q1_needed.iff", itemName = "Datadisc" }
      },
      rewards =
      {
        { rewardType = "credits", amount = 50 },
      }
    },
    {
      missionType = "escort",
      primarySpawns =
      {
        { npcTemplate = "jaanie", planetName = "naboo", npcName = "Jaanie" }
      },
      secondarySpawns = {},
      itemSpawns = {},
      rewards =
      {
        { rewardType = "credits", amount = 50 },
      }
    },
    {
      missionType = "escort",
      primarySpawns =
      {
        { npcTemplate = "fassa", planetName = "naboo", npcName = "Fassa" }
      },
      secondarySpawns =
      {
        { npcTemplate = "stormtrooper", planetName = "naboo", npcName = "" },
        { npcTemplate = "stormtrooper", planetName = "naboo", npcName = "" },
      },
      itemSpawns = {},
      rewards =
      {
        { rewardType = "credits", amount = 150 },
      }
    },
    {
      missionType = "assassinate",
      primarySpawns =
      {
        { npcTemplate = "stormtrooper_squad_leader", planetName = "naboo", npcName = "Stormtrooper Squad Leader" }
      },
      secondarySpawns =
      {
        { npcTemplate = "stormtrooper", planetName = "naboo", npcName = "" },
        { npcTemplate = "stormtrooper", planetName = "naboo", npcName = "" },
        { npcTemplate = "stormtrooper", planetName = "naboo", npcName = "" },
        { npcTemplate = "stormtrooper", planetName = "naboo", npcName = "" },
        { npcTemplate = "stormtrooper", planetName = "naboo", npcName = "" }
      },
      itemSpawns = {},
      rewards =
      {
        { rewardType = "credits", amount = 500 },
      }
    },
  }

npcMapBossNass =
  {
    {
      spawnData = { planetName = "naboo", npcTemplate = "boss_nass", x = -1991, z = 5.3, y = -5422, direction = -114, cellID = 0, position = STAND },
      worldPosition = { x = -1991, y = -5422 },
      npcNumber = 1,
      stfFile = "@static_npc/naboo/boss_nass",
      missions = boss_nass_missions
    }
  }

BossNass = ThemeParkLogic:new {
  numberOfActs = 1,
  npcMap = npcMapBossNass,
  className = "BossNass",
  screenPlayState = "boss_nass_quest",
  distance = 1000,
  faction = FACTIONREBEL
}

registerScreenPlay("BossNass", true)

boss_nass_mission_giver_conv_handler = mission_giver_conv_handler:new {
  themePark = BossNass
}
boss_nass_mission_target_conv_handler = mission_target_conv_handler:new {
  themePark = BossNass
}