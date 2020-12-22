#pragma once
// 0.0~1.0f ������ float ���� ǥ���ϱ� ���� Ŭ����
// float  �� ȣȯ���� ���Ͽ� ���۷����� ������ �߰�


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

	// ���� ������ ���۷�����
	inline const Volume operator++(const int n)
	{
		const Volume tmep = *this;
		this->volume += 0.1f;
		if (this->volume > 1.0f)
			this->volume = 1.0f;
		return tmep;
	}

	// ���� ������  ���۷�����
	inline Volume& operator++()
	{

		this->volume += 0.1f;
		if (this->volume > 1.0f)
			this->volume = 1.0f;
		return *this;
	}

	// ���� ������ ���۷�����
	inline const Volume operator--(const int n)
	{
		const Volume tmep = *this;
		this->volume -= 0.1f;
		if (this->volume > 1.0f)
			this->volume = 1.0f;
		return tmep;
	}

	// ���� ������  ���۷�����
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