set(ITKCommon_SRCS
  itkMemoryProbesCollectorBase.cxx
  itkCreateObjectFunction.cxx
  itkLogger.cxx
  itkLogOutput.cxx
  itkLoggerOutput.cxx
  itkProgressAccumulator.cxx
  itkMutexLock.cxx
  itkHexahedronCellTopology.cxx
  itkFileOutputWindow.cxx
  itkSimpleFilterWatcher.cxx
  itkObject.cxx
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
  itkMultiThreader.cxx
  itkMetaDataObject.cxx
  itkThreadLogger.cxx
  itkNumericTraitsTensorPixel.cxx
  itkStdStreamLogOutput.cxx
  itkLightProcessObject.cxx
  itkRegion.cxx
  itkImageSourceCommon.cxx
  itkImageToImageFilterCommon.cxx
  itkImageRegionSplitterDirection.cxx
  itkImageRegionSplitterMultidimensional.cxx
  itkFastMutexLock.cxx
  itkNumericTraitsRGBAPixel.cxx
  itkRealTimeClock.cxx
  itkCovariantVector.cxx
  itkMemoryUsageObserver.cxx
  itkMersenneTwisterRandomVariateGenerator.cxx
  itkLoggerBase.cxx
  itkNumericTraitsCovariantVectorPixel.cxx
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
  itkCompensatedSummation.cxx
  itkArrayOutputSpecialization.cxx
  itkNumberToString.cxx
  itkSmartPointerForwardReferenceProcessObject.cxx
  itkRandomVariateGeneratorBase.cxx
  itkAtomicInt.cxx
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
