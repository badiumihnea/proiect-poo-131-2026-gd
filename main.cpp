// This also works if you do not want `include/`, but some editors might not like it
// #include "Example.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
// #include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <vector>
#include <functional>
// #include <cmath>
// #include <cstdint>
#include <ostream>

//Poate ca include-urile nefolosite dau erori (???)

namespace Constants {
    constexpr unsigned int WINDOW_WIDTH = 1200;
    constexpr unsigned int WINDOW_HEIGHT = 720;
    constexpr unsigned int FPS = 60;

    constexpr float PLAYER_SIZE = 50.f;
    constexpr float GROUND_Y = 580.f;
    constexpr float JUMP_VELOCITY = -14.f;
    constexpr float GRAVITY = 0.7f;

    constexpr float ICON_DISPLAY_SIZE = 80.f;
    constexpr float BUTTON_WIDTH = 300.f;
    constexpr float BUTTON_HEIGHT = 55.f;

    const sf::Color COLOR_BG = sf::Color(20, 20, 40);
    const sf::Color COLOR_ACC = sf::Color(255, 180, 0);
    const sf::Color COLOR_ACC2 = sf::Color(0, 200, 255);
    const sf::Color COLOR_ACC3 = sf::Color(100, 100, 180);
    const sf::Color COLOR_BTN_IDLE = sf::Color(40, 40, 80);
    const sf::Color COLOR_BTN_HOVER = sf::Color(60, 60, 120);
    // const sf::Color COLOR_BTN_ACTIVE = sf::Color(255, 180, 0);
    const sf::Color COLOR_TEXT = sf::Color(255, 255, 255);
    // const sf::Color COLOR_TEXT_DARK = sf::Color(20, 20, 40);
}

class ResourceManager {
    sf::Font m_mainFont;
public:
    bool loadAll() {
        std::string fontPath = "../GameAssets/PUSABFONT.otf";
        if (m_mainFont.openFromFile(fontPath)) {
            std::cout<<"[Resource Manager] Font loaded\n";
            return true;
        }
        std::cout<<"[Resource Manager] WARNING: Font not loaded\n";
        return false;
    }
    const sf::Font& getFont() {
        return m_mainFont;
    }
};
class Icon {
    int m_icon_id;
    sf::Color m_col1;
    sf::Color m_col2;
    bool m_glow;
    sf::Color m_glow_col;
public:
    explicit Icon(int id=0, sf::Color col1 = sf::Color(80, 200, 120), sf::Color col2=sf::Color(0, 120, 255), bool glow=false, sf::Color glow_col= sf::Color(255, 255, 255)) :
    m_icon_id(id), m_col1(col1), m_col2(col2), m_glow(glow), m_glow_col(glow_col) {
    }

    [[nodiscard]] int getIconId() const {
        return m_icon_id;
    }

    [[nodiscard]] sf::Color getCol1() const {
        return m_col1;
    }

    [[nodiscard]] sf::Color getCol2() const {
        return m_col2;
    }

    [[nodiscard]] bool isGlow() const {
        return m_glow;
    }

    [[nodiscard]] sf::Color getGlowCol() const {
        return m_glow_col;
    }

    void set_m_icon_id(int icon_id) {
        this->m_icon_id = icon_id;
    }

    void set_m_col1(const sf::Color &col1) {
        this->m_col1 = col1;
    }

    void set_m_col2(const sf::Color &col2) {
        this->m_col2 = col2;
    }

    void set_m_glow(bool glow) {
        this->m_glow = glow;
    }

    void set_m_glow_col(const sf::Color &glow_col) {
        this->m_glow_col = glow_col;
    }

