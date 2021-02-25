set(ITKFoundationCommon_SRC
  itkAtomicInt.cxx
  itkCompensatedSummation.cxx
  itkCovariantVector.cxx
  itkImageSourceCommon.cxx
  itkMultiThreader.cxx
  itkSimpleFastMutexLock.cxx
  itkCreateObjectFunction.cxx
  itkFastMutexLock.cxx
  itkMutexLock.cxx
  itkNumericTraitsCovariantVectorPixel.cxx
  itkNumericTraits.cxx
  itkIndent.cxx
  itkEventObject.cxx
  itkNumericTraitsVectorPixel.cxx
  itkObject.cxx
  itkProcessObject.cxx
  itkRealTimeInterval.cxx
  itkNumericTraitsFixedArrayPixel.cxx
  itkMetaDataObject.cxx
  itkMetaDataDictionary.cxx
  itkMetaDataObjectBase.cxx
  itkDataObject.cxx
  itkCommand.cxx
  itkNumericTraitsPointPixel.cxx
  itkLightObject.cxx
  itkRegion.cxx
  itkImageIORegion.cxx
  itkImageRegionSplitterBase.cxx
  itkImageRegionSplitterSlowDimension.cxx
  itkVersion.cxx
  itkProgressReporter.cxx
  itkExceptionObject.cxx
  itkVector.cxx
  itkRealTimeStamp.cxx
  itkDirectory.cxx
  itkTimeStamp.cxx
  itkObjectFactoryBase.cxx
  itkOutputWindow.cxx
  itkSimpleFastMutexLock.cxx
  itkSmartPointerForwardReferenceProcessObject.cxx
  itkThreadPool.cxx
  itkMath.cxx
  )

### generating libraries
#itk_module_add_library( ITKFoundationCommon ${ITKFoundationCommon_SRC})

add_library(ITKFoundationCommon ${ITKFoundationCommon_SRC})
itk_module_link_dependencies()
itk_module_target(ITKFoundationCommon)

target_link_libraries(ITKFoundationCommon LINK_PUBLIC itksys ITKVNLInstantiation)

if(UNIX)
  target_link_libraries(ITKFoundationCommon LINK_PUBLIC ${CMAKE_THREAD_LIBS} -lm)
  if(ITK_DYNAMIC_LOADING)
    target_link_libraries(ITKFoundationCommon LINK_PUBLIC ${CMAKE_DL_LIBS})
  endif()
endif()