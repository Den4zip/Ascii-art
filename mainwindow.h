#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QSpinBox>
#include <opencv2/opencv.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoadImage();
    void onWidthChanged(int width);

private:
    Ui::MainWindow *ui;
    QTextEdit *asciiOutput;
    QPushButton *loadButton;
    QSpinBox *widthSpinBox;
    cv::Mat lastImage;
    void updateAsciiArt();
};

#endif // MAINWINDOW_H
