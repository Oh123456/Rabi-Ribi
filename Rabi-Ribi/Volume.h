#pragma once
// 0.0~1.0f 사이의 float 값을 표현하기 위한 클래스
// float  과 호환성을 위하여 오퍼레이터 연산자 추가


class Volume
{
public:
	Volume() : volume(1.0f) {};
	Volume(const float& f)
	{
		this->volume = f;
	}
	~Volume() {};
#pragma region operator 
	inline Volume& operator= (const float& f)
	{
		this->volume = f;
		if (this->volume > 1.0f)
			this->volume = 1.0f;
		else if (this->volume < 0.0f)
			this->volume = 0.0f;
		return *this;
	}

	// 후위 연산자 오퍼레이터
	inline const Volume operator++(const int n)
	{
		const Volume tmep = *this;
		this->volume += 0.1f;
		if (this->volume > 1.0f)
			this->volume = 1.0f;
		return tmep;
	}

	// 전위 연산자  오퍼레이터
	inline Volume& operator++()
	{

		this->volume += 0.1f;
		if (this->volume > 1.0f)
			this->volume = 1.0f;
		return *this;
	}

	// 후위 연산자 오퍼레이터
	inline const Volume operator--(const int n)
	{
		const Volume tmep = *this;
		this->volume -= 0.1f;
		if (this->volume > 1.0f)
			this->volume = 1.0f;
		return tmep;
	}

	// 전위 연산자  오퍼레이터
	inline Volume& operator--()
	{
		this->volume -= 0.1f;
		if (this->volume < 0.0f)
			this->volume = 0.0f;
		return *this;
	}

	inline const Volume operator+(const float& f)
	{
		Volume temp;
		temp = this->volume + f;
		return temp;
	}

	inline const Volume operator+(Volume& v)
	{
		Volume temp;
		temp = this->volume + v.c_float();
		return temp;
	}

	inline Volume& operator+=(const float& f)
	{

		this->volume += f;
		if (this->volume > 1.0f)
			this->volume = 1.0f;
		return *this;
	}

	inline Volume& operator+=(Volume& v)
	{

		this->volume += v.c_float();
		if (this->volume > 1.0f)
			this->volume = 1.0f;
		return *this;
	}

	inline const Volume operator-(const float& f)
	{
		Volume temp;
		temp = this->volume - f;
		return temp;
	}

	inline const Volume operator-(Volume& v)
	{
		Volume temp;
		temp = this->volume - v.c_float();
		return temp;
	}

	inline Volume& operator-=(const float& f)
	{

		this->volume -= f;
		if (this->volume > 1.0f)
			this->volume = 1.0f;
		return *this;
	}

	inline Volume& operator-=(Volume& v)
	{

		this->volume -= v.c_float();
		if (this->volume > 1.0f)
			this->volume = 1.0f;
		return *this;
	}

	inline const Volume operator*(const float& f)
	{
		Volume temp;
		temp = this->volume * f;
		return temp;
	}

	inline const Volume operator*(Volume& v)
	{
		Volume temp;
		temp = this->volume * v.c_float();
		return temp;
	}

	inline const Volume operator*=(const float& f)
	{
		this->volume *= f;
		if (this->volume > 1.0f)
			this->volume = 1.0f;
		return *this;
	}

	inline const Volume operator*=(Volume& v)
	{
		this->volume *= v.c_float();
		if (this->volume > 1.0f)
			this->volume = 1.0f;
		return *this;
	}

	inline const Volume operator/(const float& f)
	{
		Volume temp;
		temp = this->volume / f;
		return temp;
	}

	inline const Volume operator/(Volume& v)
	{
		Volume temp;
		temp = this->volume / v.c_float();
		return temp;
	}

	inline const Volume operator/=(const float& f)
	{
		this->volume /= f;
		if (this->volume < 0.0f)
			this->volume = 0.0f;
		return *this;
	}

	inline const Volume operator/=(Volume& v)
	{
		this->volume /= v.c_float();
		if (this->volume < 0.0f)
			this->volume = 0.0f;
		return *this;
	}

	inline bool operator< (const float& f)
	{
		return (this->volume < f);
	}

	inline bool operator> (const float& f)
	{
		return (this->volume > f);
	}

	inline bool operator<= (const float& f)
	{
		return (this->volume <= f);
	}

	inline bool operator>= (const float& f)
	{
		return (this->volume >= f);
	}

	inline bool operator== (const float& f)
	{
		return (this->volume == f);
	}

#pragma endregion

	float _float() { return this->volume; }
	const float c_float() { return this->volume; }
private:
	float volume;
};