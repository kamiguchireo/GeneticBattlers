//�N���X�̃R�s�[���֎~�������ꍇ�ɂ�����p�����Ă�������

namespace Engine {
	struct Noncopyable {
		Noncopyable() = default;
		Noncopyable(const Noncopyable &) = delete;
		Noncopyable&operator = (const Noncopyable &) = delete;
	};
}