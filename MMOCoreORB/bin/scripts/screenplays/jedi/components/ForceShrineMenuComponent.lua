ForceShrineMenuComponent = {}

function ForceShrineMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)

	if (CreatureObject(pPlayer):hasSkill("force_title_jedi_novice")) then
		menuResponse:addRadialMenuItem(120, 3, "@jedi_trials:meditate") -- Meditate
	end

	if (CreatureObject(pPlayer):hasSkill("force_title_jedi_rank_02")) then
		menuResponse:addRadialMenuItem(121, 3, "@force_rank:recover_jedi_items") -- Recover Jedi Items
	end

end

function ForceShrineMenuComponent:handleObjectMenuSelect(pObject, pPlayer, selectedID)
	if (pPlayer == nil or pObject == nil) then
		return 0
	end

	if (selectedID == 120 and CreatureObject(pPlayer):hasSkill("force_title_jedi_novice")) then
		if (CreatureObject(pPlayer):getPosture() ~= CROUCHED) then
			CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:show_respect") -- Must respect
		else
			self:doMeditate(pObject, pPlayer)
		end
	elseif (selectedID == 121 and CreatureObject(pPlayer):hasSkill("force_title_jedi_rank_02")) then
		self:recoverRobe(pPlayer)
	end

	return 0
end

function ForceShrineMenuComponent:doMeditate(pObject, pPlayer)
	local isJediPadawan = CreatureObject(pPlayer):hasSkill("force_title_jedi_rank_02")
	local isJediKnight = CreatureObject(pPlayer):hasSkill("force_title_jedi_rank_03")
	local currentTrial = JediTrials:getCurrentTrial(pPlayer)
	local knightAvailable = CreatureObject(pPlayer):villageKnightPrereqsMet("")

	if (not isJediPadawan) then
		-- Unlock Padawan
		if (CreatureObject(pPlayer):hasScreenPlayState(64, "VillageJediProgression")) then
		-- TODO: Change to generic message after padawan trials complete if not qualified for Knight trials.
		elseif (CreatureObject(pPlayer):hasScreenPlayState(32, "VillageJediProgression")) then
			if (not JediTrials:isOnPadawanTrials(pPlayer)) then
				PadawanTrials:startPadawanTrials(pObject, pPlayer)
			elseif (currentTrial == 0) then
				PadawanTrials:startNextPadawanTrial(pObject, pPlayer)
			else
				PadawanTrials:showCurrentTrial(pObject, pPlayer)
			end
		else
			CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:force_shrine_wisdom_" .. getRandomNumber(1, 15))
		end
	end
end

function ForceShrineMenuComponent:recoverRobe(pPlayer)
	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	if not (SceneObject(pInventory):isContainerFullRecursive()) then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		local pItem = giveItem(pInventory, "object/tangible/wearables/robe/robe_jedi_padawan.iff", -1)
		CreatureObject(pPlayer):sendSystemMessage("@force_rank:items_recovered")
	else
		CreatureObject(pPlayer):sendSystemMessage("@jedi_spam:inventory_full_jedi_robe")
	end
end
