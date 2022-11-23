// SungearEngine3D.cpp: определяет точку входа для приложения.
//

#include "SungearEngine3D.h";
#include "../Core3D/Core3DMain.h";

using namespace std;
using namespace Core3D;

int main()
{
	Core3DMain* m = new Core3DMain();
	cout << m->getName() << endl;
	return 0;
}
