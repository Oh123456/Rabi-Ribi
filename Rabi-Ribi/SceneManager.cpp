#include "SceneManager.h"
#include "Object.h"

Object* SceneManager::currScene = nullptr;
Object* SceneManager::loadingScene = nullptr;
Object* SceneManager::readyScene = nullptr;

DWORD CALLBACK LoadingThread(LPVOID pvParam)
{

	SceneManager::readyScene->Init();
	SceneManager::currScene = SceneManager::readyScene;
	SceneManager::currScene->SetIsValid(true);

	SceneManager::loadingScene->Release();
	SceneManager::loadingScene->SetIsValid(false);
	SceneManager::loadingScene = nullptr;
	SceneManager::readyScene = nullptr;


	return 0;
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

HRESULT SceneManager::Init()
{
	return S_OK;
}

void SceneManager::Release()
{
	sceneData.clear();
	loadingSceneData.clear();
}

void SceneManager::Update()
{
	//if (currScene)
	//	currScene->Update();
}

void SceneManager::Render()
{
	//if (currScene)
	//	currScene->Render();
}

Object* SceneManager::AddScene(string key, Object * scene)
{
	if (scene == nullptr)
		return nullptr;
	if (sceneData.find(key) != sceneData.end())
		return nullptr;
	sceneData.insert(make_pair(key, scene));
	return scene;
}

Object* SceneManager::AddLoadingScene(string key, Object * scene)
{
	if (scene == nullptr)
		return nullptr;
	if (loadingSceneData.find(key) != loadingSceneData.end())
		return nullptr;
	loadingSceneData.insert(make_pair(key, scene));
	return scene;
}

HRESULT SceneManager::ChangeScene(string name)
{
	map<string, Object*>::const_iterator it;
	it = sceneData.find(name);
	if (it == sceneData.end())
		return E_FAIL;
	Object* scene = it->second;
	if (scene)
	{
		TimerManager::GetSingleton()->AllDeleteTimer();
		if (SUCCEEDED(scene->Init()))
		{
			if (currScene)
			{
				currScene->Release();
				currScene->SetIsValid(false);
			}
			currScene = scene;
			currScene->SetIsValid(true);

			
			return S_OK;
		
		}
	}

	return E_FAIL;

}

HRESULT SceneManager::ChangeScene(string scenename, string loadingScenename)
{
	map<string, Object*>::const_iterator it;
	it = sceneData.find(scenename);
	if (it == sceneData.end())
		return E_FAIL;

	map<string, Object*>::const_iterator loading_it = loadingSceneData.find(loadingScenename);
	if (loading_it == loadingSceneData.end())
		return ChangeScene(scenename);


	if (SUCCEEDED(loading_it->second->Init()))
	{
		if (currScene)
		{
			currScene->SetIsValid(false);
			currScene->Release();
		}
		currScene = loading_it->second;

		readyScene = it->second;
		loadingScene = loading_it->second;

		currScene = loading_it->second;
		currScene->SetIsValid(true);
		TimerManager::GetSingleton()->AllDeleteTimer();
		// 스레드 핸들
		HANDLE hThread;
		DWORD loadThreadID;
		hThread = CreateThread(NULL,
										0,
										LoadingThread/*실행시킬 함수*/ ,
										NULL/*함수 파라미터*/,
										0, &loadThreadID);

		CloseHandle(hThread);
		return S_OK;
	}
	return E_FAIL;
}
