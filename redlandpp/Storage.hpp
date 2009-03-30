/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * Storage.cpp - Redland C++ Storage class interface
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

#ifndef REDLANDPP_STORAGE_HPP
#define REDLANDPP_STORAGE_HPP

#ifdef HAVE_CONFIG_H
#include <redlandpp_config.h>
#endif

#include <redland.h>

#include "redlandpp/World.hpp"
#include "redlandpp/Exception.hpp"
#include "redlandpp/Wrapper.hpp"
#include "redlandpp/Stream.hpp"
#include "redlandpp/Uri.hpp"

namespace Redland {

  class Storage : public Wrapper<librdf_storage> {
  public:
    Storage(World* w, const std::string& sn, const std::string& n="", const std::string& opts="") throw(Exception);
    Storage(World& w, const std::string& sn, const std::string& n="", const std::string& opts="") throw(Exception);

    ~Storage();

    // public methods
    const std::string name() const;

    const std::string str() const;

  protected:
    World* world_;

  private:
    std::string storage_name_;
    std::string name_;
    std::string options_;

    void init() throw(Exception);
    
    friend std::ostream& operator<< (std::ostream& os, const Storage& p);
    friend std::ostream& operator<< (std::ostream& os, const Storage* p);
  };


  class MemoryStorage : public Storage {
    public:
    MemoryStorage(World* w, const std::string n="", const std::string opts="") throw(Exception);
    MemoryStorage(World& w, const std::string n="", const std::string opts="") throw(Exception);

    ~MemoryStorage();
  };

} // namespace Redland

#endif
