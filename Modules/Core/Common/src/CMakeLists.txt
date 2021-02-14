
set(ITKCommon_SRCS
  itkMemoryProbesCollectorBase.cxx
  itkCreateObjectFunction.cxx
  itkLogger.cxx
  itkLogOutput.cxx
  itkLoggerOutput.cxx
  itkProgressAccumulator.cxx
  itkTotalProgressReporter.cxx
  itkHexahedronCellTopology.cxx
  itkFileOutputWindow.cxx
  itkSimpleFilterWatcher.cxx
  itkQuadrilateralCellTopology.cxx
  itkIterationReporter.cxx
  itkMemoryProbe.cxx
  itkTextOutput.cxx
  itkNumericTraitsTensorPixel2.cxx
  itkNumericTraitsFixedArrayPixel2.cxx
  itkStreamingProcessObject.cxx
  itkSpatialOrientationAdapter.cxx
  itkOctreeNode.cxx
  itkPlatformMultiThreader.cxx
  itkMetaDataObject.cxx
  itkThreadLogger.cxx
  itkNumericTraitsTensorPixel.cxx
  itkStdStreamLogOutput.cxx
  itkLightProcessObject.cxx
  itkImageIORegion.cxx
  itkImageSourceCommon.cxx
  itkImageToImageFilterCommon.cxx
  itkImageRegionSplitterDirection.cxx
  itkImageRegionSplitterMultidimensional.cxx
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
  itkRandomVariateGeneratorBase.cxx
  itkProgressTransformer.cxx
  itkSymmetricEigenAnalysis.cxx
  itkExtractImageFilter.cxx
  itkLoggerThreadWrapper.cxx
  itkFrustumSpatialFunction.cxx
  itkObjectStore.cxx
        itkGaussianDerivativeOperator.cxx
  )

# Prevent optimization from affecting the floating point calculation.
if( CMAKE_CXX_COMPILER MATCHES "^icc" )
  if( WIN32 )
    set_source_files_properties( itkCompensatedSummation.cxx PROPERTIES COMPILE_FLAGS /fp precise )
  else()
    set_source_files_properties( itkCompensatedSummation.cxx PROPERTIES COMPILE_FLAGS -fp-model precise )
  endif()
elseif( CMAKE_COMPILER_IS_GNUCXX )
  # -fno-associative-math appears to only be present in GCC 4.3 onwards.
  include( CheckCXXCompilerFlag )
  CHECK_CXX_COMPILER_FLAG( -fno-associative-math gcc_has_no_associative_math )
  if( gcc_has_no_associative_math )
    set_source_files_properties( itkCompensatedSummation.cxx PROPERTIES COMPILE_FLAGS -fno-associative-math )
  else()
    set_source_files_properties( itkCompensatedSummation.cxx PROPERTIES COMPILE_FLAGS -fno-unsafe-math-optimizations )
  endif()
elseif( MSVC )
  set_source_files_properties( itkCompensatedSummation.cxx PROPERTIES COMPILE_FLAGS -fp:precise )
endif()


### generating libraries
itk_module_add_library( ITKCommon ${ITKCommon_SRCS})

target_link_libraries(ITKCommon LINK_PUBLIC itksys ITKVNLInstantiation)

if(UNIX)
  target_link_libraries(ITKCommon LINK_PUBLIC ${CMAKE_THREAD_LIBS} -lm)
  if(ITK_DYNAMIC_LOADING)
    target_link_libraries(ITKCommon LINK_PUBLIC ${CMAKE_DL_LIBS})
  endif()
endif()

if(ITK_USE_TBB)
  # https://software.intel.com/en-us/node/506139
  # The macro TBB_DEPRECATED controls deprecated features.
  #      Define it to 0 to remove deprecated Intel® Threading Building Blocks (Intel® TBB) 2.1 interfaces.
  target_compile_definitions( ITKCommon PUBLIC TBB_DEPRECATED=0)
  # The macro TBB_USE_CAPTURED_EXCEPTION controls rethrow of exceptions within the library.
  #      Define TBB_USE_CAPTURED_EXCEPTION=0 to request rethrow of the exact exception.
  target_compile_definitions( ITKCommon PUBLIC TBB_USE_CAPTURED_EXCEPTION=0)
endif()
