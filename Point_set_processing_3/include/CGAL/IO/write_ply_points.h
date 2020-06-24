// Copyright (c) 2015  Geometry Factory
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org).
//
// $URL$
// $Id$
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
//
// Author(s) : Simon Giraudot

#ifndef CGAL_POINT_SET_PROCESSING_WRITE_PLY_POINTS_H
#define CGAL_POINT_SET_PROCESSING_WRITE_PLY_POINTS_H

#include <CGAL/license/Point_set_processing_3.h>

#include <CGAL/IO/helpers.h>
#include <CGAL/IO/PLY.h>

#include <CGAL/property_map.h>
#include <CGAL/point_set_processing_assertions.h>
#include <CGAL/Iterator_range.h>

#include <CGAL/boost/graph/Named_function_parameters.h>
#include <CGAL/boost/graph/named_params_helper.h>

#include <boost/utility/enable_if.hpp>
#include <boost/version.hpp>

#include <iostream>
#include <fstream>
#include <iterator>
#include <tuple>

#ifdef DOXYGEN_RUNNING
#define CGAL_BGL_NP_TEMPLATE_PARAMETERS NamedParameters
#define CGAL_BGL_NP_CLASS NamedParameters
#endif

namespace CGAL {

#ifdef DOXYGEN_RUNNING // Document some parts from Stream_support here for convenience
  /**
     \ingroup PkgPointSetProcessing3IOPly

     Generates a %PLY property handler to write 3D points. Points are
     written as 3 %PLY properties of type `FT` and named `x`, `y` and
     `z`. `FT` is `float` if the points use
     `CGAL::Simple_cartesian<float>` and `double` otherwise.

     \tparam PointMap the property map used to store points.

     \sa `write_PLY_with_properties()`
     \sa \ref IOStreamPLY
  */
  template <typename PointMap>
  std::tuple<PointMap, PLY_property<FT>, PLY_property<FT>, PLY_property<FT> >
  make_ply_point_writer(PointMap point_map);

