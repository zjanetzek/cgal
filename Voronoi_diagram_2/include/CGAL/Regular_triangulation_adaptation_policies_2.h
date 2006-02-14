// Copyright (c) 2005 Foundation for Research and Technology-Hellas (Greece).
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
// Author(s)     : Menelaos Karavelas <mkaravel@iacm.forth.gr>

#ifndef CGAL_REGULAR_TRIANGULATION_ADAPTATION_POLICIES_2_H
#define CGAL_REGULAR_TRIANGULATION_ADAPTATION_POLICIES_2_H 1

#include <CGAL/Voronoi_diagram_2/basic.h>
#include <CGAL/Voronoi_diagram_2/Regular_triangulation_degeneracy_testers.h>
#include <CGAL/Voronoi_diagram_2/Policy_base.h>
#include <CGAL/Voronoi_diagram_2/Default_site_inserters.h>
#include <CGAL/Voronoi_diagram_2/Identity_rejectors.h>

#include <CGAL/Identity_policy_2.h>

CGAL_BEGIN_NAMESPACE

//=========================================================================
//=========================================================================

template<class RT2>
struct Regular_triangulation_degeneracy_removal_policy_2
  : public CGAL_VORONOI_DIAGRAM_2_INS::Policy_base
  <RT2,
   CGAL_VORONOI_DIAGRAM_2_INS::Regular_triangulation_edge_tester_2<RT2>,
   CGAL_VORONOI_DIAGRAM_2_INS::Identity_face_rejector<RT2>,
   CGAL_VORONOI_DIAGRAM_2_INS::Default_site_inserter
   <typename RT2::Geom_traits::Point_2,RT2>,
   CGAL_VORONOI_DIAGRAM_2_INS::Default_site_remover<RT2> >
{
  typedef typename RT2::Geom_traits::Weighted_point_2  Site_2;
};


//=========================================================================
//=========================================================================


template<class RT2>
struct Regular_triangulation_caching_degeneracy_removal_policy_2
  : public CGAL_VORONOI_DIAGRAM_2_INS::Caching_policy_base
  <RT2,
   CGAL_VORONOI_DIAGRAM_2_INS::Regular_triangulation_edge_tester_2<RT2>,
   CGAL_VORONOI_DIAGRAM_2_INS::Identity_face_rejector<RT2>,
   CGAL_VORONOI_DIAGRAM_2_INS::Default_site_inserter
   <typename RT2::Geom_traits::Point_2,RT2>,
   CGAL_VORONOI_DIAGRAM_2_INS::Default_site_remover<RT2> >
{
  typedef typename RT2::Geom_traits::Weighted_point_2  Site_2;
};

//=========================================================================
//=========================================================================

CGAL_END_NAMESPACE

#endif // CGAL_REGULAR_TRIANGULATION_ADAPTATION_POLICIES_2_H
