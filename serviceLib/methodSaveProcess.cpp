#include "methodSaveProcess.h"

#include "logUtil.h"

static UA_StatusCode saveProcess
(
    UA_Server* server, const UA_NodeId* sessionId,
    void* sessionHandle, const UA_NodeId* methodId,
    void* methodContext, const UA_NodeId* objectId,
    void* objectContext, size_t inputSize,
    const UA_Variant* input, size_t outputSize,
    UA_Variant* output
)
{
    UA_String* ptrInput = (UA_String*)input->data;
    UA_String inputValue;
    UA_String_init(&inputValue);

    logUtil::writeLogMessageToConsoleAndFile("info", typeid(methodSaveProcess).name(), __LINE__, "saveProcess was called");

    if (ptrInput->length > 0)
    {
        inputValue.data = (UA_Byte*)UA_realloc(inputValue.data, inputValue.length + ptrInput->length);
        memcpy(&inputValue.data[inputValue.length], ptrInput->data, ptrInput->length);
        inputValue.length += ptrInput->length;
    }

    char* chValue = (char*)UA_malloc(sizeof(char) * inputValue.length + 1);
    memcpy(chValue, inputValue.data, inputValue.length);
    chValue[inputValue.length] = '\0';

    std::string value(chValue);
    logUtil::writeLogMessageToConsoleAndFile("info", typeid(methodSaveProcess).name(), __LINE__, "Save Process: " + value);

    UA_Variant_setScalarCopy(output, &inputValue, &UA_TYPES[UA_TYPES_STRING]);
    UA_String_clear(&inputValue);


    return UA_STATUSCODE_GOOD;

}

void methodSaveProcess::createMethod(UA_Server* server)
{
    char inputText[] = "Save Process as XML";
    UA_Argument inputArgument = createStringArgument(inputText);

    char outputText[] = "Result";
    UA_Argument outputArgument = createStringArgument(outputText);

    char methodeName[] = "Save Process as XML";
    UA_MethodAttributes methodAttributes = createMethodAttributes(methodeName);


    UA_Server_addMethodNode
    (
        server, UA_NODEID_STRING(1, methodeName),
        UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
        UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
        UA_QUALIFIEDNAME(1, methodeName),
        methodAttributes, &saveProcess,
        1, &inputArgument, 1, &outputArgument, NULL, NULL
    );
}