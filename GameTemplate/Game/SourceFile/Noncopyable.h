//クラスのコピーを禁止したい場合にこれを継承してください

namespace Engine {
	struct Noncopyable {
		Noncopyable() = default;
		Noncopyable(const Noncopyable &) = delete;
		Noncopyable&operator = (const Noncopyable &) = delete;
	};
}