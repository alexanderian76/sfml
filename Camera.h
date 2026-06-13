#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Camera
{
public:
    Camera(sf::RenderWindow &window, float worldWidth, float worldHeight);

    void update(float deltaTime, const sf::Vector2f &targetPosition,
                const sf::Vector2f &targetVelocity = sf::Vector2f(0.f, 0.f));

    void setView(sf::RenderWindow &window);

    // Эффекты
    void shake(float intensity, float duration);
    void setZoom(float zoom, float duration = 0.f);

    // Настройки камеры
    void setFollowSpeed(float speed) { m_followSpeed = speed; }
    void setLookAheadFactor(float factor) { m_lookAheadFactor = factor; }
    void setLookAheadMax(float max) { m_lookAheadMax = max; }
    void setSoftBounds(const sf::FloatRect &bounds) { m_softBounds = bounds; }

    void setDeadZone(const sf::Vector2f &size) { m_deadZoneSize = size; }
    void setDeadZone(const sf::Vector2f &size, const sf::Vector2f &offset)
    {
        m_deadZoneSize = size;
        m_deadZoneOffset = offset;
    }
    void setSoftDeadZone(bool soft) { m_useSoftDeadZone = soft; }
    void setDeadZoneSoftness(float softness) { m_deadZoneSoftness = softness; }

    sf::FloatRect getDeadZoneRect() const;

    // Преобразование координат
    sf::Vector2f screenToWorld(const sf::Vector2i &screenPos) const;
    sf::Vector2i worldToScreen(const sf::Vector2f &worldPos) const;

    sf::View getView() const { return m_view; }
    sf::Vector2f getPosition() const { return m_view.getCenter(); }

    void setViewDefault(sf::RenderWindow &window);

private:
    sf::RenderWindow &m_window;
    sf::View m_view;

    // Размеры мира
    float m_worldWidth;
    float m_worldHeight;

    // Следование
    float m_followSpeed = 5.f;
    sf::Vector2f m_currentPosition;
    sf::Vector2f m_targetPosition;

    // Look-ahead (упреждение)
    float m_lookAheadFactor = -0.03f;
    float m_lookAheadMax = 150.f;
    sf::Vector2f m_lookAheadOffset;
    sf::Vector2f m_currentLookAhead;

    // Тряска
    float m_shakeIntensity = 0.f;
    float m_shakeDuration = 0.f;
    float m_shakeTimer = 0.f;
    sf::Vector2f m_shakeOffset;

    // Зум
    float m_currentZoom = 1.f;
    float m_targetZoom = 1.f;
    float m_zoomSpeed = 3.f;

    // Границы
    sf::FloatRect m_softBounds;
    float m_boundarySoftness = 200.f; // Зона смягчения

    // Dead zone (зона нечувствительности)
    sf::Vector2f m_deadZoneSize = sf::Vector2f(300.f, 200.f); // Размер зоны
    sf::Vector2f m_deadZoneOffset = sf::Vector2f(0.f, -30.f); // Смещение (в Hades чуть ниже центра)
    bool m_useSoftDeadZone = true;                            // Мягкая или жесткая зона
    float m_deadZoneSoftness = 0.5f;                          // Мягкость перехода
};
