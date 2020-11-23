#include "methodSaveWsdl.h"

#include "logUtil.h"
#include "open62541Util.h"
#include "saveStringAsXml.h"

static UA_StatusCode saveServiceAsWsdl
(
    UA_Server* server, const UA_NodeId* sessionId,
    void* sessionHandle, const UA_NodeId* methodId,
    void* methodContext, const UA_NodeId* objectId,
    void* objectContext, size_t inputSize,
    const UA_Variant* input, size_t outputSize,
    UA_Variant* output
)
{
    logUtil::writeLogMessageToConsoleAndFile("info", typeid(methodSaveWsdl).name(), __LINE__, "saveServiceAsWsdl was called");

    UA_String* firstInput = (UA_String*)input[0].data;
    UA_String* secondInput = (UA_String*)input[1].data;
    
    std::string filename = open62541Util::uaStringPtrToStdString(firstInput);
    std::string text = open62541Util::uaStringPtrToStdString(secondInput);

    saveStringAsXml::saveStringAsFile(text, "../services/" + filename + ".wsdl");
    
    logUtil::writeLogMessageToConsoleAndFile("info", typeid(methodSaveWsdl).name(), __LINE__, "Save Service: " + filename);

    return UA_STATUSCODE_GOOD;

}

void methodSaveWsdl::createMethod(UA_Server* server)
{

    UA_Argument inputArguments[2];

    char inputServiceName[] = "Service Name";
    inputArguments[0] = createStringArgument(inputServiceName);

    char inputText[] = "Text";
    inputArguments[1] = createStringArgument(inputText);

    char outputText[] = "Result";
    UA_Argument outputArgument = createStringArgument(outputText);

    char methodeName[] = "Save Service as WSDL";
    UA_MethodAttributes methodAttributes = createMethodAttributes(methodeName);


    UA_Server_addMethodNode
    (
        server, UA_NODEID_STRING(1, methodeName),
        UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
        UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
        UA_QUALIFIEDNAME(1, methodeName),
        methodAttributes, &saveServiceAsWsdl,
        2, inputArguments, 1, &outputArgument, NULL, NULL
    );
}