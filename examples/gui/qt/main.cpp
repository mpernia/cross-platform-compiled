#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include "../../../src/includes/logger.h"

class MainWindow : public QMainWindow
{
    public:
        MainWindow()
        {
            setWindowTitle("Cross-Platform C++ GUI Template");
            setMinimumSize(400, 300);

            QWidget* centralWidget = new QWidget(this);
            setCentralWidget(centralWidget);

            QVBoxLayout* layout = new QVBoxLayout(centralWidget);

            QLabel* titleLabel = new QLabel("Hello from Qt!", this);
            titleLabel->setAlignment(Qt::AlignCenter);
            titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; margin: 20px;");

            QLabel* infoLabel = new QLabel(
                "This is a cross-platform GUI application example using Qt.\n"
                "The same code compiles and runs on Linux, macOS, and Windows.",
                this
            );
            infoLabel->setAlignment(Qt::AlignCenter);
            infoLabel->setWordWrap(true);

            QPushButton* logButton = new QPushButton("Log Message", this);
            connect(logButton, &QPushButton::clicked, this, &MainWindow::logMessage);

            QPushButton* quitButton = new QPushButton("Quit", this);
            connect(quitButton, &QPushButton::clicked, qApp, &QApplication::quit);

            layout->addWidget(titleLabel);
            layout->addWidget(infoLabel);
            layout->addWidget(logButton);
            layout->addWidget(quitButton);
            layout->addStretch();
        }

    private slots:
        void logMessage()
        {
            Logger::info("Button clicked in Qt GUI!");
        }
};

int main(int argc, char *argv[])
{
    Logger::setLevel(LogLevel::DEBUG);
    Logger::info("Starting Qt application");
    
    QApplication app(argc, argv);
    
    MainWindow window;
    window.show();
    
    int result = app.exec();
    
    Logger::info("Qt application exiting");
    return result;
}
