#ifndef ACTION_METHOD_H_
#define ACTION_METHOD_H_

#include <string>
#include <vector>

struct EncryptedMethod {
  enum MethodId {
    kWrongArg = 0,
    kMove = 1
  };

  std::string name;
  int id;
  std::vector<std::string> parameters = std::vector<std::string>(0);
};

#endif  // ACTION_METHOD_H_
