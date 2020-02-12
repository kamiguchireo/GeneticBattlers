#pragma once
class GameCamera:public IGameObject
{
public:
	GameCamera();		//コンストラクタ。
	~GameCamera();		//デストラクタ。
	
	bool Start();		//初期化処理。
	void Update();		//更新処理。

	//シングルトンパターン。
	static GameCamera* m_instance;
	static GameCamera* GetInstance()
	{
		return m_instance;
	}

private:
	CVector3 m_firstPosition = CVector3::Zero();
};

