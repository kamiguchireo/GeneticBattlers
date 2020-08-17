#include "stdafx.h"
#include "StatusBase.h"

namespace JOB_Status
{
	const Status ATTAKER =
	{
		130,		//HP
		30,			//ATK
		10,			//DEF
		5,			//MAT
		10,			//MDF
		10			//DEX
	};
	const Status HEALER =
	{
		90,			//HP
		5,			//ATK
		10,			//DEF
		30,			//MAT
		20,			//MDF
		10			//DEX
	};
	const Status SUPPOTER =
	{
		130,		//HP
		5,			//ATK
		15,			//DEF
		20,			//MAT
		15,			//MDF
		15			//DEX
	};
}

void CStatusBase::StatusAttaker()
{
	SetStatus(JOB_Status::ATTAKER);
}

void CStatusBase::StatusHealer()
{
	SetStatus(JOB_Status::HEALER);
}

void CStatusBase::StatusSupporter()
{
	SetStatus(JOB_Status::SUPPOTER);
}

int CStatusBase::Healing(int healing)
{
	int res = healing;
	m_status.HP += healing;
	//�ő�HP�𒴂����B
	if (m_status.HP > m_statusBase.HP) {
		int diff = m_status.HP - m_statusBase.HP;
		res -= diff;		//�����������������B

		m_status.HP = min(m_status.HP, m_statusBase.HP);
	}

	return res;
}

int CStatusBase::Monster_Buff(StatusBuff status, float pow, float time)
{
	int res = 0;
	//�{������1�������Ă����B
	pow -= 1.0f;

	//�o�t��������B
	switch (status)
	{
	case en_buff_ATK:
		res = static_cast<int>(m_statusBase.ATK * pow);	//�㏸�l�̌v�Z�B
		m_buffValues[status] = res;

		break;
	case en_buff_DEF:
		res = static_cast<int>(m_statusBase.DEF * pow);	//�㏸�l�̌v�Z�B
		m_buffValues[status] = res;

		break;
	case en_buff_MAT:
		res = static_cast<int>(m_statusBase.MAT * pow);	//�㏸�l�̌v�Z�B
		m_buffValues[status] = res;

		break;
	case en_buff_MDF:
		res = static_cast<int>(m_statusBase.MDF * pow);	//�㏸�l�̌v�Z�B
		m_buffValues[status] = res;

		break;
	case en_buff_DEX:
		res = static_cast<int>(m_statusBase.DEX * pow);	//�㏸�l�̌v�Z�B
		m_buffValues[status] = res;

		break;
	}
	//�o�t�̌��ʎ��Ԃ�ݒ�B
	m_buffTimeList[status] = time;
	//�o�t�̌��ʂ𔽉f�B
	SumBufAndDebuff(status);

	return res;
}

int CStatusBase::Monster_Debuff(StatusBuff status, float pow, float time)
{
	int res = 0;
	//�{������1�������Ă����B
	pow -= 1.0f;

	//�o�t��������B
	switch (status)
	{
	case en_buff_ATK:
		res = static_cast<int>(m_statusBase.ATK * pow);//�ቺ�l�̌v�Z�B
		m_debuffValues[status] = res;

		break;
	case en_buff_DEF:
		res = static_cast<int>(m_statusBase.DEF * pow);//�ቺ�l�̌v�Z�B
		m_debuffValues[status] = res;

		break;
	case en_buff_MAT:
		res = static_cast<int>(m_statusBase.MAT * pow);//�ቺ�l�̌v�Z�B
		m_debuffValues[status] = res;

		break;
	case en_buff_MDF:
		res = static_cast<int>(m_statusBase.MDF * pow);//�ቺ�l�̌v�Z�B
		m_debuffValues[status] = res;

		break;
	case en_buff_DEX:
		res = static_cast<int>(m_statusBase.DEX * pow);//�ቺ�l�̌v�Z�B
		m_debuffValues[status] = res;

		break;
	}
	//�f�o�t�̌��ʎ��Ԃ�ݒ�B
	m_debuffTimeList[status] = time;
	//�f�o�t�̌��ʂ𔽉f�B
	SumBufAndDebuff(status);

	//���ʒl�̐�Βl�����B
	res = abs(res);

	return res;
}

void CStatusBase::SumBufAndDebuff(int status)
{
	//�o�t�ƃf�o�t�𔽉f�����X�e�[�^�X���o���B
	switch (status)
	{
	case en_buff_ATK:
		m_status.ATK = m_statusBase.ATK + m_buffValues[status] + m_debuffValues[status];
		break;
	case en_buff_DEF:
		m_status.DEF = m_statusBase.DEF + m_buffValues[status] + m_debuffValues[status];
		break;
	case en_buff_MAT:
		m_status.MAT = m_statusBase.MAT + m_buffValues[status] + m_debuffValues[status];
		break;
	case en_buff_MDF:
		m_status.MDF = m_statusBase.MDF + m_buffValues[status] + m_debuffValues[status];
		break;
	case en_buff_DEX:
		m_status.DEX = m_statusBase.DEX + m_buffValues[status] + m_debuffValues[status];
		break;
	}
}

void CStatusBase::ResetBuff(int i)
{
	//�o�t�ɂ��㏸�l��0�ɂ���
	m_buffValues[i] = 0;
	//�o�t�̌��ʎ��Ԃ�0�ɂ���B
	m_buffTimeList[i] = 0.0f;

	//�X�e�[�^�X�����̃X�e�[�^�X�ɖ߂��B(�f�o�t������Ȃ炻������f)
	SumBufAndDebuff(i);
}

void CStatusBase::ResetDebuff(int i)
{
	//�f�o�t�ɂ��ቺ�l��0�ɂ���
	m_debuffValues[i] = 0;
	//�f�o�t�̌��ʎ��Ԃ�0�ɂ���B
	m_debuffTimeList[i] = 0;

	//�X�e�[�^�X�̒ቺ�����ɖ߂��B
	SumBufAndDebuff(i);
}

//bool CStatusBase::AddATB()
//{
//	const float addTime = g_gameTime.GetFrameDeltaTime() * 2.0f;
//	//���S���͏����𒆒f����B
//	if (m_stateAI == en_state_Death) return false;
//	//�o�t�̌��ʎ��Ԍ����B
//	m_activeTime += (float)m_status.DEX * addTime;
//	for (int i = 0; i < en_buff_num; i++) {
//		if (m_buffTimeList[i] == 0.0f) continue;
//
//		m_buffTimeList[i] -= addTime;
//		if (m_buffTimeList[i] < 0.0f) {
//			ResetBuff(i);
//		}
//	}
//	//�f�o�t�̌��ʎ��Ԍ����B
//	for (int i = 0; i < en_buff_num; i++) {
//		if (m_debuffTimeList[i] == 0.0f) continue;
//
//		m_debuffTimeList[i] -= addTime;
//		if (m_debuffTimeList[i] < 0.0f) {
//			ResetDebuff(i);
//		}
//	}
//
//	if (m_activeTime > m_coolTime) {
//		return true;
//	}
//	return false;
//}
