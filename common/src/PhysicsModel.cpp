#include "PhysicsModel.hpp"

PhysicsModel::PhysicsModel(const char* name, float mass, float friction, float restitution, const glm::vec3 &size, const glm::vec3 &center, BODY type) : GLNode(name)
{
    this->mass = mass;
    this->friction = friction;
    this->restitution = restitution;
    this->inertia = btVector3(0,0,0);

    transform = btTransform::getIdentity();

    switch(type)
    {
        case(CYLINDER):
            this->collisionShape = std::shared_ptr<btCylinderShape>( new btCylinderShapeZ(btVector3(btScalar(size.x),btScalar(0.1),btScalar(size.x))) );
            this->SetMotionState(glm::vec3(0, 0, 0));
            this->SetConstraints(glm::vec3(0.0,0.00,0.0), glm::vec3(1, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 0));
            break;
        case(SPHERE):
            this->collisionShape = std::shared_ptr<btSphereShape>( new btSphereShape(size.x));
            this->SetMotionState(glm::vec3(0, 0, 0));
            this->SetConstraints(glm::vec3(0.0,0.00,0.0), glm::vec3(1, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 0));
            break;
        case(BOX):
            this->collisionShape = std::shared_ptr<btBoxShape>( new btBoxShape(btVector3(btScalar(size.x),btScalar(size.y),btScalar(size.z))) );
            this->SetMotionState(glm::vec3(0, 0, 0));
            this->SetConstraints(glm::vec3(0.0,0.00,0.0), glm::vec3(1, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 0));
            break;
      
        default:
            std::cerr<< "[E] Rigid Body type not found."<<std::endl;
            return;
    }
}

// Constructor for custom convex triangle mesh
PhysicsModel::PhysicsModel(const char* name, std::shared_ptr<std::vector<glm::vec3>> vertices, const size_t numPoints) : GLNode(name)
{
    btTriangleMesh *triMesh = new btTriangleMesh();

    glm::vec3 a0, a1, a2;
    // Create triangles
    for(size_t i=0; i<numPoints - 2; i+=3)
    {
        a0 = glm::vec3( vertices->at(i+0).x, vertices->at(i+0).y, vertices->at(i+0).z );
        a1 = glm::vec3( vertices->at(i+1).x, vertices->at(i+1).y, vertices->at(i+1).z );
        a2 = glm::vec3( vertices->at(i+2).x, vertices->at(i+2).y, vertices->at(i+2).z );

        btVector3 v0(a0.x,a0.y,a0.z);
        btVector3 v1(a1.x,a1.y,a1.z);
        btVector3 v2(a2.x,a2.y,a2.z);

        triMesh->addTriangle(v0,v1,v2);
    }

    this->collisionShape = std::shared_ptr<btCollisionShape>(new btBvhTriangleMeshShape(triMesh, true));
    //this->collisionShape->calculateLocalInertia( 0, btVector3(0,0,0) );


    //TODO: Hardcoded defaults?
    this->SetMotionState(glm::vec3(0, 0, 0));
}

// Set Initial Motion State
void PhysicsModel::SetMotionState(const glm::vec3 &transform)
{
    // Set to default bullet Motion state (translation on z-axis)
    this->motionState = std::shared_ptr<btDefaultMotionState>( new btDefaultMotionState( btTransform(btQuaternion(0,0,0,1), btVector3( transform.x, 0.0, transform.z))) );

    this->collisionShape->calculateLocalInertia( this->mass, this->inertia );

    btRigidBody::btRigidBodyConstructionInfo rigidBodyInfo( this->mass, this->motionState.get(), this->collisionShape.get(), this->inertia );
    rigidBodyInfo.m_friction = friction;
    rigidBodyInfo.m_restitution = restitution;  

    this->rigidBody = std::shared_ptr<btRigidBody>(new btRigidBody( rigidBodyInfo ));

}

// Set Physics Constraints 6DOF
void PhysicsModel::SetConstraints(const glm::vec3 &origin, const glm::vec3 &linearLowerLimit, const glm::vec3 &linearUpperLimit, const glm::vec3 &angularLowerLimit, const glm::vec3 &angularUpperLimit)
{
    this->rigidBody->setActivationState(DISABLE_DEACTIVATION);
    this->rigidBody->setLinearFactor(btVector3(1,1,1));

    btTransform frame = btTransform::getIdentity();
    frame.setOrigin(btVector3(origin.x, origin.y, origin.z));

   // Generic 6DOF (used as a plane) Constraint
   this->planeConstraint = std::shared_ptr<btGeneric6DofConstraint>(new btGeneric6DofConstraint( *(this->rigidBody), frame, true ));

    // lowerlimit = upperlimit --> axis locked
    // lowerlimit < upperlimit --> motion limited between values
    // lowerlimit > upperlimit --> axis is free

    // lock the Y axis movement
    this->planeConstraint->setLinearLowerLimit( btVector3(linearLowerLimit.x, linearLowerLimit.y, linearLowerLimit.z) );
    this->planeConstraint->setLinearUpperLimit( btVector3(linearUpperLimit.x, linearUpperLimit.y, linearUpperLimit.z) );

    // lock the X, Z, rotations
    this->planeConstraint->setAngularLowerLimit( btVector3(angularLowerLimit.x, angularLowerLimit.y, angularLowerLimit.z) );
    this->planeConstraint->setAngularUpperLimit( btVector3(angularUpperLimit.x, angularUpperLimit.y, angularUpperLimit.z) );
}

void PhysicsModel::Reset()
{
   this->SetMotionState(glm::vec3(0, 0, 0));
}

// Returns the transformation matrix of the body
glm::mat4 PhysicsModel::GetTransform()
{
   this->rigidBody->getMotionState()->getWorldTransform(this->transform);
   btMatrix3x3 matrix = this->transform.getBasis();
   glm::mat4 ret(matrix[0][0], matrix[0][1], matrix[0][2], 0, matrix[1][0], matrix[1][1], matrix[1][2], 0, matrix[2][0], matrix[2][1], matrix[2][2], 0, this->transform.getOrigin().getX(), this->transform.getOrigin().getY(), this->transform.getOrigin().getZ(), 1);
   return ret;
}

void PhysicsModel::SetTransform(glm::vec4 q, glm::vec3 axis)
{
    this->rigidBody->getMotionState()->setWorldTransform(btTransform(btQuaternion(q.x, q.y, q.z, q.w), btVector3(axis.z, axis.y, axis.z)));
}

void PhysicsModel::SetTransform(btTransform newTransform)
{
    this->rigidBody->getMotionState()->setWorldTransform(newTransform);
}

// Returns the centroid
glm::vec3 PhysicsModel::GetOrigin()
{
   btVector3 origin = this->transform.getOrigin();
   glm::vec3 ret(origin.getX(), origin.getY(), origin.getZ());
   return ret;
}

std::shared_ptr<btRigidBody> PhysicsModel::GetRigidBody()
{
    return this->rigidBody;
}

std::shared_ptr<btGeneric6DofConstraint> PhysicsModel::GetConstraint()
{
    return this->planeConstraint;
}

PhysicsModel::~PhysicsModel()
{
}
