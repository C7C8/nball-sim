#include <queue>
#include "../math/Vector2D.h"
using std::queue;

namespace Hydra
{
	class Entity
	{
	public:
		Entity(int nLife);
		virtual void update()=0;
		virtual void die()=0;
		virtual void render()=0;

		void sVX(float nVX);
		void sVY(float nVY);
		void sPX(float nPX);
		void sPY(float nPY);
		void sR(float nR_rad);

		Vector2D gV();
		float gPX();
		float gPY();
		float gR();
	protected:
		int life;
		float posX;
		float posY;
		float rot;
		Vector2D vel;

		friend class HydraEngine;
	};
}
