parallelsequencetest0 = {
	{"root", "ParallelSequence", "none", PARALLELSEQUENCEBEHAVIOR},
	{"fail", "Failure", "root", BEHAVIOR},
	{"succeed", "Succeed", "root", BEHAVIOR}
}

addAiTemplate("parallelsequencetest0", parallelsequencetest0)