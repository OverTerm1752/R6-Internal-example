#pragma once
#pragma once
#include <cmath>
#include <algorithm>>
#pragma warning(disable:26451)

#define M_PI 3.14159265359

struct mat3_t
{
	union
	{
		struct
		{
			float _11, _12, _13;
			float _21, _22, _23;
			float _31, _32, _33;
		};
		float _m[3][3];
		float m[9];
	};

	void Transpose(void) {
		float temp;
		int i;
		int j;

		for (i = 0; i < 3; i++) {
			for (j = i + 1; j < 3; j++) {
				temp = _m[i][j];
				_m[i][j] = _m[j][i];
				_m[j][i] = temp;
			}
		}
	}

	mat3_t Inverse(void) const {
		mat3_t inv(*this);
		inv.Transpose();
		return inv;
	}
};



struct matrix_t
{
	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float _m[4][4];
		float m[16];
	};


	float Cofactor(const matrix_t& matrix, int row, int col)
	{
		int sign = ((row + col) % 2 == 0) ? 1 : -1;
		int i0 = (row + 1) % 4;
		int i1 = (row + 2) % 4;
		int i2 = (row + 3) % 4;
		int j0 = (col + 1) % 4;
		int j1 = (col + 2) % 4;
		int j2 = (col + 3) % 4;

		float minor0 = matrix._m[i0][j0] * (matrix._m[i1][j1] * matrix._m[i2][j2] - matrix._m[i1][j2] * matrix._m[i2][j1]);
		float minor1 = matrix._m[i0][j1] * (matrix._m[i1][j0] * matrix._m[i2][j2] - matrix._m[i1][j2] * matrix._m[i2][j0]);
		float minor2 = matrix._m[i0][j2] * (matrix._m[i1][j0] * matrix._m[i2][j1] - matrix._m[i1][j1] * matrix._m[i2][j0]);

		return sign * (minor0 - minor1 + minor2);
	}

	matrix_t Adjoint(const matrix_t& matrix)
	{
		matrix_t adjoint;

		for (int row = 0; row < 4; ++row) {
			for (int col = 0; col < 4; ++col) {
				adjoint._m[col][row] = Cofactor(matrix, row, col);
			}
		}

		return adjoint;
	}

	float Determinant(const matrix_t& matrix)
	{
		float det = 0.0f;
		for (int col = 0; col < 4; ++col) {
			det += matrix._m[0][col] * Cofactor(matrix, 0, col);
		}
		return det;
	}

	matrix_t Inverse(const matrix_t& matrix)
	{
		float det = Determinant(matrix);
		if (det == 0.0f) {
			// ¾ØÕó²»¿ÉÄæ
			return matrix;
		}

		float invDet = 1.0f / det;
		matrix_t adjoint = Adjoint(matrix);

		matrix_t inverse;
		for (int row = 0; row < 4; ++row) {
			for (int col = 0; col < 4; ++col) {
				inverse._m[row][col] = adjoint._m[row][col] * invDet;
			}
		}

		return inverse;
	}

	matrix_t Inverse()
	{
		return Inverse(*this);
	}

};

struct vec2_t
{
public:
	float x, y;

	vec2_t() = default;

	vec2_t(float x, float y)
	{
		this->x = x;
		this->y = y;
	};

	inline bool is_valid()
	{
		return (x != 0 && y != 0);
	}

	inline float length() const
	{
		return std::sqrt((x * x) + (y * y));
	}

	inline float distance(vec2_t b)
	{
		return (float)sqrt(pow(b.x - x, 2) + pow(b.y - y, 2));
	}

	inline void normalize()
	{

		if (x < -89)
			x = -89;


		else if (x > 89)
			x = 89;


		if (y < -360)
			y += 360;


		else if (y > 360)
			y -= 360;
	}

	inline vec2_t operator+(const vec2_t& input)
	{
		return vec2_t{ x + input.x, y + input.y };
	}

	inline vec2_t operator-(const vec2_t& input)
	{
		return vec2_t{ x - input.x, y - input.y };
	}

	inline vec2_t operator/(const vec2_t& input)
	{
		return vec2_t{ x / input.x, y / input.y };
	}

	inline vec2_t operator*(const vec2_t& input)
	{
		return vec2_t{ x * input.x, y * input.y };
	}

	inline vec2_t& operator+=(const vec2_t& input)
	{
		x += input.x;
		y += input.y;
		return *this;
	}

	inline vec2_t& operator+=(float input)
	{
		x += input;
		y += input;
		return *this;
	}

