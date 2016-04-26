local ObjectManager = require("managers.object.object_manager")

enclaveVotingTerminal = { }

function enclaveVotingTerminal:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local response = LuaObjectMenuResponse(pMenuResponse)
	-- Root
	response:addRadialMenuItem(151, 3, "@force_rank:vote_status")
	response:addRadialMenuItemToRadialID(151, 152, 3, "@force_rank:record_vote")
	response:addRadialMenuItemToRadialID(151, 153, 3, "@force_rank:accept_promotion")
	response:addRadialMenuItemToRadialID(151, 154, 3, "@force_rank:petition")

	if (CreatureObject(pPlayer):hasSkill("force_rank_light_rank_07")) then
		response:addRadialMenuItem(155, 3, "@force_rank:demote_member")
	end

	response:addRadialMenuItem(156, 3, "@force_rank:recover_jedi_items")

end

function enclaveVotingTerminal:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)

	local suiManager = LuaSuiManager()

	if (selectedID == 151) then
		SuiFRSVotingTerminal:voteStatusSelect(pPlayer, pSceneObject)
	elseif (selectedID == 152) then

	elseif (selectedID == 153) then

	elseif (selectedID == 154) then
		SuiFRSVotingTerminal:petitionForRank(pPlayer, pSceneObject)
	elseif (selectedID == 155) then

	elseif (selectedID == 156) then

	end

end
