/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * World.cc - Redland World class
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

  World::World()
  {
    librdf_world* w = librdf_new_world();
    if(w) {
      librdf_world_open(w);
      world_ = new Wrapper<librdf_world>((redland_object_free*)librdf_free_world,
                                         w);
    }
  }

  World::~World()
  {
  }

  librdf_world* World::world()
  {
    return world_->redland_obj();
  }

} // namespace Redland