    void draw(sf::RenderWindow& window, float cx, float cy, float size) const {
        float half=size/2.f;
        sf::RectangleShape body(sf::Vector2f(size, size));
        body.setFillColor(m_col1);
        body.setOutlineColor(m_col1);
        body.setOutlineThickness(2.f);
        body.setOrigin({half, half});
        body.setPosition({cx, cy});
        window.draw(body);

        switch (m_icon_id % 5) {
            case 0: {
                sf::ConvexShape diamond;
                diamond.setPointCount(4);
                float d = size * 0.25f;
                diamond.setPoint(0, {0.f, -d});
                diamond.setPoint(1, {d, 0.f});
                diamond.setPoint(2, {0.f, d});
                diamond.setPoint(3, {-d, 0.f});
                diamond.setFillColor(m_col2);
                diamond.setPosition({cx, cy});
                window.draw(diamond);
                break;
            }
            case 1: {
                float t = size*0.12f;
                sf::RectangleShape horizontal(sf::Vector2f(size * 0.7f, t));
                horizontal.setFillColor(m_col2);;
                horizontal.setOrigin({size * 0.35f, t/2.f});
                horizontal.setPosition({cx, cy});
                window.draw(horizontal);
                sf::RectangleShape vertical(sf::Vector2f(t, size * 0.7f));
                vertical.setFillColor(m_col2);
                vertical.setOrigin({t/2.f, size*0.35f});
                vertical.setPosition({cx, cy});
                window.draw(vertical);
                break;
            }
            case 2: {
                sf::CircleShape circle(size * 0.22f);
                circle.setFillColor(m_col2);
                circle.setOrigin({size * 0.22f, size * 0.22f});
                circle.setPosition({cx, cy});
                window.draw(circle);
                break;
            }
            case 3: {
                for (int rot:{0, 45}) {
                    sf::RectangleShape square(sf::Vector2f(size * 0.4f, size* 0.4f));
                    square.setFillColor((m_col2));
                    square.setOrigin({size * 0.2f, size * 0.2f});
                    square.setPosition({cx, cy});
                    square.setRotation(sf::degrees(static_cast<float>(rot)));
                    window.draw(square);
                }
                break;
            }
            case 4: {
                sf::ConvexShape arrow;
                arrow.setPointCount(3);
                float aw = size * 0.35f, ah = size *0.35f;
                arrow.setPoint(0, {-aw, ah/2.f});
                arrow.setPoint(1, {aw, 0.f});
                arrow.setPoint(2, {-aw, -ah/2.f});
                arrow.setFillColor(m_col2);
                arrow.setPosition({cx, cy});
                window.draw(arrow);
                break;
            }
        }
    }
};

class PlayerProfile {
    std::string m_username;
    Icon m_icon;
public:
    PlayerProfile(): m_username("GUEST") ,m_icon (0, sf::Color(80, 200, 120),
        sf::Color(0, 120, 255), false, sf::Color(255, 255, 255)) {}

    [[nodiscard]] const Icon& getIcon() const {
        return m_icon;
    }

    void setIcon (const Icon& icon) {
        m_icon = icon;
    }

    [[nodiscard]] std::string getUsername() const {
        return m_username;
    }
    void setUsername(const std::string& username) {
        this->m_username = username;
    }
};


class Button {
    sf::RectangleShape m_shape;
    sf::Text m_text;
    bool m_hovered = false;
    void centerText(float x, float y, float w, float h) {
        sf::FloatRect tb = m_text.getLocalBounds();
        m_text.setOrigin({tb.size.x/2.f , tb.size.y/2.f});
        m_text.setPosition({x + w/2.f, y + h/2.f});
    }
public:
    Button(float x, float y, float w, float h, const std::string& label, const sf::Font& font) :
    m_text(font) {
        m_shape.setSize({w, h});
        m_shape.setPosition({x, y});
        m_shape.setFillColor(Constants::COLOR_BTN_IDLE);
        m_shape.setOutlineThickness(2.f);
        m_shape.setOutlineColor(Constants::COLOR_ACC3);
        m_text.setString(label);
        m_text.setCharacterSize(22u);
        m_text.setFillColor(Constants::COLOR_TEXT);
        centerText(x, y, w, h);
    }

    void update(sf::Vector2i mousePos) {
        m_hovered = m_shape.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(mousePos.x),
            static_cast<float>(mousePos.y)));
        m_shape.setFillColor(m_hovered ? Constants::COLOR_BTN_HOVER : Constants::COLOR_BTN_IDLE);
        m_shape.setOutlineColor(m_hovered ? Constants::COLOR_ACC : Constants::COLOR_ACC3);
    }

    bool handleEvent(const sf::Event& event) {
        if (const auto* e = event.getIf<sf::Event::MouseButtonReleased>()) {
            if (e->button == sf::Mouse::Button::Left && m_hovered) {
                return true;
            }
        }
        return false;
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(m_shape);
        window.draw(m_text);
    }

    void setLabel(const std::string& label) {
        m_text.setString(label);
        auto pos = m_shape.getPosition();
        auto size = m_shape.getSize();
        centerText(pos.x, pos.y, size.x, size.y);
    }

    bool isHovered() const {
        return m_hovered;
    }
};

