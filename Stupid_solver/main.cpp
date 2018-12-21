template<class T>
class Solver{
public:
	T a[1111111];
	size_t sz;

	Solver() {
		sz = 0;
	}

	void insert(T x) {
		a[sz++] = x;
	}

	T get_min() {
		T answer = a[0];
		for (size_t i = 0; i < sz; ++i) {
			if (a[i] < answer) {
				answer = a[i];
			}
		}
		return answer;
	}

	void erase(T x) {
		for (size_t i = 0; i < sz; ++i) {
			if (a[i] == x) {
				std::swap(a[i], a[sz - 1]);
				sz--;
				break;
			}
		}
	}

	void extract_min() {
		erase(get_min());
	}

	void change(T x, T y) {
		for (size_t i = 0; i < sz; ++i) {
			if (a[i] == x) {
				a[i] = y;
				return;
			}
		}
	}
};