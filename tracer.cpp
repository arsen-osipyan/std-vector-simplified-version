#include "tracer.h"
#include <iostream>


int Tracer::level = 0;

Tracer::Tracer (const char *func_name, const char *file, int line)
  : func{ func_name }
{
  std::cerr << indent() <<"IN  --> "<< func
            <<" ["<< file <<": "<< line <<"]"<< std::endl;
  ++level;
}

Tracer::~Tracer ()
{
  --level;
  std::cerr << indent() <<"OUT <-- "<< func << std::endl;
}

std::string Tracer::indent () const
{
  constexpr char tab[] = ". ";
  std::string space;

  for (int i = 0; i < level; ++i)
    space += tab;

  return space;
}
