#include "methodGetService.h"

#include "logUtil.h"
#include "getFileAsString.h"

static UA_StatusCode getService
(
    UA_Server* server, const UA_NodeId* sessionId,
    void* sessionHandle, const UA_NodeId* methodId,
    void* methodContext, const UA_NodeId* objectId,
    void* objectContext, size_t inputSize,
    const UA_Variant* input, size_t outputSize,
    UA_Variant* output
)
{
    logUtil::writeLogMessageToConsoleAndFile("info", typeid(methodGetService).name(), __LINE__, "getService was called");

    UA_String* ptrInput = (UA_String*)input->data;
    UA_String uaStrServiceName;
    UA_String_init(&uaStrServiceName);

    if (ptrInput->length > 0)
    {
        uaStrServiceName.data = (UA_Byte*)UA_realloc(uaStrServiceName.data, uaStrServiceName.length + ptrInput->length);
        memcpy(&uaStrServiceName.data[uaStrServiceName.length], ptrInput->data, ptrInput->length);
        uaStrServiceName.length += ptrInput->length;
    }

    char* chServiceName = (char*)UA_malloc(sizeof(char) * uaStrServiceName.length + 1);
    memcpy(chServiceName, uaStrServiceName.data, uaStrServiceName.length);
    chServiceName[uaStrServiceName.length] = '\0';

    std::string serviceName(chServiceName);
    logUtil::writeLogMessageToConsoleAndFile("info", typeid(methodGetService).name(), __LINE__, "Get Service: " + serviceName);

    std::string serviceAsString = getFileAsString::getFile("../../services/" + serviceName);
    const char* service = serviceAsString.c_str();

    UA_String result;
    UA_String_init(&result);

    result.length = strlen(service);
    result.data = (UA_Byte*)service;

    UA_Variant_setScalarCopy(output, &result, &UA_TYPES[UA_TYPES_STRING]);
    UA_String_clear(&uaStrServiceName);


    return UA_STATUSCODE_GOOD;

}

void methodGetService::createMethod(UA_Server* server)
{
    char inputText[] = "Get Service";
    UA_Argument inputArgument = createStringArgument(inputText);

    char outputText[] = "Result";
    UA_Argument outputArgument = createStringArgument(outputText);

    char methodeName[] = "Get Service";
    UA_MethodAttributes methodAttributes = createMethodAttributes(methodeName);


    UA_Server_addMethodNode
    (
        server, UA_NODEID_STRING(1, methodeName),
        UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
        UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
        UA_QUALIFIEDNAME(1, methodeName),
        methodAttributes, &getService,
        1, &inputArgument, 1, &outputArgument, NULL, NULL
    );
}