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

// g++ main.cpp -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window -lsfml-audio
using namespace sf;

int main()
{

    Font font;
    if (!font.openFromFile("arialmt.ttf"))
    {
        // В случае ошибки можно использовать встроенный шрифт
        // или продолжить без него (текст не будет отображаться)
        throw std::runtime_error("Failed to load font");
    }

    SoundBuffer buffer;
    buffer.loadFromFile("test.wav");
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
    fondot.loadFromFile("696.jpg");

    Sprite fondo(fondot);

    RectangleShape reactange(Vector2f(2, 178));
    reactange.setFillColor(Color(235, 149, 13));
    //  PlayerController player;
    Clock clock;
    ObjectController obj(500, 600);
    ObjectController obj1(0, 600);
    ObjectController obj2(200, 500);
    obj.check = 1;

    GlobalObjects::objects.push_back(obj);
    GlobalObjects::objects.push_back(obj1);
    GlobalObjects::objects.push_back(obj2);

    ObjectController::wall(200, 400, 10, false, GlobalObjects::objects);
    ObjectController::wall(200, 200, 30, true, GlobalObjects::objects);
    ObjectController::wall(200, 200, 30, false, GlobalObjects::objects);
    ObjectController::wall(50, 200, 30, true, GlobalObjects::objects);

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

    //  appWindow.draw(ff);
    Texture texture;
    texture.loadFromFile("./01_idle/idle_1.png");
    Texture t("./01_idle/idle_1.png");
    //  Sprite *sprite = new Sprite(t);

    // sprite->setOrigin({sprite->getLocalBounds().size.x / 2, sprite->getLocalBounds().size.y / 2});
    // sprite->setPosition({250, 150});
    // Загрузка текстуры врага (замените на свой файл)
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("./01_idle/idle_1.png"))
    {
        std::cerr << "Failed to load enemy texture!" << std::endl;
        return -1;
    }

    // Создание спавнера врагов
    //  EnemySpawner spawner(enemyTexture);
    //  spawner.setSpawnRate(1.5f); // Спавн каждые 1.5 секунды
    //  spawner.setMaxEnemies(15);

    //  appWindow.draw(*sprite);
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
                   // GlobalObjects::camera->setViewDefault(appWindow);
                    GlobalObjects::screenManager->pushScreen(make_unique<Cutscene>("TestName", font, 36));
                }
            }
            //    std::cout << "EVENT END" << std::endl;
        }

        /*    // 3. РИСУЕМ все объекты
            for (int i = 0; i < GlobalObjects::objects.size(); i++)
            {
                appWindow.draw(GlobalObjects::objects[i].drawObject());
            }

            // Обновление спавнера
            spawner.update(clock.getElapsedTime().asSeconds(), *sprite);

            spawner.draw(appWindow);

            // Проверка коллизий с игроком
            for (auto &enemy : spawner.getEnemies())
            {
                if (FloatRect(enemy->getPosition(), {enemy->xPadding, enemy->yPadding}).findIntersection(FloatRect({sprite->getPosition().x + player.direction * (player.xPadding / (player.direction > 0 ? 1 : 2)), sprite->getPosition().y}, {1, player.yPadding / 2})))
                {
                    // Здесь нужно обрабатывать урон игроку
                    // Например: player.takeDamage(enemy->damage);
                    if (player.isAttack)
                    {
                        enemy->takeDamage(10);
                    }
                }
            }
          //  cout << "WALL" << endl;
          //  cout << wall.size() << endl;
            int collisionsCount = 0;

            player.DrawPlayer(clock, sprite, appWindow);

            appWindow.display();

            if (sound.getStatus() == Sound::Status::Stopped)
            {
                sound.play();
            }
            while (const std::optional appEvent = appWindow.pollEvent())
            {

                if (appEvent->is<Event::Closed>())
                    appWindow.close();

                // window closed
                if (appEvent->is<sf::Event::Closed>())
                {
                    appWindow.close();
                }
                else if (appEvent->is<Event::KeyReleased>())
                {
                    if (player.getMotion() == 3 || player.getMotion() == 2 || player.getMotion() == 4 || player.getMotion() == 5)
                    {
                        clock.restart();
                        player.setMotion(0);
                    }
                }
                // key pressed
                else if (appEvent->is<sf::Event::KeyPressed>())
                {

                    const auto *keyPressed = appEvent->getIf<sf::Event::KeyPressed>();

                      std::cout << (int)keyPressed->scancode << std::endl;

                    if (keyPressed->scancode == Keyboard::Scancode::B && player.getMotion() != 1)
                    {
                        clock.restart();
                        player.setMotion(1);
                    }

                    if (keyPressed->scancode == Keyboard::Scancode::D && player.getMotion() != 2)
                    {
                        player.setMotion(2);
                    }

                    if (keyPressed->scancode == Keyboard::Scancode::A && player.getMotion() != 3)
                    {
                        player.setMotion(3);
                    }

                    if (keyPressed->scancode == Keyboard::Scancode::W && player.getMotion() != 4)
                    {
                        player.setMotion(4);
                    }

                    if (keyPressed->scancode == Keyboard::Scancode::S && player.getMotion() != 5)
                    {
                        player.setMotion(5);
                    }
                    // std::cout << appEvent << std::endl;
                }
                // we don't process other types of events
            }*/
    }

    ////////////////////////////////////////////// ////////////////////////////////////////////// //////////////////////////////////////////////
    // delete sprite;

    GlobalObjects::objects.clear();
    return 0;
}