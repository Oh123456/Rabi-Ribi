#pragma once
#include "Object.h"
class ProjectileManager : public Object
{
	SUPER(Object);
public:
	ProjectileManager();
	~ProjectileManager();

	//  멤버 변수 초기화, 메모리 할당
	HRESULT Init() override;
	// 메모리 해제
	void Release() override;
	// 프레임 단위 게임 로직 실행 ( 데이터 변경)
	void Update() override;
	// 프레임 단위 출력 (이미지, 텍스트)
	void Render() override;

	class Projectile* SpawnProjectile();
	class Projectile* SpawnCarrotBomb();
	class Projectile** SpawnBlackBomb();

	const list <class Projectile*>& GetProjectile()			const { return projectiles; }
	const list <class Projectile*>& GetActiveProjectiles()	const { return activeProjectiles;}
private:
	list <class Projectile*> projectiles;
	list <class Projectile*> activeProjectiles;
	list <class Projectile*> carrotBombs;
	//class Projectile* carrotBomb; 
	class Projectile* blackBomb[2];
};

