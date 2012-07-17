MosEisleyScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "MosEisleyScreenPlay"
}

registerScreenPlay("MosEisleyScreenPlay", true)

function MosEisleyScreenPlay:start()
	self:spawnMobiles()
end

function MosEisleyScreenPlay:spawnMobiles()
end