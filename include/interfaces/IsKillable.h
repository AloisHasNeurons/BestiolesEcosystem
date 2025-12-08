#ifndef ISKILLABLE_H
#define ISKILLABLE_H

class IsKillable {
public:
  virtual ~IsKillable() {}
  virtual void kill(int delay) = 0;
};

#endif // ISKILLABLE_H