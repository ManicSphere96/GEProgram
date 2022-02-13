#include <renderer.h>
#include "ConvexCollider.h"

// This should not have to be added, but without it the compiler says:
// Error	C2027	use of undefined type 'myengine::Core'	myengine	
#include "Core.h"

#include "Component.h"
#include "Transform.h"

namespace myengine
{
	void ConvexCollider::onInit(std::shared_ptr<renderer::VertexArray> vao)
	{
        ///Registers Collider in the Vector in Core 
		getCore()->registerConvexCollider(getEntity()->getComponent<ConvexCollider>());
		m_Vao = vao;
	}
	void ConvexCollider::onDestroy()
	{
        ///Unregisters Collider in the Vector in Core
		getCore()->unregisterConvexCollider(this);
	}

	

	bool ConvexCollider::isColliding(std::shared_ptr<SphereCollider> collider)
	{
        ///Tests for collisipon between this convex collider and the given sphere collider.
        /// If the test comes back positive it affects the sphere colliders velocity.
        bool isInside = true;
        float closestDistance = 0.0f;
        for (int pi = 0; pi < (int)m_Vao->getPlanes().size(); pi++)
        {
            ///Iterating through the planes and testing if we have collided with one
            glm::vec4 transformedPt = getTransform()->getModel() * glm::vec4(m_Vao->getPlanes()[pi].point, 1.0f);
            glm::vec3 point(transformedPt.x, transformedPt.y, transformedPt.z);
            float distance = glm::dot((collider->getTransform()->getPosition() - point), m_Vao->getPlanes()[pi].normal);
            if (distance > collider->getRadius())
            {
                isInside = false;
                break;
            }
            else
            {
                /// using the plane that has the closest distance
                if ((distance > 0.0) && (closestDistance < distance))
                {
                    /// incident vector will be the normal pointing the other way "-n"
                    m_Incident = -m_Vao->getPlanes()[pi].normal;
                    closestDistance = distance;
                }
            }
        }
        if (isInside)
        {
            /// this is what affects the colliding objects velocity based on the collision.
            glm::vec3 itsVel = collider->getTransform()->getVelocity();

            float incedenceVelScalar = glm::dot(itsVel, m_Incident);
            glm::vec3 incedencePoint = -m_Incident * closestDistance + collider->getTransform()->getPosition();
            if (incedenceVelScalar > GAMMA)
            {
                collider->setHasCollided(true);
            }
            collider->getTransform()->setPosition(collider->getTransform()->getPosition() + (-m_Incident * (collider->getRadius() - closestDistance)));
            if (incedenceVelScalar < EPSILON)
            {
                collider->getTransform()->setVelocity(itsVel - (m_Incident * incedenceVelScalar));

                collider->setHasCollided(false);

            }
            collider->getTransform()->setVelocity(itsVel - (2.0f * (glm::dot(itsVel, -m_Incident) * -m_Incident)));
        }
        return isInside;

	}
	
}


