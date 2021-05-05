#include "methodGetProcess.h"

#include "logUtil.h"
#include "util.h"
#include "configFileUtil.h"
#include "open62541Util.h"

static UA_StatusCode getProcess(
    UA_Server* server, const UA_NodeId* sessionId,
    void* sessionHandle, const UA_NodeId* methodId,
    void* methodContext, const UA_NodeId* objectId,
    void* objectContext, size_t inputSize,
    const UA_Variant* input, size_t outputSize,
    UA_Variant* output) {

    logUtil::writeLogMessageToConsoleAndFile("info", typeid(methodGetProcess).name(), __LINE__, "getProcess was called");

    UA_String* Input = (UA_String*)input->data;
    std::string processName = open62541Util::uaStringPtrToStdString(Input);
    std::string directoryOfProcess = util::splitString(processName, ".")[0];

    logUtil::writeLogMessageToConsoleAndFile("info", typeid(methodGetProcess).name(), __LINE__, "Get Process: " + processName);

    if (!util::stringContainsSubstring(processName, "xml")) {
        processName += ".xml";
    }

    configFileUtil::confParam config = configFileUtil::readConfig();

    std::string processAsString = util::getFile(config.pathToProcesses + "/" + directoryOfProcess + "/" + processName);
    
    const char* process = processAsString.c_str();
    UA_String result;
    UA_String_init(&result);
    result.length = strlen(process);
    result.data = (UA_Byte*)process;

    UA_Variant_setScalarCopy(output, &result, &UA_TYPES[UA_TYPES_STRING]);

    return UA_STATUSCODE_GOOD;
}

void methodGetProcess::createMethod(UA_Server* server) {

    char inputText[] = "Get Process";
    UA_Argument inputArgument = createStringArgument(inputText);

    char outputText[] = "Result";
    UA_Argument outputArgument = createStringArgument(outputText);

    char methodeName[] = "Get Process";
    UA_MethodAttributes methodAttributes = createMethodAttributes(methodeName);

    UA_Server_addMethodNode(
        server, UA_NODEID_STRING(1, methodeName),
        UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
        UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
        UA_QUALIFIEDNAME(1, methodeName),
        methodAttributes, &getProcess,
        1, &inputArgument, 1, &outputArgument, NULL, NULL
    );
}