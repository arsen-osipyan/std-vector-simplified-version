#ifndef TRACER_H
#define TRACER_H 1


#include <string>


class Tracer
{
public:
  Tracer (const char *func_name, const char *file, int line);
  ~Tracer();

private:
  static int level;
  std::string func;

  std::string indent () const;

  // disallow copying
  Tracer (const Tracer &) = delete;
  Tracer & operator = (const Tracer &) = delete;
};


#define TRACE(name) Tracer tracer_object((name), __FILE__, __LINE__)
#define TRACE_FUNC TRACE(__func__)


#endif // #ifndef TRACER_H
