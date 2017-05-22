local ObjectManager = require("managers.object.object_manager")

craftingContractorConvoHandler = conv_handler:new {}

function craftingContractorConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (not CraftingContractor:isArtisan(pPlayer)) then
		return convoTemplate:getScreen("init_no_artisan")
	elseif (CraftingContractor:hasFullContractBox(pPlayer)) then
		return convoTemplate:getScreen("init_completed_job")
	elseif (CraftingContractor:hasContractBox(pPlayer)) then
		return convoTemplate:getScreen("init_incomplete_job")
	elseif (not CraftingContractor:canTakeQuest(pPlayer)) then
		return convoTemplate:getScreen("init_on_timer")
	else
		return convoTemplate:getScreen("init")
	end
end

function craftingContractorConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "init" or screenID == "come_back_for_work") then
		CraftingContractor:resetVariables(pPlayer)
	elseif (screenID == "take_back_crate") then
		CraftingContractor:removeContractBox(pPlayer)
	elseif (screenID == "init_completed_job") then
		local pCrate = CraftingContractor:getContractBox(pPlayer)
		local crateObject = LuaContractCrate(pCrate)

		local xpType = crateObject:getXpType()
		local xpPer = crateObject:getXpAmount()
		local itemTotal = crateObject:getAmountNeeded()
		local xpTotal = xpPer * itemTotal;
		CreatureObject(pPlayer):awardExperience(xpType, xpTotal, true)

		local crateDiff = crateObject:getCrateDifficulty();
		local payAmount = ((15 + ((crateDiff - 1) * 10)) * 0.20) * itemTotal

		CreatureObject(pPlayer):addCashCredits(payAmount, true)
		CreatureObject(pPlayer):sendSystemMessageWithDI("@quest/crafting_contract/system_messages:pay_msg", payAmount)

		CraftingContractor:removeContractBox(pPlayer)
	elseif (screenID == "what_sort_of_job") then
		clonedConversation:addOption("@conversation/crafting_contractor:s_9545de7b", "job_artisan") -- A general artisan job.

		if (CraftingContractor:isArchitect(pPlayer)) then
			clonedConversation:addOption("@conversation/crafting_contractor:s_445effe2", "job_architect") -- An architect job.
		elseif (CraftingContractor:isArmorsmith(pPlayer)) then
			clonedConversation:addOption("@conversation/crafting_contractor:s_bc453c0d", "job_armorsmith") -- An armorsmith job.
		elseif (CraftingContractor:isChef(pPlayer)) then
			clonedConversation:addOption("@conversation/crafting_contractor:s_f38e5bb9", "job_chef") -- A chef job.
		elseif (CraftingContractor:isDroidEngineer(pPlayer)) then
			clonedConversation:addOption("@conversation/crafting_contractor:s_f19dea3c", "job_droidengineer") -- A droid engineer job.
		elseif (CraftingContractor:isTailor(pPlayer)) then
			clonedConversation:addOption("@conversation/crafting_contractor:s_bf890106", "job_tailor") -- A tailor job.
		elseif (CraftingContractor:isWeaponsmith(pPlayer)) then
			clonedConversation:addOption("@conversation/crafting_contractor:s_86f52ae1", "job_weaponsmith") -- A weaponsmith job.
		end

		clonedConversation:addOption("@conversation/crafting_contractor:s_220e8901", "come_back_for_work") -- On second thought, nevermind.
	elseif (string.find(screenID, "job_")) then
		local jobType = string.sub(screenID, 5)
		CraftingContractor:setQuestProfession(pPlayer, jobType)

		if (CraftingContractor:canDoHardQuests(pPlayer, jobType)) then
			clonedConversation:addOption("@conversation/crafting_contractor:s_37b62865", "diff_hard") -- I would like a difficult task.
			clonedConversation:addOption("@conversation/crafting_contractor:s_2c56a5af", "diff_medium") -- I would like a challenging task.
		elseif (CraftingContractor:canDoMediumQuests(pPlayer, jobType)) then
			clonedConversation:addOption("@conversation/crafting_contractor:s_2c56a5af", "diff_medium") -- I would like a challenging task.
		end

		clonedConversation:addOption("@conversation/crafting_contractor:s_f59f8579", "diff_easy") -- I would like an easy task.
	elseif (string.find(screenID, "diff_")) then
		writeData(SceneObject(pPlayer):getObjectID() .. ":craftingContractor:lastJobOffer", os.time())
		local jobDiff = string.sub(screenID, 6)
		local diffLevel = 0
		if (jobDiff == "easy") then
			diffLevel = 1
		elseif (jobDiff == "medium") then
			diffLevel = 2
		elseif (jobDiff == "hard") then
			diffLevel = 3
		end

		CraftingContractor:setQuestDifficulty(pPlayer, diffLevel)

		if (not CraftingContractor:pickRandomQuest(pPlayer)) then
			return pConvScreen
		end

		local questData = CraftingContractor:getQuestData(pPlayer)

		local amountNeeded = getRandomNumber(5, 10)
		CraftingContractor:setAmountToCraft(pPlayer, amountNeeded)
		clonedConversation:setDialogTextDI(amountNeeded)
		clonedConversation:setDialogTextTO(getSchematicItemName(questData[1]))

		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if (pInventory == nil or SceneObject(pInventory):isContainerFullRecursive()) then
			clonedConversation:addOption("@conversation/crafting_contractor:s_d5278cc5", "inv_full") -- Yes, I'll get to work.
		else
			clonedConversation:addOption("@conversation/crafting_contractor:s_d5278cc5", "accept_quest") -- Yes, I'll get to work.
		end

		clonedConversation:addOption("@conversation/crafting_contractor:s_b2b95d1f", "come_back_for_work") -- No, I'd rather not do that job.
	elseif (screenID == "accept_quest") then
		deleteData(SceneObject(pPlayer):getObjectID() .. ":craftingContractor:lastJobOffer")
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if (pInventory == nil or SceneObject(pInventory):isContainerFullRecursive()) then
			return pConvScreen
		end

		local crateTemplate = CraftingContractor:getCrateTemplate(pPlayer)

		if (crateTemplate == "") then
			return pConvScreen
		end

		local pCrate = giveItem(pInventory, crateTemplate, -1)

		CraftingContractor:setupCrate(pPlayer, pCrate)
	elseif (screenID == "inv_full") then
		deleteData(SceneObject(pPlayer):getObjectID() .. ":craftingContractor:lastJobOffer")
		CraftingContractor:resetVariables(pPlayer)
	end

	return pConvScreen
end
