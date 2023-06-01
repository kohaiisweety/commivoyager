#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

int main()
{
    setlocale(LC_ALL, "ru");

    sf::RenderWindow window(sf::VideoMode(600, 300), "Allergies");
    std::string a1, a2, a3, a4;

    // определяем цвет заднего фона на белый
    window.clear(sf::Color::White);

    // загружаем шрифт из файла
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Failed to load font" << std::endl;
        return -1;
    }

    // создаем текстовые объекты и задаем их позиции
    sf::Text title("Allergies", font, 24);
    title.setFillColor(sf::Color::Black);
    sf::Text allergy1("Allergy to dairy products", font, 16);
    allergy1.setFillColor(sf::Color::Black); 
    sf::Text allergy2("Allergy to eggs", font, 16);
    allergy2.setFillColor(sf::Color::Black); 
    sf::Text allergy3("Allergy to wheat", font, 16);
    allergy3.setFillColor(sf::Color::Black); 
    sf::Text allergy4("Allergy to seafood (e.g. shrimp)", font, 16);
    allergy4.setFillColor(sf::Color::Black); 

    // определяем позицию надписей
    title.setPosition(10.f, 10.f);
    allergy1.setPosition(10.f, 50.f);
    allergy2.setPosition(10.f, 90.f);
    allergy3.setPosition(10.f, 130.f);
    allergy4.setPosition(10.f, 170.f);

    // создаем чекбоксы
    sf::RectangleShape checkbox1(sf::Vector2f(20.f, 20.f));
    sf::RectangleShape checkbox2(sf::Vector2f(20.f, 20.f));
    sf::RectangleShape checkbox3(sf::Vector2f(20.f, 20.f));
    sf::RectangleShape checkbox4(sf::Vector2f(20.f, 20.f));

    //определяем их позицию
    checkbox1.setPosition(400.f, 50.f);
    checkbox2.setPosition(400.f, 90.f);
    checkbox3.setPosition(400.f, 130.f);
    checkbox4.setPosition(400.f, 170.f);


    // задаем цвет и толщину обводки чекбоксов
    sf::Color outlineColor = sf::Color::Black;
    float outlineThickness = 2.f;
    checkbox1.setOutlineThickness(outlineThickness);
    checkbox1.setOutlineColor(outlineColor);
    checkbox2.setOutlineThickness(outlineThickness);
    checkbox2.setOutlineColor(outlineColor);
    checkbox3.setOutlineThickness(outlineThickness);
    checkbox3.setOutlineColor(outlineColor);
    checkbox4.setOutlineThickness(outlineThickness);
    checkbox4.setOutlineColor(outlineColor);