class Game;

class State {
public:
    virtual ~State() = default;
    virtual void onEnter() {}
    virtual void onExit() {}

    virtual void handleEvents(sf::RenderWindow& window, const sf::Event& event) = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow& window) = 0;
protected:
    Game* m_game = nullptr;
};

class Game {
    sf::RenderWindow m_window;
    ResourceManager m_resources;
    PlayerProfile m_profile;
    std::unique_ptr<State> m_currentState;
    std::unique_ptr<State> m_pendingState;
    bool m_fullscreen=false;
    void applyWindowSettings(bool fullscreen);
public:
    Game();
    void changeState(std::unique_ptr<State> newstate);
    sf::RenderWindow& getWindow() {
        return m_window;
    }
    ResourceManager& getResources() {
        return m_resources;
    }
    PlayerProfile& getProfile() {
        return m_profile;
    }
    bool isFullscreen() const {
        return m_fullscreen;
    }
    void toggleFullscreen();
    void run();
};

class MainMenuState : public State {
    std::vector<Button> m_buttons;
    sf::Text m_title;
    sf::Text m_subtitle;
public:
    explicit MainMenuState (Game* game) : m_title(game->getResources().getFont()),
    m_subtitle(game->getResources().getFont()) {
        m_game = game;
        const sf::Font& font = game->getResources().getFont();
        float cx = Constants::WINDOW_WIDTH / 2.f - Constants::BUTTON_WIDTH / 2.f;
        float startY = 280.f;
        float spacing = 75.f;
        m_buttons.emplace_back(cx, startY + spacing * 0, Constants::BUTTON_WIDTH,
                               Constants::BUTTON_HEIGHT, "PLAY!", font);
        m_buttons.emplace_back(cx, startY + spacing * 1, Constants::BUTTON_WIDTH,
                               Constants::BUTTON_HEIGHT, "ICON MENU", font);
        m_buttons.emplace_back(cx, startY + spacing * 2, Constants::BUTTON_WIDTH,
                               Constants::BUTTON_HEIGHT, "SETTINGS", font);
        m_buttons.emplace_back(cx, startY + spacing * 3, Constants::BUTTON_WIDTH,
                               Constants::BUTTON_HEIGHT, "EXIT :(", font);

        m_title.setString("GEOMETRY DASH");
        m_title.setCharacterSize(50u);
        m_title.setFillColor(Constants::COLOR_ACC);
        m_title.setStyle(sf::Text::Style::Bold);
        {
            sf::FloatRect tb = m_title.getLocalBounds();
            m_title.setOrigin({tb.size.x / 2.f, tb.size.y / 2.f});
        }
        m_title.setPosition({Constants::WINDOW_WIDTH / 2.f, 160.f});
        m_subtitle.setString("Unibuc OOP Edition :)");
        m_subtitle.setCharacterSize(20u);
        m_subtitle.setFillColor(Constants::COLOR_ACC2);
        {
            sf::FloatRect sb = m_subtitle.getLocalBounds();
            m_subtitle.setOrigin({sb.size.x / 2.f, sb.size.y / 2.f});
        }
        m_subtitle.setPosition({Constants::WINDOW_WIDTH / 2.f, 230.f});
    }

    void handleEvents(sf::RenderWindow& window, const sf::Event& event) override;
    void update() override;
    void render(sf::RenderWindow& window) override;
};

