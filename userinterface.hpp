#ifndef USERINTERFACE_HPP_
#define USERINTERFACE_HPP_

#include "listentries.hpp"
#include "updateinterval.hpp"


class UserInterface {
  public:
    static const int no_list_index = -1;

    using OptionalListIndex = int;

    struct UpdateOption {
      std::string text;
      UpdateInterval interval;
    };

    using UpdateOptions = std::vector<UpdateOption>;

    struct EventHandler {
      virtual void rowClicked(size_t) = 0;
      virtual void updatePressed() = 0;
      virtual void timeoutOccurred() = 0;
      virtual void updateOptionSelected(int) = 0;
    };

    void setEventHandler(EventHandler* event_handler_ptr);

    EventHandler *event_handler_ptr = 0;

    EventHandler& eventHandler();

    virtual void setUpdateOptions(const UpdateOptions &) = 0;
    virtual void setStatusMessage(const std::string &) = 0;
    virtual void setSelectedUpdateOption(int index) = 0;
    virtual OptionalListIndex selectedListIndex() = 0;
    virtual void setSelectedListIndex(OptionalListIndex) = 0;
    virtual void setTagsString(const std::string &) = 0;
    virtual std::string tagsString() = 0;
    virtual void show() = 0;
    virtual void setListEntries(const ListEntries &list_entries) = 0;
    virtual void enableTimeouts() = 0;
};

#endif /* USERINTERFACE_HPP_ */
