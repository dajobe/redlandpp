/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * World.cpp - Redland C++ World class
 *
 * Copyright (C) 2008, David Beckett http://www.dajobe.org/
 * 
 * This package is Free Software and part of Redland http://librdf.org/
 * 
 * It is licensed under the following three licenses as alternatives:
 *   1. GNU Lesser General Public License (LGPL) V2.1 or any newer version
 *   2. GNU General Public License (GPL) V2 or any newer version
 *   3. Apache License, V2.0 or any newer version
 * 
 * You may not use this file except in compliance with at least one of
 * the above three licenses.
 * 
 * See LICENSE.html or LICENSE.txt at the top of this package for the
 * complete terms and further detail along with the license texts for
 * the licenses in COPYING.LIB, COPYING and LICENSE-2.0.txt respectively.
 * 
 * 
 */


#ifdef HAVE_CONFIG_H
#include <redlandpp_config.h>
#endif

#include <World.hpp>


namespace Redland {

  using namespace std;

  int redland_world_log_handler(void *user_data, librdf_log_message *log)
  {
    World* world = (World*)user_data;
    world->error_ = std::string("Error: ") + log->message;
    return 0;
  }
  

  World::World() 
    : Redland::Wrapper<librdf_world>((redland_object_free*)librdf_free_world,
                                     librdf_new_world())
  {
    librdf_world_set_logger(cobj(), this, redland_world_log_handler);
  }


  World::~World()
  {
  }


  librdf_world* World::world()
  {
    return cobj();
  }


  void World::reset_error() throw()
  {
    error_ = "";
  }

  void World::check_and_throw()
    throw(Exception)
  {
    if(error_.size() > 0) {
      string e=error_;
      reset_error();
      throw Exception(e);
    }
  }


} // namespace Redland
