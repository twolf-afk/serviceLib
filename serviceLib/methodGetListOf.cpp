
#include "methodGetListOf.h"

#include "logUtil.h"
#include "open62541Util.h"
#include "util.h"
#include "configFileUtil.h"

static UA_StatusCode getList (
    UA_Server* server, const UA_NodeId* sessionId,
    void* sessionHandle, const UA_NodeId* methodId,
    void* methodContext, const UA_NodeId* objectId,
    void* objectContext, size_t inputSize,
    const UA_Variant* input, size_t outputSize,
    UA_Variant* output) {

    logUtil::writeLogMessageToConsoleAndFile("info", typeid(methodGetListOf).name(), __LINE__, "getList was called");

    UA_String* firstInput = (UA_String*)input->data;
    std::string listName = open62541Util::uaStringPtrToStdString(firstInput);

    logUtil::writeLogMessageToConsoleAndFile("info", typeid(methodGetListOf).name(), __LINE__, "Get List of: " + listName);

    configFileUtil::confParam config = configFileUtil::readConfig();
    std::vector<std::string> files;
    
    if (listName == "processes") {
        files = util::getFilesInDirectory(config.pathToProcesses);
    }
    else if (listName == "services") {
        files = util::getFilesInDirectory(config.pathToServices);
    }
    else {
        logUtil::writeLogMessageToConsoleAndFile("info", typeid(methodGetListOf).name(), __LINE__, "Unkown listname");
    }

    std::string fileList;
    for (int i = 0; i < files.size(); i++) {
        fileList += files.at(i) + ";";
    }

    const char* chFileList = fileList.c_str();

    UA_String result;
    UA_String_init(&result);

    result.length = strlen(chFileList);
    result.data = (UA_Byte*)chFileList;

    UA_Variant_setScalarCopy(output, &result, &UA_TYPES[UA_TYPES_STRING]);

    return UA_STATUSCODE_GOOD;
}

void methodGetListOf::createMethod(UA_Server* server) {

    char inputListName[] = "List of processes or services";
    UA_Argument inputArgument = createStringArgument(inputListName);

    char outputText[] = "Result";
    UA_Argument outputArgument = createStringArgument(outputText);

    char methodeName[] = "Get List of";
    UA_MethodAttributes methodAttributes = createMethodAttributes(methodeName);
    
    UA_Server_addMethodNode(
        server, UA_NODEID_STRING(1, methodeName),
        UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
        UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
        UA_QUALIFIEDNAME(1, methodeName),
        methodAttributes, &getList,
        1, &inputArgument, 1, &outputArgument, NULL, NULL
    );
}