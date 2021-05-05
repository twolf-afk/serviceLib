#include "methodSaveServiceOfProcess.h"

#include "logUtil.h"
#include "open62541Util.h"
#include "configFileUtil.h"
#include "util.h"

static UA_StatusCode saveService (
    UA_Server* server, const UA_NodeId* sessionId,
    void* sessionHandle, const UA_NodeId* methodId,
    void* methodContext, const UA_NodeId* objectId,
    void* objectContext, size_t inputSize,
    const UA_Variant* input, size_t outputSize,
    UA_Variant* output) {

    logUtil::writeLogMessageToConsoleAndFile("info", typeid(methodSaveServiceOfProcess).name(), __LINE__, "saveServiceOfProcess was called");

    UA_String* firstInput = (UA_String*)input[0].data;
    UA_String* secondInput = (UA_String*)input[1].data;
    UA_String* thirdInput = (UA_String*)input[2].data;

    std::string processName = open62541Util::uaStringPtrToStdString(firstInput);
    std::string serviceName = open62541Util::uaStringPtrToStdString(secondInput);
    std::string text = open62541Util::uaStringPtrToStdString(thirdInput);

    if (!util::stringContainsSubstring(serviceName, "wsdl")) {
        serviceName += ".wsdl";
    }

    configFileUtil::confParam config = configFileUtil::readConfig();

    util::createDirectory(config.pathToProcesses + "/" + processName + "/");

    util::saveStringAsFile(text, config.pathToProcesses + "/" + processName + "/" + serviceName);

    logUtil::writeLogMessageToConsoleAndFile("info", typeid(methodSaveServiceOfProcess).name(), __LINE__, "Save Service: " + serviceName + " in " + processName);

    return UA_STATUSCODE_GOOD;
}

void methodSaveServiceOfProcess::createMethod(UA_Server* server) {
    UA_Argument inputArguments[3];

    char inputProcessName[] = "Process Name";
    inputArguments[0] = createStringArgument(inputProcessName);

    char inputServiceName[] = "Service Name";
    inputArguments[1] = createStringArgument(inputServiceName);

    char inputText[] = "Text";
    inputArguments[2] = createStringArgument(inputText);

    char outputText[] = "Result";
    UA_Argument outputArgument = createStringArgument(outputText);

    char methodeName[] = "Save Service of Process";
    UA_MethodAttributes methodAttributes = createMethodAttributes(methodeName);
    
    UA_Server_addMethodNode(
        server, UA_NODEID_STRING(1, methodeName),
        UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
        UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
        UA_QUALIFIEDNAME(1, methodeName),
        methodAttributes, &saveService,
        3, inputArguments, 1, &outputArgument, NULL, NULL
    );
}