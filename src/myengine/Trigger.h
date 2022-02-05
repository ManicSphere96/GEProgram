#include "Component.h"

#include <vector>

namespace myengine
{
	struct Trigger : Component
	{
		void onTick()
		{
			/*std::shared_ptr<SphereCollider> sc = 
				getEntity()->getComponent<SphereCollider>();*/

			/*std::vector<std::shared_ptr<SphereCollider> >& colliders =
				getCore->m_colliders;*/

			/*for (size_t ci = 0; ci < colliders.size(); ci++)
			{
				if (colliders.at(ci) == sc) continue;

				if (sc->isColliding(colliders.at(ci)))
				{
					getEntity()->colliding(colliders.at(ci));
					colliders.at(ci)->getEntity()->colliding(sc);
				}
			}*/
		}
	};
}