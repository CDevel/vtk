/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkPBGLCollectGraph.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*-------------------------------------------------------------------------
  Copyright 2008 Sandia Corporation.
  Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
  the U.S. Government retains certain rights in this software.
-------------------------------------------------------------------------*/
// .NAME vtkPBGLCollectGraph - Collects all of the pieces of a
// distributed vtkGraph into a single, non-distributed vtkGraph.
//
// .SECTION Description
//
// This VTK class takes in a distributed vtkGraph and collects all of
// its vertices and edges into a single, non-distributed vtkGraph,
// which can either be stored on a single processor (all other
// processors will receive empty vtkGraphs) or can be replicated
// across all processors.
//
// When using this filter, be careful about collecting a very large
// distributed graph, because the processors receiving the resulting
// non-distributed vtkGraph may not have enough memory to represent
// the entire graph. This filter is most likely to be useful after a
// distributed vtkGraph algorithm has identified some small subset of
// the graph for further inspection, at which point it might make
// sense to collect that graph for, e.g., visualization.
//
// .SECTION See Also
// vtkGraph

#ifndef __vtkPBGLCollectGraph_h
#define __vtkPBGLCollectGraph_h

#include "vtkStdString.h" // For string type

#include <vtksys/stl/utility> // for pair
#include <vtksys/stl/numeric> // for accumulate, partial_sum
#include <vtksys/stl/functional> // for plus

#include "vtkGraphAlgorithm.h"

class vtkSelection;
class vtkDistributedGraphHelper;

class VTK_PARALLEL_EXPORT vtkPBGLCollectGraph : public vtkGraphAlgorithm
{
public:
  static vtkPBGLCollectGraph *New();
  vtkTypeRevisionMacro(vtkPBGLCollectGraph, vtkGraphAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // The rank of the target processor, where the non-distributed
  // vtkGraph will be created. All other target processors will
  // receive an empty, non-distributed vtkGraph. Only valid when
  // ReplicateGraph is false (the default). The default target
  // processor is rank 0.
  vtkGetMacro(TargetProcessor, int);
  vtkSetMacro(TargetProcessor, int);

  // Description:
  // When true, the non-distributed vtkGraph generated by this filter
  // will be replicated across all of the processors. Otherwise, the
  // non-distributed vtkGraph will only be available on the processor
  // with rank TargetProcessor. Defaults to false.
  vtkGetMacro(ReplicateGraph, bool);
  vtkSetMacro(ReplicateGraph, bool);
  vtkBooleanMacro(ReplicateGraph, bool);

  // Description:
  // When true, vertex data will be copied from the distributed graph
  // to the resulting non-distributed graph. Defaults to true.
  vtkGetMacro(CopyVertexData, bool);
  vtkSetMacro(CopyVertexData, bool);
  vtkBooleanMacro(CopyVertexData, bool);

  // Description:
  // When true, edge data will be copied from the distributed graph
  // to the resulting non-distributed graph. Defaults to true.
  vtkGetMacro(CopyEdgeData, bool);
  vtkSetMacro(CopyEdgeData, bool);
  vtkBooleanMacro(CopyEdgeData, bool);

protected:
  vtkPBGLCollectGraph();
  ~vtkPBGLCollectGraph();

  virtual int RequestData(
    vtkInformation *,
    vtkInformationVector **,
    vtkInformationVector *);

  virtual int FillInputPortInformation(
    int port, vtkInformation* info);

  virtual int FillOutputPortInformation(
    int port, vtkInformation* info);

  // Description:
  // Copy the structure of the incoming data set attributes (inAttrs)
  // to the output data set attributes (outAttrs), where the latter
  // has the given number of tuples.
  void CopyStructureOfDataSetAttributes(vtkDataSetAttributes *inAttrs,
                                        vtkDataSetAttributes *outAttrs,
                                        vtkIdType numberOfTuples);

private:
  int TargetProcessor;
  bool ReplicateGraph;
  bool CopyVertexData;
  bool CopyEdgeData;

  vtkPBGLCollectGraph(const vtkPBGLCollectGraph&);  // Not implemented.
  void operator=(const vtkPBGLCollectGraph&);  // Not implemented.

};

#endif
