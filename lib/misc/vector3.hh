#pragma once

namespace vector
{
class Vector3
{
  public:
      /* Constructor */
      Vector3(float x, float y, float z);

      /* getters */
      float x_get() const;
      float y_get() const;
      float z_get() const;

      /* setters */
      void vector_set(float x, float y, float z);

      /* operators */
      Vector3 operator+(const Vector3 other) const;

      Vector3 operator-(const Vector3 other) const;

      Vector3 operator*(const float coeff) const;

    private:
      /* Atributes */
      float x_;
      float y_;
      float z_;
  };
}