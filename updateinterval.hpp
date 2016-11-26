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
