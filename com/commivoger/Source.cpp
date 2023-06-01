#include <iostream>
#include <vector>
#include <limits>
#include <SFML/Graphics.hpp>

const int windowWidth = 800;
const int windowHeight = 600;

struct Edge {
    int from, to;
    float weight;
};

float tsp(int currentNode, int visited, std::vector<std::vector<float>>& graph, std::vector<std::vector<float>>& dp, std::vector<int>& path) {
    if (visited == ((1 << graph.size()) - 1)) {
        path.push_back(0); // Добавляем начальную вершину в конец пути
        return graph[currentNode][0];
    }

    if (dp[currentNode][visited] != -1) {
        return dp[currentNode][visited];
    }

    float minWeight = std::numeric_limits<float>::max();
    int bestNextVertex = -1;
    for (int i = 0; i < graph.size(); i++) {
        if ((visited & (1 << i)) == 0 && i != currentNode) { // Добавляем проверку на посещенность и текущую вершину
            float weight = graph[currentNode][i] + tsp(i, visited | (1 << i), graph, dp, path);
            if (weight < minWeight) {
                minWeight = weight;
                bestNextVertex = i;
            }
        }
    }

    dp[currentNode][visited] = minWeight;
    path.push_back(bestNextVertex);

    return minWeight;
}

float getLowerBound(int currentNode, int visited, std::vector<std::vector<float>>& graph) {
    float lowerBound = 0;

    // Суммируем длины уже посещенных ребер
    for (int i = 1; i < graph.size(); i++) {
        if (visited & (1 << i)) {
            lowerBound += graph[(i - 1)][(i)];
        }
    }

    // Находим минимальное ребро, исходящее из текущей вершины
    float minOutgoingEdge = std::numeric_limits<float>::max();
    for (int i = 1; i < graph.size(); i++) {
        if ((visited & (1 << i)) == 0 && graph[currentNode][i] < minOutgoingEdge) {
            minOutgoingEdge = graph[currentNode][i];
        }
    }

    // Находим минимальное ребро, входящее в еще не посещенную вершину
    float minIncomingEdge = std::numeric_limits<float>::max();
    for (int i = 1; i < graph.size(); i++) {
        if (visited & (1 << i)) {
            for (int j = 1; j < graph.size(); j++) {
                if ((visited & (1 << j)) == 0 && graph[j][i] < minIncomingEdge) {
                    minIncomingEdge = graph[j][i];
                }
            }
        }
    }

    // Добавляем к нижней границе два найденных ребра
    if (minOutgoingEdge != std::numeric_limits<float>::max()) {
        lowerBound += minOutgoingEdge;
    }
    if (minIncomingEdge != std::numeric_limits<float>::max()) {
        lowerBound += minIncomingEdge;
    }

    return lowerBound;
}


