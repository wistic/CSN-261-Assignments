/**
* @file mainwindow.cpp
* @brief This Cpp file is a program used to find the maximum length of a subarray with a given sum..
*
* @author Prathamesh Katkar
*
* @date 04/09/2019
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
* This method MainWindow::MainWindow() will be the driver program for the Mainwindow.
* @param QWidget *parent
* @date 04/09/2019
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
       ui(new Ui::MainWindow)
   {
       QString path = QDir::currentPath();

       QStringList list = path.split("/");
       QString newPath = "";
       for(int i{0}; i < list.size()-1; i++) {
            newPath += list[i] + "/";
       }

       qDebug() << newPath;

       ui->setupUi(this);
       generateTrie(newPath + "Dictionary/L4_P1_input.csv");
       searchButton = ui->pushButton;
       connect(searchButton, SIGNAL(clicked()), this, SLOT(SearchMeaning()));
}

/**
* This method MainWindow::generateTrie() will be used to generate the trie.
* @param QString filename
* @date 04/09/2019
*/
Mai
void MainWindow::generateTrie(QString filename) {
    QFile file(filename);

    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Unable to open the specified file.";
        return;
    }
    QTextStream instream(&file);
    QString inputText;

    while((inputText = instream.readLine()) != "") {
        QString wordMeaning;
        QStringList data = inputText.split(",");
        for (int i = 1; i < data.size(); ++i){
                 wordMeaning.append(data[i]);
                 if (i != data.size()-1)
                     wordMeaning.append(", ");
        }
        trie.insertNode(data[0], wordMeaning);
    }
}

/**
* Calling the destructor for MainWindow
*/
Mai
MainWindow::~MainWindow()
{
    delete ui;
}
/**
* This method MainWindow::SearchMeaning() will be used to search Word Meaning in Trie.
* @param none
* @date 04/09/2019
*/
Mai
void MainWindow::SearchMeaning() {
    QString word = ui->lineEdit->text();
    word = word.trimmed();
    ui->label_3->clear();
    ui->label_3->setText(trie.getMeaning(word));
}
