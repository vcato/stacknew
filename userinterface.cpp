#include "userinterface.hpp"

#include <iostream>
#include <QHeaderView>


using std::string;
using std::vector;
using std::cerr;


UserInterface::UserInterface(int &argc,char** const argv)
: app(argc,argv)
{
}


void UserInterface::create()
{
  widget.setLayout(&layout);
  layout.addLayout(&tags_layout);
  tags_layout.addWidget(&tags_label);
  tags_layout.addWidget(&tags_field);
  layout.addWidget(&update_button);
  layout.addWidget(&list);
  connect(&update_button,SIGNAL(clicked()),SLOT(updatePressed()));
  connect(
    &list,
    SIGNAL(itemDoubleClicked(QTableWidgetItem*)),
    SLOT(rowDoubleClicked(QTableWidgetItem*))
  );
}


void UserInterface::setCellText(int row,int col,const string &text,bool is_new)
{
  auto* item_ptr = new QTableWidgetItem(text.c_str());

  if (is_new) {
    item_ptr->setBackground(Qt::yellow);
  }

  list.setItem(row,col,item_ptr);
}


void UserInterface::fillList(const vector<ListEntry> &list_entries)
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


void UserInterface::show()
{
  widget.show();
  app.exec();
}


void UserInterface::updatePressed()
{
  update_func();
}


void UserInterface::rowDoubleClicked(QTableWidgetItem* item_ptr)
{
  row_clicked_func(list.row(item_ptr));
}


void UserInterface::setTags(std::string &arg)
{
  tags_field.setText(arg.c_str());
}
