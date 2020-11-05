#include "opcuaMethode.h"

UA_Argument opcuaMethode::createStringArgument(char argumentName[])
{
	char locale[] = "de-GER";
	char str[] = "A String";

	UA_Argument argument;
	UA_Argument_init(&argument);
	argument.name = UA_STRING(argumentName);
	argument.description = UA_LOCALIZEDTEXT(locale, str);
	argument.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
	argument.valueRank = UA_VALUERANK_SCALAR;

	return argument;
}

UA_MethodAttributes opcuaMethode::createMethodAttributes(char methodName[])
{
	char locale[] = "de-GER";

	UA_MethodAttributes methodeAttribute = UA_MethodAttributes_default;
	methodeAttribute.description = UA_LOCALIZEDTEXT(locale, methodName);
	methodeAttribute.displayName = UA_LOCALIZEDTEXT(locale, methodName);
	methodeAttribute.executable = true;
	methodeAttribute.userExecutable = true;

	return methodeAttribute;
}