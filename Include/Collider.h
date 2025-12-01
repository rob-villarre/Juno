#ifndef COLLIDER_H
#define COLLIDER_H

#include "Component.h"
#include "IEntity.h"
#include "raylib-cpp.hpp"

class CircleCollider;
class TriangleCollider;

class Collider : public Component
{
public:
    ~Collider() override = default;
    explicit Collider(const raylib::Vector2 offset) : m_Offset(offset) {};
    [[nodiscard]] virtual bool CheckCollision(const Collider& other) const = 0;
    [[nodiscard]] virtual bool CheckCollision(const CircleCollider& other) const = 0;
    [[nodiscard]] virtual bool CheckCollision(const TriangleCollider& other) const = 0;
    raylib::Vector2 GetOffset() const { return m_Offset; }

protected:
    raylib::Vector2 m_Offset;
};

class CircleCollider final : public Collider
{
public:
    explicit CircleCollider(const raylib::Vector2 offset, const float radius) : Collider(offset),
        m_Radius(radius)
    {
    };

    [[nodiscard]] bool CheckCollision(const Collider& other) const override
    {
        return other.CheckCollision(*this);
    };

    [[nodiscard]] bool CheckCollision(const CircleCollider& other) const override
    {
        return CheckCollisionCircles(
        GetOwner()->GetPosition() + m_Offset, m_Radius,
        other.GetOwner()->GetPosition() + other.GetOffset(), other.GetRadius()
        );
    }

    [[nodiscard]] bool CheckCollision(const TriangleCollider& other) const override
    {
        return false;
    }

    [[nodiscard]] float GetRadius() const { return m_Radius; }

private:
    float m_Radius;
};

class TriangleCollider final : public Collider
{
public:
    explicit TriangleCollider(
        const raylib::Vector2 offset,
        const raylib::Vector2 p1, const raylib::Vector2 p2, const raylib::Vector2 p3)
    : Collider(offset), m_P1(p1), m_P2(p2), m_P3(p3) {};

    [[nodiscard]] bool CheckCollision(const Collider& other) const override
    {
        return other.CheckCollision(*this);
    };

    bool CheckCollision(const CircleCollider& other) const override
    {
        auto [wp1, wp2, wp3] = GetWorldPoints();

        if (CheckCollisionPointTriangle(other.GetOwner()->GetPosition(), wp1, wp2, wp3)) {
            return true;
        }

        return CheckCollisionCircleLine(other.GetOwner()->GetPosition() + other.GetOffset(), other.GetRadius(), wp1, wp2) ||
               CheckCollisionCircleLine(other.GetOwner()->GetPosition() + other.GetOffset(), other.GetRadius(), wp2, wp3) ||
               CheckCollisionCircleLine(other.GetOwner()->GetPosition() + other.GetOffset(), other.GetRadius(), wp3, wp1);
    };

    bool CheckCollision(const TriangleCollider& other) const override
    {
        return false;
    }

    // Get triangle points in world space (with rotation and position applied)
    [[nodiscard]] std::tuple<raylib::Vector2, raylib::Vector2, raylib::Vector2> GetWorldPoints() const
    {
        raylib::Vector2 entityPos = GetOwner()->GetPosition() + m_Offset;
        float heading = GetOwner()->GetHeading();

        auto rotatePoint = [](const raylib::Vector2& point, float angle) -> raylib::Vector2 {
            float rad = angle * DEG2RAD;
            float cosAngle = cos(rad);
            float sinAngle = sin(rad);
            return {
                point.x * cosAngle - point.y * sinAngle,
                point.x * sinAngle + point.y * cosAngle
            };
        };

        raylib::Vector2 wp1 = entityPos + rotatePoint(m_P1, heading);
        raylib::Vector2 wp2 = entityPos + rotatePoint(m_P2, heading);
        raylib::Vector2 wp3 = entityPos + rotatePoint(m_P3, heading);

        return {wp1, wp2, wp3};
    }

private:
    raylib::Vector2 m_P1, m_P2, m_P3; // Local space points (relative to entity)
};
#endif //COLLIDER_H