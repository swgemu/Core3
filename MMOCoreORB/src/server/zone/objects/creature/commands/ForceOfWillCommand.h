/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.l"); //Through precise focus and concentration, you recapacitate with nominal side effects.
		}


		player->setPosture(CreaturePosture::UPRIGHT, true);
		incapTask->cancel();
		player->removePendingTask("incapacitationRecovery");
		player->addCooldown("tkaForceOfWill", 3600 * 1000);

		return SUCCESS;
	}
};

#endif //FORCEOFWILLCOMMAND_H_
