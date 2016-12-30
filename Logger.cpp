#include "Logger.hpp"

std::mutex Logger::mutex_;

Logger::~Logger()
{
  flushLogger();
}

Logger&
Logger::operator<<(Logger::FlushType)
{
  flushLogger();
  return *this;
}

Logger&
Logger::operator<<(Logger::EndlType)
{
  return (*this << "\n");
}

void
Logger::flushLogger()
{
  {
    std::lock_guard<std::mutex> lock(mutex_);
    std::cout << bufferStream_.str() << std::flush;
    // also write to file here
  }
  bufferStream_.str("");
  bufferStream_.clear();
}
