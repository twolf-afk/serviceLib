#ifndef METHODSAVEPROCESS_H

#define METHODSAVEPROCESS_H

#include "opcuaMethode.h"

class methodSaveProcess : public opcuaMethode
{
public:

	static void createMethod(UA_Server* server);
};

#endif
