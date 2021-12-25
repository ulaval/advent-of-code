// test

#pragma once

template <size_t M, size_t N>
using mat_t = std::array<std::array<int, N>, M>;

template <size_t M, size_t N>
std::ostream& operator<<(std::ostream& out, const mat_t<M, N>& mat) {
	static_assert(M > 0 && N > 0);
	for (size_t row=0; row<mat.size(); row++) {
		for (size_t col=0; col<mat[0].size(); col++) {
			out << std::setw(2) << mat[row][col] << ' ';
		}
		if (row < mat.size()-1) out << '\n';
	}
	return out;
}

template <size_t M, size_t N, size_t P>
auto mat_multiply(const mat_t<M, N>& a, const mat_t<N, P>& b) {
	mat_t<M, P> product{};
	for (size_t row=0; row<M; row++) {
		for (size_t col=0; col<P; col++) {
			// row of A * col of B => (row,col) of product
			for (size_t n=0; n<N; n++)
				product[row][col] += a[row][n] * b[n][col];
		}
	}
	return product;
}

constexpr auto rx(int angle) {
	// angle est en multiples de pi/2... 0, 1, 2 ou 3 pi/2
	assert(angle >= 0 && angle <= 3);
	constexpr array<int, 4> sin = { 0, 1, 0, -1 };
	constexpr array<int, 4> cos = { 1, 0, -1, 0 };
	return array{ array{1, 0, 0}, array{0, cos[angle], -sin[angle]}, array{0, sin[angle], cos[angle]} };
}

constexpr auto ry(int angle) {
	// angle est en multiples de pi/2... 0, 1, 2 ou 3 pi/2
	assert(angle >= 0 && angle <= 3);
	constexpr array<int, 4> sin = { 0, 1, 0, -1 };
	constexpr array<int, 4> cos = { 1, 0, -1, 0 };
	return array{ array{cos[angle], 0, sin[angle]}, array{0, 1, 0}, array{-sin[angle], 0, cos[angle]} };
}

constexpr auto rz(int angle) {
	// angle est en multiples de pi/2... 0, 1, 2 ou 3 pi/2
	assert(angle >= 0 && angle <= 3);
	constexpr array<int, 4> sin = { 0, 1, 0, -1 };
	constexpr array<int, 4> cos = { 1, 0, -1, 0 };
	return array{ array{cos[angle], -sin[angle], 0}, array{sin[angle], cos[angle], 0}, array{0, 0, 1} };
}

array<coord3d, 24> variations_of(const coord3d& c) {
	array<coord3d, 24> variations{};
	int i = 0;
	for (int a=0; a<4; a++) {
		const mat_t<1, 3> c1 = { array{c[0], c[1], c[2]} };
		const mat_t<1, 3> c2 = { array{-c[0], c[1], c[2]} };
		const auto r = rx(a);
		const auto p1 = mat_multiply(c1, r);
		const auto p2 = mat_multiply(c2, r);
		variations[i++] = p1[0];
		variations[i++] = p2[0];
	}
	for (int a=0; a<4; a++) {
		const mat_t<1, 3> c1 = { array{c[1], -c[2], -c[0]} };
		const mat_t<1, 3> c2 = { array{-c[1], c[2], -c[0]} };
		const auto r = ry(a);
		const auto p1 = mat_multiply(c1, r);
		const auto p2 = mat_multiply(c2, r);
		variations[i++] = p1[0];
		variations[i++] = p2[0];
	}
	for (int a=0; a<4; a++) {
		const mat_t<1, 3> c1 = { array{c[2], c[1], -c[0]} };
		const mat_t<1, 3> c2 = { array{-c[2], -c[1], -c[0]} };
		const auto r = rz(a);
		const auto p1 = mat_multiply(c1, r);
		const auto p2 = mat_multiply(c2, r);
		variations[i++] = p1[0];
		variations[i++] = p2[0];
	}
	return variations;
}