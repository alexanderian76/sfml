#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include "PlayerController.h"
#include "./Enemy/EnemySpawner.h"

#include "./Menu/Menu.h"
#include "./Menu/Screen.h"
#include "./Menu/MainMenu.h"
#include "./Menu/GameScreen.h"

#include "GlobalObjects.h"
#include "Camera.h"
#include "Cutscene/Cutscene.h"
#include "utils/utils.h"

// g++ main.cpp -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window -lsfml-audio
using namespace sf;

int main()
{

    Font font;
    if (!font.openFromFile(getResourcePath() + "arialmt.ttf"))
    {
        // В случае ошибки можно использовать встроенный шрифт
        // или продолжить без него (текст не будет отображаться)
        throw std::runtime_error("Failed to load font");
    }

    SoundBuffer buffer;
    buffer.loadFromFile(getResourcePath() + "test.wav");
    //  Sound sound(buffer);
    // sound.setBuffer(buffer);
    //  sound.setVolume(50);
    //  sound.play();
    auto video = sf::VideoMode::getDesktopMode();
    GlobalObjects::settings->resolution.y = video.size.y;
    GlobalObjects::settings->resolution.x = video.size.x;
    // sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    // std::cout << sf::VideoMode::getFullscreenModes().size() << std::endl;
    RenderWindow appWindow(video, "Bubble sort", State::Fullscreen);

    // Создаем камеру для мира 4000x4000
    GlobalObjects::camera = new Camera(appWindow, 4000.f, 4000.f);

    // Настройка камеры как в Hades
    GlobalObjects::camera->setFollowSpeed(4.5f);     // Скорость следования
    GlobalObjects::camera->setLookAheadFactor(0.4f); // Фактор упреждения
    GlobalObjects::camera->setLookAheadMax(180.f);   // Максимальное упреждение

    // Устанавливаем мягкие границы (можно задать границы комнаты)
    GlobalObjects::camera->setSoftBounds(sf::FloatRect({200.f, 200.f}, {3600.f, 3600.f}));

    appWindow.setMouseCursorVisible(false);
    // ScreenManager screenManager;
    std::cout << "HELLO" << std::endl;
    //  std::unique_ptr<MainMenuScreen> mainMenuScreen = make_unique<MainMenuScreen>();
    GlobalObjects::screenManager->pushScreen(make_unique<MainMenuScreen>());

    int j = 0;
    // Event appEvent;
    Texture fondot;
    fondot.loadFromFile(getResourcePath() + "696.jpg");

    Sprite fondo(fondot);

    RectangleShape reactange(Vector2f(2, 178));
    reactange.setFillColor(Color(235, 149, 13));
    //  PlayerController player;
    Clock clock;
    ObjectController obj(500, 600);
    ObjectController obj1(0, 600);
    ObjectController obj2(200, 500);
    obj.check = 1;

  /*  GlobalObjects::objects.push_back(obj);
    GlobalObjects::objects.push_back(obj1);
    GlobalObjects::objects.push_back(obj2);

    ObjectController::wall(200, 400, 10, false, GlobalObjects::objects);
    ObjectController::wall(200, 200, 30, true, GlobalObjects::objects);
    ObjectController::wall(200, 200, 30, false, GlobalObjects::objects);
    ObjectController::wall(50, 200, 30, true, GlobalObjects::objects);
*/
    // GlobalObjects::objects.insert(GlobalObjects::objects.end(), std::make_move_iterator(wall.begin()), std::make_move_iterator(wall.end()));
    //  wall.clear();
    srand(time(NULL));
    appWindow.setFramerateLimit(60);
    appWindow.clear(Color::Black);

    // appWindow.draw(fondo);

    for (int i = 0; i < GlobalObjects::objects.size(); i++)
    {
        //    appWindow.draw(GlobalObjects::objects[i].drawObject());
    }
    clock.start();


    // Загрузка текстуры врага (замените на свой файл)
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile(getResourcePath() + "01_idle/idle_1.png"))
    {
        std::cerr << "Failed to load enemy texture!" << std::endl;
        return -1;
    }

    appWindow.display();

    while (appWindow.isOpen())
    {

        //   appWindow.draw(fondo); // 2. РИСУЕМ фон
        Time deltaTime = clock.restart();
        GlobalObjects::screenManager->update(deltaTime);

        appWindow.clear(Color::Black); // 1. ОЧИЩАЕМ экран
        if (appWindow.getSize() != Vector2u(GlobalObjects::settings->resolution.x, GlobalObjects::settings->resolution.y))
            appWindow.setSize({GlobalObjects::settings->resolution.x, GlobalObjects::settings->resolution.y});
        GlobalObjects::screenManager->draw(appWindow);
        //  std::cout << "HELLO" << std::endl;
        appWindow.display();

        while (const auto event = appWindow.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                appWindow.close();
            }

            // Передаем события в менеджер экранов
            GlobalObjects::screenManager->handleInput(*event, appWindow);

            // Специальная обработка для меню
            if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::Escape)
                {
                    if (!GlobalObjects::screenManager->isEmpty())
                    {
                        GlobalObjects::camera->setZoom(1.f, 0.f);

                        GlobalObjects::camera->setViewDefault(appWindow);
                        int screenType = GlobalObjects::screenManager->currentScreenType();
                        int screenId = GlobalObjects::screenManager->currentScreenId();
                        if (screenId == 1)
                            GlobalObjects::screenManager->removeScreen(screenId);
                        if (screenType == 1)
                        {
                            //      GlobalObjects::screenManager->pushScreen(make_unique<GameScreen>());
                        }
                        else
                        {
                            GlobalObjects::screenManager->pushScreen(make_unique<MainMenuScreen>());
                        }
                    }
                }
                else if (keyPressed->code == sf::Keyboard::Key::Z)
                {
                    GlobalObjects::screenManager->pushScreen(make_unique<Cutscene>("TestName", font, 36));
                }
            }
        }

    }

    ////////////////////////////////////////////// ////////////////////////////////////////////// //////////////////////////////////////////////
    // delete sprite;

    GlobalObjects::objects.clear();
    return 0;
}