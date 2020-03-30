#pragma once
class GameCamera:public IGameObject
{
public:
	GameCamera();		//コンストラクタ。
	~GameCamera();		//デストラクタ。
	
	bool Start();		//初期化処理。
	void Update();		//更新処理。

	//シングルトンパターン。
	static GameCamera* GetInstance()
	{
		return m_instance;
	}

private:
	static GameCamera* m_instance;		//シングルトンパターン。
	CVector3 m_firstPosition = CVector3::Zero();
	CVector3 m_firstTarget = CVector3::Zero();
};

