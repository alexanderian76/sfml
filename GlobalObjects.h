
/*class GlobalObjects {
    public:
      //  static ObjectController* objects; //= (ObjectController*)malloc(sizeof(ObjectController) * 1);
};*/

#ifndef GLOBAL_OBJECTS
#define GLOBAL_OBJECTS

#include "ObjectController.h"
class GlobalObjects
{
public:
    inline static ObjectController* objects = (ObjectController *)calloc(1, sizeof(ObjectController));
    inline static int objectsCount = 0;
};

#endif