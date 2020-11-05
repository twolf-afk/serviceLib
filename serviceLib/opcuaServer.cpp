#include "opcuaServer.h"

#include "logUtil.h"
#include "methodSaveWsdl.h"
#include "methodGetProcess.h"
#include "methodGetService.h"
#include "methodSaveProcess.h"

#include <open62541/server_config_default.h>

opcuaServer::opcuaServer()
{
	logUtil::writeLogMessageToConsoleAndFile("info", typeid(opcuaServer).name(), __LINE__, "Create Server Instance");

	server = UA_Server_new();
	UA_ServerConfig_setDefault(UA_Server_getConfig(server));
	
	methodSaveWsdl::createMethod(server);
	methodGetService::createMethod(server);
	methodSaveProcess::createMethod(server);
	methodGetProcess::createMethod(server);

}

void opcuaServer::startServer()
{
	logUtil::writeLogMessageToConsoleAndFile("info", typeid(opcuaServer).name(), __LINE__, "Start Server");

	UA_StatusCode status = UA_Server_run(server, &running);
}

opcuaServer::~opcuaServer()
{
	logUtil::writeLogMessageToConsoleAndFile("info", typeid(opcuaServer).name(), __LINE__, "Delete Server Instance");

	UA_Server_delete(server);
}