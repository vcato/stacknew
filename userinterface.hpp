#ifndef USERINTERFACE_HPP_
#define USERINTERFACE_HPP_

#include <functional>
#include "listentries.hpp"


class UserInterface {
  public:
    std::function<void(int row)> row_clicked_func;
    std::function<void()>        update_func;
    std::function<void()>        timeout_func;

    virtual void setTagsString(const std::string &) = 0;
    virtual std::string tagsString() = 0;
    virtual void show() = 0;
    virtual void fillList(const ListEntries &list_entries) = 0;
    virtual void enableTimeouts() = 0;

    void updatePressed();
    void rowClicked(size_t row);
    void timeoutOccurred();
};

#endif /* USERINTERFACE_HPP_ */
