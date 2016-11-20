#include "qtuserinterface.hpp"

#include <iostream>
#include <cassert>
#include <QHeaderView>
#include "listentries.hpp"


using std::string;
using std::cerr;
using OptionalListIndex = UserInterface::OptionalListIndex;


QtUserInterface::QtUserInterface(int &argc,char** const argv)
: app(argc,argv)
{
  widget.setLayout(&layout);
  layout.addLayout(&tags_layout);
  tags_layout.addWidget(&tags_label);
  tags_layout.addWidget(&tags_field);
  update_layout.addWidget(&update_button);
  update_layout.addStretch();
  update_layout.addWidget(&update_label);
  update_layout.addWidget(&update_combo_box);
  layout.addLayout(&update_layout);
  list.setSelectionBehavior(QAbstractItemView::SelectRows);
  layout.addWidget(&list);
  connect(&update_button,SIGNAL(clicked()),SLOT(updateCallback()));
  connect(
    &list,
    SIGNAL(itemDoubleClicked(QTableWidgetItem*)),
    SLOT(rowDoubleClicked(QTableWidgetItem*))
  );
  connect(
    &list,
    SIGNAL(itemSelectionChanged()),
    SLOT(listSelectionChanged())
  );
  connect(&timer,SIGNAL(timeout()),SLOT(timeoutCallback()));
  connect(
    &update_combo_box,
    SIGNAL(activated(int)),
    SLOT(updateOptionActivated(int))
  );
}


void
  QtUserInterface::setCellText(int row,int col,const string &text,bool is_new)
{
  auto* item_ptr = new QTableWidgetItem(text.c_str());

  if (is_new) {
    item_ptr->setBackground(Qt::yellow);
  }

  list.setItem(row,col,item_ptr);
}


string QtUserInterface::tagsString()
{
  return tags_field.text().toUtf8().constData();
}


void QtUserInterface::setListEntries(const ListEntries &list_entries)
{
  int n_entries = list_entries.size();
  list.setRowCount(n_entries);
  list.setColumnCount(2);
  list.setHorizontalHeaderLabels({"Title","Date"});
  list.verticalHeader()->hide();

  for (int i=0; i!=n_entries; ++i) {
    const ListEntry &list_entry = list_entries[i];
    const string &title = list_entry.title;
    const string &creation_date_string = list_entry.creation_date;
    bool is_new = list_entry.is_new;

    setCellText(i,0,title,is_new);
    setCellText(i,1,creation_date_string,is_new);
  }

  list.setEditTriggers(QAbstractItemView::NoEditTriggers);

  // Prevent the list from changing width on subsequent updates.
  if (first_set) {
    list.resizeColumnsToContents();
    list.setFixedSize(
      list.horizontalHeader()->length() + 30,
      500
    );
    first_set = false;
  }
}


void QtUserInterface::enableTimeouts()
{
  int timeout_interval_in_seconds = 1;
  int timeout_interval_in_milliseconds = timeout_interval_in_seconds*1000;
  timer.start(timeout_interval_in_milliseconds);
}


void QtUserInterface::show()
{
  widget.show();
  app.exec();
}


void QtUserInterface::updateCallback()
{
  eventHandler().updatePressed();
}


void QtUserInterface::rowDoubleClicked(QTableWidgetItem* item_ptr)
{
  eventHandler().rowClicked(list.row(item_ptr));
}


void QtUserInterface::setTagsString(const std::string &arg)
{
  tags_field.setText(arg.c_str());
}


void QtUserInterface::timeoutCallback()
{
  eventHandler().timeoutOccurred();
}


void QtUserInterface::updateOptionActivated(int index)
{
  eventHandler().updateOptionSelected(index);
}


void QtUserInterface::setUpdateOptions(const UpdateOptions &update_options)
{
  for (const auto &option : update_options) {
    update_combo_box.addItem(option.text.c_str());
  }
}


OptionalListIndex QtUserInterface::selectedListIndex()
{
  QItemSelectionModel *model_ptr = list.selectionModel();
  assert(model_ptr);
  QModelIndexList selected_rows = model_ptr->selectedRows();
  if (selected_rows.size()==1) {
    return selected_rows[0].row();
  }
  return no_list_index;
}


void QtUserInterface::setSelectedListIndex(OptionalListIndex optional_index)
{
  if (optional_index==no_list_index) {
    list.clearSelection();
  }
  else {
    list.selectRow(optional_index);
  }
}


void QtUserInterface::listSelectionChanged()
{
}
