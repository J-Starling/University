#include "mainwindow.h"
#include <QtPrintSupport/QPrinter>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QDateTime>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QScreen>
#include <QGuiApplication>
#include <QScrollBar>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    scene(nullptr),
    locomotiveItem(nullptr),
    fuelLevelItem(nullptr),
    modeTextItem(nullptr),
    fuelLevelTextItem(nullptr),
    animationTimer(nullptr),
    fuelConsumptionTimer(nullptr),
    isAnimationRunning(false),
    currentFuelLevel(1.0),
    locomotivePosition(0.0)
{
    if (!dieselLocomotiveImage.load("diesel_locomotive.png")) {
        dieselLocomotiveImage = QPixmap(150, 80);
        dieselLocomotiveImage.fill(Qt::darkBlue);
    } else {
        dieselLocomotiveImage = dieselLocomotiveImage.scaled(150, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    if (!lngLocomotiveImage.load("lng_locomotive.png")) {
        lngLocomotiveImage = QPixmap(150, 80);
        lngLocomotiveImage.fill(Qt::darkGreen);
    } else {
        lngLocomotiveImage = lngLocomotiveImage.scaled(150, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    currentLocomotiveImage = dieselLocomotiveImage;

    setupUI();
    setupScene();

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &MainWindow::onAnimationTimer);

    fuelConsumptionTimer = new QTimer(this);
    connect(fuelConsumptionTimer, &QTimer::timeout, this, &MainWindow::onFuelConsumptionTimer);
}

MainWindow::~MainWindow() {
    if (animationTimer) {
        animationTimer->stop();
        delete animationTimer;
    }
    if (fuelConsumptionTimer) {
        fuelConsumptionTimer->stop();
        delete fuelConsumptionTimer;
    }
}

void MainWindow::setupUI() {
    setWindowTitle("Анализ эффективности");
    setFixedSize(1400, 800);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    QVBoxLayout *leftLayout = new QVBoxLayout();

    graphicsView = new QGraphicsView(this);
    graphicsView->setFixedSize(1000, 600);
    graphicsView->setRenderHint(QPainter::Antialiasing);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    graphicsView->horizontalScrollBar()->setEnabled(false);
    graphicsView->verticalScrollBar()->setEnabled(false);
    graphicsView->setDragMode(QGraphicsView::NoDrag);
    graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);


    leftLayout->addWidget(graphicsView);
    mainLayout->addLayout(leftLayout, 3);
}

void MainWindow::setupScene() {
    if (!scene) {
        scene = new QGraphicsScene(this);
    }
    scene->clear();
    scene->setSceneRect(0, 0, 1000, 600);

    if (graphicsView) {
        graphicsView->setScene(scene);
    }

    QLinearGradient skyGradient(0, 0, 0, 350);
    skyGradient.setColorAt(0, QColor(135, 206, 235));
    skyGradient.setColorAt(1, QColor(176, 224, 230));
    QGraphicsRectItem *sky = new QGraphicsRectItem(0, 0, 1000, 350);
    sky->setBrush(QBrush(skyGradient));
    sky->setPen(QPen(Qt::NoPen));
    sky->setZValue(-200);
    scene->addItem(sky);

    QLinearGradient groundGradient(0, 350, 0, 600);
    groundGradient.setColorAt(0, QColor(34, 139, 34));
    groundGradient.setColorAt(1, QColor(107, 142, 35));
    QGraphicsRectItem *ground = new QGraphicsRectItem(0, 350, 1000, 250);
    ground->setBrush(QBrush(groundGradient));
    ground->setPen(QPen(Qt::NoPen));
    ground->setZValue(-150);
    scene->addItem(ground);

    createClouds();
    drawRailwayTrack();
    createTrees();
    createPowerPoles();
    createStationBuildings();

    locomotiveItem = new QGraphicsPixmapItem(currentLocomotiveImage);
    scene->addItem(locomotiveItem);
    locomotiveItem->setPos(locomotivePosition, 400);
    locomotiveItem->setZValue(100);

    drawFuelTank();

    QGraphicsRectItem *infoPanel = new QGraphicsRectItem(10, 10, 300, 120);
    infoPanel->setBrush(QBrush(QColor(255, 255, 255, 220)));
    infoPanel->setPen(QPen(Qt::darkGray, 2));
    infoPanel->setZValue(150);
    scene->addItem(infoPanel);

    modeTextItem = new QGraphicsTextItem("Режим: Дизель");
    modeTextItem->setDefaultTextColor(Qt::darkBlue);
    modeTextItem->setFont(QFont("Arial", 14, QFont::Bold));
    modeTextItem->setPos(20, 20);
    modeTextItem->setZValue(151);
    scene->addItem(modeTextItem);

    fuelLevelTextItem = new QGraphicsTextItem("Уровень топлива: 100%");
    fuelLevelTextItem->setDefaultTextColor(Qt::darkGreen);
    fuelLevelTextItem->setFont(QFont("Arial", 10));
    fuelLevelTextItem->setPos(20, 60);
    fuelLevelTextItem->setZValue(151);
    scene->addItem(fuelLevelTextItem);

    QGraphicsEllipseItem *sun = new QGraphicsEllipseItem(900, 20, 70, 70);
    sun->setBrush(QBrush(QColor(255, 255, 0, 200)));
    sun->setPen(QPen(QColor(255, 165, 0, 180), 2));
    sun->setZValue(-100);
    scene->addItem(sun);

    for (int i = 0; i < 8; i++) {
        double angle = i * 45 * 3.14159 / 180;
        int x1 = 935 + 40 * cos(angle);
        int y1 = 55 + 40 * sin(angle);
        int x2 = 935 + 60 * cos(angle);
        int y2 = 55 + 60 * sin(angle);
        QGraphicsLineItem *ray = new QGraphicsLineItem(x1, y1, x2, y2);
        ray->setPen(QPen(QColor(255, 165, 0, 150), 3));
        ray->setZValue(-101);
        scene->addItem(ray);
    }
}

void MainWindow::drawRailwayTrack() {
    QGraphicsRectItem *ballast = new QGraphicsRectItem(0, 440, 1000, 40);
    ballast->setBrush(QBrush(QColor(139, 69, 19)));
    ballast->setPen(QPen(Qt::NoPen));
    ballast->setZValue(10);
    scene->addItem(ballast);

    QPen railPen(QColor(50, 50, 50), 12);
    railPen.setCapStyle(Qt::FlatCap);

    QGraphicsLineItem *rail1 = new QGraphicsLineItem(0, 450, 1000, 450);
    rail1->setPen(railPen);
    rail1->setZValue(20);
    scene->addItem(rail1);

    QGraphicsLineItem *rail2 = new QGraphicsLineItem(0, 470, 1000, 470);
    rail2->setPen(railPen);
    rail2->setZValue(20);
    scene->addItem(rail2);

    QPen tiePen(QColor(101, 67, 33), 8);
    for (int x = 0; x < 1000; x += 50) {
        QGraphicsLineItem *tie = new QGraphicsLineItem(x, 445, x, 475);
        tie->setPen(tiePen);
        tie->setZValue(15);
        scene->addItem(tie);
    }

    QPen clipPen(QColor(100, 100, 100), 4);
    for (int x = 25; x < 1000; x += 50) {
        QGraphicsLineItem *clip1 = new QGraphicsLineItem(x, 450, x, 445);
        clip1->setPen(clipPen);
        clip1->setZValue(25);
        scene->addItem(clip1);

        QGraphicsLineItem *clip2 = new QGraphicsLineItem(x, 470, x, 475);
        clip2->setPen(clipPen);
        clip2->setZValue(25);
        scene->addItem(clip2);
    }
}

void MainWindow::drawFuelTank() {
    QRectF tankRect(850, 150, 120, 250);
    QGraphicsRectItem *tankOutline = new QGraphicsRectItem(tankRect);

    QLinearGradient tankGradient(850, 150, 970, 400);
    tankGradient.setColorAt(0, QColor(180, 180, 180));
    tankGradient.setColorAt(1, QColor(120, 120, 120));
    tankOutline->setBrush(QBrush(tankGradient));
    tankOutline->setPen(QPen(Qt::black, 3));
    tankOutline->setZValue(50);
    scene->addItem(tankOutline);

    QGraphicsEllipseItem *tankLid = new QGraphicsEllipseItem(905, 145, 10, 10);
    tankLid->setBrush(QBrush(QColor(80, 80, 80)));
    tankLid->setPen(QPen(Qt::black, 2));
    tankLid->setZValue(51);
    scene->addItem(tankLid);

    QGraphicsRectItem *tankStand = new QGraphicsRectItem(840, 400, 140, 25);
    tankStand->setBrush(QBrush(QColor(70, 70, 70)));
    tankStand->setPen(QPen(Qt::black, 2));
    tankStand->setZValue(49);
    scene->addItem(tankStand);

    for (int i = 0; i < 3; i++) {
        QGraphicsRectItem *leg = new QGraphicsRectItem(850 + i * 50, 425, 15, 25);
        leg->setBrush(QBrush(QColor(50, 50, 50)));
        leg->setPen(QPen(Qt::black, 1));
        leg->setZValue(48);
        scene->addItem(leg);
    }

    QGraphicsRectItem *gaugeWindow = new QGraphicsRectItem(860, 160, 100, 230);
    gaugeWindow->setBrush(QBrush(Qt::white));
    gaugeWindow->setPen(QPen(Qt::black, 2));
    gaugeWindow->setZValue(52);
    scene->addItem(gaugeWindow);

    if (fuelLevelItem) {
        scene->removeItem(fuelLevelItem);
        delete fuelLevelItem;
    }

    fuelLevelItem = new QGraphicsRectItem(0, 0, 100, 230 * currentFuelLevel);
    fuelLevelItem->setBrush(QBrush(QColor(0, 200, 0, 200)));
    fuelLevelItem->setPen(QPen(QColor(0, 150, 0), 1));
    fuelLevelItem->setPos(860, 160 + 230 * (1 - currentFuelLevel));
    fuelLevelItem->setZValue(53);
    scene->addItem(fuelLevelItem);

    QPen gaugePen(Qt::black, 1);
    for (int i = 0; i <= 4; i++) {
        int y = 160 + i * 57;
        QGraphicsLineItem *mark = new QGraphicsLineItem(850, y, 860, y);
        mark->setPen(gaugePen);
        mark->setZValue(54);
        scene->addItem(mark);

        QGraphicsLineItem *mark2 = new QGraphicsLineItem(960, y, 970, y);
        mark2->setPen(gaugePen);
        mark2->setZValue(54);
        scene->addItem(mark2);

        QGraphicsTextItem *label = new QGraphicsTextItem(QString::number(100 - i * 25) + "%");
        label->setDefaultTextColor(Qt::black);
        label->setFont(QFont("Arial", 8));
        label->setPos(970, y - 10);
        label->setZValue(54);
        scene->addItem(label);
    }
}

void MainWindow::createClouds() {
    QGraphicsEllipseItem *cloud1_part1 = new QGraphicsEllipseItem(50, 30, 70, 45);
    cloud1_part1->setBrush(QBrush(QColor(255, 255, 255, 180)));
    cloud1_part1->setPen(QPen(Qt::NoPen));
    cloud1_part1->setZValue(-120);
    scene->addItem(cloud1_part1);

    QGraphicsEllipseItem *cloud1_part2 = new QGraphicsEllipseItem(85, 20, 80, 55);
    cloud1_part2->setBrush(QBrush(QColor(255, 255, 255, 180)));
    cloud1_part2->setPen(QPen(Qt::NoPen));
    cloud1_part2->setZValue(-120);
    scene->addItem(cloud1_part2);

    QGraphicsEllipseItem *cloud1_part3 = new QGraphicsEllipseItem(120, 30, 70, 45);
    cloud1_part3->setBrush(QBrush(QColor(255, 255, 255, 180)));
    cloud1_part3->setPen(QPen(Qt::NoPen));
    cloud1_part3->setZValue(-120);
    scene->addItem(cloud1_part3);

    QGraphicsEllipseItem *cloud2_part1 = new QGraphicsEllipseItem(300, 50, 60, 35);
    cloud2_part1->setBrush(QBrush(QColor(255, 255, 255, 160)));
    cloud2_part1->setPen(QPen(Qt::NoPen));
    cloud2_part1->setZValue(-120);
    scene->addItem(cloud2_part1);

    QGraphicsEllipseItem *cloud2_part2 = new QGraphicsEllipseItem(330, 40, 80, 45);
    cloud2_part2->setBrush(QBrush(QColor(255, 255, 255, 160)));
    cloud2_part2->setPen(QPen(Qt::NoPen));
    cloud2_part2->setZValue(-120);
    scene->addItem(cloud2_part2);

    QGraphicsEllipseItem *cloud3_part1 = new QGraphicsEllipseItem(600, 60, 50, 30);
    cloud3_part1->setBrush(QBrush(QColor(255, 255, 255, 140)));
    cloud3_part1->setPen(QPen(Qt::NoPen));
    cloud3_part1->setZValue(-120);
    scene->addItem(cloud3_part1);

    QGraphicsEllipseItem *cloud3_part2 = new QGraphicsEllipseItem(630, 50, 60, 35);
    cloud3_part2->setBrush(QBrush(QColor(255, 255, 255, 140)));
    cloud3_part2->setPen(QPen(Qt::NoPen));
    cloud3_part2->setZValue(-120);
    scene->addItem(cloud3_part2);
}

void MainWindow::createTrees() {
    QGraphicsRectItem *tree1_trunk = new QGraphicsRectItem(80, 380, 18, 60);
    tree1_trunk->setBrush(QBrush(QColor(101, 67, 33)));
    tree1_trunk->setPen(QPen(Qt::NoPen));
    tree1_trunk->setZValue(30);
    scene->addItem(tree1_trunk);

    QGraphicsEllipseItem *tree1_crown = new QGraphicsEllipseItem(45, 340, 88, 70);
    tree1_crown->setBrush(QBrush(QColor(34, 139, 34, 200)));
    tree1_crown->setPen(QPen(Qt::NoPen));
    tree1_crown->setZValue(31);
    scene->addItem(tree1_crown);

    QGraphicsRectItem *tree2_trunk = new QGraphicsRectItem(400, 380, 15, 60);
    tree2_trunk->setBrush(QBrush(QColor(139, 69, 19)));
    tree2_trunk->setPen(QPen(Qt::NoPen));
    tree2_trunk->setZValue(30);
    scene->addItem(tree2_trunk);

    QGraphicsEllipseItem *tree2_crown = new QGraphicsEllipseItem(365, 340, 88, 70);
    tree2_crown->setBrush(QBrush(QColor(0, 100, 0, 220)));
    tree2_crown->setPen(QPen(Qt::NoPen));
    tree2_crown->setZValue(31);
    scene->addItem(tree2_crown);

    QGraphicsRectItem *tree3_trunk = new QGraphicsRectItem(750, 380, 12, 60);
    tree3_trunk->setBrush(QBrush(QColor(101, 67, 33)));
    tree3_trunk->setPen(QPen(Qt::NoPen));
    tree3_trunk->setZValue(30);
    scene->addItem(tree3_trunk);

    QGraphicsEllipseItem *tree3_crown = new QGraphicsEllipseItem(715, 350, 82, 60);
    tree3_crown->setBrush(QBrush(QColor(60, 179, 113, 180)));
    tree3_crown->setPen(QPen(Qt::NoPen));
    tree3_crown->setZValue(31);
    scene->addItem(tree3_crown);

    QGraphicsRectItem *tree4_trunk = new QGraphicsRectItem(200, 520, 14, 50);
    tree4_trunk->setBrush(QBrush(QColor(101, 67, 33)));
    tree4_trunk->setPen(QPen(Qt::NoPen));
    tree4_trunk->setZValue(30);
    scene->addItem(tree4_trunk);

    QGraphicsEllipseItem *tree4_crown = new QGraphicsEllipseItem(170, 490, 74, 50);
    tree4_crown->setBrush(QBrush(QColor(50, 205, 50, 190)));
    tree4_crown->setPen(QPen(Qt::NoPen));
    tree4_crown->setZValue(31);
    scene->addItem(tree4_crown);

    QGraphicsRectItem *tree5_trunk = new QGraphicsRectItem(650, 530, 16, 55);
    tree5_trunk->setBrush(QBrush(QColor(139, 69, 19)));
    tree5_trunk->setPen(QPen(Qt::NoPen));
    tree5_trunk->setZValue(30);
    scene->addItem(tree5_trunk);

    QGraphicsEllipseItem *tree5_crown = new QGraphicsEllipseItem(620, 500, 82, 60);
    tree5_crown->setBrush(QBrush(QColor(46, 139, 87, 200)));
    tree5_crown->setPen(QPen(Qt::NoPen));
    tree5_crown->setZValue(31);
    scene->addItem(tree5_crown);
}

void MainWindow::createPowerPoles() {
    for (int x = 200; x < 900; x += 250) {
        QGraphicsRectItem *pole = new QGraphicsRectItem(x, 270, 12, 170);
        pole->setBrush(QBrush(QColor(70, 70, 70)));
        pole->setPen(QPen(Qt::black, 1));
        pole->setZValue(-8);
        scene->addItem(pole);

        QGraphicsRectItem *crossbar = new QGraphicsRectItem(x - 50, 270, 112, 10);
        crossbar->setBrush(QBrush(QColor(50, 50, 50)));
        crossbar->setPen(QPen(Qt::black, 1));
        crossbar->setZValue(-7);
        scene->addItem(crossbar);

        for (int i = 0; i < 3; i++) {
            int insulatorX = x - 35 + i * 35;
            QGraphicsEllipseItem *insulator = new QGraphicsEllipseItem(insulatorX, 265, 10, 15);
            insulator->setBrush(QBrush(QColor(220, 220, 220)));
            insulator->setPen(QPen(Qt::black, 1));
            insulator->setZValue(-6);
            scene->addItem(insulator);
        }
    }

    for (int i = 0; i < 5; i++) {
        for (int wireNum = 0; wireNum < 3; wireNum++) {
            int startX = 250 * i + wireNum * 35 - 80;
            int endX = 250 * (i + 1) + wireNum * 35 - 80;

            drawPowerWire(startX, endX, 275, 275);
        }
    }
}

void MainWindow::drawPowerWire(int startX, int endX, int startY, int endY) {
    QPainterPath path;
    path.moveTo(startX, startY);

    int controlY = startY + 25;
    int control1X = startX + (endX - startX) / 3;
    int control2X = startX + 2 * (endX - startX) / 3;

    path.cubicTo(control1X, controlY, control2X, controlY, endX, endY);

    QGraphicsPathItem *wire = new QGraphicsPathItem(path);

    QPen wirePen(QColor(130, 130, 130), 2.5);
    wirePen.setCapStyle(Qt::RoundCap);
    wirePen.setJoinStyle(Qt::RoundJoin);
    wire->setPen(wirePen);
    wire->setZValue(50);
    scene->addItem(wire);
}

void MainWindow::createStationBuildings() {
    QGraphicsRectItem *stationMain = new QGraphicsRectItem(50, 240, 140, 120);
    QLinearGradient stationGrad(50, 240, 190, 360);
    stationGrad.setColorAt(0, QColor(210, 180, 140));
    stationGrad.setColorAt(1, QColor(180, 150, 110));
    stationMain->setBrush(QBrush(stationGrad));
    stationMain->setPen(QPen(QColor(139, 115, 85), 3));
    stationMain->setZValue(-30);
    scene->addItem(stationMain);

    QPolygonF roof;
    roof << QPointF(50, 240) << QPointF(120, 200) << QPointF(190, 240);
    QGraphicsPolygonItem *roofItem = new QGraphicsPolygonItem(roof);
    roofItem->setBrush(QBrush(QColor(139, 0, 0, 200)));
    roofItem->setPen(QPen(QColor(100, 0, 0), 2));
    roofItem->setZValue(-29);
    scene->addItem(roofItem);

    for (int i = 0; i < 3; i++) {
        QGraphicsRectItem *window = new QGraphicsRectItem(70 + i * 35, 270, 25, 35);
        window->setBrush(QBrush(QColor(173, 216, 230, 180)));
        window->setPen(QPen(QColor(70, 130, 180), 2));
        window->setZValue(-28);
        scene->addItem(window);

        QGraphicsLineItem *windowCross1 = new QGraphicsLineItem(70 + i * 35 + 12, 270, 70 + i * 35 + 12, 305);
        windowCross1->setPen(QPen(QColor(70, 130, 180), 1));
        windowCross1->setZValue(-27);
        scene->addItem(windowCross1);

        QGraphicsLineItem *windowCross2 = new QGraphicsLineItem(70 + i * 35, 287, 95 + i * 35, 287);
        windowCross2->setPen(QPen(QColor(70, 130, 180), 1));
        windowCross2->setZValue(-27);
        scene->addItem(windowCross2);
    }

    QGraphicsRectItem *door = new QGraphicsRectItem(110, 310, 30, 50);
    door->setBrush(QBrush(QColor(101, 67, 33)));
    door->setPen(QPen(QColor(70, 45, 20), 2));
    door->setZValue(-28);
    scene->addItem(door);

    QGraphicsEllipseItem *doorKnob = new QGraphicsEllipseItem(135, 330, 5, 5);
    doorKnob->setBrush(QBrush(QColor(200, 200, 0)));
    doorKnob->setPen(QPen(Qt::black, 1));
    doorKnob->setZValue(-27);
    scene->addItem(doorKnob);

    QGraphicsRectItem *sign = new QGraphicsRectItem(90, 220, 60, 20);
    sign->setBrush(QBrush(QColor(255, 255, 255, 220)));
    sign->setPen(QPen(Qt::darkRed, 2));
    sign->setZValue(-25);
    scene->addItem(sign);

    QGraphicsTextItem *signText = new QGraphicsTextItem("СТАНЦИЯ");
    signText->setDefaultTextColor(Qt::darkRed);
    signText->setFont(QFont("Comic Sans MS", 8, QFont::Bold));
    signText->setPos(88, 220);
    signText->setZValue(-24);
    scene->addItem(signText);
}

void MainWindow::onAnimationTimer() {
    locomotivePosition += 1.5;
    if (locomotivePosition > 1000) {
        locomotivePosition = -150;
    }
    locomotiveItem->setPos(locomotivePosition, 400);

    statusBar()->showMessage(QString("Локомотив движется. Позиция: %1").arg(locomotivePosition));
}

void MainWindow::onFuelConsumptionTimer() {
    if (currentFuelLevel > 0) {
        currentFuelLevel -= 0.002;
        if (currentFuelLevel < 0) currentFuelLevel = 0;
        updateFuelTankVisual();
        if (currentFuelLevel <= 0.01 && isAnimationRunning) {
            animationTimer->stop();
            fuelConsumptionTimer->stop();
            isAnimationRunning = false;

            QMessageBox::warning(this, "Топливо закончилось",
                                 "Топливный бак пуст! Анимация остановлена.\n\n"
                                 "Заправьте топливо для продолжения.");
            statusBar()->showMessage("Топливо закончилось! Анимация остановлена");
        } else if (currentFuelLevel <= 0.01) {
            statusBar()->showMessage("Топливо на исходе! Нажмите правой кнопкой для заправки.");
        }
    }
}

void MainWindow::refuel() {
    currentFuelLevel = 1.0;
    updateFuelTankVisual();
    statusBar()->showMessage("Топливный бак заправлен");

    if (!isAnimationRunning) {
        statusBar()->showMessage("Топливный бак заправлен. Можно запустить анимацию.");
    }
}

void MainWindow::updateFuelTankVisual() {
    currentLocomotiveImage = dieselLocomotiveImage;

    if (locomotiveItem && !currentLocomotiveImage.isNull()) {
        locomotiveItem->setPixmap(currentLocomotiveImage);
    }

    if (fuelLevelItem) {
        fuelLevelItem->setRect(0, 0, 100, 230 * currentFuelLevel);
        fuelLevelItem->setPos(860, 160 + 230 * (1 - currentFuelLevel));
        fuelLevelItem->setBrush(QBrush(QColor(0, 200, 0, 200)));
    }

    if (fuelLevelTextItem) {
        int fuelPercent = static_cast<int>(currentFuelLevel * 100);
        fuelLevelTextItem->setPlainText(QString("Уровень топлива: %1%").arg(fuelPercent));
    }

    if (modeTextItem) {
        modeTextItem->setPlainText("Режим: Дизель");
    }
}

void MainWindow::toggleAnimation() {
    if (isAnimationRunning) {
        animationTimer->stop();
        fuelConsumptionTimer->stop();
        statusBar()->showMessage("Анимация приостановлена");
        isAnimationRunning = false;
    } else {
        if (currentFuelLevel <= 0.01) {
            QMessageBox::warning(this, "Нет топлива", "Топливный бак пуст! Заправьте топливо перед запуском анимации.\n\n"
                                                      "Нажмите правой кнопкой мыши на локомотиве или топливном баке для заправки.");
            statusBar()->showMessage("Невозможно запустить анимацию: топливный бак пуст");
            return;
        }

        animationTimer->start(30);
        fuelConsumptionTimer->start(80);
        statusBar()->showMessage("Анимация запущена");
        isAnimationRunning = true;
    }
}

void MainWindow::resetAnimation() {
    locomotivePosition = 0.0;
    if (locomotiveItem) {
        locomotiveItem->setPos(locomotivePosition, 400);
    }

    if (isAnimationRunning) {
        animationTimer->stop();
        fuelConsumptionTimer->stop();
        isAnimationRunning = false;
        statusBar()->showMessage("Анимация сброшена");
    } else {
        statusBar()->showMessage("Позиция локомотива сброшена. Уровень топлива: " + QString::number(static_cast<int>(currentFuelLevel * 100)) + "%");
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space) {
        toggleAnimation();
        event->accept();
    } else if (event->key() == Qt::Key_R) {
        resetAnimation();
        event->accept();
    } else if (event->key() == Qt::Key_F) {
        refuel();
        event->accept();
    } else {
        QMainWindow::keyPressEvent(event);
    }
}
