#include <cassert>

class UpdateInterval {
  public:
    bool isNone() const { return interval_in_minutes==no_interval; }

    int inMinutes() const
    {
      assert(interval_in_minutes!=no_interval);
      return interval_in_minutes;
    }

    static UpdateInterval fromMinutes(int n_minutes)
    {
      assert(n_minutes>=0);
      assert(n_minutes!=no_interval);
      UpdateInterval result;
      result.interval_in_minutes = n_minutes;
      return result;
    }

    static UpdateInterval none()
    {
      UpdateInterval result;
      result.interval_in_minutes = no_interval;
      return result;
    }

  private:
    static const int no_interval = 0;
    int interval_in_minutes = no_interval;
};
