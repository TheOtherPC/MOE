//
// Created by gru on 3/27/24.
//

#ifndef MOE_PHYSICS_H
#define MOE_PHYSICS_H


#include <bullet3/src/btBulletDynamicsCommon.h>
#include <glm/glm.hpp>

#include <vector>
//#include <btBulletDynamicsCommon.h>
//#include <bullet3/src/btBulletCollisionCommon.h>
//#include <bullet3/src/btBroadphaseInterface.h>

namespace MOE {
    class Physics {
    public:
        static void Init();
        static void Run();
        static void ShutDown();
        static void SetWorld();
        static void AddObject(std::pair<glm::vec3, glm::vec3>, float, glm::vec3);
        static std::vector<glm::vec3> GetPositions();
    private:
        static btDefaultCollisionConfiguration* collisionConfiguration;
        static btCollisionDispatcher* dispatcher;
        static btBroadphaseInterface* overlappingPairCache;
        static btSequentialImpulseConstraintSolver* solver;
        static btDiscreteDynamicsWorld* dynamicsWorld;
        static btAlignedObjectArray<btCollisionShape*> collisionShapes;
    };
}

#endif //MOE_PHYSICS_H

