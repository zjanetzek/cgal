// Copyright (c) 2002 Utrecht University (The Netherlands).
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
// Author(s)     : Hans Tangelder (<hanst@cs.uu.nl>)


#ifndef CGAL_MANHATTAN_DISTANCE_ISO_BOX_POINT_H
#define CGAL_MANHATTAN_DISTANCE_ISO_BOX_POINT_H

#include <CGAL/Kd_tree_rectangle.h>

namespace CGAL {

  template <class SearchTraits>
  class Manhattan_distance_iso_box_point {

    public:

    typedef typename SearchTraits::Point_d Point_d;
    typedef typename SearchTraits::Iso_box_d Iso_box_d;
    typedef typename SearchTraits::FT    FT;
    typedef Iso_box_d                  Query_item;

    
    Manhattan_distance_iso_box_point() {}
      
    
    // obsolete as we no longer store dimension Manhattan_distance_iso_box_point(const int d) : the_dimension(d) {}

    //copy constructor
    Manhattan_distance_iso_box_point(const Manhattan_distance_iso_box_point& d) {}

    ~Manhattan_distance_iso_box_point() {}

    inline FT transformed_distance(const Query_item& q, const Point_d& p) {
		FT distance = FT(0);
		typename SearchTraits::Construct_cartesian_const_iterator_d construct_it;
		typename SearchTraits::Construct_min_vertex_d construct_min_vertex;
		typename SearchTraits::Construct_max_vertex_d construct_max_vertex;
                typename SearchTraits::Cartesian_const_iterator_d qmaxit = construct_it(construct_max_vertex(q)),
		  qe = construct_it(construct_max_vertex(q),1), qminit = construct_it(construct_min_vertex(q)),
		  pit = construct_it(p);
		for (; qmaxit != qe; ++pit,++qmaxit,++qminit) {
			if ((*pit)>(*qmaxit)) distance += 
			(*pit)-(*qmaxit); 
			else if ((*pit)<(*qminit)) distance += 
			(*qminit)-(*pit);	
		}
        	return distance;
    }


    inline FT min_distance_to_rectangle(const Query_item& q,
					      const Kd_tree_rectangle<SearchTraits>& r) {
		FT distance = FT(0);
		typename SearchTraits::Construct_cartesian_const_iterator_d construct_it;
		typename SearchTraits::Construct_min_vertex_d construct_min_vertex;
		typename SearchTraits::Construct_max_vertex_d construct_max_vertex;
                typename SearchTraits::Cartesian_const_iterator_d qmaxit = construct_it(construct_max_vertex(q)),
		  qe = construct_it(construct_max_vertex(q),1), qminit = construct_it(construct_min_vertex(q));
		for (unsigned int i = 0; qmaxit != qe; ++ qmaxit, ++qminit, ++i)  {
			if (r.min_coord(i)>(*qmaxit)) 
			  distance +=(r.min_coord(i)-(*qmaxit)); 
			if (r.max_coord(i)<(*qminit)) 
			  distance += ((*qminit)-r.max_coord(i));
	        }
		return distance;
	}

    inline 
    FT 
    max_distance_to_rectangle(const Query_item& q,
			      const Kd_tree_rectangle<SearchTraits>& r) {
      FT distance=FT(0);
      typename SearchTraits::Construct_cartesian_const_iterator_d construct_it;
		typename SearchTraits::Construct_min_vertex_d construct_min_vertex;
		typename SearchTraits::Construct_max_vertex_d construct_max_vertex;
      typename SearchTraits::Cartesian_const_iterator_d qmaxit = construct_it(construct_max_vertex(q)),
	qe = construct_it(construct_max_vertex(q),1), qminit = construct_it(construct_min_vertex(q));
      for (unsigned int i = 0; qmaxit != qe; ++ qmaxit, ++qminit, ++i)  {
	if ( r.max_coord(i)-(*qminit) >(*qmaxit)-r.min_coord(i) )  
	  distance += (r.max_coord(i)-(*qminit));
	else 
	  distance += ((*qmaxit)-r.min_coord(i));
      }
      return distance;
    }
	
  inline 
  FT 
  transformed_distance(FT d) 
  {
    return d;
  }

  inline 
  FT 
  inverse_of_transformed_distance(FT d) 
  {
    return d;
  }

}; // class Manhattan_distance_iso_box_point

} // namespace CGAL
#endif // MANHATTAN_DISTANCE_ISO_BOX_POINT_H
