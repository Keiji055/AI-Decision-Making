#pragma once

#include "Vector2.hpp"

namespace CommonUtilities
{
	template <class T>
	class AABB2D
	{
	public:
		// Default constructor: there is no AABB, both min and max points are the zero vector.
		AABB2D();

		// Copy constructor.
		AABB2D(const AABB2D<T>& aAABB2D);

		// Constructor taking the positions of the minimum and maximum corners.
		AABB2D(const Vector2<T>& aMin, const Vector2<T>& aMax);

		// Init the AABB with the positions of the minimum and maximum corners, same as
		// the constructor above.
		void InitWithMinAndMax(const Vector2<T>& aMin, const Vector2<T>& aMax);

		Vector2<T> GetMin() const;
		Vector2<T> GetMax() const;

		// Returns whether a point is inside the AABB: it is inside when the point is on one of the AABB's sides or inside of the AABB.
		bool IsInside(const Vector2<T>& aPosition) const;

	private:
		union
		{
			Vector2<T> min;
			Vector2<T> myMin;
		};
		union
		{
			Vector2<T> max;
			Vector2<T> myMax;
		};

	};

	typedef AABB2D<float> AABB2Df;
	typedef AABB2D<double> AABB2Dd;

	template<class T>
	inline AABB2D<T>::AABB2D()
	{
		min = Vector2<T>();
		max = Vector2<T>();
	}

	template<class T>
	inline AABB2D<T>::AABB2D(const AABB2D<T>& aAABB2D)
	{
		min = aAABB2D.min;
		max = aAABB2D.max;
	}

	template<class T>
	inline AABB2D<T>::AABB2D(const Vector2<T>& aMin, const Vector2<T>& aMax)
	{
		min = aMin;
		max = aMax;
	}

	template<class T>
	inline void AABB2D<T>::InitWithMinAndMax(const Vector2<T>& aMin, const Vector2<T>& aMax)
	{
		min = aMin;
		max = aMax;
	}

	template<class T>
	inline Vector2<T> AABB2D<T>::GetMin() const
	{
		return min;
	}

	template<class T>
	inline Vector2<T> AABB2D<T>::GetMax() const
	{
		return max;
	}

	template<class T>
	inline bool AABB2D<T>::IsInside(const Vector2<T>& aPosition) const
	{
		return aPosition.x >= min.x && aPosition.y >= min.y && aPosition.x <= max.x && aPosition.y <= max.y;
	}
}