class IconSelectState : public State {
    std::vector<Icon> m_icons;
    int m_selected = 0;
    sf::Text m_title;
    std::unique_ptr<Button> m_backButton;
    std::pair<float, float> iconPosition(int i) const {
        int n = static_cast<int>(m_icons.size());
        float spacing = 130.f;
        float totalW = spacing * static_cast<float>((n-1));
        float startX = Constants::WINDOW_WIDTH / 2.f - totalW /2.f;
        float cy = Constants::WINDOW_HEIGHT/2.f - 20.f;
        return {startX + spacing * static_cast<float>(i), cy};
    }
public:
    explicit IconSelectState(Game* game) : m_title(game->getResources().getFont()) {
        m_game = game;
        const sf::Font& font = game->getResources().getFont();
        m_icons = {
            Icon(0, sf::Color(80, 200, 120), sf::Color(0, 120, 255), false),
            Icon(1, sf::Color(80, 200, 120), sf::Color(0, 120, 255), false),
            Icon(2, sf::Color(80, 200, 120), sf::Color(0, 120, 255), false),
            Icon(3, sf::Color(80, 200, 120), sf::Color(0, 120, 255), false),
            Icon(4, sf::Color(80, 200, 120), sf::Color(0, 120, 255), true, sf::Color(255, 0, 144)),
        };
        m_selected = game->getProfile().getIcon().getIconId();
        m_title.setString("Select Icon");
        m_title.setCharacterSize(40u);
        m_title.setFillColor(Constants::COLOR_ACC);
        {
            sf::FloatRect tb = m_title.getLocalBounds();
            m_title.setOrigin({tb.size.x/2.f, tb.size.y/2.f});
        }
        m_title.setPosition({Constants::WINDOW_WIDTH / 2.f, 120.f});
        float bx = Constants::WINDOW_WIDTH / 2.f - 100.f;
        m_backButton = std::make_unique<Button>(bx, 500.f, Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT, "Back", font);
    }

    void handleEvents(sf::RenderWindow& /*window*/, const sf::Event& event) override {
        if (m_backButton->handleEvent(event)) {
            m_game->changeState(std::make_unique<MainMenuState>(m_game));
            return;
        }

        if (const auto* e = event.getIf<sf::Event::MouseButtonReleased>()) {
            if (e->button == sf::Mouse::Button::Left) {
                for (int i=0; i<static_cast<int>(m_icons.size()); ++i) {
                    auto [cx, cy] = iconPosition(i);
                    float half = Constants::ICON_DISPLAY_SIZE / 2.f;
                    sf::FloatRect slot({cx - half, cy-half}, {Constants::ICON_DISPLAY_SIZE,
                    Constants::ICON_DISPLAY_SIZE});
                    if (slot.contains(sf::Vector2f(static_cast<float>(e->position.x), static_cast<float>(e->position.y)))) {
                        m_selected = i;
                        m_game->getProfile().setIcon(m_icons[i]);
                    }
                }
            }
        }

        if (const auto* e = event.getIf<sf::Event::KeyPressed>()) {
            if (e->code == sf::Keyboard::Key::Escape) {
                m_game->changeState(std::make_unique<MainMenuState>(m_game));
            }
        }
    }

    void update() override {
        sf::Vector2i mp = sf::Mouse::getPosition(m_game->getWindow());
        m_backButton->update(mp);
    }

    void render(sf::RenderWindow& window) override;
};

class SettingsState : public State {
    sf::Text m_title;
    std::unique_ptr<Button> m_fullscreenButton;
    std::unique_ptr<Button> m_backButton;
    sf::Text m_volumeLabel;
    sf::RectangleShape m_sliderTrack;
    sf::CircleShape m_sliderThumb;

