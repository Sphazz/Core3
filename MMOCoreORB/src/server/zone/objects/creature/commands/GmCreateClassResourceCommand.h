/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GMCREATECLASSRESOURCECOMMAND_H_
#define GMCREATECLASSRESOURCECOMMAND_H_

#include "server/zone/managers/resource/ResourceManager.h"

class GmCreateClassResourceCommand : public QueueCommand {
public:

	GmCreateClassResourceCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<ResourceManager* > resourceManager = server->getZoneServer()->getResourceManager();
		if (resourceManager == nullptr) {
			creature->sendSystemMessage("Resource Manager is currently disabled.");
			return 0;
		}
		resourceManager->createResourceSpawn(creature, arguments);

		return SUCCESS;
	}

};

#endif //GMCREATECLASSRESOURCECOMMAND_H_
