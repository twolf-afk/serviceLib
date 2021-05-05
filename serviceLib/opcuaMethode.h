#ifndef OPCUAMETHODE_H

#define OPCUAMETHODE_H

#include "open62541/server.h"

class opcuaMethode {

public:

	virtual void createMethod(char methodName[], UA_Server* server) =0;

protected:

	static UA_Argument createStringArgument(char argumentName[]);

	static UA_MethodAttributes createMethodAttributes(char methodName[]);

};

#endif 