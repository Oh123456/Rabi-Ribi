#pragma once
// 기하학 정보 구조체 해더 파일


enum class GeometryKinds
{
	None,
	Triangle,
	Square,
	// 사다리꼴
	Trapezoid,

};

struct GeometryInfo
{
	GeometryKinds geometrykind;
	float width;
	float height;
	// 사다리꼴만 사용
	float _width;
	// 사다리꼴만 사용
	float _height;
	// 로테이션
	float rotation;
	bool isRevers;

	inline void ReSet()
	{
		width = 0.0f;
		height = 0.0f;
		_width = 0.0f;
		_height = 0.0f;
		rotation = 0.0f;
		isRevers = false;
		geometrykind = GeometryKinds::None;
	}

	bool operator == (const GeometryInfo& geometry)
	{
		if (geometry.geometrykind != this->geometrykind)
			return false;
		if (geometry.isRevers != this->isRevers)
			return false;
		switch (geometrykind)
		{
		case  GeometryKinds::None:
			return false;
			break;
		case GeometryKinds::Square:
		case GeometryKinds::Triangle:
			if (this->width != geometry.width)
				return false;
			if (this->height != geometry.height)
				return false;
			break;
		case GeometryKinds::Trapezoid:
			if (this->width != geometry.width)
				return false;
			if (this->height != geometry.height)
				return false;
			if (this->_width != geometry._width)
				return false;
			if (this->_height != geometry._height)
				return false;
		default:
			return false;
			break;
		}
		return true;
	}

	bool operator != (const GeometryInfo& geometry)
	{
		if (*this == geometry)
			return false;
		return true;
	}

};

