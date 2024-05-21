//
// Created by gru on 3/27/24.
//



//#include "Physics.h"


//#include "btBulletDynamicsCommon.h"
#include "Physics.h"
#include <iostream>
#include <cstdio>

/// This is a Hello World program for running a basic Bullet physics simulation

namespace MOE {
    btDefaultCollisionConfiguration* Physics::collisionConfiguration;
    btCollisionDispatcher* Physics::dispatcher;
    btBroadphaseInterface* Physics::overlappingPairCache;
    btSequentialImpulseConstraintSolver* Physics::solver;
    btDiscreteDynamicsWorld* Physics::dynamicsWorld;
    btAlignedObjectArray<btCollisionShape*> Physics::collisionShapes;
    void Physics::Init() {
        Physics::collisionConfiguration = new btDefaultCollisionConfiguration();

        ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
        Physics::dispatcher = new btCollisionDispatcher(collisionConfiguration);

        ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
        Physics::overlappingPairCache = new btDbvtBroadphase();

        ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
        Physics::solver = new btSequentialImpulseConstraintSolver;

        Physics::dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

//        Physics::dynamicsWorld->setGravity(btVector3(0, -10, 0));
        Physics::dynamicsWorld->setGravity(btVector3(0, -5, 0));
//        Physics::SetWorld();
    }
    void Physics::AddObject(std::pair<glm::vec3, glm::vec3> extents, float m, glm::vec3 pos) {
        float halfx = (extents.first.x + extents.second.x)/2.0f;
        float halfy = (extents.first.y + extents.second.y)/2.0f;
        float halfz = (extents.first.z + extents.second.z)/2.0f;
        std::cout<< "HALFS: " << halfx << ", " << halfy << ", " << halfz << std::endl;
        btVector3 halfs(halfx, halfy, halfz);
        btCollisionShape* objectShape = new btBoxShape(halfs);
        collisionShapes.push_back(objectShape);
        btTransform objectTransform;
        objectTransform.setIdentity();
        objectTransform.setOrigin(btVector3(pos.x,pos.y,pos.z));
        btScalar mass(m);

        bool isDynamic = (mass != 0.);
        btVector3 localInertia(0,0,0);
        if (isDynamic)
            objectShape->calculateLocalInertia(mass, localInertia);

        btDefaultMotionState* motionState = new btDefaultMotionState(objectTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, objectShape, localInertia);
        btRigidBody* body = new btRigidBody(rbInfo);


//        int collisionFilterGroup, collisionFilterMask;
//        if (!isDynamic) {
//            body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
//            collisionFilterGroup = btBroadphaseProxy::StaticFilter;
//            collisionFilterMask = btBroadphaseProxy::AllFilter;
//        } else {
//            collisionFilterGroup = btBroadphaseProxy::DefaultFilter;
//            collisionFilterMask = btBroadphaseProxy::AllFilter;
//        }
//        body->getBroadphaseProxy()->m_collisionFilterGroup = collisionFilterGroup;
//        body->getBroadphaseProxy()->m_collisionFilterMask = collisionFilterMask;

        dynamicsWorld->addRigidBody(body);
    }
    void Physics::SetWorld() {
        {
            btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));

            collisionShapes.push_back(groundShape);

            btTransform groundTransform;
            groundTransform.setIdentity();
            groundTransform.setOrigin(btVector3(0, 0, 0));

            btScalar mass(0.);

            //rigidbody is dynamic if and only if mass is non zero, otherwise static
            bool isDynamic = (mass != 0.f);

            btVector3 localInertia(0, 0, 0);
            if (isDynamic)
                groundShape->calculateLocalInertia(mass, localInertia);

            //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
            btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
            btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
            btRigidBody* body = new btRigidBody(rbInfo);

            //add the body to the dynamics world
            dynamicsWorld->addRigidBody(body);
        }

//        {
//            //create a dynamic rigidbody
//
//            //btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
//            btCollisionShape* colShape = new btSphereShape(btScalar(1.));
//            collisionShapes.push_back(colShape);
//
//            /// Create Dynamic Objects
//            btTransform startTransform;
//            startTransform.setIdentity();
//
//            btScalar mass(1.f);
//
//            //rigidbody is dynamic if and only if mass is non zero, otherwise static
//            bool isDynamic = (mass != 0.f);
//
//            btVector3 localInertia(0, 0, 0);
//            if (isDynamic)
//                colShape->calculateLocalInertia(mass, localInertia);
//
//            startTransform.setOrigin(btVector3(2, 10, 0));
//
//            //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
//            btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
//            btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
//            btRigidBody* body = new btRigidBody(rbInfo);
//
//            dynamicsWorld->addRigidBody(body);
//        }

    }
    void Physics::Run(){
        dynamicsWorld->stepSimulation(1.f / 60.f, 10);
    }

    std::vector<glm::vec3> Physics::GetPositions() {

        std::vector<glm::vec3> pos;
        for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
        {
            btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
            btRigidBody* body = btRigidBody::upcast(obj);
            btTransform trans;
            if (body && body->getMotionState())
            {
                body->getMotionState()->getWorldTransform(trans);
            }
            else
            {
                trans = obj->getWorldTransform();
            }
//            printf("world pos object %d = %f,%f,%f\n", i, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
            pos.emplace_back(float(trans.getOrigin().getX()), float(trans.getOrigin().getY()),float(trans.getOrigin().getZ()));
        }
        return pos;
    }

    void Physics::ShutDown() {

        //cleanup in the reverse order of creation/initialization
        ///-----cleanup_start-----

        //remove the rigidbodies from the dynamics world and delete them
        for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
        {
            btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
            btRigidBody* body = btRigidBody::upcast(obj);
            if (body && body->getMotionState())
            {
                delete body->getMotionState();
            }
            dynamicsWorld->removeCollisionObject(obj);
            delete obj;
        }

        //delete collision shapes
        for (int j = 0; j < collisionShapes.size(); j++)
        {
            btCollisionShape* shape = collisionShapes[j];
            collisionShapes[j] = 0;
            delete shape;
        }

        //delete dynamics world
        delete dynamicsWorld;

        //delete solver
        delete solver;

        //delete broadphase
        delete overlappingPairCache;

        //delete dispatcher
        delete dispatcher;

        delete collisionConfiguration;

        //next line is optional: it will be cleared by the destructor when the array goes out of scope
        collisionShapes.clear();
    }
}