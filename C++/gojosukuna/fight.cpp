#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <optional>
#include <cstdlib>
#include <cstdint>
#include <algorithm>

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 700;
const float GROUND_HEIGHT = 600.0f;
const float GRAVITY = 0.9f;
const float JUMP_FORCE = -16.0f;
const float MOVE_ACCELERATION = 1.5f;
const float MAX_SPEED = 9.0f;
const float FRICTION = 0.85f;
const float DASH_FORCE = 25.0f;

const float MAX_ENERGY = 100.0f;
const float ENERGY_REGEN = 0.3f;
const float COST_BASIC = 15.0f;
const float COST_SPECIAL = 50.0f;

enum AttackType
{
    BASIC,
    SPECIAL
};

class Particle
{
public:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    float lifetime;

    Particle(float x, float y, sf::Color color)
    {
        shape.setPosition({x, y});
        shape.setSize({4.0f, 4.0f});
        shape.setFillColor(color);
        float angle = (rand() % 360) * 3.14f / 180.0f;
        float speed = (rand() % 12 + 2.0f);
        velocity = {std::cos(angle) * speed, std::sin(angle) * speed};
        lifetime = 1.0f;
    }

    bool update()
    {
        velocity.y += 0.5f;
        shape.move(velocity);
        lifetime -= 0.05f;
        sf::Color c = shape.getFillColor();
        c.a = static_cast<std::uint8_t>(255 * lifetime);
        shape.setFillColor(c);
        return lifetime > 0;
    }
};

class Projectile
{
public:
    sf::RectangleShape shapeRect;
    sf::CircleShape shapeOrb;
    sf::Vector2f velocity;
    bool active;
    std::string owner;
    AttackType type;
    int damage;

    Projectile(float x, float y, float dir, std::string who, AttackType t)
    {
        owner = who;
        type = t;
        active = true;

        if (who == "Gojo")
        {
            if (type == BASIC)
            {
                shapeOrb.setRadius(15.0f);
                shapeOrb.setOrigin({15.0f, 15.0f});
                shapeOrb.setFillColor(sf::Color::Cyan);
                velocity = {dir * 18.0f, 0};
                damage = 8;
            }
            else
            {
                shapeOrb.setRadius(30.0f);
                shapeOrb.setOrigin({30.0f, 30.0f});
                shapeOrb.setFillColor(sf::Color::Red);
                velocity = {dir * 12.0f, 0};
                damage = 25;
            }
            shapeOrb.setPosition({x, y});
            shapeRect.setSize({0, 0});
        }
        else
        {
            if (type == BASIC)
            {
                shapeRect.setSize({10.0f, 60.0f});
                shapeRect.setOrigin({5.0f, 30.0f});
                shapeRect.setFillColor(sf::Color::Red);
                velocity = {dir * 11.0f, 0};
                damage = 10;
            }
            else
            {
                shapeRect.setSize({60.0f, 20.0f});
                shapeRect.setOrigin({30.0f, 10.0f});
                shapeRect.setFillColor(sf::Color(255, 69, 0));
                velocity = {dir * 16.0f, 0};
                damage = 30;
            }
            shapeRect.setPosition({x, y});
            shapeOrb.setRadius(0);
        }
    }

    void update()
    {
        if (owner == "Gojo")
        {
            shapeOrb.move(velocity);
            if (shapeOrb.getPosition().x < -100 || shapeOrb.getPosition().x > WINDOW_WIDTH + 100)
                active = false;
        }
        else
        {
            shapeRect.move(velocity);
            if (type == BASIC)
                shapeRect.rotate(sf::degrees(10.0f));
            if (shapeRect.getPosition().x < -100 || shapeRect.getPosition().x > WINDOW_WIDTH + 100)
                active = false;
        }
    }

    sf::FloatRect getBounds()
    {
        if (owner == "Gojo")
            return shapeOrb.getGlobalBounds();
        return shapeRect.getGlobalBounds();
    }
};

class Player
{
public:
    sf::RectangleShape hitbox;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f velocity;
    bool isGrounded;
    int hp;
    int maxHp;
    float energy;
    std::string name;
    bool facingRight;

    int jumpCount;
    int maxJumps;

    sf::Clock attackClock;
    sf::Clock dashClock;
    float attackCooldown;
    float dashCooldown;

