awarePet = {
	{id="2672408205",	name="Sequence",	pid="none"},
	{id="2428980616",	name="Not",	pid="2672408205"},
	{id="502701510",	name="If",	pid="2428980616"},
	{id="1498311304",	name="CheckIsInCombat",	pid="502701510"},
	{id="3748783887",	name="Not",	pid="2672408205"},
	{id="2777768044",	name="If",	pid="3748783887"},
	{id="2342952551",	name="CheckPetCommand",	pid="2777768044",	args={condition=PET_STAY}},
	{id="2624621770",	name="Not",	pid="2672408205"},
	{id="1629721978",	name="If",	pid="2624621770"},
	{id="854873693",	name="CheckFollowState",	pid="1629721978",	args={condition=PATROLLING}},
	{id="3351684077",	name="SetFollowState",	pid="2672408205",	args={state=FOLLOWING}},
	{id="559248213",	name="TreeSocket",	pid="2672408205",	args={slot=MOVE}}}
addAiTemplate("awarePet", awarePet)

idlePet = {
	{id="2602839395",	name="Selector",	pid="none"},
	{id="1196938563",	name="Sequence",	pid="2602839395"},
	{id="2159332246",	name="If",	pid="1196938563"},
	{id="2297306633",	name="CheckFollowState",	pid="2159332246",	args={condition=PATROLLING}},
	{id="2901314389",	name="WriteBlackboard",	pid="1196938563",	args={key="moveMode", val=WALK}},
	{id="3579768154",	name="TreeSocket",	pid="1196938563",	args={slot=MOVE}},
	{id="3694282813",	name="Wait",	pid="1196938563",	args={duration=5.0}},
	{id="4089440207",	name="Sequence",	pid="2602839395"},
	{id="4147395704",	name="Not",	pid="4089440207"},
	{id="3397268825",	name="If",	pid="4147395704"},
	{id="1418550182",	name="CheckPetCommand",	pid="3397268825",	args={condition=PET_STAY}},
	{id="4036559077",	name="WriteBlackboard",	pid="4089440207",	args={key="moveMode", val=RUN}},
	{id="5946488",	name="AlwaysSucceed",	pid="4089440207"},
	{id="1805516334",	name="TreeSocket",	pid="5946488",	args={slot=MOVE}}}
addAiTemplate("idlePet", idlePet)

movePet = {
	{id="3554620412",	name="Selector",	pid="none"},
	{id="5634087",	name="Not",	pid="3554620412"},
	{id="2198896283",	name="Sequence",	pid="5634087"},
	{id="803210878",	name="If",	pid="2198896283"},
	{id="2465258569",	name="CheckPosture",	pid="803210878",	args={condition=UPRIGHT}},
	{id="3810468866",	name="If",	pid="2198896283"},
	{id="2565025743",	name="CheckDestination",	pid="3810468866",	args={condition=0.0}},
	{id="1780994926",	name="AlwaysFail",	pid="3554620412"},
	{id="1891282080",	name="Sequence",	pid="1780994926"},
	{id="1556803780",	name="If",	pid="1891282080"},
	{id="1543236352",	name="CheckSpeed",	pid="1556803780",	args={condition=0.0}},
	{id="2113831125",	name="CompleteMove",	pid="1891282080"},
	{id="3808575642",	name="Sequence",	pid="3554620412"},
	{id="2714566339",	name="Not",	pid="3808575642"},
	{id="1610732848",	name="If",	pid="2714566339"},
	{id="580291233",	name="CheckOwnerInRange",	pid="1610732848",	args={condition=128.0}},
	{id="2044240713",	name="AlwaysFail",	pid="3808575642"},
	{id="2024110586",	name="PetReturn",	pid="2044240713"},
	{id="4111934468",	name="FindNextPosition",	pid="3554620412"}}
addAiTemplate("movePet", movePet)

Pet = {
	{id="1955706839",	name="LookForTarget",	pid="none"}}
addAiTemplate("Pet", Pet)

targetPet = {
	{id="2727643421",	name="Selector",	pid="none"},
	{id="564148782",	name="Sequence",	pid="2727643421"},
	{id="2325957935",	name="Selector",	pid="564148782"},
	{id="1588174195",	name="Sequence",	pid="2325957935"},
	{id="2487017921",	name="If",	pid="1588174195"},
	{id="1805084865",	name="CheckPetCommand",	pid="2487017921",	args={condition=PET_GUARD}},
	{id="4093395222",	name="GetProspectFromTarget",	pid="1588174195"},
	{id="3411899925",	name="Sequence",	pid="2325957935"},
	{id="2270135938",	name="Selector",	pid="3411899925"},
	{id="2800276185",	name="If",	pid="2270135938"},
	{id="3458904446",	name="CheckPetCommand",	pid="2800276185",	args={condition=PET_ATTACK}},
	{id="2865585610",	name="If",	pid="2270135938"},
	{id="2172835025",	name="CheckPetCommand",	pid="2865585610",	args={condition=PET_SPECIAL_ATTACK1}},
	{id="2606935716",	name="If",	pid="2270135938"},
	{id="2878990487",	name="CheckPetCommand",	pid="2606935716",	args={condition=PET_SPECIAL_ATTACK2}},
	{id="4137584383",	name="GetProspectFromCommand",	pid="3411899925"},
	{id="89792960",	name="Sequence",	pid="2325957935"},
	{id="1114936193",	name="If",	pid="89792960"},
	{id="4248996732",	name="CheckPetCommand",	pid="1114936193",	args={condition=PET_PATROL}},
	{id="312457495",	name="Selector",	pid="89792960"},
	{id="312307422",	name="GetProspectFromThreatMap",	pid="312457495"},
	{id="869980090",	name="GetProspectFromDefenders",	pid="312457495"},
	{id="2780806186",	name="Selector",	pid="564148782"},
	{id="1463571926",	name="Sequence",	pid="2780806186"},
	{id="494241456",	name="If",	pid="1463571926"},
	{id="2930289772",	name="CheckTargetIsValid",	pid="494241456"},
	{id="734829524",	name="AlwaysFail",	pid="2780806186"},
	{id="532716569",	name="Sequence",	pid="734829524"},
	{id="2355980134",	name="DropProspectFromDefenders",	pid="532716569"},
	{id="3244187974",	name="EraseBlackboard",	pid="532716569",	args={param="targetProspect"}},
	{id="1977209620",	name="If",	pid="564148782"},
	{id="706949249",	name="CheckOwnerInRange",	pid="1977209620",	args={condition=128.0}},
	{id="2191514309",	name="SetDefenderFromProspect",	pid="564148782"},
	{id="3536084980",	name="AlwaysFail",	pid="2727643421"},
	{id="2207924975",	name="ExitCombat",	pid="3536084980",	args={clearDefenders=1}}}
addAiTemplate("targetPet", targetPet)