	inline vec2_t& operator*=(float input)
	{
		x *= input;
		y *= input;
		return *this;
	}

	inline vec2_t& operator/=(float input)
	{
		x /= input;
		y /= input;
		return *this;
	}

	inline vec2_t operator/(float input)
	{
		return vec2_t{ x / input, y / input };
	}

	inline bool operator==(const vec2_t& input) const
	{
		return x == input.x && y == input.y;
	}

	inline bool operator!=(const vec2_t& input) const
	{
		return x != input.x || y != input.y;
	}
};

struct vec3_t
{
public:
	vec3_t()
	{
		x = y = z = 0.f;
	}

	vec3_t(float fx, float fy, float fz)
	{
		x = fx;
		y = fy;
		z = fz;
	}

	float x, y, z;

	inline vec3_t operator+(const vec3_t& input) const
	{
		return vec3_t{ x + input.x, y + input.y, z + input.z };
	}

	inline vec3_t operator-(const vec3_t& input) const
	{
		return vec3_t{ x - input.x, y - input.y, z - input.z };
	}

	inline vec3_t operator/(float input) const
	{
		return vec3_t{ x / input, y / input, z / input };
	}

	inline vec3_t operator*(float input) const
	{
		return vec3_t{ x * input, y * input, z * input };
	}

	inline vec3_t& operator+=(const vec3_t& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}

	inline vec3_t& operator-=(const vec3_t& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}

	inline vec3_t& operator/=(float input)
	{
		x /= input;
		y /= input;
		z /= input;
		return *this;
	}

	inline vec3_t& operator*=(float input)
	{
		x *= input;
		y *= input;
		z *= input;
		return *this;
	}

	inline bool operator==(const vec3_t& input) const
	{
		return x == input.x && y == input.y && z == input.z;
	}

	inline bool operator!=(const vec3_t& input) const
	{
		return x != input.x || y != input.y || z != input.z;
	}

	inline bool operator<(const vec3_t& input) const
	{
		return false;
	}

	inline void make_absolute()
	{
		x = std::abs(x);
		y = std::abs(y);
		z = std::abs(z);
	}

	inline float clamp0to1(float value)
	{
		float result;
		if (value < 0)
		{
			result = 0;
		}
		else if (value > 1.f)
		{
			result = 1.f;
		}
		else
		{
			result = value;
		}
		return result;
	}

	inline float Lerp()
	{
		return x + (y - x) * clamp0to1(z);
	}

	inline float length_sqr() const
	{
		return (x * x) + (y * y) + (z * z);
	}

	inline float length() const
	{
		return (float)sqrt(length_sqr());
	}

	inline float length_2d() const
	{
		return (float)sqrt((x * x) + (y * y));
	}

	inline vec3_t normalize()
	{
		vec3_t out = *this;
		auto len = length();
		if (!len)
			return *this;

		out.x /= len;
		out.y /= len;
		out.z /= len;
		return out;
	}

	inline vec3_t cross(vec3_t rhs)
	{
		return vec3_t(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
	}

	inline float unity_magnitude()
	{
		return (float)sqrt((double)(x * x + y * y + z * z));
	}

	inline vec3_t unity_normalize()
	{
		float num = unity_magnitude();
		if (num > 1E-05f)
		{
			x /= num;
			y /= num;
			z /= num;
		}
		else
		{
			x = 0;
			y = 0;
			z = 0;
		}

		return { x,y,z };
	}

	inline vec3_t normalized() const
	{
		return { x == 0 ? 0 : x / length(), y == 0 ? 0 : y / length(), z == 0 ? 0 : z / length() };
	}

	inline float dot(vec3_t input) const
	{
		return (x * input.x) + (y * input.y) + (z * input.z);
	}

	inline float distance(vec3_t input) const
	{
		return (*this - input).length();
	}

	inline float distancesqr(vec3_t input) const
	{
		vec3_t dif = { x - input.x, y - input.y, z - input.z };
		return dif.x * dif.x + dif.y * dif.y + dif.z * dif.z;
	}

	inline float Distance(vec3_t v)
	{
		return sqrtf((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y) + (v.z - z) * (v.z - z));
	}

	inline float distance_2d(vec3_t input) const
	{
		return (*this - input).length_2d();
	}

	inline void clamp()
	{
		static_cast<void>(std::clamp(x, -89.f, 89.f));
		static_cast<void>(std::clamp(y, -180.f, 180.f));
		z = 0.f;
		return;
	}

	inline bool is_valid() const
	{
		return !(x == 0.f && y == 0.f && z == 0.f) || (x == -1.f && y == -1.f && z == -1.f);
	}
};

struct vec4_t
{
public:
	vec4_t()
	{
		x = y = z = w = 0.f;
	}

