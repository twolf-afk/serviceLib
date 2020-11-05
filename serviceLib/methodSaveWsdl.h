#ifndef METHODSAVEWSDL_H

#define METHODSAVEWSDL_H

#include "opcuaMethode.h"

class methodSaveWsdl : public opcuaMethode
{

public:

	static void createMethod(UA_Server* server);

};

#endif