    std::string fullscreenLabel() const {
        return m_game->isFullscreen() ? "Fullscreen : ON" : "Fullscreen : OFF";
    }
public:
    explicit SettingsState(Game* game) : m_title(game->getResources().getFont()), m_volumeLabel(game->getResources().getFont()) {
        m_game = game;
        const sf::Font& font = game->getResources().getFont();
        m_title.setString("Settings");
        m_title.setCharacterSize(42u);
        m_title.setFillColor(Constants::COLOR_ACC);
        {
            sf::FloatRect tb = m_title.getLocalBounds();
            m_title.setOrigin({tb.size.x/2.f, tb.size.y/2.f});
        }
        m_title.setPosition({Constants::WINDOW_WIDTH / 2.f, 120.f});
        float cx = Constants::WINDOW_WIDTH/2.f - Constants::BUTTON_WIDTH/2.f;
        m_fullscreenButton = std::make_unique<Button>(cx, 240.f, Constants::BUTTON_WIDTH,
            Constants::BUTTON_HEIGHT, fullscreenLabel(), font);

        m_volumeLabel.setString("Volume\n\n\n\n(Warning: This doesn't work yet lmao)");
        m_volumeLabel.setCharacterSize(20u);
        m_volumeLabel.setFillColor(sf::Color(200, 200, 200));
        {
            sf::FloatRect vb = m_volumeLabel.getLocalBounds();
            m_volumeLabel.setOrigin({vb.size.x/2.f, vb.size.y/2.f});
        }
        m_volumeLabel.setPosition({Constants::WINDOW_WIDTH/2.f, 360.f});

        m_sliderTrack.setSize({360.f, 8.f});
        m_sliderTrack.setFillColor(sf::Color(80, 80, 120));
        m_sliderTrack.setPosition({Constants::WINDOW_WIDTH/2.f-150.f, 390.f});
        m_sliderThumb.setRadius(12.f);
        m_sliderThumb.setFillColor(Constants::COLOR_ACC);
        m_sliderThumb.setOrigin({12.f, 12.f});
        m_sliderThumb.setPosition({Constants::WINDOW_WIDTH/2.f, 394.f});

        m_backButton = std::make_unique<Button>(cx, 500.f, Constants::BUTTON_WIDTH,
            Constants::BUTTON_HEIGHT, "Back", font);
    }

    void handleEvents(sf::RenderWindow& /*window*/, const sf::Event& event) override {
        if (m_fullscreenButton->handleEvent(event)) {
            m_game->toggleFullscreen();
            m_fullscreenButton->setLabel(fullscreenLabel());
        }
        if (m_backButton->handleEvent(event)) {
            m_game->changeState(std::make_unique<MainMenuState>(m_game));
            return;
        }
        if (const auto* e = event.getIf<sf::Event::KeyPressed>()) {
            if(e->code == sf::Keyboard::Key::Escape) {
                m_game->changeState(std::make_unique<MainMenuState>(m_game));
            }
        }
    }

    void update() override {
        sf::Vector2i mp = sf::Mouse::getPosition(m_game->getWindow());
        m_fullscreenButton->update(mp);
        m_backButton->update(mp);
    }

    void render(sf::RenderWindow& window) override;
};

class PlayState : public State {
    float m_playerX;
    float m_playerY;
    float m_velocityY;
    bool m_onGround;
    float m_rotation;
    sf::RectangleShape m_ground;
    sf::Text m_jumpHint;
    int m_jumpHintAlpha = 0;
    bool m_returnPending = false;

    void tryJump() {
        if (m_onGround) {
            m_velocityY = Constants::JUMP_VELOCITY;
            m_onGround = false;
            m_jumpHintAlpha = 255;
        }
    }

