//************************************************************
// Profiler.hpp
//
// Created on Thu Feb  6 20:32:14 2014 by Jan Comans
//
// Copyright 2014 Jan Comans -- jan@comans.be
//
// License: Boost Software License Version 1.0
// See LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt
//************************************************************

#ifndef _PROFILER_H_
#define _PROFILER_H_

#include <map>
#include <string>
#include <vector>

#include <boost/scoped_ptr.hpp>

////////////////////////////////////////////////////////////////////////////////
// The profiler
////////////////////////////////////////////////////////////////////////////////
class Profiler
{
public:
  Profiler();
  Profiler(const Profiler& other);
  ~Profiler();
  void clear();
  void tick();
  void incrementalTock(const char* tag);
  void dump(std::ostream& stream);

private:
  class Implementation;
  boost::scoped_ptr<Implementation> pimpl_;
};


////////////////////////////////////////////////////////////////////////////////
// The manager
////////////////////////////////////////////////////////////////////////////////
class usProfilerManager
{
public:
  static Profiler& get(const char* name)
  {
    static ProfilerMap the_map;
    return the_map[name];
  }
private:
  typedef std::map<std::string, Profiler> ProfilerMap;
};

#endif /* _PROFILER_H_ */
