//クラスのコピーを禁止したい場合にこれを継承してください
#ifndef _NONCOPYABLE_H_
#define _NONCOPYABLE_H_

namespace Engine {
	struct Noncopyable {
		Noncopyable() = default;
		Noncopyable(const Noncopyable &) = delete;
		Noncopyable&operator = (const Noncopyable &) = delete;
	};
}

#endif