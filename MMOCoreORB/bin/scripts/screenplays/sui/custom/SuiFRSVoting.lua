local ObjectManager = require("managers.object.object_manager")

SuiFRSVotingTerminal = {
	sides = {"dark", "light"},

	ranks = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}
}


function SuiFRSVotingTerminal:voteStatusSelect(pPlayer, pTerminal)
	if (pPlayer == nil) then
		return nil
	end

	local sui = SuiListBox.new("SuiFRSVotingTerminal", "voteStatusCallback")
	sui.setTitle("@force_rank:rank_selection")
	sui.setPrompt("@force_rank:vote_status_select")
	sui.setForceCloseDistance(10)
	sui.setTargetNetworkId(SceneObject(pTerminal):getObjectID())

	for i=1,11 do
		sui.add("@force_rank:rank" .. tostring(i), "")
	end

	sui.sendTo(pPlayer)
end

function SuiFRSVotingTerminal:noCallback(pPlayer, pSui, eventIndex)
end

function SuiFRSVotingTerminal:getVotingSide(pPlayer)
	if (CreatureObject(pPlayer):isImperial() and CreatureObject(pPlayer):hasSkill("force_rank_dark_novice")) then
		return SuiFRSVotingTerminal.sides[1]
	elseif (CreatureObject(pPlayer):isRebel() and CreatureObject(pPlayer):hasSkill("force_rank_light_novice")) then
		return SuiFRSVotingTerminal.sides[2]
	end
end

function SuiFRSVotingTerminal:voteStatusCallback(pPlayer, pSui, eventIndex, rowIndex)
	if (eventIndex == 1) then
		return
	end

	local pPageData = LuaSuiBoxPage(pSui):getSuiPageData()

	if (pPageData == nil) then
		return
	end

	rowIndex = tonumber(rowIndex)

	local votingCanidates = getForceRankVotingPetitioners(self:getVotingSide(pPlayer), rowIndex)
	local votingOpen = true -- Until we can find out when these closed?
	local seatsAvailable = getForceRankSeatsAvailable(self:getVotingSide(pPlayer), rowIndex)
	local timeLeft = getForceRankRemainingVoteTime(self:getVotingSide(pPlayer), rowIndex)

	if (votingCanidates == nil) then
		CreatureObject(pPlayer):sendSystemMessage("@force_rank:no_cluster_data_returned")
		return
	end

	local sui2 = SuiListBox.new("SuiFRSVoting", "noCallback")
	local promptTxt = "Current Stage: "

	if (votingOpen == false) then
		sui2.setTitle("@force_rank:voting_closed")
		promptTxt = promptTxt .. "CLOSED"
	else
		sui2.setTitle("@force_rank:voting_open")
		promptTxt = promptTxt .. "OPEN"
	end

	promptTxt = promptTxt .. "/nSeats Available: " .. tostring(seatsAvailable)
	promptTxt = promptTxt .. "/nTime Remaining: " .. tostring(timeLeft)

	sui2.setPrompt(promptTxt)

	sui2.add("Petitioners:", "")
	for i=1,table.getn(votingCanidates) do
		sui2.add(tostring(votingCanidates[i]) .. " -- Votes: " .. votingCanidates[i][1], "")
	end

	sui2.sendTo(pPlayer)
end

function SuiFRSVotingTerminal:petitionForRank(pPlayer, pTerminal)
	if (pPlayer == nil) then
		return nil
	end

	local sui = SuiListBox.new("SuiFRSVotingTerminal", "votePetitionCallback")
	sui.setTitle("@force_rank:rank_selection")
	sui.setPrompt("@force_rank:vote_petition_select")
	sui.setForceCloseDistance(10)
	sui.setTargetNetworkId(SceneObject(pTerminal):getObjectID())

	local highestRank = self:getHighestRank(pPlayer)

	for i=highestRank,11 do
		sui.add("@force_rank:rank" .. tostring(i), "")
	end

	sui.sendTo(pPlayer)
