//
// Created by gru on 3/27/24.
//

#ifndef MOE_PHYSICS_H
#define MOE_PHYSICS_H


#include <bullet3/src/btBulletDynamicsCommon.h>
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

