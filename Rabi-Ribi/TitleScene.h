#pragma once
#include "Object.h"
class TitleScene : public Object
{
public:
	//  멤버 변수 초기화, 메모리 할당
	HRESULT Init() override;
	// 메모리 해제
	void Release() override;
	// 프레임 단위 게임 로직 실행 ( 데이터 변경)
	void Update() override;
	// 프레임 단위 출력 (이미지, 텍스트)
	void Render() override;
private:
	ImageInfo bg;
	ImageInfo font;
	ImageInfo start;
};

