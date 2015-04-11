local ObjectManager = require("managers.object.object_manager")

huff_darklighter_missions =
	{
		{
			missionType = "escort",
			preReq = { type = "state", screenPlayState = "krayt_skull_epic_quest", state = 2 },
			primarySpawns =
			{
				{ npcTemplate = "huff_niece", planetName = "tatooine", npcName = "Huff's Niece" }
			},
			secondarySpawns = {},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 500 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "thug", planetName = "tatooine", npcName = "Slaver" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "loot",  lootGroup = "task_reward_huff_quest_krayt_dragon_skull" }
			}
		},
	}

huff_guard_missions =
	{
		{
			missionType = "deliver",
			preReq = { type = "item", itemTemplate = "object/tangible/loot/quest/rifle_quest_tusken.iff", destroy = false },
			primarySpawns =
			{
				{ npcTemplate = "huff_delivery_guy", planetName = "tatooine", npcName = "Delivery Guy" }
			},
			secondarySpawns = {},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/ledger_s01.iff", itemName = "A Ledger" }
			},
			rewards = {}
		},
	}

borvo_the_hutt_missions =
	{
		{
			missionType = "assassinate",
			preReq = { type = "state", screenPlayState = "krayt_skull_epic_quest", state = 1 },
			primarySpawns =
			{
				{ npcTemplate = "srio", planetName = "naboo", npcName = "Sri-O" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 100 },
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "montrus", planetName = "naboo", npcName = "Montrus" }
			},
			secondarySpawns =	{},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/keepsakes.iff", itemName = "Precious Keep-sakes" }
			},
			rewards =
			{
				{ rewardType = "loot",  lootGroup = "task_reward_huff_quest_tusken_king_rifle" }
			}
		},
	}

thale_dusturnner_missions =
	{
		{
			missionType = "assassinate",
			preReq = { type = "item", itemTemplate = "object/tangible/loot/quest/huff_quest_corsec_badge.iff", destroy = false },
			primarySpawns =
			{
				{ npcTemplate = "aldalad", planetName = "corellia", npcName = "Aldalad" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 25 },
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "maerzen", planetName = "corellia", npcName = "Maerzen" }
			},
			secondarySpawns =	{},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/briefcase_s01.iff", itemName = "A Locked Briefcase" }
			},
			rewards =
			{
				{ rewardType = "loot",  lootGroup = "task_reward_huff_quest_borvos_money" }
			}
		}
	}

borvo_guard_missions =
	{
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "dagorel", planetName = "naboo", npcName = "Dagorel" }
			},
			secondarySpawns = {},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 25 },
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "frangee", planetName = "naboo", npcName = "Frangee" }
			},
			secondarySpawns =	{},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/ledger_s01.iff", itemName = "A Ledger" }
			},
			rewards =
			{
				{ rewardType = "loot",  lootGroup = "task_reward_huff_quest_corsec_badge" }
			}
		}
	}

npcMapKraytDragonSkull =
	{
		{
			spawnData = { planetName = "tatooine", npcTemplate = "huff_darklighter", x = 0.1, z = 1.0, y = 2.4, direction = 177, cellID = 1845354, position = STAND },
			worldPosition = { x = -698, y = -6750 },
			npcNumber = 16,
			stfFile = "@epic_quest/krayt_skull/huff_darklighter",
			missions = huff_darklighter_missions
		},
		{
			spawnData = { planetName = "tatooine", npcTemplate = "huffs_guard", x = -694.1, z = 8.0, y = -6733.8, direction = -12, cellID = 0, position = STAND },
			worldPosition = { x = -694, y = -6734 },
			npcNumber = 8,
			stfFile = "@epic_quest/krayt_skull/huff_guard",
			missions = huff_guard_missions
		},
		{
			spawnData = { planetName = "naboo", npcTemplate = "borvo_the_hutt", x = -30.8, z = -0.5, y = 7.5, direction = 33, cellID = 121, position = STAND },
			worldPosition = { x = 4875, y = -4590 },
			npcNumber = 4,
			stfFile = "@epic_quest/krayt_skull/borvo_the_hutt",
			missions = borvo_the_hutt_missions
		},
		{
			spawnData = { planetName = "corellia", npcTemplate = "thale_dustrunner", x = -0.05, z = 3.08, y = -10.94, direction = 187.3, cellID = 1855463, position = STAND },
			worldPosition = { x = -209, y = -4581 },
			npcNumber = 2,
			stfFile = "@epic_quest/krayt_skull/corsec_captain",
			missions = thale_dusturnner_missions
		},
		{
			spawnData = { planetName = "naboo", npcTemplate = "borvos_guard", x = -18.4, z = -0.9, y = 18.3, direction = 173, cellID = 120, position = STAND },
			worldPosition = { x = 4888, y = -4600 },
			npcNumber = 1,
			stfFile = "@epic_quest/krayt_skull/borvo_guard",
			missions = borvo_guard_missions
		},
	}

