#include "graphwidget.h"
#include "iostream"
#include <QKeyEvent>

GraphWidget::GraphWidget(QWidget *parent): QGraphicsView(parent)//Конструктор
{
    scene = new QGraphicsScene(this);
    setScene(scene);
}



void GraphWidget::addNode()//Добавляем вершину
{
    Node *node = new Node(this); // Создаём новую вершину
    scene->addItem(node); // Добавляем её на экран
    listOfNode << node; // Добавить эту вершину в список вершин
    changeIndecesOfAllVerteces(); // Поставить новый индекс вершине
    int ii = node->getIndex();
    node->setPos(QPointF(50+ii*10, 50+ii*10));
    update(); // Обновяем экран
}

void GraphWidget::deleteEdge(Edge *edge)
{
    scene->removeItem(edge);
    edge->destNode()->removeEdge(edge);
    edge->sourceNode()->removeEdge(edge);
    delete edge;
};

Node* GraphWidget::addNode1(QPointF position,int t)
//Добавляем вершину с заданной позицией и номером
{
    Node *node = new Node(this); // Создаём новую вершину
    node->setIndex(t);
    scene->addItem(node); // Добавляем её на экран
    listOfNode << node; // Добавить эту вершину в список вершин
    node->setPos(position);
    update(); // Обновяем экран
    return node;
};

Edge * GraphWidget::addEdge(Node *source,Node *dest, unsigned length)
{
    Edge *edge = new Edge(source, dest, length);
    scene->addItem(edge);
    return edge;
}

void GraphWidget::addEdge(Node *source, Node *dest)
{
    scene->addItem(new Edge(source, dest));
};



QPointF GraphWidget::getPosOfNode(int index)
// Возвращает местоположение вершины с номером index
{
    return listOfNode.at(index)->pos();
}

int GraphWidget::getListOfNodeSize()
//Возвращает количество вершин
{
    return listOfNode.size();
}

void GraphWidget::changeIndecesOfAllVerteces()
//Переименовывет вершины после удаления некоторых вершин
{
    foreach (Node *itemNode, listOfNode)
    {
        itemNode->setIndex(listOfNode.indexOf(itemNode));
        itemNode->update();
    }
}

QVector<Edges *> GraphWidget::getEdges()
// Возвращает список всех рёбер графа
{
    QVector<Edges *> EdgesList;
    foreach (Node *Node, listOfNode)
    {
        foreach (Edge *edge, Node->edges())
        {
            if (Node->getIndex() == edge->destNode()->getIndex()) continue;
            Edges *curr = new Edges;
            curr->source = Node->getIndex(); // В каждую запись включает первую вершину ребра
            curr->dest = edge->destNode()->getIndex(); // Вторую вершину ребра
            curr->length = (int)edge->getLength();     // Длину ребра
            curr->edge = edge; // Ссылку на само ребро
            EdgesList << curr;
        }
    }
    return EdgesList;
}

void GraphWidget::deleteSelectedItems()
//Удаляет выбранные вершины
{
    foreach (QGraphicsItem *itemNode, scene->selectedItems())//Для каждой выбранной вершины
    {
        scene->removeItem(itemNode);//Убрать её из окна
        listOfNode.removeAt(listOfNode.indexOf((Node *)itemNode)); //Убрать из списка вершин

        foreach (Edge *itemEdge, ((Node *)itemNode)->edges()) //Для каждого ребра, связанного с данной вершиной
        {
            // ???? пытаюсь удалить автомобиль
            if(!itemEdge->it->pixmap().isNull()) // Удалить со сцены аним. объект
                scene->removeItem(itemEdge->it);
            scene->removeItem(itemEdge);//Убрать ребро из окна
            itemEdge->destNode()->removeEdge(itemEdge);//Убрать ребро из списка рёбер первой вершины
            itemEdge->sourceNode()->removeEdge(itemEdge);//Убрать ребро из списка рёбер второй вершины
            delete itemEdge;//Удалить само ребро
        }
        delete itemNode;//Удалить саму вершину
    }
}

