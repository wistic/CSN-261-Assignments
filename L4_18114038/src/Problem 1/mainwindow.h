#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QRegExp>
#include <QPushButton>
#include <QDir>

namespace Ui {
class MainWindow;
}
struct TrieNode {
  public:
    bool isLeaf;
    QHash<QChar, TrieNode*> hashmap;
    QString meaning;

    TrieNode(){
        isLeaf = false;
    }
};



class Trie{
public:
        TrieNode *head;

        Trie() {
            head = nullptr;
        }

        void insertNode(QString word, QString meaning){

            if (head == nullptr)
                head = new TrieNode();

            TrieNode* temp = head;
            for (int i = 0; i < word.length(); i++) {
                QChar x = word[i];


                if (temp->hashmap.find(x) == temp->hashmap.end())
                    temp->hashmap[x] = new TrieNode();

                temp = temp->hashmap[x];
            }

            temp->isLeaf = true;
            temp->meaning = meaning;
        }


        QString getMeaning(QString word){

            if (head == nullptr)
                return "";

            TrieNode* temp = head;

            for (int i = 0; i < word.length(); i++) {
                temp = temp->hashmap[word[i]];
                if (temp == nullptr)
                    return "Invalid Word";
            }

            if (temp->isLeaf)
                return temp->meaning;
            return "invalid Word";
        }
};
//        void insertNode(QString word, QString meaning){

//            if (root == nullptr)
//                root = new TrieNode();

//            ListNode* temp = root->head;
//            TrieNode* ntemp=root;
//            for (int i = 0; i < word.length(); i++) {
//                QChar x = word[i];
//                if (temp!=nullptr){
//                    if (temp->c!=x)
//                        temp=temp->next;
//                    else {
//                        ntemp=temp->node;
//                        if (ntemp!=nullptr)
//                            temp=temp->node->head;
//                        else {
//                            ntemp=new TrieNode();
//                            temp->node=ntemp;
//                            temp=ntemp->head;
//                        }
//                    }
//                }
//                else {
//                    temp=new ListNode();
//                    temp->c=x;
//                    if (i==word.length()-1)
//                    {
//                        ntemp->isLeaf = true;
//                        ntemp->meaning = meaning;
//                    }
//                    ntemp=new TrieNode();
//                    ntemp->head=new ListNode();
//                }

//                /*f (temp->map.find(x) == temp->map.end())
//                    temp->map[x] = new TrieNode();*/
//            }
//        }




class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void generateTrie(QString filename);
        Trie trie;
    public slots:
            void SearchMeaning();

private:
    Ui::MainWindow *ui;
    QPushButton *searchButton;
};

#endif // MAINWINDOW_H
