#include "methodSaveWsdl.h"

#include "logUtil.h"
#include "open62541Util.h"
#include "configFileUtil.h"
#include "util.h"

static UA_StatusCode saveServiceAsWsdl (
    UA_Server* server, const UA_NodeId* sessionId,
    void* sessionHandle, const UA_NodeId* methodId,
    void* methodContext, const UA_NodeId* objectId,
    void* objectContext, size_t inputSize,
    const UA_Variant* input, size_t outputSize,
    UA_Variant* output ) {

    logUtil::writeLogMessageToConsoleAndFile("info", typeid(methodSaveWsdl).name(), __LINE__, "saveServiceAsWsdl was called");

    UA_String* firstInput = (UA_String*)input[0].data;
    
    std::string text = open62541Util::uaStringPtrToStdString(firstInput);
    std::vector<std::string> inputParts = util::splitString(text, ",");
    std::string serviceName = inputParts[0];
    std::string service = inputParts[1];

    if (!util::stringContainsSubstring(serviceName, "wsdl")) {
        serviceName += ".wsdl";
    }   
    
    configFileUtil::confParam config = configFileUtil::readConfig();
    util::saveStringAsFile(service, config.pathToServices + serviceName);
    
    logUtil::writeLogMessageToConsoleAndFile("info", typeid(methodSaveWsdl).name(), __LINE__, "Save Service: " + serviceName);

    UA_String result;
    UA_String_init(&result);

    UA_Variant_setScalarCopy(output, &result, &UA_TYPES[UA_TYPES_STRING]);

    return UA_STATUSCODE_GOOD;
}

void methodSaveWsdl::createMethod(UA_Server* server) {

    char inputListName[] = "Service";
    UA_Argument inputArgument = createStringArgument(inputListName);

    char outputText[] = "Result";
    UA_Argument outputArgument = createStringArgument(outputText);

    char methodeName[] = "Save Service as WSDL";
    UA_MethodAttributes methodAttributes = createMethodAttributes(methodeName);
    
    UA_Server_addMethodNode (
        server, UA_NODEID_STRING(1, methodeName),
        UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
        UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
        UA_QUALIFIEDNAME(1, methodeName),
        methodAttributes, &saveServiceAsWsdl,
        1, &inputArgument, 1, &outputArgument, NULL, NULL
    );
}