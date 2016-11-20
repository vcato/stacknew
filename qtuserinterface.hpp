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
#include "listentry.hpp"
#include "userinterface.hpp"



class QtUserInterface : public QObject, public UserInterface {
    Q_OBJECT

  public:
    QtUserInterface(int &argc,char** const argv);

    void create();
    void fillList(const std::vector<ListEntry> &list_entries) override;
    void setTags(std::string &) override;
    void show() override;

  private:
    QApplication app;
    QWidget widget;
    QVBoxLayout layout;
    QHBoxLayout tags_layout;
    QLabel tags_label{"Tags:"};
    QLineEdit tags_field;
    QPushButton update_button{"Update"};
    QTableWidget list;

    void setCellText(int row,int col,const std::string &text,bool is_new);

  private slots:
    void updatePressed();
    void rowDoubleClicked(QTableWidgetItem*);
};

#endif /* QTUSERINTERFACE_HPP_ */
