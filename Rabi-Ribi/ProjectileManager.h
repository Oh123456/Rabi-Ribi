#pragma once
#include "Object.h"
class ProjectileManager : public Object
{
	SUPER(Object);
public:
	ProjectileManager();
	~ProjectileManager();

	//  ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	HRESULT Init() override;
	// �޸� ����
	void Release() override;
	// ������ ���� ���� ���� ���� ( ������ ����)
	void Update() override;
	// ������ ���� ��� (�̹���, �ؽ�Ʈ)
	void Render() override;

	class Projectile* SpawnProjectile();
	class Projectile* SpawnCarrotBomb();

	const list <class Projectile*>& GetProjectile()			const { return projectiles; }
	const list <class Projectile*>& GetActiveProjectiles()	const { return activeProjectiles;}
private:
	list <class Projectile*> projectiles;
	list <class Projectile*> activeProjectiles;
	class Projectile* carrotBomb;
};