	vec4_t(float fx, float fy, float fz, float fw)
	{
		x = fx;
		y = fy;
		z = fz;
		w = fw;
	}

	float x, y, z, w;

	inline vec4_t operator+(const vec4_t& input) const
	{
		return vec4_t{ x + input.x, y + input.y, z + input.z, w + input.w };
	}

	inline vec4_t operator-(const vec4_t& input) const
	{
		return vec4_t{ x - input.x, y - input.y, z - input.z, w - input.w };
	}

	inline vec4_t operator/(float input) const
	{
		return vec4_t{ x / input, y / input, z / input, w / input };
	}

	inline vec4_t operator*(float input) const
	{
		return vec4_t{ x * input, y * input, z * input, w * input };
	}

	inline vec4_t& operator-=(const vec4_t& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;

		return *this;
	}

	inline vec4_t& operator/=(float input)
	{
		x /= input;
		y /= input;
		z /= input;
		w /= input;
		return *this;
	}

	inline vec4_t& operator*=(float input)
	{
		x *= input;
		y *= input;
		z *= input;
		w *= input;
		return *this;
	}

	inline bool operator==(const vec4_t& input) const
	{
		return x == input.x && y == input.y && z == input.z && w == input.w;
	}

	inline void make_absolute()
	{
		x = std::abs(x);
		y = std::abs(y);
		z = std::abs(z);
		w = std::abs(w);
	}

	inline float length_sqr() const
	{
		return (x * x) + (y * y) + (z * z) + (w * w);
	}

	inline float length() const
	{
		return (float)sqrt(length_sqr());
	}

	inline float length_2d() const
	{
		return (float)sqrt((x * x) + (y * y));
	}

	inline vec4_t normalized() const
	{
		return { x / length(), y / length(), z / length(), w / length() };
	}

	inline float dot(vec4_t input) const
	{
		return (x * input.x) + (y * input.y) + (z * input.z) + (w * input.w);
	}

	inline float distance(vec4_t input) const
	{
		return (*this - input).length();
	}

	inline float distance_2d(vec4_t input) const
	{
		return (*this - input).length_2d();
	}
	inline void clamp()
	{
		static_cast<void>(std::clamp(x, -89.f, 89.f));
		static_cast<void>(std::clamp(y, -180.f, 180.f));

		z = 0.f;
		w = 0.f;
	}

	float r2d = 57.2957795131f;
	float d2r = 0.01745329251f;



	vec4_t CreateAngleFromYawPitchRoll(float yaw, float pitch, float roll) {

		vec4_t result;
		float sr, cr, sp, cp, sy, cy;

		float hRoll = roll * 0.5f;
		sr = sin(hRoll);
		cr = cos(hRoll);

		float hPitch = pitch * 0.5f;
		sp = sin(hPitch);
		cp = cos(hPitch);

		float hYaw = yaw * 0.5f;
		sy = sin(hYaw);
		cy = cos(hYaw);

		result.x = cy * sr * cp - sy * cr * sp;
		result.y = cy * cr * sp + sy * sr * cp;
		result.z = sy * cr * cp - cy * sr * sp;
		result.w = cy * cr * cp + sy * sr * sp;

		return result;

	}




	inline static vec4_t QuaternionLookRotation(vec3_t forward, vec3_t up)
	{
		vec3_t vector = forward.unity_normalize();
		vec3_t Vector2 = (up).cross(vector).unity_normalize();
		vec3_t vec3_t = (vector).cross(Vector2);
		auto m00 = Vector2.x;
		auto m01 = Vector2.y;
		auto m02 = Vector2.z;
		auto m10 = vec3_t.x;
		auto m11 = vec3_t.y;
		auto m12 = vec3_t.z;
		auto m20 = vector.x;
		auto m21 = vector.y;
		auto m22 = vector.z;


		float num8 = (m00 + m11) + m22;
		auto quaternion = vec4_t();
		if (num8 > 0.f)
		{
			auto num = (float)sqrt(num8 + 1.f);
			quaternion.w = num * 0.5f;
			num = 0.5f / num;
			quaternion.x = (m12 - m21) * num;
			quaternion.y = (m20 - m02) * num;
			quaternion.z = (m01 - m10) * num;
			return quaternion;
		}
		if ((m00 >= m11) && (m00 >= m22))
		{
			auto num7 = (float)sqrt(((1.f + m00) - m11) - m22);
			auto num4 = 0.5f / num7;
			quaternion.x = 0.5f * num7;
			quaternion.y = (m01 + m10) * num4;
			quaternion.z = (m02 + m20) * num4;
			quaternion.w = (m12 - m21) * num4;
			return quaternion;
		}
		if (m11 > m22)
		{
			auto num6 = (float)sqrt(((1.f + m11) - m00) - m22);
			auto num3 = 0.5f / num6;
			quaternion.x = (m10 + m01) * num3;
			quaternion.y = 0.5f * num6;
			quaternion.z = (m21 + m12) * num3;
			quaternion.w = (m20 - m02) * num3;
			return quaternion;
		}
		auto num5 = (float)sqrt(((1.f + m22) - m00) - m11);
		auto num2 = 0.5f / num5;
		quaternion.x = (m20 + m02) * num2;
		quaternion.y = (m21 + m12) * num2;
		quaternion.z = 0.5f * num5;
		quaternion.w = (m01 - m10) * num2;
		return quaternion;
	}

