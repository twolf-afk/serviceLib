#ifndef METHODGETPROCESS_H

#define METHODGETPROCESS_H

#include "opcuaMethode.h"

class methodGetProcess : public opcuaMethode
{

public:

	static void createMethod(UA_Server* server);

};

#endif