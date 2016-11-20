#ifndef USERINTERFACE_HPP_
#define USERINTERFACE_HPP_

#include "listentries.hpp"


class UserInterface {
  public:
    struct UpdateInterval {
      bool is_none = true;
      int interval_in_minutes = 0;

      bool isNone() const { return is_none; }
      int inMinutes() const { return interval_in_minutes; }

      static UpdateInterval inMinutes(int n_minutes)
      {
        UpdateInterval result;
        result.is_none = false;
        result.interval_in_minutes = n_minutes;
        return result;
      }

      static UpdateInterval none()
      {
        UpdateInterval result;
        result.is_none = true;
        result.interval_in_minutes = 0;
        return result;
      }
    };

    struct UpdateOption {
      std::string text;
      UpdateInterval interval;
    };

    using UpdateOptions = std::vector<UpdateOption>;

    struct EventHandler {
      using UpdateInterval = UserInterface::UpdateInterval;

      virtual void rowClicked(size_t) = 0;
      virtual void updatePressed() = 0;
      virtual void timeoutOccurred() = 0;
      virtual void updateOptionSelected(int) = 0;
    };

    void setEventHandler(EventHandler* event_handler_ptr);

    EventHandler *event_handler_ptr = 0;

    EventHandler& eventHandler();

    virtual void setUpdateOptions(const UpdateOptions &) = 0;
    virtual void setTagsString(const std::string &) = 0;
    virtual std::string tagsString() = 0;
    virtual void show() = 0;
    virtual void fillList(const ListEntries &list_entries) = 0;
    virtual void enableTimeouts() = 0;
};

#endif /* USERINTERFACE_HPP_ */
