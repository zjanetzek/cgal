// Copyright (c) 2005  INRIA (France).
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
// $Id$
// 
//
// Author(s)     : Laurent Saboret, Pierre Alliez


#ifndef CGAL_PARAM_MESH_PATCH_ITERATORS_H
#define CGAL_PARAM_MESH_PATCH_ITERATORS_H

#include <CGAL/Param_mesh_patch_vertex.h>
#include <CGAL/parameterization_assertions.h>

#include <list>

CGAL_BEGIN_NAMESPACE


/// The class Param_mesh_patch_vertex_list si the type of
/// the list of all vertices of a
/// Parameterization_mesh_patch_3<ParameterizationPatchableMesh_3> mesh
template<class ParameterizationPatchableMesh_3>
class Param_mesh_patch_vertex_list
    : public std::list< Param_mesh_patch_vertex<ParameterizationPatchableMesh_3> >
{
// Public types
public:

    /// Export template parameter type
    typedef ParameterizationPatchableMesh_3 Adaptor;
};


/// Param_mesh_patch_vertex_list_iterator is an iterator of a 
/// Param_mesh_patch_vertex_list list.
/// It provides the same features as 
/// Param_mesh_patch_vertex_list<ParameterizationPatchableMesh_3>::iterator
/// + a conversion to Param_mesh_patch_vertex_handle
template<class ParameterizationPatchableMesh_3>
class Param_mesh_patch_vertex_list_iterator
    : public Param_mesh_patch_vertex_list<ParameterizationPatchableMesh_3>::iterator
{
// Private types
private:

    typedef typename Param_mesh_patch_vertex_list<ParameterizationPatchableMesh_3>::iterator
                                            Base;
    typedef Param_mesh_patch_vertex_list_iterator
                                            Self;
    typedef Param_mesh_patch_vertex<ParameterizationPatchableMesh_3>
                                            Vertex;

// Public types
public:

    /// Export template parameter type
    typedef ParameterizationPatchableMesh_3 Adaptor;

// Public operations
public:

    Param_mesh_patch_vertex_list_iterator() {}
    Param_mesh_patch_vertex_list_iterator(const Base& toCopy) : Base(toCopy) {}

    Param_mesh_patch_vertex_list_iterator(const Self& toCopy) : Base(toCopy) {}
    Self& operator=(const Self& toCopy) { Base::operator=(toCopy); return *this; }

    Self & operator++()     { Base::operator++(); return *this; }
    Self & operator--()     { Base::operator--(); return *this; }
    Self operator++(int)    { Self tmp(*this); ++(*this); return tmp; }
    Self operator--(int)    { Self tmp(*this); --(*this); return tmp; }

    bool operator==(const Self& it) const { return Base::operator==(it); }
    bool operator!=(const Self& it) const { return ! (*this == it); }

    /// Comparison to NULL pointer
    bool operator==(CGAL_NULL_TYPE ptr) const {
        CGAL_parameterization_assertion(ptr == NULL);
        return Base::operator==( Base() );
    }
    bool operator!=(CGAL_NULL_TYPE ptr) const { return ! (*this == ptr); }

    /// Conversion to handle
    operator Param_mesh_patch_vertex_handle<Adaptor>() const {
        return &*(*this);
    }
    operator Param_mesh_patch_vertex_const_handle<Adaptor>() const {
        return &*(*this);
    }
};


/// Param_mesh_patch_vertex_list_const_iterator is an iterator of a 
/// Param_mesh_patch_vertex_list list.
/// It provides the same features as
/// Param_mesh_patch_vertex_list<ParameterizationPatchableMesh_3>::const_iterator
/// + a conversion to Param_mesh_patch_vertex_const_handle
template<class ParameterizationPatchableMesh_3>
class Param_mesh_patch_vertex_list_const_iterator
    : public Param_mesh_patch_vertex_list<ParameterizationPatchableMesh_3>::const_iterator
{
// Private types
private:

    typedef typename Param_mesh_patch_vertex_list<ParameterizationPatchableMesh_3>::const_iterator
                                            Base;
    typedef Param_mesh_patch_vertex_list_const_iterator
                                            Self;
    typedef Param_mesh_patch_vertex<ParameterizationPatchableMesh_3>
                                            Vertex;

// Public types
public:

    /// Export template parameter type
    typedef ParameterizationPatchableMesh_3 Adaptor;

// Public operations
public:

    Param_mesh_patch_vertex_list_const_iterator() {}
    Param_mesh_patch_vertex_list_const_iterator(const Base& toCopy) : Base(toCopy) {}

    Param_mesh_patch_vertex_list_const_iterator(const Self& toCopy) : Base(toCopy) {}
    Self& operator=(const Self& toCopy) { Base::operator=(toCopy); return *this; }

    Self & operator++()     { Base::operator++(); return *this; }
    Self & operator--()     { Base::operator--(); return *this; }
    Self operator++(int)    { Self tmp(*this); ++(*this); return tmp; }
    Self operator--(int)    { Self tmp(*this); --(*this); return tmp; }

    bool operator==(const Self& it) const { return Base::operator==(it); }
    bool operator!=(const Self& it) const { return ! (*this == it); }

    /// Comparison to NULL pointer
    bool operator==(CGAL_NULL_TYPE ptr) const {
        CGAL_parameterization_assertion(ptr == NULL);
        return Base::operator==( Base() );
    }
    bool operator!=(CGAL_NULL_TYPE ptr) const { return ! (*this == ptr); }

    /// Conversion to handle
    operator Param_mesh_patch_vertex_const_handle<Adaptor>() const {
        return &*(*this);
    }
};


CGAL_END_NAMESPACE

#endif //CGAL_PARAM_MESH_PATCH_ITERATORS_H

