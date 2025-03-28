#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imageconverter.h"
#include <QFileDialog>
#include <QVBoxLayout>
#include <QFileInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Инициализация интерфейса
    asciiOutput = new QTextEdit(this);
    asciiOutput->setReadOnly(true);
    asciiOutput->setFont(QFont("Courier New", 10));  // Увеличенный размер шрифта
    asciiOutput->setLineWrapMode(QTextEdit::NoWrap); // Отключение переноса строк

    loadButton = new QPushButton("Load Image", this);
    widthSpinBox = new QSpinBox(this);
    widthSpinBox->setRange(40, 200);
    widthSpinBox->setValue(120);  // Увеличенная стартовая ширина
    widthSpinBox->setPrefix("Width: ");

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(asciiOutput);
    layout->addWidget(loadButton);
    layout->addWidget(widthSpinBox);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Подключение сигналов
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::onLoadImage);
    connect(widthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::onWidthChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLoadImage()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Open Image",
        QDir::homePath(),
        "Images (*.png *.jpg *.jpeg *.bmp)"
        );

    if(filePath.isEmpty()) return;

    QFileInfo fileInfo(filePath);
    if(fileInfo.isDir()) {
        asciiOutput->setPlainText("Error: Selected path is a directory");
        return;
    }

    lastImage = cv::imread(filePath.toStdString(), cv::IMREAD_COLOR);
    if(lastImage.empty()) {
        asciiOutput->setPlainText("Error: Failed to load image\n" + filePath);
        return;
    }

    updateAsciiArt();
}

void MainWindow::onWidthChanged(int width)
{
    Q_UNUSED(width);
    if(!lastImage.empty()) {
        updateAsciiArt();
    }
}

void MainWindow::updateAsciiArt()
{
    int width = widthSpinBox->value();
    std::string asciiArt = ImageConverter::convertToAscii(lastImage, width);
    asciiOutput->setPlainText(QString::fromStdString(asciiArt));
}
