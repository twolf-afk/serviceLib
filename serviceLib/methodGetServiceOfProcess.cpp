#include "methodGetServiceOfProcess.h"

#include "logUtil.h"
#include "util.h"
#include "configFileUtil.h"
#include "open62541Util.h"

static UA_StatusCode getService(
    UA_Server* server, const UA_NodeId* sessionId,
    void* sessionHandle, const UA_NodeId* methodId,
    void* methodContext, const UA_NodeId* objectId,
    void* objectContext, size_t inputSize,
    const UA_Variant* input, size_t outputSize,
    UA_Variant* output) {

    logUtil::writeLogMessageToConsoleAndFile("info", typeid(methodGetServiceOfProcess).name(), __LINE__, "getService was called");

    UA_String* firstInput = (UA_String*)input[0].data;
    std::string arguments = open62541Util::uaStringPtrToStdString(firstInput);

    std::vector<std::string> argumentVector = util::splitString(arguments, ";");

    std::string serviceName = argumentVector[0];
    std::string processName = argumentVector[1];

    if (!util::stringContainsSubstring(serviceName, "wsdl")) {
        serviceName += ".wsdl";
    }

    logUtil::writeLogMessageToConsoleAndFile("info", typeid(methodGetServiceOfProcess).name(), __LINE__, "Get Service: " + serviceName + " of Process: " + processName);

    configFileUtil::confParam config = configFileUtil::readConfig();

    std::string serviceAsString = util::getFile(config.pathToProcesses + processName + "/" + serviceName);
    const char* service = serviceAsString.c_str();

    UA_String result;
    UA_String_init(&result);

    result.length = strlen(service);
    result.data = (UA_Byte*)service;

    UA_Variant_setScalarCopy(output, &result, &UA_TYPES[UA_TYPES_STRING]);

    return UA_STATUSCODE_GOOD;
}

void methodGetServiceOfProcess::createMethod(UA_Server* server) {

    char inputServiceName[] = "Servicename + ; + Processname";
    UA_Argument inputArgument = createStringArgument(inputServiceName);

    char outputText[] = "Result";
    UA_Argument outputArgument = createStringArgument(outputText);

    char methodeName[] = "Get Service of Process";
    UA_MethodAttributes methodAttributes = createMethodAttributes(methodeName);

    UA_Server_addMethodNode(
        server, UA_NODEID_STRING(1, methodeName),
        UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
        UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
        UA_QUALIFIEDNAME(1, methodeName),
        methodAttributes, &getService,
        1, &inputArgument, 1, &outputArgument, NULL, NULL
    );
}