    void drawPlayerWithRotation(sf::RenderWindow& window) {
        const Icon& icon = m_game->getProfile().getIcon();
        float size = Constants::PLAYER_SIZE;
        sf::RectangleShape body({size, size});
        body.setFillColor(icon.getCol1());
        body.setOutlineColor(icon.getCol2());
        body.setOutlineThickness(2.f);
        body.setOrigin({size/2.f, size/2.f});
        body.setPosition({m_playerX, m_playerY});
        body.setRotation(sf::degrees(m_rotation));
        window.draw(body);
        sf::Transform innerT;
        innerT.translate({m_playerX, m_playerY});
        innerT.rotate(sf::degrees(m_rotation));

        switch (icon.getIconId() % 5) {
            case 0: {
                sf::ConvexShape diamond;
                diamond.setPointCount(4);
                float d = size * 0.25f;
                diamond.setPoint(0, {0.f, -d});
                diamond.setPoint(1, {d, 0.f});
                diamond.setPoint(2, {0.f, d});
                diamond.setPoint(3, {-d, 0.f});
                diamond.setFillColor(icon.getCol2());
                window.draw(diamond, innerT);
                break;
            }
            case 1: {
                float t = size*0.12f;
                sf::RectangleShape horizontal(sf::Vector2f(size * 0.7f, t));
                horizontal.setFillColor(icon.getCol2());;
                horizontal.setOrigin({size * 0.35f, t/2.f});
                window.draw(horizontal, innerT);
                sf::RectangleShape vertical(sf::Vector2f(t, size * 0.7f));
                vertical.setFillColor(icon.getCol2());
                vertical.setOrigin({t/2.f, size*0.35f});
                window.draw(vertical, innerT);
                break;
            }
            case 2: {
                sf::CircleShape circle(size * 0.22f);
                circle.setFillColor(icon.getCol2());
                circle.setOrigin({size * 0.22f, size * 0.22f});
                window.draw(circle, innerT);
                break;
            }
            case 3: {
                for (int rot:{0, 45}) {
                    sf::RectangleShape square(sf::Vector2f(size * 0.4f, size* 0.4f));
                    square.setFillColor(icon.getCol2());
                    square.setOrigin({size * 0.2f, size * 0.2f});
                    sf::Transform rt=innerT;
                    rt.rotate(sf::degrees(static_cast<float>(rot)));
                    window.draw(square, rt);
                }
                break;
            }
            case 4: {
                sf::ConvexShape arrow;
                arrow.setPointCount(3);
                float aw = size * 0.35f, ah = size *0.35f;
                arrow.setPoint(0, {-aw, ah/2.f});
                arrow.setPoint(1, {aw, 0.f});
                arrow.setPoint(2, {-aw, -ah/2.f});
                arrow.setFillColor(icon.getCol2());
                window.draw(arrow, innerT);
                break;
            }
        }
    }

public:
    explicit PlayState(Game* game) : m_jumpHint(game->getResources().getFont()) {
        m_game = game;
        m_playerX = Constants::WINDOW_WIDTH/2.f;
        m_playerY=Constants::GROUND_Y;
        m_velocityY = 0.f;
        m_onGround=true;
        m_rotation = 0.f;
        m_ground.setSize({static_cast<float>(Constants::WINDOW_WIDTH), 100.f});
        m_ground.setFillColor(Constants::COLOR_ACC2);
        m_ground.setPosition({0.f, Constants::GROUND_Y});
    }

    void handleEvents(sf::RenderWindow& /*window*/, const sf::Event& event) override {
        if (const auto* e = event.getIf<sf::Event::MouseButtonPressed>()) {
            if (e->button == sf::Mouse::Button::Left) {
                tryJump();
            }
        }
        if (const auto* e = event.getIf<sf::Event::KeyPressed>()) {
            if (e->code == sf::Keyboard::Key::Up) {
                tryJump();
            }
            if (e->code == sf::Keyboard::Key::Escape) {
                m_returnPending = true;
            }
        }
    }

    void update() override {
        if (m_returnPending) {
            m_game->changeState(std::make_unique<MainMenuState>(m_game));
            return;
        }

        m_velocityY += Constants::GRAVITY;
        m_playerY += m_velocityY;
        if (m_playerY >= Constants::GROUND_Y) {
            m_playerY = Constants::GROUND_Y;
            m_velocityY = 0.f;
            m_onGround = true;
        }
        else {
            m_onGround = false;
        }

        if (!m_onGround) {
            m_rotation += 5.f;
        }
    }

    void render(sf::RenderWindow& window) override {
        window.clear(Constants::COLOR_BG);
        window.draw(m_ground);
        drawPlayerWithRotation(window);
    }
};

class Obstacle {
    std::string m_obsId;
    float m_x;
    float m_y;
    int m_layer;
public:
    Obstacle(std::string id, float x, float y, int layer=0) : m_obsId(std::move(id)), m_x(x), m_y(y), m_layer(layer) {
    }

    [[nodiscard]] std::string getObsId() const {
        return m_obsId;
    }

    [[nodiscard]] float getX() const {
        return m_x;
    }

    void setX(float x) {
        this->m_x = x;
    }

    [[nodiscard]] float getY() const {
        return m_y;
    }

    void setY(float y) {
        this->m_y = y;
    }

    [[nodiscard]] int getLayer() const {
        return m_layer;
    }

    void setLayer(int layer) {
        this->m_layer = layer;
    }

