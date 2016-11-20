#ifndef QTUSERINTERFACE_HPP_
#define QTUSERINTERFACE_HPP_

#include <functional>
#include <vector>
#include <QApplication>
#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QBoxLayout>
#include <QLabel>
#include <QTimer>
#include "listentries.hpp"
#include "userinterface.hpp"



class QtUserInterface : public QObject, public UserInterface {
    Q_OBJECT

  public:
    QtUserInterface(int &argc,char** const argv);

    void fillList(const ListEntries &list_entries) override;
    std::string tagsString() override;
    void setTagsString(const std::string &) override;
    void enableTimeouts();
    void show() override;

  private:
    QApplication app;
    QWidget widget;
    QVBoxLayout layout;
    QHBoxLayout tags_layout;
    QLabel tags_label{"Tags:"};
    QLineEdit tags_field;
    QPushButton update_button{"Update"};
    QTimer timer;
    QTableWidget list;

    void setCellText(int row,int col,const std::string &text,bool is_new);

  private slots:
    void updateCallback();
    void rowDoubleClicked(QTableWidgetItem*);
    void timeoutCallback();
};

#endif /* QTUSERINTERFACE_HPP_ */
