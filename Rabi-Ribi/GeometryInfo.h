#pragma once
// ������ ���� ����ü �ش� ����


enum class GeometryKinds
{
	None,
	Triangle,
	Square,
	// ��ٸ���
	Trapezoid,

};

struct GeometryInfo
{
	GeometryKinds geometrykind;
	float width;
	float height;
	// ��ٸ��ø� ���
	float _width;
	// ��ٸ��ø� ���
	float _height;
	// �����̼�
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

