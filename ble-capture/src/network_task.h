#ifndef NETWORK_TASK_H
#define NETWORK_TASK_H

class NetworkTask {
public:
  virtual void connect() = 0;
  virtual void sendData() = 0;
};

#endif // NETWORK_TASK_H