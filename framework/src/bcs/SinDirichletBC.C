/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "SinDirichletBC.h"

template<>
InputParameters validParams<SinDirichletBC>()
{
  InputParameters params = validParams<NodalBC>();
  params.set<Real>("initial")=0.0;
  params.set<Real>("final")=0.0;
  params.set<Real>("duration")=0.0;

  return params;
}

SinDirichletBC::SinDirichletBC(const InputParameters & parameters) :
    NodalBC(parameters),
    _initial(getParam<Real>("initial")),
    _final(getParam<Real>("final")),
    _duration(getParam<Real>("duration"))
{
}

Real
SinDirichletBC::computeQpResidual()
{
  Real value;

  if (_t < _duration)
    value = _initial + (_final-_initial) * std::sin((0.5/_duration) * libMesh::pi * _t);
  else
    value = _final;

  return _u[_qp]- value;
}

