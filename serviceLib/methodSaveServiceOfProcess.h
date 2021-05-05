#ifndef METHODSAVESERVICEOFPROCESS_H

#define METHODSAVESERVICEOFPROCESS_H

#include "opcuaMethode.h"

class methodSaveServiceOfProcess : public opcuaMethode {

public: 

	static void createMethod(UA_Server* server);

};

#endif