	float quat_to_deg(const vec4_t& quat) {
		if (!quat.is_valid()) return 0.0f;

		// Convert quaternion to Euler angles
		float ysqr = quat.y * quat.y;

		// Roll (x-axis rotation)
		float t0 = 2.0f * (quat.w * quat.x + quat.y * quat.z);
		float t1 = 1.0f - 2.0f * (quat.x * quat.x + ysqr);
		float roll = std::atan2(t0, t1);

		// Pitch (y-axis rotation)
		float t2 = 2.0f * (quat.w * quat.y - quat.z * quat.x);
		t2 = t2 > 1.0f ? 1.0f : t2;
		t2 = t2 < -1.0f ? -1.0f : t2;
		float pitch = std::asin(t2);

		// Yaw (z-axis rotation)
		float t3 = 2.0f * (quat.w * quat.z + quat.x * quat.y);
		float t4 = 1.0f - 2.0f * (ysqr + quat.z * quat.z);
		float yaw = std::atan2(t3, t4);

		// Convert to degrees
		const float rad_to_deg = 180.0f / 3.14159265358979323846f;
		yaw *= rad_to_deg;
		pitch *= rad_to_deg;
		roll *= rad_to_deg;

		// For this example, we'll assume we want the yaw angle
		return yaw;
	}

	inline bool is_valid() const
	{
		return !((x == 0.f && y == 0.f && z == 0.f && w == 0.f) || (x == -1.f && y == -1.f && z == -1.f && w == -1.f));
	}
};

/*
Vector2 calculate_angle(vec3_t source, vec3_t destination)
{
	vec3_t difference = source - destination;
	float length = difference.length();

	Vector2 ret{};

	ret.y = asinf(difference.y / length);
	ret.x = -atan2f(difference.x, -difference.z);

	ret = { ret.x * 57.29578f, ret.y * 57.29578f };

	return ret;
}

void normalize(vec3_t& in)
{
	if (in.x > 89.f) in.x -= 360.f;
	else if (in.x < -89.f) in.x += 360.f;

	while (in.y > 180)in.y -= 360;
	while (in.y < -180)in.y += 360;
	in.z = 0;
}
vec3_t smooth_aim(vec3_t target, vec3_t delta_rotation, float smooth)
{
	vec3_t diff = target - delta_rotation;
	normalize(diff);
	return delta_rotation + diff / smooth;
}

static auto calculate_angle2(const vec3_t from, const vec3_t to) -> Vector2
{
	auto const diff = from - to;
	auto const length = diff.length();

	Vector2 ret
	{
		ret.y = asinf(diff.y / length),
		ret.x = -atan2(diff.x, -diff.z),
	};

	return Vector2(ret.x * 57.29578, ret.y * 57.29578);
}

float normalize_angle(float angle)
{
	while (angle > 360) angle -= 360;
	while (angle < 0) angle += 360;
	return angle;
}

Vector2 rotate_point(Vector2 point_to_rotate, Vector2 center_point, float angle)
{
	float rad = ((normalize_angle(angle)) * static_cast<float>((M_PI / 180.f)));
	float s = -sin(rad);
	float c = cos(rad);
	float xnew = point_to_rotate.x * c - point_to_rotate.y * s;
	float znew = point_to_rotate.x * s + point_to_rotate.y * c;
	point_to_rotate.x -= center_point.x;
	point_to_rotate.y -= center_point.y;
	point_to_rotate.x = xnew + center_point.x;
	point_to_rotate.y = znew + center_point.y;
	return point_to_rotate;
}
*/