KraytDragonSkull = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapKraytDragonSkull,
	className = "KraytDragonSkull",
	screenPlayState = "krayt_dragon_skull",
	distance = 800
}

registerScreenPlay("KraytDragonSkull", true)

KraytSkullContainerComponent = {}

function KraytSkullContainerComponent:transferObject(pContainer, pObj, slot)
	local pPlayer = KraytDragonSkull:getObjOwner(pObj)

	if (pPlayer == nil) then
		return 0
	end

	if (SceneObject(pContainer):getObjectName() == "borvo_the_hutt") then
		local object = SceneObject(pObj)
		if (object:getTemplateObjectPath() == "object/tangible/loot/quest/huff_quest_borvos_money.iff") then
			spatialChat(pContainer, "Good")
			KraytDragonSkull:setState(CreatureObject(pPlayer), 1, "krayt_skull_epic_quest")
			object:destroyObjectFromWorld()
			object:destroyObjectFromDatabase()
			return 1
		else
			spatialChat(pContainer, "@static_npc/naboo/borvo:notit_1")
			return 0
		end
	elseif (SceneObject(pContainer):getCustomObjectName() == "Huff Darklighter") then
		local object = SceneObject(pObj)
		if (KraytDragonSkull:getActiveNpcNumber(pPlayer) ~= 16) then
			spatialChat(pContainer, "@epic_quest/krayt_skull/huff_darklighter:notyet")
		elseif (object:getTemplateObjectPath() == "object/tangible/loot/quest/rifle_quest_tusken.iff") then
			spatialChat(pContainer, "@epic_quest/krayt_skull/huff_darklighter:good")
			KraytDragonSkull:setState(CreatureObject(pPlayer), 2, "krayt_skull_epic_quest")
			object:destroyObjectFromWorld()
			object:destroyObjectFromDatabase()
			return 1
		else
			spatialChat(pContainer, "@epic_quest/krayt_skull/huff_darklighter:notit")
			return 0
		end
	end

	return 0
end

function KraytSkullContainerComponent:canAddObject(pContainer, pObj, slot)
	local pPlayer = KraytDragonSkull:getObjOwner(pObj)

	if (pPlayer == nil) then
		return -1
	end

	if (SceneObject(pContainer):getObjectName() == "borvo_the_hutt" and CreatureObject(pPlayer):hasScreenPlayState(1, "krayt_skull_epic_quest")) or
		(SceneObject(pContainer):getCustomObjectName() == "Huff Darklighter" and CreatureObject(pPlayer):hasScreenPlayState(2, "krayt_skull_epic_quest")) then
		return -1
	else
		return true
	end
end

function KraytSkullContainerComponent:removeObject(pContainer, pObj, slot)
	return -1
end

function KraytDragonSkull:setState(creatureObject, state, questGiver)
	creatureObject:setScreenPlayState(state, questGiver)
end

function KraytDragonSkull:removeState(creatureObject, state, questGiver)
	creatureObject:removeScreenPlayState(state, questGiver)
end

function KraytDragonSkull:getObjOwner(pObj)
	local pPlayerInv = SceneObject(pObj):getParent()

	if (pPlayerInv == nil) then
		return nil
	end

	local parent = SceneObject(pPlayerInv):getParent()

	if (parent == nil) then
		return nil
	end

	if (SceneObject(parent):isCreatureObject()) then
		return parent
	end

	return nil
end

-- Custom spawnNpcs to handle setting npcs as containers for quest item turnin
function KraytDragonSkull:spawnNpcs()
	for i = 1, # self.npcMap do
		local npcSpawnData = self.npcMap[i].spawnData
		if isZoneEnabled(npcSpawnData.planetName) then
			local pNpc = spawnMobile(npcSpawnData.planetName, npcSpawnData.npcTemplate, 1, npcSpawnData.x, npcSpawnData.z, npcSpawnData.y, npcSpawnData.direction, npcSpawnData.cellID)
			if npcSpawnData.position == SIT then
				CreatureObject(pNpc):setState(STATESITTINGONCHAIR)
			end
			if npcSpawnData.npcTemplate == "borvo_the_hutt" or npcSpawnData.npcTemplate == "huff_darklighter" then
				SceneObject(pNpc):setContainerComponent("KraytSkullContainerComponent")
			end
		end
	end
end

krayt_dragon_skull_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = KraytDragonSkull
}
krayt_dragon_skull_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = KraytDragonSkull
}