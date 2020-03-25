#include "stdafx.h"
#include "SkillList.h"

SkillList*SkillList::m_instance = nullptr;

SkillList::SkillList()
{
	if (m_instance != nullptr)
	{
		std::abort();
	}

	m_instance = this;

	//�ʏ�s���B
	const int typeNum = 3;
	SkillTable typeList[typeNum];
	auto attack = NewGO<Attack>(0);		//�ʏ�U���B
	attack->InitSkill("�ʏ�U��", 1.0f, 30.0f, 0.95f, 0);
	attack->SetEffect(L"Assets/effect/test.efk");
	typeList[0].push_back(attack);
	auto doublAttack = NewGO<DoubleAttack>(0);		//�_�u���A�^�b�N�B
	doublAttack->InitSkill("�_�u���A�^�b�N", 1.0f, 50.0f, 0.85f, 1);
	typeList[0].push_back(doublAttack);

	//�񕜖��@�B
	auto heal = NewGO<Heal>(0);		//�q�[���B
	heal->InitSkill("�q�[��", 0.7f, 30.0f, 1.0f, 100, en_elements_Empty, true);
	typeList[1].push_back(heal);
	auto hiheal = NewGO<Heal>(0);	//�n�C�q�[���B
	hiheal->InitSkill("�n�C�q�[��", 1.3f, 50.0f, 1.0f, 101, en_elements_Empty, true);
	typeList[1].push_back(hiheal);

	//�o�t���@
	auto sukuruto = NewGO<BuffSkill>(0);	//�X�N���g�B
	sukuruto->InitSkill("�X�N���g", 2.0f, 50.0f, 1.0f, 200, en_elements_Empty, true);
	sukuruto->SetStatusBuff(en_buff_DEF);
	typeList[2].push_back(sukuruto);
	auto sukara = NewGO<BuffSkillWide>(0);
	sukara->InitSkill("�X�J��", 1.5f, 60.0f, 1.0f, 201, en_elements_Empty, true);
	sukara->SetStatusBuff(en_buff_DEF);
	typeList[2].push_back(sukara);
	
	for (int i = 0; i < typeNum; i++)
	{
		m_skillList.push_back(typeList[i]);
	}
}

SkillList::~SkillList()
{
	for (SkillTable table : m_skillList)
	{
		for (SkillBase* SB : table)
		{
			DeleteGO(SB);
		}
	}

	m_instance = nullptr;
}

//�ʏ�U���B
bool Attack::UseSkill(MonsterBase * attack, MonsterBase * target)
{
	if(skillEffect == nullptr){
		//�G�t�F�N�g�̍Đ��B
		skillEffect = NewGO<prefab::CEffect>(0);
		skillEffect->Play(effectPath);
		skillEffect->SetPosition(attack->GetPosition() + CVector3::AxisY()*20.0f);
		skillEffect->SetRotation(attack->GetRotation());
		skillEffect->SetScale(CVector3::One() * 20.0f);
	}
	else if (!skillEffect->IsPlay()) {
		//�_���[�W��^����B
		int damage = DamageCalcuration(attack, target);
		int res = target->Damage(damage);

		attack->SetActResult(m_skillNo, res);
		//�N�[���^�C���̐ݒ�B
		attack->SetCoolTime(coolTime);

		skillEffect = nullptr;

		return true;
	}

	return false;
}

//�_�u���A�^�b�N�B
bool DoubleAttack::UseSkill(MonsterBase * attack, MonsterBase * target)
{
	if (skillEffect == nullptr) {
		//�G�t�F�N�g�̍Đ��B
		skillEffect = NewGO<prefab::CEffect>(0);
		skillEffect->Play(L"Assets/effect/test.efk");
		skillEffect->SetPosition(attack->GetPosition() + CVector3::AxisY()*20.0f);
		CQuaternion qRot;
		qRot.SetRotationDeg(CVector3::AxisY(), 90.0f);
		qRot.Multiply(attack->GetRotation());
		skillEffect->SetRotation(qRot);
		skillEffect->SetScale(CVector3::One() * 20.0f);
	}
	else if (!skillEffect->IsPlay()) {
		int res = 0;
		//�_���[�W�̌v�Z�B
		int damage = DamageCalcuration(attack, target);
		res += target->Damage(damage);
		//�Q��U���B
		damage = DamageCalcuration(attack, target);
		res += target->Damage(damage);
		
		attack->SetActResult(m_skillNo, res);

		//�N�[���^�C���̐ݒ�B
		attack->SetCoolTime(coolTime);

		skillEffect = nullptr;

		return true;
	}


	return false;
}


//�q�[���B
bool Heal::UseSkill(MonsterBase * attack, MonsterBase * target)
{
	if (skillEffect == nullptr) {
		//�G�t�F�N�g�̍Đ��B
		skillEffect = NewGO<prefab::CEffect>(0);
		skillEffect->Play(L"Assets/effect/chant1.efk");
		skillEffect->SetPosition(attack->GetPosition() + CVector3::AxisY()*20.0f);
		skillEffect->SetScale(CVector3::One() * 50.0f);
	}
	else if (!skillEffect->IsPlay()) {
		//�񕜗ʂ̌v�Z�B
		int result = attack->GetStatus().MAT * skillPower;
		int res = target->Healing(result);
		attack->SetActResult(m_skillNo, res);
		//�N�[���^�C���̐ݒ�B
		attack->SetCoolTime(coolTime);

		skillEffect = nullptr;

		return true;
	}

	return false;
}

bool BuffSkill::UseSkill(MonsterBase * attack, MonsterBase * target)
{
	if (skillEffect == nullptr) {
		//�G�t�F�N�g�̍Đ��B
		skillEffect = NewGO<prefab::CEffect>(0);
		skillEffect->Play(L"Assets/effect/chant1.efk");
		skillEffect->SetPosition(attack->GetPosition() + CVector3::AxisY()*20.0f);
		skillEffect->SetScale(CVector3::One() * 50.0f);
	}
	else if (!skillEffect->IsPlay()) {
		//���ʎ��Ԃ��v�Z�B
		int result = attack->GetStatus().MAT * 5.0f;
		//�o�t��������B
		int res = target->Monster_Buff(m_status, skillPower, result);
		attack->SetActResult(m_skillNo, res);
		//�N�[���^�C���̐ݒ�B
		attack->SetCoolTime(coolTime);

		skillEffect = nullptr;

		return true;
	}

	return false;
}

bool BuffSkillWide::UseSkill(MonsterBase * attack, MonsterBase * target)
{
	if (skillEffect == nullptr) {
		//�G�t�F�N�g�̍Đ��B
		skillEffect = NewGO<prefab::CEffect>(0);
		skillEffect->Play(L"Assets/effect/chant1.efk");
		skillEffect->SetPosition(attack->GetPosition() + CVector3::AxisY()*20.0f);
		skillEffect->SetScale(CVector3::One() * 50.0f);
	}
	else if (!skillEffect->IsPlay()) {
		//���ʎ��Ԃ̌v�Z�B
		int result = attack->GetStatus().MAT * 5.0f;
		//�`�[�������o�[���擾�B
		auto list = target->GetTeamMenber();

		int res = 0;
		for (int i = 0; i < list.size(); i++) {
			//�S�̂Ƀo�t��������B
			res += list[i]->Monster_Buff(m_status, skillPower, result);
		}
		res /= list.size();		//�㏸�l�̕��ς��Ƃ�B
		attack->SetActResult(m_skillNo, res);
		//�N�[���^�C���̐ݒ�B
		attack->SetCoolTime(coolTime);

		skillEffect = nullptr;

		return true;
	}

	return false;
}