    void draw(sf::RenderWindow& window) const {
        sf::ConvexShape spike;
        spike.setPointCount(3);
        spike.setPoint(0, {0.f, -30.f});
        spike.setPoint(1, {20.f, 10.f});
        spike.setPoint(2, {-20.f, 10.f});
        spike.setFillColor(sf::Color(220, 50, 50));
        spike.setPosition({m_x, m_y});
        window.draw(spike);
    }

    friend std::ostream& operator<<(std::ostream& os, const Obstacle& obs) {
        std::cout<<"This object is an obstacle. Its ingame ID is "<<obs.m_obsId<<
        ". It will be placed at X: "<<obs.m_x<<" and Y: "<<obs.m_y<<
        " on Layer #"<<obs.m_layer<<".\n";
        return os;
    }
};

class OtherObj {
    std::string m_obj_id;
    float m_x;
    float m_y;
    int m_layer;

public:
    OtherObj(std::string obj_id, float x, float y, int layer)
        : m_obj_id(std::move(obj_id)),
          m_x(x),
          m_y(y),
          m_layer(layer) {
    }

    [[nodiscard]] std::string getObjId() const {
        return m_obj_id;
    }

    void setObjid(const std::string &id) {
        this->m_obj_id = id;
    }

    [[nodiscard]] float getX() const {
        return m_x;
    }

    void setX(float x) {
        this->m_x = x;
    }

    [[nodiscard]] float getY() const {
        return m_y;
    }

    void setY(float y) {
        this->m_y = y;
    }

    [[nodiscard]] int getLayer() const {
        return m_layer;
    }

    void setLayer(int layer) {
        this->m_layer = layer;
    }

    friend std::ostream& operator<<(std::ostream& os, const OtherObj& obj) {
        std::cout<<"The object's ingame ID is "<<obj.m_obj_id<<
        ". The object will be placed at X: "<<obj.m_x<<" and Y: "<<
        obj.m_y<<" on Layer #"<<obj.m_layer<<".\n";
        return os;
    }
};

class Level {
    std::string m_lvl_id;
    std::vector<Obstacle> m_layout={};
    std::vector<OtherObj> m_otherObjs={};
public:
    Level(std::string lvl_id, const std::vector<Obstacle> &layout, const std::vector<OtherObj> &other_objs)
        : m_lvl_id(std::move(lvl_id)),
          m_layout(layout),
          m_otherObjs(other_objs) {
    }

    Level(const Level& other) :
    m_lvl_id(other.m_lvl_id), m_layout(other.m_layout), m_otherObjs(other.m_otherObjs) {
        std::cout<<"Level has been copied!\n";
    }

    Level& operator=(const Level& other) {
        m_lvl_id = other.m_lvl_id;
        m_layout = other.m_layout;
        m_otherObjs = other.m_otherObjs;
        std::cout<<"Level has been copied! (using operator=)\n";
        return *this;
    }

    ~Level() {
        std::cout<<"Level has been deleted. Bye bye!\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Level& lvl) {
        std::cout<<"Level ID is "<<lvl.m_lvl_id<<". The number of objects is "<<size(lvl.m_layout) + size(lvl.m_otherObjs)<<"\n";
        if (size(lvl.m_layout) + size(lvl.m_otherObjs) >= 1000) {
            std::cout<<"Level has a large amount of objects.";
        }
        return os;
    }

    void draw(sf::RenderWindow& window) const {
        for (const auto& obs:m_layout) {
            obs.draw(window);
        }
    }

    [[nodiscard]] int objectCount() const {
        return static_cast<int>(m_layout.size() + m_otherObjs.size());
    }
};


void Game::changeState(std::unique_ptr<State> newState) {
    m_pendingState = std::move(newState);
}

void Game::applyWindowSettings(bool fullscreen) {
    if (fullscreen) {
        m_window.create(sf::VideoMode::getDesktopMode(), "Geometry Dash: OOP Edition", sf::State::Fullscreen);
    }
    else {
        m_window.create(sf::VideoMode({Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT}),
            "Geometry Dash: OOP Edition", sf::State::Windowed);
    }
    m_window.setFramerateLimit(Constants::FPS);
}

void Game::toggleFullscreen() {
    m_fullscreen= !m_fullscreen;
    applyWindowSettings(m_fullscreen);
}

