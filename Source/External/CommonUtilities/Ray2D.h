#pragma once

#include "Vector2.hpp"

namespace CommonUtilities
{
	template <class T>
	class Ray2D
	{
	public:
		// Default constructor: there is no ray, the origin and direction are the zero vector.
		Ray2D() = default;

		// Copy constructor.
		Ray2D(const Ray2D<T>& aRay) = default;

		// Constructor that takes two points that define the ray, the direction aPoint - aOrigin and the origin is aOrigin.
		Ray2D(const Vector2<T>& aOrigin, const Vector2<T>& aPoint);

		// Init the ray with two points, the same as the constructor above.
		void InitWith2Points(const Vector2<T>& aOrigin, const Vector2<T>& aPoint);

		// Init the ray with an origin and a direction.
		void InitWithOriginAndDirection(const Vector2<T>& aOrigin, const Vector2<T>& aDirection);

		Vector2<T> GetDirection() const;
		Vector2<T> GetOrigin() const;

		void SetDirection(const Vector2<T>& aDirection);
		void SetOrigin(const Vector2<T>& aOrigin);

	private:
		Vector2<T> myOrigin;
		Vector2<T> myDirection;
	};

	typedef Ray2D<float> Ray2Df;
	typedef Ray2D<double> Ray2Dd;

	// Constructor that initializes with two points (origin and point the ray points to)
	template<class T>
	inline Ray2D<T>::Ray2D(const Vector2<T>& aOrigin, const Vector2<T>& aPoint)
	{
		myOrigin = aOrigin;
		myDirection = Vector2<T>(aPoint - aOrigin).GetNormalized();
	}

	// Initializes the ray with two points
	template<class T>
	inline void Ray2D<T>::InitWith2Points(const Vector2<T>& aOrigin, const Vector2<T>& aPoint)
	{
		myOrigin = aOrigin;
		myDirection = Vector2<T>(aPoint - aOrigin).GetNormalized();
	}

	// Initializes the ray with an origin and direction
	template<class T>
	inline void Ray2D<T>::InitWithOriginAndDirection(const Vector2<T>& aOrigin, const Vector2<T>& aDirection)
	{
		myOrigin = aOrigin;
		myDirection = aDirection.GetNormalized();
	}

	// Getters
	template<class T>
	inline Vector2<T> Ray2D<T>::GetDirection() const
	{
		return myDirection;
	}

	template<class T>
	inline Vector2<T> Ray2D<T>::GetOrigin() const
	{
		return myOrigin;
	}

	// Setters
	template<class T>
	inline void Ray2D<T>::SetDirection(const Vector2<T>& aDirection)
	{
		myDirection = aDirection.GetNormalized();
	}

	template<class T>
	inline void Ray2D<T>::SetOrigin(const Vector2<T>& aOrigin)
	{
		myOrigin = aOrigin;
	}
}
