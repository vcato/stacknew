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


// We need to have our own TableWidget class so that we can have a custom
// size hint, which is the preferred size of the table.  We'll calculate the
// size hint based on the contents.
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
    QTimer timer;
    QLineEdit *tags_field_ptr = nullptr;
    QComboBox *update_combo_box_ptr = nullptr;
    QLabel *status_label_ptr = nullptr;
    QtTableWidget *list_ptr = nullptr;

    QLineEdit &tagsField()
    {
      assert(tags_field_ptr);
      return *tags_field_ptr;
    }

    QComboBox &updateComboBox()
    {
      assert(update_combo_box_ptr);
      return *update_combo_box_ptr;
    }

    QLabel &statusLabel()
    {
      assert(status_label_ptr);
      return *status_label_ptr;
    }

    QtTableWidget &list()
    {
      assert(list_ptr);
      return *list_ptr;
    }

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
