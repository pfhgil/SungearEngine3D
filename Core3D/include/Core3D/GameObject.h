#include <iostream>
#include <vector>

using namespace std;

namespace Core3D
{
	namespace GameObject
	{
		class GameObject
		{
			private:
				vector<Component> _components;

			public:
				GameObject() { }
				~GameObject() { }
				
		};

		class Component
		{
			public:
				Component() { }
				~Component() { }

				GameObject* _gameObject;

				void Init();
				void Update();
				void DeltaUpdate(float deltaTime);
		};

		class MeshRendererComponent : Component
		{
			public:
				MeshRendereComponent() { }
				~MeshRendereComponent() { }
		};
	}
}