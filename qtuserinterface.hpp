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
#include <QComboBox>
#include "listentries.hpp"
#include "userinterface.hpp"


struct QtTableWidget : QTableWidget {
  QSize size_hint;

  virtual QSize sizeHint() const override
  {
    return size_hint;
  }
};


class QtUserInterface : public QObject, public UserInterface {
    Q_OBJECT

  public:
    QtUserInterface(int &argc,char** const argv);

    void setUpdateOptions(const UpdateOptions &) override;
    void setListEntries(const ListEntries &list_entries) override;
    std::string tagsString() override;
    void setTagsString(const std::string &) override;
    void enableTimeouts();
    void show() override;
    OptionalListIndex selectedListIndex() override;
    void setSelectedListIndex(OptionalListIndex) override;
    void setSelectedUpdateOption(int index) override;
    void setStatusMessage(const std::string &) override;

  private:
    QApplication app;
    QWidget widget;
    QVBoxLayout layout;
    QHBoxLayout tags_layout;
    QLabel tags_label{"Tags:"};
    QLineEdit tags_field;
    QPushButton update_button{"Update Now"};
    QHBoxLayout update_layout;
    QLabel update_label{"Automatic Update Interval:"};
    QComboBox update_combo_box;
    QLabel status_label;
    QTimer timer;
    QtTableWidget list;
    bool first_set = true;

    void setCellText(int row,int col,const std::string &text,bool is_new);

  private slots:
    void updateCallback();
    void rowDoubleClicked(QTableWidgetItem*);
    void timeoutCallback();
    void updateOptionActivated(int index);
    void listSelectionChanged();
};

#endif /* QTUSERINTERFACE_HPP_ */
