
/*class GlobalObjects {
    public:
      //  static ObjectController* objects; //= (ObjectController*)malloc(sizeof(ObjectController) * 1);
};*/

#ifndef GLOBAL_OBJECTS
#define GLOBAL_OBJECTS

#include "ObjectController.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include "./Menu/Screen.h"
#include "Camera.h"
#include "./Common/Settings.h"
class GlobalObjects
{
public:
    inline static std::vector<ObjectController> objects;
    inline static ScreenManager* screenManager = new ScreenManager;
    inline static Camera *camera;
  //  inline static uint screenWidth = 800;
  //  inline static uint screenHeight = 600;
    inline static Settings *settings = new Settings;
};

#endif


/*
// Если хотите остаться без vector, вот правильная версия:

#ifndef GLOBAL_OBJECTS
#define GLOBAL_OBJECTS

#include "ObjectController.h"
#include <iostream>
#include <cstdlib>
#include <new>

class GlobalObjects
{
public:
    inline static ObjectController* objects = nullptr;
    inline static int objectsCount = 0;
    inline static int objectsCapacity = 0;
    
    static void init() {
        if (objects == nullptr) {
            objectsCapacity = 4;
            objects = (ObjectController*)malloc(sizeof(ObjectController) * objectsCapacity);
            if (objects) {
                // Вызываем конструкторы!
                for (int i = 0; i < objectsCapacity; i++) {
                    new(&objects[i]) ObjectController(0, 0, 0, 0);
                }
            }
        }
    }
    
    static void addObject(const ObjectController& obj) {
        if (!objects) init();
        
        if (objectsCount >= objectsCapacity) {
            int newCapacity = objectsCapacity * 2;
            ObjectController* newObjects = (ObjectController*)malloc(sizeof(ObjectController) * newCapacity);
            
            if (!newObjects) return;
            
            // Копируем старые объекты
            for (int i = 0; i < objectsCount; i++) {
                new(&newObjects[i]) ObjectController(objects[i]);
            }
            
            // Уничтожаем старые объекты
            for (int i = 0; i < objectsCount; i++) {
                objects[i].~ObjectController();
            }
            
            free(objects);
            
            // Инициализируем новые слоты
            for (int i = objectsCount; i < newCapacity; i++) {
                new(&newObjects[i]) ObjectController(0, 0, 0, 0);
            }
            
            objects = newObjects;
            objectsCapacity = newCapacity;
        }
        
        objects[objectsCount] = obj;
        objectsCount++;
    }
    
    static void cleanup() {
        if (objects) {
            for (int i = 0; i < objectsCount; i++) {
                objects[i].~ObjectController();
            }
            free(objects);
            objects = nullptr;
            objectsCount = 0;
            objectsCapacity = 0;
            std::cout << "GLOBAL OBJECTS CLEANED" << std::endl;
        }
    }
};

#endif
*/