end

function SuiFRSVotingTerminal:getHighestRank(pPlayer)

	if (CreatureObject(pPlayer):isImperial()) then
		if (CreatureObject(pPlayer):hasSkill("force_rank_dark_master")) then
			return 11
		elseif (CreatureObject(pPlayer):hasSkill("force_rank_dark_rank_10")) then
			return 10
		elseif (CreatureObject(pPlayer):hasSkill("force_rank_dark_rank_09")) then
			return 9
		elseif (CreatureObject(pPlayer):hasSkill("force_rank_dark_rank_08")) then
			return 8
		elseif (CreatureObject(pPlayer):hasSkill("force_rank_dark_rank_07")) then
			return 7
		elseif (CreatureObject(pPlayer):hasSkill("force_rank_dark_rank_06")) then
			return 6
		elseif (CreatureObject(pPlayer):hasSkill("force_rank_dark_rank_05")) then
			return 5
		elseif (CreatureObject(pPlayer):hasSkill("force_rank_dark_rank_04")) then
			return 4
		elseif (CreatureObject(pPlayer):hasSkill("force_rank_dark_rank_03")) then
			return 3
		elseif (CreatureObject(pPlayer):hasSkill("force_rank_dark_rank_02")) then
			return 2
		elseif (CreatureObject(pPlayer):hasSkill("force_rank_dark_rank_01")) then
			return 1
		elseif (CreatureObject(pPlayer):hasSkill("force_rank_dark_novice")) then
			return 0
		end
	elseif (CreatureObject(pPlayer):isRebel()) then
		if (CreatureObject(pPlayer):hasSkill("force_rank_light_master")) then
			return 11
		elseif (CreatureObject(pPlayer):hasSkill("force_rank_light_rank_10")) then
			return 10
		elseif (CreatureObject(pPlayer):hasSkill("force_rank_light_rank_09")) then
			return 9
		elseif (CreatureObject(pPlayer):hasSkill("force_rank_light_rank_08")) then
			return 8
		elseif (CreatureObject(pPlayer):hasSkill("force_rank_light_rank_07")) then
			return 7
		elseif (CreatureObject(pPlayer):hasSkill("force_rank_light_rank_06")) then
			return 6
		elseif (CreatureObject(pPlayer):hasSkill("force_rank_light_rank_05")) then
			return 5
		elseif (CreatureObject(pPlayer):hasSkill("force_rank_light_rank_04")) then
			return 4
		elseif (CreatureObject(pPlayer):hasSkill("force_rank_light_rank_03")) then
			return 3
		elseif (CreatureObject(pPlayer):hasSkill("force_rank_light_rank_02")) then
			return 2
		elseif (CreatureObject(pPlayer):hasSkill("force_rank_light_rank_01")) then
			return 1
		elseif (CreatureObject(pPlayer):hasSkill("force_rank_light_novice")) then
			return 0
		end
	end
end

function SuiFRSVotingTerminal:voteStatusCallback(pPlayer, pSui, eventIndex, rowIndex)
	if (pPlayer == nil) then
		return
	end

	local side = self:getVotingSide(pPlayer)
	rowIndex = tonumber(rowIndex)
	local hr = self:getHighestRank(pPlayer)

	if (hr == rowIndex) then
		CreatureObject(pPlayer):sendSystemMessage("@force_rank:petition_already_have_rank")
		return
	end


	if (getSeatsAvailable(self:getVotingSide(pPlayer), rowIndex)) < 0 then
		CreatureObject(pPlayer):sendSystemMessage("@force_rank:petitioning_no_room")
		return
	end

	if (hr < rowIndex) or (hr > rowIndex) then
		CreatureObject(pPlayer):sendSystemMessage("@force_rank:petitioning_not_eligible")
		return
	end

	-- Passed all the checks
	CreatureObject(pPlayer):sendSystemMessage("@force_rank:petitioning_complete")
	addForceRankVotingPetitioner(pPlayer, rowIndex)

end
