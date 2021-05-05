#include "methodSaveProcess.h"

#include "logUtil.h"
#include "open62541Util.h"
#include "configFileUtil.h"
#include "util.h"

static UA_StatusCode saveProcess (
    UA_Server* server, const UA_NodeId* sessionId,
    void* sessionHandle, const UA_NodeId* methodId,
    void* methodContext, const UA_NodeId* objectId,
    void* objectContext, size_t inputSize,
    const UA_Variant* input, size_t outputSize,
    UA_Variant* output) {

    logUtil::writeLogMessageToConsoleAndFile("info", typeid(methodSaveProcess).name(), __LINE__, "saveProcessAsXml was called");

    UA_String* firstInput = (UA_String*)input[0].data;
    UA_String* secondInput = (UA_String*)input[1].data;

    std::string filename = open62541Util::uaStringPtrToStdString(firstInput);
    std::string text = open62541Util::uaStringPtrToStdString(secondInput);

    std::string directoryName = filename;

    if (!util::stringContainsSubstring(filename, "xml")) {
        filename += ".xml";
    }

    configFileUtil::confParam config = configFileUtil::readConfig();

    util::createDirectory(config.pathToProcesses + "/" + directoryName);
    util::saveStringAsFile(text, config.pathToProcesses + "/" + directoryName + "/" + filename);

    logUtil::writeLogMessageToConsoleAndFile("info", typeid(methodSaveProcess).name(), __LINE__, "Save Process: " + filename);

    return UA_STATUSCODE_GOOD;
}

void methodSaveProcess::createMethod(UA_Server* server) {
    UA_Argument inputArguments[2];

    char inputProcessName[] = "Process Name";
    inputArguments[0] = createStringArgument(inputProcessName);

    char inputText[] = "Text";
    inputArguments[1] = createStringArgument(inputText);

    char outputText[] = "Result";
    UA_Argument outputArgument = createStringArgument(outputText);

    char methodeName[] = "Save Process as XML";
    UA_MethodAttributes methodAttributes = createMethodAttributes(methodeName);
    
    UA_Server_addMethodNode(
        server, UA_NODEID_STRING(1, methodeName),
        UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
        UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
        UA_QUALIFIEDNAME(1, methodeName),
        methodAttributes, &saveProcess,
        2, inputArguments, 1, &outputArgument, NULL, NULL
    );
}