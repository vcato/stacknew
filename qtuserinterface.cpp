#include "qtuserinterface.hpp"

#include <iostream>
#include <QHeaderView>
#include "listentries.hpp"


using std::string;
using std::cerr;


QtUserInterface::QtUserInterface(int &argc,char** const argv)
: app(argc,argv)
{
}


void QtUserInterface::create()
{
  widget.setLayout(&layout);
  layout.addLayout(&tags_layout);
  tags_layout.addWidget(&tags_label);
  tags_layout.addWidget(&tags_field);
  layout.addWidget(&update_button);
  layout.addWidget(&list);
  connect(&update_button,SIGNAL(clicked()),SLOT(updateCallback()));
  connect(
    &list,
    SIGNAL(itemDoubleClicked(QTableWidgetItem*)),
    SLOT(rowDoubleClicked(QTableWidgetItem*))
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


void QtUserInterface::fillList(const ListEntries &list_entries)
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
  list.resizeColumnsToContents();
  list.setFixedSize(
    list.horizontalHeader()->length() + 30,
    500
  );
}


void QtUserInterface::show()
{
  widget.show();
  app.exec();
}


void QtUserInterface::updateCallback()
{
  updatePressed();
}


void QtUserInterface::rowDoubleClicked(QTableWidgetItem* item_ptr)
{
  row_clicked_func(list.row(item_ptr));
}


void QtUserInterface::setTags(std::string &arg)
{
  tags_field.setText(arg.c_str());
}
