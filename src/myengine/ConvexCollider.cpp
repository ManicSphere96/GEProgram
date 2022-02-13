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
		getCore()->registerConvexCollider(getEntity()->getComponent<ConvexCollider>());
		m_Vao = vao;
	}
	void ConvexCollider::onDestroy()
	{
		getCore()->unregisterConvexCollider(this);
	}

	

	bool ConvexCollider::isColliding(std::shared_ptr<SphereCollider> collider)
	{
		
        bool isInside = true;
        float closestDistance = 0.0f;
        for (int pi = 0; pi < (int)m_Vao->getPlanes().size(); pi++)
        {
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
                // use the plane that has the closest distance
                if ((distance > 0.0) && (closestDistance < distance))
                {
                    // incident vector will be the normal pointing the other way "-n"
                    //SetIncident(-m_Vao->getPlanes()[pi].normal);
                    m_Incident = -m_Vao->getPlanes()[pi].normal;
                    closestDistance = distance;
                }
            }
        }
        if (isInside)
        {
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
	void ConvexCollider::currentlyColliding(std::shared_ptr<SphereCollider> collidingObj)
	{
		/*glm::vec3 itsVel = collidingObj->getTransform()->getVelocity();
		
		float incedenceVelScalar = glm::dot(itsVel, m_Incident);
		if (incedenceVelScalar < -GAMMA)
		{
			collidingObj->setHasCollided(true);
		}
		collidingObj->getTransform()->setPosition(myLoc + m_Incident * (m_Radius + collidingObj->getRadius()));
		if (incedenceVelScalar > -EPSILON)
		{
			collidingObj->getTransform()->setVelocity(itsVel - (m_Incident * incedenceVelScalar));
			
			collidingObj->setHasCollided(false);

		}


	collidingObj->getTransform()->setVelocity(itsVel - (2.0f * (glm::dot(itsVel, m_Incident) * m_Incident)));
	*/
	}
	
}