    Player(float x, float y, std::string imgPath, std::string n, int startHp, bool isAi) : sprite(texture)
    {
        if (!texture.loadFromFile(imgPath))
        {
            hitbox.setFillColor(sf::Color::Magenta);
        }
        else
        {
            sprite.setTexture(texture, true);
            hitbox.setFillColor(sf::Color::Transparent);
        }

        name = n;
        maxHp = startHp;
        hp = maxHp;
        energy = MAX_ENERGY;
        isGrounded = false;
        facingRight = true;
        jumpCount = 0;
        maxJumps = 2;

        attackCooldown = 0.4f;
        dashCooldown = 1.5f;

        hitbox.setSize({70.0f, 120.0f});
        hitbox.setOrigin({35.0f, 60.0f});
        hitbox.setPosition({x, y});

        if (texture.getSize().x > 0)
        {
            float scaleX = 70.0f / static_cast<float>(texture.getSize().x);
            float scaleY = 120.0f / static_cast<float>(texture.getSize().y);
            sprite.setScale({scaleX, scaleY});
            sprite.setOrigin({static_cast<float>(texture.getSize().x) / 2.0f, static_cast<float>(texture.getSize().y) / 2.0f});
        }
        sprite.setPosition(hitbox.getPosition());
    }

    void update(float timeScale = 1.0f)
    {
        if (energy < MAX_ENERGY)
        {
            energy += ENERGY_REGEN * timeScale;
            if (energy > MAX_ENERGY)
                energy = MAX_ENERGY;
        }

        velocity.y += GRAVITY * timeScale;
        if (velocity.y > 20.0f)
            velocity.y = 20.0f;
        hitbox.move(velocity * timeScale);

        if (hitbox.getPosition().y + hitbox.getSize().y / 2 >= GROUND_HEIGHT)
        {
            hitbox.setPosition({hitbox.getPosition().x, GROUND_HEIGHT - hitbox.getSize().y / 2});
            velocity.y = 0;
            isGrounded = true;
            jumpCount = 0;
        }
        else
        {
            isGrounded = false;
        }

        velocity.x *= FRICTION;
        if (std::abs(velocity.x) < 0.1f)
            velocity.x = 0;

        sprite.setPosition(hitbox.getPosition());

        float scaleAbsX = std::abs(sprite.getScale().x);
        if (facingRight)
            sprite.setScale({scaleAbsX, sprite.getScale().y});
        else
            sprite.setScale({-scaleAbsX, sprite.getScale().y});
    }

    void accelerate(float dir)
    {
        velocity.x += dir * MOVE_ACCELERATION;
        if (velocity.x > MAX_SPEED)
            velocity.x = MAX_SPEED;
        if (velocity.x < -MAX_SPEED)
            velocity.x = -MAX_SPEED;
        if (dir > 0)
            facingRight = true;
        if (dir < 0)
            facingRight = false;
    }

    void jump()
    {
        if (isGrounded || jumpCount < maxJumps)
        {
            velocity.y = JUMP_FORCE;
            isGrounded = false;
            jumpCount++;
        }
    }

