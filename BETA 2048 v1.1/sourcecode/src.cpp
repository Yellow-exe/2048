#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
using std::cout; using std::cin; using std::endl;
using namespace sf;
int main() {
    srand(time(NULL));
    bool not_running = true; int laps = 0;
    //global movements vars//
    bool moveright = false, moveleft = false, moveup = false, movedown = false;

    //spawn vars
    int x_spawn, y_spawn;
    bool spawn;

    ///IMAGES///
    //2
    Texture twoT;
    twoT.loadFromFile("images/2.png");
    Sprite two(twoT);
    two.setScale(0.125, 0.125);

    //4
    Texture fourT;
    fourT.loadFromFile("images/4.png");
    Sprite four(fourT);
    four.setScale(0.125, 0.125);

    //8
    Texture eightT;
    eightT.loadFromFile("images/8.png");
    Sprite eight(eightT);
    eight.setScale(0.125, 0.125);

    //16
    Texture sixteenT;
    sixteenT.loadFromFile("images/16.png");
    Sprite sixteen(sixteenT);
    sixteen.setScale(0.125, 0.125);

    //32
    Texture thirtytwoT;
    thirtytwoT.loadFromFile("images/32.png");
    Sprite thirtytwo(thirtytwoT);
    thirtytwo.setScale(0.125, 0.125);

    //64
    Texture sixtyfourT;
    sixtyfourT.loadFromFile("images/64.png");
    Sprite sixtyfour(sixtyfourT);
    sixtyfour.setScale(0.125, 0.125);

    //128
    Texture OneTwoEightT;
    OneTwoEightT.loadFromFile("images/128.png");
    Sprite OneTwoEight(OneTwoEightT);
    OneTwoEight.setScale(0.125, 0.125);

    //256
    Texture TwoFiveSixT;
    TwoFiveSixT.loadFromFile("images/256.png");
    Sprite TwoFiveSix(TwoFiveSixT);
    TwoFiveSix.setScale(0.125, 0.125);

    //512
    Texture FiveOneTwoT;
    FiveOneTwoT.loadFromFile("images/512.png");
    Sprite FiveOneTwo(FiveOneTwoT);
    FiveOneTwo.setScale(0.125, 0.125);

    //1024
    Texture OneOTwoFourT;
    OneOTwoFourT.loadFromFile("images/1024.png");
    Sprite OneOTwoFour(OneOTwoFourT);
    OneOTwoFour.setScale(0.125, 0.125);

    //2048
    Texture TwoOFourEightT;
    TwoOFourEightT.loadFromFile("images/2048.png");
    Sprite TwoOFourEight(TwoOFourEightT);
    TwoOFourEight.setScale(0.125, 0.125);

    //matrix storage
    int canvas[4][4] = { 0 };

    //world spawn (init) run twice//
    for (int i = 0; i < 2; i++) {
        int y_spawn = rand() % 4; //coordinates in matrix
        int x_spawn = rand() % 4;
        int type = rand() % 2 + 1; // 4 or 8
        //for specific debugging
        //int y_spawn = 0;
        //int x_spawn = 1+i*2;
        //int type = 1+i;
        //cout << y_spawn << x_spawn << type << "|";
        canvas[y_spawn][x_spawn] = type;
    }
    y_spawn = 2; //coordinates in matrix
    x_spawn = 0;
    int type = 1; // 4 or 8
    canvas[y_spawn][x_spawn] = type;

    y_spawn = 2; //coordinates in matrix
    x_spawn = 2;
    type = 1; // 4 or 8
    canvas[y_spawn][x_spawn] = type;

    sf::RenderWindow window(sf::VideoMode(256, 256), "Retardgame!");
    window.setFramerateLimit(144);
    int p = 3;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            //kb listener
            if (not_running) { p = 3; }
            if (Keyboard::isKeyPressed(Keyboard::Right) && not_running) {  moveright = 1; not_running = 0;  }
            if (Keyboard::isKeyPressed(Keyboard::Left) && not_running) { moveleft = 1; not_running = 0; }
            if (Keyboard::isKeyPressed(Keyboard::Up) && not_running) { moveup = 1; not_running = 0; }
            if (Keyboard::isKeyPressed(Keyboard::Down) && not_running) { movedown = 1; not_running = 0; }
            if (Keyboard::isKeyPressed(Keyboard::S)) { for (int y = 0; y < 3; y++) { for (int x = 0; x < 3; x++) { canvas[y][x] = 0; canvas[0][0] = 1; canvas[0][3] = 2; } } }
        }
        //saves//
        // for(int z = x - 1; z > 0; z--){if (canvas[y][x])}
        // end //
        // 
        //basic global movements//
        if (!not_running) {
            spawn = 1;
            if (moveleft || moveup) {
                for (int y = 0; y <= 3; y++) {
                    for (int x = 0; x <= 3; x++) {
                        if (canvas[y][x] != 0) {
                            //left
                            if (moveleft) {
                                if (x != 0) {
                                    if (canvas[y][x - 1] == 0) { canvas[y][x - 1] = canvas[y][x]; canvas[y][x] = 0; }
                                    else if (canvas[y][x - 1] != 0) { if (canvas[y][x - 1] == canvas[y][x]) { canvas[y][x - 1]++; canvas[y][x] = 0; } }
                                    else { spawn = 0; }
                                }
                            }
                            if (moveup) {
                                if (y != 0) {
                                    if (canvas[y - 1][x] == 0) { canvas[y - 1][x] = canvas[y][x]; canvas[y][x] = 0; }
                                    else if (canvas[y - 1][x] != 0) { if (canvas[y - 1][x] == canvas[y][x]) { canvas[y - 1][x]++; canvas[y][x] = 0; } }
                                    else { spawn = 0; }
                                }
                            }
                        }
                    }
                }
                //reset
                if (p == 0) { moveleft = 0; moveup = 0; }
            }
            if (moveright || movedown) {
                for (int y = 3; y >= 0; y--) {
                    for (int x = 3; x >= 0; x--) {
                        if (canvas[y][x] != 0) {
                            if (moveright) {
                                switch (x) {
                                case 0:if (canvas[y][1] == 0) { canvas[y][1] = canvas[y][x]; canvas[y][x] = 0; }
                                      else if (canvas[y][1] == canvas[y][x]) { canvas[y][1]++; canvas[y][x] = 0; }; break;
                                case 1:if (canvas[y][2] == 0) { canvas[y][2] = canvas[y][x]; canvas[y][x] = 0; }
                                      else if (canvas[y][2] == canvas[y][x]) { canvas[y][2]++; canvas[y][x] = 0; }; break;
                                case 2:if (canvas[y][3] == 0) { canvas[y][3] = canvas[y][x]; canvas[y][x] = 0; }
                                      else if (canvas[y][3] == canvas[y][x]) { canvas[y][3]++; canvas[y][x] = 0; }; break;
                                default: spawn = 0; break;
                                }

                            }
                            if (movedown) {
                                if (y != 3) {
                                    if (canvas[y + 1][x] == 0) { canvas[y + 1][x] = canvas[y][x]; canvas[y][x] = 0; }
                                    else if (canvas[y + 1][x] != 0) { if (canvas[y + 1][x] == canvas[y][x]) { canvas[y + 1][x]++; canvas[y][x] = 0; } }
                                    else { spawn = 0; }
                                }
                            }
                        }
                    }
                }
                //reset
                if (p == 0) { moveright = 0; movedown = 0; }
            }
            if (p == 0) {
                not_running = 1;
                int count = 0;
                for (int y = 0; y < 4; y++) { for (int x = 0; x < 4; x++) { if (canvas[y][x] != 0) { count++; } if (count != 16) { spawn = 1; } else { spawn = 0; } } }
                cout << count;

                if (spawn) {
                    bool spawn_unique = 0;
                    while (!spawn_unique) {
                        int spawnamt = rand() % 2 + 1;
                        for (int i = 0; i < spawnamt; i++) {
                            y_spawn = rand() % 4; //coordinates in matrix
                            x_spawn = rand() % 4;
                        }
                        if (canvas[y_spawn][x_spawn] != 0) { spawn_unique = 0; }
                        else { spawn_unique = 1; int type = rand() % 2 + 1; canvas[y_spawn][x_spawn] = type; }
                    }
                }


            }
            else { p--; }
        }
        /*
        //basic global movements//
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                //(in construction)
                //canvas[y][x]
                if (moveright) {
                    if (laps < 8) { OneOTwoFour.move(8, 0); laps++; }
                    else { not_running = 1; moveright = 0; laps = 0; }
                }
                if (moveleft) {
                    if (laps < 8) { OneOTwoFour.move(-8, 0); laps++; }
                    else { not_running = 1; moveleft = 0; laps = 0; }
                }
                if (moveup) {
                    if (laps < 8) { OneOTwoFour.move(0, -8); laps++; }
                    else { not_running = 1; moveup = 0; laps = 0; }
                }
                if (movedown) {
                    if (laps < 8) { OneOTwoFour.move(0, 8); laps++; }
                    else { not_running = 1; movedown = 0; laps = 0; }
                }
            }
        }
        */
        //draw canvas// 
       /* system("cls");
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                cout << canvas[y][x] << " ";
            }
            cout << endl;
        }*/
        //draw tiles according to "canvas"//
        window.clear(Color::White);
        for (int y = 0; y <= 3; y++) {
            for (int x = 0; x <= 3; x++) {
                if (canvas[y][x] != 0) {
                    if (canvas[y][x] == 1) { two.setPosition(x * 64, y * 64); window.draw(two); }
                    if (canvas[y][x] == 2) { four.setPosition(x * 64, y * 64); window.draw(four); }
                    if (canvas[y][x] == 3) { eight.setPosition(x * 64, y * 64); window.draw(eight); }
                    if (canvas[y][x] == 4) { sixteen.setPosition(x * 64, y * 64); window.draw(sixteen); }
                    if (canvas[y][x] == 5) { thirtytwo.setPosition(x * 64, y * 64); window.draw(thirtytwo); }
                    if (canvas[y][x] == 6) { sixtyfour.setPosition(x * 64, y * 64); window.draw(sixtyfour); }
                    if (canvas[y][x] == 7) { OneTwoEight.setPosition(x * 64, y * 64); window.draw(OneTwoEight); }
                    if (canvas[y][x] == 8) { TwoFiveSix.setPosition(x * 64, y * 64); window.draw(TwoFiveSix); }
                    if (canvas[y][x] == 9) { FiveOneTwo.setPosition(x * 64, y * 64); window.draw(FiveOneTwo); }
                    if (canvas[y][x] == 10) { OneOTwoFour.setPosition(x * 64, y * 64); window.draw(OneOTwoFour); }
                    if (canvas[y][x] == 11) { TwoOFourEight.setPosition(x * 64, y * 64); window.draw(TwoOFourEight); }
                }
                else { continue; }
            }
        }
        window.display();
    }

    return 0;
}