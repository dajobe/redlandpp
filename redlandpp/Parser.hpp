/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * Parser.cpp - Redland C++ Parser class interface
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

#ifndef REDLANDPP_PARSER_HPP
#define REDLANDPP_PARSER_HPP

#include <string>

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

  class Parser : public Wrapper<librdf_parser> {
  public:
    Parser(World* w, const std::string name) throw(Exception);
    Parser(World* w, Uri* uri, std::string mime_type, const std::string buffer, const std::string identifier) throw(Exception);
    ~Parser();

    const std::string name() const;
    const std::string str() const;

    librdf_parser* parser() const;

    Stream* parseString(std::string str, Uri* uri, Uri* base_uri) throw(Exception);
    Stream* parseUri(Uri* uri, Uri* base_uri) throw(Exception);

  protected:
    World* world_;

  private:
    std::string name_;

    friend std::ostream& operator<< (std::ostream& os, const Parser& p);
    friend std::ostream& operator<< (std::ostream& os, const Parser* p);
  };

} // namespace Redland

#endif
