// Copyright (c) 2005  Tel-Aviv University (Israel).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$ $Date$
// 
//
// Author(s)     : Baruch Zukerman <baruchzu@post.tau.ac.il>

#ifndef GPS_DIFFERENCE_FUNCTOR
#define GPS_DIFFERENCE_FUNCTOR

#include <CGAL/Boolean_set_operations_2/Gps_base_functor.h>

CGAL_BEGIN_NAMESPACE

template <class Arrangement_>
class Gps_difference_functor : public Gps_base_functor<Arrangement_>
{
public:
  typedef Arrangement_                                    Arrangement_2;

  typedef typename Arrangement_2::Face_const_handle       Face_const_handle;
  typedef typename Arrangement_2::Face_handle             Face_handle;
 


  void create_face (Face_const_handle f1,
                    Face_const_handle f2,
                    Face_handle res_f)
  {
     if(f1->contained() && !f2->contained())
     {
       res_f->set_contained(true);
     }
  }

};


CGAL_END_NAMESPACE

#endif
