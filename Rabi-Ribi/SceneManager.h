#pragma once
#include "pch.h"
#include "Singleton.h"

class Object;

class SceneManager :public Singleton<SceneManager>
{
public:
	SceneManager();
	~SceneManager() override;

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	// ¾À Ãß°¡
	Object* AddScene(string key, Object* scene);
	Object* AddLoadingScene(string key, Object* scene);

	HRESULT ChangeScene(string name);
	HRESULT ChangeScene(string scenename, string loadingScenename);

public:
	// ÇöÀç ¸Ê
	static Object* currScene;
	// ·Îµù
	static Object* loadingScene;
	// ÀÐ°íÀÕ´Â
	static Object* readyScene;
private:
	map<string, Object*> sceneData;
	map<string, Object*> loadingSceneData;

	bool isLoading;
};

