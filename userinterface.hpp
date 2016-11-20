#ifndef USERINTERFACE_HPP_
#define USERINTERFACE_HPP_

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


class UserInterface : public QObject {
    Q_OBJECT

  public:
    UserInterface(int &argc,char** const argv);

    void create();
    void fillList(const std::vector<ListEntry> &list_entries);
    void setTags(std::string &);
    void show();

    std::function<void(int row)> row_clicked_func;
    std::function<void()>        update_func;

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

#endif /* USERINTERFACE_HPP_ */
