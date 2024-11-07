#pragma once
class Scene
{
protected:
	std::list<GameObject*> gameObjects;

	std::list<GameObject*> addGameObjects;
	std::list<GameObject*> removeGameObjects;

	sf::View uiView;
	sf::View worldView;
	sf::View saveView;


public:
	const SceneIds id;

	Scene(SceneIds id);
	virtual ~Scene() = default;

	virtual void Init();
	virtual void Release();

	virtual void Enter();
	virtual void Exit();

	virtual void Update(float dt);
	virtual void LateUpdate(float dt);
	virtual void FixedUpdate(float dt);
	virtual void OnPreDraw();
	virtual void Draw(sf::RenderWindow& window);
	virtual void OnPostDraw();

	template<typename T>
	T* AddGo(T* obj)
	{
		addGameObjects.push_back(obj);
		return obj;
	}

	virtual void RemoveGo(GameObject* obj);
	virtual GameObject* FindGo(const std::string& name);
	virtual int FindGoAll(const std::string& name, std::list<GameObject*>& list);
	sf::Vector2f ScreenToWorld(sf::Vector2i screenPos);
	sf::Vector2f WorldToScreen(sf::Vector2i worldPos);
	//sf::Vector2f ScreenToUi(sf::Vector2i screenPos);
	//sf::Vector2f UiToScreen(sf::Vector2i worldPos);

	void ApplyAddGo();
	void ApplyRemoveGO();

};
