#ifndef METHODGETSERVICE_H

#define METHODGETSERVICE_H

#include "opcuaMethode.h"

class methodGetService : public opcuaMethode {

public:

	static void createMethod(UA_Server* server);

};

#endif