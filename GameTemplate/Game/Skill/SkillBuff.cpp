#include "stdafx.h"
#include "SkillBuff.h"

void SkillBuff::SkillSetting()
{
	//�G�t�F�N�g�̍Đ��B
	skillEffect = NewGO<prefab::CEffect>(0);
	skillEffect->Play(L"Assets/effect/chant1.efk");
	skillEffect->SetPosition(m_user->GetPosition() + CVector3::AxisY()*20.0f);
	skillEffect->SetScale(CVector3::One() * 50.0f);

	//�A�j���[�V�����̍Đ��B
	//m_user->AnimationMagic();
}

void SkillBuff::Update()
{
	if (!skillEffect->IsPlay()) {
		//���ʒl�B
		int res = 0;
		//�o�t��������B
		if (!m_isWide) {
			//���ʎ��Ԃ��v�Z�B
			int result = m_user->GetStatusManager().GetStatus().MAT * 5.0f;
			res = m_target->Monster_Buff(m_status, skillPower, result);
		}
		else {	//�S�̂ɂ�����B
			res = WideBuff();
		}

		//���ʒl���L�^�B
		m_user->SetDamageResult(res);
		//�N�[���^�C���̐ݒ�B
		m_user->SetCoolTime(coolTime);

		skillEffect = nullptr;
		DeleteGO(this);
	}
}

int SkillBuff::WideBuff()
{
	//���ʎ��Ԃ̌v�Z�B
	int result = m_user->GetStatusManager().GetStatus().MAT * 5.0f;
	//�`�[�������o�[���擾�B
	auto list = m_target->GetTeamMenber();

	int res = 0;
	for (int i = 0; i < list.size(); i++) {
		//�S�̂Ƀo�t��������B
		res += list[i]->Monster_Buff(m_status, skillPower, result);
	}
	res /= list.size();		//�㏸�l�̕��ς��Ƃ�B

	return res;
}
