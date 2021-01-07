#pragma once
#include "Character.h"

DELEGATE_OneParam(OnSee, Object*);
class Enemy : public Character
{
	SUPER(Character);
public:
	Enemy();
	~Enemy();

	void Update()	override;
	// 충동처리후 캐릭터 움직일떄 사용
	void MoveCharacter() override;
	void Render() override;

	// 적캐릭터 움직일때 사용
	virtual void MoveCharacter(Vector2_F speed);

	GeometryCollision* GetSeeArea() const { return seeArea; }
	const SIZE_F& GetSeeAreaSize() const { return seeAreaSize; }
protected:
	void SettingSeeArea();
	void SettingSeeArea(SIZE_F& size);
	// 피격한 대상의 무적 처리 
	void HitCharacterInvincible(Character* hitCharacter);
public:
	OnSee onSee;
protected:
	Location worldLocation;
	// 충돌처리 전까지 플레이어가 움직이면 카메라의 좌표가 
	//변함으로 실제 위치와 다르게 되서 처음 위치구했을때의 
	//값을 저장해둔 변수
	Location cameraLocation;


	// 적이 플레이어를 볼수있는 영역
	GeometryCollision* seeArea;
	SIZE_F seeAreaSize;
};