Game::Game() {
    applyWindowSettings(false);
    m_resources.loadAll();
    m_currentState = std::make_unique<MainMenuState>(this);
    m_currentState->onEnter();
}

void Game::run() {
    while (m_window.isOpen()) {
        if (m_pendingState) {
            if (m_currentState) {
                m_currentState->onExit();
            }
            m_currentState = std::move(m_pendingState);
            m_pendingState = nullptr;
            m_currentState->onEnter();
        }

        while (const std::optional<sf::Event> event = m_window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                m_window.close();
                continue;
            }
            if (m_currentState) {
                m_currentState->handleEvents(m_window, *event);
            }
        }

        if (m_currentState) {
            m_currentState->update();
        }
        if (m_currentState) {
            m_currentState->render(m_window);
        }
        m_window.display();
    }
}

void MainMenuState::handleEvents(sf::RenderWindow& window, const sf::Event& event) {
    if (m_buttons[0].handleEvent(event)) {
        m_game->changeState(std::make_unique<PlayState>(m_game));
    }
    if (m_buttons[1].handleEvent(event)) {
        m_game->changeState(std::make_unique<IconSelectState>(m_game));
    }
    if (m_buttons[2].handleEvent(event)) {
        m_game->changeState(std::make_unique<SettingsState>(m_game));
    }
    if (m_buttons[3].handleEvent(event)) {
        window.close();
    }
}

void MainMenuState::update() {
    sf::Vector2i mp = sf::Mouse::getPosition(m_game->getWindow());
    for (auto& button : m_buttons) {
        button.update(mp);
    }
}

void MainMenuState::render(sf::RenderWindow& window) {
    window.clear(Constants::COLOR_BG);
    sf::RectangleShape band({static_cast<float>(Constants::WINDOW_WIDTH), 120.f});
    band.setFillColor(sf::Color(0, 0, 0, 80));
    band.setPosition({0.f, 100.f});
    window.draw(band);
    window.draw(m_title);
    window.draw(m_subtitle);
    for (auto& button : m_buttons) {
        button.draw(window);
    }
}

void IconSelectState::render(sf::RenderWindow& window) {
    window.clear(Constants::COLOR_BG);
    window.draw(m_title);
    for (int i=0; i<static_cast<int>(m_icons.size()); ++i) {
        auto [cx, cy] = iconPosition(i);
        float size = Constants::ICON_DISPLAY_SIZE;

        if (i==m_selected) {
            sf::RectangleShape highlight({size + 16.f, size+ 16.f});
            highlight.setFillColor(sf::Color(0, 0, 0));
            highlight.setOutlineThickness(3.f);
            highlight.setOutlineColor(sf::Color(0, 0, 0));
            highlight.setOrigin({(size + 16.f)/2.f, (size + 16.f)/2.f});
            highlight.setPosition({cx, cy});
            window.draw(highlight);
        }
        m_icons[i].draw(window, cx, cy, size);
    }
        sf::Text previewLabel(m_game->getResources().getFont());
        previewLabel.setString("Selected:");
        previewLabel.setCharacterSize(20u);
        previewLabel.setFillColor(sf::Color(200, 200, 200));
        previewLabel.setPosition({Constants::WINDOW_WIDTH/2.f -120.f, Constants::WINDOW_HEIGHT/2.f - 120.f});
        window.draw(previewLabel);

        m_icons[m_selected].draw(window, Constants::WINDOW_WIDTH/2.f + 60.f, Constants::WINDOW_HEIGHT/2.f - 100.f, 50.f);
        m_backButton->draw(window);
}

void SettingsState::render(sf::RenderWindow& window) {
    window.clear(Constants::COLOR_BG);
    for (int i=0; i<8; ++i) {
        sf::RectangleShape line({static_cast<float>(Constants::WINDOW_WIDTH), 1.f});
        line.setFillColor(sf::Color(60, 60, 100, 60));
        line.setPosition({0.f, static_cast<float>(i*100)});
        window.draw(line);
    }

    window.draw(m_title);
    m_fullscreenButton->draw(window);
    window.draw(m_volumeLabel);
    window.draw(m_sliderTrack);
    window.draw(m_sliderThumb);
    m_backButton->draw(window);
}

int main() {
    Game game;
    game.run();
    return 0;
}
