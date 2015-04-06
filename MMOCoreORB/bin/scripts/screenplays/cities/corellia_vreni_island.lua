VreniIslandScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "VreniIslandScreenPlay",
	
}

registerScreenPlay("VreniIslandScreenPlay", true)

function VreniIslandScreenPlay:start()
	if (isZoneEnabled("corellia")) then
		self:spawnMobiles()
		self:spawnSceneObjects()
	end
end

function VreniIslandScreenPlay:spawnSceneObjects()
 
	-- Shuttleport
    spawnSceneObject("corellia", "object/static/particle/particle_distant_ships_rebel.iff", -5551, 100, -6041, 0, 1, 0, 0, 0)
   
end

function VreniIslandScreenPlay:spawnMobiles()

	spawnMobile("corellia", "businessman",60,-5428.59,24.1812,-6228.31,140.458,0)
	spawnMobile("corellia", "cll8_binary_load_lifter",60,-5696,14.6,-6154.2,75,0)
	spawnMobile("corellia", "commoner",60,-5505.69,23.4,-6118.63,272.183,0)
	spawnMobile("corellia", "commoner",60,-5468.42,23.4,-6144.87,182.034,0)
	spawnMobile("corellia", "commoner",60,-5495.01,23.4,-6190.5,325.039,0)
	spawnMobile("corellia", "commoner",60,-5504.22,23.4,-6211.56,1.34408,0)
	spawnMobile("corellia", "commoner",60,-5488.87,23.8964,-6242.6,304.866,0)
	spawnMobile("corellia", "commoner",60,-5519.68,23.4,-6224.4,134.773,0)
	spawnMobile("corellia", "commoner",60,-5551.88,23.4,-6221.48,124.882,0)
	spawnMobile("corellia", "commoner",60,-5549.18,23.4,-6189.25,119.296,0)
	spawnMobile("corellia", "commoner",60,-5571.88,23.4,-6129.85,97.3312,0)
	spawnMobile("corellia", "commoner",60,-5385.68,24,-6239.93,118.359,0)
	spawnMobile("corellia", "commoner",60,-5708.22,14.6,-6157.68,63.8572,0)
	spawnMobile("corellia", "commoner",60,-5686.69,14.6,-6148.05,214.943,0)
	spawnMobile("corellia", "commoner",60,-5693.27,14.6,-6177.12,293.479,0)
	spawnMobile("corellia", "corsec_inspector_sergeant",300,24.9055,1.28309,5.31569,360.011,2775414)
	spawnMobile("corellia", "corsec_investigator",300,8.4,1.0,10.8,-172,2775413)
	spawnMobile("corellia", "corsec_detective",300,8.2,1.0,8.7,7,2775413)
	spawnMobile("corellia", "corsec_master_sergeant",300,24.9055,1.28309,6.41569,180.019,2775414)
	spawnMobile("corellia", "rebel_specforce_pathfinder",300,-5538.4,16.4902,-6054.7,182.005,0)
	spawnMobile("corellia", "specforce_master_sergeant",300,-5533.2,23.4,-6202.2,46,0)
	spawnMobile("corellia", "specforce_technician",300,-5405,25,-6220,37,0)
	spawnMobile("corellia", "rebel_specforce_pathfinder",300,-5534.1,23.4,-6217.9,138.004,0)
	spawnMobile("corellia", "specforce_infiltrator",300,-5549.5,23.4,-6202.1,310.009,0)
	spawnMobile("corellia", "specforce_procurement_specialist",300,-5549,23.4,-6217.8,-139,0)
	spawnMobile("corellia", "rebel_specforce_pathfinder",300,-5429.8,24,-6218.9,0,0)
	spawnMobile("corellia", "rebel_specforce_captain",300,-5411.4,24.9599,-6219.3,5.00012,0)
	spawnMobile("corellia", "specforce_marine",300,-5398,24.2,-6242.9,81,0)
	spawnMobile("corellia", "specforce_marine",300,-5443.6,24,-6243,282.008,0)
	spawnMobile("corellia", "specforce_marine",300,-5716.1,14.6,-6153.1,269.008,0)
	spawnMobile("corellia", "specforce_infiltrator",300,-5716.1,14.6,-6147.5,271.008,0)
	spawnMobile("corellia", "specforce_marine",300,-5664,14.6,-6179.3,94.0028,0)
	spawnMobile("corellia", "rebel_specforce_pathfinder",300,-5664,14.7566,-6185.3,94.0028,0)
	spawnMobile("corellia", "eg6_power_droid",60,-5690.7,14.6,-6154.2,-87,0)
	spawnMobile("corellia", "eg6_power_droid",60,-5692.65,14.6,-6151.28,179.632,0)
	spawnMobile("corellia", "farmer",60,-22.5021,1.6,4.63468,179.972,2775415)
	spawnMobile("corellia", "gambler",60,-22.5017,1.59973,3.53494,359.971,2775415)
	spawnMobile("corellia", "informant_npc_lvl_3",0,-5559,23.4,-6220,90,0)
	spawnMobile("corellia", "karrek_flim",60,-6.11988,1.6,-7.43599,219.682,2775417)
	spawnMobile("corellia", "noble",60,-24.96,1.6,-4.79578,14.5444,2775419)
	spawnMobile("corellia", "r2",60,-5528,23.4,-6195.05,84.2678,0)                -- "R2-P2" When/if option customName is available to spawnMobile function
	spawnMobile("corellia", "scientist",60,-5557.29,23.4,-6203.08,226.081,0)
	spawnMobile("corellia", "scientist",60,-5691.18,14.6,-6133.32,248.134,0)

	spawnMobile("corellia", "trainer_entertainer",0,22.0446,-0.894993,11.7787,189,3005697)
	spawnMobile("corellia", "trainer_doctor",0,-2.9,0.7,2.5,132,7615446)
	spawnMobile("corellia", "trainer_musician",0,-5408,24.7288,-6260,50,0)

end

