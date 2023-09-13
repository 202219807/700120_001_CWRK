#pragma once
class Physics
{
public:
	Physics(const bool useGravity, const float mass, const float drag, const float angularDrag);
	~Physics();

	Physics(const Physics& other) = default;
	Physics(Physics&& other) noexcept = default;
	Physics& operator= (const Physics& other) = default;
	Physics& operator= (Physics&& other) noexcept = default;

	bool  GetUseGravity() const;
	float GetMass() const;
	float GetDrag() const;
	float GetAngularDrag() const;

	void SetUseGravity(const bool useGravity);
	void SetMass(const float mass);
	void SetDrag(const float drag);
	void SetAngularDrag(const float angularDrag);

private:
	bool  m_useGravity;
	float m_mass;
	float m_drag;
	float m_angularDrag;
};

