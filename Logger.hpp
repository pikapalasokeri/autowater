#ifndef Logger_hpp
#define Logger_hpp

#include <mutex>
#include <sstream>
#include <iostream>

class Logger
{
public:
  Logger() {}
  
  Logger(const std::string& filePath,
	 const std::string& stdOutPrefix);

  ~Logger();

  class FlushType {};
  class EndlType {};

  static FlushType flush;
  static EndlType endl;

  Logger& operator<<(FlushType);
  Logger& operator<<(EndlType);
  
  template <class T>
  Logger& operator<<(const T& obj)
  {
    bufferStream_ << obj;
    return *this;
  }
  
private:
  void flushLogger();
  
  std::ostringstream bufferStream_;
  static std::mutex mutex_;
};

#endif
