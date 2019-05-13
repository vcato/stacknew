#include "qtuserinterface.hpp"

#include <iostream>
#include <cassert>
#include <QHeaderView>
#include "listentries.hpp"


using std::string;
using std::cerr;
using OptionalListIndex = UserInterface::OptionalListIndex;


template <typename Widget,typename... Args>
static Widget& createWidget(QBoxLayout &layout,const Args&... args)
{
  Widget *widget_ptr = new Widget(args...);
  layout.addWidget(widget_ptr);
  return *widget_ptr;
}


template <typename Layout>
static Layout& createLayout(QBoxLayout &parent_layout)
{
  Layout *layout_ptr = new Layout;
  parent_layout.addLayout(layout_ptr);
  return *layout_ptr;
}


template <typename Layout>
static Layout& createLayout(QWidget &parent_widget)
{
  Layout *layout_ptr = new Layout;
  parent_widget.setLayout(layout_ptr);
  return *layout_ptr;
}


QtUserInterface::QtUserInterface(int &argc,char** const argv)
: app(argc,argv)
{
  auto &layout = createLayout<QVBoxLayout>(widget);

  // Tags
  auto& tags_layout = createLayout<QHBoxLayout>(layout);
  createWidget<QLabel>(tags_layout,"Tags:");
  tags_field_ptr = &createWidget<QLineEdit>(tags_layout);

  // Update
  auto &update_layout = createLayout<QHBoxLayout>(layout);
  auto &update_button = createWidget<QPushButton>(update_layout,"Update Now");
  update_layout.addStretch();
  createWidget<QLabel>(update_layout,"Automatic Update Interval:");
  auto &update_combo_box = createWidget<QComboBox>(update_layout);
  update_combo_box_ptr = &update_combo_box;
  connect(&update_button,SIGNAL(clicked()),SLOT(updateCallback()));
  connect(
    &update_combo_box,
    SIGNAL(activated(int)),
    SLOT(updateOptionActivated(int))
  );

  // Status
  status_label_ptr = &createWidget<QLabel>(layout);

  // List
  auto &list = createWidget<QtTableWidget>(layout);
  list_ptr = &list;
  layout.setStretchFactor(list_ptr,1);
  list.setSelectionBehavior(QAbstractItemView::SelectRows);
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

  // Timer
  connect(&timer,SIGNAL(timeout()),SLOT(timeoutCallback()));
}


void
  QtUserInterface::setCellText(int row,int col,const string &text,bool is_new)
{
  auto* item_ptr = new QTableWidgetItem(text.c_str());

  if (is_new) {
    item_ptr->setBackground(Qt::yellow);
  }

  list().setItem(row,col,item_ptr);
}


string QtUserInterface::tagsString()
{
  return tagsField().text().toUtf8().constData();
}


void QtUserInterface::setListEntries(const ListEntries &list_entries)
{
  int n_entries = list_entries.size();
  QtTableWidget &list = this->list();
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

  // Calculate a good width the first time, so that the interface opens with
  // a good default size, but don't change it later since that would be
  // distracting.
  if (first_set) {
    list.resizeColumnsToContents();
    list.size_hint = list.size();
    first_set = false;
  }

#if QT_VERSION >= 0x050000
  list.horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeMode::Stretch);
#else
  list.horizontalHeader()->setResizeMode(0,QHeaderView::ResizeMode::Stretch);
#endif
  list.scrollToTop();
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
  eventHandler().rowClicked(list().row(item_ptr));
}


void QtUserInterface::setTagsString(const std::string &arg)
{
  tagsField().setText(arg.c_str());
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
    updateComboBox().addItem(option.description.c_str());
  }
}


void QtUserInterface::setSelectedUpdateOption(int index)
{
  updateComboBox().setCurrentIndex(index);
}


void QtUserInterface::setStatusMessage(const std::string &arg)
{
  statusLabel().setText(("Status: "+arg).c_str());
}


OptionalListIndex QtUserInterface::selectedListIndex()
{
  QItemSelectionModel *model_ptr = list().selectionModel();
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
    list().clearSelection();
  }
  else {
    list().selectRow(optional_index);
  }
}


void QtUserInterface::listSelectionChanged()
{
}
