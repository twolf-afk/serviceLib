#include "methodGetProcess.h"

#include "logUtil.h"
#include "getFileAsString.h"

static UA_StatusCode getProcess
(
    UA_Server* server, const UA_NodeId* sessionId,
    void* sessionHandle, const UA_NodeId* methodId,
    void* methodContext, const UA_NodeId* objectId,
    void* objectContext, size_t inputSize,
    const UA_Variant* input, size_t outputSize,
    UA_Variant* output
)
{
    logUtil::writeLogMessageToConsoleAndFile("info", typeid(methodGetProcess).name(), __LINE__, "getProcess was called");

    UA_String* ptrInput = (UA_String*)input->data;
    UA_String uaStrProcessName;
    UA_String_init(&uaStrProcessName);

    if (ptrInput->length > 0)
    {
        uaStrProcessName.data = (UA_Byte*)UA_realloc(uaStrProcessName.data, uaStrProcessName.length + ptrInput->length);
        memcpy(&uaStrProcessName.data[uaStrProcessName.length], ptrInput->data, ptrInput->length);
        uaStrProcessName.length += ptrInput->length;
    }

    char* chProcessName = (char*)UA_malloc(sizeof(char) * uaStrProcessName.length + 1);
    memcpy(chProcessName, uaStrProcessName.data, uaStrProcessName.length);
    chProcessName[uaStrProcessName.length] = '\0';

    std::string processNameAsString(chProcessName);
    logUtil::writeLogMessageToConsoleAndFile("info", typeid(methodGetProcess).name(), __LINE__, "Get Process: " + processNameAsString);

    std::string processAsString = getFileAsString::getFile("../../processes/" + processNameAsString);
    const char* process = processAsString.c_str();

    UA_String result;
    UA_String_init(&result);

    result.length = strlen(process);
    result.data = (UA_Byte*)process;

    UA_Variant_setScalarCopy(output, &result, &UA_TYPES[UA_TYPES_STRING]);
    UA_String_clear(&uaStrProcessName);


    return UA_STATUSCODE_GOOD;

}

void methodGetProcess::createMethod(UA_Server* server)
{
    char inputText[] = "Get Process";
    UA_Argument inputArgument = createStringArgument(inputText);

    char outputText[] = "Result";
    UA_Argument outputArgument = createStringArgument(outputText);

    char methodeName[] = "Get Process";
    UA_MethodAttributes methodAttributes = createMethodAttributes(methodeName);


    UA_Server_addMethodNode
    (
        server, UA_NODEID_STRING(1, methodeName),
        UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
        UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
        UA_QUALIFIEDNAME(1, methodeName),
        methodAttributes, &getProcess,
        1, &inputArgument, 1, &outputArgument, NULL, NULL
    );
}