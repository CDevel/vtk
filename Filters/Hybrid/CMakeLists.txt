set(Module_SRCS
  vtkBSplineTransform.cxx
  vtkDepthSortPolyData.cxx
  vtkDSPFilterDefinition.cxx
  vtkDSPFilterGroup.cxx
  vtkEarthSource.cxx
  vtkFacetReader.cxx
  vtkGreedyTerrainDecimation.cxx
  vtkGridTransform.cxx
  vtkImageToPolyDataFilter.cxx
  vtkImplicitModeller.cxx
  vtkPCAAnalysisFilter.cxx
  vtkPolyDataSilhouette.cxx
  #vtkPolyDataToImageStencil.cxx
  vtkProcrustesAlignmentFilter.cxx
  vtkProjectedTerrainPath.cxx
  vtkRenderLargeImage.cxx
  vtkTemporalDataSetCache.cxx
  vtkTemporalFractal.cxx
  vtkTemporalInterpolator.cxx
  vtkTemporalShiftScale.cxx
  vtkTemporalSnapToTimeStep.cxx
  vtkTransformToGrid.cxx
  vtkWeightedTransformFilter.cxx
  )

vtk_module_library(vtkFiltersHybrid ${Module_SRCS})
