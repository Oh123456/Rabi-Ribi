#pragma once
#include "Character.h"

//player
enum class ErinaAnimmationKinds
{
	Idle,
	Move_Right,
	Move_Left,
};


class Erina : public Character
{
	SUPER(Character);
public:
	Erina();
	~Erina();

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;


	void PlayerInputSetting(class PlayerInput* playerInput) override;

	ErinaAnimmationKinds GetAnimKinds() { return animKinds; }
private:
	void MoveUP();
	void MoveSide();

private:
	class Animinstance* animmation;

	ErinaAnimmationKinds animKinds;
};