// создаем кнопку для открытия окна с рациономм
    sf::RectangleShape submitButton(sf::Vector2f(100.f, 50.f));
    submitButton.setPosition(450.f, 240.f);
    submitButton.setFillColor(sf::Color::Blue);


    // создаем текстовый объект для этой кнопки
    sf::Text submitText("Get diet", font, 16);
    submitText.setFillColor(sf::Color::White);
    submitText.setPosition(submitButton.getPosition().x + 15.f, submitButton.getPosition().y + 10.f);


    // создаем кнопки для определения режима тренировок
    sf::RectangleShape button1(sf::Vector2f(100.f, 50.f));
    button1.setFillColor(sf::Color::Green);
    button1.setPosition(20.f, 239.f);
    sf::RectangleShape button2(sf::Vector2f(100.f, 50.f));
    button2.setFillColor(sf::Color::Yellow);
    button2.setPosition(140.f, 239.f);
    sf::RectangleShape button3(sf::Vector2f(100.f, 50.f));
    button3.setFillColor(sf::Color::Red);
    button3.setPosition(260.f, 239.f);


    // добавляем надписи внутри кнопок
    sf::Text buttonText1("Easy", font, 16);
    buttonText1.setFillColor(sf::Color::White);
    buttonText1.setPosition(button1.getPosition().x + 15.f, button1.getPosition().y + 10.f);
    sf::Text buttonText2("Middle", font, 16);
    buttonText2.setFillColor(sf::Color::Black);
    buttonText2.setPosition(button2.getPosition().x + 15.f, button2.getPosition().y + 10.f);
    sf::Text buttonText3("Hard", font, 16);
    buttonText3.setFillColor(sf::Color::White);
    buttonText3.setPosition(button3.getPosition().x + 15.f, button3.getPosition().y + 10.f);


    window.display();

    // переменные для определения состояния чекбоксов
    bool dairy = false;
    bool eggs = false;
    bool wheat = false;
    bool seafood = false;


    // главный цикл
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // событие которое активируется нажатием на кнопку
            if (event.type == sf::Event::MouseButtonPressed)
            {


                // проверка состояния чекбоксов
                if (checkbox1.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    dairy = !dairy;
                    checkbox1.setFillColor(dairy ? sf::Color::Green : sf::Color::Red);
                    a1 = dairy ? "1" : "0";
                }
                else if (checkbox2.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    eggs = !eggs;
                    checkbox2.setFillColor(eggs ? sf::Color::Green : sf::Color::Red);
                    a2 = eggs ? "1" : "0";
                }
                else if (checkbox3.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    wheat = !wheat;
                    checkbox3.setFillColor(wheat ? sf::Color::Green : sf::Color::Red);
                    a3 = wheat ? "1" : "0";
                }
                else if (checkbox4.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    seafood = !seafood;
                    checkbox4.setFillColor(seafood ? sf::Color::Green : sf::Color::Red);
                    a4 = seafood ? "1" : "0";
                }



                // проверяем была ли нажата кнопка для выявления рациона питания
                if (submitButton.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {


                    // создаем новое окно для вывода диеты
                    sf::RenderWindow resultWindow(sf::VideoMode(800, 450), "Results");

                    // создаем текстовые объекты для второго окна
                    sf::Text resultsTitle("Results", font, 24);
                    resultsTitle.setFillColor(sf::Color::Black);


                    // складываем название файла с диетой из текстовых переменных a1, a2, a3, and a4, значения которых мы получили при проверке чекбоксов 
                    std::string fileName = a1 + a2 + a3 + a4 + ".png"; //изначально тут был + ".txt"
                    std::ifstream inFile(fileName);

                                                                         //
                    /*std::string fileContents;
                    if (inFile.is_open()) {
                        std::stringstream buffer;                           эта часть кода нужна была чтобы открывать изначально файл в формате .txt и выводить на экран текст из файлов
                        buffer << inFile.rdbuf();
                        fileContents = buffer.str();                        изменил на .png так как не нашел как вывести кириллицу
                        inFile.close();
                    }*/
                    /*sf::Text fileResult(fileContents, font, 16);
                    fileResult.setFillColor(sf::Color::Black);*/
                                                                          //

                    // закгружаем изображение
                    sf::Texture bgTexture;
                    if (!bgTexture.loadFromFile(fileName)) {
                        // ошибка поиска изображения
                    }

                    //делаем изображение фоновым
                    sf::Sprite bgSprite(bgTexture);
                    bgSprite.setPosition(0, 0);

                    float scaleX = static_cast<float>(resultWindow.getSize().x) / bgTexture.getSize().x;
                    float scaleY = static_cast<float>(resultWindow.getSize().y) / bgTexture.getSize().y;

                    bgSprite.setScale(scaleX, scaleY);
                    resultWindow.draw(bgSprite);

                    resultWindow.display();

                    while (resultWindow.isOpen())
                    {
                        sf::Event resultsEvent;
                        while (resultWindow.pollEvent(resultsEvent))
                        {
                            if (resultsEvent.type == sf::Event::Closed)
                            {
                                resultWindow.close();
                            }
                        }
                    }                    
                }

                //проверка на то что была нажата одна из кнопок для получения комплекса упражнений
                if (button1.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) || button2.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) || button3.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {

                    //создаем окно для вывода комплекса упражнений
                    sf::RenderWindow secondWindow(sf::VideoMode(1100, 500), "Exercise");
                    secondWindow.clear(sf::Color::White);

                    //выводим названия нового окна
                    sf::Text secondTitle("Exercise", font, 24);
                    secondTitle.setFillColor(sf::Color::Black);

                    if (button1.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {

                        //если была нажата первая кнопка то мы ввыводим соответсвующее ей изображение
                        std::string fileName = "easy.png";
                        std::ifstream inFile(fileName);
                        sf::Texture bgTexture;

                        if (!bgTexture.loadFromFile(fileName)) {
                        }
                        sf::Sprite bgSprite(bgTexture);
                        bgSprite.setPosition(0, 0);

                        float scaleX = static_cast<float>(secondWindow.getSize().x) / bgTexture.getSize().x;
                        float scaleY = static_cast<float>(secondWindow.getSize().y) / bgTexture.getSize().y;

                        bgSprite.setScale(scaleX, scaleY);
                        secondWindow.draw(bgSprite);
                    }
                    if (button2.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {

                        //если была нажата вторая кнопка то мы ввыводим соответсвующее ей изображение
                        std::string fileName = "middle.png";
                        std::ifstream inFile(fileName);
                        sf::Texture bgTexture;

                        if (!bgTexture.loadFromFile(fileName)) {
                        }
                        sf::Sprite bgSprite(bgTexture);
                        bgSprite.setPosition(0, 0);

                        float scaleX = static_cast<float>(secondWindow.getSize().x) / bgTexture.getSize().x;
                        float scaleY = static_cast<float>(secondWindow.getSize().y) / bgTexture.getSize().y;

                        bgSprite.setScale(scaleX, scaleY);
                        secondWindow.draw(bgSprite);
                    }
                    if (button3.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {

                        //если была нажата третья кнопка то мы ввыводим соответсвующее ей изображение
                        std::string fileName = "hard.png";
                        std::ifstream inFile(fileName);
                        sf::Texture bgTexture;

                        if (!bgTexture.loadFromFile(fileName)) {
                        }
                        sf::Sprite bgSprite(bgTexture);
                        bgSprite.setPosition(0, 0);

                        float scaleX = static_cast<float>(secondWindow.getSize().x) / bgTexture.getSize().x;
                        float scaleY = static_cast<float>(secondWindow.getSize().y) / bgTexture.getSize().y;

                        bgSprite.setScale(scaleX, scaleY);
                        secondWindow.draw(bgSprite);
                    }
                    secondWindow.display();
                    while (secondWindow.isOpen())
                    {
                        sf::Event resultsEvent;
                        while (secondWindow.pollEvent(resultsEvent))
                        {
                            if (resultsEvent.type == sf::Event::Closed)
                            {
                                secondWindow.close();
                            }
                        }
                    }
                }
        }
    }
    window.clear(sf::Color::White);

    //вывод текстовых объектов на главное окно
    window.draw(title);
    window.draw(allergy1);
    window.draw(allergy2);
    window.draw(allergy3);
    window.draw(allergy4);

    //вывод кнопок и текста в них на главное окно
    window.draw(checkbox1);
    window.draw(checkbox2);
    window.draw(checkbox3);
    window.draw(checkbox4);


    window.draw(submitButton);
    window.draw(submitText);


    window.draw(button1);
    window.draw(buttonText1);

    window.draw(button2);
    window.draw(buttonText2);

    window.draw(button3);
    window.draw(buttonText3);


    window.display();
}
return 0;
}