  /**
     \ingroup PkgPointSetProcessing3IOPly

     Generates a %PLY property handler to write 3D normal
     vectors. Vectors are written as 3 %PLY properties of type `FT`
     and named `nx`, `ny` and `nz`. `FT` is `float` if the vectors use
     `CGAL::Simple_cartesian<float>` and `double` otherwise.

     \tparam VectorMap the property map used to store vectors.

     \sa `write_PLY_with_properties()`
     \sa \ref IOStreamPLY
  */
  template <typename VectorMap>
  std::tuple<VectorMap, PLY_property<FT>, PLY_property<FT>, PLY_property<FT> >
  make_ply_normal_writer(VectorMap normal_map);
#endif

/**
   \ingroup PkgPointSetProcessing3IOPly

   \brief Saves the range of `points` with properties to a .ply stream.

   %PLY is either ASCII or binary depending on the value of `CGAL::get_mode(os)`.

   Properties are handled through a variadic list of property
   handlers. A `PropertyHandler` can either be:

   - A `std::pair<PropertyMap, PLY_property<T> >` if the user wants
   to write a scalar value T as a %PLY property (for example, writing
   an `int` variable as an `int` %PLY property).

   - A `std::tuple<PropertyMap, PLY_property<T>...>` if the
   user wants to write a complex object as several %PLY
   properties. In that case, a specialization of `Output_rep` must
   be provided for `PropertyMap::value_type` that handles both ASCII
   and binary output (see `CGAL::get_mode()`).

   \tparam PointRange is a model of `ConstRange`. The value type of
   its iterator is the key type of the `PropertyMap` objects provided
   within the `PropertyHandler` parameter.
   \tparam PropertyHandler handlers to recover properties.

   \return `true` on success.

   \sa \ref IOStreamPLY
   \sa `make_ply_point_writer()`
   \sa `make_ply_normal_writer()`
*/
template <typename PointRange,
          typename ... PropertyHandler>
  bool write_PLY_with_properties(std::ostream& os, ///< output stream.
                                 const PointRange& points, ///< input point range.
                                 PropertyHandler&& ... properties) ///< parameter pack of property handlers
{
  CGAL_point_set_processing_precondition(points.begin() != points.end());

  if(!os)
  {
    std::cerr << "Error: cannot open file" << std::endl;
    return false;
  }

  // Write header
  os << "ply" << std::endl
     << ((get_mode(os) == IO::BINARY) ? "format binary_little_endian 1.0" : "format ascii 1.0") << std::endl
     << "comment Generated by the CGAL library" << std::endl
     << "element vertex " << points.size() << std::endl;

  IO::internal::output_property_header (os, std::forward<PropertyHandler>(properties)...);

  os << "end_header" << std::endl;

  // Write positions + normals
  for(typename PointRange::const_iterator it = points.begin(); it != points.end(); it++)
    IO::internal::output_properties (os, it, std::forward<PropertyHandler>(properties)...);

  return !os.fail();
}

/**
   \ingroup PkgPointSetProcessing3IOPly

   \brief Saves the range of `points` (positions + normals, if available) to a .ply stream.

    %PLY is either ASCII or binary depending on the value of `CGAL::get_mode(os)`.

   \tparam PointRange is a model of `ConstRange`. The value type of
   its iterator is the key type of the named parameter `point_map`.
   \tparam NamedParameters a sequence of \ref bgl_namedparameters "Named Parameters"

   \param os output stream
   \param points input point range
   \param np an optional sequence of \ref bgl_namedparameters "Named Parameters" among the ones listed below

   \cgalNamedParamsBegin
     \cgalParamNBegin{point_map}
       \cgalParamDescription{a property map associating points to the elements of the point range}
       \cgalParamType{a model of `ReadablePropertyMap` with value type `geom_traits::Point_3`}
       \cgalParamDefault{`CGAL::Identity_property_map<geom_traits::Point_3>`}
     \cgalParamNEnd

     \cgalParamNBegin{normal_map}
       \cgalParamDescription{a property map associating normals to the elements of the poing range}
       \cgalParamType{a model of `ReadablePropertyMap` with value type `geom_traits::Vector_3`}
       \cgalParamDefault{If this parameter is omitted, normals are not written in the output stream.}
     \cgalParamNEnd

     \cgalParamNBegin{geom_traits}
       \cgalParamDescription{an instance of a geometric traits class}
       \cgalParamType{a model of `Kernel`}
       \cgalParamDefault{a \cgal Kernel deduced from the point type, using `CGAL::Kernel_traits`}
     \cgalParamNEnd

     \cgalParamNBegin{stream_precision}
       \cgalParamDescription{a parameter used to set the precision (i.e. how many digits are generated) of the output stream}
       \cgalParamType{int}
       \cgalParamDefault{`6`}
     \cgalParamNEnd
   \cgalNamedParamsEnd

   \attention Be mindful of the flag `std::ios::binary` flag when creating the `ofstream` when writing a binary file

   \return `true` on success.
*/
template <typename PointRange,
          typename CGAL_BGL_NP_TEMPLATE_PARAMETERS>
bool write_PLY(std::ostream& os,
               const PointRange& points,
               const CGAL_BGL_NP_CLASS& np
#ifndef DOXYGEN_RUNNING
               , typename boost::enable_if<IO::internal::is_Range<PointRange> >::type* = nullptr
#endif
               )
{
  using parameters::choose_parameter;
  using parameters::get_parameter;

  // basic geometric types
  typedef typename CGAL::GetPointMap<PointRange, CGAL_BGL_NP_CLASS>::type PointMap;
  typedef typename Point_set_processing_3::GetNormalMap<PointRange, CGAL_BGL_NP_CLASS>::type NormalMap;

  bool has_normals = !(boost::is_same<NormalMap,
                       typename Point_set_processing_3::GetNormalMap<PointRange, CGAL_BGL_NP_CLASS>::NoMap>::value);

  PointMap point_map = choose_parameter<PointMap>(get_parameter(np, internal_np::point_map));
  NormalMap normal_map = choose_parameter<NormalMap>(get_parameter(np, internal_np::normal_map));

  if(!os)
  {
    std::cerr << "Error: cannot open file" << std::endl;
    return false;
  }

  const int precision = choose_parameter(get_parameter(np, internal_np::stream_precision), 6);
  os << std::setprecision(precision);

  if (has_normals)
    return write_PLY_with_properties(os, points,
                                     make_ply_point_writer(point_map),
                                     make_ply_normal_writer(normal_map));
  // else
  return write_PLY_with_properties(os, points, make_ply_point_writer(point_map));
}

template <typename PointRange>
bool write_PLY(std::ostream& os, const PointRange& points,
               typename boost::enable_if<IO::internal::is_Range<PointRange> >::type* = nullptr)
{
  return write_PLY(os, points, parameters::all_default());
}


/**
   \ingroup PkgPointSetProcessing3IOPly

   \brief Saves the range of `points` (positions + normals, if available) to a .ply stream.

   %PLY is either ASCII or binary depending on the value of `CGAL::get_mode(os)`.

   \tparam PointRange is a model of `ConstRange`. The value type of
   its iterator is the key type of the named parameter `point_map`.
   \tparam NamedParameters a sequence of \ref bgl_namedparameters "Named Parameters"

   \param filename the path to the output file
   \param points input point range
   \param np an optional sequence of \ref bgl_namedparameters "Named Parameters" among the ones listed below

   \cgalNamedParamsBegin
     \cgalParamNBegin{use_binary_mode}
       \cgalParamDescription{indicates whether data should be written in binary (`true`) or in ASCII (`false`)}
       \cgalParamType{Boolean}
       \cgalParamDefault{`true`}
     \cgalParamNEnd

     \cgalParamNBegin{point_map}
       \cgalParamDescription{a property map associating points to the elements of the point range}
       \cgalParamType{a model of `ReadablePropertyMap` with value type `geom_traits::Point_3`}
       \cgalParamDefault{`CGAL::Identity_property_map<geom_traits::Point_3>`}
     \cgalParamNEnd

     \cgalParamNBegin{normal_map}
       \cgalParamDescription{a property map associating normals to the elements of the poing range}
       \cgalParamType{a model of `ReadablePropertyMap` with value type `geom_traits::Vector_3`}
       \cgalParamDefault{If this parameter is omitted, normals are not written in the output stream.}
     \cgalParamNEnd

     \cgalParamNBegin{geom_traits}
       \cgalParamDescription{an instance of a geometric traits class}
       \cgalParamType{a model of `Kernel`}
       \cgalParamDefault{a \cgal Kernel deduced from the point type, using `CGAL::Kernel_traits`}
     \cgalParamNEnd

     \cgalParamNBegin{stream_precision}
       \cgalParamDescription{a parameter used to set the precision (i.e. how many digits are generated) of the output stream}
       \cgalParamType{int}
       \cgalParamDefault{`6`}
     \cgalParamNEnd
   \cgalNamedParamsEnd

   \return `true` on success.

   \sa \ref IOStreamPLY
*/
template <typename PointRange, typename CGAL_BGL_NP_TEMPLATE_PARAMETERS>
bool write_PLY(const char* filename,
               const PointRange& points,
               const CGAL_BGL_NP_CLASS& np
#ifndef DOXYGEN_RUNNING
               , typename boost::enable_if<IO::internal::is_Range<PointRange> >::type* = nullptr
#endif
               )
{
  const bool binary = CGAL::parameters::choose_parameter(CGAL::parameters::get_parameter(np, internal_np::use_binary_mode), true);
  if(binary)
  {
    std::ofstream os(filename, std::ios::binary);
    CGAL::set_mode(os, CGAL::IO::BINARY);
    return write_PLY(os, points, np);
  }
  else
  {
    std::ofstream os(filename);
    CGAL::set_mode(os, CGAL::IO::ASCII);
    return write_PLY(os, points, np);
  }
}

template <typename PointRange>
bool write_PLY(const char* filename, const PointRange& points,
               typename boost::enable_if<IO::internal::is_Range<PointRange> >::type* = nullptr)
{
  return write_PLY(filename, points, parameters::all_default());
}

template <typename PointRange, typename CGAL_BGL_NP_TEMPLATE_PARAMETERS>
bool write_PLY(const std::string& filename, const PointRange& points, const CGAL_BGL_NP_CLASS& np,
               typename boost::enable_if<IO::internal::is_Range<PointRange> >::type* = nullptr)
{
  return write_PLY(filename.c_str(), points, np);
}

template <typename PointRange>
bool write_PLY(const std::string& filename, const PointRange& points,
               typename boost::enable_if<IO::internal::is_Range<PointRange> >::type* = nullptr)
{
  return write_PLY(filename.c_str(), points, parameters::all_default());
}

#ifndef CGAL_NO_DEPRECATED_CODE

template <typename ForwardIterator,
          typename PointMap,
          typename VectorMap>
CGAL_DEPRECATED_MSG("you are using the deprecated V1 API of CGAL::write_ply_points_and_normals(), please update your code")
bool write_ply_points_and_normals(std::ostream& os, ///< output stream.
                                  ForwardIterator first, ///< first input point.
                                  ForwardIterator beyond, ///< past-the-end input point.
                                  PointMap point_map, ///< property map: value_type of OutputIterator -> Point_3.
                                  VectorMap normal_map) ///< property map: value_type of OutputIterator -> Vector_3.
{
  CGAL::Iterator_range<ForwardIterator> points (first, beyond);
  return write_PLY(os, points, parameters::point_map(point_map)
                                              .normal_map(normal_map));
}

template <typename ForwardIterator,
          typename VectorMap>
CGAL_DEPRECATED_MSG("you are using the deprecated V1 API of CGAL::write_ply_points_and_normals(), please update your code")
bool write_ply_points_and_normals(std::ostream& os, ///< output stream.
                                  ForwardIterator first, ///< first input point.
                                  ForwardIterator beyond, ///< past-the-end input point.
                                  VectorMap normal_map) ///< property map: value_type of OutputIterator -> Vector_3.
{
  CGAL::Iterator_range<ForwardIterator> points(first, beyond);
  return write_PLY(os, points, parameters::normal_map (normal_map));
}

template <typename ForwardIterator,
          typename PointMap >
CGAL_DEPRECATED_MSG("you are using the deprecated V1 API of CGAL::write_ply_points(), please update your code")
bool write_ply_points(std::ostream& os, ///< output stream.
                      ForwardIterator first, ///< first input point.
                      ForwardIterator beyond, ///< past-the-end input point.
                      PointMap point_map) ///< property map: value_type of OutputIterator -> Point_3.
{
  CGAL::Iterator_range<ForwardIterator> points(first, beyond);
  return write_PLY(os, points, parameters::point_map(point_map));
}

template <typename ForwardIterator >
CGAL_DEPRECATED_MSG("you are using the deprecated V1 API of CGAL::write_ply_points(), please update your code")
bool write_ply_points(std::ostream& os, ///< output stream.
                      ForwardIterator first, ///< first input point.
                      ForwardIterator beyond) ///< past-the-end input point.
{
  CGAL::Iterator_range<ForwardIterator> points (first, beyond);
  return write_PLY(os, points);
}

#endif // CGAL_NO_DEPRECATED_CODE

#ifndef CGAL_NO_DEPRECATED_CODE

/**
\ingroup PkgPointSetProcessing3IODeprecated

\deprecated This function is deprecated since \cgal 5.2,
            \link PkgPointSetProcessing3IOPly `CGAL::write_PLY_with_properties()` \endlink should be used instead.
*/
template <typename PointRange,
          typename ... PropertyHandler>
CGAL_DEPRECATED bool write_ply_points_with_properties(std::ostream& os, ///< output stream.
                                                      const PointRange& points, ///< input point range.
                                                      PropertyHandler&& ... properties) ///< parameter pack of property handlers
{
  return write_PLY_with_properties(os, points, std::forward<PropertyHandler>(properties)...);
}

/**
\ingroup PkgPointSetProcessing3IODeprecated

\deprecated This function is deprecated since \cgal 5.2,
            \link PkgPointSetProcessing3IOPly `CGAL::write_PLY()` \endlink should be used instead.
*/
template <typename PointRange, typename CGAL_BGL_NP_TEMPLATE_PARAMETERS>
CGAL_DEPRECATED bool write_ply_points(std::ostream& os, const PointRange& points, const CGAL_BGL_NP_CLASS& np)
{
  return write_PLY(os, points, np);
}

/// \cond SKIP_IN_MANUAL

template <typename PointRange>
CGAL_DEPRECATED bool write_ply_points(std::ostream& os, const PointRange& points)
{
  return write_PLY(os, points, parameters::all_default());
}

/// \endcond

#endif // CGAL_NO_DEPRECATED_CODE

} // namespace CGAL

#endif // CGAL_POINT_SET_PROCESSING_WRITE_PLY_POINTS_H
