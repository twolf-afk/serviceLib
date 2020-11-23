#ifndef METHODGETLISTOF_H

#define METHODGETLISTOF_H

#include "opcuaMethode.h"

class methodGetListOf : public opcuaMethode
{

public:

	static void createMethod(UA_Server* server);

};

#endif