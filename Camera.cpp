#include "Camera.h"
#include <random>

Camera::Camera(sf::RenderWindow &window, float worldWidth, float worldHeight)
    : m_window(window), m_worldWidth(worldWidth), m_worldHeight(worldHeight), m_currentPosition(worldWidth / 2.f, worldHeight / 2.f), m_targetPosition(worldWidth / 2.f, worldHeight / 2.f), m_softBounds({0.f, 0.f}, {worldWidth, worldHeight})
{

    // Начальный вид
    sf::Vector2u windowSize = window.getSize();
    m_view.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    m_view.setCenter(m_currentPosition);
}

void Camera::update(float deltaTime, const sf::Vector2f &targetPosition,
                    const sf::Vector2f &targetVelocity)
{
    // 1. Вычисляем look-ahead смещение на основе скорости
    sf::Vector2f desiredLookAhead = targetVelocity * m_lookAheadFactor;

    // Ограничиваем максимальное смещение
    float lookAheadLength = std::sqrt(desiredLookAhead.x * desiredLookAhead.x +
                                      desiredLookAhead.y * desiredLookAhead.y);
    if (lookAheadLength > m_lookAheadMax)
    {
        desiredLookAhead = desiredLookAhead / lookAheadLength * m_lookAheadMax;
    }

    // Плавно интерполируем look-ahead
    m_currentLookAhead += (desiredLookAhead - m_currentLookAhead) *
                          std::min(m_followSpeed * 0.7f * deltaTime, 1.f);

    sf::Vector2f targetWithLookAhead = targetPosition + m_currentLookAhead;
    sf::Vector2f delta = targetWithLookAhead - m_currentPosition;
    // 3. Применяем dead zone
    sf::Vector2f deadZoneHalf = m_deadZoneSize / 2.f;

    if (m_useSoftDeadZone)
    {
        // Мягкая dead zone: плавное начало движения
        sf::Vector2f pushForce(0.f, 0.f);

        // Вычисляем насколько цель вышла за пределы dead zone с учетом смещения
        float leftBound = -deadZoneHalf.x + m_deadZoneOffset.x;
        float rightBound = deadZoneHalf.x + m_deadZoneOffset.x;
        float topBound = -deadZoneHalf.y + m_deadZoneOffset.y;
        float bottomBound = deadZoneHalf.y + m_deadZoneOffset.y;

        // Проверяем выход за границы по X
        if (delta.x < leftBound)
        {
            pushForce.x = delta.x - leftBound;
        }
        else if (delta.x > rightBound)
        {
            pushForce.x = delta.x - rightBound;
        }

        // Проверяем выход за границы по Y
        if (delta.y < topBound)
        {
            pushForce.y = delta.y - topBound;
        }
        else if (delta.y > bottomBound)
        {
            pushForce.y = delta.y - bottomBound;
        }

        // Масштабируем силу с учетом мягкости
        pushForce *= m_deadZoneSoftness;

        // Применяем смещение
        m_targetPosition = m_currentPosition + pushForce;
    }
    else
    {
        // Жесткая dead zone: камера движется только при полном выходе за пределы
        sf::Vector2f deadZoneOffset = m_deadZoneOffset;

        // Проверяем X
        if (std::abs(delta.x - deadZoneOffset.x) > deadZoneHalf.x)
        {
            float signX = (delta.x - deadZoneOffset.x) > 0 ? 1.f : -1.f;
            m_targetPosition.x = targetWithLookAhead.x - signX * deadZoneHalf.x - deadZoneOffset.x;
        }
        else
        {
            m_targetPosition.x = m_currentPosition.x;
        }

        // Проверяем Y
        if (std::abs(delta.y - deadZoneOffset.y) > deadZoneHalf.y)
        {
            float signY = (delta.y - deadZoneOffset.y) > 0 ? 1.f : -1.f;
            m_targetPosition.y = targetWithLookAhead.y - signY * deadZoneHalf.y - deadZoneOffset.y;
        }
        else
        {
            m_targetPosition.y = m_currentPosition.y;
        }
    }

    // 3. Применяем мягкие границы (как в Hades)
    sf::Vector2u windowSize = m_window.getSize();
    float halfWidth = m_view.getSize().x / 2.f / m_currentZoom;
    float halfHeight = m_view.getSize().y / 2.f / m_currentZoom;

    // Вычисляем допустимые границы с учетом мягкой зоны
    float minX = m_softBounds.position.x - m_boundarySoftness + halfWidth;
    float maxX = m_softBounds.position.x + m_softBounds.size.x + m_boundarySoftness - halfWidth;
    float minY = m_softBounds.position.y - m_boundarySoftness + halfHeight;
    float maxY = m_softBounds.position.y + m_softBounds.size.y + m_boundarySoftness - halfHeight;

    // Применяем мягкое ограничение
    if (m_targetPosition.x < minX)
    {
        float diff = minX - m_targetPosition.x;
        m_targetPosition.x += diff * (1.f - std::exp(-diff / m_boundarySoftness));
    }
    else if (m_targetPosition.x > maxX)
    {
        float diff = m_targetPosition.x - maxX;
        m_targetPosition.x -= diff * (1.f - std::exp(-diff / m_boundarySoftness));
    }

    if (m_targetPosition.y < minY)
    {
        float diff = minY - m_targetPosition.y;
        m_targetPosition.y += diff * (1.f - std::exp(-diff / m_boundarySoftness));
    }
    else if (m_targetPosition.y > maxY)
    {
        float diff = m_targetPosition.y - maxY;
        m_targetPosition.y -= diff * (1.f - std::exp(-diff / m_boundarySoftness));
    }

    // 4. Плавное следование
    float smoothFactor = 1.f - std::exp(-m_followSpeed * deltaTime);
    m_currentPosition += (m_targetPosition - m_currentPosition); //* smoothFactor;

    // 5. Обработка тряски
    if (m_shakeTimer > 0.f)
    {
        m_shakeTimer -= deltaTime;

        // Используем шум Перлина или случайные значения
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(-1.f, 1.f);

        float decay = m_shakeTimer / m_shakeDuration;
        m_shakeOffset.x = dis(gen) * m_shakeIntensity * decay;
        m_shakeOffset.y = dis(gen) * m_shakeIntensity * decay;
    }
    else
    {
        m_shakeOffset = sf::Vector2f(0.f, 0.f);
    }

    // 6. Плавный зум
    if (std::abs(m_currentZoom - m_targetZoom) > 0.001f)
    {
        m_currentZoom += (m_targetZoom - m_currentZoom) * m_zoomSpeed * deltaTime;
    }
    else
    {
        m_currentZoom = m_targetZoom;
    }

    // 7. Применяем все к виду
    m_view.setCenter(m_currentPosition + m_shakeOffset);
    m_view.setSize(sf::Vector2f(windowSize.x, windowSize.y) / m_currentZoom);
}

void Camera::setView(sf::RenderWindow &window)
{
    window.setView(m_view);
}

void Camera::setViewDefault(sf::RenderWindow &window)
{
    m_view.setCenter(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
    m_view.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    window.setView(m_view);
}

void Camera::shake(float intensity, float duration)
{
    m_shakeIntensity = intensity;
    m_shakeDuration = duration;
    m_shakeTimer = duration;
}

void Camera::setZoom(float zoom, float duration)
{
    m_targetZoom = zoom;
    if (duration <= 0.f)
    {
        m_currentZoom = zoom;
    }
}

sf::Vector2f Camera::screenToWorld(const sf::Vector2i &screenPos) const
{
    return m_window.mapPixelToCoords(screenPos, m_view);
}

sf::Vector2i Camera::worldToScreen(const sf::Vector2f &worldPos) const
{
    return m_window.mapCoordsToPixel(worldPos, m_view);
}