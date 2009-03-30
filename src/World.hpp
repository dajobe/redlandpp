/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * World.hpp - Redland++ World class interface
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

#ifndef REDLANDPP_WORLD_HPP
#define REDLANDPP_WORLD_HPP

#include <redland.h>

#include <Exception.hpp>
#include <Wrapper.hpp>
#include <Uri.hpp>
#include <Node.hpp>

namespace Redland {

  class World : public Wrapper<librdf_world> {
    public:
      // default constructor
      World();

      // destructor
      ~World();

      Node* feature(Uri* feature) throw(Exception);
      void setFeature(Uri* feature, Node* value) throw(Exception);

      const std::string shortCopyrightString() const;
      const std::string copyrightString() const;
      const std::string versionString() const;
      int versionMajor() const;
      int versionMinor() const;
      int versionRelease() const;
      int versionDecimal() const;

    protected:
      std::string error_;

      void reset_error()     throw();
      void check_and_throw() throw(Exception);
      
    private:
      friend class Model;
      friend class Parser;
      friend class Serializer;
      friend class Storage;
      friend int redland_world_log_handler(void *user_data, librdf_log_message *log);
      friend std::ostream& operator<< (std::ostream& os, const World& world);
  };

} // namespace Redland

#endif
