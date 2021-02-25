set(ITKCommon_SRCS
  itkMemoryProbesCollectorBase.cxx
  itkLogger.cxx
  itkLogOutput.cxx
  itkLoggerOutput.cxx
  itkProgressAccumulator.cxx
  itkHexahedronCellTopology.cxx
  itkFileOutputWindow.cxx
  itkSimpleFilterWatcher.cxx
  itkQuadrilateralCellTopology.cxx
  itkIterationReporter.cxx
  itkMemoryProbe.cxx
  itkTextOutput.cxx
  itkNumericTraitsTensorPixel2.cxx
  itkNumericTraitsFixedArrayPixel2.cxx
  itkConditionVariable.cxx
  itkBarrier.cxx
  itkSpatialOrientationAdapter.cxx
  itkOctreeNode.cxx
  itkThreadLogger.cxx
  itkNumericTraitsTensorPixel.cxx
  itkStdStreamLogOutput.cxx
  itkLightProcessObject.cxx
  itkImageToImageFilterCommon.cxx
  itkImageRegionSplitterDirection.cxx
  itkImageRegionSplitterMultidimensional.cxx
  itkNumericTraitsRGBAPixel.cxx
  itkRealTimeClock.cxx
  itkMemoryUsageObserver.cxx
  itkMersenneTwisterRandomVariateGenerator.cxx
  itkLoggerBase.cxx
  itkMultipleLogOutput.cxx
  itkQuadraticTriangleCellTopology.cxx
  itkTimeProbesCollectorBase.cxx
  itkSmapsFileParser.cxx
  itkTriangleCellTopology.cxx
  itkLoggerManager.cxx
  itkTimeProbe.cxx
  itkNumericTraitsRGBPixel.cxx
  itkTetrahedronCellTopology.cxx
  itkThreadedIndexedContainerPartitioner.cxx
  itkFloatingPointExceptions.cxx
  itkNumericTraitsDiffusionTensor3DPixel.cxx
  itkEquivalencyTable.cxx
  itkXMLFileOutputWindow.cxx
  itkXMLFilterWatcher.cxx
  itkStoppingCriterionBase.cxx
  itkArrayOutputSpecialization.cxx
  itkNumberToString.cxx
  itkRandomVariateGeneratorBase.cxx
  )

### generating libraries
itk_module_add_library( ITKCommon ${ITKCommon_SRCS})

target_link_libraries(ITKCommon LINK_PUBLIC itksys ITKVNLInstantiation)

if(UNIX)
  target_link_libraries(ITKCommon LINK_PUBLIC ${CMAKE_THREAD_LIBS} -lm)
  if(ITK_DYNAMIC_LOADING)
    target_link_libraries(ITKCommon LINK_PUBLIC ${CMAKE_DL_LIBS})
  endif()
endif()
