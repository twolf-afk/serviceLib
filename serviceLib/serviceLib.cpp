
#include "serviceLib.h"

#include "logUtil.h"
#include "opcuaServer.h"
#include "util.h"

int main()
{
	
	logUtil::writeLogMessageToConsoleAndFile("info", typeid(serviceLib).name(), __LINE__, "Start Service Lib");

	opcuaServer server = opcuaServer();

	server.startServer();

	server.~opcuaServer();

	logUtil::writeLogMessageToConsoleAndFile("info", typeid(serviceLib).name(), __LINE__, "Stopp Service Lib");
}
