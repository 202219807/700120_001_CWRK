#include "Physics.h"

Physics::Physics(const bool useGravity, const float mass, const float drag, const float angularDrag) : 
	m_useGravity(useGravity), 
	m_mass(mass), 
	m_drag(drag), 
	m_angularDrag(angularDrag) 
{
}

Physics::~Physics() {};

bool Physics::GetUseGravity() const 
{
	return m_useGravity;
}

float Physics::GetMass() const 
{
	return m_mass;
}

float Physics::GetDrag() const 
{
	return m_drag;
}

float Physics::GetAngularDrag() const 
{
	return m_angularDrag;
}

void Physics::SetUseGravity(const bool useGravity) 
{
	m_useGravity = useGravity;
}

void Physics::SetMass(const float mass) 
{
	m_mass = mass;
}

void Physics::SetDrag(const float drag) 
{
	m_drag = drag;
}

void Physics::SetAngularDrag(const float angularDrag) 
{
	m_angularDrag = angularDrag;
}