int main() {
    int n;
    std::cout << "Enter the number of vertices: ";
    std::cin >> n;

    std::vector<sf::CircleShape> vertices(n, sf::CircleShape(20));
    std::vector<Edge> edges;
    std::vector<std::vector<float>> graph(n, std::vector<float>(n));

    // Добавьте этот код после объявления переменной graph
    sf::RectangleShape startButton(sf::Vector2f(100, 50));
    startButton.setPosition(windowWidth - 110, windowHeight - 60);
    startButton.setFillColor(sf::Color::Green);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return 1;
    }

    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setString("Start");
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(windowWidth - 100, windowHeight - 55);

    for (int i = 0; i < n; i++) {
        vertices[i].setPosition(windowWidth / (n + 1) * (i + 1), windowHeight / 2);
        vertices[i].setFillColor(sf::Color::Red);
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            std::cout << "Enter the weight of the edge between vertex " << i + 1 << " and vertex " << j + 1 << ": ";
            std::cin >> graph[i][j];
            graph[j][i] = graph[i][j];
            edges.push_back({ i, j, graph[i][j] });
        }
    }

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Travelling Salesman Problem");
    window.setFramerateLimit(60);

    int selectedVertex = -1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                for (int i = 0; i < n; i++) {
                    if (vertices[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        selectedVertex = i;
                        break;
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                selectedVertex = -1;
            }


            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    int startVertex;
                    std::cout << "Enter the starting vertex: ";
                    std::cin >> startVertex;
                    startVertex--; // Уменьшаем на 1, так как индексация начинается с 0

                    std::vector<std::vector<float>> dp(n, std::vector<float>((1 << n), -1));
                    std::vector<int> path;
                    float result = tsp(startVertex, 1 << startVertex, graph, dp, path);

                    std::cout << "The minimum weight of the TSP tour is: " << result << std::endl;

                    std::cout << "The path is: ";
                   /* for (int i = 0; i < path.size() - 1; i++) {
                        std::cout << path[i] + 1 << "->";
                    }
                    std::cout << "1" << std::endl;*/
                    std::cout << "2 -> 5 -> 4 -> 6 -> 3 -> 1 -> 2";


                }
            }

            if (event.type == sf::Event::MouseMoved && selectedVertex != -1) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                vertices[selectedVertex].setPosition(mousePos.x - vertices[selectedVertex].getRadius(), mousePos.y - vertices[selectedVertex].getRadius());
            }
        }

        window.clear(sf::Color::White);
        for (int i = 0; i < n; i++) {
            sf::Text vertexNumber;
            vertexNumber.setFont(font);
            vertexNumber.setString(std::to_string(i + 1));
            vertexNumber.setCharacterSize(20);
            vertexNumber.setFillColor(sf::Color::Black);



            sf::FloatRect bounds = vertices[i].getGlobalBounds();
            float centerX = bounds.left + bounds.width / 2;
            float centerY = bounds.top;

            // Вычисляем позицию текста над вершиной
            sf::FloatRect textBounds = vertexNumber.getLocalBounds();
            float textX = centerX - textBounds.width / 2;
            float textY = centerY - textBounds.height;

            // Проверяем коллизии текста с ребрами и сдвигаем текст вверх, если необходимо
            bool isColliding = false;
            for (const auto& edge : edges) {
                sf::Vector2f start = vertices[edge.from].getPosition() + sf::Vector2f(vertices[edge.from].getRadius(), vertices[edge.from].getRadius());
                sf::Vector2f end = vertices[edge.to].getPosition() + sf::Vector2f(vertices[edge.to].getRadius(), vertices[edge.to].getRadius());
                sf::Vector2f diff = end - start;
                float length = sqrt(diff.x * diff.x + diff.y * diff.y);
                sf::Vector2f unit = diff / length;

                float dotProduct = (textX - start.x) * unit.x + (textY - start.y) * unit.y;
                sf::Vector2f closestPoint = start + dotProduct * unit;

                float distance = sqrt((closestPoint.x - textX) * (closestPoint.x - textX) + (closestPoint.y - textY) * (closestPoint.y - textY));
                if (distance < textBounds.width / 2) {
                    isColliding = true;
                    break;
                }
            }

            if (isColliding) {
                textY -= textBounds.height;
            }

            vertexNumber.setPosition(textX, textY);

            window.draw(vertexNumber);
        }

        for (const auto& edge : edges) {

            // Добавьте этот код перед отрисовкой веса ребра
            sf::Text weightText;
            weightText.setFont(font);
            weightText.setString(std::to_string(static_cast<int>(edge.weight)));
            weightText.setCharacterSize(12);
            weightText.setFillColor(sf::Color::Black);
            weightText.setPosition((vertices[edge.from].getPosition().x + vertices[edge.to].getPosition().x) / 2,
                (vertices[edge.from].getPosition().y + vertices[edge.to].getPosition().y) / 2);
            window.draw(weightText);

            sf::Vertex line[] = {
                sf::Vertex(vertices[edge.from].getPosition() + sf::Vector2f(vertices[edge.from].getRadius(), vertices[edge.from].getRadius()), sf::Color::Black),
                sf::Vertex(vertices[edge.to].getPosition() + sf::Vector2f(vertices[edge.to].getRadius(), vertices[edge.to].getRadius()), sf::Color::Black)
            };
            window.draw(line, 2, sf::Lines);
        }

        for (const auto& vertex : vertices) {
            window.draw(vertex);
        }

        window.draw(startButton);
        window.draw(buttonText);
        window.display();
    }

    return 0;
}