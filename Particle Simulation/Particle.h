#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <vector>

using namespace sf;
using namespace std;

class Particle
{
private:
	Vector2f mVelocity;
	Vector2f mPosition;
	Vector2f mAcceleration;
	float mMass;
	vector<Vector2f> mForces;

public:
	Particle();
	Particle(const Vector2f& position, const float& mass);
	void update(const Time& dTime);
	Vector2f getTotalForce() const;
	vector<Vector2f> getForces() const;
	void addForce(const Vector2f & force);
	void clearForces();
	void setPosition(const Vector2f& pos);
	const Vector2f&	getPosition();
	void setVelocity(const Vector2f& vel);
	const Vector2f& getVelocity();
};