    void dash()
    {
        if (dashClock.getElapsedTime().asSeconds() > dashCooldown && energy >= 10.0f)
        {
            energy -= 10.0f;
            float dashDir = facingRight ? 1.0f : -1.0f;
            velocity.x = dashDir * DASH_FORCE;
            velocity.y = -5.0f;
            jumpCount = 1;
            dashClock.restart();
        }
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Jujutsu Kaisen: Cursed Energy Update");
    window.setFramerateLimit(60);
    srand(time(NULL));

    sf::Texture bgTexture;
    sf::RectangleShape background(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    if (bgTexture.loadFromFile("/Users/oskarzuk/Desktop/C++/gojosukuna/grafika/tlo.jpg"))
    {
        background.setTexture(&bgTexture);
    }
    else
    {
        background.setFillColor(sf::Color(30, 30, 30));
    }

    sf::RectangleShape domainOverlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    domainOverlay.setFillColor(sf::Color(100, 0, 200, 100));
    bool domainActive = false;
    sf::Clock domainClock;

    Player gojo(200, GROUND_HEIGHT - 100, "/Users/oskarzuk/Desktop/C++/gojosukuna/grafika/gojo.jpg", "Gojo", 200, false);
    Player sukuna(800, GROUND_HEIGHT - 100, "/Users/oskarzuk/Desktop/C++/gojosukuna/grafika/sukuna.jpg", "Sukuna", 400, true);

    std::vector<Projectile> projectiles;
    std::vector<Particle> particles;

    bool spacePressedLastFrame = false;
    bool ePressedLastFrame = false;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (event->is<sf::Event::KeyPressed>())
            {
                const auto *keyEvent = event->getIf<sf::Event::KeyPressed>();
                if (keyEvent)
                {
                    if (keyEvent->code == sf::Keyboard::Key::W)
                        gojo.jump();
                    if (keyEvent->code == sf::Keyboard::Key::F && !domainActive && gojo.energy >= 80.0f)
                    {
                        gojo.energy -= 80.0f;
                        domainActive = true;
                        domainClock.restart();
                    }
                    if (keyEvent->code == sf::Keyboard::Key::LShift)
                        gojo.dash();
                }
            }
        }

        if (domainActive && domainClock.getElapsedTime().asSeconds() > 5.0f)
            domainActive = false;
        float sukunaTimeScale = domainActive ? 0.2f : 1.0f;

        if (gojo.hp > 0)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
                gojo.accelerate(-1.0f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
                gojo.accelerate(1.0f);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
            {
                if (!spacePressedLastFrame && gojo.attackClock.getElapsedTime().asSeconds() > 0.2f)
                {
                    if (gojo.energy >= COST_BASIC)
                    {
                        gojo.energy -= COST_BASIC;
                        float dir = gojo.facingRight ? 1.0f : -1.0f;
                        projectiles.push_back(Projectile(gojo.hitbox.getPosition().x, gojo.hitbox.getPosition().y, dir, "Gojo", BASIC));
                        gojo.attackClock.restart();
                    }
                }
                spacePressedLastFrame = true;
            }
            else
            {
                spacePressedLastFrame = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
            {
                if (!ePressedLastFrame && gojo.attackClock.getElapsedTime().asSeconds() > 0.5f)
                {
                    if (gojo.energy >= COST_SPECIAL)
                    {
                        gojo.energy -= COST_SPECIAL;
                        float dir = gojo.facingRight ? 1.0f : -1.0f;
                        projectiles.push_back(Projectile(gojo.hitbox.getPosition().x, gojo.hitbox.getPosition().y, dir, "Gojo", SPECIAL));
                        gojo.attackClock.restart();
                    }
                }
                ePressedLastFrame = true;
            }
            else
            {
                ePressedLastFrame = false;
            }
        }

        if (sukuna.hp > 0)
        {
            float dx = gojo.hitbox.getPosition().x - sukuna.hitbox.getPosition().x;
            float distance = std::abs(dx);

            if (distance > 550)
                sukuna.accelerate((dx > 0 ? 1.0f : -1.0f));
            else if (distance < 350)
                sukuna.accelerate((dx > 0 ? -1.0f : 1.0f));

            if (dx > 0)
                sukuna.facingRight = true;
            else
                sukuna.facingRight = false;

            if (rand() % 100 < 2 && sukuna.isGrounded)
                sukuna.jump();

            if (distance < 800 && sukuna.attackClock.getElapsedTime().asSeconds() > sukuna.attackCooldown)
            {
                float dir = (dx > 0) ? 1.0f : -1.0f;

                if (sukuna.energy > COST_SPECIAL && (rand() % 100 < 25))
                {
                    sukuna.energy -= COST_SPECIAL;
                    projectiles.push_back(Projectile(sukuna.hitbox.getPosition().x, sukuna.hitbox.getPosition().y, dir, "Sukuna", SPECIAL));
                }
                else if (sukuna.energy > COST_BASIC)
                {
                    sukuna.energy -= COST_BASIC;
                    projectiles.push_back(Projectile(sukuna.hitbox.getPosition().x, sukuna.hitbox.getPosition().y, dir, "Sukuna", BASIC));
                }
                sukuna.attackClock.restart();
            }
        }

        gojo.update(1.0f);
        sukuna.update(sukunaTimeScale);

        for (size_t i = 0; i < projectiles.size(); i++)
        {
            float projSpeed = (projectiles[i].owner == "Sukuna") ? sukunaTimeScale : 1.0f;
            projectiles[i].update();

            bool hit = false;
            Player *target = nullptr;

            if (projectiles[i].owner == "Gojo" && projectiles[i].getBounds().findIntersection(sukuna.hitbox.getGlobalBounds()))
            {
                target = &sukuna;
                hit = true;
            }
            else if (projectiles[i].owner == "Sukuna" && projectiles[i].getBounds().findIntersection(gojo.hitbox.getGlobalBounds()))
            {
                target = &gojo;
                hit = true;
            }

            if (hit && target->hp > 0)
            {
                target->hp -= projectiles[i].damage;

                if (projectiles[i].type == SPECIAL)
                {
                    float pushDir = (projectiles[i].velocity.x > 0) ? 1.0f : -1.0f;
                    target->velocity.x = pushDir * 15.0f;
                    target->velocity.y = -10.0f;
                }

                projectiles[i].active = false;

                sf::Color bloodColor = (target->name == "Gojo") ? sf::Color::Red : sf::Color(100, 0, 0);
                for (int k = 0; k < 20; k++)
                {
                    particles.push_back(Particle(target->hitbox.getPosition().x, target->hitbox.getPosition().y, bloodColor));
                }
            }

            if (!projectiles[i].active)
            {
                projectiles.erase(projectiles.begin() + i);
                i--;
            }
        }

        for (size_t i = 0; i < particles.size(); i++)
        {
            if (!particles[i].update())
            {
                particles.erase(particles.begin() + i);
                i--;
            }
        }

        window.clear();
        window.draw(background);
        if (domainActive)
            window.draw(domainOverlay);
        if (gojo.hp > 0)
            window.draw(gojo.sprite);
        if (sukuna.hp > 0)
            window.draw(sukuna.sprite);

        for (auto &p : projectiles)
        {
            if (p.owner == "Gojo")
                window.draw(p.shapeOrb);
            else
                window.draw(p.shapeRect);
        }
        for (auto &p : particles)
            window.draw(p.shape);

        sf::RectangleShape hpGojoBg({104, 14});
        hpGojoBg.setPosition({50, 50});
        hpGojoBg.setFillColor(sf::Color::Black);
        window.draw(hpGojoBg);
        sf::RectangleShape hpGojo({100.0f * ((float)gojo.hp / gojo.maxHp), 10});
        hpGojo.setPosition({52, 52});
        hpGojo.setFillColor(sf::Color::Green);
        window.draw(hpGojo);
        sf::RectangleShape enGojoBg({104, 8});
        enGojoBg.setPosition({50, 70});
        enGojoBg.setFillColor(sf::Color::Black);
        window.draw(enGojoBg);
        sf::RectangleShape enGojo({100.0f * (gojo.energy / MAX_ENERGY), 4});
        enGojo.setPosition({52, 72});
        enGojo.setFillColor(sf::Color::Cyan);
        window.draw(enGojo);

        sf::RectangleShape hpSukunaBg({604, 14});
        hpSukunaBg.setPosition({WINDOW_WIDTH / 2 - 302, 50});
        hpSukunaBg.setFillColor(sf::Color::Black);
        window.draw(hpSukunaBg);
        sf::RectangleShape hpSukuna({600.0f * ((float)sukuna.hp / sukuna.maxHp), 10});
        hpSukuna.setPosition({WINDOW_WIDTH / 2 - 300, 52});
        hpSukuna.setFillColor(sf::Color::Red);
        window.draw(hpSukuna);
        sf::RectangleShape enSukunaBg({604, 8});
        enSukunaBg.setPosition({WINDOW_WIDTH / 2 - 302, 70});
        enSukunaBg.setFillColor(sf::Color::Black);
        window.draw(enSukunaBg);
        sf::RectangleShape enSukuna({600.0f * (sukuna.energy / MAX_ENERGY), 4});
        enSukuna.setPosition({WINDOW_WIDTH / 2 - 300, 72});
        enSukuna.setFillColor(sf::Color(100, 100, 255));
        window.draw(enSukuna);

        window.display();

        if (gojo.hp <= 0)
        {
            window.close();
        }
        else if (sukuna.hp <= 0)
        {
            window.close();
        }
    }
    return 0;
}