void GraphWidget::deleteAllItems() //Удаляет все вершины
{
   foreach (Node *itemNode, listOfNode)
    {
        scene->removeItem(itemNode);//Убрать её из окна

        foreach (Edge *itemEdge, itemNode->edges())
            //Для каждого ребра, связанного с данной вершиной
        {
            scene->removeItem(itemEdge);//Убрать ребро из окна
            itemEdge->destNode()->removeEdge(itemEdge);
            //Убрать ребро из списка рёбер первой вершины
            itemEdge->sourceNode()->removeEdge(itemEdge);
            //Убрать ребро из списка рёбер второй вершины
            delete itemEdge;//Удалить само ребро
        }
        itemNode->edges().clear();
        delete itemNode;//Удалить саму вершину
    }
   listOfNode.clear();
   scene->clear();
}


#ifndef QT_NO_WHEELEVENT
//! [5]
void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}
//! [5]
#endif
//! [7]
void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}
//! [7]

bool GraphWidget::createGraphFromInc(QString temp)         // Создать граф из списка инц.
{
    QList<QString> nodes;
    QList<QStringList> child_of_nodes;
    temp  = temp.trimmed();
    QTextStream stream(&temp);
    while(!stream.atEnd())
    {
        QString line = add_spaces_and_simplifie(stream.readLine(220));
        if(line.isEmpty()) continue;
        QStringList list = line.split(":");
        if(list.first() == list.last()) return false;
        QString t = list.first().trimmed();
        if (nodes.count(t) == 0)
            nodes << t;
        QString t2 = list.last().trimmed();
        QStringList list_of_children = t2.split(" , ",QString::SkipEmptyParts);
        child_of_nodes << list_of_children;
    }
    QList<QString> all_n; // Все вершины
    for (int i = 0; i < nodes.size();i++)
        if(!all_n.contains(nodes[i]))
            all_n << nodes[i];
    for (int i = 0; i < nodes.size();i++)
        for(int k = 0; k < child_of_nodes[i].size();k++)
            if(!all_n.contains(child_of_nodes[i][k]))
                all_n << child_of_nodes[i][k];
    //проверка, что все вершины это числа
    bool ok = true;
    for (int i = 0; i < nodes.size();i++)
        for(int k = 0; k < child_of_nodes[i].size();k++)
        {
            child_of_nodes[i][k].toInt(&ok);
        }
    if (!ok)
    {
        return false;
    }
    int radius = 200;
    double segments = (/*TwoPi*/6.28)/all_n.size();
    if (all_n.size() >= 16)
        radius = all_n.size()*70/6;
    double current_angle = 0;

    foreach(QString str,all_n)
    {
        // Создание всех вершин и размещение их по кругу
        QPointF pos(radius*cos(current_angle)+250,radius*sin(current_angle)+250);
        int k = str.toInt();
        //чтобы получить целые координаты для сохранения в файл
        int a, b;
        a = static_cast<int>(pos.rx());
        b = static_cast<int>(pos.ry());
        pos.setX(a); pos.setY(b);
        addNode1(pos,k);
        update();
        current_angle += segments;
    }
    for (int i = 0; i < nodes.size(); i++)
    {
        Node * a = findNode(nodes[i].toInt());
        //по номеру надо найти вершину
        for(int k = 0; k < child_of_nodes[i].size(); k++)
        {
            Node* b = findNode(child_of_nodes[i][k].toInt());
            if (a && b) // Елси найдены
            {
                addEdge(a, b);
            }
            else
                continue;
        }
    }
    return true;
}

QString GraphWidget::add_spaces_and_simplifie(QString str_for_work)
{
    QChar symbs[2]{':',','};
    for(int i = 0; i < 2; i++)
    {
        int a = -2;
        while((a = str_for_work.indexOf(symbs[i],a+2))!=-1)
        {
            {
                str_for_work.insert(a, ' ');
                str_for_work.insert(a+2, ' ');
            }
        }
    }
    str_for_work = str_for_work.simplified();
    return str_for_work;
}


Node* GraphWidget::findNode(int val)//по номеру надо найти вершину
{
    Node *a;
    //по номеру надо найти вершину
    foreach (Node *itemNode, listOfNode)
    {
        if (itemNode->getIndex() == val)
        {
            a = static_cast<Node*>(itemNode); // Привести текушую вершину к типу Node
            return a;
        }
    }
    return nullptr;
}
